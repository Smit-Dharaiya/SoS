#include<WiFiEsp.h>
#include <WiFiEspClient.h>
#include <PubSubClient.h>

int smokeA0 = A0;

char ssid[] = "Hi"; // your network SSID (name)
char pass[] = "ahol6956"; // your network password  
int status = WL_IDLE_STATUS; // the Wifi radio's status

WiFiEspClient espClient;

PubSubClient client(espClient);


void setup() {
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
  Serial3.begin(115200);
  WiFi.init(&Serial3);
  status = WiFi.begin(ssid,pass);

  client.setServer("3.84.0.107",1883);
  if (!client.connected()) {
    Serial.print(client.connected());
    }

    client.connect("CID01");
    delay(3000);

    if (client.connected()) {
    Serial.print(client.state()+"Connected");
    }
    client.publish("CID01","Hell0");
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  if(analogSensor>180){
    client.publish("CID01","ALERT GAS LIMIT EXCEEDED");
  }

  if (!client.connected()) {
    Serial.print(client.connected());
    client.connect("CID01");
    }

    
    
  delay(5000);

  
}
