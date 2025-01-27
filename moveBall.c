bool adjustment = true;
void backToBox(){
	stopRobot();
	while (ballCaptured == true) {
		rotate(rotSpeed);
		int orn = readCompass();
		while (orn == 6) {
			moveBackward(50);
			int deviation = SensorValue(LineTracking1);
			if (deviation == 0) {
				moveForward(50, 1000);
				rotateWithTime(30, 500);
			}
			if (isReturn(LimitSwitchL, LimitSwitchR)) {
				stopRobot();
				gatePush();
				ballCaptured = false;
				ballDetected = false;
				adjustment = true;
				searchDirection = 50;
				moveForward(120, 3500);
				break;
			}
		}
	}
}
