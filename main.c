#include <stdio.h>
#include <stdbool.h>
#define BOARD_SIZE 10
#define NUMERO_DE_NAVIOS 5

typedef struct {
    int x;
    int y;
} Coordinate;

typedef struct {
    Coordinate position;
    bool isSunk;
} Ship;

void iniciar(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0; 
        }
    }
}

void print(int board[BOARD_SIZE][BOARD_SIZE]) {
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                printf("~ ");
            } else if (board[i][j] == 1) {
                printf("N ");
            } else if (board[i][j] == 2) {
                printf("X ");
            } else if (board[i][j] == 3) {
                printf("O ");
            }
        }
        printf("\n");
    }
}

bool validacao(int x, int y) {
    return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE);
}

bool ocupado(int board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    return board[x][y] == 1;
}

void lugarnavios(int board[BOARD_SIZE][BOARD_SIZE], Ship ships[NUMERO_DE_NAVIOS]) {
    for (int i = 0; i < NUMERO_DE_NAVIOS; i++) {
        int x, y;
        printf("Informe as coordenadas para o Navio %d (x y): ", i + 1);
        scanf("%d %d", &x, &y);

        if (validacao(x, y) && !ocupado(board, x, y)) {
            board[x][y] = 1; 
            ships[i].position.x = x;
            ships[i].position.y = y;
            ships[i].isSunk = false;
        } else {
            printf("Coordenadas inválidas. Tente novamente.\n");
            i--;
        }
    }
}

bool perdeu(Ship ships[NUMERO_DE_NAVIOS]) {
    for (int i = 0; i < NUMERO_DE_NAVIOS; i++) {
        if (!ships[i].isSunk) {
            return false;
        }
    }
    return true;
}

void tiro(int board[BOARD_SIZE][BOARD_SIZE], Ship ships[NUMERO_DE_NAVIOS], int x, int y) {
    if (validacao(x, y)) {
        if (board[x][y] == 1) {
            printf("Acertou!\n");
            board[x][y] = 2; 
            for (int i = 0; i < NUMERO_DE_NAVIOS; i++) {
                if (ships[i].position.x == x && ships[i].position.y == y) {
                    ships[i].isSunk = true;
                    break;
                }
            }
        } else {
            printf("Errou!\n");
            board[x][y] = 3; 
        }
    } else {
        printf("Coordenadas inválidas. Tente novamente.\n");
    }
}

int main() {
    int player1Board[BOARD_SIZE][BOARD_SIZE];
    int player2Board[BOARD_SIZE][BOARD_SIZE];
    Ship player1Ships[NUMERO_DE_NAVIOS];
    Ship player2Ships[NUMERO_DE_NAVIOS];

    iniciar(player1Board);
    iniciar(player2Board);

    printf("Jogador 1, posicione seus navios:\n");
    lugarnavios(player1Board, player1Ships);

    printf("Jogador 2, posicione seus navios:\n");
    lugarnavios(player2Board, player2Ships);

    int currentPlayer = 1;

    while (true) {
        printf("Turno do Jogador %d:\n", currentPlayer);
        printf("Seu tabuleiro:\n");
        print(currentPlayer == 1 ? player1Board : player2Board);

        int x, y;
        printf("Informe as coordenadas para atirar (x y): ");
        scanf("%d %d", &x, &y);

        if (currentPlayer == 1) {
            tiro(player2Board, player2Ships, x, y);
        } else {
            tiro(player1Board, player1Ships, x, y);
        }

        if (perdeu(currentPlayer == 1 ? player2Ships : player1Ships)) {
            printf("Jogador %d venceu!\n", currentPlayer);
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1; 
    }

    return 0;
}

