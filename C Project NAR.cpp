#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

int alive = 1;
    int enemy = 1;
struct score{
    char name[10];
    int score;
};

void printMap(char map[][33]){
    for(int i = 0; i < 17; i++){
        for(int j = 0; j < 33; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

void genWall(char map[][33], int walls, int doorLoc[]){
    srand(time(0));
    int door = 1;
    while(walls > 0){
    for(int i = 0; i < 17; i++){
        for(int j = 0; j < 33; j++){
                //printf("%d || %d\n", i, j);
                if(map[i][j] == ' '){
                    //printf("%d\n", walls);
                if((rand() % 100) <= 5){
                        if(((rand() % 100) <= 10) || door == 1){
                            doorLoc[0] = i;
                            doorLoc[1] = j;
                            map[i][j] = 'H';
                            walls--;
                            door = 0;
                        }
                        else{
                        map[i][j] = 'H';
                        walls--;
                }
            }
            if(walls == 0) break;
        }
        if(walls == 0) break;
    }
}
}
}

void genEnemy(char map[][33], int enemies, int enemPos[][2]){
    srand(time(0));
    int counter = 0;
    while(enemies > 0){
        for(int i = 0; i < 17; i++){
            for(int j = 0; j < 33; j++){
                if(map[i][j] == ' '){
                    if((rand() % 100) <= 5){
                        map[i][j] = 'X';
                        enemPos[counter][0] = i;
                        enemPos[counter][1] = j;
                        enemies--;
                        counter++;
                    }
                }
                else continue;
                if(enemies == 0) break;
            }
        if(enemies == 0) break;
        }
}
}

void printBoard(int level, int score, char map[][33]){
        printf("%16s : %d\n", "LEVEL", level);
        printMap(map);
        printf("%POINT : %d\n", score);
}

void movEnemy(int enemPos[][2], char map[][33], int enemy){
    srand(time(0));
    for(int i = 0; i < enemy; i++){
            int x = enemPos[i][0];
            int y = enemPos[i][1];
            if(alive == 0) break;
    int moved = 0;
    while(moved == 0){
        int dir = rand() % 4;
    switch(dir){
        case 0:{
            if((x - 1) < 0) break;
            else if(map[x - 1][y] == '*') break;
            else if(map[x - 1][y] == ' '){
               // printf("%d | %d |UP\n", enemPos[i][0], enemPos[i][1]);
                map[x - 1][y] = 'X';
                map[x][y] = ' ';
                enemPos[i][0] = x - 1;
                moved = 1;
            }
            else if(map[x - 1][y] == '@'){
                alive = 0;
                moved = 1;
            }
        break;
        }
        case 1:{
            if((x + 1) > 32) break;
            else if(map[x + 1][y] == '*') break;
            else if(map[x + 1][y] ==' '){
                //printf("%d | %d |DOWN\n", enemPos[i][0], enemPos[i][1]);
                map[x + 1][y] = 'X';
                map[x][y] = ' ';
                enemPos[i][0] = x + 1;
                moved = 1;
            }
            else if(map[x + 1][y] == '@'){
                alive = 0;
                moved = 1;
            }
        break;
        }
        case 2:{
            if((y - 1) < 0) break;
            else if(map[x][y - 1] == '*') break;
            else if(map[x][y - 1] == ' '){
                //printf("%d | %d |LEFT\n", enemPos[i][0], enemPos[i][1]);
                map[x][y - 1] = 'X';
                map[x][y] = ' ';
                enemPos[i][1] = y - 1;
                moved = 1;
            }
            else if(map[x][y - 1] == '@'){
                alive = 0;
                moved = 1;
            }
        break;
        }
        case 3:{
            if((y + 1) > 32) break;
            else if(map[x][y - 1] == '*') break;
            else if(map[x][y + 1] == ' '){
                //printf("%d | %d |RIGHT\n", enemPos[i][0], enemPos[i][1]);
                map[x][y + 1] = 'X';
                map[x][y] = ' ';
                enemPos[i][1] = y + 1;
                moved = 1;
            }
            else if(map[x][y + 1] == '@'){
                alive = 0;
                moved = 1;
            }
        }
    }

}
}
}

void insertionSort(struct score data[], int num){
    int i, j;
    struct score key;
        for (i = 0; i < num; i++) {
            key = data[i];
            j = i - 1;
                while (j >= 0 && strcmp(data[j].name, key.name) > 0) {
                    data[j + 1] =  data[j];
                    j = j - 1;
                }
            data[j + 1] = key;
}

}

void overWriteSave(struct score data[], int num){
    FILE *newestSave = fopen("save.txt", "w");
    printf("NUM %d\n", num);
    for(int i = 0; i < num; i++){
        fprintf(newestSave, "%s#%d\n", data[i].name, data[i].score);
        printf("%s#%d\n", data[i].name, data[i].score);
    }
    fclose(newestSave);
}

int bombBoom(int x, int y, int doorLoc[], int score, int level, int enemPos[][2], char map[][33]){
    int mov[8][2] ={{-1, -1}, {1, 1},
                    {1, -1}, {-1, 1},
                    {0, -1}, {0, 1},
                    {-1, 0}, {1, 0}};
    map[x][y] = ' ';
    for(int i = 0; i < 8; i++){
        if((map[x + mov[i][0]][y + mov[i][1]]) == 'H'){

            if(((x + mov[i][0]) == doorLoc[0]) && ((y + mov[i][1]) == doorLoc[1])){
                map[x + mov[i][0]][y + mov[i][1]] = 'o';
                score += level * 50;
            }
            else{
                map[x + mov[i][0]][y + mov[i][1]] = ' ';
                score += level * 50;
            }
        }
        else if(map[x + mov[i][0]][y + mov[i][1]] == 'X'){
            map[x + mov[i][0]][y + mov[i][1]] = ' ';
            int j;
            for(j = 0; j < enemy; j++){
                if((enemPos[j][0] == (x  + mov[i][0])) && enemPos[j][1] == (y + mov[i][1])) break;
            }
            for(int k = j; k < enemy; k++){
                enemPos[k][0] = enemPos[k + 1][0];
                enemPos[k][1] = enemPos[k + 1][1];
            }
            enemy--;
            score += level * 100;
    }
        else if(map[x + mov[i][0]][y + mov[i][1]] == '@'){
            alive = 0;
        }
}
return score;
}

int main(){
    srand(time(0));
    struct score playerInfo[20];
    FILE *save = fopen("save.txt", "r");
    if(save == NULL){
        printf("SAVE FILE NOT FOUND!\n");
        printf("CREATING A NEW ONE\n");
        FILE *newSave = fopen("save.txt", "w");
        fclose(newSave);
        FILE *save = fopen("save.txt", "r");
        getchar();

    }
    int saveNum = 0;
    while(fscanf(save, "%[^#]#%d\n", playerInfo[saveNum].name, &playerInfo[saveNum].score) != EOF) saveNum++;
    FILE *map = fopen("map.txt", "r");
    if(map == NULL){
            printf("MAP NOT FOUND!\n");
            return 0;
    }
    char cleanMap[17][33];
    char game[17][33];
    int level = 1;
    int line = 0;
    while(feof(map) == 0){
          fscanf(map, "%[^\n]\n", cleanMap[line]);
            line++;
    }

    int doorLoc[2];
    int score = 0;
    int enemPos[50][2];
    int gameStart = 1;
    int walls;
    int exitGame = 0;
    int player[2] = {1, 1};
    game[1][1] = '@';
    char direction;
    char prevDir;
    int bombTimer[5]= {0};
    int bombloc[5][2] = {0};
    int bombCount = 0;
    while(alive == 1){

        if(gameStart == 1){
            memcpy(game, cleanMap, 17 *33 *sizeof(char));
            game[1][1] = '@';
            player[0] = 1;
            player[1] = 1;
            walls = ((((rand()) % 10) + 9) + (level * 10));
            genWall(game, walls, doorLoc);
            enemy = level + 1;
            genEnemy(game, enemy, enemPos);
            gameStart = 0;
        }
        system("cls");
        printBoard(level, score, game);
        prevDir = direction;
        direction = getch();

    switch(direction){
        case 'w':{
            if((player[0] - 1) < 0) break;
            else if(game[player[0] - 1][player[1]] == ' '){
                game[player[0] - 1][player[1]] = '@';
                game[player[0]][player[1]] = ' ';
                player[0] -= 1;
            }
            else if(game[player[0] - 1][player[1]] == 'o'){
                gameStart = 1;
                level++;
            }
        break;
        }
        case 's':{
            if((player[0] + 1) > 32) break;
            else if(game[player[0] + 1][player[1]] == ' '){
                game[player[0] + 1][player[1]] = '@';
                game[player[0]][player[1]] = ' ';
                player[0] += 1;
            }
            else if(game[player[0] + 1][player[1]] == 'o'){
                gameStart = 1;
                level++;
            }

        break;
        }
        case 'a':{
            if((player[1] - 1) < 0) break;
            else if(game[player[0]][player[1] - 1] == ' '){
                game[player[0]][player[1] - 1] = '@';
                game[player[0]][player[1]] = ' ';
                player[1] -= 1;
            }
            else if(game[player[0]][player[1] - 1] == 'o'){
                gameStart = 1;
                level++;
            }

        break;
        }
        case 'd':{
            if((player[1] + 1) > 32) break;
            else if(game[player[0]][player[1] + 1] == ' '){
                game[player[0]][player[1] + 1] = '@';
                game[player[0]][player[1]] = ' ';
                player[1] += 1;
            }
            else if(game[player[0]][player[1] + 1] == 'o'){
                gameStart = 1;
                level++;
            }
            break;
        }
        case 27:{
            char input;
            while(input != 3){
            system("cls");
            printf("1. Back\n");
            printf("2. View Highscores\n");
            printf("3. Exit\n");
            printf(">>");
            scanf("%c", &input);
            getchar();
            if(input == '1'){
                system("cls");
                printBoard(level, score, game);
                printf("Press any button to continue\n");
                getchar();
                break;
            }
            else if(input =='2'){
                printf("%-8s%8s | SCORE\n", " ", "NAME");
                    for(int i = 0; i< saveNum; i++){
                    printf("%s | %d\n", playerInfo[i].name, playerInfo[i].score);
                }
                printf("Press any button to continue\n");
                getchar();
            }
            else if(input == '3'){
                char inputName[20];
                int length = 0;
                while(length < 3){
                    printf("ENTER NAME : ");
                    scanf("%[^\n]", inputName);
                    getchar();
                    length = strlen(inputName);
                    if(length < 2){
                            printf("INVALID NAME\n");
                            printf("Press any button to continue\n");
                            getchar();
                            length = 0;
                    }
                    for(int j = 0; j < length; j++){
                        if(inputName[j] == ' '){
                            printf("INVALID NAME\n");
                            printf("Press any button to continue\n");
                            getchar();
                            length = 0;
                        }
                    }
                }
                inputName[0] = toupper(inputName[0]);
                strcpy(playerInfo[saveNum].name, inputName);
                playerInfo[saveNum].score = score;
                saveNum++;
                printf("SUCCESS SAVE\n");
                printf("Press any button to continue\n");
                insertionSort(playerInfo, saveNum);
                overWriteSave(playerInfo, saveNum);
                getchar();
                exitGame = 1;
                break;
            }
        }
        break;
    }
        case ' ':{
    switch(prevDir){
        case 'w':{
            if((player[0] - 1) < 0) break;
            else if(game[player[0] - 1][player[1]] == ' '){
                game[player[0] - 1][player[1]] = '*';
                bombloc[bombCount][0] = player[0] - 1;
                bombloc[bombCount][1] = player[1];
                bombTimer[bombCount] = 2;
                bombCount++;
            }

        break;
        }
        case 's':{
            if((player[0] + 1) > 32) break;
            else if(game[player[0] + 1][player[1]] == ' '){
                    printf("TEST\n");
                game[player[0] + 1][player[1]] = '*';
                bombloc[bombCount][0] = player[0] + 1;
                bombloc[bombCount][1] = player[1];
                bombTimer[bombCount] = 2;
                bombCount++;
            }

        break;
        }
        case 'a':{
            if((player[1] - 1) < 0) break;
            else if(game[player[0]][player[1] - 1] == ' '){
                game[player[0]][player[1] - 1] = '*';
                bombloc[bombCount][0] = player[0];
                bombloc[bombCount][1] = player[1] - 1;
                bombTimer[bombCount] = 2;
                bombCount++;
            }

        break;
        }
        case 'd':{
            if((player[1] + 1) > 32) break;
            else if(game[player[0]][player[1] + 1] == ' '){
                game[player[0]][player[1] + 1] = '*';
                bombloc[bombCount][0] = player[0];
                bombloc[bombCount][1] = player[1] + 1;
                bombTimer[bombCount] = 2;
                bombCount++;
            }
            break;
        }
        default:{
            break;
        }
        }
        break;
    }
    }

        for(int k = 0; k < bombCount; k++){
            if(bombTimer[k] == 0){
                score = bombBoom(bombloc[k][0], bombloc[k][1], doorLoc,score, level, enemPos, game);
                for(int q = k; q < bombCount; q++){
                    bombloc[q][0] = bombloc[q + 1][0];
                    bombloc[q][1] = bombloc[q + 1][1];
                    bombTimer[q] = bombTimer[q + 1];
                }
                bombCount--;
            }
            else bombTimer[k]--;
        }
        if(exitGame == 1) break;
        movEnemy(enemPos, game, enemy);
        system("cls");
        printBoard(level, score, game);
        if(alive == 0){
            system("cls");
            printf("YOU LOST\n");
            char inputName[20];
                int length = 0;
                while(length < 3){
                    printf("ENTER NAME : ");
                    scanf("%[^\n]", inputName);
                    getchar();
                    length = strlen(inputName);
                    if(length < 2){
                            printf("INVALID NAME\n");
                            printf("Press any button to continue\n");
                            getchar();
                            length = 0;
                    }
                    for(int j = 0; j < length; j++){
                        if(inputName[j] == ' '){
                            printf("INVALID NAME\n");
                            printf("Press any button to continue\n");
                            getchar();
                            length = 0;
                        }
                    }
                }
                inputName[0] = toupper(inputName[0]);
                strcpy(playerInfo[saveNum].name, inputName);
                playerInfo[saveNum].score = score;
                saveNum++;
                printf("SUCCESS SAVE\n");
                insertionSort(playerInfo, saveNum);
                overWriteSave(playerInfo, saveNum);
            printf("Thank You For playing\n");
            getchar();
        }
    }

}
