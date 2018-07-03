#include "mraa.hpp"

#define GPIO_A 23
#define GPIO_B 24
#define GPIO_C 25
#define GPIO_D 26
#define GPIO_E 27
#define GPIO_F 28
#define GPIO_G 29
#define GPIO_H 30
#define GPIO_I 31
#define GPIO_J 32
#define GPIO_K 33
#define GPIO_L 34

#define SLEEP_TIME 1

using namespace std;

int main(int argc, char* argv[]){
	
	mraa::Gpio* gpio;

	gpio = new mraa::Gpio(GPIO_I);
	gpio->dir(mraa::DIR_OUT);

	while(true){
		gpio->write(0);
		sleep(SLEEP_TIME);
		gpio->write(1);
		sleep(SLEEP_TIME);
	}
	delete gpio;
	return 0;
}
