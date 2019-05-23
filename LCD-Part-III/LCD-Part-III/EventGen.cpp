#include "EventGen.h"
#include <istream>

#define TECLA_S 83
#define TECLA_A 65
#define TECLA_R 82
#define TECLA_Q 81
#define TECLA_E 69 //reemplaza al mas
#define TECLA_W 87 //reemplaza al menos

#define MAX_DIF_TIMER 1.0
using namespace std;


EventGen::EventGen()
{
	evento = eventType::NO_EV;
	is_stopped = false;
	dif = 0.1;
}
eventType
EventGen::get_event()
{
	return evento;
}

bool
EventGen::stop()
{
	return is_stopped;
}

bool
EventGen::hay_evento(list<Tweet>& lista, Timer& timer)//, list<Tweet>::iterator itr)
{
	bool ret = true;
	
	int pkey = cin.get();

	if (pkey)
	{
		key = pkey;
		evento = eventType::KEYBOARD_EV;
	}

	else if (timer.dif_timer(dif)) //(si termino el timer)
	{
		evento=eventType::TIMER_EV;
	}
	/*
	else if()
	{
		evento=eventType::SOFTWARE_EV;
	}
	*/
	else
	{
		evento = eventType::NO_EV;
	}
	
	
	return ret;
}

void
EventGen::dispatcher()
{
	switch (evento)
	{
	case eventType::KEYBOARD_EV:
	{
		keyboard();
	}
	case eventType::TIMER_EV:
	{
		//timer();
	}
	case eventType::NO_EV:
	{

	}
	}
	
}

void 
EventGen::keyboard()
{
	if (key)
	{
		switch (key)
		{
		case TECLA_A:
		{	//anterior

		}
		case TECLA_S:
		{		//siguiente

		}
		case TECLA_R:
		{		//repite

		}
		case TECLA_E:
		{	//mas
			if (dif >= MAX_DIF_TIMER)
			{
				dif = MAX_DIF_TIMER;
			}
			dif += 0.05;
		}
		case TECLA_W:
		{	//menos
			if (dif <= 0.1)
			{
				dif = 0.1;
			}
			else
			{
				dif -= 0.05;
			}
		}
		case TECLA_Q:
		{		//chau
			is_stopped = true;
			break;
		}
		default:
			break;
		}
	}
}