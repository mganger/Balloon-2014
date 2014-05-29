#Made to test the ability to shell script the password stuff so that it can be as secure as possible
#tested, and it works. Pretty simple stuff

read -s -p "Enter password for remote server: " remotepass

sshpass -p $remotepass scp *.svg pi@ganger.webhop.org:/var/www/science_honors/

echo "Done!"
