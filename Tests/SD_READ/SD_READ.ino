#include "SD.h"


//simple sd-read file
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
while(!Serial){ // wait for serial port to connect. Needed for native USB
    delay(100);
  }
  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    return;
  }
  
  Serial.println("SD Card initialized successfully");
 readCSVfromSD("/wifi_config.csv");
}

void loop() {
  // put your main code here, to run repeatedly:

}
void readCSVfromSD(const char *filename){
  File file = SD.open(filename);
  
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  
  Serial.println("Reading CSV data from SD card:");
  
  // Read and print each line of the file
  while(file.available()){
    Serial.write(file.read());
  }
  
  file.close();
}