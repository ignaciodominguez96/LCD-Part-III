#pragma once
#include <ctime>
#include <cstdbool>

//La clase Timer sirve para calcular la diferencia de tiempo
//  entre el momento en que se setea hasta que se calcula la
//  diferencia. Su gran ventaja es que es exactamente como
//  un cronometro de la vida real y es de facil uso.

class Timer
{
public:
	Timer() {};
	~Timer() {};
	void set_timer(); //Inicia el timer
	bool dif_timer(double dif); //Chequea la deferencia de tiempo
	void reset(); //Setea en 0 el timer
private:
	clock_t cronos;
};

