#include <SPI.h>

// Constants
const int N_samples = 1000;
const int WaveLength = 149;  // (74*2) + 1
const int VoltSense = A4;
const int AmpSense = A3;
const float VREF = 471.73;
const float VREF2 = 475.02;
const float CURRENTNORM = 0.57;
const float VOLTNORM = 0.476;

float totalVolt = 0.0;
float totalAmp = 0.0;
int tcnt = 0;
float avgwattdata[1800];
int avgwattdataidx = 0;

// Variables to store data
float voltagedata[N_samples];
float ampdata[N_samples];
float wattdata[WaveLength];

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 1800; i++) {
    avgwattdata[i] = 0;
  }
}

void loop() {
  // Collect data samples
  for (int i = 0; i < N_samples; i++) {
    voltagedata[i] = analogRead(VoltSense);
    ampdata[i] = analogRead(AmpSense);
  }

  // Process the data
  processData();

  // Simulate some delay (adjust according to your sampling rate)
  delay(1000);
}

void processData() {
  float vRMS = 0.0;
  float aRMS = 0.0;
  float vave = 0.0;
  float aave = 0.0;

  // Offset correction and normalization
  for (int i = 0; i < N_samples; i++) {
    voltagedata[i] = (voltagedata[i] - VREF2) * VOLTNORM;
    ampdata[i] = (ampdata[i] - VREF) * CURRENTNORM;

    if (i < WaveLength) {
      vave += abs(voltagedata[i]);
      vRMS += voltagedata[i] * voltagedata[i];
      aave += abs(ampdata[i]);
      aRMS += ampdata[i] * ampdata[i];
      wattdata[i] = ampdata[i] * voltagedata[i];
    }
  }

  // RMS Calculations
  vRMS = sqrt(vRMS / WaveLength);
  aRMS = sqrt(aRMS / WaveLength);
  float wattAve = 0.0;
  for (int i = 0; i < WaveLength; i++) {
    wattAve += wattdata[i];
  }
  wattAve /= WaveLength;

  avgwattdata[avgwattdataidx] = wattAve;
  avgwattdataidx++;
  if (avgwattdataidx >= 1800) {
    avgwattdataidx = 0;  // Reset index after filling the buffer
  }

  // Print results
  Serial.print("Volt RMS: ");
  Serial.print(vRMS);
  Serial.print("V, Amp RMS: ");
  Serial.print(aRMS);
  Serial.print("A, Watt: ");
  Serial.print(wattAve);
  Serial.println("W");

  // Optionally log data to SD card or EEPROM
}

// Optionally implement a calibration function if needed
void calibrateADC() {
  totalVolt = 0.0;
  totalAmp = 0.0;

  for (int i = 0; i < WaveLength; i++) {
    totalVolt += voltagedata[i];
    totalAmp += ampdata[i];
  }

  tcnt += WaveLength;
  Serial.print("VREF: ");
  Serial.println(totalVolt / tcnt);
  Serial.print("VREF2: ");
  Serial.println(totalAmp / tcnt);
}
