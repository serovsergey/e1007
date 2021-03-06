#pragma once
#include "arduino.h"

#define BUF_SIZE 100
#define ANSWER_DELAY 250

const unsigned char PROGMEM successful_answer[] = {
  0x07, 0x31, 0x04, 0x01, 0x01, 0x06, 0xFF, 0xFE, 0xBE};
const unsigned char PROGMEM barcode_term[] = {
  0x0D, 0x0A};
  
#define ANSWER_OK_SIZE sizeof(successful_answer)
#define TERM_SIZE sizeof(barcode_term)

const unsigned char PROGMEM trigger_scan[] = {
  0x0A, 0x04, 0x31, 0x00, 0x00, 0x59, 0x4c, 0x54, 0x4b, 0xFF, 0xFD, 0x7E};
const unsigned char PROGMEM stop_scan[] = {
  0x0A, 0x04, 0x31, 0x00, 0x00, 0x59, 0x4c, 0x53, 0x4b, 0xFF, 0xFD, 0x7F};  
/*const unsigned char PROGMEM read_ver[] = {
  0x0A, 0x04, 0x31, 0x00, 0x00, 0x59, 0x52, 0x56, 0x4b, 0xFF, 0xFD, 0x76};*/
  
class e1007 {

  private:
    HardwareSerial *_serial;
    void (*_ScanCallback)(char *, long);
    char *in_buf;
    bool waiting_answer;
    void cleanBuffer();
    int in_buf_size;
    long timeout;
    long timeshot;
    long scan_param;
  
  public:
    e1007(HardwareSerial*, void (*_ScanCallback)(char*, long), int = 9600, long = 4000);
    ~e1007();
    void loop();
    bool startScan(long = 0);
    void stopScan();
    bool isWaiting();
};


