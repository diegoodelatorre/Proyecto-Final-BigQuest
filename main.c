#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "juego.h"

int main() {
    int jugador_f = 5;
    int jugador_c = 5;

    // Mapa completo
    inicializar_mapa();
    
    // La parte visible
    imprimir_ventana(jugador_f, jugador_c);
    
    system("pause");
    return 0;
}