# **serial-readline**
Arduino library for buffered serial line reading

## Supported boards
Should work on most of the boards, tested on UNO and ESP32DevKitV1

## Usage
### Example event based use of SerialLineReader
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
	reader.tick();
}
```

### Example polling based use of SerialLineReader
```
#include <serial-readline.h>

SerialLineReader reader(Serial, received);

void setup() {
	Serial.begin(115200);
}

void loop() {
	reader.tick();
	if(reader.available()) {
		char text[reader.len()];
		reader.read(text);
		Serial.println(text);
	}
}
```

### Constructors

SerialLineReader(Serial)
SerialLineReader(Serial, isr)
SerialLineReader(Serial, bufsize)
SerialLineReader(Serial, bufsize, isr)

Default bufsize is 100. ISR is void function with one argument of type char*. It's called when line is ready to be read.

## About
This library allows microcontroller to achieve better performance with Serial communication based on sending lines (terminated with \n). In Arduino polling is a must, because you don't have core support for idle detection. Polling is problematic, because if you poll to fast, data comes in separate pieces and figuring out when transfer is complete is kind of tricky. This lib extends you arsenal with SerialLineReader, which have tick() method used for polling. It receives data in separate pieces, writes to buffer, slices into lines and puts into queue, from which you can take those lines nice and easy using read() method. You can also specify function which will be called, when line is ready to be received.
 
 
 
 
 
 
 
 
