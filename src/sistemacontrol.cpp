#include "sistemacontrol.h"
void sistemacontrol::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	      %Type% is the parameter type

//Obtener Parametros
l = va_arg(parameters, double); 
deltal = va_arg(parameters, double);
vc = va_arg(parameters, double);
puerto_mesa1 = va_arg(parameters, int);
puerto_mesa2 = va_arg(parameters, int);
puerto_cinta = va_arg(parameters, int);

//Inicilizar Variables del Estado
corre_cinta = true;
sigma = DBL_MAX;

//Inicializar Variables de Salida 

}
double sistemacontrol::ta(double t) {
//This function returns a double.
return sigma;

}
void sistemacontrol::dint(double t) {
salida.setComando("NULL");
sigma = DBL_MAX;
}
void sistemacontrol::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
std::string comando = *(std::string*)(x.value);
int puerto = x.port;

if(comando == "DETECT"){
	if(! mesa1.getDisponible() && !mesa2.getDisponible()){
		corre_cinta = false;
		salida.setComando("STOP");
		salida.setPuerto(puerto_cinta);
		sigma = 0;
	}
}
if(comando == "LEAVE"){
	if(mesa1.getDisponible()){
		mesa1.setDisponible(false);
		salida.setComando("ARRIVE");
		salida.setPuerto(puerto_mesa1);
		sigma = 0;
	}
	if(mesa2.getDisponible()){
		mesa2.setDisponible(false);
		salida.setComando("ARRIVE");
		salida.setPuerto(puerto_mesa2);
		sigma = 0;
	}
}
if(comando == "UP"){
	if(puerto == puerto_mesa1){
		mesa1.moveUp();
		salida.setComando("ROTATE RIGHT");
		salida.setPuerto(puerto_mesa1);
		sigma = 0;
	}
	if(puerto == puerto_mesa2){
		mesa2.moveUp();
		salida.setComando("ROTATE RIGHT");
		salida.setPuerto(puerto_mesa2);
		sigma = 0;
	}
}
if(comando == "RIGHT"){
	if(puerto == puerto_mesa1){
		mesa1.rotateRight();
		salida.setComando("PICK");
		salida.setPuerto(puerto_mesa1);
		sigma = 0;
	}
	if(puerto == puerto_mesa2){
		mesa2.rotateRight();
		salida.setComando("PICK");
		salida.setPuerto(puerto_mesa2);
		sigma = 0;
	}
}
if(comando == "PIKED"){
	if(puerto == puerto_mesa1){
		salida.setComando("MOVE DOWN");
		salida.setPuerto(puerto_mesa1);
		sigma = 0;
	}
	if(puerto == puerto_mesa2){
		salida.setComando("MOVE DOWN");
		salida.setPuerto(puerto_mesa2);
		sigma = 0;
	}
}
if(comando == "DOWN"){
	if(puerto == puerto_mesa1){
		mesa1.moveDown();
		salida.setComando("ROTATE LEFT");
		salida.setPuerto(puerto_mesa1);
		sigma = 0;
	}
	if(puerto == puerto_mesa2){
		mesa2.moveDown();
		salida.setComando("ROTATE LEFT");
		salida.setPuerto(puerto_mesa2);
		sigma = 0;
	}
}
if(comando == "LEFT"){
	if(puerto == puerto_mesa1){
		mesa1.rotateLeft();
		mesa1.setDisponible(true);
	}
	if(puerto == puerto_mesa2){
		mesa2.rotateLeft();
		mesa2.setDisponible(true);
	}
	salida.setPuerto(puerto_cinta);
	if(corre_cinta){
		salida.setComando("NULL");
		sigma = DBL_MAX;
	}else{
		corre_cinta = true;
		salida.setComando("START");
		sigma = 0;
	}
}
}
Event sistemacontrol::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)


y = salida.getComando();
x = salida.getPuerto();

return Event(&y,x);
}
void sistemacontrol::exit() {
//Code executed at the end of the simulation.

}
