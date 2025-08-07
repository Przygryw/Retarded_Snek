#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>


#define XARENA 10
#define YARENA 10

char arena[XARENA][YARENA];
int length = 1;
char *snakeX = NULL;
char *snakeY = NULL;
char *snakeDirection = NULL;

//char snakeX[1] = {0};
//char snakeY[1] = {0};

char pointX;
char pointY;

char movement = 'D';
char Pmovement;

void generateArena()
{
    for(int x =0; x < XARENA; x++)
    {
        for(int y = 0; y < YARENA; y++)
        {
            if(x == 0 || x == XARENA-1) arena[x][y] = '.';
            else if(y == 0 || y == YARENA-1) arena[x][y] = '.';
            else arena[x][y] = ' ';
        }
    }   
}

void displayArena()
{
    for(int x =0; x < XARENA; x++)
    {
        for(int y = 0; y < YARENA; y++)
        {
            printf("%c", arena[x][y]);
        } printf("\n");
    } 
}
void generateObstacles()
{
    char obstacles = 0;
    int xrand;
    int yrand;
    while(obstacles < XARENA/2)
    {
        xrand=1+rand()%(XARENA-2);
        yrand=1+rand()%(YARENA-2);
        if(arena[xrand][yrand] != 'X') {arena[xrand][yrand] = 'X'; obstacles ++;}
    }
}

void snakePosition()
{
    int elementID = 0;
    bool  mark = 0;
    for(int x = 0; x < XARENA; x++)
    {
        mark = 0;
        for(int y = 0; y < YARENA; y++)
        {  
            elementID = 0;
            while(elementID < length)
            {
                if(x == snakeX[elementID] && y == snakeY[elementID]) 
                {
                    printf("#"); 
                    y+=1;
                }
                elementID++;
            }
            printf("%c", arena[x][y]);
        }printf("\n");
    } 
}

void snakeMovement()
{
    int elementID = 0;
    if(_kbhit())
    {
        char a;
        a = _getch();
        switch (a)
        {
            case 'w': movement = 'W'; break;
            case 's': movement = 'S'; break;
            case 'a': movement = 'A'; break;
            case 'd': movement = 'D'; break;
            default : break;
        }
    }
    if(Pmovement == 'W' && movement == 'S') movement = 'W';
    else if(Pmovement == 'A' && movement == 'D') movement = 'A';
    else if(Pmovement == 'D' && movement == 'A') movement = 'D';
    else if(Pmovement =='S' && movement == 'W') movement = 'S';

    
        for(int i =length-1; i > 0; i--)
        {
            snakeX[i] = snakeX[i-1];
            snakeY[i] = snakeY[i-1];
        }

        switch(movement)
        {
            case 'W': snakeX[0]--; if(snakeX[0] <= 0) snakeX[0] = XARENA-1; break;
            case 'S': snakeX[0]++; if(snakeX[0] >= XARENA) snakeX[0] = 1; break;
            case 'A': snakeY[0]--; if(snakeY[0] <= 0) snakeY[0] = YARENA-1; break;
            case 'D': snakeY[0]++; if(snakeY[0] >= YARENA) snakeY[0] = 1; break;
            default: break;
        }
}

bool snakeCollide()
{
    bool response = 0;
    int elementID = 1;
    for(int x =0; x < XARENA; x++)
    {
        
        for(int y = 0; y < YARENA; y++)
        {
            //Obstacle
            if(arena[x][y] == 'X' && (snakeX[0] == x && snakeY[0] == y)) response = 1;
        }
    } 
    while(elementID < length)
    {
        if(snakeX[elementID] == snakeX[0] && snakeY[elementID] == snakeY[0]) response = 1;
        elementID ++;
    }
    return response;
}
void addSnake()
{
    length ++;
    snakeX = realloc(snakeX,length*sizeof(char));
    snakeY = realloc(snakeY,length*sizeof(char));
    if(movement == 'W') 
    {
        snakeX[length-1] = snakeX[length-2]+=1; 
        snakeY[length-1] = snakeY[length-2];
    }
    else if(movement == 'S') 
    {
        snakeX[length-1] = snakeX[length-2]-=1; 
        snakeY[length-1] = snakeY[length-2];
    }
    else if(movement == 'D') 
    {
        snakeX[length-1] = snakeX[length-2]; 
        snakeY[length-1] = snakeY[length-2]+=1;
    }
    else if(movement == 'A') 
    {
        snakeX[length-1] = snakeX[length-2]; 
        snakeY[length-1] = snakeY[length-2]-=1;
    }
}

