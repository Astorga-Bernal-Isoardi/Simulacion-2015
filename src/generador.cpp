#include "generador.h"
void generador::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
// %Name% is the parameter name
//	%Type% is the parameter type
srand(time(0));

_lambda = va_arg(parameters, double);
_l = va_arg(parameters, double);
_deltal = va_arg(parameters, double);
_vc = va_arg(parameters, double);

do{
	u = (rand()/(double) (RAND_MAX + 1));
	s = -log(u)/_lambda;
} while (s < (_deltal / _vc));

sigma = s;
y = "ARRIVE";
}
double generador::ta(double t) {
//This function returns a double.
return sigma;
}
void generador::dint(double t) {
do{
	u = (rand()/(double) (RAND_MAX + 1));
	s = -log(u)/_lambda;
} while (s < (_deltal / _vc));

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
