/*
*example to control a button to control an LED
*/

int led_pin = 3;
int button_pin = A0;

void setup(){
	pinMode(led_pin, OUTPUT);
	pinMode(button_pin, INPUT);
}

bool last_button = false;
int led_state = 0;

void loop(){
	bool button = digitalRead(button_pin);
	if (last_button != button){
		if (button){
			led_state = (led_state +1) % 4;
			analogWrite(led_pin, led_state * 0x3f);
		}	
		delay(100);
	}
	last_button = button;
}

