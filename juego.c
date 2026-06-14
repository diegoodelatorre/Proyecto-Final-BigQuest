#include <stdio.h>
#include <stdlib.h>
#include "juego.h"

char mapa_actual[FILAS_MAPA][COLS_MAPA];

void inicializar_mapa() {
    // Recorre la matriz completa
    for (int f = 0; f < FILAS_MAPA; f++) {
        for (int c = 0; c < COLS_MAPA; c++) {
            // Pone la pared en los bordes del mapa
            if (f == 0 || f == FILAS_MAPA - 1 || c == 0 || c == COLS_MAPA - 1) {
                mapa_actual[f][c] = '#'; 
            } else {
                // Pone el camino libre
                mapa_actual[f][c] = '.'; 
            }
        }
    }
}

void imprimir_ventana(int jugador_f, int jugador_c) {
    int inicio_f = jugador_f - (VENTANA_FILAS / 2);
    int inicio_c = jugador_c - (VENTANA_COLS / 2);

    // Validar que no se salga de los bordes
    if (inicio_f < 0) inicio_f = 0;
    if (inicio_c < 0) inicio_c = 0;
    if (inicio_f > FILAS_MAPA - VENTANA_FILAS) inicio_f = FILAS_MAPA - VENTANA_FILAS;
    if (inicio_c > COLS_MAPA - VENTANA_COLS) inicio_c = COLS_MAPA - VENTANA_COLS;

    system("cls");

    // Imprime la ventana de 20x20
    for (int f = inicio_f; f < inicio_f + VENTANA_FILAS; f++) {
        for (int c = inicio_c; c < inicio_c + VENTANA_COLS; c++) {
            if (f == jugador_f && c == jugador_c) {
                printf("P");
            } else {
                printf("%c", mapa_actual[f][c]);
            }
        }
        printf("\n"); 
    }
}