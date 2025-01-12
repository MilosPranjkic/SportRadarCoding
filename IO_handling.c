#include "IO_handling.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


/* Prints out menu with all the options*/
void vPrintOptionManu(void)
{
	printf("\nPlese select one of the options (select the number for the option that you would like):\n\n \
		1. Start new match\n \
		2. Update score\n \
		3. End game\n \
		4. Get summary\n\n");
}

/* Prints out menu error message when invalid option is selected in the main manu*/
void vPrintErrorWrongOptionSelected(void)
{
	printf("Entered value not valid, please try again. Only exceptable opetions are numbers from 1 to 4 followed by \"Enter key \"");
}

/* Instruction on the form of the teams to be added to the board */
void vPrintAddInstuction(void)
{
	printf("\nEnert Game to a Score Board, type first team, than \"Enter Key\", than second team and \"Enter Key\" again\n\n");
}

/* Reads the values from the terminal and does basic error detection and handling */
unsigned char ucReadTeams(struct str_Game* sSingleGame)
{
	unsigned char ucRetVal = RetValOk; 								
	fgets(sSingleGame->sTeam_A, Longest_Country_Name, stdin);		/* Read value from console */

	sSingleGame->sTeam_A[strlen(sSingleGame->sTeam_A) - 1] = '\0'; 	/* remove enter caracter*/

	fgets(sSingleGame->sTeam_B, Longest_Country_Name, stdin);		/* Read value from console */

	sSingleGame->sTeam_B[strlen(sSingleGame->sTeam_B) - 1] = '\0';	/* remove enter caracter*/

	for (int i = 0; i < strlen(sSingleGame->sTeam_A) - 1; ++i)
	{
		if ((sSingleGame->sTeam_A[i] >= 'a' && sSingleGame->sTeam_A[i] <= 'z') || (sSingleGame->sTeam_A[i] >= 'A' && sSingleGame->sTeam_A[i] <= 'Z') || sSingleGame->sTeam_A[i] != ' ')
		{
			/* Checks if all of the caracters from the console are letteres or space caracter for team A*/
		}
		else
		{	
			ucRetVal = RetValError; 	/* In case that there is a caracter that is not letter or a space error is returned */
			break;
		}
	}

	for (int i = 0; i < strlen(sSingleGame->sTeam_B) - 1; ++i)
	{
		if ((sSingleGame->sTeam_B[i] >= 'a' && sSingleGame->sTeam_B[i] <= 'z') || (sSingleGame->sTeam_B[i] >= 'A' && sSingleGame->sTeam_B[i] <= 'Z') || sSingleGame->sTeam_B[i] != ' ')
		{
			/* Checks if all of the caracters from the console are letteres for team B*/
		}
		else
		{	
			ucRetVal = RetValError; 	/* In case that there is a caracter that is not letter or a space error is returned */
			break;
		}
	}

	if (strcmp(sSingleGame->sTeam_A, sSingleGame->sTeam_B) == 0)	/* Check if the same team is put as team A and team B */
	{
		ucRetVal = RetValError; 
	}

	if (RetValError == ucRetVal)	/* In case of any issue print out an error log */
	{
		printf("\nEnteries not valid, check if you entered any value that is not a letter or if you entered same team twice\n");
	}

	return ucRetVal;
}


/* Checks if one of the teams is slaredy on the scoreboard */
unsigned char ucTeamAlreadyPlaying(struct str_Game* sSingleGame, struct str_Game* sScoreBoard)
{
	unsigned char ucRetVal = RetValOk; 

	for (int i = 0; i < MAX_GAMES; ++i)					/* Go through the board, check if any of the teams is alredy in */
	{
		if (sScoreBoard[i].bGame_Active == 1)			/* Iterate only through the active games*/
		{
			if(strcmp(sSingleGame->sTeam_A, sScoreBoard[i].sTeam_A) == 0 || 
				strcmp(sSingleGame->sTeam_A, sScoreBoard[i].sTeam_B) == 0 || 
				strcmp(sSingleGame->sTeam_B, sScoreBoard[i].sTeam_A) == 0 || 
				strcmp(sSingleGame->sTeam_B, sScoreBoard[i].sTeam_B) == 0)
			{
				ucRetVal = RetValError;					/* In case that there is an ongoing game error is set */
				printf("\nOne or both teams that you enter are already in the active game, please start the new game only if the team is currently not in an active game\n");
				break;
			}
		}
	}

	return ucRetVal;
}

