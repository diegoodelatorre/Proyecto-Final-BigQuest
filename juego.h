#ifndef JUEGO_H
#define JUEGO_H

#include "mapas.h"

void inicializar_mapa(int nivel);
void imprimir_ventana(int jugador_f, int jugador_c);

// Funciones de NASM
extern int validar_movimiento(char* mapa, int columnas, int nueva_fila, int nueva_col);
extern int detectar_objeto(char* mapa, int columnas, int fila, int col, char objeto);
extern int contar_caracteres(char* mapa, int total_celdas, char caracter);
extern int contar_celdas_libres(char* mapa, int total_celdas);

#endif