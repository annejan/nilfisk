#!/usr/bin/env bash

if [[ -z $2 ]] 
then
	echo Usage $0 PORT /dev/cu.usbmodemXXX
	exit
fi

cat $2 &

nc -l $1 > $2
