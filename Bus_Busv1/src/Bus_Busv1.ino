/*
 * Project L14_04_LoRaGPS_Capstone_BusDirector
 * Description: Starter Code for utilizing LoRa
 * Author: Brian Rashap and Christian Chavez_modified by Vernon Cox
 * Date: 24-MAR-2023_12APR23
 */


SYSTEM_MODE(SEMI_AUTOMATIC);

#include <Adafruit_GPS.h>
#include <IoTClassroom_CNM.h>
 
Adafruit_GPS GPS(&Wire);

IoTTimer myTimer;

// Define User and Credentials
String password = "AA4104132968BA2224299079021594AB"; // AES128 password
String busName = "53";
const int RADIOADDRESS = 0xC2; // Get address from Instructor, it will be a value between 0xC1 - 0xCF
const int TIMEZONE = -6;

// Define Constants
const int RADIONETWORK = 4;    // range of 0-16
const int SENDADDRESS =0 ;   // address of radio to be sent to

// Declare Variables
float lat,lon,alt;
int sat;
const int busNumbr=53;


void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 5000);

  Serial1.begin(115200);
  reyaxSetup(password);
  delay(10000);

  //Initialize GPS
  GPS.begin(0x10);  // The I2C address to use is 0x10
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); 
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
  GPS.println(PMTK_Q_RELEASE);

//sendData(busName, lat, lon, sat);
  delay(2000);
}

void loop() {
  // Get data from GSP unit (best if you do this continuously)
  GPS.read();


  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) {
      return;
    }   
  }
  // listen for incoming lora messages and then send GPS back
  // if (Serial1.available())  { // full incoming buffer: +RCV=203,50,35.08,9,-36,41 
  //   String parse0 = Serial1.readStringUntil('=');  //+RCV
  //   String parse1 = Serial1.readStringUntil(',');  // address received from
  //   String parse2 = Serial1.readStringUntil(',');  // buffer length
  //   String parse3 = Serial1.readStringUntil(',');  // fuseSound
  //   String parse4 = Serial1.readStringUntil(',');  // fuseDust
  //   String parse5 = Serial1.readStringUntil(',');  // rssi
  //   String parse6 = Serial1.readStringUntil('\n'); // snr
  //   String parse7 = Serial1.readString();          // extra

  //   Serial.printf("parse0: %s\nparse1: %s\nparse2: %s\nparse3: %s\nparse4: %s\nparse5: %s\nparse6: %s\nparse7: %s\n", parse0.c_str(), parse1.c_str(), parse2.c_str(), parse3.c_str(), parse4.c_str(), parse5.c_str(), parse6.c_str(), parse7.c_str());
  //   delay(100);
  //    myTimer.startTimer(5000);
  //     digitalWrite(D7,HIGH);

    getGPS(&lat,&lon,&alt,&sat);

    if(lat != 0) {
      sendData(busName, lat, lon, sat);
    }
    else {
      sendData(busName, 33.400322, -104.534897, 0);
    }


  //}
 
  if (myTimer.isTimerReady()){
         digitalWrite(D7,LOW);
  }
//sendData(busName, lat, lon, sat);
  delay(17000);
}


void getGPS(float *latitude, float *longitude, float *altitude, int *satellites) {
  int theHour;

  theHour = GPS.hour + TIMEZONE;
  if (theHour < 0) {
    theHour = theHour + 24;
  }

  Serial.printf("Time: %02i:%02i:%02i:%03i\n", theHour, GPS.minute, GPS.seconds, GPS.milliseconds);
  Serial.printf("Dates: %02i-%02i-%02i\n", GPS.month, GPS.day, GPS.year);
  Serial.printf("Fix: %i, Quality: %i", (int)GPS.fix, (int)GPS.fixquality);
  if (GPS.fix) {
    *latitude = GPS.latitudeDegrees;
    *longitude = GPS.longitudeDegrees;
    *altitude = GPS.altitude;
    *satellites = (int)GPS.satellites;
  }
}

void sendData(String name, float latitude, float longitude, int satelittes) {
  char buffer[60];

  Serial.printf("Sending GPS Data to bus station\n");
  sprintf(buffer, "AT+SEND=%i,60,%f,%f,%i,%s\r\n", SENDADDRESS, latitude, longitude, satelittes, name.c_str());
  Serial1.printf("%s",buffer);
  Serial.printf("%s",buffer);
  //Serial1.println(buffer); 
  delay(1000);
  if (Serial1.available() > 0)
  {
    Serial.printf("Awaiting Reply from send\n");
    String reply = Serial1.readStringUntil('\n');
    Serial.printf("Send reply: %s\n", reply.c_str());
  }
}

void reyaxSetup(String password) {
  // following four paramaters have most significant effect on range
  // recommended within 3 km: 10,7,1,7
  // recommended more than 3 km: 12,4,1,7
  const int SPREADINGFACTOR = 10;
  const int BANDWIDTH = 7;
  const int CODINGRATE = 1;
  const int PREAMBLE = 7;
  String reply; // string to store replies from module

  Serial1.printf("AT+ADDRESS=%i\r\n", RADIOADDRESS); // set the radio address
  delay(200);
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply from address\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("Reply address: %s\n", reply.c_str());
  }

  Serial1.printf("AT+NETWORKID=%i\r\n", RADIONETWORK); // set the radio network
  delay(200);
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply from networkid\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("Reply network: %s\n", reply.c_str());
  }

  Serial1.printf("AT+CPIN=%s\r\n", password.c_str());
  delay(200);
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply from password\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("Reply: %s\n", reply.c_str());
  }

  Serial1.printf("AT+PARAMETER=%i,%i,%i,%i\r\n", SPREADINGFACTOR, BANDWIDTH, CODINGRATE, PREAMBLE);
  delay(200);
  if (Serial1.available() > 0) {
    reply = Serial1.readStringUntil('\n');
    Serial.printf("reply: %s\n", reply.c_str());
  }

  Serial1.printf("AT+ADDRESS?\r\n");
  delay(200);
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("Radio Address: %s\n", reply.c_str());
  }

  Serial1.printf("AT+NETWORKID?\r\n");
  delay(200);
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("Radio Network: %s\n", reply.c_str());
  }

  Serial1.printf("AT+PARAMETER?\r\n");
  delay(200);
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("RadioParameters: %s\n", reply.c_str());
  }

  Serial1.printf("AT+CPIN?\r\n");
  delay(200);
  if (Serial1.available() > 0) {
    Serial.printf("Awaiting Reply\n");
    reply = Serial1.readStringUntil('\n');
    Serial.printf("Radio Password: %s\n", reply.c_str());
  }
}