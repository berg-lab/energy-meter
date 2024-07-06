#include "methods.h"
const int currentPin = A0; // Pin for voltage
const int voltagePin = A1; // Pin for current

void setup() {
  Serial.begin(9600); // Start the serial communication
  
}
int voltage_arr[19];
int i=0;
void loop() {
  int voltageValue = analogRead(voltagePin); // Read the voltage
  int currentValue = analogRead(currentPin); // Read the current
  while(i<=19){
    voltage_arr[i] = voltageValue;
    Serial.println(voltage_arr[i]);
  }
  i++;


  // Convert the analog readings to meaningful values
  float voltage = voltageValue * (5.0 / 1023.0); // Assuming a 5V reference voltage
  float current = currentValue * (5.0 / 1023.0); // Convert current reading to voltage

  // Print the values to the Serial Monitor
  Serial.print("Voltage:");
  Serial.print(voltageValue);
  Serial.print(",");
  Serial.print("Current:");
  Serial.println(currentValue);
  
  

  // delay(1000); // Wait for 1 second before next reading
}
