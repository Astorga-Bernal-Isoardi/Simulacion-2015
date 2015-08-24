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

numero_piezas_rechazadas = 0;

INFINITO = DBL_MAX;

sigma = INFINITO;

l = va_arg(parameters, double);
deltal = va_arg(parameters, double);
vc = va_arg(parameters, double);

salida = "NULL";
y = 0;

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
if(_estado_cinta == DETENIDA){
	sigma = INFINITO;
}else{
	sigma = _sigma;
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
		numero_piezas_rechazadas++;
		sigma = 0;
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
			//salida con lista_distancias.size();
			_sigma = sigma - ( (double) e );
			sigma = 0;
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
	salida = "DETECT";
	return Event(&salida,0);
}
if (*it == (l+deltal)){
	//salida con lista_distancias.size();
	salida = "LEAVE";
	return Event(&salida,0);
}
if(_estado_cinta == DETENIDA){
	y = numero_piezas_rechazadas;
	//Salida al plot de numero de piezas rechazada.
	return Event(&y,1);
}else{
	y = lista_distancias.size();
	//Salida al plot de numero de piezas en cinta.
	return Event(&y,2);
}
}
void cinta::exit() {
//Code executed at the end of the simulation.

}
