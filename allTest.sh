#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2`
yellow=`tput setaf 3`
cyan=`tput setaf 6`
reset=`tput sgr0`

echo "${cyan}Compiling test...${reset}"
make -s re
if [ $? -eq 0 ]; then
	echo "${green}Compilation successful!${reset}"
else
	echo "${red}Compilation failed!${reset}"
	exit 1
fi
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

#testing map
./exe/ft_map && ./exe/std_map
./exe/checker Map ./testOutput/ft_map_out.txt ./testOutput/std_map_out.txt
if command -v leaks > /dev/null; then
	echo "${cyan}Testing leaks: ${reset}"
	leaks -q -atExit -- ./exe/ft_map > /dev/null 2> /dev/null
	if [ $? -eq 0 ]; then
		echo "${green}No leaks detected :)${reset}"
	else
		echo "${red}Leaks detected !!${reset}"
	fi
fi
