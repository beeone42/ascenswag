# ascenswag
la musique dans l'ascenswag

installer vlc-nox

mettre www/* dans la racine d'apache/nginx, installer php

mettre play.sh et volume-boot.sh dans /home/pi/

mettre les musiques en .aac dans /MP3/ et mapper /MP3/ dans la conf web sur /MP3/


Ajouter dans /etc/rc.local

/home/pi/volume-boot.sh

/usr/bin/sudo -u pi /home/pi/play.sh > /dev/null &
