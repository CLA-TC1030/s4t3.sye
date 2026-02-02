#define CATCH_CONFIG_MAIN // defines main() automatically
#include <catch2/catch.hpp>

#include "../Ctesconf.hpp"
#include "../CCasilla.hpp"
#include "../CasillaNormal.hpp"
#include "../CasillaEscalera.hpp"
#include "../CasillaSerpiente.hpp"
#include "../Tablero.hpp"
#include "../Jugador.hpp"
#include "../CDado.hpp"
#include "../GameManual.hpp"
#include "../GameAutomatic.hpp"
#include "../Game.hpp"
#include "chkFiles.hpp"

// Pruebas para casillas -----------------------------------------------------------

TEST_CASE("ex0", "[Casillas Base bien formadas]")
{   
    CCasilla c1, c2(2,"E"), c3(3,"S");

    SECTION( "Validando casillas Base normales" ) {
        INFO("FUNCIONALIDAD ESPERADA: La clase CCasilla debe inicializarse correctamente con valores por defecto y con parámetros. Debe almacenar el número de casilla, tipo y calcular la siguiente casilla según el premio o castigo.");
        INFO("SUGERENCIA DE PROGRAMACIÓN: Implementa un constructor por defecto que inicialice numero=1, tipo='N' y premio_castigo=NOR_PREMIO_CASTIGO. El constructor parametrizado debe recibir numero y tipo, asignándolos a los atributos correspondientes.");
        REQUIRE( c1.getNumeroCasilla() == 1 );
        REQUIRE( c1.getTipo() == "N" );
        REQUIRE( c1.getSiguienteCasilla() == c1.getNumeroCasilla() + NOR_PREMIO_CASTIGO );
        REQUIRE( c2.getNumeroCasilla() == 2);
        REQUIRE( c2.getTipo() == "E" );
        REQUIRE( c2.getSiguienteCasilla() == c2.getNumeroCasilla() + NOR_PREMIO_CASTIGO);
        REQUIRE( c3.getNumeroCasilla() == 3);
        REQUIRE( c3.getTipo() == "S" );
        REQUIRE( c3.getSiguienteCasilla() == c3.getNumeroCasilla() + NOR_PREMIO_CASTIGO);
    }
}

TEST_CASE("ex1", "[Casillas Normales bien formadas]")
{   
    CasillaNormal c1, c2(3);

    SECTION( "Validando casillas Normales" ) {
        INFO("FUNCIONALIDAD ESPERADA: La clase CasillaNormal debe heredar de CCasilla y representar casillas sin premio ni castigo. El tipo debe ser 'N' y el valor de siguiente casilla debe ser igual al número actual.");
        INFO("SUGERENCIA DE PROGRAMACIÓN: Utiliza herencia de CCasilla. En el constructor por defecto invoca al constructor base sin parámetros. En el constructor parametrizado, asigna el número recibido al atributo numero y asegúrate que tipo='N' y premio_castigo=NOR_PREMIO_CASTIGO.");
        REQUIRE( c1.getNumeroCasilla() == 1 );
        REQUIRE( c1.getTipo() == "N" );
        REQUIRE( c1.getSiguienteCasilla() == c1.getNumeroCasilla() + NOR_PREMIO_CASTIGO);

        REQUIRE( c2.getNumeroCasilla() == 3 );
        REQUIRE( c2.getTipo() == "N" );
        REQUIRE( c2.getSiguienteCasilla() == c2.getNumeroCasilla() + NOR_PREMIO_CASTIGO);
    }
}

