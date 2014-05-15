#!/bin/bash
#this is a simple script designed to run the serialstreamtest program and log
#to a file
#serial.sh $Device $Folderpath

#Test whether a device is specified
if [ -z "$1" ]
	then
		echo "No device supplied"
		exit
fi

#Test whether a directory is specified
if [ -z "$1" ]
	then
		echo "No directory supplied. Use '.' to put it in the current directory"
		exit
fi

mkdir -p $2
cd $2
../serialstreamtest $1 | tee $(date +"%T;%m-%d-%y")

