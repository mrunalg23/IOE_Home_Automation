#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLXTg6K0tH"
#define BLYNK_DEVICE_NAME "NodemcuBkynk"
#define BLYNK_AUTH_TOKEN "RqwkcVF8DelDvHvvUaGThnYd6CMLrfo4"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> 
#include <DHT.h>
#include <ThingSpeak.h>

#define DHTTYPE DHT22
#define DHTPIN 2 //D4 of ESP8266
DHT dht(DHTPIN,DHTTYPE);

WiFiClient client;
const char auth[]= BLYNK_AUTH_TOKEN;
long channelNumber = 1879010;
const char writeAPIKey[] = "6BVCKE54D2VBH6XM";

BlynkTimer timer;
float val1=2.64,val2=0.5,val3=0.65,val4=10.0,total=0;
int relay1 = 14; //D5 of ESP8266
int relay2 = 12; //D6 of ESP8266
int relay3 = 13; //D7 of ESP8266
int relay4 = 15; //D8 of ESP8266

char ssid[] = "SILIKON";
char pass[] = "silikon786786786";

void setup()  
{
  Serial.begin(115200);
  dht.begin();
  Serial.println("started");
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  WiFi.begin(ssid,pass);
  Blynk.begin(auth, ssid, pass);
  while(WiFi.status()!=WL_CONNECTED){  
    delay(200);
  }
  Serial.println("connected");
  ThingSpeak.begin(client);
}

void loop()
{
  delay(2000);
  float t = dht.readTemperature();
  Serial.println(t);
  if(t < 15.0) 
  digitalWrite(relay1, HIGH);
  Blynk.virtualWrite(V4, t);
  Blynk.run();
  delay(500);
  ThingSpeak.writeField(channelNumber,1,t,writeAPIKey);
  ThingSpeak.writeField(channelNumber,2,val1,writeAPIKey);
  ThingSpeak.writeField(channelNumber,3,val2,writeAPIKey);
  ThingSpeak.writeField(channelNumber,4,val3,writeAPIKey);
  ThingSpeak.writeField(channelNumber,5,val4,writeAPIKey);
  total=val1+val2+val3+val4;
  ThingSpeak.writeField(channelNumber,6,total,writeAPIKey);
  Serial.println(total);
}

BLYNK_WRITE(V0) {
  int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable
  Serial.print(pinValue);
  if (pinValue == 1) {
    digitalWrite(relay1, LOW);
    val1=2.64;//device 1 power
  }
  if(pinValue == 0)
  {
    digitalWrite(relay1, HIGH);
    val1=0;
  }
  Serial.println(val1);
}
BLYNK_WRITE(V1) {
  //red bulb
  int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable
  Serial.print(pinValue);
  if (pinValue == 1) {
    digitalWrite(relay2, LOW);
    val2=0.5;
  }
  if(pinValue == 0)
  {
    digitalWrite(relay2, HIGH);
    val2=0;
  }
  Serial.println(val2);
}
BLYNK_WRITE(V2) {
  //white bulb
  int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable
  Serial.print(pinValue);
  if (pinValue == 1) {
    digitalWrite(relay3, LOW);
    val3=0.65;
  }
  if(pinValue == 0)
  {
    digitalWrite(relay3, HIGH);
    val3=0;
  }
  Serial.println(val3);
}
BLYNK_WRITE(V3) {
  int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable
  Serial.print(pinValue);
  if (pinValue == 1) {
    digitalWrite(relay4, LOW);
    val4=10.0;
  }
  if(pinValue == 0)
  {
    digitalWrite(relay4, HIGH);
    val4=0;
  }
  Serial.println(val4);
}
