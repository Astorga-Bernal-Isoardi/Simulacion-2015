//CPP:src/generador.cpp
#if !defined generador_h
#define generador_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "string"
#include "cmath"


class generador: public Simulator { 
// Declare the state,

double s;

// output variables

std::string y;

// and parameters

double sigma;

double lambda_distribucion;

double l;

double deltal;

double vc;

//Aux

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
