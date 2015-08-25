#include "mesamovil.h"
void mesamovil::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor. 
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
// %Name% is the parameter name
// %Type% is the parameter type

//Obtener Parametros
l = va_arg(parameters, double); //Longitud de la cinta
deltal = va_arg(parameters, double); //Longitud de los objetos que viajan en la cinta
vc = va_arg(parameters, double); //Velocidad a la cual se mueve la cinta
tmov = va_arg(parameters, double);
puerto = va_arg(parameters, double);

//Inicilizar Variables del Estado
sigma = DBL_MAX;

//Inicializar Variables de Salida 
salida = "NULL";
}
double mesamovil::ta(double t) {
//This function returns a double.
return sigma;

}
void mesamovil::dint(double t) {
//Inicilizar Variables del Estado
sigma = DBL_MAX;

//Inicializar Variables de Salida 
salida = "NULL";
}
void mesamovil::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
std::string vx = *(std::string*)(x.value);
// Asumiendo que el sistema de control sabe  
// que esta en posicion correcta

if(salida != "NULL" ){
		if(vx == "ARRIVE"){
			salida = "UP";
			sigma = tmov;
		}
		if(vx == "MOVE UP"){
			salida = "UP";
			sigma = tmov;
		}
		if(vx == "MOVE DOWN"){
			salida = "DOWN";
			sigma = tmov;
		}
		if(vx == "ROTATE LEFT"){
			salida = "LEFT";
			sigma = tmov;
		}
		if(vx == "ROTATE RIGHT"){
			salida = "RIGHT";
			sigma = tmov;
		}
		if(vx == "PICK"){
        srand(time(NULL));
			s = rand()%(6)+ 3; 
			salida = "PIKED";
			sigma = s;
		} 	 
} else {
		//Inicilizar Variables del Estado
		sigma = DBL_MAX;
		//Inicializar Variables de Salida 
		salida = "NULL";
}
	
}
Event mesamovil::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)

return Event(&salida,2);
}
void mesamovil::exit() {
//Code executed at the end of the simulation.

}
