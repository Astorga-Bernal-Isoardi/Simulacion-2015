//CPP:proyecto-2015/generador.cpp
#if !defined generador_h
#define generador_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "C:/PowerDEVS/bin/gcc/include/stdlib.h"
#include "C:/PowerDEVS/bin/gcc/include/math.h"


class generador: public Simulator { 
// Declare the state,
double s;
// output variables
double y;
// and parameters
double sigma;

double lamb;

double u;

public:
	generador(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
