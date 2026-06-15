#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "juego.h"

int main() {
    int jugador_f = 5;
    int jugador_c = 5;
    char tecla;
    int jugando = 1;

    // Variable de estado para la llave
    int tiene_llave = 0;
    
    // Variable para las monedas recolectadas
    int monedas_recolectadas = 0;

    // Mapa completo
    inicializar_mapa();
    
    // Total de celdas en el mapa
    int total_celdas = FILAS_MAPA * COLS_MAPA;
    
    // Se usan las rutinas de NASM para contar dinamicamente
    int total_monedas = contar_caracteres((char*)mapa_actual, total_celdas, 'M');
    int celdas_libres = contar_celdas_libres((char*)mapa_actual, total_celdas);

    // Ciclo principal del juego
    while (jugando) {
        // La parte visible
        imprimir_ventana(jugador_f, jugador_c);

        // Muestra el progreso de monedas y la llave
        printf("Monedas: %d/%d | Llave: %s\n", monedas_recolectadas, total_monedas, tiene_llave ? "SI" : "NO");

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

        // Interaccion con la puerta 'D'
        if (es_valido == 1) {
            if (detectar_objeto((char*)mapa_actual, COLS_MAPA, nueva_f, nueva_c, 'D')) {
                if (tiene_llave) {
                    mapa_actual[nueva_f][nueva_c] = '.'; // Solo se abre si tiene la llave
                } else {
                    es_valido = 0; // Si no se bloquea
                }
            }
        }

        // Si sigue siendo valido el movimiento se actualiza la posicion
        if (es_valido == 1) {
            jugador_f = nueva_f;
            jugador_c = nueva_c;

            // Interaccion con las monedas 'M'
            if (detectar_objeto((char*)mapa_actual, COLS_MAPA, jugador_f, jugador_c, 'M')) {
                monedas_recolectadas++;
                mapa_actual[jugador_f][jugador_c] = '.'; // Desaparece cuando la recoges
            }

            // Interaccion con la llave 'K'
            if (detectar_objeto((char*)mapa_actual, COLS_MAPA, jugador_f, jugador_c, 'K')) {
                tiene_llave = 1;
                mapa_actual[jugador_f][jugador_c] = '.'; // Desaparece cuando la recoges
            }

            // Llega a la salida 'E'
            if (detectar_objeto((char*)mapa_actual, COLS_MAPA, jugador_f, jugador_c, 'E')) {
                jugando = 0; // Se rompe el ciclo del juego
                system("cls");
                printf("=================================\n");
                printf("  ¡Llegaste a la salida! \n");
                printf("=================================\n");
                // Muestra los contadores que calculo NASM
                printf("Celdas libres contadas en NASM: %d\n", celdas_libres);
                printf("Monedas recolectadas: %d/%d\n", monedas_recolectadas, total_monedas);
                printf("=================================\n");
            }
        }
    }
    
    system("pause");
    return 0;
}