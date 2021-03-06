#!/bin/bash
echo "This script only works on files already on the disk. It does not work on devices. Use picocom and tee for that."
echo "Takes 3 files as argument"
read -s -p "Enter password for remote server: " remotepass


while :
	do
	./fileparse $1
	./fileparse $2
	./fileparse $3

	mkdir -p ./graphs
	gnuplot -persist -e "load 'gnuscript'"
	
	sshpass -p $remotepass scp graphs/*.svg pi@ganger.webhop.org:/var/www/science_honors/
	echo "Waiting for new data"
	sleep 5
	echo "Back to Work"
done 

#Extraneous information for reference.
#dataArray is current with Data class as of 05/17/2014

#Data being stored in the array
#dataArray[0] = index++;
#dataArray[1] = timeCollect;
#dataArray[2] = temp;
#dataArray[3] = pres;
#dataArray[4] = humi;
#dataArray[5] = CO2;
#dataArray[6] = UV;
#dataArray[7] = O3;
#dataArray[8] = IRup;
#dataArray[9] = IRdown;
#dataArray[10] = visUp;
#dataArray[11] = visDown;
