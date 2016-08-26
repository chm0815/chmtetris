chmtetris
=========

My old tetris written in C using allegro. 
tested on Windows XP,Vista,7, Linux (Ubuntu 8.1 or newer)

![screenshot](/tetris_screenshot.png?raw=true "Tetris Screenshot")


**compile:**


Install the allegro library:
 sudo apt-get install liballegro4.2-dev

compile with:
gcc -o tetris *.c $(allegro-config --libs)
