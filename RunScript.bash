#!/usr/bin/env bash
if ! test -f ./testRun
then
  echo "Error: file 'testRun' does not exist."
  exit 1
fi
echo  #blank line, to separate the running program from everything else
if [ "$1" == "valgrind" ]   #checks if the first arg to this script is 'valgrind'
then
  valgrind --leak-check=full --show-reachable=yes --track-origins=yes -s ./testRun /home/SmartFridge/CLionProjects/atlas-monty/test_code.m  #runs the program with valgrind (usage: "./TestRunScript.bash valgrind")
else
  ./testRun /home/SmartFridge/CLionProjects/atlas-monty/test_code.m   #runs the program (usage: "./TestRunScript.bash")
fi
exitcode=$?   #save exit code
echo  #blank line, to separate the running program from everything else
echo "Process finished with exit code $exitcode."   #print exit code
