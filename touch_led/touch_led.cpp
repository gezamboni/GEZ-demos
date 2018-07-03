#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "mraa.hpp"

bool running = true;
bool led_state = false;
int last_touch = 0;

void sig_handler(int signo){
	if (signo == SIGINT)
		running = false;
}

int main(){
	mraa::Gpio* touch_gpio = new mraa::Gpio(23);
	mraa::Gpio* led_gpio = new mraa::Gpio(27);
	mraa::Result response;
	int touch;

	signal(SIGINT, sig_handler);

	response = touch_gpio->dir(mraa::DIR_IN);
	if (response != mraa::SUCCESS)
		return 1;
	response = led_gpio->dir(mraa::DIR_OUT);
	if (response != mraa::SUCCESS)
		return 1;

	led_gpio->write(led_state);

	while(running){
		touch = touch_gpio->read();
		if (touch == 1 && last_touch ==0){
			led_state = !led_state;
			response = led_gpio->write(led_state);
			usleep(100000);
		}
		last_touch = touch;
	}
	response = led_gpio->write(false);
	delete led_gpio;
	delete touch_gpio;
	return response;
}

