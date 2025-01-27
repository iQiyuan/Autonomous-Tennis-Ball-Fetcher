void isOppoInfront(int RT, int LT) {
  if (isObjectInfront(RT) || isObjectInfront(LT)) {
    writeDebugStream("isOppo triggered\n");
  } else {
    writeDebugStream("Now proceed to isBall\n");
  }
}

bool isOppoBack(int ls_isOppo) {
  int lsState = SensorValue[ls_isOppo];
  if (lsState == 0) {
    writeDebugStream("isOppoBack TRUE, #MotorCommand 2 Needed\n");
    return true;
  }
  else {
    return false;
  }
}
