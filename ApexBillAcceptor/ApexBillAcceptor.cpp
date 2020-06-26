#include <ApexBillAcceptor.h>

ApexBillAcceptor::ApexBillAcceptor(int a, int b, int c, int d){
	pin_enable_line = a;
	pinMode(pin_enable_line, OUTPUT);
	digitalWrite(pin_enable_line, LOW);
	
	pin_interrupt_line = b;						
	pinMode(pin_interrupt_line, INPUT);
	
	pin_send_line = c;
	pinMode(pin_send_line, OUTPUT);					
	
	pin_ttl_rx = d;
	pinMode(pin_ttl_rx, INPUT_PULLUP);
	mySerial = new ReceiveOnlySoftwareSerial(pin_ttl_rx);
	mySerial->begin(600);
}

int ApexBillAcceptor::checkForBill(){
	if (digitalRead(pin_interrupt_line) == LOW){
		digitalWrite(pin_send_line, LOW);
		digitalWrite(pin_send_line, HIGH);  

		delay(5);
		
		if (mySerial->available()){
			int code = mySerial->read();					
			return code;
		}
	}
	return 0;
}

char* ApexBillAcceptor::getDescription(int codeFromBillAcceptor){
	for(int i=0; i < sizeof(codes)/sizeof(codes[0]); i++){
		if (codes[i].code == codeFromBillAcceptor){
			return codes[i].description;
		}
	}
	return "(code undefined)";
}

//returns Bill value
int ApexBillAcceptor::getValue(int codeFromBillAcceptor){
	switch(billCode) {
		case 0x81:
			return(1);
			break;
		case 0x83:
			return(5);      
			break;
		case 0x84:
			return(10);
			break;
		case 0x85:
			return(20);  
			break;
		case 0x86:
			return(50);
			break;
		case 0x87:
			return(100);  
			break;			
		default:
			return(0);
			break;	
	}
}

void ApexBillAcceptor::enable(){
	digitalWrite(pin_enable_line, LOW);
}

void ApexBillAcceptor::disable(){
	digitalWrite(pin_enable_line, HIGH);
}

void ApexBillAcceptor::toggle(){
	digitalWrite(pin_enable_line, !digitalRead(pin_enable_line));
}