/* Function that adds the game to the score board */
unsigned char ucAddGameToScoreBoard(struct str_Game* sSingleGame, struct str_Game* sScoreBoard, unsigned int uiTimeStamp)
{
	unsigned char ucRetVal = RetValError;

	sSingleGame->ucTeam_A_Goals = 0;				/* Setting the score */
	sSingleGame->ucTeam_B_Goals = 0;
	sSingleGame->bGame_Active = 1; 					/* Setting the active flag */
	sSingleGame->ucTimeStamp = uiTimeStamp;			/* Setting the timestamp */

	int i = 0; 

	for (i = 0; i < MAX_GAMES; ++i)
	{
		if(sScoreBoard[i].bGame_Active != 1)		/* Checks the array for the first game slot that is not active and sets the values */
		{
			memcpy(sScoreBoard[i].sTeam_A, sSingleGame->sTeam_A, sizeof(sSingleGame->sTeam_A));
			memcpy(sScoreBoard[i].sTeam_B, sSingleGame->sTeam_B, sizeof(sSingleGame->sTeam_A));
			
			sScoreBoard[i].ucTeam_A_Goals = 0;
			sScoreBoard[i].ucTeam_B_Goals = 0;
			sScoreBoard[i].bGame_Active = 1; 
			sScoreBoard[i].ucTimeStamp = uiTimeStamp;

			ucRetVal = RetValOk;

			break; 
		}
	}


	/* Prints the status message */
	if (ucRetVal == RetValError)
	{
		printf("\nUnable to add new game, before adding new one end one of the games that are ongoing so there are teams that can play new game\n");
	}
	else
	{
		printf("\nGame: %s vs %s succesfully added\n", sScoreBoard[i].sTeam_A, sScoreBoard[i].sTeam_B);
	}

	return ucRetVal;
}

/* Used to update score for the existing game */
unsigned char ucUpdateScore(struct str_Game* sScoreBoard)
{	
	struct str_Game sSingleGame; 											/* temp structure */

	unsigned char ucRetVal = RetValError;	

	char input [Longest_Country_Name + Longest_Country_Name + 20];			/* Input buffer for storring the values from console */

	printf("\nEnter the the score in the follwoing format: Team_A,Team_B,X,Y\nWhere X and Y are number of svores for team A (X) and team B(Y)\n\n");

	fgets(input, Longest_Country_Name + Longest_Country_Name + 20, stdin);	/* Read data from console */

	input[strlen(input) - 1] = '\0';										/* Terminating the string and removin enter caracter */	

	char *token;															/* Temr variable for parsing */

	token = strtok(input, ",");												/* Read firs team */
	strcpy(sSingleGame.sTeam_A, token);

	token = strtok(NULL, ",");												/* Read second team */
	strcpy(sSingleGame.sTeam_B, token);

	token = strtok(NULL, ",");												/* read first score and covert it from character to number */
	sSingleGame.ucTeam_A_Goals = (unsigned char)atoi(token);			
	
	token = strtok(NULL, ",");
	sSingleGame.ucTeam_B_Goals = (unsigned char)atoi(token);				/* read second score and covert it from character to number */

	int i = 0;

	for (i = 0; i < MAX_GAMES; ++i)											/* Check if the game that score should be changed exists and is active */
	{
		if (sScoreBoard[i].bGame_Active == 1)
		{
			if ((strcmp(sScoreBoard[i].sTeam_A, sSingleGame.sTeam_A) == 0) && (strcmp(sScoreBoard[i].sTeam_B, sSingleGame.sTeam_B) == 0))
			{
				sScoreBoard[i].ucTeam_A_Goals = sSingleGame.ucTeam_A_Goals;	/* If the game is found modify da score */
				sScoreBoard[i].ucTeam_B_Goals = sSingleGame.ucTeam_B_Goals;
				ucRetVal = RetValOk;
				break;
			}
		}
	}


	if (ucRetVal == RetValError) 											/* Status message printouts succesfull or error */
	{
		printf("\nThere has been a problem with changing the score, check if the score is given in the right format or if the game is active, plese try again with right values\n");
	}
	else
	{
		printf("\nScore updated succesfully, new score between %s and %s is %u - %u \n",sScoreBoard[i].sTeam_A, sScoreBoard[i].sTeam_B, sScoreBoard[i].ucTeam_A_Goals, sScoreBoard[i].ucTeam_B_Goals);
	}

	return ucRetVal;
}

