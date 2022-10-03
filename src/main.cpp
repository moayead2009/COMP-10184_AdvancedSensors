//"I Mouaiad Hejazi,001220081 certify that this material is my original work. No other person's work has been used without due acknowledgement. I have not made my work available to anyone else."

// ******************************************************************
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program
// COMP-10184
// Mohawk College

// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>

// Pin that the  DS18B20 is connected to
const int oneWireBus = D3;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);

// Temperature reading from DS18B20
DeviceAddress tempSensor;

/**
 * The setup() function is used to configure the USB serial monitor and start the DS18B20 sensor
 */
void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // Start the DS18B20 sensor
  DS18B20.begin();

  // check if the sensor is not connected then print an error message
  if (!DS18B20.getAddress(tempSensor, 0))
  {
    Serial.println("");
    Serial.println("Temperature Application");
    Serial.println("No DS18B20 temperature sensors are installed");
  }
  else
  {
    // retrieve the sensor address
    DS18B20.getAddress(tempSensor, 0);

    Serial.println("");
    Serial.println("Temperature Application");

    // print the address

    /* Declaring a variable called address and initializing it to an empty string. */
    String address = "";
    /* This is a for loop that is used to print the address of the sensor. */
    for (uint8_t i = 0; i < 8; i++)
    {
      // print the address with word " found" at the end
      address += String(tempSensor[i], HEX);
    }

    Serial.println("Found DS18B20 sensor with address: " + address);
  }
}

/**
 * If the DS18B20 sensor is found, then ask it for the current temperature, and print it to the serial
 * monitor
 */
void loop()
{
  /* This is a conditional statement that checks if the sensor is connected. */
  if (DS18B20.getAddress(tempSensor, 0))
  {
    /* Declaring a variable called fTemp and initializing it to a float. */
    float fTemp;

    // ask DS18B20 for the current temperature
    DS18B20.requestTemperatures();

    // fetch the temperature.  We only have 1 sensor, so the index is 0.
    fTemp = DS18B20.getTempCByIndex(0);

    /* This is a conditional statement that checks the temperature and prints the status of the
    temperature. */
    String status = fTemp < 10   ? "Cold"
                    : fTemp < 15 ? "Cool"
                    : fTemp < 25 ? "Perfect"
                    : fTemp < 30 ? "Warm"
                    : fTemp < 35 ? "Hot"
                                 : "Very Too Hot";

    Serial.println("Current temperature is: " + String(fTemp) + "° C, or " + status);

    // wait 5s (5000ms) before doing this again
    delay(5000);
  }
}