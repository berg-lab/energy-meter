#include "SD.h"
#include <WiFi.h>
#include <BDL.h>
//This code needs more security on wifi credentials
BDL bdl; 

// Define a struct to hold WIFI credentials
struct WifiCredentials {
  String ssid;
  String password;
};

void setup() {
  Serial.begin(115200);
  bdl.begin();
  while (!Serial) { // wait for serial port to connect. Needed for native USB
    delay(100);
  }
  
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  
  Serial.println("SD Card initialized successfully");

  WifiCredentials cred = readWifiConfigFromCSV("/wifi_config.csv");
  
  Serial.println("name :" + cred.ssid);
  Serial.println("password :" + cred.password);
  Serial.println();
  // Serial.println();
  Serial.print("Connecting to ");
  Serial.println(cred.ssid.c_str());
  // Serial.println("SSID ASCII values:");
  // printASCIIValues(cred.ssid);
  WiFi.begin(cred.ssid.c_str(), cred.password.c_str());
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
}

WifiCredentials readWifiConfigFromCSV(const char *filename) {
  WifiCredentials cred;
  // Read and parse each line of the file
  File file = SD.open(filename);
  
  if (!file) {
    Serial.println("Failed to open file for reading");
    return cred; // Return empty credentials
  }
  
  while (file.available()) {
    String line = file.readStringUntil('\n'); // Read a line until newline character
    
    // Check if the line contains "SSID : "
    if (line.startsWith("SSID : ")) {
      cred.ssid = line.substring(7); // Extract SSID (remove "SSID : " prefix)
    }
    
    // Check if the line contains "Password : "
    if (line.startsWith("Password : ")) {
      cred.password = line.substring(11); // Extract password (remove "Password : " prefix)
    }
  }
  cred.ssid.trim();
  cred.password.trim();
  file.close();
  
  return cred; // Return the Wi-Fi credentials
}
void printASCIIValues(String str) {
  for (size_t i = 0; i < str.length(); i++) {
    Serial.print(str[i]);
    Serial.print(": ");
    Serial.println(int(str[i]));
  }
}