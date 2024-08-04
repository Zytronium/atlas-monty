#!/usr/bin/env bash
gcc -ggdb3 *.c -o testRun -Wall -Wextra -pedantic -std=gnu89  #compiles
if ! test -f ./testRun  #checks if compile failed
then
  echo "Couldn't compile."
  exit
fi
chmod +x ./testRun  #make file executable
echo  #blank line, to separate the running program from everything else
if [ "$1" == "valgrind" ]   #checks if the first arg to this script is 'valgrind'
then
  valgrind --leak-check=full --show-reachable=yes --track-origins=yes -s ./testRun test_code.m  #runs the program with valgrind (usage: "./TestRunScript.bash valgrind")
else
  ./testRun test_code.m   #runs the program (usage: "./TestRunScript.bash")
fi
exitcode=$?   #save exit code
echo  #blank line, to separate the running program from everything else
echo "Process finished with exit code $exitcode."   #print exit code
rm testRun  #delete test file
