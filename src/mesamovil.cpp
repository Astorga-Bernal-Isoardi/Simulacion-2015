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
l = va_arg(parameters, double); 
deltal = va_arg(parameters, double);
vc = va_arg(parameters, double);

//Inicilizar Variables del Estado
sigma = DBL_MAX;

//Inicializar Variables de Salida 
salida = "NULL";
y = 0;
}
double mesamovil::ta(double t) {
//This function returns a double.
return sigma;

}
void mesamovil::dint(double t) {

}
void mesamovil::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

}
Event mesamovil::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)


return Event();
}
void mesamovil::exit() {
//Code executed at the end of the simulation.

}
