#!/bin/bash

./a.out

mkdir ../graphs
gnuplot -persist -e "set term svg;set output '../graphs/altitude.svg';set title 'altitude';set datafile separator ',';plot '../data.csv' using 2:3 with lines"
gnuplot -persist -e "set term svg;set output '../graphs/pressure.svg';set title 'pressure';set datafile separator ',';plot '../data.csv' using 2:4 with lines"
gnuplot -persist -e "set term svg;set output '../graphs/humidity.svg';set title 'humidity';set datafile separator ',';plot '../data.csv' using 2:5 with lines"
gnuplot -persist -e "set term svg;set output '../graphs/CO2.svg';set title 'CO2';set datafile separator ',';plot '../data.csv' using 2:6 with lines"
gnuplot -persist -e "set term svg;set output '../graphs/UV.svg';set title 'Ultra Violet';set datafile separator ',';plot '../data.csv' using 2:7 with lines"
gnuplot -persist -e "set term svg;set output '../graphs/O3.svg';set title 'Ozone';set datafile separator ',';plot '../data.csv' using 2:8 with lines"
gnuplot -persist -e "set term svg;set output '../graphs/IR.svg';set title 'InfraRed';set datafile separator ',';plot '../data.csv' using 2:9 title 'IR up' with lines, '../data.csv' using 2:10 title 'IR down' with lines, '../data.csv' using 2:11 title 'Visible Up' with lines,'../data.csv' using 2:12 title 'Visible Down' with lines"

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
