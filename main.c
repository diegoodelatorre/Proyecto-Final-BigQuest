#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "juego.h"

int main() {
    int nivel_actual = 1;
    
    // Estadisticas globales de toda la partida
    int total_global_monedas = 0;
    int monedas_globales_recolectadas = 0;
    int pasos_totales = 0;

    // Ciclo principal de niveles (1 al 3)
    for (nivel_actual = 1; nivel_actual <= 3; nivel_actual++) {
        int jugador_f = 5;
        int jugador_c = 5;
        char tecla;
        int jugando = 1;

        // Estadisticas de este nivel en especifico
        int monedas_recolectadas = 0;
        int tiene_llave = 0;
        int pasos = 0; // Nuevo contador de pasos

        // Se carga el laberinto correspondiente al nivel actual
        inicializar_mapa(nivel_actual);

        // Total de celdas en el mapa
        int total_celdas = FILAS_MAPA * COLS_MAPA;
        
        // Se usan las rutinas de NASM para contar dinamicamente
        int total_monedas = contar_caracteres((char*)mapa_actual, total_celdas, 'M');
        int celdas_libres = contar_celdas_libres((char*)mapa_actual, total_celdas);
        
        // Acumulamos las monedas posibles al total del juego
        total_global_monedas += total_monedas;

        // Ciclo principal del nivel
        while (jugando) {
            // La parte visible
            imprimir_ventana(jugador_f, jugador_c);
            
            // Muestra el nivel actual y progreso
            printf("--- NIVEL %d ---\n", nivel_actual);
            printf("Monedas: %d/%d | Llave: %s | Pasos: %d\n", monedas_recolectadas, total_monedas, tiene_llave ? "SI" : "NO", pasos);

            // Lee la tecla presionada
            tecla = _getch();

            // Variables para el nuevo movimiento
            int nueva_f = jugador_f;
            int nueva_c = jugador_c;

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
                        mapa_actual[nueva_f][nueva_c] = '.'; 
                    } else {
                        es_valido = 0; 
                    }
                }
            }

            // Si sigue siendo valido el movimiento se actualiza su posicion
            if (es_valido == 1) {
                // Si el jugador realmente se movio a una nueva celda, cuenta un paso
                if (jugador_f != nueva_f || jugador_c != nueva_c) pasos++;
                
                jugador_f = nueva_f;
                jugador_c = nueva_c;

                // Interaccion con las monedas 'M'
                if (detectar_objeto((char*)mapa_actual, COLS_MAPA, jugador_f, jugador_c, 'M')) {
                    monedas_recolectadas++;
                    monedas_globales_recolectadas++; // Suma a las globales
                    mapa_actual[jugador_f][jugador_c] = '.'; 
                }

                // Interaccion con la llave 'K'
                if (detectar_objeto((char*)mapa_actual, COLS_MAPA, jugador_f, jugador_c, 'K')) {
                    tiene_llave = 1;
                    mapa_actual[jugador_f][jugador_c] = '.'; 
                }

                // Llega a la salida 'E'
                if (detectar_objeto((char*)mapa_actual, COLS_MAPA, jugador_f, jugador_c, 'E')) {
                    jugando = 0;
                    pasos_totales += pasos; // Se suman los pasos al total
                }
            }
        } // Fin del nivel

        // Resumen final del nivel
        system("cls");
        printf("=================================\n");
        printf("      NIVEL %d COMPLETADO! \n", nivel_actual);
        printf("=================================\n");
        printf("Celdas libres: %d\n", celdas_libres);
        printf("Monedas recolectadas: %d/%d\n", monedas_recolectadas, total_monedas);
        printf("Pasos realizados: %d\n", pasos);
        printf("=================================\n");
        system("pause");
    } // Se pasa al siguiente nivel

    // Al terminar los 3 niveles se calcula el puntaje final usando NASM
    int puntaje_final = calcular_puntaje(monedas_globales_recolectadas, pasos_totales, 3);

    // Resumen de todo el juego
    system("cls");
    printf("=================================\n");
    printf("       JUEGO COMPLETADO          \n");
    printf("=================================\n");
    printf("Monedas totales recolectadas: %d/%d\n", monedas_globales_recolectadas, total_global_monedas);
    printf("Pasos totales: %d\n", pasos_totales);
    printf("Niveles completados: 3\n");
    printf("Puntaje final: %d\n", puntaje_final);
    printf("=================================\n");
    printf("Gracias por jugar BitQuest.\n");

    system("pause");
    return 0;
}