TEST_CASE("ex2", "[Casillas Escalera bien formadas]")
{   
    CasillaEscalera c1, c2(3);

    SECTION( "Validando casillas Escalera" ) {
        INFO("FUNCIONALIDAD ESPERADA: La clase CasillaEscalera debe heredar de CCasilla y representar casillas con premio positivo. El tipo debe ser 'L' y la siguiente casilla debe sumar ESC_PREMIO_CASTIGO al número actual.");
        INFO("SUGERENCIA DE PROGRAMACIÓN: Hereda de CCasilla e inicializa premio_castigo=ESC_PREMIO_CASTIGO y tipo='L' en el constructor. Invoca al constructor base CCasilla{numero, 'L'} en la lista de inicialización del constructor parametrizado.");
        REQUIRE( c1.getNumeroCasilla() == 1 );
        REQUIRE( c1.getTipo() == "L" );
        REQUIRE( c1.getSiguienteCasilla() == c1.getNumeroCasilla() + ESC_PREMIO_CASTIGO );

        REQUIRE( c2.getNumeroCasilla() == 3 );
        REQUIRE( c2.getTipo() == "L" );
        REQUIRE( c2.getSiguienteCasilla() == c2.getNumeroCasilla() + ESC_PREMIO_CASTIGO );
    }
}

TEST_CASE("ex3", "[Casillas Serpiente bien formadas]")
{   
    CasillaSerpiente c1, c2(10);

    SECTION( "Validando casillas Serpiente" ) {
        INFO("FUNCIONALIDAD ESPERADA: La clase CasillaSerpiente debe heredar de CCasilla y representar casillas con castigo negativo. El tipo debe ser 'S' y la siguiente casilla debe restar el valor absoluto de SER_PREMIO_CASTIGO al número actual.");
        INFO("SUGERENCIA DE PROGRAMACIÓN: Hereda de CCasilla, asigna premio_castigo=SER_PREMIO_CASTIGO (valor negativo) y tipo='S'. En el constructor por defecto, calcula numero=1-SER_PREMIO_CASTIGO para compensar el castigo inicial.");
        REQUIRE( c1.getNumeroCasilla() == 1 - SER_PREMIO_CASTIGO );
        REQUIRE( c1.getTipo() == "S" );
        REQUIRE( c1.getSiguienteCasilla() == c1.getNumeroCasilla() + SER_PREMIO_CASTIGO);

        REQUIRE( c2.getNumeroCasilla() == 10 );
        REQUIRE( c2.getTipo() == "S" );
        REQUIRE( c2.getSiguienteCasilla() == c2.getNumeroCasilla() + SER_PREMIO_CASTIGO);
    }
}

TEST_CASE("ex4", "[Polimorfismo de casillas]")
{   
    CCasilla c1{CasillaNormal(1)}, c2{CasillaEscalera(3)}, c3{CasillaSerpiente(10)};

    SECTION( "Validando casillas Normales, Escalera, Serpiente polimorficamente" ) {
        INFO("FUNCIONALIDAD ESPERADA: Las clases derivadas (CasillaNormal, CasillaEscalera, CasillaSerpiente) deben poder asignarse a objetos de tipo CCasilla, manteniendo su comportamiento específico mediante polimorfismo.");
        INFO("SUGERENCIA DE PROGRAMACIÓN: Asegúrate que CCasilla tenga métodos virtuales si es necesario. Utiliza inicialización por copia o conversión de tipos. Las clases derivadas deben sobrescribir correctamente los atributos heredados en sus constructores.");
        REQUIRE( c1.getNumeroCasilla() == 1 );
        REQUIRE( c1.getTipo() == "N" );
        REQUIRE( c1.getSiguienteCasilla() == c1.getNumeroCasilla() + NOR_PREMIO_CASTIGO );

        REQUIRE( c2.getNumeroCasilla() == 3 );
        REQUIRE( c2.getTipo() == "L" );
        REQUIRE( c2.getSiguienteCasilla() == c2.getNumeroCasilla() + ESC_PREMIO_CASTIGO );

        REQUIRE( c3.getNumeroCasilla() == 10 );
        REQUIRE( c3.getTipo() == "S" );
        REQUIRE( c3.getSiguienteCasilla() == c3.getNumeroCasilla() + SER_PREMIO_CASTIGO );
    }
}

// Pruebas para Tablero -----------------------------------------------------------

