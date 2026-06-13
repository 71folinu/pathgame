#!/usr/bin/env bash
cd ~/pathgame
echo 'printing current directory...'
pwd
while [ true ]; do
  echo ---------------------------------------------------------------------------------------------------
  rm pathgame
  make
  ./pathgame
  rm pathgame
  read
  echo ---------------------------------------------------------------------------------------------------
done
