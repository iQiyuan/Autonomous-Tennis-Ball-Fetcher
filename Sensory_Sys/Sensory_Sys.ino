/*_______________________________________________________
1. Documentation

2. Suggestion of Possible MotorCommand:
  2.1. MotorCommand #1: Heading to Tennis Ball.
  2.2. MotorCommand #2: Avoid Opponent.
  2.3. MotorCommand #3: Search Around.
  2.4. MotorCommand #4: Collect Tennis Ball.
  2.5. MotorCommand #5: Back to Box.
  2.6. MotorCommand #6: Drop Tennis Ball.
_______________________________________________________*/



//_______________________________________________________
// tennis ball detection system configurations & functions
//_______________________________________________________

const int IR1 = A0, IR2 = A1, IR3 = A2, IR4 = A3;
int indexing(int sensorPin) {
  // indexing the sensor pin
  int sensorIndex;
  if (sensorPin == IR1) {sensorIndex = 0;} 
  else if (sensorPin == IR2) {sensorIndex = 1;} 
  else if (sensorPin == IR3) {sensorIndex = 2;} 
  else if (sensorPin == IR4) {sensorIndex = 3;}
  return sensorIndex;
}

int lastValue[4] = {0};
bool isObjectInfront(int sensorPin) {
  // analog read 500+ consistently in 1 ~ 12 cm
  int sensorIndex = indexing(sensorPin);
  int rawValue = analogRead(sensorPin);
  bool exist = (lastValue[sensorIndex] >= 500 && rawValue >= 500);
  lastValue[sensorIndex] = rawValue;
  return exist;
}

unsigned long startTime[4] = {0};
unsigned long dynamicDuration[4] = {0};
unsigned long timeElapse(int sensorPin) {
  // time elapsed when isObjectInFront reads TRUE
  int sensorIndex = indexing(sensorPin);
  // int rawValue = analogRead(sensorPin);
  if (isObjectInfront(sensorPin)) {
    if (startTime[sensorIndex] == 0) {
      startTime[sensorIndex] = millis();
    }
    else {
      dynamicDuration[sensorIndex] = millis() - startTime[sensorIndex];
    }
  }
  else {
    startTime[sensorIndex] = 0;
    dynamicDuration[sensorIndex] = 0;
  }
  return dynamicDuration[sensorIndex];
}

unsigned long max[4] = {0};
unsigned long maxTimeDuration (int sensorPin, unsigned long timeElapsed, bool reset) {
  // give final duration of sweeping
  int sensorIndex = indexing(sensorPin);
  if (timeElapsed > max[sensorIndex]) {max[sensorIndex] = timeElapsed;}
  if (reset) {max[sensorIndex] = 0;}
  return max[sensorIndex];
}

unsigned long lowerLimit = 1000;
unsigned long middleLimit = 2000;
unsigned long upperlimit = 3000;
unsigned long maxTime[4] = {0};
int whatInfront(int sensorPin, unsigned long timeElapsed) {
  // based on time elapsed to classify what in front
  int sensorIndex = indexing(sensorPin);
  int result = 0;
  if (isObjectInfront(sensorPin)) {
    maxTime[sensorIndex] = maxTimeDuration(sensorPin, timeElapsed, false);
    Serial.println("Object is infront, max time: " + String(maxTime[sensorIndex]));
  }
  else {
    int resetMaxTime = maxTimeDuration(sensorPin, timeElapsed, true);
    if (maxTime[sensorIndex] >= lowerLimit && maxTime[sensorIndex] <= middleLimit) {
      maxTime[sensorIndex] = 0;
      result = 1;
      Serial.println("Ball! #MotorCommand Collect"); delay(5000);
    }
    else if ((maxTime[sensorIndex] >= middleLimit && maxTime[sensorIndex] <= upperlimit)) {
      maxTime[sensorIndex] = 0;
      result = 2;
      Serial.println("Opponent! #MotorCommand Bypass"); delay(5000);
    }
    else {
      maxTime[sensorIndex] = 0;
      result = 3;
      Serial.println("Nothing! #MotorCommand Search");
    }
    return result;
  }
}

void isOppo(int RT, int LT) {
  //check if opponent encountered
  if (isObjectInfront(RT) || isObjectInfront(LT)) {
    Serial.println("isOppo triggered");
  }
  else {Serial.println("Now proceed to isBall");}
}

void isBall(int RB, int LB) {
  int searcher = whatInfront(RB, timeElapse(RB));
  int comfirmer = whatInfront(LB, timeElapse(LB));
  if (searcher == 1 || comfirmer == 1) {
    Serial.println("isBall triggered, #MotorCommand 1 Needed"); delay(2000);
    Serial.println("done #MotorCommand 1, search again, #MotorCommand 2 Needed"); delay(2000);
    int comfirmer = whatInfront(LB, timeElapse(LB));
    if (comfirmer == 1) {
      Serial.println("isBall comfirm a ball infront, #MotorCommand 4 Needed"); delay(2000);
    }
    else {
      Serial.println("isBall false alarm, #MotorCommand 3 Needed"); delay(2000);
    }
  }
  if (searcher == 2 || comfirmer ==2) {
    Serial.println("isBall triggered, Oppo infront, #MotorCommad 2 Needed");
  }
}

