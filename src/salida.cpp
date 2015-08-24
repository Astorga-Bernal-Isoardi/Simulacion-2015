#include "string"
using namespace std;

class Salida 
{

public:

	string comando;

	int puerto;

    Salida( void )
    {
        comando = "NULL";
        puerto = 0;
    }
    
    string getComando( void ){
       return comando;
    }
    
    void setComando( string _comando){
        comando = _comando;
    }
    
    double getPuerto( void ){
        return puerto;
    }
    
    void setPuerto( int _puerto){
        puerto = _puerto;
    }
    
};