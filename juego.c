#include <stdio.h>
#include <stdlib.h>
#include "juego.h"

char mapa_actual[FILAS_MAPA][COLS_MAPA];

void inicializar_mapa(int nivel) {
    // llenar el camino libre y los bordes del mapa
    for (int f = 0; f < FILAS_MAPA; f++) {
        for (int c = 0; c < COLS_MAPA; c++) {
            if (f == 0 || f == FILAS_MAPA - 1 || c == 0 || c == COLS_MAPA - 1) {
                mapa_actual[f][c] = '#'; 
            } else {
                mapa_actual[f][c] = '.'; 
            }
        }
    }

    // Mapa del nivel 1
    if (nivel == 1) {
        for (int i = 5; i < 55; i++) mapa_actual[5][i] = '#';  
        for (int i = 5; i < 50; i++) mapa_actual[i][54] = '#'; 
        for (int i = 10; i < 55; i++) mapa_actual[50][i] = '#';
        for (int i = 10; i < 50; i++) mapa_actual[i][10] = '#';
        
        for (int i = 15; i < 45; i++) mapa_actual[10][i] = '#';
        for (int i = 10; i < 40; i++) mapa_actual[i][45] = '#';
        for (int i = 20; i < 45; i++) mapa_actual[40][i] = '#';
        for (int i = 20; i < 40; i++) mapa_actual[i][20] = '#';
        
        mapa_actual[7][15] = 'M'; mapa_actual[25][50] = 'M'; mapa_actual[55][20] = 'M'; 
        mapa_actual[45][15] = 'M'; mapa_actual[30][30] = 'M';
        
        mapa_actual[55][5] = 'K'; // llave abajo a la izquierda
        mapa_actual[25][25] = 'D'; // puerta en el centro
        mapa_actual[25][28] = 'E'; // salida en el centro
    }
    // Mapa del nivel 2
    else if (nivel == 2) {
        for (int f = 12; f <= 15; f++) for(int c = 5; c < 55; c++) mapa_actual[f][c] = '#';
        for (int f = 28; f <= 31; f++) for(int c = 5; c < 55; c++) mapa_actual[f][c] = '#';
        for (int f = 44; f <= 47; f++) for(int c = 5; c < 55; c++) mapa_actual[f][c] = '#';
        
        for (int c = 20; c <= 23; c++) for(int f = 5; f < 55; f++) mapa_actual[f][c] = '#';
        for (int c = 40; c <= 43; c++) for(int f = 5; f < 55; f++) mapa_actual[f][c] = '#';
        
        for (int f = 12; f <= 15; f++) { mapa_actual[f][10]='.'; mapa_actual[f][11]='.'; mapa_actual[f][30]='.'; mapa_actual[f][31]='.'; }
        for (int f = 28; f <= 31; f++) { mapa_actual[f][25]='.'; mapa_actual[f][26]='.'; mapa_actual[f][48]='.'; mapa_actual[f][49]='.'; }
        for (int f = 44; f <= 47; f++) { mapa_actual[f][15]='.'; mapa_actual[f][16]='.'; mapa_actual[f][35]='.'; mapa_actual[f][36]='.'; }
        
        for (int c = 20; c <= 23; c++) { mapa_actual[20][c]='.'; mapa_actual[21][c]='.'; mapa_actual[38][c]='.'; mapa_actual[39][c]='.'; }
        for (int c = 40; c <= 43; c++) { mapa_actual[8][c]='.'; mapa_actual[9][c]='.'; mapa_actual[35][c]='.'; mapa_actual[36][c]='.'; }

        mapa_actual[20][10] = 'M'; mapa_actual[40][50] = 'M'; mapa_actual[50][10] = 'M';
        mapa_actual[8][48] = 'K'; 
        mapa_actual[52][50] = 'D'; 
        mapa_actual[55][55] = 'E'; // salida hasta abajo
    }
    // Mapa del nivel 3
    else if (nivel == 3) {
        // Colocar las paredes que rodean la salida
        for (int f = 45; f <= 58; f++) {
            for (int c = 25; c <= 35; c++) {
                if (f == 45 || c == 25 || c == 35) {
                    mapa_actual[f][c] = '#';
                }
            }
        }
        mapa_actual[45][30] = 'D'; // La puerta bloquea el unico camino a la salida
        mapa_actual[55][30] = 'E'; // La salida dentro de las paredes que la deben de rodear

        for (int f = 10; f <= 13; f++) for(int c = 5; c < 50; c++) mapa_actual[f][c] = '#';
        for (int f = 25; f <= 28; f++) for(int c = 10; c < 55; c++) mapa_actual[f][c] = '#';
        for (int f = 38; f <= 41; f++) for(int c = 5; c < 45; c++) mapa_actual[f][c] = '#';

        for (int c = 15; c <= 18; c++) for(int f = 5; f < 45; f++) mapa_actual[f][c] = '#';
        for (int c = 42; c <= 45; c++) for(int f = 15; f < 55; f++) mapa_actual[f][c] = '#';
        
        for (int f = 10; f <= 13; f++) { mapa_actual[f][22]='.'; mapa_actual[f][23]='.'; }
        for (int f = 25; f <= 28; f++) { mapa_actual[f][30]='.'; mapa_actual[f][31]='.'; }
        for (int f = 38; f <= 41; f++) { mapa_actual[f][10]='.'; mapa_actual[f][11]='.'; }
        
        for (int c = 15; c <= 18; c++) { mapa_actual[20][c]='.'; mapa_actual[21][c]='.'; }
        for (int c = 42; c <= 45; c++) { mapa_actual[30][c]='.'; mapa_actual[31][c]='.'; mapa_actual[50][c]='.'; mapa_actual[51][c]='.'; }

        for (int c = 19; c <= 35; c++) mapa_actual[30][c] = '#';
        
        mapa_actual[5][50] = 'M'; mapa_actual[35][20] = 'M'; mapa_actual[45][10] = 'M'; mapa_actual[20][48] = 'M';
        mapa_actual[35][30] = 'K';
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

    // Imprime la ventana de 20x20 y algunas instrucciones de apoyo
    for (int f = inicio_f; f < inicio_f + VENTANA_FILAS; f++) {
        
        // fila del mapa
        for (int c = inicio_c; c < inicio_c + VENTANA_COLS; c++) {
            if (f == jugador_f && c == jugador_c) {
                printf("P");
            } else {
                printf("%c", mapa_actual[f][c]);
            }
        }
        
        int fila_relativa = f - inicio_f;
        
        if (fila_relativa == 2)       printf("      --- JUEGO ---");
        else if (fila_relativa == 4)  printf("      P : Jugador");
        else if (fila_relativa == 5)  printf("      # : Pared");
        else if (fila_relativa == 6)  printf("      . : Camino libre");
        else if (fila_relativa == 7)  printf("      M : Moneda");
        else if (fila_relativa == 8)  printf("      K : Llave");
        else if (fila_relativa == 9)  printf("      D : Puerta");
        else if (fila_relativa == 10) printf("      E : Salida");
        else if (fila_relativa == 12) printf("      --- CONTROLES ---");
        else if (fila_relativa == 14) printf("      W : Arriba");
        else if (fila_relativa == 15) printf("      S : Abajo");
        else if (fila_relativa == 16) printf("      A : Izquierda");
        else if (fila_relativa == 17) printf("      D : Derecha");
        else if (fila_relativa == 18) printf("      Q : Salir del juego");
        
        printf("\n"); 
    }
}