
/*
 * Code:   Develop offline Webserver to control GPIO: Demonstrate offline webserver using HTML webpage 
 *         which can be accessed from web browser and through which LED can be toggled
 *  
 *    The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *    server_ip is the IP address of the ESP8266 module, will be 
 *    printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>
  
#define LED1 D1
#define LED2 D2
#define LED3 D3
#define LED4 D4

int val1=0, val2=0, val3=0, val4=0;
const char* ssid = "VVPEC"; //WiFiSSID
const char* password = "vvpec@123"; //PASSWORD

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,HIGH);
  
 // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid,password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
  
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  //s += (val)?"high":"low";
  s+= "<h1>ESP8266 WEB SERVER</h1>\r\n";
  s+= "<h3>NoT using Web Application </h3>\r\n";
  s+= "<p>LIGHT1 <a href=\"?pin=ON1\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF1\"><button>OFF</button></a></p>\r\n";
  s+= "<p>LIGHT2 <a href=\"?pin=ON2\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF2\"><button>OFF</button></a></p>\r\n";
  s+= "<p>FAN1 <a href=\"?pin=ON3\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF3\"><button>OFF</button></a></p>\r\n";
  s+= "<p>FAN2 <a href=\"?pin=ON4\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF4\"><button>OFF</button></a></p>\r\n";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request

   if (req.indexOf("?pin=ON1") != -1)
   {  val1 = 0;
      digitalWrite(LED1, val1);}
  else if (req.indexOf("?pin=OFF1") != -1)
  {val1 = 1;
   digitalWrite(LED1, val1);}
  else if (req.indexOf("?pin=ON2") != -1)
   {  val2 = 0;
      digitalWrite(LED2, val2);}
  else if (req.indexOf("?pin=OFF2") != -1)
    { val2 = 1;
      digitalWrite(LED2, val2);}
  else if (req.indexOf("?pin=ON3") != -1)
    {val3 = 0;
     digitalWrite(LED3, val3);}
  else if (req.indexOf("?pin=OFF3") != -1)
    {val3 = 1;
    digitalWrite(LED3, val3);}
  else if (req.indexOf("?pin=ON") != -1)
    {val4 = 0;
     digitalWrite(LED4, val4);}
  else if (req.indexOf("?pin=OFF") != -1)
    {val4 = 1; 
     digitalWrite(LED4, val4);}
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set GPIO2 according to the request
//  digitalWrite(LED1, val1);
 // digitalWrite(LED2, val2);
  //digitalWrite(LED3, val3);
 // digitalWrite(LED4, val4);
    client.flush();

  // Prepare the response
 /* String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  s += (val)?"high":"low";
  s+= "<h1>ESP8266 WEB SERVER</h1>\r\n";
  s+= "<h3>Program Created for : Workshop on IOT</h3>\r\n";
  s+= "<p>GPIO0 <a href=\"?pin=ON1\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF1\"><button>OFF</button></a></p>\r\n";
  s+= "<p>GPIO2 <a href=\"?pin=ON2\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF2\"><button>OFF</button></a></p>\r\n";
  s += "</html>\n";*/

      // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
