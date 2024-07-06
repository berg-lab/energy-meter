import serial
import csv
import time
import os
from datetime import datetime

# Configure the serial connection (adjust the COM port and baud rate as needed)
ser = serial.Serial('COM20', 115200)  # Change 'COM3' to the appropriate port for your Arduino

# Specify the directory where you want to save the CSV file
save_directory = r'C:\Users\arjun\OneDrive - Illinois Institute of Technology\RA\Energy_meter_gihub\energy-meter\data_calibration_test\calibration_it1'
os.makedirs(save_directory, exist_ok=True)  # Create the directory if it does not exist
file_path = os.path.join(save_directory, 'Iron_Box_data.csv')

# Open a CSV file to write data
with open(file_path, mode='w', newline='') as file:
    writer = csv.writer(file)
    while True:
        if ser.in_waiting > 0:
            # Read a line from the serial port
            line = ser.readline().decode('utf-8').strip()
            print(line)

            # Replace placeholder with actual time
            current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            line = line.replace("TIME_PLACEHOLDER", current_time)

            # Split the line into data fields
            data = line.split(',')

            # Write the data to the CSV file
            writer.writerow(data)

            # Optionally, you can add a delay to control the logging frequency
            time.sleep(0.5)
