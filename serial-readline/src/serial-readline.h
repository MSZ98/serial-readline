/*
    pcf8574.cpp
    Version 0.0.1
    Created 3.03.2022
    Author: MSZ98 (github.com/MSZ98)
    Copyright (C) 2022 MSZ98
    This file is part of the Arduino serial-readline.h library.
    The serial-readline.h library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.
    
    The Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU Lesser General Public License for more details.
    
    You should have received a copy of the GNU Lesser General Public
    License along with the GNU C Library; if not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SERIAL_READLINE_H
#define SERIAL_READLINE_H

#include <Arduino.h>
#include <string.h>

class LineQueue {

private:
	typedef struct {
		char *line;
		void *next;
	} Line;

	Line *first = NULL, *last = NULL;
	int _size = 0;
	
public:
	void add(char* line) {
		Line *l = new Line;
		l->line = line;
		l->next = NULL;
		if(last != NULL) last->next = l;
		last = l;
		if(first == NULL) first = last;
		_size++;
	}
	
	char* get() {
		Line *l = first;
		first = (Line*) l->next;
		if(first == NULL) last = NULL;
		char *line = l->line;
		delete l;
		_size--;
		return line;
	}

	boolean isEmpty() {
		return first == NULL;
	}

	int size() {return _size;}
	int firstLineLength() {return strlen(first->line);}
	
};


class SerialLineReader {

private:
	LineQueue queue;
	HardwareSerial *hs;
	void (*isr)(char*) = NULL;

	int buffer_len = 0;
	int buffer_limit;
	char *buffer;

public:
	SerialLineReader(HardwareSerial &hs, int bufsize, void (*isr)(char*)) {
		initialize(hs, bufsize, isr);
	}
	SerialLineReader(HardwareSerial &hs, void (*isr)(char*)) {
		initialize(hs, 100, isr);
	}
	SerialLineReader(HardwareSerial &hs, int bufsize) {
		initialize(hs, bufsize, NULL);
	}
	SerialLineReader(HardwareSerial &hs) {
		initialize(hs, 100, NULL);
	}
	~SerialLineReader() {
		delete buffer;
	}

	int available() {return queue.size();}
	int len() {return queue.firstLineLength();}
	
	void poll();
	void read(char*);

private:
	void initialize(HardwareSerial &hs, int bufsize, void (*isr)(char*)) {
		this->hs = &hs;
		this->isr = isr;
		buffer = new char[bufsize];
		buffer_limit = bufsize;
	}
};


#endif
