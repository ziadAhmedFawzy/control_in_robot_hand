// open server and connect from wiFi
#include <WiFi.h>
// control in servo from ESP-32
#include <ESP32Servo.h>

// servo zone
Servo fing1,fing2,fing3,fing4;

// servo pin
int servoPin1 = 14, servoPin2 = 27, servoPin3 = 32, servoPin4 = 33;

// delay
int hold = 1000;

// my Wifi or hotspot
const char* ssid     = "Ziad";
const char* password = "helloWorld11";

WiFiServer server(80);

void setup()
{   
    Serial.begin(115200);
    // delay(milli)
    delay(10);

    // We start by connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
    
    // attach   //pin servo
    fing1.attach(servoPin1);
    fing2.attach(servoPin2);
    fing3.attach(servoPin3);
    fing4.attach(servoPin4);
}

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // desgin my website:
            client.print("<!DOCTYPE html>");
            client.print("<html lang=\"en\">");
            client.print("<head><meta charset=\"UTF-8\">");
            client.print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            client.print("<meta name=\"description\" content=\"this's website to control in robot hand\">");
            client.print("<meta name=\"author\" content=\"ziad Fawzy\">");
            client.print("<title>control in robot hand</title>");
            client.print("<style>");
            client.print(".header {font-family: \"cairo\";text-align: center;font-weight: bold;color: #fff;text-transform: uppercase;}");
            client.print(".header img {width: 150px;}");
            client.print("body {background-color: #03a9f4;}");
            client.print(".parent {display: flex;flex-flow: row wrap;justify-content: center;align-items: center;width: 90%;margin: 20px auto;}");
            client.print(".parent div {margin: 10px 50px;border: 10px solid #fff;");
            client.print("border-radius: 50%;padding: 10px;display: flex;justify-content: center;align-items: center;");
            client.print("font-family: \"cairo\";font-size: 53px;width: 100px;height: 100px;transition-duration: 0.5s;}");
            client.print(".parent div a {font-size: 60px;text-decoration: none;color: #673ab7;}");
            client.print("</style>");
            client.print("</head>");
            client.print("<body>");
            client.print("<div class=\"header\"><h1>control in robot's hand</h1><p>IoT innovators</p></div>");
            client.print("<div class=\"parent\">");
            client.print("<div class=\"child1\"><azzz href=\"/1\">1</a></div>");
            client.print("<div class=\"child2\"><a href=\"/2\">2</a></div>");
            client.print("<div class=\"child3\"><a href=\"/3\">3</a></div>");
            client.print("<div class=\"child4\"><a href=\"/4\">4</a></div>");
            client.print("<div class=\"child5\"><a href=\"/5\">5</a></div>");
            client.print("</div>");
            client.print("</body>");
            client.print("</html>");
            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // get postion hands
        if (currentLine.endsWith("GET /1")) {
          fing1.write(0);
          delay(hold);
          fing2.write(0);
          delay(hold);
          fing4.write(0);
          delay(hold);
          fing3.write(0);
          delay(hold);
        }
        if (currentLine.endsWith("GET /2")) {
          fing1.write(170);
          delay(hold);
          fing2.write(0);
          delay(hold);
          fing4.write(0);
          delay(hold);
          fing3.write(0);
          delay(hold);
        }
        if (currentLine.endsWith("GET /3")) {
          fing1.write(170);
          delay(hold);
          fing2.write(170);
          delay(hold);
          fing4.write(0);
          delay(hold);
          fing3.write(0);
          delay(hold);
        }
        if (currentLine.endsWith("GET /4")) {
          fing1.write(170);
          delay(hold);
          fing2.write(170);
          delay(hold);
          fing4.write(170);
          delay(hold);
          fing3.write(0);
          delay(hold);
        }
        if (currentLine.endsWith("GET /5")) {
          fing1.write(170);
          delay(hold);
          fing2.write(170);
          delay(hold);
          fing4.write(170);
          delay(hold);
          fing3.write(170);
          delay(hold);
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
