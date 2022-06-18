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
./exe/ft_map && ./exe/std_map
./exe/checker Map ./testOutput/ft_map_out.txt ./testOutput/std_map_out.txt
if command -v leaks > /dev/null; then
	echo "${cyan}Testing leaks: ${reset}"
	leaks -q -atExit -- ./exe/ft_stack > /dev/null 2> /dev/null
	if [ $? -eq 0 ]; then
		echo "${green}No leaks detected :)${reset}"
	else
		echo "${red}Leaks detected !!${reset}"
	fi
fi