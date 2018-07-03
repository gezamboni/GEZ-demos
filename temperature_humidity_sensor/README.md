/*
Para rodar este programa devo ter:

1. Packages up tp date
	$sudo apt-get update
	$ sudo apt-get dist-upgrade -u

2. Extra tool packages
	$ sudo apt-get install arduino.ml arduino git build-essential autoconf libtool swig3.0 python-dev cmake pkg-config libpcre3-dev
	$sudo apt-get install curl
	curl -sl https://deb.nodesource.com/setup_8_x | sudo bash -
	sudo apt-get install nodejs

3. Install I/O libraries
	$ sudo apt-get install libsoc-dev
	$ sudo apt-get install libmraa-dev
	$ sudo apt-get install libupm-dev
	$ sudo apt-get install python-upm

4. Configure software
	$ sudo adduser linaro i2c
	$ git clone https://github.com/96boards/96boards-tools
	$ sudo cp 96boards-tools/70-96boards-common.rules /etc/udev/rules.d/
	$ cat | sudo tee /etc/profile.d/96boards-sensors.sh << EOF
	export JAVA_TOOL_OPTIONS="-Dgnu.io.rxtx.SerialPorts=/dev/tty96B0"
	export MONITOR_PORT=/dev/tty96B0
	export PYTHONPATH="$PYTHONPATH:/usr/local/lib/python2.7/site-packages"
	EOF

	$ sudo cp /etc/profile.d/96boards-sensors.sh /etc/X11/Xsession.d/96boardssensors
	$ sudo reboot

5. Hardware
	LCD em I2C0
	sensor em A0

6. Criar um arquivo Makefile com:
	include /usr/share/arduino/Arduino.mk
	run: upload
		python humid_temp.py

7. Biblioteca especial
	Copiar para dentro de diretorio a lib DHT

	$ git clone https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor.git
	$ cd Grove_Temperature_And_Humidity_Sensor/
	$ mv DHT.* ../
	$ cd ..

8. Run Demo

	$ PYTHONPATH=$PYTHONPATH:/usr/lib/aarch64-linux-gnu/python2.7/site-packages
	$ make run

*/



