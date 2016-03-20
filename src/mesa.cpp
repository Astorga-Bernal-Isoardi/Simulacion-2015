#include "stdarg.h"
#include "string"
using namespace std;

class Mesa 
{
public:

	std::string elevacion;

	std::string rotacion;

	bool disponible;
	
    Mesa( void )
    {
        elevacion = "DOWN";
        rotacion = "LEFT";
        disponible = true;
    }
    
    string getElevacion( void ){
       return elevacion;
    }
    	
    string getRotacion( void ){
        return rotacion;
    }
    
    void moveUp( void ){
        elevacion = "UP";
    }
    
    void moveDown( void ){
        elevacion = "DOWN";
    }
    
    void rotateLeft( void ){
        rotacion = "LEFT";
    }
    
    void rotateRight( void ){
        rotacion = "RIGHT";
    }
    
    void setDisponible(bool _disponible){
        disponible = _disponible;
    }
    
    bool getDisponible( void ){
        return disponible;
    }
};