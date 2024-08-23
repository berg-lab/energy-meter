
const int VOLTSENSE = A1;      // Pin for voltage sensing
const int CURRENTSENSE = A0;   // Pin for current sensing
const int numSamples = 100;     // Number of samples to store

float voltageSamples[numSamples];   // Array to store voltage samples
float currentSamples[numSamples];   // Array to store current samples

const float MAINSVPP = 340;     // Peak-to-peak voltage for 120Vrms(checked online to be 339-350 vpp aprrox , need to research more)(170*2)
const float CURRENTNORM = 15.5; // Normalizing constant for current 
const float VREF = 460;         // Reference voltage for current sensing(value had to be calibrated , initial value was 498, connect killa-watt ,without load ad calibrate current to approx 0)

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud
  Serial.println("Time,RMS Voltage (V),RMS Current (A),Power (W), Raw Voltage ADC,Raw Current ADC"); // Add labels for your data columns
}

void loop() {
  // Read 20 samples and store them in arrays
  for (int i = 0; i < numSamples; i++) {
    voltageSamples[i] = analogRead(VOLTSENSE);    // Read the voltage value from A1
    currentSamples[i] = analogRead(CURRENTSENSE); // Read the current value from A0
    
  }
  //  for (int i = 0; i < numSamples; i++) {
  //   Serial.print((int)voltageSamples[i]);
  //   if (i < numSamples - 1) Serial.print(",");
  // }
  // Serial.println();
  //  for (int i = 0; i < numSamples; i++) {
  //   Serial.print((int)currentSamples[i]);
  //   if (i < numSamples - 1) Serial.print(",");
  // }

  // Calculate the min and max voltage
  int min_v = 1023;
  int max_v = 0;
  for (int i = 0; i < numSamples; i++) {
    if (voltageSamples[i] < min_v) min_v = voltageSamples[i];
    if (voltageSamples[i] > max_v) max_v = voltageSamples[i];
  }

  // Calculate average and peak-to-peak voltage
  int avgv = (min_v + max_v) / 2;
  int vpp = max_v - min_v;

  // Normalize voltage readings
  for (int i = 0; i < numSamples; i++) {
    voltageSamples[i] -= avgv;  // Remove DC bias
    voltageSamples[i] = (voltageSamples[i] * MAINSVPP) / vpp;  // Scale to actual voltage range
    // voltageSamples[i] = abs(voltageSamples[i]);  // Convert to absolute value

  }

  // Normalize current readings
  for (int i = 0; i < numSamples; i++) {
    currentSamples[i] -= VREF;  // Remove DC bias
    currentSamples[i] /= CURRENTNORM;  // Convert to amperes
    // currentSamples[i] = abs(currentSamples[i]);  // Convert to absolute value
  }

   // Calculate RMS voltage
  float sumSqVoltage = 0.0;
  float sumSqCurrent = 0.0;
  for (int i = 0; i < numSamples; i++) {
    sumSqVoltage += sq(voltageSamples[i]);  // sq() computes the square of a number
    sumSqCurrent += sq(currentSamples[i]);
  }
  float rmsVoltage = sqrt(sumSqVoltage / numSamples);
  float rmsCurrent = sqrt(sumSqCurrent / numSamples);
//send time placeholder

 Serial.print("TIME_PLACEHOLDER,"); 
  // Send RMS voltage and current over serial

  // Serial.print("RMS Voltage (V): ");

  Serial.print(rmsVoltage);


  // Serial.print("RMS Current (A): ");
  Serial.print(",");
  Serial.print(rmsCurrent);


  // Serial.print("Power (W): ");
  Serial.print(",");
  Serial.print(rmsVoltage*rmsCurrent);
  

Serial.print(",");
   // Print the normalized values to the serial monitor
  
  for (int i = 0; i < numSamples; i++) {
    Serial.print(voltageSamples[i]);
    if (i < numSamples - 1) Serial.print(",");
  }
  Serial.print(",");
  
  for (int i = 0; i < numSamples; i++) {
    Serial.print(currentSamples[i]);
    if (i < numSamples - 1) Serial.print(",");
  }
Serial.println("");
  
  
  
  // Send data to serial
  // Serial.print(millis());
  // Serial.print(",");

  // for (int i = 0; i < numSamples; i++) {
  //   Serial.print(voltageSamples[i]);
  //   if (i < numSamples - 1) Serial.print(",");
  // }
  // Serial.print(",");

  // for (int i = 0; i < numSamples; i++) {
  //   Serial.print(currentSamples[i]);
  //   if (i < numSamples - 1) Serial.print(",");
  // }
  // Serial.print(",");

  // for (int i = 0; i < numSamples; i++) {
  //   Serial.print(analogRead(VOLTSENSE));    // Raw ADC voltage values
  //   if (i < numSamples - 1) Serial.print(",");
  // }
  // Serial.print(",");

  // for (int i = 0; i < numSamples; i++) {
  //   Serial.print(analogRead(CURRENTSENSE)); // Raw ADC current values
  //   if (i < numSamples - 1) Serial.print(",");
  // }
  // Serial.print(",");

  // Serial.print(rmsVoltage);
  // Serial.print(",");
  // Serial.print(rmsCurrent);
  // Serial.print(",");
  // Serial.println(rmsVoltage * rmsCurrent);

  // delay(1000);  // Adjust the delay as needed
}

