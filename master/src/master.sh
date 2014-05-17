#!/bin/bash
#This program calls the master.cc program and liveplot.sh. The master handles
#the communications with the radio/balloon and writes the transmissions it
#receives to files. Live plot.sh then goes through those files and turns them
#into 1 large .csv (using aggregate.cpp) and then runs gnuplot on them to create
#7 graphs (altitude, pressure, humidity, CO2, UV, IRup, IRdown, O3).

#Usage:
#	./master.sh $DEVICE $DIRECTORY

#Make sure the right number of argmuents have been specified
if [  $# -ne 2 ]
	then
		echo "Wrong number of arguments"
		exit
fi

#Check to make sure that the device exists
if [ ! -f $1 ]
	then
		echo "Device does not exist"
		exit
fi

#Check to make sure that the directory argument is kosher
if [ -z "$2" ]
	then
		echo "No directory supplied."
		exit
fi

#Save the current directory to run master and liveplot
path = $(pwd)
cd $2

#set the baud of the input device to 115200 with stty
stty -F $1 115200
sh $3/liveplot.sh > /dev/null & 
$3/master.cc


