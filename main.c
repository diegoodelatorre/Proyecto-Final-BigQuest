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

        // Variables para el nuevo movimiento
        int nueva_f = jugador_f;
        int nueva_c = jugador_c;

        // Por ahora el movimiento es libre
        switch (tecla) {
            case 'w': case 'W': nueva_f--; break;
            case 's': case 'S': nueva_f++; break;
            case 'a': case 'A': nueva_c--; break;
            case 'd': case 'D': nueva_c++; break;
            case 'q': case 'Q': 
                system("cls");
                printf("Saliste del juego.\n");
                exit(0);
        }

        // Se valida si esta chocando con una pared o no
        int es_valido = validar_movimiento((char*)mapa_actual, COLS_MAPA, nueva_f, nueva_c);

        // Si el movimiento es valido se actualiza la posicion del jugador
        if (es_valido == 1) {
            jugador_f = nueva_f;
            jugador_c = nueva_c;
        }
    }
    
    system("pause");
    return 0;
}

