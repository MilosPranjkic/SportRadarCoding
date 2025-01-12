#include <stdio.h>
#include "common.h"

void vPrintOptionManu(void);
void vPrintErrorWrongOptionSelected(void);
void vPringAllMatches(struct str_Game* sScoreBoard);
void vPrintAddInstuction(void);
unsigned char ucReadTeams(struct str_Game* sScoreBoard);
unsigned char ucTeamAlreadyPlaying(struct str_Game* sSingleGame, struct str_Game* sScoreBoard);
unsigned char ucAddGameToScoreBoard(struct str_Game* sSingleGame, struct str_Game* sScoreBoard, unsigned int uiTimeStamp);
unsigned char ucUpdateScore(struct str_Game* sScoreBoard);
unsigned char ucRemoveGame (struct str_Game* sScoreBoard);
void vPringAll(struct str_Game* sScoreBoard);
void vSortGames(struct str_Game* sScoreBoard);




