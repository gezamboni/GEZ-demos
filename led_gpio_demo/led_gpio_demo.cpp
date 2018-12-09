#include <signal.h>
#include <unistd.h>
#include "mraa.hpp"

#define SLEEP_TIME 1

bool running = true;

using namespace std;

void sig_handler(int signo){
	if (signo==SIGINT){
		running = false;
	}
}

int main(int argc, char* argv[]){
	
	mraa::Gpio* gpio = new mraa::Gpio(27);
	gpio->dir(mraa::DIR_OUT);

	while(running){
		gpio->write(0);
		sleep(SLEEP_TIME);
		gpio->write(1);
		sleep(SLEEP_TIME);
	}
	delete gpio;
	return 0;
}
