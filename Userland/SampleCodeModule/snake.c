#include <colors.h>
#include <time.h>

#define WIDTH 70
#define HEIGHT 70
#define MAXDIM 200

#define PIXELWIDTH (get_scrWidht() / WIDTH)
#define PIXELHEIGHT (get_scrHeight() / HEIGHT)
#define MAX_BUFFER 254

#define PLAYER1_UP 'w'
#define PLAYER1_DOWN 's'
#define PLAYER1_LEFT 'a'
#define PLAYER1_RIGHT 'd'

#define PLAYER2_UP 'i'
#define PLAYER2_DOWN 'k'
#define PLAYER2_LEFT 'j'
#define PLAYER2_RIGHT 'l'


static unsigned long int next = 1;


void singlePlayerSnake();
void mpSnake();

int rand() {
    time_t tiempo;
    time(&tiempo);
    unsigned int semilla = (unsigned int)tiempo;
    
    // Usa la semilla para generar un número pseudoaleatorio en el rango [0, 70).
    unsigned int numeroAleatorio = (semilla % 68) + 1;

}

int finish;
int foodPosX, foodPosY;

struct Position{
    int x;
    int y;
};

typedef struct Player{
    int currentX;
    int currentY;
    int alive;
    char body;
    int direction;
    int length;
    //Revisar Color color;
    struct Position position[MAXDIM];
}Player;




void drawBoard(char board[HEIGHT][WIDTH], Player *player) {
    //Color currentColor;
    int i, j;
    
    // Recorre las filas y columnas del tablero
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            // Si la celda está vacía, establece el color de fondo en blanco
            if (board[i][j] == ' ') {
                //currentColor = WHITE;
            }
            // Si la celda contiene al jugador, usa su color
            else if (i == player-> currentY && j == player-> currentX) {
                //currentColor = player-> color;
            }
            // Si la celda contiene comida, usa un color específico
            else if (board[i][j] == '*') {
              //  currentColor = RED;
            }
            // Dibuja un rectángulo en la posición actual con el color correspondiente
            //drawRectangle(j * PIXELWIDTH, i * PIXELHEIGHT, PIXELWIDTH - 1, PIXELHEIGHT - 1, currentColor);
        }
    }

}

void createFood(char snake[HEIGHT][WIDTH], int *foodPosX, int *foodPosY){
    do{
        *foodPosX = rand();
        *foodPosY = rand(); 
    } while (snake[*foodPosY][*foodPosX] != '0');

    snake[*foodPosY][*foodPosX] = '#';
}

void initializeGame(char snake[HEIGHT][WIDTH], Player *player){
    player->currentX = WIDTH/2;
    player->currentY = HEIGHT/2;
    player->direction = PLAYER1_LEFT;
    player->alive = 1;
    player->body = '*';
   //revisar color player->playerColor
    player->length = 3;

    snake[player->currentY][player->currentX] = player->body;

    int i,j;

    for(i = 0; i < HEIGHT ; i++){
        for (j = 0 ; j < WIDTH; j++){
            snake[i][j] = '0'; //revisar falopeada de iker 
        }
    }

    createFood(snake,&foodPosX,&foodPosY);
}


void playerInput(struct Player *player,char up, char down, char left, char right) {
    char key;
    key = getChar();

    if (key == up && player->direction != down) {
        player->direction = up;
    } else if (key == down && player->direction != up) {
        player->direction = down;
    } else if (key == left && player->direction != right) {
        player->direction = left;
    } else if (key == right && player->direction != left) {
        player->direction = right;
    }
}

void eraseTail(char board[HEIGHT][WIDTH], int i, int j) {
    board[i][j] = '0';
}

//revisar eraseTail call
void snakeMovement(char snake[HEIGHT][WIDTH], Player *player) {
    if (player->length >= 1) {
        eraseTail(snake, player->position[player->length - 1].x, player->position[player->length - 1].y);
        for (int i = player->length - 1; i > 0; i--) {
            player->position[i] = player->position[i - 1];
        }
    }
}

void gameLogic(char snake[HEIGHT][WIDTH], Player * player, char up, char down, char left, char right){

    if (player->direction == up) {
        player->currentY--;
    } else if (player->direction == down) {
        player->currentY++;
    } else if (player->direction == left) {
        player->currentX--;
    } else if (player->direction == right) {
        player->currentX++;
    }

    // check self collision
    for (int i = 0; i < player->length; i++) {
        if (player->currentX == player->position[i].y && player->currentY == player->position[i].x) {
            player->alive = 0;
            break;
        }
    }
    

    // check snake border collision
    if (player-> currentX < 0 || player-> currentX >= WIDTH  || player-> currentY < 0 || player-> currentY >= HEIGHT ) {
        player->alive = 0;
    }
    

    if (!player->alive) {
        finish = 1;
        // player->playerColor = BLACK;
    }

    if (player-> currentX == foodPosX && player->currentY == foodPosY) {
        player->length++;
        createFood(snake, &foodPosX, &foodPosY);
        //sys_playSound(1500);
        //sys_mute();
    }

    if (player->alive) {
        snake[player->currentY][player->currentX] = player->body;
        player->position[0].y = player->currentY;
        player->position[0].x = player->currentX;
    }
}