TEST_CASE("ex5", "[Tablero bien formado]")
{   
    SECTION( "Validando Tablero en memoria" ) {
        INFO("FUNCIONALIDAD ESPERADA: La clase Tablero debe poder crear un tablero de MAX_CASILLAS, permitir asignar casillas de diferentes tipos en posiciones específicas y mostrar el tablero completo.");
        INFO("SUGERENCIA DE PROGRAMACIÓN: Utiliza un arreglo de CCasilla de tamaño MAX_CASILLAS. Implementa setCasilla(CCasilla, int) para asignar una casilla en la posición indicada (índice-1) y print() para recorrer e imprimir todas las casillas.");

        Tablero t;

        t.setCasilla(CasillaEscalera(5), 5);
        t.setCasilla(CasillaEscalera(10), 10);
        t.setCasilla(CasillaEscalera(15), 15);

        t.setCasilla(CasillaSerpiente(7), 7);
        t.setCasilla(CasillaSerpiente(12), 12);
        t.setCasilla(CasillaSerpiente(25), 25);

        t.print();
        REQUIRE( true );
    }

    SECTION( "Validando desde Archivo" ) {
        INFO("FUNCIONALIDAD ESPERADA: El Tablero debe poder cargar su configuración desde un archivo de texto, leyendo el tipo de cada casilla (N, L, S) línea por línea y creando las casillas correspondientes.");
        INFO("SUGERENCIA DE PROGRAMACIÓN: Implementa un constructor que reciba el nombre del archivo. Usa std::ifstream para leer línea por línea. Según el carácter leído ('N', 'L', 'S'), crea objetos CasillaNormal, CasillaEscalera o CasillaSerpiente y asígnalos con setCasilla().");
        Tablero tf("t1.tab");

        tf.print();
        REQUIRE( true );
    }

    SECTION( "Validando casillas en Tablero ") {
        INFO("FUNCIONALIDAD ESPERADA: El método getCasilla(int) debe devolver la casilla en la posición especificada, preservando su tipo y propiedades (número, tipo, siguiente casilla).");
        INFO("SUGERENCIA DE PROGRAMACIÓN: Implementa getCasilla(int i) retornando this->c[i-1] para acceder al arreglo con base 1. Verifica que el tipo y atributos de la casilla se mantengan correctos después de ser asignados y recuperados.");
        Tablero tf("t1.tab");

        REQUIRE (tf.getCasilla(1).getNumeroCasilla()==1);
        REQUIRE (tf.getCasilla(1).getTipo()=="N");
        REQUIRE (tf.getCasilla(1).getSiguienteCasilla()==tf.getCasilla(1).getNumeroCasilla()+NOR_PREMIO_CASTIGO);

        REQUIRE (tf.getCasilla(10).getNumeroCasilla()==10);
        REQUIRE (tf.getCasilla(10).getTipo()=="L");
        REQUIRE (tf.getCasilla(10).getSiguienteCasilla()==tf.getCasilla(10).getNumeroCasilla()+ESC_PREMIO_CASTIGO);

        REQUIRE (tf.getCasilla(25).getNumeroCasilla()==25);
        REQUIRE (tf.getCasilla(25).getTipo()=="S");
        REQUIRE (tf.getCasilla(25).getSiguienteCasilla()==tf.getCasilla(25).getNumeroCasilla()+SER_PREMIO_CASTIGO);

    }
}

TEST_CASE("ex6", "[Jugador bien formado]")
{   
    SECTION( "Validando Jugador" ) {
        INFO("FUNCIONALIDAD ESPERADA: La clase Jugador debe almacenar el número de jugador y su casilla actual. Debe inicializarse en la casilla 1 y permitir consultar y modificar la casilla actual.");
        INFO("SUGERENCIA DE PROGRAMACIÓN: Implementa atributos numero y casilla_actual. El constructor debe recibir el número del jugador e inicializar casilla_actual=1. Crea métodos getCasilla_actual() que retorne casilla_actual y setCasilla_actual(int) que la actualice.");
        Jugador j(1), k(2);

        REQUIRE(j.getCasilla_actual()==1);

        k.setCasilla_actual(10);
        REQUIRE(k.getCasilla_actual()==10);
    }
}

