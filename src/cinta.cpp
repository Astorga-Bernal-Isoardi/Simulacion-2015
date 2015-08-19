#include "cinta.h"
void cinta::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
// %Name% is the parameter name
//	%Type% is the parameter type

_estado_cinta = CORRIENDO;

piezas_rechazadas = 0;

salida_piezas_cinta = 0;

salida_piezas_rechazadas = 0;

INFINITO = DBL_MAX;

sigma = INFINITO;

l = va_arg(parameters, double);

deltal = va_arg(parameters, double);

vc = va_arg(parameters, double);
}
double cinta::ta(double t) {
//This function returns a double.
return sigma;
}
void cinta::dint(double t) {
std::list<double>::iterator it = lista_distancias.begin();
if (*it == l){
	sigma = deltal/vc;
}
if (*it == (l+deltal)){
	lista_distancias.pop_front();
	it = lista_distancias.begin();
	sigma = (l-*it)/vc;
}

}
void cinta::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
std::string valor = *(std::string*)(x.value);
std::list<double>::iterator it = lista_distancias.begin();

if(_estado_cinta == DETENIDA){
	
	if(valor == "ARRIVE"){
		piezas_rechazadas++;
		sigma = INFINITO;
	}
	if(valor == "START"){
		_estado_cinta = CORRIENDO;
		sigma = (l-*it)/vc;
	}
	if(valor == "STOP"){
		sigma = INFINITO;
	}
}else{
	if(_estado_cinta == CORRIENDO){
		
		if(valor == "ARRIVE"){
			it = lista_distancias.begin();
			while(it != lista_distancias.end()){
				*it += (vc * (double) e);
				it++;
			}
			lista_distancias.push_back(0);
			sigma -= (double) e;
		}
		if(valor == "START"){
			_estado_cinta = CORRIENDO;
			it = lista_distancias.begin();
			while(it != lista_distancias.end()){
				*it += (vc * (double) e);
				it++;
			}
			sigma -= (double) e;
		}
		if(valor == "STOP"){
			_estado_cinta = DETENIDA;
			it = lista_distancias.begin();
			while(it != lista_distancias.end()){
				*it += (vc * (double) e);
				it++;
			}
			sigma = INFINITO;
		}
	}
}
}
Event cinta::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)

std::list<double>::iterator it = lista_distancias.begin();
if (*it == l){
	y = DETECT;
}
if (*it == (l+deltal)){
	y = LEAVE;
}

return Event(&y,0);
}
void cinta::exit() {
//Code executed at the end of the simulation.

}
