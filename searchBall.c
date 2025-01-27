//___________________________________________________________________________________________________
bool ballDetected = false;
bool ballCaptured = false;
int searchDirection = 50;

void searchWhateverInfront_version2() {
	rotate(rotSpeed);
	clearTimer(T1);
	while (time1[T1] < 5000) {
		if (isObjectInfront(IR3, 500)) {
			if (!(isObjectInfront(IR1, 500))) {
				stopRobot();
				if (rotSpeed > 0) {
					rotateWithTime(-rotSpeed, 350);
				}
				else if (rotSpeed < 0) {
					rotateWithTime(rotSpeed, 350);
				}
				forward(30);
				clearTimer(T1);
				while (time1[T1] < 3000) {
					if (isBall(IR2)) {
						gateControl(-85);
						break;
					}
				}
				if (isCapture(IR4)) {
					ballCaptured = true;
					stopRobot();
				}
				break;
			}
			else {
				backWithTime(25, 500);
			}
		}
	}
	int orn = readCompass();
	while ((!ballCaptured) && orn != 6) {
		rotate(rotSpeed);
		orn = readCompass();
	}
	if (!ballCaptured) {
		moveForward(searchDirection, 800);
	}
}