TEST_CASE("ex7", "[Dado no aleatorio-secuencial]")
{   
    SECTION( "Validando Dado no aleatorio-secuencial" ) {
        INFO("FUNCIONALIDAD ESPERADA: La clase CDado debe poder configurarse como no aleatoria y generar valores secuenciales del 1 al 6 repetidamente (1,2,3,4,5,6,1,2,3...).");
        INFO("SUGERENCIA DE PROGRAMACIÓN: Usa un atributo estático cara y switchrandom. Si switchrandom=false, implementa getValorDado() para incrementar cara=(cara%6)+1 y retornar ese valor. Si switchrandom=true, usa rand()%6+1.");
        CDado d(false);

        for (auto i=0; i < 12; i++)
        {
            std::cout << d.getValorDado() << "\n";
        }
        REQUIRE(true);
    }
}


TEST_CASE("ex8", "[Ejecucion de Juego Manual]")
{   
    SECTION( "Validando Ejecucion de Juego Manual" ) {
        INFO("FUNCIONALIDAD ESPERADA: La clase GameManual debe ejecutar un juego completo leyendo comandos del usuario o archivo, procesando turnos, moviendo jugadores y determinando al ganador. La salida debe coincidir exactamente con el archivo de referencia.");
        INFO("SUGERENCIA DE PROGRAMACIÓN: Implementa el método getInput() para leer del archivo 'input' si swio=true o de cin si swio=false. El método start() debe simular turnos, lanzar dados, mover jugadores según las casillas y escribir la salida al archivo 'output' o cout.");
        Game *gm = new GameManual("t1.tab");

        gm->setDadoAleatorio(false);
        gm->setOutputToFile(true);

        gm->start();

        delete gm;
        
        REQUIRE(chkFiles("output", "test/toutput"));
    }
}

TEST_CASE("ex9", "[Ejecucion de Juego Automatico]")
{   
    SECTION( "Validando Ejecucion de Juego Automatico" ) {
        INFO("FUNCIONALIDAD ESPERADA: La clase GameAutomatic debe ejecutar un juego automático sin intervención del usuario, retornando siempre 'C' como entrada. El resultado del juego debe coincidir exactamente con el archivo de referencia.");
        INFO("SUGERENCIA DE PROGRAMACIÓN: Sobrescribe el método getInput() para retornar siempre 'C'. El resto de la lógica hereda de Game. Asegúrate que la simulación de turnos y generación de salida funcionen correctamente usando el dado no aleatorio configurado.");
        Game *ga = new GameAutomatic("t1.tab");

        ga->setDadoAleatorio(false);
        ga->setOutputToFile(true);

// Prueba que la entrada del juego es solo "C", no proviene ni del teclado, ni del archivo "input". Proviene del "Automata" imaginario ...
        bool isC=true;
        for (auto i=0; i<99; i++) 
            if (ga->getInput() != "C")
                isC=false;
        
        ga->start();

        delete ga;
            
        REQUIRE(isC);   
        REQUIRE(chkFiles("output", "test/toutput"));
    }
}

TEST_CASE("ex10", "[Dado sobrecargado]")
{
    CDado d(false);

    SECTION( "Validando Ejecucion de Dado sobrecargado lanzado  1 vez" ) {
        INFO("FUNCIONALIDAD ESPERADA: El operador + sobrecargado debe permitir lanzar el dado n veces y retornar el valor del último lanzamiento. Para 1 lanzamiento después de resetear, debe retornar 1.");
        INFO("SUGERENCIA DE PROGRAMACIÓN: Implementa operator+(int tiradas) que ejecute un ciclo de tiradas iteraciones, llamando getValorDado() en cada una y retornando el último valor obtenido. Asegúrate que resetDado() inicialice cara=0.");
        d.resetDado();
        REQUIRE(d+1==1);
    }

    SECTION( "Validando Ejecucion de Dado sobrecargado lanzado  5 veces" ) {
        INFO("FUNCIONALIDAD ESPERADA: El operador + sobrecargado con 5 lanzamientos debe retornar el valor de la quinta tirada. Después de resetear en 0, la quinta tirada debe ser 5.");
        INFO("SUGERENCIA DE PROGRAMACIÓN: El operador+ debe acumular los lanzamientos secuencialmente. Si cara inicia en 0 y cada llamada incrementa cara=(cara%6)+1, entonces: lanzamiento 1→1, 2→2, 3→3, 4→4, 5→5.");
        d.resetDado();
        REQUIRE(d+5==5);
    }
}
