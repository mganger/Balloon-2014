/*
 * parser.cc
 * This file is part of Balloon 2014
 *
 * Copyright (C) 2014 - Michael Ganger
 *
 * Balloon 2014 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Balloon 2014 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Balloon 2014. If not, see <http://www.gnu.org/licenses/>.
 */

//This program is designed to parse the radio connection data. It has to:
//
//Calibrate the time data
//Grab the corrupt packet data
//Combine it with the GPS data

//Radio Antenna: 42.4558539722222 N 78.1910899999 W

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define SMOOTH 10000

using namespace std;

int main(){
	//check the number of lines
	ifstream gps("coordinates.csv");
	string line = " ";
	int gpsnumber;
	for(int i = 0; line != ""; i++){
		getline(gps,line,'\n');
		gpsnumber = i;
	}
	cout << gpsnumber << " lines in gps" << endl;
	gps.close();

	gps.open("coordinates.csv");
	for(int i = 0; i < gpsnumber; i++){
		//parse data
	}

	
	ifstream radio("maple_15_mile.csv");
	line = " ";
	int radionumber;
	for(int i = 0; line != ""; i++){
		getline(radio,line,'\n');
		radionumber = i;
	}
	cout << radionumber << " lines in radio" << endl;
	radio.close();

	radio.open("maple_15_mile.csv");

	//make an array of the radio data points
	long int time[radionumber];
	int trials[radionumber];
	double char64[radionumber];
	double ping[radionumber];
	double charping[radionumber];
	int disconnects[radionumber];
	double livecorrupt[radionumber];
	double totalcorrupt[radionumber];
	double livetimeout[radionumber];

	string timestr;
	string trialsstr;
	string char64str;
	string pingstr;
	string charpingstr;
	string disconnectsstr;
	string livecorruptstr;
	string totalcorruptstr;
	string livetimeoutstr;
	string lineend;

	//parse radio stats
	for(int i = 0; i < radionumber; i++){
		getline(radio,timestr,',');
		getline(radio,trialsstr,',');
		getline(radio,char64str,',');
		getline(radio,pingstr,',');
		getline(radio,charpingstr,',');
		getline(radio,disconnectsstr,',');
		getline(radio,livecorruptstr,',');
		getline(radio,totalcorruptstr,',');
		getline(radio,livetimeoutstr,',');
		getline(radio,lineend,'\n');

		time[i] = atoi(timestr.c_str());
		trials[i] = atoi(trialsstr.c_str());
		char64[i] = atof(char64str.c_str());
		ping[i] = atof(pingstr.c_str());
		charping[i] = atoi(charpingstr.c_str());
		disconnects[i] = atof(disconnectsstr.c_str());
		livecorrupt[i] = atof(livecorruptstr.c_str());
		totalcorrupt[i] = atof(totalcorruptstr.c_str());
		livetimeout[i] = atof(livetimeoutstr.c_str());
	}

	//make arrays of gps stats
	long double latitude[gpsnumber];
	double longitude[gpsnumber];
	double altitude[gpsnumber];
	long int timegps[gpsnumber];

	string latstr;
	string longstr;
	string altstr;
	string datestr;
	string hour;
	string min;
	string sec;

	//parse gps data
	for(int i = 0; i < gpsnumber; i++){
		getline(gps,latstr, ',');
		getline(gps,longstr,',');
		getline(gps,altstr,',');
		getline(gps,datestr,',');
		getline(gps,hour,':');
		getline(gps,min,':');
		getline(gps,sec,'\n');

		latitude[i] = atof(latstr.c_str());
		longitude[i] = atof(longstr.c_str());
		altitude[i] = atof(altstr.c_str());
		timegps[i] = atoi(hour.c_str())*3600000 + atoi(min.c_str())*60000 + atoi(sec.c_str())*1000;
	}
	//output gps data to a file
	ofstream gpsoutput("gpsoutput.csv", ios::trunc);
//	gpsoutput << "time (ms)" << '\t' << "latitude" << '\t' << "longitude" << '\t' << "x (m)   " << '\t' << "y (m)   " << '\t' << "z (m)   " << '\t' << "distance (m)" << '\t';
//	gpsoutput << "vx (m/s)" << '\t' << "vy (m/s)" << '\t' << "vz (m/s)" << '\t' << "v (m/s)" << '\t' << "mph" << endl;

	double xlast;
	double ylast;
	double zlast;
	double vx = 0;
	double vy = 0;
	double vz = 0;
	for(int i = 0; i < gpsnumber; i++){
		//y
		double y = (latitude[i] - 42.4558539722222) * 111082.1132284918;
		double x = (longitude[i] + 78.1910899999) * 82256.78;
		double z = altitude[i];
		if(i > 0){
			long int timesince = timegps[i] - timegps[i-1];
			if(timesince != 0){
				double vxnow = 1000*(x - xlast)/timesince;
				vx = (vxnow -vx) / (SMOOTH);
				double vynow = 1000*(y - ylast)/timesince;
				vy = (vynow -vz)/ (SMOOTH);
				double vznow = 1000*(z - zlast)/timesince;
				vz = (vznow - vz)/ (SMOOTH);
			}
		}
		gpsoutput << timegps[i] << ',' << (double)timegps[i]/3600000 -16 << ',' << latitude[i] << ',' << longitude[i] << ',' << x << ',' << y << ',' << z << ',' << sqrt(x*x + y*y + z*z) << ',';
		gpsoutput << vx << ',' << vy << ',' << sqrt(vx*vx +vy*vy + vz*vz) << ',' << sqrt(vx*vx +vy*vy + vz*vz)*2.23694 << endl;

		xlast = x;
		ylast = y;
		zlast = z;
	}
	gpsoutput.close();

	//output radio data to a file
	ofstream radiooutput("radiooutput.csv",ios::trunc);
	for(int i = 0; i < radionumber; i++){
		radiooutput << time[i] << ',' << (double)(time[i] -10561656 + 74658000)/3600000 -16 << ',' << disconnects[i] << ',';
		radiooutput << ping[i] << ',' << charping[i] << ',' << livecorrupt[i] << ',' << totalcorrupt[i] << ',' << livetimeout[i] << endl;
	}


}


















