// http://code.google.com/p/ardroneme/
// From the file NavData2.zip 

/* Updated by MAPGPS based on Richi's code:
 * http://ulrichard.is-a-geek.net/?p=23
 */

//Update by boulderjoe 12/30/11 to work with arduino 1.0 

#ifndef INTERSEMA_BARO_H
#define INTERSEMA_BARO_H

#include <Wire.h>
#include <util/delay.h>
#include "Arduino.h"

namespace Intersema
{
  
class BaroPressure
{
public:
	virtual void init() = 0;   
   
	int32_t getPressure(void)
	{
		return AcquireAveragedSampleCm(NUM_SAMP_FOR_AVG);
	}   
	
protected:
	virtual int32_t AcquireAveragedSampleCm(const uint8_t nSamples) = 0;
	virtual uint32_t ConvertPressureTemperature(uint32_t pressure, uint32_t temperature) = 0;
	
	int32_t PascalToCentimeter(const int32_t pressurePa)
	{
	return pressurePa;
	}
	
	static const uint8_t NUM_SAMP_FOR_AVG = 4;

	unsigned int coefficients_[6];
};

class BaroPressure_MS5607B : public BaroPressure
{
public:
	/// @param CSB  i2c address select
	BaroPressure_MS5607B(bool CSB = false) : i2cAddr_((CSB ? 0xEC : 0xEE) >> 1) { }
	
	void init()
	{	
		ResetSensor();
		ReadCoefficients();
	}
	
private:

	const uint8_t i2cAddr_;
	static const uint8_t cmdReset_   = 0x1E;
	static const uint8_t cmdAdcRead_ = 0x00;
	static const uint8_t cmdAdcConv_ = 0x40;
	static const uint8_t cmdAdcD1_   = 0x00;
	static const uint8_t cmdAdcD2_   = 0x10;
	static const uint8_t cmdAdc256_  = 0x00;
	static const uint8_t cmdAdc512_  = 0x02;
	static const uint8_t cmdAdc1024_ = 0x04;
	static const uint8_t cmdAdc2048_ = 0x06;
	static const uint8_t cmdAdc4096_ = 0x08;
	static const uint8_t cmdPromRd_  = 0xA0;

	void ResetSensor()
	{
	Wire.begin();
		Wire.beginTransmission(i2cAddr_);
		Wire.write(cmdReset_);   
		Wire.endTransmission(); 
		delay(3);
	}

	void ReadCoefficients(void)
	{
		for(uint8_t i=0; i<6; ++i)
		    coefficients_[i] = ReadCoefficient(i + 1);  
		    
	}

	uint16_t ReadCoefficient(const uint8_t coefNum)
	{
		uint16_t rC=0;
	
		Wire.beginTransmission(i2cAddr_);
		Wire.write(cmdPromRd_ + coefNum * 2); // send PROM READ command
		Wire.endTransmission(); 
	
		Wire.requestFrom(i2cAddr_, static_cast<uint8_t>(2));

		if(Wire.available() >= 2)
		{
		    uint16_t ret = Wire.read();   // read MSB and acknowledge
		    uint16_t rC  = 256 * ret;
		    ret = Wire.read();        // read LSB and not acknowledge
		    rC  = rC + ret;
		    return rC;
		}
	
		return 0;
	}

	virtual int32_t AcquireAveragedSampleCm(const uint8_t nSamples)
	{
		int64_t pressAccum = 0;

		for(size_t n = nSamples; n; n--) 
		{
		    const uint32_t temperature = ReadAdc(cmdAdcD2_ | cmdAdc4096_); // digital temperature value : typical 8077636  
		    const uint32_t pressure    = ReadAdc(cmdAdcD1_ | cmdAdc4096_); // digital pressure value : typical 6465444        
		    const uint32_t pressConv   = ConvertPressureTemperature(pressure, temperature);                 
		    pressAccum += pressConv;
		}

		const int32_t pressAvg = pressAccum / nSamples;        
		const int32_t AltCm = PascalToCentimeter(pressAvg);
	
		return AltCm;	
	}
	
	int32_t ReadAdc(const uint8_t cmd)
	{	         
		Wire.beginTransmission(i2cAddr_);
		Wire.write(cmdAdcConv_ | cmd); // send conversion command
		Wire.endTransmission(); 

		// wait necessary conversion time
		switch(cmd & 0x0f) 
		{
		case cmdAdc256_: 
		    delay(1);
		    break;
		case cmdAdc512_: 
		    delay(3);
		    break;
		case cmdAdc1024_: 
		    delay(4);
		    break;
		case cmdAdc2048_: 
		    delay(6);
		    break;
		case cmdAdc4096_: 
		    delay(10); 
		    break;
		}

		Wire.beginTransmission(i2cAddr_);
		Wire.write(cmdAdcRead_);
		Wire.endTransmission();
	
		Wire.requestFrom(i2cAddr_, static_cast<uint8_t>(3));

		if(Wire.available() >= 3)
		{
		    uint16_t ret  = Wire.read(); // read MSB and acknowledge
		    uint32_t temp = 65536 * ret;
		    ret  = Wire.read();      // read byte and acknowledge
		    temp = temp + 256 * ret;
		    ret  = Wire.read();  // read LSB and not acknowledge
		    temp = temp + ret;
		        
		    return temp;
		}
		return 0;
	}

	uint32_t ConvertPressureTemperature(uint32_t pressure, uint32_t temperature)
	{
		const int32_t dT    = temperature - coefficients_[4] * 256;                     // difference between actual and reference temperature
		const int32_t OFF   = coefficients_[1] * 4 + ((float)dT / 2048) * ((float)coefficients_[3] / 1024);
		const int32_t SENS  = coefficients_[0] * 2 + ((float)dT / 4096) * ((float)coefficients_[2] / 1024);
		const int32_t press =  ((float)pressure / 2048) * ((float)SENS / 1024) - OFF;

		return press; 
	}

};

} // namespace Intersema
#endif



