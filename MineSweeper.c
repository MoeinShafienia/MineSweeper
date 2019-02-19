#include<string.h>
#include <stdio.h>
#include<time.h>
#include <stdlib.h>
#include <windows.h>
//hello
void SetBombNumbersZero(int IsBomb[][31],int bombnearby[][31]){
		for(int i =1 ; i < 15 ; i++){
			for(int j = 1 ; j<31  ;j++){
				IsBomb[i][j] = 0;       // if IsBomb = 0 it means that this cell is not a bomb (now we are getting ready to make random bombs)
				bombnearby[i][j] = 0;   // bombnearby means the number of bombs around a cell
			}
		}
}

void SetSharp(char gamescreen[][31],int opration[][31]){
	for(int i =1 ; i < 15 ; i++){
		for(int j = 1 ; j<31  ;j++){
			gamescreen[i][j] = '#';  // this is for showing to the player
			opration[i][j] = 0;		/* each cell has a oprating number(only 0 and 1). 
									if it is 0 it means that that cell hasnt been checked for a bomb */
		}
	}
}

void MakingRandomBombs(int IsBomb[][31],int bombnearby[][31]){
	int i , j;
    srand(time(NULL));
	for(int m = 0 ; m<40 ; m++){
		i = (rand()%14) +1;
		j = (rand()%30) +1;
		if (IsBomb[i][j] == 1){		// this is for generating exactly 40 bombs
			m--;
			continue ;
		}
		IsBomb[i][j] = 1;

        bombnearby[i-1][j-1]++;    // when a bomb created , all of its nearby cells will be incremented by one in bombnearby array
		bombnearby[i-1][j]++;
		bombnearby[i-1][j+1]++;
		bombnearby[i][j-1]++;
		bombnearby[i][j+1]++;
		bombnearby[i+1][j-1]++;
		bombnearby[i+1][j]++;
		bombnearby[i+1][j+1]++;
    }
}

void cls(){
    system("cls");
}

void PrintGameBoard(char gamescreen[][31]){      // this is for showing player the game screen after chenges 
	cls();
	printf("  ");
	for (int i = 1; i<=30; i++)
		printf("%3d",i);
	printf("\n");
	for (int i = 1; i<15; i++){
		printf("%2d",i);
		for(int j = 1; j < 31; j++){
			printf("%3c",gamescreen[i][j]);
	}
	printf("\n");
	}
}

int IsWinner(char gamescreen[][31],int IsBomb[][31]){  		// by each move we should check if the player wins or not
	for(int i =1 ; i < 15 ; i++){
		for(int j = 1 ; j<31  ;j++){
			if (IsBomb[i][j] == 0){		// this means if a cell is not a bomb , shouldnt be # (only bombs should be # or be flaged)
				if (gamescreen[i][j] == '#' || gamescreen[i][j] == "P")
					return 0;
			}
		}
	}
	return 1;
}

void check(char gamescreen[][31],int opration[][31],int bombnearby[][31],int i,int j){
	// this function check the current cell and check nearby cells until it gets to a number (in bombnearby array)

	if (opration[i][j] == 0){	// if a cell is checked , it doesnt need to be checked anymore

		if (bombnearby[i][j]){		/* if there is a bomb around the cell 
		                            	it should print the number and stop cheking other cells */
			gamescreen[i][j] = bombnearby[i][j] + '0';
			opration[i][j] = 1;
		}
		else{
			gamescreen[i][j] = ' ';
			opration[i][j] = 1;
			if (i>0 && i<15 && j>0 && j<31){	// cells shouldnt be out of arrays
				check(gamescreen,opration,bombnearby,i-1,j-1);
				check(gamescreen,opration,bombnearby,i-1,j);
				check(gamescreen,opration,bombnearby,i-1,j+1);
				check(gamescreen,opration,bombnearby,i,j-1);
				check(gamescreen,opration,bombnearby,i,j+1);
				check(gamescreen,opration,bombnearby,i+1,j-1);
				check(gamescreen,opration,bombnearby,i+1,j);
				check(gamescreen,opration,bombnearby,i+1,j+1); 
			} 
		}
	}
}

void MakeBombsStar(char gamescreen[][31],int IsBomb[][31]){
	for(int i =1 ; i < 15 ; i++){
		for(int j = 1 ; j<31  ;j++){
			if (IsBomb[i][j])
				gamescreen[i][j] = '*';   									 
		}
	}
}



int main (){

    int IsBomb[15][31],bombnearby[15][31],opration[15][31];
    char gamescreen[15][31];
    SetBombNumbersZero(IsBomb,bombnearby);
    SetSharp(gamescreen,opration);
    MakingRandomBombs(IsBomb,bombnearby);

    PrintGameBoard(gamescreen);

    char cmd[3];
	while (1){
		fgets(cmd,sizeof(cmd)*3,stdin);
		int i , j;
		scanf("%d %d",&i,&j);

		if(strcmp(cmd,"cho\n") == 0){	 // when player says cho
			if(gamescreen[i][j] != 'P'){
				if (IsBomb[i][j]){		// if the player select a bomb
					MakeBombsStar(gamescreen,IsBomb);
					PrintGameBoard(gamescreen);
					printf("YOU LOST");
					Sleep(5000);
					break; 
				}
				else{	// if the player dosent select a bomb
					if (bombnearby[i][j] == 0){	  // if there is not a single bomb around a cell should print ' ' and check the nearby cells	
						gamescreen[i][j] = ' ';
						check(gamescreen,opration,bombnearby,i,j);
					}
					else{	// if there are bombs around a cell should print the number of bombs and stop checking nearby cells 
						gamescreen[i][j] = bombnearby[i][j] + '0';
					}
					if (IsWinner(gamescreen,IsBomb)){
						PrintGameBoard(gamescreen);
						printf("YOU WON");
						Sleep(7000);
						break ;
					}
					else{ 
						PrintGameBoard(gamescreen);
						continue ;
					}
				}
			}
			else{
				PrintGameBoard(gamescreen);
			}
		}
		
		else if (strcmp(cmd,"fla\n") == 0){	// when player says fla
			if (gamescreen[i][j] == '#')
				gamescreen[i][j] = 'P';
        	PrintGameBoard(gamescreen);
		}

		else if (strcmp(cmd,"ufl\n") == 0){	// when player says ufl
			if (gamescreen[i][j] == 'P')
				gamescreen[i][j] = '#';
            PrintGameBoard(gamescreen);
		}

		else if (strcmp(cmd,"ext\n") == 0){	// when player says ext
			break ;
		}
	}
	return 0;
}

