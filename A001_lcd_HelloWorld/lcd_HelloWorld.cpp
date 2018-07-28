
/*
Este e um arquivo de Cpp modificado e baseado no
https://githib.com/96boards/Sensor_Mezzanine_Getting_Started/blob/master/README.md

conectar o lcd no I2C0


*/

#include <Arduino.h>

#include <string.h>              // inclui a biblioteca de strings
#include "/usr/include/upm/jhd1313m1a.hpp"   // inclui a biblioteca de utm para o lcd

// define as constates que usa no programa

#define I2C_BUS 0              // constante I2C_BUS do lcd
#define RGB_WHT 0xff, 0xff, 0xff   // constante RGB_WHT como branco
#define RGB_RED 0xff, 0x00, 0x00   // constante RGB_RED como vermelho
#define RGB_GRN 0x00, 0xff, 0x00   // constante RGB_GRN como verde
#define RGB_BLU 0x00, 0x00, 0xff   // constante RGB_BLU como azul
#define SLEEP_TIME 2

// Para usar os recursos de entrada e saida da biblioteca iostream em C++ 
// devemos incluir o comando    using namespace std
// que serve para definir um espaço de nomes que permite definir estruturas, classes etc etc
//  que estarão vinculadas a esse namespace e evita duplicidade
//  namespace std então é a biblioteca padrão

using namespace std;
upm::Jhd1313m1* lcd;   // estamos dando o scope = upm  e class = Jhd1313m1 com pointer
                       // escreve um string no lcd

void display(string str1, string str2, int red, int green, int blue){
	lcd->clear();    // lcd aponta para o metodo clear que limpa o display de caracteres
	lcd->setColor(red,green,blue);   //define a cor do fundo
	lcd->setCursor(0,0);  // primeira linha
	lcd->write(str1);
	lcd->setCursor(1,2);  // segunda linha
	lcd->write(str2);
	sleep(SLEEP_TIME);
}

int main(int argc, char* argv[]){
  init();
	string str1 = "96Boards!";
	string str2 = "Grove Sensors!";
	string str3 = "Linaro!";

	lcd = new upm::Jhd1313m1(I2C_BUS, 0x3e, 0x62);

	if ((argc >= 2) && (argv[1] != NULL))
		str1 = argv[1];
	if ((argc >= 3) && (argv[2] != NULL))
		str2 = argv[2];
	if ((argc >=4 ) && (argv[3] != NULL))
		str3 = argv[3];

	while (true){
		display(str1, "Red", RGB_RED);
		display(str2, "Green", RGB_GRN);
		display(str3, "Blue", RGB_BLU);
	}
	delete lcd;
	return 0;
}


