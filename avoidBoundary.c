int orn = readCompass();
void adjustDirection() {
		while ((!ballCaptured) && orn != 6) {
			rotate(rotSpeed);
			orn = readCompass();
	}
}

bool LineTrackTriggered = false;

void isDetect() {
	int BL = SensorValue(LineTracking1);
	int FL = SensorValue(LineTracking2);
	int BR = SensorValue(LineTracking3);
	int FR = SensorValue(LineTracking4);
	if (BL == 0) {
		LineTrackTriggered = true;
		stopRobot();
		moveForward(30, 800);
		adjustDirection();

		rotSpeed = -40;
		searchDirection = 50;
	}
	else if (FL == 0) {
		LineTrackTriggered = true;
		stopRobot();
		backWithTime(30, 800);
		adjustDirection();

		rotSpeed = -40;
		searchDirection = -50;
	}
	else if (BR == 0) {
		LineTrackTriggered = true;
		stopRobot();
		moveForward(50, 800);
		adjustDirection();

		rotSpeed = 40;
		searchDirection = 50;
	}
	else if (FR == 0) {
		LineTrackTriggered = true;
		stopRobot();
		backWithTime(30, 800);
		adjustDirection();

		rotSpeed = 40;
		searchDirection = -50;
	}
	if (SensorValue(LimitSwitchL) == 1 || SensorValue(LimitSwitchR) == 1) {
		LineTrackTriggered = true;
		ballCaptured = false;
		ballDetected = false;
		adjustment = true;
		searchDirection = 50;
		moveForward(50, 1300);
	}
}
