
#include <Adafruit_NeoPixel.h>

#define N_PIXELS	288					// Number of pixels in strand
#define MIC_PIN		4					// Microphone is attached to this analog pin
#define LED_PIN		6					// NeoPixel LED strand is connected to this pin
#define LED_PIN2	7					// NeoPixel LED strand is connected to this pin
#define DC_OFFSET	0					// DC offset in mic signal - if unusure, leave 0
#define NOISE		10					// Noise/hum/interference in mic signal
#define SAMPLES		10					// Length of buffer for dynamic level adjustment
#define TOP			((N_PIXELS/2) + 2)		// Allow dot to go slightly off scale
#define PEAK_FALL	5					// Rate of peak falling dot

byte	peak = 0;
byte	dotCount = 0;
byte	volCount  = 0;
int	vol[SAMPLES];					        // Collection of prior volume samples
int	lvl = 10;						// Current "dampened" audio level
int	minLvlAvg = 0;					        // For dynamic adjustment of graph low & high
int	maxLvlAvg = 512;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(N_PIXELS, LED_PIN2, NEO_GRB + NEO_KHZ800);

void setup() {
	Serial.begin(115200);
	analogReference(EXTERNAL);
	memset(vol, 0, sizeof(vol));
	strip.begin();
	strip2.begin();
}

void loop() {
	int i, j, k = 0;

	bargraph();
}

void setpixel(Adafruit_NeoPixel *strip1, Adafruit_NeoPixel *strip2, int i, uint32_t w)
{
    strip1->setPixelColor(i      , w);
    strip1->setPixelColor(i + (N_PIXELS / 2), w);
    strip2->setPixelColor(i      , w);
    strip2->setPixelColor(i + (N_PIXELS / 2), w);
}

void setpixel(Adafruit_NeoPixel *strip1, Adafruit_NeoPixel *strip2, int i, int r, int g, int b)
{
    strip1->setPixelColor(i      , r, g, b);
    strip1->setPixelColor(i + (N_PIXELS / 2), r, g, b);
    strip2->setPixelColor(i      , r, g, b);
    strip2->setPixelColor(i + (N_PIXELS / 2), r, g, b);
}


void bargraph(void) {
	uint8_t  i;
	uint16_t minLvl, maxLvl;
	int      n, height;

	n = analogRead(MIC_PIN);			// Raw reading from mic
        Serial.print ("Mic: ");
        Serial.println (n);
	n = abs(n - 512 - DC_OFFSET);		// Center on zero
	n = (n <= NOISE) ? 0 : (n - NOISE);	// Remove noise/hum
	lvl = ((lvl * 7) + n) >> 3;			// "Dampened" reading (else looks twitchy)
	height = TOP * (lvl - minLvlAvg) / (long)(maxLvlAvg - minLvlAvg);

	if (height < 0L)
		height = 0;
	else if (height > TOP)
		height = TOP;
	if (height > peak)
		peak = height;

	for(i=0; i< (N_PIXELS / 2); i++) {
		if (i >= height)
			setpixel(&strip, &strip2, i, 0, 0, 0);
		else
			setpixel(&strip, &strip2, i, Wheel(map(i,0,(strip.numPixels() / 2) - 1,30,150)));
	}

	if (peak > 0 && peak <= (N_PIXELS/2)-1)
		setpixel(&strip, &strip2, peak,Wheel(map(peak,0,(strip.numPixels() / 2) - 1,30,150)));

	strip.show();
	strip2.show();

	if (++dotCount >= PEAK_FALL) {
		if (peak > 0)
			peak--;

		dotCount = 0;
	}

	vol[volCount] = n;
	if (++volCount >= SAMPLES)
		volCount = 0;

	minLvl = maxLvl = vol[0];
	for(i=1; i<SAMPLES; i++) {
		if (vol[i] < minLvl)
			minLvl = vol[i];
		else if (vol[i] > maxLvl)
			maxLvl = vol[i];
	}

	if ((maxLvl - minLvl) < TOP)
		maxLvl = minLvl + TOP;

	minLvlAvg = (minLvlAvg * 63 + minLvl) >> 6; // Dampen min/max levels
	maxLvlAvg = (maxLvlAvg * 63 + maxLvl) >> 6; // (fake rolling average)
}

uint32_t Wheel(byte WheelPos) {
	if (WheelPos < 85) {
		return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	} else if (WheelPos < 170) {
		WheelPos -= 85;
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	} else {
		WheelPos -= 170;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}