void generatePoint()
{
    bool clash;
    do
    {
        clash = 0;
        pointX = 1 + rand()%(XARENA-2);
        pointY = 1 + rand()%(YARENA-2);
        if(arena[pointX][pointY] == 'X') clash = 1;
    }while(clash != 0);

    arena[pointX][pointY] = 'o';
}


void FileOperation(int scoreGained)
{    
    printf("\n");
    FILE *f1;
    char names[5][5], score[5];
    f1 = fopen("HiScore.hs", "r");
    char errorCheck = 0;
    char wholeFile[47];
    char tmp;
    do
    {
        tmp = fgetc(f1);
        wholeFile[errorCheck] = tmp;
        errorCheck++;
    }while(tmp != EOF);
    while(errorCheck < 10) {printf("Error while reading the file\n");}
    //printf("%s", wholeFile);
    char unID = 0, charID = 0, uID = 0;
    char status = 'e';
    int power = 1;
    char s = 0;
    while(unID < errorCheck)
    {
        if(wholeFile[unID] == '.') {status = 'u'; unID++;}
        else if (wholeFile[unID] == ',') {status = 's'; unID++;}

        if(status == 'u') names[uID][charID++] = wholeFile[unID]; 
        else if(status == 's') {s += (char)(pow(10,power--)*(wholeFile[unID]-48));}
        if(charID == 5 && power < 0) {charID = 0; score[uID] = s;  uID++; power = 1; s = 0; printf("\n");}
        unID++;
    }
    printf("\n");
    /*
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            printf("%c",names[i][j]);
        }printf("| %i", score[i]);printf("\n"); 
    }*/
    //CHECK SCORES
    status = 10;
    unID = 4;
    while(status == 10 || unID >= 0)
    {
        if(scoreGained > score[unID]) status = unID;
        unID --;
    }

    if(status != 10 && status >=0)
    {
                //OVERWRITE REST
        for(int i = 4; i > status; i--)
        {
            score[i] = score[i-1];
        }
        score[status] = scoreGained;
        char userName[5];
        do
        {
            printf("\nEnter player name (5 characters): ");
            scanf("%s", &userName);
        } while (strlen(userName) != 5);
        for(int i = 0; i < 5; i++) names[status][i] = userName[i];

        
    }
    else printf("\nNo record, try again!");
    //printf("Status: %i\n", status);

    //SAVE TO FILE
    f1 = fopen("HiScore.hs", "w");
    for(int i =0; i < 5; i++)
    {
        fprintf(f1,".");
        for(int j =0; j < 5; j++) fprintf(f1,"%c", names[i][j]);
        fprintf(f1,",");
        if(score[i] < 10) fprintf(f1,"0%i", score[i]);
        else fprintf(f1,"%i", score[i]);
    }
    fprintf(f1,"|\0");

    printf("\nCurrent top Scores:\n");
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            printf("%c",names[i][j]);
        }printf("| %i", score[i]);printf("\n"); 
    }
}

int main()
{
    srand(time(NULL));
    bool lost = 0;
    snakeX = malloc(length * sizeof(char));
    snakeY = malloc(length * sizeof(char));
    snakeX[0] = 0;
    snakeY[0] = 0;
    //TESTS AND SETTINGS
    generateArena();
    displayArena();
    generateObstacles();
    generatePoint();
    //displayArena();
    while(lost != 1)
    {
        snakePosition();
        if(movement == 'S' || movement == 'W') Sleep(350);
        else Sleep(200);
        snakeMovement();
        lost = snakeCollide();
        if(snakeX[0] == pointX && snakeY[0] == pointY) 
        {
            addSnake();
            arena[pointX][pointY] = ' ';
            generatePoint();
        }
        system("CLS");
        Pmovement = movement; 
    }
    printf("You lost!\n Points: %i", length-1);
    FileOperation(length-1);
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
}
