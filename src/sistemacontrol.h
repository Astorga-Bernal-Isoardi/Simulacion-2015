//CPP:src/sistemacontrol.cpp
#if !defined sistemacontrol_h
#define sistemacontrol_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "limits"
#include "string"
#include "cfloat"


class sistemacontrol: public Simulator { 
// Declare the state,
double sigma;
// output variables

std::string salida; 

double y;

// and parameters

double l; 

double deltal;

double vc;

public:
	sistemacontrol(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
