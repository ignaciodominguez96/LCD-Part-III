#include <iostream>
#include "Tweet.h"
#include <list>

enum class eventType{NO_EV, KEYBOARD_EV, TIMER_EV, SOFTWARE_EV};

class EventGen
{
public:
	EventGen();
	eventType get_event(void);
	bool hay_evento(list<Tweet>& lista);
	void dispatcher(void);

private:
	eventType evento;
	int key;

};