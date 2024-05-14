#define BLYNK_TEMPLATE_NAME "MicroProjectRoof"
#define BLYNK_TEMPLATE_ID "Your_Template_ID_Here"  // Define an arbitrary template ID

#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char authPerson1[] = "x3P0t5qhWV82fzUaWHlj5aCxt6Yrwxe-";
char authPerson2[] = "VOwxdT9RwlYSn1SB_jKyHccj-flYfjMF";

char ssid[] = "One Virus Found";        // Your WiFi SSID
char pass[] = "mfaho499";    // Your WiFi password

char currentAuth[] = "VOwxdT9RwlYSn1SB_jKyHccj-flYfjMF"; // Current authentication token

#define SERVO_PIN D1  // Define the pin for the servo motor
Servo myServo; // Create a servo object

void setup() {
  Serial.begin(115200);
  Blynk.begin(currentAuth, ssid, pass);
  myServo.attach(SERVO_PIN); // Attach the servo to the pin
}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(V0) {
  // Function triggered when data is received from the Terminal widget (V0)
  String command = param.asStr(); // Get the received command as a string
  Serial.println("Received command: " + command);
  if(command =="123" || command =="345"){
      Blynk.virtualWrite(V0, "Password is correct. Unlocking the roof door!\nIt will be opened for 10 seconds only\n");
      myServo.write(180); // Rotate servo to 90 degrees
      delay(9000); // Delay for 10 second
      Blynk.virtualWrite(V0, "\nThe roof door is closing in 1 sec!\n");
      delay(1000);
      myServo.write(0); // Rotate servo back to 0 degrees
      Blynk.virtualWrite(V0, "\nThe roof door is closed!");
      Serial.println("Servo ran");
    }
  if (command == "person1") {
    strncpy(currentAuth, authPerson1, sizeof(currentAuth)); // Set authentication token to person 1's token
    Blynk.config(currentAuth); // Reconfigure Blynk with the new authentication token
    Serial.println("Switched to person 1's authentication token");
    delay(15000); // Delay for 15 seconds
    Blynk.virtualWrite(V0, "Provide the Password to unlock: "); // Write to V0 pin
  } else if (command == "person2") {
    strncpy(currentAuth, authPerson2, sizeof(currentAuth)); // Set authentication token to person 2's token
    Blynk.config(currentAuth); // Reconfigure Blynk with the new authentication token
    Serial.println("Switched to person 2's authentication token");
    delay(15000); // Delay for 15 seconds
    Blynk.virtualWrite(V0, "Provide the Password to unlock: "); // Write to V1 pin
  } else {
//    Serial.println("Invalid command");
  }
}
