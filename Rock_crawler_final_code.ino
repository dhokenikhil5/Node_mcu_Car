// NodeMCU Based WIFI Controlled Car//

#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)

#include <ESP8266WiFi.h>
#include <WiFiClient.h>  
#include <ESP8266WebServer.h>
#include <Servo.h>

String command;             //String to store app command state.
Servo myservo;              // create Servo object to control a servo
int speedCar = 800;         // 400 - 1023.
int currentAngle = 90;      // Default position

const char* ssid = "Nik's Wifi Car";
ESP8266WebServer server(80);

void setup() 
{
 
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 

 myservo.attach(D4);               // attaches the servo on pin 9 to the Servo object

 myservo.write(currentAngle);     // Set to center initially 

 Serial.begin(115200);
 
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void goAhead()                                           
{ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);

}

void goBack()
{ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
}

void move_steering_right()
{ 
   myservo.write(120);                // Move servo to 30 degree left                          
}

void move_steering_left()
{
   myservo.write(60);                  // Move servo to 30 degree right                          
}

void goAheadRight()
{
      myservo.write(120);              

      digitalWrite(IN_1, LOW);         // Ahead Logic
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
}

void goAheadLeft()
{
      myservo.write(60);
                             

      digitalWrite(IN_1, LOW);         // Ahead Logic
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
}

void goBackRight()
{ 
      myservo.write(120);
                              
      
      digitalWrite(IN_1, HIGH);       // Back Logic
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
}

void goBackLeft()
{ 
      myservo.write(60);
                             

      digitalWrite(IN_1, HIGH);        // Back Logic
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
}

void stopRobot()
{  

      myservo.write(90);              // tell servo to go to default position 
                             

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
}

void loop() 
{
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") move_steering_left();
      else if (command == "R") move_steering_right();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "0") speedCar = 400;
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023;
      else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) 
{

if( server.hasArg("State"))
{
       Serial.println(server.arg("State"));
}
  server.send ( 200, "text/html", "" );
  delay(1);
}
