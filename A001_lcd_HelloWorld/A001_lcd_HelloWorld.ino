extern "C" {
  #include <string>              // inclui a biblioteca de strings
#include "upm/jhd1313m1.hpp"   // inclui a biblioteca de utm para o lcd

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

}
