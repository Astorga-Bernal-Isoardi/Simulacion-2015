//CPP:src/sistemacontrol.cpp
#if !defined sistemacontrol_h
#define sistemacontrol_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "limits"
#include "string"
#include "cfloat"
#include "mesa.cpp"
#include "salida.cpp"


class sistemacontrol: public Simulator { 
// Declare the state,

Mesa mesa1;

Mesa mesa2;

//True = Corriendo | False = Detenida //
bool corre_cinta; 

double sigma;

// output variables

Salida salida;

std::string y;

std::string z;

int x;

// and parameters

double l; 

double deltal;

double vc;

int puerto_mesa1;

int puerto_mesa2;

int puerto_cinta;








































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
