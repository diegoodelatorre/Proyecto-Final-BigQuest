bits 64
default rel 
section .text

global validar_movimiento
global detectar_objeto

validar_movimiento:
    ; Convierte parametros de 32 bits a 64 bits para usarlos como indices de memoria
    movsxd rdx, edx
    movsxd r8, r8d
    movsxd r9, r9d

    ; Calcula el indice en el arreglo 1D: indice = (fila * columnas) + columna
    mov rax, r8          ; rax = fila
    imul rax, rdx        ; rax = fila * columnas
    add rax, r9          ; rax = (fila * columnas) + columna

    ; Se obtiene el caracter en esa posicion de memoria
    movzx eax, byte [rcx + rax]

    ; Verificación de si es una pared
    cmp al, '#'
    je .movimiento_bloqueado

    ; En el caso de que no sea pared, es valido
    mov eax, 1
    ret

.movimiento_bloqueado:
    mov eax, 0
    ret


detectar_objeto:
    movsxd rdx, edx
    movsxd r8, r8d
    movsxd r9, r9d

    ; Indice = (fila * columnas) + columna
    mov rax, r8
    imul rax, rdx
    add rax, r9

    ; Caracter actual de la matriz
    movzx eax, byte [rcx + rax]

    ; Obtener desde la pila el parametro a buscar que es el quinto
    mov r10d, dword [rsp + 40]

    ; Se compara el caracter de la matriz con el que se busca
    cmp al, r10b
    je .objeto_encontrado

    ; Cuando no es el que se busca
    mov eax, 0
    ret

.objeto_encontrado:
    mov eax, 1
    ret

global contar_caracteres
contar_caracteres:
    xor eax, eax
    xor r9, r9
    movsxd rdx, edx

.bucle_contar:
    cmp r9, rdx
    jge .fin_contar

    movzx r10d, byte [rcx + r9]
    cmp r10d, r8d
    jne .siguiente

    inc eax

.siguiente:
    inc r9
    jmp .bucle_contar

.fin_contar:
    ret

global contar_celdas_libres
contar_celdas_libres:
    xor eax, eax
    xor r8, r8
    movsxd rdx, edx

.bucle_libres:
    cmp r8, rdx
    jge .fin_libres

    movzx r9d, byte [rcx + r8]
    cmp r9b, '.'
    jne .siguiente_libre

    inc eax

.siguiente_libre:
    inc r8
    jmp .bucle_libres

.fin_libres:
    ret

global calcular_puntaje
calcular_puntaje:
    ; Se multiplican las monedas por 100
    mov eax, ecx
    imul eax, 100     ; eax = Monedas * 100

    ; Se restan los pasos
    sub eax, edx      ; eax = (Monedas * 100) - Pasos

    ; Se suma un bonus por completar el nivel
    mov r9d, r8d
    imul r9d, 500
    add eax, r9d

    ; Como minimo se deja de puntaje 0
    cmp eax, 0
    jge .fin_puntaje
    mov eax, 0

.fin_puntaje:
    ret