#include <Adafruit_CircuitPlayground.h>
#include <Wire.h> //communication for sensors
#include <SPI.h> //short distance communication for microcontrollers and sensors

int count = 1; // Current round count

int score = 0; // Store the player's score

// Constants for timing and game difficulty
int holding = 500; // Duration to hold the button in milliseconds
int loading = 100; // Delay between lighting up LEDs in milliseconds
int timer = 10;    // Time delay for each loop iteration in milliseconds
int level = 0;     // Game level

bool leftButtonPressed;  // if the left button is pressed
bool rightButtonPressed; // if the right button is pressed

bool slideSwitch = CircuitPlayground.slideSwitch();//slide switch

void setup() {
  Serial.begin(9600); // Initialize serial communication
  CircuitPlayground.begin(); // Initialize Circuit Playground board
}

void loop() {
  // Local variables for various aspects of light patterns
  int lightMode;
  int lightTime;
  int lightTimeR;
  int lightTimeL;

  int longerTime;

  bool slideSwitch = CircuitPlayground.slideSwitch(); // Reads the state of the slide switch

  // Clear all LEDs and turn off the red LED
  CircuitPlayground.clearPixels();
  CircuitPlayground.redLED(LOW);

  // Check if the slide switch is on
  if (slideSwitch) {
    if (count == 1) {
      // Generate random parameters for the light pattern
      int lightMode = random(1, 5);
      int lightTime = random(1, 6);
      int lightTimeR = random(1, 6);
      int lightTimeL = random(1, 6);

      // Determine the longer time between lightTimeR and lightTimeL
      if (lightTimeR > lightTimeL) {
        longerTime = lightTimeR;
      } else if (lightTimeR <= lightTimeL) {
        longerTime = lightTimeL;
      }

      //Print the longer time to serial monitor
      Serial.print("longer Time is ");
      Serial.println(longerTime);

      // Execute different light patterns based on lightMode
      switch (lightMode) {
        case 1:
          //Print current lightMode and lightTime
          Serial.print("lightMode is ");
          Serial.println(lightMode);
          Serial.print("lightTime is ");
          Serial.println(lightTime);

          // Light up LEDs with delay
          for (int i = 0; i < lightTime; i++) {
            CircuitPlayground.setPixelColor(i, 255, 0, 0);
            delay(loading);
          }
          break;

        case 2:
          // Print current lightMode and lightTimeR
          Serial.print("lightMode is ");
          Serial.println(lightMode);
          Serial.print("lightTimeR is ");
          Serial.println(lightTime);

          // Light up LEDs from right to left with delay
          for (int i = 0; i < lightTime; i++) {
            int ll = map(i, 0, 4, 9, 5);
            CircuitPlayground.setPixelColor(ll, 255, 0, 0);
            delay(loading);
          }
          break;

        case 3:
          //Print current lightMode and both lightTimeR and lightTimeL
          Serial.print("lightMode is ");
          Serial.println(lightMode);
          Serial.print("lightTimeR is ");
          Serial.println(lightTimeR);
          Serial.print("lightTimeL is ");
          Serial.println(lightTimeL);

          // Light up LEDs from both ends towards the center with delay
          for (int i = 0; i < lightTimeR || i < lightTimeL; i++) {
            if (i < lightTimeR) {
              CircuitPlayground.setPixelColor(i, 255, 0, 0);
              delay(loading);
            }
            if (i < lightTimeL) {
              CircuitPlayground.setPixelColor(9 - i, 255, 0, 0);
              delay(loading);
            }
          }
          break;

        case 4:
          //Print current lightMode
          Serial.print("lightMode is ");
          Serial.println(lightMode);

          // Light up all LEDs and turn on the red LED
          CircuitPlayground.setPixelColor(0, 255, 0, 0);
          CircuitPlayground.setPixelColor(1, 255, 0, 0);
          CircuitPlayground.setPixelColor(2, 255, 0, 0);
          CircuitPlayground.setPixelColor(3, 255, 0, 0);
          CircuitPlayground.setPixelColor(4, 255, 0, 0);
          CircuitPlayground.setPixelColor(5, 255, 0, 0);
          CircuitPlayground.setPixelColor(6, 255, 0, 0);
          CircuitPlayground.setPixelColor(7, 255, 0, 0);
          CircuitPlayground.setPixelColor(8, 255, 0, 0);
          CircuitPlayground.setPixelColor(9, 255, 0, 0);
          CircuitPlayground.redLED(HIGH);
          break;
      }

      // Variables and loop for player input
      int right = 0;
      int left = 0;
      int step = 0;

      // Loop for the "lightMode 1" pattern
      while (lightMode == 1) { //'while' loop condition checks if the value of 'lightMode' is equal to 1.
        // Increment step counter
        step++; // used to keep track of the number of steps taken within this specific pattern

        // Read button states
        leftButtonPressed = CircuitPlayground.rightButton();
        rightButtonPressed = CircuitPlayground.leftButton();

        // Check if the right button is pressed within the time limit
        if (right < lightTime && rightButtonPressed) {
          CircuitPlayground.setPixelColor(right, 0, 255, 0);
          right++;
          score++;
          Serial.println(right);
          delay(holding);
        } else if (leftButtonPressed || (step * timer) > ((lightTime * holding) * 1.5)) {
          count = 0;
          break;
        } else if (right >= lightTime) {
          passTone();
          break;
        }
        delay(timer);
      }

      // Loop for the "lightMode 2" pattern
      while (lightMode == 2) {
        // Increment step counter
        step++;

        // Read button states
        leftButtonPressed = CircuitPlayground.rightButton();
        rightButtonPressed = CircuitPlayground.leftButton();

        // Check if the left button is pressed within the time limit
        if (left < lightTime && leftButtonPressed) {
          CircuitPlayground.setPixelColor(9 - left, 0, 255, 0);
          left++;
          score++;
          Serial.println(left);
          delay(holding);
        } else if (rightButtonPressed || (step * timer) > ((lightTime * holding) * 1.5)) {
          count = 0;
          break;
        } else if (
  // right button pressed or time limit exceeded, exit loop
  left >= lightTime) {
          passTone();
          break;
        }
        delay(timer);
      }
      
      // Loop for the "lightMode 3" pattern
      while (lightMode == 3) {
        // Increment step counter
        step++;

        // Read button states
        leftButtonPressed = CircuitPlayground.rightButton();
        rightButtonPressed = CircuitPlayground.leftButton();

        // Check if the right button is pressed within the time limit
        if ((right < lightTimeR) && rightButtonPressed) {
          CircuitPlayground.setPixelColor(right, 0, 255, 0);
          delay(holding);
          right++;
          score++;
          Serial.println(right);
        }

        // Check if the left button is pressed within the time limit
        if (left < lightTimeL && leftButtonPressed) {
          CircuitPlayground.setPixelColor(9 - left, 0, 255, 0);
          delay(holding);
          left++;
          score++;
          Serial.println(left);
        }

        // Check if time limit exceeded
        if ((step * timer) > (longerTime * holding) * 1.5) {
          count = 0;
          break;
        }

        // Check if both sides reached their respective light times
        if (right >= lightTimeR && left >= lightTimeL) {
          passTone();
          break;
        }
        delay(timer);
      }

      // Loop for the "lightMode 4" pattern
      while (lightMode == 4) {
        // Increment step counter
        step++;

        // Read button states
        leftButtonPressed = CircuitPlayground.rightButton();
        rightButtonPressed = CircuitPlayground.leftButton();

        // Read light sensor value
        int lightLevel = CircuitPlayground.lightSensor();

        // Check if any button is pressed, exit loop
        if (leftButtonPressed || rightButtonPressed) {
          count = 0;
          break;
        }

        // If light level is low, light up all LEDs and increment score
        if (lightLevel < 200) {
          for (int i = 0; i < 10; i++) {
            CircuitPlayground.setPixelColor(i, 0, 255, 0);
          }
          score++;
          delay(holding);
          break;
        }
        delay(timer);
      }

      // Print the player's score
      Serial.println("your score is");
      Serial.println(score);
      Serial.println("-----------");
    }
  }
}

// Function to play a tone indicating a passed round
void passTone() {
  CircuitPlayground.playTone(440, 60);
  CircuitPlayground.playTone(466, 60);
  CircuitPlayground.playTone(494, 60);
  CircuitPlayground.playTone(523, 60);
}
