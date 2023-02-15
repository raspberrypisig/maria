# Holo Assistant for Web

Based on 

https://github.com/jessp/holo-assistant


which in turn is based on 

https://github.com/roxanneluo/Pepper-s-Cone-Unity


### Raylib

Raylib needs to be recompiled (remove previous librarylib.a)
I used the instructions for Raspberry Pi 

https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)


### raylib web template

This repo started with

https://github.com/raysan5/raylib-game-template

and then ported Holo Assistant code for PLATFORM_WEB

To compile this code:

Open a terminal, and type(only need to do this once per terminal tab/session)

```
source ~/emsdk/
```

This sets up the right environment variables for emscripten

Then to compile

```
make PLATFORM=PLATFORM_WEB -B -e
```

Depending on the contents of the Makefile(look for PROJECT_NAME), you should have a html and a js file produced from the c file. Just host the directory(using either python or nodejs), eg.

```
sudo python -m http.server 80
```

Then go to browser, and point to http://IP_ADDRESS/maria.html


