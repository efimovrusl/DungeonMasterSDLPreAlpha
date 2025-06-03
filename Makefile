all: game

game:
	clang -std=c11 -Wall -pedantic src/*.c -I resource/SDL -L resource/SDL/lib -lSDL2 -lSDL2_mixer -o endgame

inst: install_lib

rem_inst: uninstall_lib

install_lib:
	rm -drf resource/SDL
	brew install sdl2
	brew install sdl2_mixer
	mkdir resource/SDL
	mkdir resource/SDL/lib
	sh resource/scripts/install_lib.sh

uninstall_lib:
	rm -drf resource/SDL

reinstall:
	make uninstall_lib
	make install_lib
	make reinstall_brew
	make inst
	make

install_brew:
	sh resource/scripts/install_brew.sh
