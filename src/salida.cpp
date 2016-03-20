#include "stdarg.h"
#include "string"
using namespace std;

class Salida 
{

public:

	std::string comando;

	int puerto;

    Salida( void )
    {
        comando = "NULL";
        puerto = 0;
    }
    
    string getComando( void ){
       return comando;
    }
    
    void setComando(std::string _comando){
        comando = _comando;
    }
    
    double getPuerto( void ){
        return puerto;
    }
    
    void setPuerto( int _puerto){
        puerto = _puerto;
    }
    
};