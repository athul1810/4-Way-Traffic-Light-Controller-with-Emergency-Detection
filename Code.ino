const int redPins[] = {2, 5, 8, 11};      // Red LEDs for all directions
const int orangePins[] = {3, 6, 9, 12};   // Orange LEDs for all directions
const int greenPins[] = {4, 7, 10, 13}; // Green LEDs for all directions
const int irSensors[] = {22, 24, 26, 30}; // IR sensor pins
int threshold = 500; // Adjust this threshold value based on your setup
#define button1 52
#define green A0
int value,temp;
#define red 53
bool whiteDetected = false; // Track if white is detected
bool ped1 = false;
int a;
void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(redPins[i], OUTPUT);
    pinMode(orangePins[i], OUTPUT);
    pinMode(greenPins[i], OUTPUT);
    pinMode(irSensors[i], INPUT);
  }
  for (int i = 0; i < 4; i++) {
    turnOnRedf(i);
    turnOnOrangef(i);
    turnOnGreenf(i);
    turnOnOrangef(i);
    turnOnRedf(i);
  } 
  pinMode(button1,INPUT);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  Serial.begin(9600);
}

void turnOnGreen(int direction) {
  digitalWrite(redPins[direction], LOW);
  digitalWrite(orangePins[direction], LOW);
  digitalWrite(greenPins[direction], HIGH);
  delay(500);
}

void turnOnOrange(int direction) {
  digitalWrite(redPins[direction], LOW);
  digitalWrite(orangePins[direction], HIGH);
  digitalWrite(greenPins[direction], LOW);
  delay(500); // Orange for 2 seconds
}

void turnOnRed(int direction) {
  digitalWrite(orangePins[direction], LOW);
  digitalWrite(greenPins[direction], LOW);
  digitalWrite(redPins[direction], HIGH);
  delay(500); // Red for 2 seconds
}

void turnOnGreenf(int direction) {
  digitalWrite(redPins[direction], LOW);
  digitalWrite(orangePins[direction], LOW);
  digitalWrite(greenPins[direction], HIGH);
  delay(2);
}

void turnOnOrangef(int direction) {
  digitalWrite(redPins[direction], LOW);
  digitalWrite(orangePins[direction], HIGH);
  digitalWrite(greenPins[direction], LOW);
  delay(2); // Orange for 2 seconds
}

void turnOnRedf(int direction) {
  digitalWrite(orangePins[direction], LOW);
  digitalWrite(greenPins[direction], LOW);
  digitalWrite(redPins[direction], HIGH);
  delay(2); // Red for 2 seconds
}

void loop() {
        analogWrite(red,150);
        temp=0;
    delay(25);
    analogWrite(green,0);
    delay(25);
    int ped1value = digitalRead(button1);

  // Read the values from the IR sensors
  int irSensorValues[4];  // Create an array to store the sensor values

  for (int i = 0; i < 4; i++) {
    irSensorValues[i] = digitalRead(irSensors[i]); // Use analogRead for IR sensors
  }

  // Check if any of the IR sensors are detecting "white"
  whiteDetected = false; // Reset the flag
  ped1=false;
  for (int i = 0; i < 4; i++) {
    if (irSensorValues[i] == 0) {
      whiteDetected = true;
      break;  // Exit the loop as soon as one sensor detects white
    }
  }
  if(ped1value==0)
  {
    ped1=true;
  }
  else
  {
    ped1=false;
  }
  // Traffic light cycle: Red -> Orange -> Green -> Orange -> Red
  if (whiteDetected) {
    // Turn on the corresponding green light while the others are off
    for (int i = 0; i < 4; i++) {
      if (whiteDetected && irSensorValues[i] == 0) {
        turnOnGreen(i);
        a = i;
        delay(200); // Allow some time for detection to stabilize
        digitalWrite(greenPins[i], LOW);
      } else {
        // Turn off the other lights
        digitalWrite(orangePins[i], LOW);
        digitalWrite(greenPins[i], LOW);
      }
    }
  } else {
    // If no white is detected, follow your regular traffic light cycle
    for (int i = a ; i < 4; i++) {
      turnOnRed(i);
      turnOnOrange(i);
      turnOnGreen(i);
      turnOnOrange(i);
      turnOnRed(i);
      value=digitalRead(button1);
      if(value==0)
      {
        temp=1;

      }

      int irSensorValues[4];  // Create an array to store the sensor values

  for (int i = 0; i < 4; i++) {
    irSensorValues[i] = digitalRead(irSensors[i]); // Use analogRead for IR sensors
  }

  // Check if any of the IR sensors are detecting "white"
  whiteDetected = false; // Reset the flag

  for (int i = 0; i < 4; i++) {
    if (irSensorValues[i] == 0) {
      whiteDetected = true;
      break;  // Exit the loop as soon as one sensor detects white
    }
  }

  // Traffic light cycle: Red -> Orange -> Green -> Orange -> Red
  if (whiteDetected) {
    // Turn on the corresponding green light while the others are off
    ped1 =false;
    for (int i = 0; i < 4; i++) {
      if (whiteDetected && irSensorValues[i] == 0) {
        turnOnGreen(i);
        delay(200); // Allow some time for detection to stabilize
        digitalWrite(greenPins[i], LOW);
        break;
        break;
      } else {
        // Turn off the other lights
        digitalWrite(orangePins[i], LOW);
        digitalWrite(greenPins[i], LOW);
        break;
      }
      digitalWrite(redPins[i],HIGH);
    }break;
    }a=0;
  }
  }
  analogWrite(red,150);
    delay(25);
    analogWrite(green,0);
    delay(25);

  if(temp==1)
  {
    analogWrite(red,0);
    delay(25);
    analogWrite(green,150);
    turnOnRed(0);
    turnOnRed(1);
    turnOnRed(2);
    turnOnRed(3);

    delay(1200);  
    analogWrite(red,150);
    delay(25);
    analogWrite(green,0);
    delay(25);
  }
  
}