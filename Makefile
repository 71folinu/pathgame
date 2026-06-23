bin: main.c
	gcc -g -lraylib main.c -Werror -Wfatal-errors -Wpedantic --pedantic-errors -Wall -Wextra -Wformat -pedantic -Wimplicit -o bin
