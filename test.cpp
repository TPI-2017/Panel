#include "protocol/Message.h"
#include <iostream>


int mai()
{
	using namespace std;
	{
		Message m = Message::createSetTextRequest("123", 3.25, 1.50, "Texto");
		cout << m.blinkRate() << endl;
		cout << m.slideRate() << endl;
	}
	{
		Message m = Message::createGetTextResponse(3.25, 1.50, "Texto");
		cout << m.blinkRate() << endl;
		cout << m.slideRate() << endl;
	}
	return 0;
}
