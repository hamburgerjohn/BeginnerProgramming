char data;
String SerialData="";


void setup() {
  Serial.begin(115200);
  pinMode(D0, OUTPUT);

}

void loop() {
  while(Serial.available())
  {
     delay(15);
     data=Serial.read();
     SerialData+=data;
  }
  if(SerialData=="on")
  {
    digitalWrite(D0, LOW);
    Serial.println("LED ON");
  }
  if(SerialData=="off")
  {
    Serial.println("LED OFF");
    digitalWrite(D0,HIGH);
  }
  SerialData="";

}
