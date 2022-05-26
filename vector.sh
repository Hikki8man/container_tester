#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2`
yellow=`tput setaf 3`
cyan=`tput setaf 6`
reset=`tput sgr0`

echo "${cyan}Compiling test...${reset}"
make -s vector
make -s clean
#testing vector
./exe/ft_vector && ./exe/std_vector
./exe/checker Vector ./testOutput/ft_vector_out.txt ./testOutput/std_vector_out.txt
if command -v leaks > /dev/null; then
	echo "${cyan}Testing leaks: ${reset}"
	leaks -q -atExit -- ./exe/ft_vector > /dev/null 2> /dev/null
	if [ $? -eq 0 ]; then
		echo "${green}No leaks detected :)${reset}"
	else
		echo "${red}Leaks detected !!${reset}"
	fi
fi
