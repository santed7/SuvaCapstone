/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/vcox/Documents/IoT/SuvaCapstone/BlueMACv1/src/BlueMACv1.ino"
/*
 * Project BlueInTheFace2
 * Description: BLE Scanner
 * Author: Brian Rashap
 * Date: 27-MAR-2023
 */
// Create BLE Scanner Object

#include <Adafruit_BME280.h>

void setup();
void loop();
#line 11 "c:/Users/vcox/Documents/IoT/SuvaCapstone/BlueMACv1/src/BlueMACv1.ino"
const byte SCAN_RESULT_MAX = 40;
BleScanResult scanResults[SCAN_RESULT_MAX];
// Declare Variables
byte count, i,j;
byte buf[BLE_MAX_ADV_DATA_LEN];
byte mac[SCAN_RESULT_MAX][6];
int8_t rssi[SCAN_RESULT_MAX];
BleAdvertisingData data;


SYSTEM_MODE(MANUAL);
void setup() {
    Serial.begin(9600);
    waitFor(Serial.isConnected,10000);
    BLE.on();
     BLE.advertise(&data);
}
void loop() {
    // Only scan for 500 milliseconds
    BLE.setScanTimeout(500);
    count = BLE.scan(scanResults, SCAN_RESULT_MAX);
    Serial.printf("%i devices found\n",count);
    for (int i = 0; i < count; i++) {
        scanResults[i].advertisingData().get(BleAdvertisingDataType::MANUFACTURER_SPECIFIC_DATA, buf, BLE_MAX_ADV_DATA_LEN);
        for(j=0;j<6;j++){
            mac[i][j] = scanResults[i].address()[j];
            rssi[i] = scanResults[i].rssi();
        }
        Serial.printf("MAC address = %02X:%02X:%02X:%02X:%02X:%02X. RSSI = %i\n",mac[i][0],mac[i][1],mac[i][2],mac[i][3],mac[i][4],mac[i][5],rssi[i]);
    
    }
  delay(5000);
}