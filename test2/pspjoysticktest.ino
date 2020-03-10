/*
7 2 1
5 4 3
6

7       8
11
12 13 14

1
4  2  3
*/
#include "HID-Project.h"
#include <Keypad.h>
const byte ROWS = 2; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
	{ '0','1','2','3' },
	{ '4','5','6','7' }
};
byte rowPins[ROWS] = { 8,9 }; //connect to the row pinouts of the kpd
byte colPins[COLS] = { 2,3,4,5 }; //connect to the column pinouts of the kpd
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
unsigned long startTime;
String msg;
int sensorValueX = 0;
int sensorValueY = 0;
int c1 = 0;
void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);
	startTime = millis();
	msg = "";
	Gamepad.begin();
}

void loop() {
	// put your main code here, to run repeatedly:
	sensorValueX = analogRead(A3);
	sensorValueY = analogRead(A2);
	if ((millis() - startTime)>10) {
		Gamepad.xAxis(sensorValueX);
		Gamepad.yAxis(sensorValueY);
		startTime = millis();
		if (c1 == 1)
		{
			Gamepad.press(8);
			Gamepad.press(1);
			delay(20);
			Gamepad.write();
			Gamepad.release(8);
			Gamepad.release(1);
			delay(20);
			Gamepad.write();
		}
		Gamepad.write();
	}
	if (kpd.getKeys())
	{
		for (int i = 0; i<LIST_MAX; i++)   // Scan the whole key list.
		{
			if (kpd.key[i].stateChanged)   // Only find keys that have changed state.
			{
				switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
				case PRESSED:
					msg = " PRESSED.";
					if (kpd.key[i].kchar == '7')
						Gamepad.press(7);
					else if (kpd.key[i].kchar == '6')
						Gamepad.press(8);
					else if (kpd.key[i].kchar == '2')
					{
						Gamepad.press(11);
						Gamepad.press(3);
					}
					else if (kpd.key[i].kchar == '1')
					{
						Gamepad.press(8);
						Gamepad.press(1);
						delay(20);
						Gamepad.write();
						Gamepad.release(8);
						Gamepad.release(1);
						delay(20);
						Gamepad.write();
						c1 = 1;
					}
					else if (kpd.key[i].kchar == '3')
						Gamepad.press(3);
					else if (kpd.key[i].kchar == '4')
						Gamepad.press(1);
					else if (kpd.key[i].kchar == '5')
						Gamepad.press(4);
					Gamepad.write();
					break;
				case HOLD:
					msg = " HOLD.";

					break;
				case RELEASED:
					if (kpd.key[i].kchar == '7')
						Gamepad.release(7);
					else if (kpd.key[i].kchar == '6')
						Gamepad.release(8);
					else if (kpd.key[i].kchar == '2')
					{
						Gamepad.release(11);
						Gamepad.release(3);
					}
					else if (kpd.key[i].kchar == '1')
					{
						Gamepad.release(11);
						Gamepad.release(3);
						Gamepad.write();
						c1 = 0;
					}

					else if (kpd.key[i].kchar == '3')
						Gamepad.release(3);
					else if (kpd.key[i].kchar == '4')
						Gamepad.release(1);
					else if (kpd.key[i].kchar == '5')
						Gamepad.release(4);
					Gamepad.write();
					msg = " RELEASED.";

					break;
				case IDLE:
					msg = " IDLE.";
				}
				Serial.print("Key ");
				Serial.print(kpd.key[i].kchar);
				Serial.println(msg);
			}
		}
	}
}
