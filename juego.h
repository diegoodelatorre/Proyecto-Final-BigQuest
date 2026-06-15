#ifndef JUEGO_H
#define JUEGO_H

#include "mapas.h"

void inicializar_mapa();
void imprimir_ventana(int jugador_f, int jugador_c);

// Funciones de NASM
extern int validar_movimiento(char* mapa, int columnas, int nueva_fila, int nueva_col);

#endif