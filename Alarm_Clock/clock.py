#!/usr/bin/env python
# import libraries
import serial, pyupm_i2clcd, time, mraa

"""
Para este programa foi usado
  - Placa Dragonboard 410c
  - Sensor mezzanine da 96boards
e devemos conectar os seguintes sensores
  - Potenciometro  -> A0 (pino analogico 0)
  - Botao - D7 (pino digital 7)
  - Touch botao -> GPIO 29
  - led -> gpio 27
  - lcd -> i2c0
sao usadas as bibliotecas 
  - serial
  - pyupm_i2clcd (high level)
  - time
  - mraa (low level)

este programa deve rodas usando
  - make upload reset_stty
  - sudo python clock.py (o sudo e necessario para rodar mraa)

para instalar a biblioteca libsoc GPIO seguir os pasos dados no:
  - https://pythonhosted.org/libsoc_zero/setup.html
  - mudar o PYTHONPATH para:
     export PYTHONPATH="$PYTHONPATH:/usr/local/lib/python3.4/site-packages
     export ARCH=arm64

Para trabalhar com gpio python deve rodar como sudo.
Isto significa que o super user deve poder acessar ao PYTHONATH.
para isso devo usar 
  - sudo visudo
  - acrescentar Defaults env_keep += "PYTHONPATH"

"""

# inicializa as devices utilizadas
ard = serial.Serial('/dev/tty96B0', 9600)
lcd = pyupm_i2clcd.Jhd1313m1(0, 0x3e, 0x62)

# inicializa o LED
led = mraa.Gpio(27)
led.dir(mraa.DIR_OUT)
led.write(0)

#inicializa o buzzer
#buzzer = mraa.Gpio(27)
#buzzer.dir(mraa.DIR_OUT)
#buzzer.write(0)

#inicializa o sensor de touch
touch = mraa.Gpio(29)
touch.dir(mraa.DIR_IN)

# formatar a hora para ser mostrada no visor LCD
time_format = '%H:%M:%S'

# definir uma classe para seguimento de quando o botao e apertado
class Button:
    previous  = None
    activated = None
    def init(self):
        self.previous = False
        self.activated = False

    def check(self, change):
        if (change and (not self.previous)):
            self.activated = True

        else:
            self.activated = False
        self.previous = change
        return self.activated

# Le os valores do arduino e retorna um dicionario guardando os valores
def readArduino():
    ardout = ard.readline()
    myList = ardout.split(", ")
    
    # inicializa um dicionario novo e guarda nele os pares chave/ valor lidos
    dataDict = {}

    # Para cada entrada em myList guarda-las como chave/ valor em dataDict
    for word in myList:
        key, equals, data = word.split(" ",2)
        data = data.replace("\r\n", "")
        dataDict[key] = int (data)
        
    return dataDict

# Converte um dicionario guardando a data em um string formatado com a data
def dictTimeToString(alarm):
    timeStruct = time.gmtime((3600*alarm["hours"]) + (60*alarm["minutes"]))
    timeString = time.strftime(time_format, timeStruct)
    return timeString

# Escreve duas linhas uma para a primeira linha do LCD e outra para a segunda linha
def writeToLCD(string1, string2):

    lcd.clear()
    lcd.setCursor(0,0)
    lcd.write(string1)
    lcd.setCursor(1,0)
    lcd.write(string2)
    lcd.setColor(255,180,180)


# Verifica se esta na hora de tocar o alarme
# retorna tambem a hora corrente como string
def checkAlarm(alarm,led,touchButton,touchValue):
    currentTimeString = time.strftime(time_format)
    alarm_string = dictTimeToString(alarm)
    
    if(currentTimeString == alarm_string):
        led.write(1)
        print ("ALARM!!!")
    elif(touchButton.check(touchValue)):
        led.write(0)
        print ("Alarm dismissed")
    return currentTimeString

# Verifica em qual estado esta o relogio e permite os features de cada estado
# Define a habilidade de setar o alarme
# Chama writeToLCD para escrever nele o estado atual
def showState(clock_state, data, alarm, currentTimeString):
    
    #print("clock state: %s" %clock_state)
    titles = {
        0: "Clock",
        1: "Alarm",
        2: "Setting Hours",
        3: "Setting Minutes"
    }

    if clock_state == 2:
        chunk_size = 1024/23
        hours = data["pot"]/chunk_size
        
        if hours > 23:
            hours = 23
        alarm["hours"] = hours
    if clock_state == 3:
        chunk_size = 1024/59
        minutes = data["pot"]/chunk_size
        
        if minutes > 59:
            minutes = 59
        alarm["minutes"] = minutes

    title = titles[clock_state]
    toWrite = None
    if (clock_state != 0):
        toWrite = dictTimeToString(alarm)
        
    else:
        toWrite = currentTimeString
        
    writeToLCD(title, toWrite)

if __name__ == '__main__':
    print("Welcome to the button reader!!!\n")

    # Inicializa as variaveis
    dotButton = Button()
    touchButton = Button()
    clock_state = 0
    alarm = {"hours":0, "minutes":0}

# Manter o codigo em um bloco try para poder sair corretamente quando for interrompido
try:
    # Verifica constantemente os estados e chamadas das funcoes
    while True:
        data = readArduino()
        buttonValue = data.get("button")
        touchValue = int(touch.read())
        if (dotButton.check(buttonValue)):
            clock_state += 1
            clock_state %= 4

        currentTimeString = checkAlarm(alarm, led, touchButton, touchValue)
        #print(currentTimeString)

        showState(clock_state, data, alarm, currentTimeString)
except KeyboardInterrupt:
    print("Saindo")


