#include "cinta.h"
void cinta::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//     %Name% is the parameter name
//     %Type% is the parameter type

//Obtener Parametros
l = va_arg(parameters, double);
deltal = va_arg(parameters, double);
vc = va_arg(parameters, double);

//Inicilizar Variables del Estado
corre_cinta = true;//Cinta corriendo
numero_piezas_rechazadas = 0;
sigma = DBL_MAX;
numero_piezas_totales = 0;

//Inicializar Variables de Salida
salida = "NULL";
y = 0;

//Aux
salida_plot_rechazadas = false;
salida_plot_piezas = false;
}
double cinta::ta(double t) {
//This function returns a double.
return sigma;
}
void cinta::dint(double t) {
std::list<double>::iterator i = lista_distancias.begin();

if(salida_plot_rechazadas || salida_plot_piezas){
	if(salida_plot_rechazadas){
		salida_plot_rechazadas = false;
		sigma = DBL_MAX;
	}else{
		if ( *i == (l+deltal) ){ //Salida por LEAVE
			lista_distancias.pop_front();
			i = lista_distancias.begin();
			sigma = (l-*i)/vc;
		}else{
			sigma = _sigma;	//Salida por ARRIVE
		}
		salida_plot_piezas = false;
	}
}else{
	sigma = deltal/vc;
}
}
void cinta::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
std::string valor = *(std::string*)(x.value);
std::list<double>::iterator i = lista_distancias.begin();

if(corre_cinta){
		//Cinta Corriendo
		if(valor == "ARRIVE"){
			numero_piezas_totales++;
			if(!lista_distancias.empty()){
				i = lista_distancias.begin();
				_sigma = (l-*i)/vc;
				while(i != lista_distancias.end()){
					*i += (vc * (double) e);
					i++;
				}
			}else{
				_sigma = l/vc;
			}
			lista_distancias.push_back(0);
			salida_plot_piezas = true;
			sigma = 0;
		}
		if(valor == "START"){
			corre_cinta = true;
			i = lista_distancias.begin();
			while(i != lista_distancias.end()){
				*i += (vc * (double) e);
				i++;
			}
			sigma -= (double) e;
		}
		if(valor == "STOP"){
			corre_cinta = false;
			i = lista_distancias.begin();
			while(i != lista_distancias.end()){
				*i += (vc * (double) e);
				i++;
			}
			sigma = DBL_MAX;
		}
}else{
	if(valor == "ARRIVE"){
		numero_piezas_totales++;
		numero_piezas_rechazadas++;
		salida_plot_rechazadas = true;
		sigma = 0;
	}
	if(valor == "START"){
		corre_cinta = true;
		sigma = (l-*i)/vc;
	}
	if(valor == "STOP"){
		sigma = DBL_MAX;
	}	
}
}
Event cinta::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)

std::list<double>::iterator i = lista_distancias.begin();

if( salida_plot_rechazadas || salida_plot_piezas ){
	if( salida_plot_rechazadas ){
		//Salida al plot de numero de piezas rechazada.	
		y = (numero_piezas_rechazadas/numero_piezas_totales) * 100;
		return Event(&y,1);	
	}else{
		//Salida al plot de numero de piezas en cinta
		y = lista_distancias.size();
		return Event(&y,2);
	}
}else{
	if( *i < l ){
		*i = l;
		salida = "DETECT";
	}else{
		*i = l+deltal;
		salida = "LEAVE";
		salida_plot_piezas = true;
	}
	return Event(&salida,0);
}
}
void cinta::exit() {
//Code executed at the end of the simulation.

}
