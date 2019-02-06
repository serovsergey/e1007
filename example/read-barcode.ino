#include "e1007.h"

HardwareSerial Serial2(2);
e1007 scanner(&Serial2, &ScanCallback, 9600);

void setup() {
  Serial.begin(115200);
}

void ScanCallback(char* barcode, long mode){
  Serial.print("Scanned Barcode: ");
  Serial.println();
}

void loop() {
  long scan_mode = 1;
  if(!scanner.startScan(scan_mode)){
    Serial.println("Scan start error!");
  }
  delay(5000);
}
