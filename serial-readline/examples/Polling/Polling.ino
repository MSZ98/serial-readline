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
