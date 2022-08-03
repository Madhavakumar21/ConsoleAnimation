/*
 * animation.c
 *
 *  Created on: 27-Jul-2022
 *      Author: Madhavakumar
 */


// Includes -------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "animation.h"


// Constants ------------------------------

#define RAIN_WIDTH							47
#define RAIN_HEIGHT							8
#define RAIN_BACKGROUND						' '
#define MAX_EXISTING_CONTENT_SIZE			100
#define RAIN_COMPLETED						1
#define RAIN_UNFINISHED						0
#define MIN_RAIN_INTENSITY					1
#define MAX_RAIN_INTENSITY					3
#define RAIN_DELAY							300
#define TYPEWRITER_DELAY					100
#define FLASH_SHOW_DELAY					1000


// Global Variables -----------------------

char g_rain_target_str[RAIN_HEIGHT][RAIN_WIDTH + 1] = {
"   X  ST    X     X  XXXXXXX     XX     XXXXX  ",
"  XX        X     X  X          X  X    X    X ",
" X X         X   X   X         X    X   X    X ",
"   X          XXX    X        X      X  X   X  ",
"   X           X     XXXXX    XXXXXXXX  XXXXX  ",
"   X           X     X        X      X  X    X ",
"   X           X     X        X      X  X     X",
"XXXXXXX        X     XXXXXXX  X      X  X     X"
};

char g_rain_current_str[RAIN_HEIGHT][RAIN_WIDTH + 1] = {
"                                               ",
"                                               ",
"                                               ",
"                                               ",
"                                               ",
"                                               ",
"                                               ",
"                                               "
};

//char g_rain_current_needs[RAIN_WIDTH + 1];

//char g_existing_content[MAX_EXISTING_CONTENT_SIZE + 1];


// Static Function prototypes -------------

int custom_random(int lower, int upper);
//void update_existing_str(char *existing_content);
int update_rain();
void display_current_rain();


// Static Function definitions ------------

int custom_random(int lower, int upper)
{
	return ((rand() % (upper - lower + 1)) + lower);
}


/*
void update_existing_str(char *existing_content)
{
	for(int i = 0; i < MAX_EXISTING_CONTENT_SIZE; i++)
	{
		g_existing_content[i] = existing_content[i];

		if(g_existing_content[i] == '\0')
			break;
	}
}
*/


int update_rain()
{
	char rain_current_needs[RAIN_WIDTH + 1];
	int needs_locations[RAIN_WIDTH];   // Stack DataStructure
	int needs_locations_size = 0;      // top pointer of the stack
	int flag;
	int k;
	int rand_ind, need_ind, rand_rain_intensity;

	memset(rain_current_needs, '\0', sizeof(rain_current_needs));

	for(int i = RAIN_HEIGHT - 1; i > 0; i--)
	{
		for(int j = 0; j < RAIN_WIDTH; j++)
		{
			if((rain_current_needs[j] == '\0') && (g_rain_current_str[i][j] != g_rain_target_str[i][j]))
			{
				rain_current_needs[j] = g_rain_target_str[i][j];
				//needs_locations[needs_locations_size] = j;
				needs_locations_size++;
			}
			if((g_rain_current_str[i][j] == RAIN_BACKGROUND) && (g_rain_current_str[i - 1][j] != RAIN_BACKGROUND) && (rain_current_needs[j] != '\0'))
			{
				g_rain_current_str[i][j] = g_rain_current_str[i - 1][j];
				g_rain_current_str[i - 1][j] = RAIN_BACKGROUND;
				rain_current_needs[j] = '\0';
				needs_locations_size--;
			}
		}
	}

	for(int j = 0; j < RAIN_WIDTH; j++)
	{
		if((rain_current_needs[j] == '\0') && (g_rain_current_str[0][j] != g_rain_target_str[0][j]))
		{
			rain_current_needs[j] = g_rain_target_str[0][j];
			needs_locations_size++;
		}
		/*
		if((g_rain_current_str[i][j] == RAIN_BACKGROUND) && (g_rain_current_str[i - 1][j] != RAIN_BACKGROUND) && (rain_current_needs[j] != '\0'))
		{
			//flag2 = 1;
			g_rain_current_str[i][j] = g_rain_current_str[i - 1][j];
			g_rain_current_str[i - 1][j] = RAIN_BACKGROUND;
			rain_current_needs[j] = '\0';
			needs_locations_size--;
		}
		*/
	}

	k = 0;
	for(int j = 0; j < needs_locations_size; j++)
	{
		while(!rain_current_needs[k]) k++;

		needs_locations[j] = k;
		k++;
	}

	if(needs_locations_size)
	{
		rand_rain_intensity = custom_random(MIN_RAIN_INTENSITY, MAX_RAIN_INTENSITY);
		for(int i = 0; i < rand_rain_intensity; i++)
		{
			if(!needs_locations_size)
				break;

			rand_ind = custom_random(0, needs_locations_size - 1);
			need_ind = needs_locations[rand_ind];
			for(int j = rand_ind; j < needs_locations_size - 1; j++)
				needs_locations[j] = needs_locations[j + 1];
			needs_locations_size--;

			g_rain_current_str[0][need_ind] = rain_current_needs[need_ind];
			//rain_current_needs[need_ind] = '\0';
		}
	}

	flag = RAIN_COMPLETED;
	for(int i = 0; i < RAIN_HEIGHT; i++)
	{
		for(int j = 0; j < RAIN_WIDTH; j++)
		{
			if(g_rain_current_str[i][j] != g_rain_target_str[i][j])
				flag = RAIN_UNFINISHED;
		}
	}

	return flag;
}


void display_current_rain()
{
	for(int i = 0; i < RAIN_WIDTH; i++) printf("-");
	printf("\n");
	for(int i = 0; i < RAIN_HEIGHT; i++)
	{
		printf("%s\n", g_rain_current_str[i]);
	}
	for(int i = 0; i < RAIN_WIDTH; i++) printf("-");
	printf("\n");
}


// API Function definitions ---------------


void start_rain(char *existing_content)
{
	int status;

	srand(time(0));
	//update_existing_str(existing_content);

	do
	{
		system("cls");
		printf("%s\n", existing_content);

		display_current_rain();
		status = update_rain();

		Sleep(RAIN_DELAY);
	}
	while(status != RAIN_COMPLETED);

	system("cls");
	printf("%s\n", existing_content);
	display_current_rain();

	//
}


void typewrite(char *target_content)
{
	for(int i = 0; target_content[i] != '\0'; i++)
	{
		printf("%c", target_content[i]);
		Sleep(TYPEWRITER_DELAY);
	}
}


void flash_show(char **str_list, int list_size)
{
	printf("\n");
	for(int i = 0; i < list_size; i++)
	{
		printf("%s    ", str_list[i]);
		Sleep(FLASH_SHOW_DELAY);
	}
	printf("\n\n");
}




// ------------------- END -------------------
