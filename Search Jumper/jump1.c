#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//jump1.c
//Create by Seong Hyun Han
//Created Date 2016-01-22
//Description:
// jump1.c load and read file from text file call "jump.txt"
// after reading a file, program takes input from the user then matching input distance
// with store data from text file.
// If two data is match, then print the search result
// If no data is match with input, then print not found.


//define structure for a player
typedef struct{
	char fName[30];
	char lName[30];
	char national[20];
	float distances;
}Player;

void load(char filename[10], Player container[]){
	char tempFName[30];
	char tempLName[30];
	char tempNational[20];
	char tempDistName[10];
	float tempDistance;
	int counter;

	FILE* input = fopen(filename, "r+");
	if(input == NULL){
		perror("Error opening the file");
	}else{
		counter = -1;

		while(!feof(input)){
			strcpy(tempFName, "");
			if(counter == -1){
				fscanf(input, "%s %s %s %s", tempFName, tempLName, tempNational, tempDistName);
				counter++;
			}else{
				fscanf(input, "%s %s %s %f", tempFName, tempLName, tempNational, &tempDistance);
				if(strcmp(tempFName, "") != 0){
					strcpy(container[counter].fName, tempFName);
					strcpy(container[counter].lName, tempLName);
					strcpy(container[counter].national, tempNational);
					container[counter].distances = tempDistance;
					counter++;
				}
			}
		}
		printf("The data are loaded successfully\n");
		fclose(input);
	}
}

//search function
int search(float distance, Player all[],int max){
	for(int i=0;i<max;i++){
		if(distance <= all[i].distances){
			return i;
		}
	}
	return -1;
}

//print information
void printPlayer(Player p, float searchDist){
	printf("The jumpers exceeded %.2fm are: \n", searchDist);
	printf("%s %s %s %.2f\n", p.fName, p.lName, p.national, p.distances);
}

int main(int argc, char* argv[]){

	// define an arrays of Player
	Player player[41];
	float tempDist;
	char myFileName[10]="jump.txt";
	int validate=-1;

	load(myFileName, player);

	// get input from user(keyboard) and validate input
	while(validate == -1){
		printf("Please enter the distance threshold: ");
		if(scanf("%f", &tempDist) != 1){
			printf("Invalid Input!\nPlease enter valid input\n");			
		}else{
			validate = 0;
		} 
		fflush(stdin);
	}

	// call the search
	//used to keep the return value of the search
	// it has been set to -1 that indicates not found
	
	int loc = -1;
	loc=search(tempDist,player,41);

    if(loc != -1){
			printPlayer(player[loc], tempDist);
	}else{
		printf("Not Found\n"); 
	}

	return 0;
}
