#This is a stupid simple program that just sends the stuff from the serial port


#Test whether a device is specified
if [ -z "$1" ]
	then
		echo "No device supplied"
		exit
fi


#Test whether a directory is specified
if [ -z "$2" ]
	then
		echo "No directory supplied. Use '.' to put it in the current directory"
		exit
fi

stty -F $1 115200
mkdir -p $2
cd $2
more $1 > $(date +"%T;%m-%d-%y")