void snakeFunctionality(char snake[HEIGHT][WIDTH], Player *player, char up, char down, char left, char right) {
    gameLogic(snake,player,up,down,left,right);

    drawBoard(snake, player);
}

///// IMPLEMENTATION 2 PLAYERS ////

void initializeGameMP(char snake[HEIGHT][WIDTH], Player *player1, Player *player2){
    player1->currentX = WIDTH/4;
    player1->currentY = HEIGHT/2;
    player1->direction = PLAYER1_LEFT;
    player1->alive = 1;
    player1->body = '*';
   //revisar color player->playerColor
    player1->length = 3;

    player2->currentX = 3 * WIDTH/4;
    player2->currentY = HEIGHT/2;
    player2->direction = PLAYER1_UP;
    player2->alive = 1;
    player2->body = '⁰';
   //revisar color player->playerColor
    player2->length = 3;

    snake[player1->currentY][player1->currentX] = player1->body;
    snake[player2->currentY][player2->currentX] = player2->body;

    int i,j;

    for(i = 0; i < HEIGHT ; i++){
        for (j = 0 ; j < WIDTH; j++){
            snake[i][j] = '0'; //revisar falopeada de iker 
        }
    }

    createFood(snake,&foodPosX,&foodPosY);

}

void snakeFunctionality2(char snake[HEIGHT][WIDTH], Player *player, char up, char down, char left, char right) {
    gameLogic(snake,player,up,down,left,right);

}

void drawBoard2(char board[HEIGHT][WIDTH], Player *player1, Player *player2) {
    //Color currentColor;
    int i, j;
    
    // Recorre las filas y columnas del tablero
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            // Si la celda está vacía, establece el color de fondo en blanco
            if (board[i][j] == ' ') {
                //currentColor = WHITE;
            }
            // Si la celda contiene al jugador, usa su color
            else if (i == player1-> currentY && j == player1-> currentX) {
                //currentColor = player1-> color;
            }else if(i == player1 -> currentY && j == player2 -> currentX){
                // currentColor = player2 -> color
            }
            // Si la celda contiene comida, usa un color específico
            else if (board[i][j] == '*') {
              //  currentColor = RED;
            }
            // Dibuja un rectángulo en la posición actual con el color correspondiente
            //drawRectangle(j * PIXELWIDTH, i * PIXELHEIGHT, PIXELWIDTH - 1, PIXELHEIGHT - 1, currentColor);
        }
    }

}

////////// 1 player startup //////////
void snake(){
    sys_clean_screen();
    singlePlayerSnake();
}


void singlePlayerSnake(){
    char snake[HEIGHT][WIDTH];

    Player player;

    initializeGame(snake,&player);

    finish = 0;

    while(!finish){
        playerInput(&player,PLAYER1_UP,PLAYER1_DOWN,PLAYER1_LEFT,PLAYER1_RIGHT);
        snakeMovement(snake,&player);
        snakeFunctionality(snake, &player,PLAYER1_UP,PLAYER1_DOWN,PLAYER1_LEFT,PLAYER1_RIGHT);
        // verificar si se mueve muy rapido la snake, en ese caso agregar un wait()
    }
   // hay que implementar lo que pasa cuando termina el juego
   
}


////////// 2 players startup //////////

void snake2(){
    sys_clean_screen();
    mpSnake();
}

void mpSnake(){
    char snake[HEIGHT][WIDTH];

    Player player1, player2;

    initializeGameMP(snake, &player1, &player2);

    finish = 0;

    while(!finish){
        playerInput(&player1,PLAYER1_UP,PLAYER1_DOWN,PLAYER1_LEFT,PLAYER1_RIGHT);
        snakeMovement(snake,&player1);
        snakeFunctionality2(snake, &player1,PLAYER1_UP,PLAYER1_DOWN,PLAYER1_LEFT,PLAYER1_RIGHT);
       
        playerInput(&player2,PLAYER2_UP,PLAYER2_DOWN,PLAYER2_LEFT,PLAYER2_RIGHT);
        snakeMovement(snake,&player2);
        snakeFunctionality2(snake, &player2,PLAYER2_UP,PLAYER2_DOWN,PLAYER2_LEFT,PLAYER2_RIGHT);
        
        drawBoard2(snake, &player1, &player2);
        
        // verificar si se mueve muy rapido la snake, en ese caso agregar un wait()    
    }
    
}