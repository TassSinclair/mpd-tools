make:
	gcc -lmpdclient mpd-seek.c -o bin/mpd-seek
	gcc -lmpdclient mpd-adjust-volume.c -o bin/mpd-adjust-volume
	chmod u+x bin/*
