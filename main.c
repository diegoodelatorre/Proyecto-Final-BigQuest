#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "juego.h"

int main() {
    int jugador_f = 5;
    int jugador_c = 5;
    char tecla;
    int jugando = 1;

    // Mapa completo
    inicializar_mapa();
    
    // Ciclo principal del juego
    while (jugando) {
        // La parte visible
        imprimir_ventana(jugador_f, jugador_c);

        // Lee la tecla presionada
        tecla = _getch();

        // Por ahora el movimiento es libre
        switch (tecla) {
            case 'w': case 'W': jugador_f--; break;
            case 's': case 'S': jugador_f++; break;
            case 'a': case 'A': jugador_c--; break;
            case 'd': case 'D': jugador_c++; break;
            case 'q': case 'Q': 
                system("cls");
                printf("Saliste del juego.\n");
                exit(0);
        }

        // Validaciones basicas por ahora para que no se salga del mapa
        if (jugador_f < 0) jugador_f = 0;
        if (jugador_c < 0) jugador_c = 0;
        if (jugador_f >= FILAS_MAPA) jugador_f = FILAS_MAPA - 1;
        if (jugador_c >= COLS_MAPA) jugador_c = COLS_MAPA - 1;
    }
    
    system("pause");
    return 0;
}

