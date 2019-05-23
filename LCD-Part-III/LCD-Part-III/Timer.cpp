#include "Timer.h"

void
Timer::set_timer()
{
	cronos = clock(); //Clock actual
}

bool
Timer::dif_timer(double dif)
{
	if (cronos != 0)
	{
		clock_t clock_dif = clock() - cronos;
		double result = (double)clock_dif / CLOCKS_PER_SEC;
		return (result > dif); //Si es mayor esta todo peola
	}
	else
		return false; //No fue iniciado
}

void
Timer::reset()
{
	cronos = 0;
}