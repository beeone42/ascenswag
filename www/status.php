<?php

header("Content-type: application/json");

// {"state":"playing","audiofilters":{"filter_0":{}},"subtitledelay":"0","length":"254","fullscreen":"0","apiversion":"3","repeat":"false","rate":"1","random":"false","currentplid":"21","loop":"true","audiodelay":"0","videoeffects":{"hue":"0","contrast":"1","saturation":"1","brightness":"1","gamma":"1"},"time":"108","equalizer":{},"version":"2.2.1 Terry Pratchett (Weatherwax)","volume":"256","position":"0.43047338724136","information":{"category":[{"@attributes":{"name":"meta"},"info":"Dizkodeath - Orchid (Gost Remix)-e4ViK55osFE.aac"},{"@attributes":{"name":"Stream 0"},"info":["Stereo","Audio","44100 Hz","MPEG AAC Audio (mp4a)"]}]},"stats":{"decodedaudio":"4658","displayedpictures":"0","demuxdiscontinuity":"0","demuxreadbytes":"3432357","readpackets":"1129","playedabuffers":"4658","demuxcorrupted":"0","lostabuffers":"0","sendbitrate":"0","sentbytes":"0","averagedemuxbitrate":"0","inputbitrate":"0.033075228333473","lostpictures":"0","averageinputbitrate":"0","demuxbitrate":"0.031837690621614","decodedvideo":"0","demuxreadpackets":"0","sentpackets":"0","readbytes":"3466240"}}

$xml_string = file_get_contents("http://127.0.0.1:8081/requests/status.xml");
$xml = simplexml_load_string($xml_string);

//print_r($xml);

$fname = @strval($xml->information->category->info);
if (preg_match('/.*-([A-Za-z0-9_-]{11})\.aac/', $fname, $regs))
{
	$xml->vidid = $regs[1];
}
if (preg_match('/.*-([A-Za-z0-9_-]{11})\.mp3/', $fname, $regs))
{
	$xml->vidid = $regs[1];
}

echo json_encode($xml);

?>
