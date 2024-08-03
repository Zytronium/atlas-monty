#!/usr/bin/env bash
gcc -ggdb3 *.c -o testRun -Wall -Wextra -pedantic -std=gnu89  #compiles
if ! test -f ./testRun  #checks if compile failed
then
  echo "Couldn't compile."
  exit
fi
echo "Compiled Successfully. Run './testRun' to run the program, or use the 'RunScript.bash' script."
chmod +x ./testRun  #make file executable
