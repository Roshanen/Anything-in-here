#include <stdio.h>
#include <string.h>

enum State {
    play,
    bonus,
    end,
    foul,
    miss
};

const char *balls[][2] = {{"W","0"},{"R","1"},{"R","1"},{"R","1"},{"R","1"},{"R","1"},{"Y","2"},{"G","3"},{"O","4"},{"Bl","5"},{"P","6"},{"Br","7"}};
int topBallScore = 0;
char alpha[] = "abcdefghijkl";
int onBoard[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

int maxBalls = 12;
int remainBalls = 12;
int lowestIndex = 1;
int score = 0;
enum State gameState = end;

void displayOnBoardBalls();
void displayOnBoardScores();
void displayOnBoardAlpha();
void displayPlayerScore();
void displayGameStat();

void initGame(){
    for (int i = 0; i < maxBalls; i++){
        onBoard[i] = 1;
    }
    remainBalls = maxBalls;
    lowestIndex = 1;
    score = 0;
    displayGameStat();
}

void continueGame(){
    displayGameStat();
    gameState = play;
}

void displayAtMainMenu(){
    printf("--------------------------\n");
    printf("        Game Start\n");
    printf("--------------------------\n");
    printf(" 1. Reset Game\n");
    printf(" 2. Continue & Play Game\n");
    printf(" q. Exit\n");
    printf("--------------------------\n");
}

void displayOnBoardBalls(){
    for (int i = 0; i < maxBalls; i++){
        if (onBoard[i]){
            printf("%-3s", balls[i][0]);
        }
    }
    printf("\n");
}

void displayOnBoardScores(){
    for (int i = 0; i < maxBalls; i++){
        if (onBoard[i]){
            printf("%-3s", balls[i][1]);
        }
    }
    printf("\n");
}

void displayOnBoardAlpha(){
    for (int i = 0; i < remainBalls; i++){
        printf("%-3c", alpha[i]);
    }
    printf("\n");
}

void displayPlayerScore(){
    printf("Your Score is : %d\n\n", score);
}

void displayWhenFouled(){
    printf("--------------------------\n");
    printf("\033[31m");
    printf("        Game Foul\n");
    printf("\033[0m");
    printf("--------------------------\n\n");
    displayAtMainMenu();
}

void displayWhenMissed(){
    printf("--------------------------\n");
    printf("\033[31m");
    printf("        Next Turn\n");
    printf("\033[0m");
    printf("--------------------------\n\n");
    displayAtMainMenu();
}

void displayWhenEnded(){
    printf("--------------------------\n");
    printf("\033[32m");
    printf("        Game End\n");
    printf("\033[0m");
    printf("--------------------------\n\n");
    displayAtMainMenu();
}

void displayGameStat(){
    displayOnBoardBalls();
    displayOnBoardScores();
    displayOnBoardAlpha();
    displayPlayerScore();
}

int aToi(const char *ch){
    return (ch[0] - '0');
}

int foundBall(int index){
    int temp = 0;
    while (index > 0){
        temp++;
        if (onBoard[temp] == 1){
            index--;
        }
    }
    return temp;
}

int checkValidShoot(int index){
    if (index == 0){
        topBallScore = 7;
        return 0;
    }

    index = foundBall(index);
    topBallScore = aToi(balls[index][1]);

    if (gameState == play){
        if (aToi(balls[lowestIndex][1]) == aToi(balls[index][1])){
            if (aToi(balls[lowestIndex][1]) == 1){
                gameState = bonus;
            }
            onBoard[lowestIndex++] = 0;
            remainBalls--;
            return 1;
        }
        else{
            return 0;
        }
    }
    else if (gameState == bonus){
        gameState = play;
        if (aToi(balls[index][1]) != 1 && aToi(balls[index][1]) != 7){
            return 1;
        }
        else{
            onBoard[lowestIndex++] = 0;
            remainBalls--;
            return 0;
        }
    }
}

char promptInput(){
    printf("\033[33m");
    char ch = '\0';
    scanf("%c", &ch);
    printf("\033[0m");
    fflush(stdin);
    return ch;
}

int main(void){
    displayAtMainMenu();
    while (1){
        printf("Enter your choice : ");
        char ch = promptInput();

        if (ch == '1'){
            initGame();
        } else if (ch == '2'){
            continueGame();
        } else if (ch == 'q'){
            break;
        }

        while (gameState == play || gameState == bonus){
            printf("Enter an Alphabet to Shoot : ");
            ch = promptInput();
            int index = ch - 'a';

            if (index >= remainBalls || index < 0){
                gameState = miss;
            }
            else if (checkValidShoot(index)){
                score += topBallScore;
            }
            else {
                score -= topBallScore;
                gameState = foul;
            }

            if (remainBalls <= 1){
                gameState = end;
            }

            displayGameStat();
            
            if (gameState == foul){
                displayWhenFouled();
            }
            else if (gameState == miss){
                displayWhenMissed();
            }
            else if (gameState == end){
                displayWhenEnded();
            }
        }
    }
    return 0;
}