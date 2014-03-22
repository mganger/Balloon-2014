/*
 * Data.h
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

class Data { 

	public:
		int * returnData();
		int * returnData(int index);
		void saveData();
		void readSensorData();
		void readTemp(int pin);
		void readAlti(int pin);
		void readHumi(int pin);
		void readPres(int pin);
		void readCO2_(int pin);
		void readN2O_(int pin);
		void readCO__(int pin);
		void readIR__(int pin);
		void readO3__(int pin);

					//Public methods to set private variables
		void setAltiPin(int pin);
		void setHumiPin(int pin);
		void setPresPin(int pin);
		void setTempPin(int pin);
		void setCO2_Pin(int pin);
		void setN2O_Pin(int pin);
		void setCO__Pin(int pin);
		void setIR__Pin(int pin);
		void setUV__Pin(int pin);
		void setO3__Pin(int pin);

	private:
		int temp, pres, alti, humi, CO2_, CO__, N2O_, UV__, O3__;
		int tempPin, presPin, altiPin, humiPin, CO2_Pin, CO__Pin, N2O_Pin, UV__Pin, O3__Pin;
}
