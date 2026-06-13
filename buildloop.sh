#!/usr/bin/env bash
cd ~/pathgame
echo 'printing current directory...'
pwd
while [ true ]; do
  echo ---------------------------------------------------------------------------------------------------
  rm a.out
  gcc -g -lraylib main.c -Werror -Wfatal-errors -Wpedantic --pedantic-errors -Wall -Wextra -Wformat -pedantic -Wimplicit
  ./a.out
  read
  echo ---------------------------------------------------------------------------------------------------
done
