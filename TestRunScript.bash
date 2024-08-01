#!/usr/bin/env bash
gcc  -ggdb3 *.c -o testRun -Wall -Wextra -pedantic -std=gnu89   #compiles
if ! test -f ./testRun  #checks if compile failed
then
  echo "Couldn't compile."
  exit
fi
chmod +x ./testRun  #make file executable
echo  #blank line, to separate the running program from everything else
./testRun /home/SmartFridge/CLionProjects/atlas-monty/14  #runs the program
exitcode=$?   #save exit code
echo  #blank line, to separate the running program from everything else
echo "Process finished with exit code $exitcode."   #print exit code
rm testRun  #delete test file

