//CPP:src/mesamovil.cpp
#if !defined mesamovil_h
#define mesamovil_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class mesamovil: public Simulator { 
// Declare the state,
// output variables
// and parameters

public:
	mesamovil(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
