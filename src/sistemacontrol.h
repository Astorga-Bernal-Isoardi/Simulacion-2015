//CPP:src/sistemacontrol.cpp
#if !defined sistemacontrol_h
#define sistemacontrol_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class sistemacontrol: public Simulator { 
// Declare the state,
// output variables
// and parameters

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
