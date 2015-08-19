//CPP:proyecto-2015/cinta.cpp
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

enum Estado_Cinta {CORRIENDO , DETENIDA};

Estado_Cinta _estado_cinta;

double piezas_rechazadas;

// output variables
enum Salida {LEAVE , DETECT};

Salida y;

double salida_piezas_cinta;

double salida_piezas_rechazadas;

// and parameters
double sigma;

double l;

double deltal;

double vc;

//std::numeric_limits<double>::max();

double INFINITO;
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
