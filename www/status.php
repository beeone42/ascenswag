<?php

header("Content-type: application/json");

$xml_string = file_get_contents("http://127.0.0.1:8080/requests/status.xml");
$xml = simplexml_load_string($xml_string);
echo json_encode($xml);

?>