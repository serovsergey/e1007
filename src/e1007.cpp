#include "e1007.h"

e1007::e1007(HardwareSerial *serial, void (*ScanCallback)(String, long), int _speed, long _timeout){
  _ScanCallback = ScanCallback;
  _serial = serial;
  _serial->begin(_speed);
  timeout = _timeout;
  _serial->setTimeout(timeout);
  in_buf = new char(BUF_SIZE);
}

e1007::~e1007(){
  delete[] in_buf;
}

void e1007::cleanBuffer(){
  while (_serial->available()>0) {
    byte inChar = _serial->read();}
}

bool e1007::startScan(long param){
  if(waiting_answer) stopScan();
  char buf[100];
  memset(&buf, 0, 100);
  cleanBuffer();
  _serial->write(trigger_scan, sizeof(trigger_scan));
  delay(ANSWER_DELAY);
  int readed = _serial->readBytes(buf, ANSWER_OK_SIZE);
  if(readed==ANSWER_OK_SIZE) {
      if(!memcmp(buf, successful_answer, ANSWER_OK_SIZE)){
        scan_param = param;
        waiting_answer = true;
        in_buf_size = 0;
        timeshot=millis();
        Serial.println("... startScan Successful ...");
        return true;    
      }
  }
  if(!readed) Serial.println("!!! Scan Timeout !!!");
  return false;
}

void e1007::stopScan(){
  Serial.println("... stopScan ...");
  char buf[100];
  memset(&buf, 0, 100);
  _serial->write(stop_scan, sizeof(stop_scan));
  delay(ANSWER_DELAY);
  waiting_answer = false;
  cleanBuffer();
}

void e1007::loop(){
  if(!waiting_answer) return;
  if(millis()-timeshot > timeout) waiting_answer = false;
  while (_serial->available()>0) {
    char inChar = _serial->read();
    in_buf_size++;
    in_buf[in_buf_size-1] = inChar;
    if(in_buf_size>TERM_SIZE){
      if(!memcmp(in_buf+in_buf_size-TERM_SIZE, barcode_term, TERM_SIZE)){
        char tmpbuf[in_buf_size+1];
        memcpy(tmpbuf, in_buf, in_buf_size-1);
        tmpbuf[in_buf_size-1] = 0;
        waiting_answer = false;
        _ScanCallback(tmpbuf, scan_param);
      }
    }
  }
}

bool e1007::isWaiting(){
  return waiting_answer;
}

