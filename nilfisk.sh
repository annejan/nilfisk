#!/bin/bash

if [[ -z $1 ]] 
then
	echo Usage $0 /dev/cu.usbmodemXXX
	exit
fi

cat $1 &

nc -l 9001 > $1
