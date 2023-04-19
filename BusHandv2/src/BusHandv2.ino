/*
 * Project Capstone
 * Description: Starter Code for utilizing LoRa
 * Author: Brian Rashap and Christian Chavez _ Modified by Vernon Cox
 * Date: 24-MAR-2023 _ 12Apr23
 */


#include "Adafruit_SSD1306.h"
#include "Encoder.h"
#include <IoTClassroom_CNM.h>
#define OLED_RESET D4
 
//Adafruit_GPS GPS(&Wire);
Adafruit_SSD1306 display(OLED_RESET);
IoTTimer myTimer;

Encoder busEnc(D12,D11); //This is where the A and B pin are mapped.

// Define User and Credentials
String password = "AA4104132968BA2224299079021594AB"; // AES128 password
String myName = "DrVernonCox";
const int RADIOADDRESS = 0xC6; // Get address from Instructor, it will be a value between 0xC1 - 0xCF
const int TIMEZONE = -6;

// Define Constants
const int RADIONETWORK = 4;    // range of 0-16
const int SENDADDRESS = 0;   // address of radio to be sent to

// Declare Variables
float lat,lon,alt;
int sat;
static int busSe;
int busNmbr[]={53,53,53,53,53,53};
const int busBuzz=D5;//vibr buzzer
int busFind;
int busName;
int busHold;
int mappedBus;

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
SYSTEM_MODE(SEMI_AUTOMATIC);


void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 5000);
  Serial1.begin(115200);
  reyaxSetup(password);
  delay(10000);

  pinMode(busBuzz,OUTPUT);
  digitalWrite(busBuzz,HIGH);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.display(); // show splashscreen


}

void loop() {

   //busNmbr=busEnc.read(busNmbr);
   mappedBus=busEnc.read();
   busFind=map(mappedBus, 0,4,0,1);
   
   //Serial.printf(" %i \n", busFind);
   //busSe=map(busFind,0,95,0,4);
   if (busFind>4){
    busFind=4;
   }
   if (busFind<0){
    busFind=0;
   }
   //Serial.printf(" %i \n", busFind);
busName=busNmbr[busFind];
Serial.printf(" %i \n", busName);

// switch (busName) {
//   case 24:
//     printf("Bus24");
//     break;
//   case 19:
//     printf("Bus19");
//     break;
//   case 53:
//     printf("Bus53");
//     break;
//   case 77:
//     printf("Bus77");
//     break;
//   case 25:
//     printf("Bus25");
//     break;

// }

  //  Serial.printf("Bus is %i near:\n", busNmbr[busSe]);
  //  display.display();


  // listen for incoming lora messages and then send GPS back
  if (Serial1.available())  { // full incoming buffer: +RCV=203,50,35.08,9,-36,41 
    String parse0 = Serial1.readStringUntil('=');  //+RCV
    String parse1 = Serial1.readStringUntil(',');  // address received from
    String parse2 = Serial1.readStringUntil(',');  // buffer length
    String parse3 = Serial1.readStringUntil(',');  // fuseSound
    String parse4 = Serial1.readStringUntil(',');  // fuseDust
    String parse5 = Serial1.readStringUntil(',');  // rssi
    String parse6 = Serial1.readStringUntil(','); // snr
    String parse7 = Serial1.readStringUntil('\n'); // busNmbr
    String parse8 = Serial1.readString();          // extra

    Serial.printf("parse0: %s\nparse1: %s\nparse2: %s\nparse3: %s\nparse4: %s\nparse5: %s\nparse6: %s\nparse7: %s\nparse8: %s\n", parse0.c_str(), parse1.c_str(), parse2.c_str(), parse3.c_str(), parse4.c_str(), parse5.c_str(), parse6.c_str(), parse7.c_str(), parse8.c_str());
    delay(100);
      myTimer.startTimer(5000);
      digitalWrite(D7,HIGH);

           busHold=atoi(parse6.c_str());   
          Serial.printf("bushold %i ", busHold);
           if(busHold == busName) {
            display.clearDisplay();
            display.setTextSize(2);
            display.setTextColor(WHITE);
            display.setCursor(0,0);
            display.printf("Bus %i is coming\n",busHold);
            display.display();
        
          //using these lines to activate vibr motor
         digitalWrite(busBuzz,HIGH);
         delay(7350);
         digitalWrite(busBuzz,LOW);
  //      }


  //   // display.clearDisplay();
  //   // display.setTextSize(2);
  //   // display.setTextColor(WHITE);
  //   // display.setCursor(0,0);
  //   // display.printf("%+10.5f%+10.5f%10.2fSat: %i\n",lat, lon, alt, sat);
  //   // display.display();
  // }
 
  // if (myTimer.isTimerReady()){
  //        digitalWrite(D7,LOW);
   }
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