//_______________________________________________________
// line tracking system configurations & functions
//_______________________________________________________

bool reflectiveDetect(int sensorPin) {
  // boolean value indicate detection
  int rawValue = analogRead(sensorPin);
  int threshold = 750;
  return (rawValue <= threshold);
}

const int lineTrackPin[4] = {A7, A8, A9, A10};
int isDetect(int LTPinList[], int size) {
  // based on detection give motor command
  bool detected = false;
  int result = 0;
  for (int i = 0; i < size; i++) {
    int sensorPin = LTPinList[i];
    if (reflectiveDetect(sensorPin)) {
      detected = true;
      if (sensorPin == A7) {result = 4;}
      else if (sensorPin == A8) {result = 5;}
      else if (sensorPin == A9) {result = 6;}
      else if (sensorPin == A10) {result = 7;}
    }
  }
  if (detected) {return result;} 
  else {
    Serial.println("nothing in front, keep searching");
    return 3;
  }
}

//_______________________________________________________
// limit switch system configurations & functions
//_______________________________________________________

const int LS1 = A12, LS2 = A13, LS3 = A14, LS4 = A15;
bool isCapture(int LS_isCaptured) {
  // bool value reflects is ball captured
  int lsState = digitalRead(LS_isCaptured);
  if (lsState == LOW) {
    Serial.println("isCaptured TRUE, #MotorCommand 5 Needed");
    return true;
  }
  else {return false;}
}

bool isReturn(int LS_back_1, int LS_back_2) {
  // bool value reflect is vehicle returne
  bool LSB1 = digitalRead(LS_back_1) == LOW;
  bool LSB2 = digitalRead(LS_back_2) == LOW;
  if (LSB1 && LSB2) {
    Serial.println("isReturned, drop ball, #MotorCommand 6 Needed.");
    return true;
  }
  else {return false;}
}

bool isOppoBack(int ls_isOppo) {
  // bool value reflects is opponent at back
  int lsState = digitalRead(ls_isOppo);
  if (lsState == LOW) {
    Serial.println("isOppoBack TRUE, #MotorCommand 2 Needed");
    return true;
  }
  else {return false;}
}

//_______________________________________________________
// digital compass configurations & functions
//_______________________________________________________

// const int DC1 = 50, DC2 = 51, DC3 = 52, DC4 = 53;
// int nowDirection(int DC1, int DC2, int DC3, int DC4) {
//   // digital compass gives current direction
//   bool E = digitalRead(DC1); Serial.println("E: " + String(E)); delay(500);
//   bool S = digitalRead(DC2); Serial.println("S: " + String(S)); delay(500);
//   bool W = digitalRead(DC3); Serial.println("W: " + String(W)); delay(500);
//   bool N = digitalRead(DC4); Serial.println("N: " + String(N)); delay(500);
//   int dir = 0;
//   if (E) {dir = 1; Serial.println("EAST");}
//   else if (S) {dir = 2; Serial.println("SOUTH");}
//   else if (W) {dir = 3; Serial.println("WEST");}
//   else if (N) {dir = 4; Serial.println("NORTH");}
//   return dir;
// }

//_______________________________________________________
// pin configuration setup
//_______________________________________________________

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // sharp distance sensor
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  // limit switch
  pinMode(LS1, INPUT_PULLUP);
  pinMode(LS2, INPUT_PULLUP);
  pinMode(LS3, INPUT_PULLUP);
  pinMode(LS4, INPUT_PULLUP);
  // line tracking sensor & digital compass
  for (int i = 0; i < 4; i++) {
    pinMode(lineTrackPin[i], INPUT);
  }
}

//_______________________________________________________
// main program execution
//_______________________________________________________

void loop() {
  // put your main code here, to run repeatedly:
  
  // debug IR
  // Serial.println("isObjectInfront sensor#1: " + String(isObjectInfront(IR1)));                            // tested & worked
  // Serial.println("isObjectInfront sensor#3: " + String(isObjectInfront(IR3)));                            // tested & worked
  // Serial.println("timeElapsed sensor#1: " + String(timeElapse(IR1)));                                     // tested & worked
  // Serial.println("timeElapsed sensor#3: " + String(timeElapse(IR3)));                                     // tested & worked
  // Serial.println("maxTimeElapsed sensor#1: " + String(maxTimeDuration(IR1, timeElapse(IR1), false)));     // tested & worked
  // Serial.println("maxTimeElapsed sensor#3: " + String(maxTimeDuration(IR3, timeElapse(IR3), false)));     // tested & worked
  // Serial.println(whatInfront(IR1, timeElapse(IR1)));                                                      // tested & worked
  // Serial.println(whatInfront(IR3, timeElapse(IR3)));                                                      // tested & worked
  // isOppo(IR1, IR3);                                                                                       // tested & worked
  // isBall(IR1, IR3);                                                                                       // tested & worked

  // debug LT
  // Serial.println(isDetect(lineTrackPin, 4));                                                              // tested & worked

  // debug DC
  // nowDirection(DC1, DC2, DC3, DC4);

  // debug LS
  isCapture(LS3);                                                                                         // tested & worked
  // isReturn(LS2, LS3);                                                                                     // tested & worked
  // isOppoBack(LS3);                                                                                        // tested & worked
}