/* Function used for removing existing game from the board */
unsigned char ucRemoveGame (struct str_Game* sScoreBoard)
{	
	unsigned char ucRetVal = RetValError;

	struct str_Game sSingleGame; 									/* temp structure */

	printf("\nEnter a game that endeed and has to be removed from the Score Board, type first team, than \"Enter Key\", than second team and \"Enter Key\" again\n\n");

	fgets(sSingleGame.sTeam_A, Longest_Country_Name, stdin);		/* read team A from the console */
	sSingleGame.sTeam_A[strlen(sSingleGame.sTeam_A) - 1] = '\0'; 	/* remove enter caracter*/

	fgets(sSingleGame.sTeam_B, Longest_Country_Name, stdin);		/* read team A from the console */
	sSingleGame.sTeam_B[strlen(sSingleGame.sTeam_B) - 1] = '\0';	/* remove enter caracter*/

	int i = 0;

	for (i = 0; i < MAX_GAMES; ++i)									/* Iterate through the score board and find the game that should be removed */
	{
		if (sScoreBoard[i].bGame_Active == 1)
		{
			if ((strcmp(sScoreBoard[i].sTeam_A, sSingleGame.sTeam_A) == 0) && (strcmp(sScoreBoard[i].sTeam_B, sSingleGame.sTeam_B) == 0))
			{
				//printf("Pronadjen par\n");
				sScoreBoard[i].bGame_Active = 0;					/* Put active flag to 0, marking is an non active */
				ucRetVal = RetValOk;
				break;
			}
		}
	}

	if (ucRetVal == RetValOk)										/* Status message printouts succesfull or error */
	{
		printf("\nSuccesfuly removed a Game between %s and %s \n",sScoreBoard[i].sTeam_A, sScoreBoard[i].sTeam_B);
		memset(&sScoreBoard[i], 0, sizeof(struct str_Game));		/* Clear the array element */

	}
	else
	{
		printf("\nThere is no currently no active game between thos 2 teams, check you endered in a correct format (order of the teams) or if some type is made and try again");
	}

}


/* Printout of the single game */
void vPrintSingleMatch (struct str_Game* sScoreBoard)
{
	printf("%s %u - %s %u\n", sScoreBoard->sTeam_A, sScoreBoard-> ucTeam_A_Goals, sScoreBoard->sTeam_B, sScoreBoard->ucTeam_B_Goals);
}

/* Print all active games from the board */
void vPringAllMatches(struct str_Game* sScoreBoard)
{	
	unsigned char cNoActiveGame = 0;

	printf("\n");

	for (int i = 0; i < MAX_GAMES; ++i)
	{
		if (sScoreBoard[i].bGame_Active == 1)
		{
			vPrintSingleMatch(&sScoreBoard[i]);
			cNoActiveGame++;
		}
	}

	if (cNoActiveGame == 0)			/* Printout that there are no active games */
	{
		printf("\nThere are currentlu no games in progress\n");
	}
}

void vPringAll(struct str_Game* sScoreBoard)		/* For dev use, not used now*/
{	
	printf("\n\n\n");
	for (int i = 0; i < MAX_GAMES; ++i)
	{
		vPrintSingleMatch(&sScoreBoard[i]);
	}
}


/* Swaps two array elements */
void swap(struct str_Game *sScoreBoard_A, struct str_Game *sScoreBoard_B) 
{ 
	struct str_Game sTemp = *sScoreBoard_A; 
	*sScoreBoard_A = *sScoreBoard_B; 
	*sScoreBoard_B = sTemp; 
}

/* Function to sort the array based on the goals and timestamp criteria */
void sortGames(struct str_Game* sScoreBoard, int n) 
{ 
	for (int i = 0; i < n-1; i++) 
	{ 
		for (int j = 0; j < n-i-1; j++) 
		{ 
			unsigned char cGoals_1 = sScoreBoard[j].ucTeam_A_Goals + sScoreBoard[j].ucTeam_B_Goals; 							/* Calculates number of goals for firs game */
			unsigned char cGoals_2 = sScoreBoard[j+1].ucTeam_A_Goals + sScoreBoard[j+1].ucTeam_B_Goals; 						/* Calculates number of goals for sedond game */
			if (cGoals_1 < cGoals_2 || (cGoals_1 == cGoals_2 && sScoreBoard[j].ucTimeStamp < sScoreBoard[j+1].ucTimeStamp)) 	/* Checks what  game ha more goals, in case that the values are equal it takes the timestamp into accund */
			{ 
				swap(&sScoreBoard[j], &sScoreBoard[j+1]); 																		/* Swaps 2 games in the array */
			} 
		} 
	} 
}


/* Function for sorting the array */
void vSortGames(struct str_Game* sScoreBoard)
{
	sortGames(sScoreBoard, MAX_GAMES);
}









