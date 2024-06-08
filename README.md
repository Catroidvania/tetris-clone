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

## playing the game

controls are:
- left and right arrow keys move piece left and right
- down arrow soft drops
- up arrow hard drops
- z and x are rotate counterclockwise and clockwise respectively
- space and arrow keys to navigate the menu

### solo

single player mode

clear stack blocks and clear lines to rack up score

clearing multiple lines at once will give you more score than clearing each individually

the more lines you clear the faster the game will go

play until you lose

### vs cpu

play against the computer

similar to singleplayer but with a few additions

clearing more than one line will send "junk" pieces to the opponent

survive longer than the computer to win

### other

psst

press shift while selecting a mode to try one of the secret alt modes

youll have to figure out the controls yourself though

# and dont forget to

have fun
