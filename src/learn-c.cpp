//============================================================================
// Name        : learn-c.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class hello {
	public:int a;
	public:char name[100] = {"hello"};

	public:int get_int (void) {
		a = 100;
		return a;
	}

	public:char *get_string (void) {
		return name;
	}
};

int main() {
	hello h;

	cout << "!!!Hello World!!!" << h.get_int() << endl << h.a << h.name << endl; // prints !!!Hello World!!!
	return 0;
}
