bits 64
default rel 
section .text

global validar_movimiento

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