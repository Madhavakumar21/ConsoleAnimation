/*
 * main.c
 *
 *  Created on: 27-Jul-2022
 *      Author: Madhavakumar
 */


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "main.h"


int main()
{
	char initial_msg[] = "Had a great time in...\n";
	// Gained a lot of knowledge in a very short duration.
	// Enjoyed all the classes, lab sessions, seminars and contests.
	// It was really a wonderful experience.
	//
	// Thanks
	// Regards
	// Madhavakumar D
	char *sem1_subj_list[9] = {'\0'};
	sem1_subj_list[0] = "English-1";
	sem1_subj_list[1] = "Maths-1";
	sem1_subj_list[2] = "Physics";
	sem1_subj_list[3] = "Chemistry";
	sem1_subj_list[4] = "Python";
	sem1_subj_list[5] = "EG";
	sem1_subj_list[6] = "Phy-Che-Lab";
	sem1_subj_list[7] = "Python-Lab";

	char *sem2_subj_list[9] = {'\0'};
	sem2_subj_list[0] = "English-2";
	sem2_subj_list[1] = "Maths-2";
	sem2_subj_list[2] = "BEEME";
	sem2_subj_list[3] = "C-Prog-DS";
	sem2_subj_list[4] = "Web-App-Dev";
	sem2_subj_list[5] = "EVS";
	sem2_subj_list[6] = "EP-Lab";
	sem2_subj_list[7] = "C-Prog-DS-Lab";


	system("cls");
	typewrite(initial_msg);
	start_rain(initial_msg);
	flash_show(sem1_subj_list, 8);
	typewrite("...and...\n");
	Sleep(1000);
	flash_show(sem2_subj_list, 8);
	typewrite("\nGained a lot of knowledge in a very short duration.\n\
Enjoyed all the classes, lab sessions, seminars and contests.\n\
It was really a wonderful experience.\n\
\nThanks\nRegards\nMadhavakumar D\n");

	Sleep(2000);
	return 0;
}


// ------------------- END -------------------
