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
numero_piezas_rechazadas.push_back(initial_value);
numero_piezas_totales.push_back(initial_value);
sigma = DBL_MAX;

//Inicializar Variables de Salida
salida = "NULL";
y = 0;
t = 0;
}
double cinta::ta(double t) {
//This function returns a double.
return sigma;
}
void cinta::dint(double t) {
std::list<double>::iterator i = lista_distancias.begin();
std::list<std::tuple<double,double>>::iterator j = numero_piezas_totales.begin();

if ( *i == l ) { //Salida por ARRIVE
	sigma = (l-*i)/vc;
}
if ( *i == (l+deltal) ){ //Salida por LEAVE
	lista_distancias.pop_front();

   // En caso de que sea por referencia
	// Usar copy
  	std::tuple<double,double> new_value (initial_value);
	v = std::get<0>(*j);
	std::get<0>(new_value) = v-1;
	std::get<1>(new_value) = t; //Tiempo de la simulacion
 
	numero_piezas_totales.push_back(new_value);
	i = lista_distancias.begin();
	sigma = (l-*i)/vc;
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
std::list<std::tuple<double,double>>::iterator j = numero_piezas_totales.begin();

if(corre_cinta){
		//Cinta Corriendo
		if(valor == "ARRIVE"){
			// En caso de que sea por referencia
			// Usar copy
  		 	std::tuple<double,double> new_value (initial_value);
			v = std::get<0>(*j);
			std::get<0>(new_value) = v+1;
			std::get<1>(new_value) = t; //Tiempo de la simulacion
			numero_piezas_totales.push_back(new_value);

			if(!lista_distancias.empty()){
				i = lista_distancias.begin();
				sigma = (l-*i)/vc;
				while( i!= lista_distancias.end()){
					*i += (vc * (double) e);
					i++;
				}
			}else{
				sigma = l/vc;
			}
			lista_distancias.push_back(0);
		}
		if(valor == "START"){
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
		std::tuple<double,double> new_value (initial_value);
		v = std::get<0>(*j);
		std::get<0>(new_value) = v+1;
		std::get<1>(new_value) = t; //Tiempo de la simulacion
		numero_piezas_rechazadas.push_back(new_value);
		sigma = DBL_MAX;
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
if( *i < l ){
	*i = l;
	salida = "DETECT";
}else{
	*i = l+deltal;
	salida = "LEAVE";
}
return Event(&salida,0);
}
void cinta::exit() {
//Code executed at the end of the simulation.

}
