#include <Arduino.h>
#include <ApexBillAcceptor.h>

#define PIN_ENABLE 7 //Purple wire, to enable set low, to disable set high
#define PIN_INTERRUPT_LINE 8 //Orange wire on Apex, Request to send data to host
#define PIN_SEND_LINE 9 //White/Blue wire, Host Ready Signal
#define PIN_TTL_RX 10 //Green wire, Transmit Data Line from acceptor

const int  outputPin  = 12;
const int  pulseOn  = 300;
const int  pulseOff = 300; 
const int  pulsePerDollar = 10;

ApexBillAcceptor *billAcceptor;
int code;

void setup() {
    Serial.begin(9600); 
    pinMode(outputPin, OUTPUT);   
    billAcceptor = new ApexBillAcceptor(PIN_ENABLE, PIN_INTERRUPT_LINE, PIN_SEND_LINE, PIN_TTL_RX);    
}

void loop() {
    if(code = billAcceptor->checkForBill()){
        Serial.print("Code: 0x");
        Serial.print(code, HEX);
        Serial.print(", Description: ");
        Serial.println(billAcceptor->getDescription(code));
        int pulse=billAcceptor->getValue(code)*pulsePerDollar;
        for (int i = 1; i <= pulse; i++) {
            digitalWrite(outputPin, HIGH);
            delay(pulseOn);
            digitalWrite(outputPin, LOW);
            delay(pulseOff);
        }
    }
}
