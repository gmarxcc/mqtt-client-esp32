#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Familia 2.4G";
const char* password = "rr20072015";
const char* mqttServer = "192.168.1.17";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";

WiFiClient espClient;
PubSubClient client(espClient);

void OnMqttReceived(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Received on ");
    Serial.print(topic);
    Serial.print(": ");
    String content = "";
    for (size_t i = 0; i < length; i++)
    {
        content.concat((char)payload[i]);
    }
    Serial.print(content);
    Serial.println();
}

void setup()
{ Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("...................................");

  Serial.print("Connecting to WiFi.");
  while (WiFi.status() != WL_CONNECTED)
       {  delay(500);
          Serial.print(".") ;
       }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
while (!client.connected())
{      Serial.println("Connecting to MQTT...");
       if (client.connect("prueba", mqttUser, mqttPassword ))
           {Serial.println("connected");
           client.subscribe("prueba/xd");
           client.setCallback(OnMqttReceived);
           }
       else
       {   Serial.print("failed with state ");
           Serial.print(client.state());
           delay(2000);
       }
}
}

void loop()
  {  client.loop();
     char str[16];

if(Serial.read()>0)
{
sprintf(str, "%u", random(100));

client.publish("prueba/xd", str);
Serial.println(str);
delay(100);
}
     
     
     
 }
