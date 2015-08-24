//CPP:src/cinta.cpp
#if !defined cinta_h
#define cinta_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "list"
#include "limits"
#include "string"
#include "cfloat"


class cinta: public Simulator { 
// Declare the state,

std::list<double> lista_distancias;

bool corre_cinta; //True = Corriendo | False = Detenida //

double numero_piezas_rechazadas;

double sigma;

double numero_piezas_totales;

// output variables

std::string salida;

double y;

// and parameters

double l;

double deltal;

double vc;

//Aux

bool salida_plot_rechazadas;

bool salida_plot_piezas;
 
double _sigma;







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
