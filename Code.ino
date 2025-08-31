// Include required libraries
#if defined(ESP32)
#include <WiFi.h>
// #elif defined(ESP8266)
// #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <DHT.h>  // Include the DHT sensor library

// Define DHT sensor parameters
#define DHTPIN 4
#define DHTTYPE DHT11

// Define MQ135 sensor pin
#define MQ135_PIN 34

// --- IMPORTANT ---
// Replace these with your actual WiFi and Firebase credentials
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Define Firebase API Key, Project ID, and user credentials
#define API_KEY "YOUR_FIREBASE_API_KEY"
#define FIREBASE_PROJECT_ID "YOUR_FIREBASE_PROJECT_ID"
#define USER_EMAIL "YOUR_FIREBASE_USER_EMAIL"
#define USER_PASSWORD "YOUR_FIREBASE_USER_PASSWORD"
// -----------------

// Define Firebase Data object, Firebase authentication, and configuration
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Initialize the DHT sensor
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Print Firebase client version
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  // Assign the API key
  config.api_key = API_KEY;

  // Assign the user sign-in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the callback function for the long-running token generation task
  config.token_status_callback = tokenStatusCallback;  // see addons/TokenHelper.h

  // Begin Firebase with configuration and authentication
  Firebase.begin(&config, &auth);

  // Reconnect to Wi-Fi if necessary
  Firebase.reconnectWiFi(true);
}

void loop() {
  // Define the path to the Firestore document
  String documentPath = "EspData/SensorData";

  // Create a FirebaseJson object for storing data
  FirebaseJson content;

  // Read temperature and humidity from the DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read air quality value from the MQ135 sensor
  int airQuality = analogRead(MQ135_PIN);

  // Print sensor values for debugging
  Serial.println("Temperature: " + String(temperature) + " *C");
  Serial.println("Humidity: " + String(humidity) + " %");
  Serial.println("Air Quality: " + String(airQuality));

  // Check if the values are valid (not NaN for DHT)
  if (!isnan(temperature) && !isnan(humidity)) {
    // Set the fields in the FirebaseJson object according to Firestore REST API structure
    content.set("fields/Temperature/doubleValue", String(temperature, 2));
    content.set("fields/Humidity/doubleValue", String(humidity, 2));
    content.set("fields/AirQuality/integerValue", String(airQuality));

    Serial.print("Updating document in Firestore... ");

    // Use the patchDocument method to update the Firestore document
    // The mask ensures only these fields are updated
    if (Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw(), "Temperature,Humidity,AirQuality")) {
      Serial.printf("OK\n%s\n\n", fbdo.payload().c_str());
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
      Serial.println("--------------------");
    }
  } else {
    Serial.println("Failed to read from DHT sensor.");
  }

  // Delay before the next reading
  delay(10000);
}
