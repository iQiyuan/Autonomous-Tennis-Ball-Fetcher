void moveBackward(int speed) {
    motor[vexBaseR] = speed;
    motor[vexBaseL] = speed;
}

void backWithTime(int speed, int msec) {
		motor[vexBaseR] = speed;
    motor[vexBaseL] = speed;
    wait1Msec(msec);
    motor[vexBaseR] = 0;
    motor[vexBaseL] = 0;
}

void forward(int speed) {
		motor[vexBaseR] = -speed;
    motor[vexBaseL] = -speed;
}

void moveForward(int speed, int msec) {
    motor[vexBaseR] = speed;
    motor[vexBaseL] = speed;
    wait1Msec(msec);
    motor[vexBaseR] = 0;
    motor[vexBaseL] = 0;
}

int rotSpeed = 40;
void rotate(int speed) {
    motor[vexBaseR] = speed;
    motor[vexBaseL] = -speed;
}

void rotateWithTime(int speed, int msec) {
		motor[vexBaseR] = speed;
    motor[vexBaseL] = -speed;
    wait1Msec(msec);
    motor[vexBaseR] = 0;
    motor[vexBaseL] = 0;
}

void stopRobot() {
    motor[vexBaseR] = 0;
    motor[vexBaseL] = 0;
}


void gateControl(int pos) {
	while (abs(SensorValue(gateEncoder)-(pos)) > 10) {
		int error = (pos) - SensorValue(gateEncoder);
		int speed = 1.25 * error;
		motor[vexGate] = speed;
	}
	motor[vexGate] = 0;
}

void gatePush() {
	motor[vexGate] = -127;
	wait1Msec(1000);
	gateControl(0);
}
