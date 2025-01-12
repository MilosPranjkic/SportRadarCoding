#include <stdbool.h>

#ifndef COMMON
#define COMMON

#define MAX_GAMES 100 /*there are 195 countries in the world, with a small buffer there can be max 100 games in the WC */
#define Longest_Country_Name 33 /* longest country name has 32 caracters */
#define RetValError 1
#define RetValOk 0

#pragma pack(push, 1)
struct str_Game
{
	char sTeam_A [Longest_Country_Name];
	char sTeam_B [Longest_Country_Name];
	unsigned char ucTeam_A_Goals;
	unsigned char ucTeam_B_Goals;
	unsigned int ucTimeStamp;
	bool bGame_Active;
};
#pragma pack(pop)


#endif //COMMON