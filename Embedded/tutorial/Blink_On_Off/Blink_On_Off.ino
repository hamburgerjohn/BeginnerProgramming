char data;
String SerialData="off";


void setup() {
  Serial.begin(115200);
  pinMode(D0, OUTPUT);
  pinMode(D2, OUTPUT);
  

}

void OnOff(){
  while(Serial.available())
  {
     delay(15);
     data=Serial.read();
     SerialData+=data;
  }
  if(SerialData=="on")
  {
    digitalWrite(D0, LOW);
    digitalWrite(D2, LOW);
    delay(1000);
    digitalWrite(D0,HIGH);
    digitalWrite(D2,HIGH);
    Serial.println("Power ON");
  }
  if(SerialData=="off"){
    digitalWrite(D0, LOW);
    digitalWrite(D2, LOW);
    delay(5500);
    digitalWrite(D0,HIGH);
    digitalWrite(D2,HIGH);
    Serial.println("Power OFF");
  }
 
  SerialData="";
}

void loop() {

  OnOff();

}
