 #include <stdio.h>
#include <string.h>
#include <stdlib.h>

//jump2.c
//Create by Seong Hyun Han
//Created Date 2016-01-26
//Description:
// jump2.c load and read file from text file call "jump.txt"
// after reading a file, program takes input from the user then matching input distance
// with store data from text file.
// If two data is match, then print the search results
// If no data is match with input, then print not found.

// *********************Importan*********************
// In otder to run jump2.c file, jump1.c file must be exclude from execute.

//define structure for a player
typedef struct{
	char fName[30];
	char lName[30];
	char national[20];
	float distances;
}Player;

//Function load text file that contains player name, nationality, and distance
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
			if(counter == -1){ //This if statement set to ignore the first line of text file, in order to record only the data (not column name)
				fscanf(input, "%s %s %s %s", tempFName, tempLName, tempNational, tempDistName);
				counter++;
			}else{ //Start to store data 
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
		//once load are successful print this line to let user know load are successful
		printf("The data are loaded successfully\n");
		fclose(input);
	}
}

//print information that are matched
void printPlayer(Player p, int counter, float searchDist){
	if(counter == 0){
		printf("The jumpers exceeded %.2fm are: \n", searchDist);
	}
	printf("%s %s %s %.2f\n", p.fName, p.lName, p.national, p.distances);
}

//search function
//whenever it found the player that are matched with the user input
//it called printPlayer function to print the information
void search(float distance, Player all[],int max){
	int counter=0;
	for(int i=0;i<max;i++){
		if(distance <= all[i].distances){
			printPlayer(all[i], counter, distance);
			counter++;
		}
	}
	if(counter == 0){
		printf("Search Not Found\n");
	}
}

int main(int argc, char* argv[]){

	// define an arrays of Player, and variables
	Player player[41];
	float searchDist;
	char myFileName[10]="jump.txt";
	int validate=-1;

	load(myFileName, player);

	// get input from user(keyboard) and validate input
	while(validate == -1){
		printf("Please enter the distance threshold: ");
		if(scanf("%f", &searchDist) != 1){
			printf("Invalid Input!\nPlease enter valid input\n");			
		}else{
			validate = 0;
		} 
		fflush(stdin);
	}

	// call the search	
	search(searchDist,player,41);

	return 0;
}
