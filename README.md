# cetris

a tetromino stacking game of the cursed skull

## compiling

to compile this program you need:
- a `C` compiler (we are using gcc)
- `SDL`, `SDL_mixer`, and `SDL_image`

### debian

to install the required dependancies run:
```sh
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
```

to compile the program:
```sh
git clone https://github.com/Catroidvania/tetris-clone.git
cd tetris-clone
make
```

run the program with:
```sh
./bin/cetris
```

have fun
