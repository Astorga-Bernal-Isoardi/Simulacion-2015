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
puerto_mesa1 = va_arg(parameters, int);
puerto_mesa2 = va_arg(parameters, int);
puerto_cinta = va_arg(parameters, int);
l = va_arg(parameters, double); 
deltal = va_arg(parameters, double);
vc = va_arg(parameters, double);

//Inicilizar Variables del Estado
corre_cinta = true;
sigma = DBL_MAX;
x = 0;
z = "NULL";
salida.setComando(z);
salida.setPuerto(puerto_cinta);

mesa1.setDisponible(true);
mesa2.setDisponible(true);
//Inicializar Variables de Salida 

}
double sistemacontrol::ta(double t) {
//This function returns a double.
return sigma;

}
void sistemacontrol::dint(double t) {
z = "NULL";
x = 0;
salida.setComando(z);
sigma = DBL_MAX;
}
void sistemacontrol::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
std::string comando = *(std::string*)(x.value);
int puerto = (int) x.port;

if(comando == "DETECT"){
	printLog("[CONTROLADOR] Cinta Corriendo - ENTRADA DESDE CINTA Vx= DETECT\n");
	if(! mesa1.getDisponible() && !mesa2.getDisponible()){
		corre_cinta = false;
		z = "STOP";
		salida.setComando(z);
		salida.setPuerto(puerto_cinta);
		printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A CINTA STOP\n");
		sigma = 0;
	}
}
if(comando == "LEAVE"){
	printLog("[CONTROLADOR] Cinta Corriendo - ENTRADA DESDE CINTA Vx= LEAVE\n");
	if(mesa1.getDisponible()){
		mesa1.setDisponible(false);
		z = "ARRIVE";
		salida.setComando(z);
		salida.setPuerto(1);
		printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A MESA 1 ARRIVE\n");
		sigma = 0;
	}else{
		if(mesa2.getDisponible()){
			mesa2.setDisponible(false);
			z = "ARRIVE";
			salida.setComando(z);
			salida.setPuerto(2);
			printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A MESA 2 ARRIVE\n");
			sigma = 0;
		}else{
			printLog("[CONTROLADOR] ERROR NO HAY MESAS DISPONIBLE Y LLEGO UN LEAVE\n");
		}
	}
}
if(comando == "UP"){
	if(puerto == 1){
		salida.setPuerto(1);
		printLog("[CONTROLADOR] Cinta Corriendo - ENTRADA DESDE MESA 1 Vx= UP");
		printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A MESA 1 MOVE UP\n");
	}
	if(puerto == 2){
		salida.setPuerto(2);
		printLog("[CONTROLADOR] Cinta Corriendo - ENTRADA DESDE MESA 2 Vx= UP");
		printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A MESA 2 MOVE UP\n");
	}
	z = "MOVE UP";
	salida.setComando(z);
	sigma = 0;
}
if(comando == "RIGHT"){
	if(puerto == 1){
		mesa1.moveUp();
		salida.setPuerto(1);
		printLog("[CONTROLADOR] Cinta Corriendo - ENTRADA DESDE MESA 1 Vx= RIGHT");
		printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A MESA 1 ROTATE RIGHT\n");}
	if(puerto == 2){
		mesa2.moveUp();
		salida.setPuerto(2);
		printLog("[CONTROLADOR] Cinta Corriendo - ENTRADA DESDE MESA 2 Vx= RIGHT");
		printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A MESA 2 ROTATE RIGHT\n");
	}
	z = "ROTATE RIGHT";
	salida.setComando(z);
	sigma = 0;
}
if(comando == "PIKED"){
	if(puerto == 1){
		mesa1.rotateRight();
		salida.setPuerto(1);
		printLog("[CONTROLADOR] Cinta Corriendo - ENTRADA DESDE MESA 1 Vx= PIKED");
		printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A MESA 1 PICK\n");
	}
	if(puerto == 2){
		mesa2.rotateRight();
		salida.setPuerto(2);
		printLog("[CONTROLADOR] Cinta Corriendo - ENTRADA DESDE MESA 2 Vx= PIKED");
		printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A MESA 2 PICK\n");
	}
	z = "PICK";
	salida.setComando(z);
	sigma = 0;
}
if(comando == "DOWN"){
	if(puerto == 1){
		salida.setPuerto(1);
		printLog("[CONTROLADOR] Cinta Corriendo - ENTRADA DESDE MESA 1 Vx= DOWN");
		printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A MESA 1 MOVE DOWN\n");	
	}
	if(puerto == 2){
		salida.setPuerto(2);
		printLog("[CONTROLADOR] Cinta Corriendo - ENTRADA DESDE MESA 2 Vx= DOWN");
		printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A MESA 2 MOVE DOWN\n");	
	}
	z = "MOVE DOWN";
	salida.setComando(z);
	sigma = 0;
}
if(comando == "LEFT"){
	if(puerto == 1){
		printLog("[CONTROLADOR] Cinta Corriendo - ENTRADA DESDE MESA 1 Vx= LEFT");
		printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A MESA 1 ROTATE LEFT\n");	
		mesa1.moveDown();
		salida.setPuerto(1);
	}
	if(puerto == 2){
		printLog("[CONTROLADOR] Cinta Corriendo - ENTRADA DESDE MESA 2 Vx= LEFT");
		printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A MESA 2 ROTATE LEFT\n");	
		mesa2.moveDown();
		salida.setPuerto(2);
	}
	z = "ROTATE LEFT";
	salida.setComando(z);
	sigma = 0;
}
if(comando == "READY"){
	if(puerto == 1){
		mesa1.rotateLeft();
		mesa1.setDisponible(true);
	}
	if(puerto == 2){
		mesa2.rotateLeft();
		mesa2.setDisponible(true);
	}
	if(corre_cinta){
		sigma = DBL_MAX;
	}else{
		corre_cinta = true;
		salida.setPuerto(0);
		z = "START";
		salida.setComando(z);
		sigma = 0;
		printLog("[CONTROLADOR] Cinta Corriendo - SALIDA A CINTA START\n");	
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
