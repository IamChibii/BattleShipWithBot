#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define TAB 10 
#define MAXBARCOS 5
#define MAXPUNTOS 17 //Verificar el ganador 

void mostrarTablero(char tablero[TAB][TAB]);
//void mostrarTabPos(char tablero[TAB][TAB]);
int validarPos(char tablero[TAB][TAB], char fila, int columna, int direccion, int tamBarco);
void colocarB(char tablero[TAB][TAB], char barco, char fila, int columna, int direccion, int tamBarco);
void mostrarDisponibles(int colocados[], char nom[][20], int tamanos[]);
int obtenerSB(int colocados[]);
//void posicionarB(char tablero[TAB][TAB], char barco, int barcoTam, char nameB[]);
void posicionarBS(char tablero[TAB][TAB]);
void posicionarBBot(char tablero[TAB][TAB]);
void marcarBHundido(char tabA[TAB][TAB], int fila, int columna);
void tenerUnAtaque(char* fila, int* columna);
//void realizarAhumano(char tablero[TAB][TAB], char tabA[TAB][TAB], char fila, int columna);
void ataqueHumano(char tablero[TAB][TAB], char tabA[TAB][TAB]);
void ataqueBot(char tablero[TAB][TAB], char tabA[TAB][TAB]);
int verificarGanador(char tabAhumano[TAB][TAB], char tabAbot[TAB][TAB]);
void limpiarTablero(char tablero[TAB][TAB]);
void reiniciarJuego(char tabHumano[TAB][TAB], char tabAHumano[TAB][TAB], char tabBot[TAB][TAB], char tabABot[TAB][TAB]);
void inicializarTablero(char tablero[TAB][TAB]);


int main() {
    char tabHumano[TAB][TAB];
    char tabAHumano[TAB][TAB];
    char tabBot[TAB][TAB];
    char tabABot[TAB][TAB];

    char nombreJugador[20];
    
    int jugarDenuevo = 1;

    printf("BIENVENIDO A Oceanos en Confrontacion: El Duelo Naval!\n");
    printf("(mas conocido como batalla naval)\n\n");

    printf("Ingresa tu nombre:");
    scanf("%s",nombreJugador);
    printf("\n");

    while (jugarDenuevo) {
        reiniciarJuego(tabHumano, tabAHumano, tabBot, tabABot);

        // Posicionar barcos del Humano
        printf("\nPor favor selecciona y posiciona tus barcos:\n");
        posicionarBS(tabHumano);


        // Posicionar barcos del Bot
        printf("\nEl BOT esta posicionando sus barcos...\n");
        posicionarBBot(tabBot);

        while (1) {
            // Turno del Humano
            printf("\n+-+-+- Turno de ''%s'' -+-+-+\n",nombreJugador);
            printf("\nEste es el tablero de ataque tuyo:\n");
            
            mostrarTablero(tabAHumano);
            ataqueHumano(tabBot, tabAHumano);
            

            if (verificarGanador(tabAHumano, tabABot) == 1) {
                printf("\nHAS GANADO EL JUEGO! LO HAS HECHO MUY BIEN! :3\n");
                break;
            }

            // Turno del Bot
            printf("\n+-+-+- Turno del ''BOT'' -+-+-+\n");
            ataqueBot(tabHumano, tabABot);

            if (verificarGanador(tabAHumano, tabABot) == 2) {
                printf("\nEl BOT ha ganado el juego. Si quieres, inténtalo nuevamente! :D\n");
                break;
            }
        }

        printf("\nDeseas jugar nuevamente? (0 - No, 1 - S): ");
        scanf("%d", &jugarDenuevo);
    }

    return 0;
}

void reiniciarJuego(char tabHumano[TAB][TAB], char tabAHumano[TAB][TAB], char tabBot[TAB][TAB], char tabABot[TAB][TAB]) {
    inicializarTablero(tabHumano);
    inicializarTablero(tabAHumano);
    inicializarTablero(tabBot);
    inicializarTablero(tabABot);
}

void inicializarTablero(char tablero[TAB][TAB]) {
    int i = 0;
    while (i < TAB) {
        int j = 0;
        while (j < TAB) {
            tablero[i][j] = '-';
            j++;
        }
        i++;
    }
}

void limpiarTablero(char tablero[TAB][TAB]){
    // Reiniciar tableros para una nueva partida
    int i = 0;
    while (i < TAB) {
        int j = 0;
        while (j < TAB) {
            tablero[i][j] = '-';
            j++;
        }
        i++;
    }
}

