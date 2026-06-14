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