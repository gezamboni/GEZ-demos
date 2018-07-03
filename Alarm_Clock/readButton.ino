// especifica os pinos dos sensores
const int buttonPin = 7;		// D7 para o botão
const int potPin = 0;			// A0 para o potenciometro

// inicia o setup
void setup(){
	Serial.begin(9600);		// inicia a comunicacao serial
	pinMode(buttonPin, INPUT);	// define o pino do botao para receber inputs
}

// inicia o loop
void loop(){
	int pot = analogRead(potPin);	// le o angulo girado do potenciometro
	int button = digitalRead(buttonPin);	// le o estado do botao

	// envia para o clock.py via comunicacao serial
	// as leituras feitas do potenciometro e do botao

	Serial.print("button = ");
	Serial.print(button);
	Serial.print(" pot = ");
	Serial.print(pot);
}
