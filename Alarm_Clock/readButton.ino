// especifica os pinos dos sensores
const int buttonPin = 7;		// D7 para o botão
const int potPin = 0;			// A0 para o potenciometro
//const int touchPin = 5;			// D5 para o touch button
//const int ledPin = 3;			// D3 para o led

// inicia o setup

void setup(){
	Serial.begin(9600);	   // inicia a comunicacao serial
	pinMode(buttonPin, INPUT); // define o pino do botao para inputs
	pinMode(potPin, INPUT);	   // define o pino do potenciometro para inputs
	//pinMode(touchPin, INPUT);  // define o pino do touch para input
	//pinMode(ledPin, OUTPUT);   // define o pino do led para dar output
}


// inicia o loop
void loop(){
	int pot = analogRead(potPin);	// le o angulo girado do potenciometro
	int button = digitalRead(buttonPin);	// le o estado do botao
	//int touch = digitalRead(touchPin);    // le o estado do touch

	// envia para o clock.py via comunicacao serial
	// as leituras feitas do potenciometro e do botao

	Serial.print("button = ");
	Serial.print(button);
	Serial.print("pot = ");
	Serial.print(pot);
	//Serial.print("touch = ");
	//Serial.print(touch);
	
}
