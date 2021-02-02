#include <SoftwareSerial.h>
SoftwareSerial GPRS(7,8);
boolean state, lastState;

void setup() 
{
  pinMode(2,INPUT_PULLUP);
  state = digitalRead(2);
  lastState = state;
  GPRS.begin(9600);
  GPRS.println("AT");
  delay(1000); 
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(1000);
  
  delay(8000);
  digitalWrite(10,HIGH);
  delay(1000);
  digitalWrite(10,LOW);
  delay(1000);
  sendSMSpembuka();
  delay(500);
  
}

void loop() 
{
  while(GPRS.available())
  {
    Serial.write(GPRS.read());
  }
  lastState = state;
  state = digitalRead(2);
  if(state != lastState)
  {
    sendSMS();
  }
  delay(500);
}

void sendSMS()
{
  
  GPRS.println("AT+CMGS=\"+62895806377168\"");
  delay(500);
  
  GPRS.println("PINTU TELAH"); 
  GPRS.println(state ? "DI BUKA" : "DI TUTUP KEMBALI");
  GPRS.write(0x1a);
  delay(500);

  
}

void sendSMSpembuka()
{
  GPRS.println("AT+CMGS=\"+62895806377168\"");
  delay(500);
  GPRS.println("Sistem Telah Siap");
  GPRS.write(0x1a);
  delay(500);
}