void mostrarTablero(char tablero[TAB][TAB]) {
    printf("Tablero:\n");
    //printf("  1 2 3 4 5 6 7 8 9 10\n");
    
    //IMPRIME LAS POSICIONES POSIBLES
    int j = 1;
    printf("  ");
    while (j <= TAB)
    {
        printf("%d ",j);
        j++;
    }
    printf("\n");    

    int i = 0;
    while (i < TAB) {
        printf("%c ", 'A' + i);

        int j = 0;
        while (j < TAB) {
            char casilla = tablero[i][j];

            if (casilla == '-') {
                printf("%c ", '-');
            } else {
                printf("%c ", casilla);
            }

            j++;
        }

        printf("\n");
        i++;
    }

    printf("\n");
}


int validarPos(char tablero[TAB][TAB], char fila, int columna, int direccion, int tamBarco) {
    int numF = fila - 'A';

    int i = 0;
    while (i < tamBarco) {
        if (numF < 0 || numF >= TAB || columna < 0 || columna >=TAB ||
            tablero[numF][columna] != '-') {
            return 0;
        }

        if (direccion == 0) {
            if (columna + 1 >= TAB) {
                return 0;
            }
            columna++;
        } else {
            if (numF + 1 >= TAB) {
                return 0;
            }
            numF++;
        }

        i++;
    }
    return 1;
}

void colocarB(char tablero[TAB][TAB], char barco, char fila, int columna, int direccion, int tamBarco) {
  
    int numF = fila - 'A'; // Convierte la letra de la fila a un indice num?rico
    int i = 0;
    while (i < tamBarco) { // Itera a travas de las celdas del barco
        tablero[numF][columna] = barco; // Coloca el simbolo del barco en la casilla correspondiente
        if (direccion == 0) { // Si la direccion es horizontal
            columna++; // Incrementa la columna para la siguiente casilla del barco
        } else { // Si la direccion es vertical
            numF++; // Incrementa la fila para la siguiente casilla del barco
        }
        i++;
    }
}

void mostrarDisponibles(int colocados[], char nom[][20], int tamanos[]) {
    printf("\nAqui tienes la lista de barcos disponibles:\n");

    int i = 0;
    while (i < MAXBARCOS) {
        if (colocados[i] == 0) {
            printf("%d.- %s (%d celdas)\n", i + 1, nom[i], tamanos[i]);
        } else {
            printf("%d. No disponible! - %s (%d celdas)\n", i + 1, nom[i], tamanos[i]);
        }

        i++;
    }
}

int obtenerSB(int colocados[]) {
    printf("\nSelecciona el barco que quieras colocar en el tablero: \n ");
    int opcion;
    scanf("%d", &opcion);

    int i = 0;
    while (i < MAXBARCOS) {
        if (opcion < 1 || opcion > MAXBARCOS) {
            printf("La opcion no esta disponible. Por favor, selecciona un numero de barco valido.\n");
            return -1;
        }

        if (colocados[opcion - 1] == 1) {
            printf("YA LO SELECCIONASTE! Por favor, selecciona otro barco.\n");
            return -1;
        }

        i++;
    }

    return opcion;
}


void posicionarBS(char tablero[TAB][TAB]) {
    int barcosC = 0;

    // Definir los barcos disponibles con sus tamaoos y nom
    char barcos[MAXBARCOS] = {'P', 'B', 'D', 'S', 'T'};
    int tamanos[MAXBARCOS] = {5, 4, 3, 3, 2};
    char nom[MAXBARCOS][20] = {"Portaaviones", "Buque de Guerra", "Destructor", "Submarino", "Patrullero"};

    // Arreglo para almacenar el estado de colocacion de los barcos
    int colocados[MAXBARCOS] = {0};
    
    while (barcosC < MAXBARCOS) {
        mostrarDisponibles(colocados, nom, tamanos); // Mostrar los barcos disponibles

        int opcion = obtenerSB(colocados); // Obtener la seleccion de barco del jugador
        if (opcion == -1) {
            continue; // Si la seleccion es invalida, volver al inicio del ciclo
        }

        // Obtener los datos del barco seleccionado
        char barco = barcos[opcion - 1];
        //printf("Barco HUMANO: %c \n",barco);
        int tamBarco = tamanos[opcion - 1];
        //printf("EL BARCO ES DE TAMANO %d\n",tamBarco);
        char nomBarco[20];
        //printf("ESTOY COPIANDO: %s\n",nom[opcion - 1]);
        strcpy(nomBarco, nom[opcion - 1]);

        printf("Posiciona el barco %s .\n", nomBarco);

        mostrarTablero(tablero);

        // Posicionar el barco en el tablero
        char fila;
        int columna, direccion;

        while (1) {
            printf("Ingresa la fila  (A-J): ");
            scanf(" %c", &fila);
            fila = (fila >= 'a' && fila <= 'j') ? (fila - 'a' + 'A') : fila;

            if (fila < 'A' || fila > 'J') {
                printf("Fila invalida. Ingresa una fila entre A y J.\n");
                continue;
            }

            printf("Ingresa la columna  (1-10): ");
            scanf("%d", &columna);

            if (columna < 1 || columna > 10) {
                printf("Columna invalida. Ingresa una columna entre 1 y 10.\n");
                continue;
            }

            printf("Ingresa la direccion (0-horizontal, 1-vertical): ");
            scanf("%d", &direccion);

            if (direccion != 0 && direccion !=  1) {
                printf("Direccion invalida. Ingresa 0 para horizontal o 1 para vertical.\n");
                continue;
            }

            columna--;

            if (!validarPos(tablero, fila, columna, direccion, tamBarco)) {
                printf("Posicion invalida. Por favor, intenta nuevamente.\n");
            } else {
                break;
            }
        }
        
        colocarB(tablero, barco, fila, columna, direccion, tamBarco);

        // Actualizar el estado del barco
        mostrarTablero(tablero);

        colocados[opcion - 1] = 1;

        barcosC++;
    }
}

