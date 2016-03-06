//CPP:custom/cinta.cpp
#if !defined cinta_h
#define cinta_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "list"
#include "limits"
#include "string"
#include "cfloat"
#include "tuple"


class cinta: public Simulator { 
// Declare the state,

std::list<double> lista_distancias;

bool corre_cinta; //True = Corriendo | False = Detenida //

std::list<std::tuple<double,double>> numero_piezas_rechazadas;

std::list<std::tuple<double,double>> numero_piezas_totales;

double sigma;

// output variables

std::string salida;

double y;

// and parameters

double l;

double deltal;

double vc;

// Aux

std::tuple<double,double> initial_value (0,0);

double _sigma;

double T = 0;

public:
	cinta(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
