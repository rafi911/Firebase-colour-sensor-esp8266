#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// firebase 
#define FIREBASE_HOST "XXXXXXXXXX.firebaseio.com"
//This is  Firebase Hostname which can be found in the Firebase console.
#define FIREBASE_AUTH "******************************************"


//  network details
const char* ssid = "your router name";
const char* password = "your router's password";

// Web Server on port 80
WiFiServer server(80);

void initWifi() {
   Serial.print("Connecting to ");
   Serial.print(ssid);
   if (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);
   }

   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
  Serial.print("\nWiFi connected, IP address: ");
  Serial.println(WiFi.localIP());
}

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 D4
#define S1 D5
#define S2 D6
#define S3 D7
#define sensorOut D1

int frequencyR = 0;
int frequencyG = 0;
int frequencyB = 0;
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
   initWifi();
  
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  // farebase is started
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 
  Serial.println("Web server running. Waiting for the ESP IP...");
  delay(1000);
  
  // Printing the ESP IP address
  Serial.println(WiFi.localIP());
  
}
void loop() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequencyR = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  //frequencyR = map(frequencyR, 25,72,255,0);
  Serial.print(frequencyR);//printing RED color frequency
  
  Firebase.set("/RGB/R", frequencyR);
  
  Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequencyG = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  //frequencyG = map(frequencyG, 30,90,255,0);
  Serial.print(frequencyG);//printing RED color frequency
  
  Firebase.set("/RGB/G",frequencyG);
  
  Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequencyB = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  //frequencyB = map(frequencyB, 25,70,255,0);
  Serial.print(frequencyB);//printing RED color frequency

   // set the value on that path
   Firebase.set("/RGB/B", frequencyB);
  
  Serial.println("  ");
  delay(100);
}
