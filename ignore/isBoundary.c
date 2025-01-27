bool reflectiveDetect(tSensors sensorPin) {
  // boolean value indicate detection
  int rawValue = SensorValue[sensorPin];
  int threshold = 512;
  return (rawValue <= threshold);
}

//___________________________________________________________________________________________________

tSensors LTPinList[4] = {LineTrack1,LineTrack2,LineTrack3,LineTrack4};
int isDetect() {
  bool detected = false;
  int result = 0;
  for (int i = 0; i < 4; i++) {
    int sensorPin = LTPinList[i];
    if (reflectiveDetect(sensorPin)) {
      detected = true;
      if (sensorPin == LTPinList[0]) {result = 4;}
      else if (sensorPin == LTPinList[1]) {result = 5;}
      else if (sensorPin == LTPinList[2]) {result = 6;}
      else if (sensorPin == LTPinList[3]) {result = 7;}
    }
  }
  if (detected) return result;
  else {
    return 3;
  }
}
