int indexing(tSensors sensorPin) {
	// Function to index sensor pins
  int sensorIndex;
  if (sensorPin == IR1) sensorIndex = 0;
  else if (sensorPin == IR2) sensorIndex = 1;
  else if (sensorPin == IR3) sensorIndex = 2;
  else if (sensorPin == IR4) sensorIndex = 3;
  return sensorIndex;
}

//___________________________________________________________________________________________________

int lastValue[4] = {0,0,0,0};
bool isObjectInfront(int sensorPin, int Threshold) {
	// Function to check if an object is in front
  int sensorIndex = indexing(sensorPin);
  int rawValue = SensorValue[sensorPin];
  bool exist = (lastValue[sensorIndex] >= Threshold && rawValue >= Threshold);
  lastValue[sensorIndex] = rawValue;
  return exist;
}

//___________________________________________________________________________________________________
