ESP32 Sensor Data Logger with Firebase
![ESP32 Firebase Project Banner]

This project uses an ESP32 microcontroller to read environmental data from DHT11 (temperature and humidity) and MQ135 (air quality) sensors. The collected data is then transmitted over Wi-Fi and stored in a Google Firebase Firestore database, allowing for real-time monitoring and data logging.

Key Features:
Reads temperature and humidity from a DHT11 sensor.

Reads analog air quality values from an MQ135 sensor.

Connects to a Wi-Fi network.

Authenticates and sends data to a Google Firebase Firestore database.

Provides serial output for debugging and monitoring.

Hardware Required:
ESP32 Development Board

DHT11 Temperature and Humidity Sensor

MQ135 Air Quality Sensor

Breadboard and connecting wires

Wiring Diagram:
Connect the components as follows:

Sensor Pin

ESP32 Pin

DHT11 VCC

3.3V

DHT11 GND

GND

DHT11 Data

D4

MQ135 VCC

5V

MQ135 GND

GND

MQ135 A0

D34 (ADC1)

Getting Started
Follow these steps to get the project up and running.

1. Firebase Setup
Before you can use the code, you need to set up a Firebase project.

Create a Firebase Project: Go to the Firebase Console and create a new project.

Add a Web App: In your project dashboard, add a new Web App. This will provide you with the necessary configuration details.

Enable Firestore: Go to the "Firestore Database" section and create a new database. Start in test mode for easy setup (you can secure it later with security rules).

Enable Authentication: Go to the "Authentication" section, select the "Sign-in method" tab, and enable Email/Password authentication. Create a new user with an email and password.

Get Credentials: Find your Web API Key and Project ID in the Project Settings. You will need these for the code.

2. Software & Library Setup
You will need an IDE to upload the code to your ESP32.

Install IDE: Install the Arduino IDE or VS Code with the PlatformIO extension.

Install ESP32 Board Support: If using the Arduino IDE, make sure you have added the ESP32 board manager.

Install Libraries: Install the following libraries through the library manager:

Firebase ESP Client by Mobizt

DHT sensor library by Adafruit

3. Configure and Upload
Clone the Repository:

git clone [https://github.com/your-username/your-repo-name.git](https://github.com/your-username/your-repo-name.git)
cd your-repo-name

Add Your Credentials: Open the main.cpp file and update the following lines with your own credentials from the Firebase setup and your Wi-Fi details.

// --- IMPORTANT ---
// Replace these with your actual WiFi and Firebase credentials
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

#define API_KEY "YOUR_FIREBASE_API_KEY"
#define FIREBASE_PROJECT_ID "YOUR_FIREBASE_PROJECT_ID"
#define USER_EMAIL "YOUR_FIREBASE_USER_EMAIL"
#define USER_PASSWORD "YOUR_FIREBASE_USER_PASSWORD"
// -----------------

Upload the Code: Connect your ESP32 to your computer, select the correct board and COM port in your IDE, and upload the code.

4. Usage
Once the code is uploaded, open the Serial Monitor (set the baud rate to 115200). You will see the ESP32 connect to Wi-Fi and start sending sensor readings.

You can then log in to your Firebase Console and see the data appear in your Firestore database under the EspData/SensorData document.

Contributing
Contributions are welcome! If you have any improvements or suggestions, please feel free to fork the repository and submit a pull request.

License
This project is licensed under the MIT License. See the LICENSE file for more details.
