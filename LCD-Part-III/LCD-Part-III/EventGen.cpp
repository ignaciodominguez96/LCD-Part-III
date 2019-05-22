#include "EventGen.h"
#include <istream>

using namespace std;

EventGen::EventGen()
{
	evento = eventType::NO_EV;
}
eventType
EventGen::get_event()
{
	return evento;
}

bool
EventGen::hay_evento(list<Tweet>& lista)
{
	bool ret = true;

	int pkey = cin.get();
	if (pkey)
	{
		key = pkey;
		evento = eventType::KEYBOARD_EV;
	}

	//else if (funcion_timer) (si termino el timer)
	//evento=timer;
	
	
	return ret;
}

void
EventGen::dispatcher()
{
	/*
	if(evento==KEYBOARD)
	{
		keyboard(key);
	}
	else if(Timer)
	{
		timer();
	}
	*/
}

