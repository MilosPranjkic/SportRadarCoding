#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
#include "IO_handling.h"
#include "common.h"

	


/*char sTeam_A [Longest_Country_Name];
	char sTeam_B [Longest_Country_Name];
	unsigned char ucTeam_A_Goals;
	unsigned char ucTeam_B_Goals;
	unsigned int ucTimeStamp;
	bool bGame_Active;*/

int main()
{	
	struct str_Game sScoreBoard[MAX_GAMES]; 		/* Creating the score board */

	struct str_Game SingleGame;						/* Create single game as a helper struckt */

	unsigned int uiTimeStamp = 0; 					/* Used for keeping track of when whas a game added */		

	unsigned char cOption = 0; 						/* stors the option for the main menu */

	memset(sScoreBoard, 0, sizeof(sScoreBoard)); 	/* Cleaning up the garbage memory */

	

	while(1)
	{	
		memset(&SingleGame, 0, sizeof(SingleGame)); 		/* Cleaning up the garbage memory from helper struct */

		vPrintOptionManu();									/* print the option */

		cOption = (unsigned char)getchar(); 				/* get the option from the console */
		while ((getchar() != '\n')){}						/* clean the input buffer from garbage */

		
		switch(cOption-=48)									/* Input from consol is a caracter, asci diff between caracter and coresponding number is 48 */
		{
			case 1:											/* Option for starting new game */
			{
				vPrintAddInstuction();
				if (ucReadTeams(&SingleGame) != RetValError);	/* Check if consol input is susccesful */
				{	
					if (ucTeamAlreadyPlaying(&SingleGame, sScoreBoard) != RetValError)	/* Check if the team is alredy playing */
					{
						if (ucAddGameToScoreBoard (&SingleGame, sScoreBoard, uiTimeStamp) != RetValError)	/* Add the team to thee board */
						{
							/* New Game succesfuly added */
							uiTimeStamp ++; 					/* Increse the timestamp */
						}
					}
				}

				break;
			};

			case 2:
			{	
				ucUpdateScore(sScoreBoard);						/* Chang the score */
				break;
			};

			case 3:
			{	
				ucRemoveGame(sScoreBoard);						/* Removing the game */
				break; 
			};

			case 4:
			{	
				vSortGames(sScoreBoard);						/* Sort games on the board */
				vPringAllMatches(sScoreBoard);					/* Print all the active games */
				break;
			};

			default:
			{
				vPrintErrorWrongOptionSelected();				/* Default case */
				break; 
			};
		}

	}
	return 0; 
}

