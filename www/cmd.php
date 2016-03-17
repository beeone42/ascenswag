<?php

// vlc web interface proxy, with basic ip filtering

$ipc = substr($_SERVER['REMOTE_ADDR'], 0, 6);
if (($ipc != "10.42.") && ($ipc != "10.43."))
{
	header("HTTP/1.0 404 Not Found");
	exit ;
}

file_get_contents("http://localhost:8080/requests/status.xml?command=".$_REQUEST['cmd']."&val=".urlencode($_REQUEST['param']));
echo "OK";

?>