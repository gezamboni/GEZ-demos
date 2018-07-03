#include <string.h>
#include <stdio.h>
#include "upm/jhd1313m1.hpp"
#include <signal.h>
#include "mraa.hpp"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

//#include <serial.h>

#define I2C_BUS 0
#define RGB_BLUE 0x00,0x00,0xff
#define SLEEP_TIME 1

bool running = true;
bool led_state = false;
int last_touch = 0;


using namespace std;
upm::Jhd1313m1* lcd;


/* Handler para ler o sinal do software interrupt
   Esta funcao aceita um integer de sinal correspondente ao sinal que deve ser tratado 
   */
void sig_handler(int signo){
	if (signo == SIGINT){
	running = false;
	}
}

void display( string str1, string str2, int red, int green, int blue){
	lcd->clear();
	lcd->setColor(red, green, blue);
	lcd->setCursor(0,0);
	lcd->write(str1);
	lcd->setCursor(1,0);
	lcd->write(str2);
	sleep(SLEEP_TIME);
}

int main(){
	lcd = new upm::Jhd1313m1(I2C_BUS, 0x3e, 0x62);

	// inicializacao do led e do touch
	mraa::Gpio* led_gpio = new mraa::Gpio(27);
	mraa::Gpio* touch_gpio = new mraa::Gpio(29);
	mraa::Result response;
	int touch;

	signal(SIGINT, sig_handler);

	// definir direcao de cada sensor
	response = touch_gpio->dir(mraa::DIR_IN);
	if (response != mraa::SUCCESS)
		return 1;
	response = led_gpio->dir(mraa::DIR_OUT);
	if (response != mraa::SUCCESS)
		return 1;

	led_gpio->write(led_state);

	while(running){
		display("Gustavo Zamboni", "Azul", RGB_BLUE);
		touch = touch_gpio->read();
		if (touch == 1 && last_touch == 0){
			led_state = ! led_state;
			response = led_gpio-> write(led_state);
			//usleep(100000);
		}
		last_touch = touch;
	}

	response = led_gpio->write(led_state);
	delete lcd;
	delete led_gpio;
	delete touch_gpio;
	return response;

}
