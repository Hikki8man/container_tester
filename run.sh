#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2`
yellow=`tput setaf 3`
cyan=`tput setaf 6`
reset=`tput sgr0`
#containers=(vector stack map)
containers=(vector stack)

#if arguments are specified, only run those tests (e.g. ./run.sh vector)
if [ $# -ne 0 ]; then
	containers=($@);
fi

invalid=()

#compile specified tests
mkdir -p make_errors
echo "${cyan}Compiling tests...${reset}"
for container in ${containers[@]}; do
	echo -n "${cyan}${container}... ${reset}"
	make -s $container 2> make_errors/"$container".txt
	if [ $? -eq 0 ]; then
		echo "✅"
	else
		echo "❌"
		invalid+=($container)
	fi
	if [ ! -s make_errors/"$container".txt ]; then #remove error file if no errors happened (a.k.a if error file is empty)
		rm -f make_errors/"$container".txt
	fi
	make -s clean
done

if [ -n "$invalid" ]; then
	echo "💡${cyan}Compilation errors logged to make_errors/<container>.txt${reset}"
fi

#remove tests that did not compile from the list of tests to run
for rm in ${invalid[@]}
do
   containers=("${containers[@]/$rm}")
done


if [ -z "$containers" ]; then
    echo "${red}No tests to run :(${reset}"
else
   	echo "${cyan}Running tests...${reset}"
	sleep 1
fi

#run specified tests individually
for container in ${containers[@]}; do
	./exe/ft_$container && ./exe/std_$container
	./exe/checker $container ./testOutput/ft_"$container"_out.txt ./testOutput/std_"$container"_out.txt
	if command -v leaks > /dev/null; then
		echo "${cyan}Testing leaks: ${reset}"
		leaks -q -atExit -- ./exe/ft_$container > /dev/null 2> /dev/null
		if [ $? -eq 0 ]; then
			echo "${green}No leaks detected :)${reset}"
		else
			echo "${red}Leaks detected !!${reset}"
		fi
	fi
	echo
done