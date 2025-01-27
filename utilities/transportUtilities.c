bool isCapture(int sensorPin) {
  int rawValue = SensorValue[sensorPin];
  if (rawValue > 1000) {
    return true;
  }
  else {
    return false;
  }
}

//___________________________________________________________________________________________________

bool isBall(int sensorPin) {
	int rawValue = SensorValue[sensorPin];
  if (rawValue > 2000) {
    return true;
  }
  else {
    return false;
  }
}

//___________________________________________________________________________________________________

bool isReturn(int LS_back_1, int LS_back_2) {
  bool LSB1 = SensorValue[LS_back_1] == 1;
  bool LSB2 = SensorValue[LS_back_2] == 1;
  if (LSB1 && LSB2) {
    return true;
  }
  else {
    return false;
  }
}

//___________________________________________________________________________________________________

int compass_status;
int readCompass()
{
    int pin1 = SensorValue(Compass1);
    int pin2 = SensorValue(Compass2);
    int pin3 = SensorValue(Compass3);
    int pin4 = SensorValue(Compass4);
    int combination = pin1 * 1000 + pin2 * 100 + pin3 * 10 + pin4;
    switch (combination)
    {
    case 1110: //NORTH
    		compass_status = 0;
        break;
    case 1100: //NORTH_EAST
        compass_status = 1;
        break;
    case 1101: //EAST
        compass_status = 2;
        break;
    case 1001: //SOUTH_EAST
        compass_status = 3;
        break;
    case 1011: //SOUTH
        compass_status = 4;
        break;
    case 0011: //SOUTH_WEST
        compass_status = 5;
        break;
    case 0111: //WEST
        compass_status = 6;
        break;
    case 0110: //NORTH_WEST
        compass_status = 7;
        break;
    default: //INVALID_COMBINATION
        compass_status = 8;
        break;
    }
    return compass_status;
}
