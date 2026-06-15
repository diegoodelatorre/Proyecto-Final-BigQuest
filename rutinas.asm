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