void posicionarBBot(char tablero[TAB][TAB]) {
    srand(time(NULL)); // Inicializar la semilla aleatoria

    int barcosC = 0;

    // Definir los barcos disponibles con sus tamaos y nom
    char barcos[MAXBARCOS] = {'P', 'B', 'D', 'S', 'T'}; //T es patrullero
    int tamanos[MAXBARCOS] = {5, 4, 3, 3, 2};
    char nom[MAXBARCOS][20] = {"Portaaviones", "Buque de Guerra", "Destructor", "Submarino", "Patrullero"};

    // Arreglo para almacenar el estado de colocacin de los barcos
    int colocados[MAXBARCOS] = {0};

    while (barcosC < MAXBARCOS) {
        int opcion = rand() % MAXBARCOS; // Generar una opcin aleatoria

        if (colocados[opcion] == 1) {
            continue; // Si el barco ya fue colocado, pasar a la siguiente iteracin
        }

        // Obtener los datos del barco seleccionado
        char barco = barcos[opcion];
        printf("Barco: %c ",barco);
        int tamBarco = tamanos[opcion];
        char nomBarco[20];
        strcpy(nomBarco, nom[opcion]);

        int fila, columna, direccion;

        // Generar aleatoriamente una posicin y direccion vlida para el barco
        while (1) {
            fila = rand() % TAB;
            columna = rand() % TAB;
            direccion = rand() % 2;

            int numF = fila;
            int numC = columna;

            int i = 0;
            while (i < tamBarco) {
                if (numF < 0 || numF >= TAB || numC < 0 || numC >= TAB || tablero[numF][numC] != '-') {
                    break;
                }

                if (direccion == 0) {
                    numC++;
                } else {
                    numF++;
                }

                i++;
            }

            if (i == tamBarco) {
                break;
            }
        }

        // Posicionar el barco en el tablero
        int numF = fila;
        int numC = columna;
        int i = 0;
        while (i < tamBarco) {
            tablero[numF][numC] = barco;

            if (direccion == 0) {
                numC++;
            } else {
                numF++;
            }

            i++;
        }

        colocados[opcion] = 1; // Actualizar el estado del barco a [Colocado]
        barcosC++;
    }
}

void marcarBHundido(char tabA[TAB][TAB], int fila, int columna) {
    char barco = tabA[fila][columna];
    int tamBarco = 0;

    int i = 0;
    while (i < TAB) {
        int j = 0;
        while (j < TAB) {
            if (tabA[i][j] == barco) {
                tamBarco++;
            }
            j++;
        }
        i++;
    }

    i = 0;
    while (i < TAB) {
        int j = 0;
        while (j < TAB) {
            if (tabA[i][j] == barco) {
                tabA[i][j] = 'H';
            }
            j++;
        }
        i++;
    }

    //printf("Que pena tu Barco '%c' se a hundido :c %d\n", barco, tamBarco);
}

void tenerUnAtaque(char* fila, int* columna) {
    int pasarAloSig = 1;
    while (pasarAloSig) {
        printf("Ingresa la fila para el ataque (A-J): \n");
        scanf(" %c", fila);
        *fila = (*fila >= 'a' && *fila <= 'j') ? (*fila - 'a' + 'A') : *fila;

        if (*fila < 'A' || *fila > 'J') {
            printf("Fila invalida. Ingresa una fila entre A y J: \n");
            continue;
        }

        printf("Ingresa la columna para el ataque (1-10): \n");
        scanf("%d", columna);

        if (*columna < 1 || *columna > 10) {
            printf("Columna invalida. Ingresa una columna entre 1 y 10.\n");
            continue;
        }

        (*columna)--;

        pasarAloSig = 0;
    }
}

