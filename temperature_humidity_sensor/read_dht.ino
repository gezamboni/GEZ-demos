#include "DHT.h"

DHT dht(A0,DHT11);

void setup(){
	Serial.begin(9600);
	//Serial.println("teste de DHT11");
	dht.begin();
}

void loop(){
	// Reading temperature or humidity takes about 250 milliseconds
	// Sensor readings may also be up to 2 seconds old (slow sensor)
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	// check if valid
	// if NaN (not a Number) then something went wrong!
	if (isnan(t) || isnan(h))
	{
		Serial.println("Failed to read from DHT");
		return;
	}
	else
	{
	Serial.print("Humidity: ");
	Serial.print(h);
	Serial.print(" %\t");
	Serial.print("Temperature: ");
	Serial.print(t);
	Serial.println(" *C");
	//delay(2000);
	}
}

