#!/usr/bin/tcsh

cd /MP3/ || exit

while (1)
    date >> /home/pi/vlc.log
    /usr/bin/vlc -I http --loop *.aac >> /home/pi/vlc.log
    sleep 10
end
