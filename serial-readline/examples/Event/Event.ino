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
