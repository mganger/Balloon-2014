#!/bin/bash
#This script takes stuff off the sd card, saves it to a file with the date and
#time as the name, and then reflashes the sd card to have an fat32 file system

mkdir -p SD_archive
cd SD_archive
time=$(date +"%T,%m-%d-%y")
mkdir $time
cd $time

cp -r $2/ ./
umount $1
mkfs.fat
