/**
* Implementation of temperature sensor MCP9808.
* With cpp-class
*
* @author urban
*/

#include <stdio.h>
#include <float.h>
#include <signal.h>
#include "pigpio.h"

#define I2C_BUS 1
#define DEV_ADDR 0x18

int main()
{
	// Variables
	char i2c_handle;
	char error; // Response from the I2C command
	
	char upperByte = 0;
	char lowerByte = 0;


	printf("\nHelloTemperatureDemo\n");
	if(gpioInitialise() < 0)
	{
		printf("Initialise failed\n");
		return -1;
	}
	
	i2c_handle = i2cOpen(I2C_BUS, DEV_ADDR, 0);
	error = i2cWriteByte(i2c_handle, 0);
	
	if(i2c_handle >= 0 &&  error >= 0)
	{
		printf("Found temperature sensor.\n");
	}
	else
	{
		printf("No connection to sensor.\n");
	}
	
	return 0;
}



// Upper Byte of the Temperatureregister
byte upperByte = 0;
// Lower Byte of the Temperatureregister
byte lowerByte = 0;
// Temporal Variable
int temp = 0;
// Calculated Temperature
float temperature;
// Location of the configuration register  
byte pointerByteConfig = 0x01;
// Data for the configuration register
byte upperByteData_c = 0B00000000;
byte lowerByteData_c = 0B00001000;
// Location of the upper limit register
byte pointerByteUL = 0x02;
// Data for the upper limit register
byte upperByteData_tl = 0B00000001;
byte lowerByteData_tl = 0B11100000;
// Location of the temperature register
byte pointerByteReadTemp = 0x05;
// Data for the upper limit register


    Wire.beginTransmission(address);
    // Device address is called. Result is an errorcode
    // 0 = Device found, 4 = error, else no device found)
    error = Wire.endTransmission();

    // Device was found
    if (error == 0)
    {
      Serial.println("I2C device found");
    }
    // Error in communication
    else if (error==4)
    {
      Serial.println("Unknow error");
    }
    // No device found  
    else
    {
      Serial.println("No I2C device found\n");
    }
    
    // Configuration of the temperature sesnor
    Wire.beginTransmission(address); // Start communication
    Wire.write(pointerByteConfig); // Write to the location
    Wire.write(upperByteData_c); // Write the value => upperByte
    Wire.write(lowerByteData_c); // Write the value => lowerByte
    Wire.endTransmission(); // End communication

    // Read out the configuration Register
    Wire.beginTransmission(address); // Start communication
    Wire.write(pointerByteConfig); // Write to the location
    Wire.endTransmission(false); // Trigger communication
    Wire.beginTransmission(address); // Start communication
    Wire.requestFrom(address, 2); // Read two bytes from the address
    if (Wire.available()) { // Store the values
        upperByte = Wire.read();
        lowerByte = Wire.read();
    }
    Wire.endTransmission(); // End communication

    Serial.print("Configuration Register = ");
    Serial.print(upperByte,BIN);
    Serial.println(lowerByte,BIN);

    // Configuration of the temperature limit
    Wire.beginTransmission(address); // Start communication
    Wire.write(pointerByteUL); // Write to the location
    Wire.write(upperByteData_tl); // Write the value => upperByte
    Wire.write(lowerByteData_tl); // Write the value => lowerByte
    Wire.endTransmission(); // End communication

    // Read out the configuration Register
    Wire.beginTransmission(address); // Start communication
    Wire.write(pointerByteUL); // Write to the location
    Wire.endTransmission(false); // Trigger communication
    Wire.beginTransmission(address); // Start communication
    Wire.requestFrom(address, 2); // Read two bytes from the address
    if (Wire.available()) { // Store the values
        upperByte = Wire.read();
        lowerByte = Wire.read();
    }
    Wire.endTransmission(); // End communication

    Serial.print("Upper Limit Register = ");
    Serial.print(upperByte,BIN);
    Serial.println(lowerByte,BIN);

}



/********************************************************************************************/
 /* Main Loop
/********************************************************************************************/
void loop() {


    // Read the temperature
    Wire.beginTransmission(address); // Start communication
    Wire.write(pointerByteReadTemp); // Read from this location
    Wire.endTransmission(false); // Trigger communication
    Wire.beginTransmission(address); // Start communication
    Wire.requestFrom(address, 2); // Read two Bytes from the address
    if (Wire.available()) { // Store the values
        upperByte = Wire.read();
        lowerByte = Wire.read();
    }
    Wire.endTransmission(); // End communication
  
    //Serial.print("Temperature Register = ");
    //Serial.print(upperByte,BIN);
    //Serial.println(lowerByte,BIN);

    // Delete the upper three bist
    upperByte = upperByte & 0x1F;
    // If the temperature is negative
    if((upperByte & 0x10) == 0x10)
    {
      // Delet the sign bit
      upperByte = upperByte & 0x0F;
      // Calculate the temperature according to the datasheet
      temp = upperByte * 16;
      temperature = (float(lowerByte) / 16) + temp;
      temperature = 256 - temperature;
      // Plot the temperature to the serial monitor.
      Serial.print("Current temperature: -");
      Serial.print(temperature,4);
      Serial.println("°C");
    }
    else
    {
      // Calculate the temperature according to the datasheet
      temp = upperByte * 16;
      temperature = (float(lowerByte) / 16) + temp;
      // Plot the temperature to the serial monitor.
      Serial.print("Current temperature: ");
      Serial.print(temperature,4);
      Serial.println("°C");
    }

    delay(200);
 
}