/*void realizarAhumano(char tablero[TAB][TAB], char tabA[TAB][TAB], char fila, int columna) {
    // Verificar si la posicion de ataque ya ha sido atacada previamente
    if (tabA[fila - 'A'][columna] != '-') {
        printf("YA ATACASTE UNA VEZ, NO PUEDES ATACAR DE NUEVO AQU?. Por favor, elige otra.\n");
        return;  // Salir de la funci?n, ya que no se puede realizar el ataque en una posicion repetida
    }

    // Verificar si se ha acertado a un barco enemigo en la posicion de ataque
    if (tablero[fila - 'A'][columna] != '-') {
        printf("ATACASTE A UN BARCO ENEMIGO %c%d!\n", fila, columna + 1);
        tabA[fila - 'A'][columna] = 'A';  // Marcar la posicion de ataque como acertada en el tablero de ataque
        tablero[fila - 'A'][columna] = 'A';  // Marcar la posicion de ataque como acertada en el tablero del jugador

        // Verificar si se hundi? el barco
        int i = 0;
        int j;
        while (i < TAB) {
            j = 0;
            while (j < TAB) {
                if (tabA[i][j] == tabA[fila - 'A'][columna]) {
                    tabA[i][j] = 'H';
                }
                j++;
            }
            i++;
        }

        printf(">HUNDISTE EL BARCO %c!\n", tabA[fila - 'A'][columna]);
    } else {
        printf(">FALLASTE! Aqui no hay un barco en la posicion %c%d.\n", fila, columna + 1);
        
        tabA[fila - 'A'][columna] = 'F';  // Marcar la posicion de ataque como fallida en el tablero de ataque
    }
}*/

void ataqueHumano(char tablero[TAB][TAB], char tabA[TAB][TAB]) {
    char fila;
    int columna;

    // Obtener la fila y columna de ataque desde el usuario
    tenerUnAtaque(&fila, &columna);

    // Realizar el ataque del jugador en la posicion obtenida
    int numF = fila - 'A';
    int numC = columna;
    if (tabA[numF][numC] != '-') {
        printf("NO PUEDES ATACAR EN UN LUGAR QUE YA ATACASTE. Por favor, elige otra posicion.\n");
        return;
    }

    if (tablero[numF][numC] != '-') {
        printf(">ACERTASTE A UN BARCO ENEMIGO! En la posicion: %c%d!\n", fila, columna + 1);
        tabA[numF][numC] = 'A';
        tablero[numF][numC] = 'A';
        marcarBHundido(tabA, numF, numC);
        printf("Tablero HUMANO:\n");
        mostrarTablero(tabA);

    } else {
        printf(">FALLASTE! No acertaste en la posicion: %c%d.\n", fila, columna + 1);
        tabA[numF][numC] = 'F';
        printf("Tablero HUMANO:\n");
        mostrarTablero(tabA);
    }
}

void ataqueBot(char tablero[TAB][TAB], char tabA[TAB][TAB]) {
    int fila, columna;

    // Generar una posicion de ataque aleatoria hasta encontrar una posicion v?lida
    while (1) {
        fila = rand() % TAB;
        columna = rand() % TAB;

        // Verificar si la posicion de ataque es v?lida (no ha sido atacada previamente)
        if (tabA[fila][columna] == '-') {
            break;
        }
    }

    // Realizar el ataque del bot en la posicion generada
    if (tablero[fila][columna] != '-') {
        printf(">EL BOT HA ACERTADO A UN BARCO DE TU POSICI?N %c%d!\n", fila + 'A', columna + 1);
        tabA[fila][columna] = 'A';
        tablero[fila][columna] = 'A';
        marcarBHundido(tabA, fila, columna);
        mostrarTablero(tabA);
    } else {
        printf("EL BOT HA FALLADO SU ATAQUE A LA POSICI?N %c%d.\n", fila + 'A', columna + 1);
        tabA[fila][columna] = 'F';
        mostrarTablero(tabA);
    }
}

int verificarGanador(char tabAhumano[TAB][TAB], char tabAbot[TAB][TAB]) {
    int aciertosH = 0;
    int aciertosB = 0;

    int i = 0;
    while (i < TAB) {
        int j = 0;
        while (j < TAB) {
            if (tabAhumano[i][j] == 'H') {
                aciertosH++;
            }
            if (tabAbot[i][j] == 'H') {
                aciertosB++;
            }
            j++;
        }
        i++;
    }

    if (aciertosH >= MAXPUNTOS) {
        return 1; // Humano gan
    } else if (aciertosB >= MAXPUNTOS) {
        return 2; // Bot gan
    } else {
        return 0; // Juego en progreso
    }
}
