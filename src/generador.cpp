#include "generador.h"
void generador::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
// %Name% is the parameter name
//	%Type% is the parameter type

//Obtener Parametros
lambda_distribucion = va_arg(parameters, double);
l = va_arg(parameters, double);
deltal = va_arg(parameters, double);
vc = va_arg(parameters, double);

//Inicilizar Variables del Estado
srand(time(NULL));
do{
	u = (rand()/(double) (RAND_MAX + 1));
	s = -(1/lambda_distribucion) * log(u); //Wikipedia
} while (s < (deltal / vc));
sigma = s;

//Inicializar Variables de Salida
y = "ARRIVE";
}
double generador::ta(double t) {
//This function returns a double.
return sigma;
}
void generador::dint(double t) {
do{
	u = (rand()/(double) (RAND_MAX + 1));
	s = -log(u)/lambda_distribucion;
} while (s < (deltal / vc));

sigma = s;
}
void generador::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

}
Event generador::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)

return Event(&y, 0);
}
void generador::exit() {
//Code executed at the end of the simulation.

}
