pathgame: main.c buttons.c
	gcc -g -lraylib main.c buttons.c -Werror -Wfatal-errors -Wpedantic --pedantic-errors -Wall -Wextra -Wformat -pedantic -Wimplicit -o pathgame
