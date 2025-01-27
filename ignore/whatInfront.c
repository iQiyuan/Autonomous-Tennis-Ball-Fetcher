unsigned long startTime[4] = {0,0,0,0};
unsigned long dynamicDuration[4] = {0,0,0,0};
unsigned long timeElapse(int sensorPin) {
  int sensorIndex = indexing(sensorPin);
  if (isObjectInfront(sensorPin)) {
    if (startTime[sensorIndex] == 0) {
      startTime[sensorIndex] = time1[T1];
    } else {
      dynamicDuration[sensorIndex] = time1[T1] - startTime[sensorIndex];
    }
  } else {
    startTime[sensorIndex] = 0;
    dynamicDuration[sensorIndex] = 0;
  }
  return dynamicDuration[sensorIndex];
}



unsigned long max[4] = {0,0,0,0};
unsigned long maxTimeDuration(int sensorPin, unsigned long timeElapsed, bool reset) {
  int sensorIndex = indexing(sensorPin);
  if (timeElapsed > max[sensorIndex]) max[sensorIndex] = timeElapsed;
  if (reset) max[sensorIndex] = 0;
  return max[sensorIndex];
}



unsigned long lowerLimit = 1000;
unsigned long middleLimit = 2000;
unsigned long upperLimit = 3000;
unsigned long maxTime[4] = {0,0,0,0};
int result = 0;
int whatInfront(int sensorPin) {
  int sensorIndex = indexing(sensorPin);
  unsigned long timeElapsed = timeElapse(sensorPin);
  result = 0;
  if (isObjectInfront(sensorPin)) {
    maxTime[sensorIndex] = maxTimeDuration(sensorPin, timeElapsed, false);
  } else {
    maxTimeDuration(sensorPin, timeElapsed, true);
    if (maxTime[sensorIndex] >= lowerLimit && maxTime[sensorIndex] <= middleLimit) {
      maxTime[sensorIndex] = 0;
      result = 1;
      wait1Msec(10000);
    } else if (maxTime[sensorIndex] >= middleLimit && maxTime[sensorIndex] <= upperLimit) {
      maxTime[sensorIndex] = 0;
      result = 2;
      wait1Msec(5000);
    } else {
      maxTime[sensorIndex] = 0;
      result = 3;
    }
  }
  return result;
}
