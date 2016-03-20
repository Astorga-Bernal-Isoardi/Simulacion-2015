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
tmov = va_arg(parameters, double);
l = va_arg(parameters, double); //Longitud de la cinta
deltal = va_arg(parameters, double); //Longitud de los objetos que viajan en la cinta
vc = va_arg(parameters, double); //Velocidad a la cual se mueve la cinta
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
salida = "NULL";
}
void mesamovil::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
std::string vx = *(std::string*)(x.value);
puerto = x.port; 

// Asumiendo que el sistema de control sabe  
// que esta en posicion correcta

printLog("[MESA] ENTRADA DESDE CONTROLADOR A MESA %i", x.port ); 
printLog(" Y = %s\n",vx.data()); 
if(vx == "ARRIVE"){
	salida = "UP";
	sigma = tmov;
}
if(vx == "MOVE UP"){
	salida = "RIGHT";
	sigma = tmov;
}
if(vx == "ROTATE RIGHT"){
	salida = "PIKED";
	sigma = tmov;
}
if(vx == "PICK"){
	srand(time(NULL));
	salida = "DOWN";
	sigma = rand()%(6)+ 3;
}
if(vx == "MOVE DOWN"){
	salida = "LEFT";
	sigma = tmov;
}
if(vx == "ROTATE LEFT"){
	salida = "READY";
	sigma = tmov;
}

}
Event mesamovil::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
printLog("[MESA] SALIDA A CONTROLADOR DATO Y = %s",salida.data()); 
printLog(" PUERTO Y = %i\n", (int) puerto); 
return Event(&salida, (int) puerto);
}
void mesamovil::exit() {
//Code executed at the end of the simulation.

}
