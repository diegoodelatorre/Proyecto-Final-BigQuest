# BitQuest - Proyecto Final de Arquitectura de Computadoras



**BitQuest** es un juego de exploración y laberintos por terminal desarrollado en lenguaje C y Ensamblador (NASM de 64 bits). El proyecto demuestra la integración exitosa entre un lenguaje de alto nivel (para la lógica general y el renderizado) y rutinas de bajo nivel (para cálculos matemáticos, manejo de memoria y validaciones).



## 🎯 Objetivo del Juego

El jugador (`P`) debe navegar a través de 3 laberintos de dificultad progresiva. Para avanzar al siguiente nivel, debe explorar el mapa para encontrar la llave (`K`), lo cual le permitirá abrir la puerta (`D`) y finalmente llegar a la salida (`E`). A lo largo del camino, el jugador puede recolectar monedas (`M`) para aumentar su puntaje final.



## ⚙️ Requisitos del Sistema

Para poder compilar y ejecutar este juego, el entorno debe contar con:

- Sistema Operativo: Windows (64 bits).

- Compilador de C: `gcc` (MinGW-w64).

- Ensamblador: `nasm` (Netwide Assembler).

- Nota: Ambos comandos (`gcc` y `nasm`) deben estar agregados al PATH del sistema.*



## 🚀 Instrucciones de Compilación y Ejecución

El proyecto incluye un script automatizado para facilitar su compilación.

1. Clona o descarga este repositorio en tu máquina local.

2. Abre la carpeta del proyecto.

3. Haz doble clic en el archivo **`build.bat`** (o ejecútalo desde la terminal).

4. El script realizará los siguientes pasos de forma automática:

   - Compilará `rutinas.asm` generando el código objeto `rutinas.obj`.

   - Enlazará `main.c` y `juego.c` junto con el objeto de NASM usando `gcc`.

   - Ejecutará el binario resultante `BitQuest.exe`.



## 🎮 Controles

El juego detecta las pulsaciones del teclado en tiempo real (sin necesidad de presionar Enter):

- **W / w** : Moverse hacia Arriba

- **S / s** : Moverse hacia Abajo

- **A / a** : Moverse a la Izquierda

- **D / d** : Moverse a la Derecha

- **Q / q** : Salir del juego inmediatamente



## 🗺️ Simbología del Mapa (Ventana de 20x20)

- `P` : Jugador

- `#` : Muro (Colisión sólida)

- `.` : Camino libre

- `M` : Moneda (Suma puntos)

- `K` : Llave (Requerida para escapar)

- `D` : Puerta (Se abre al tener la llave)

- `E` : Salida del nivel



## 🧠 Arquitectura y Desarrollo en NASM

Para cumplir con los requerimientos técnicos del proyecto, el motor principal del juego delega las tareas más intensivas a rutinas nativas en Ensamblador x86_64, las cuales reciben parámetros desde C siguiendo la convención de llamadas de Windows (RCX, RDX, R8, R9 y Pila):



1. `validar_movimiento`: Calcula dinámicamente el índice de la matriz en memoria `(fila * columnas) + columna` y valida si la celda destino es un muro.

2. `detectar_objeto`: Identifica las interacciones del jugador recuperando el quinto parámetro (el carácter a buscar) desde el *shadow space* de la pila (`[rsp+40]`).

3. `contar_caracteres`: Recorre la memoria linealmente para contar el total de monedas de forma dinámica en cada nivel.

4. `contar_celdas_libres`: Analiza el mapa base y retorna el total de celdas transitables.

5. `calcular_puntaje`: Ejecuta las operaciones aritméticas finales `(Monedas * 100) - Pasos + (Nivel * 500)`.



---

Autores:

- Diego Alejandro Delgado de la Torre - 550402 
- Fabricio Martinez Ávila - 549789
- Regina Rodriguez Hernandez - 551750
- José Eduardo Valadez Pedroza - 549815