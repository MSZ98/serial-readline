# serial-readline
Arduino library for buffered serial line reading

## 1. Supported boards
Should work on most of the boards, tested on UNO and ESP32DevKitV1

## 2. Usage
### 2.1 Example - event based use of SerialLineReader
```
#include <serial-readline.h>

void received(char*);
SerialLineReader reader(Serial, received);

void setup() {
	Serial.begin(115200);
}

void received(char *line) {
	Serial.println(line);
}

void loop() {
	reader.poll();
}
```

### 2.2 Example - polling based use of SerialLineReader
```
#include <serial-readline.h>

SerialLineReader reader(Serial);

void setup() {
	Serial.begin(115200);
}

void loop() {
	reader.poll();
	if(reader.available()) {
		char text[reader.len()];
		reader.read(text);
		Serial.println(text);
	}
}
```

### 2.3 Constructors

SerialLineReader(Serial)</br>
SerialLineReader(Serial, isr)</br>
SerialLineReader(Serial, bufsize)</br>
SerialLineReader(Serial, bufsize, isr)</br>

HardwareSerial is passed by reference. Default bufsize is 100. ISR is void function with one argument of type char*. It's called when line is ready to be read.

## 3.About
This library allows microcontroller to achieve better performance with Serial communication based on sending lines (terminated with \n). In Arduino polling is a must, because you don't have core support for idle detection. Polling is problematic, because if you poll too fast, data comes in separate pieces and figuring out when transfer is complete is kind of tricky. This lib extends your arsenal with SerialLineReader, which have poll() method used for polling. It receives data in separate pieces, writes to buffer, slices into lines and puts into queue, from which you can take those lines nice and easy using read() method. You can also specify function which will be called, when line is ready to be received.
 
 
 
 
 
 
 
 
