/*
 * Communications.h
 * This file is part of Borp
 *
 * Copyright (C) 2014 - Houghton College Science Honors
 *
 * Borp is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Borp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Borp. If not, see <http://www.gnu.org/licenses/>.
 */

/* The purpose of this library is to provide almost seamless integration with
the Arduino libraries. Differences include Serial.begin() (takes path, not baud)
Serial.readByte(), Serial.readString, Serial.readArray() (= Serial.readBytes), 
Serial.wait(), Serial.clean().

From my current understanding, by writing to the file /dev/ttyS* (or whatever
device you so choose) it acts in a similar way to the serial buffer on the 
Arduino.

EASY WAY TO TEST:
	echo $STRING > /dev/ttyS0

		->with Arduino plugged in, where $String is "something"

Baud rate is set by: 
	stty -F /dev/ttyS* 115200

There is also the program called setserial, which does lets you configure just
about anything for the serial.
*/

class Communications {
	public:
		//Begins serial on path (/dev/ttyS*), returns error code as int
		int begin(std::string path);

		//writes a string to serial device, no println; just add "\n" to above
		void print(std::string);		

		//write the integer as 1 or 2 bytes		
		void write(int number);

		//writes an array to serial
		void write(int * array, int size);

		//This function assumes that serial on linux uses the same buffer
		int available();

		//This read the first character in the buffer and destroy it
		char read();

		//This returns a string; something the Arduino should but doesn't have
		std::string readString();

		//returns the byte as an int
		short int readByte();

		//reads the bytes into an array
		int readArray(int * array, int size);

		//checks the Serial device for stuff, period between iterations is in
		//milliseconds, delayTime is also in milliseconds (to fill buffer)
		int wait(int period, int delayTime);

		//removes everything from receiving buffer, returns # of bytes removed
		int clean();
	private:
		std::string serialPath;			//String to hold the USB location
} Serial;


