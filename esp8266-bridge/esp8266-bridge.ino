#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Servo.h>


// TODO: change this for your setup
static const char* ssid = "ssid";         // Your ROUTER SSID
static const char* pw = "pass";           // WiFi PASSWORD
static const int port = 9265;


static WiFiServer server(port);
static WiFiClient client;


void setup()
{
  delay(500);
  
  Serial.begin(19200);

  // use in case of mode problem
  WiFi.disconnect();
  
  // switch to Station mode
  if (WiFi.getMode() != WIFI_STA)
    WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, pw);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
    
  // TODO
  Serial.swap();
    
  server.begin();
}

static inline void pump(Stream& input, Stream& output)
{
  const int BUFFER_SIZE = 128;
  uint8_t buf[BUFFER_SIZE]; 
  int i = 0;
  int value;
 
  while ((value = input.read()) != -1 && i < BUFFER_SIZE)
    buf[i++] = value;

  if (i > 0)
    output.write(buf, i);
}

void loop()
{
  if (client.connected() == false)
  {
    client = server.available();
  }
  else
  {
    pump(client, Serial);
    pump(Serial, client);
  }
}

