# ascenswag

**la musique dans l'ascenswag**

Le systeme est composé:
- d'un raspberry pi pour diffuser la musique
- d'enceintes 2.1 en sortie du raspberry pi
- d'un arduino equipé d'un micro: https://www.adafruit.com/product/1063
- de 4 bandes de 144 LEDs RGB NeoPixel: https://www.adafruit.com/product/1507
- de 4 alimentations 5V 10A: https://www.adafruit.com/products/658

# code arduino

ascenswag.ino contient le code pour piloter les bandes de LEDs RGB.
Il est base sur l'exemple suivant d'adafruit:

https://learn.adafruit.com/led-ampli-tie

    [arduino][D6]---[bande1 (144 leds)]---[bande2 (144 leds)]
             [D7]---[bande3 (144 leds)]---[bande4 (144 leds)]

les bandes 1 et 2 sont en serie, ainsi que 3 et 4

    ==============================
    | bande1              bande2 |
    | 1                      145 |
    | .                        . |
    | .                        . |
    | 144                    288 |
    | -------------------------- |
    | 144                    288 |
    | .                        . |
    | .                        . |
    | 1                      145 |
    |bande3               bande4 |
    =====[------porte-----]=======

[![Ascenswag](http://img.youtube.com/vi/s792ASOWUyY/0.jpg)](http://www.youtube.com/watch?v=s792ASOWUyY)

# musique sur raspberry pi

installer vlc-nox

mettre www/* dans la racine d'apache/nginx, installer php

mettre play.sh et volume-boot.sh dans /home/pi/

mettre les musiques en .aac dans /MP3/ et mapper /MP3/ dans la conf web sur /MP3/


Ajouter dans /etc/rc.local

/home/pi/volume-boot.sh

/usr/bin/sudo -u pi /home/pi/play.sh > /dev/null &



![screenshot](https://cloud.githubusercontent.com/assets/11945268/17586535/ac45769c-5fc2-11e6-90de-bc36e35a115d.png "ascenswag screenshot")
