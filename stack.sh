#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2`
yellow=`tput setaf 3`
cyan=`tput setaf 6`
reset=`tput sgr0`

echo "${cyan}Compiling test...${reset}"
make -s stack
make -s clean
#testing stack
./exe/ft_stack && ./exe/std_stack
./exe/checker Stack ./testOutput/ft_stack_out.txt ./testOutput/std_stack_out.txt
if command -v leaks > /dev/null; then
	echo "${cyan}Testing leaks: ${reset}"
	leaks -q -atExit -- ./exe/ft_stack > /dev/null 2> /dev/null
	if [ $? -eq 0 ]; then
		echo "${green}No leaks detected :)${reset}"
	else
		echo "${red}Leaks detected !!${reset}"
	fi
fi