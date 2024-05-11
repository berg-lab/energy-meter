#include "FS.h"
#include "SD.h"
#include "SPI.h"

void setup(){
  Serial.begin(115200);
  while(!Serial){ // wait for serial port to connect. Needed for native USB
    delay(100);
  }
  
  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    return;
  }
  
  Serial.println("SD Card initialized successfully");

  // Write CSV data to SD card
  writeCSVtoSD("/wifi_config.csv");
 
}

void loop(){
  // You can add continuous data logging or any other functionality here
}

void writeCSVtoSD(const char *filename){
  File file = SD.open(filename, FILE_WRITE);
  
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  
  // Simulated data values
    String name = "krishna";
    String password="zxcv0987";
    String data = generateCSVData(name,password); // Generate CSV formatted data
    file.println(data);
  
  
  file.close();
  Serial.println("CSV data written to SD card");
}

String generateCSVData(String name,String password){

  // Format data as CSV string
  String data = String("SSID")     + " : " + String(name)     +"\n"+
                String("Password") + " : " + String(password);
  
  return data;
}

