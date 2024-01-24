/*
.										UNIVERSITY OF THE PHILIPPINES LOS BANOS
.									Computer Science 21 - Fundamentals of Programming
.											First Semester A.Y. 2016-2017
.			Creator:	BATICOS, Andric Quinn Sargento
.					2015-13764 / 09291720966
.					BS Computer Science - College of Arts and Sciences
.			
.			Program Title: SIETE​: Teacher-to-Class Management System (User Input Functions)
.			
.			File Description: 	This file contains all functions used for user input.
*/
//---------------------------------------------------------------------------------------------------------------------------	FUNCTIONS

//	[FUNCTION DEFINITION] This function is used to uppercase every character of a given string.
void uppercaseString(char *string) {
	int i;
	for (i = 0; i < strlen(string); i++) {
		string[i] = toupper(string[i]);
	}
}

//	[FUNCTION DEFINITION] This function is used to check every character of user input if it is an integer or not. It returns -1 if it sees that a character is not an integer. Otherwise, it returns 0.
int checkString(char *string) {
	
	int i;
	
	for (i = 0; i < strlen(string); i++) {
		if (isdigit(string[i]) || string[i] == '.') continue;
		else return -1;
	}
	
	return 0;
}

//	[FUNCTION DEFINITION] This function is used to get the user's name.
void getName (char *fName, char *lName) {
	
	char *temp_fname; char *temp_lname;
	temp_fname = (char *) malloc (sizeof(char));
	temp_lname = (char *) malloc (sizeof(char));
	
	repeat1:
		printf ("  First Name: "); scanf ("%[^\n]s", temp_fname); getchar();
		if (strlen(temp_fname) == 0) {
			printf (ANSI_COLOR_RED"  --------------------------------------\n  Invalid Input! Try Again!\n  --------------------------------------\n"ANSI_COLOR_RESET);
			goto repeat1;
		}
	repeat2:
		printf ("  Last Name: "); scanf ("%[^\n]s", temp_lname); getchar();
		if (strlen(temp_lname) == 0) {
			printf (ANSI_COLOR_RED"  --------------------------------------\n  Invalid Input! Try Again!\n  --------------------------------------\n"ANSI_COLOR_RESET);
			goto repeat2;
		}
	
	temp_fname[strlen(temp_fname)] = '\0'; temp_lname[strlen(temp_lname)] = '\0';
	uppercaseString(temp_fname); uppercaseString (temp_lname);	// This function will uppercase the user's name to avoid case sensitivity.
	
	strcpy(fName, temp_fname); strcpy(lName,temp_lname);
	free (temp_fname); free (temp_lname);
}

//	[FUNCTION DEFINITION] This function is used to get the user's employee number input.
void getEN(char *EN) {
	
	int isDigit, flag = -1; char *en;
	en = (char *) malloc (sizeof(char));
	
	do {
		
	repeat:
		printf ("  Employee Number: "); scanf ("%[^\n]s", en); getchar();
		if (strlen(en) > 9) {
			printf ("  -----------------------------\n");
			printf (ANSI_COLOR_RED"  Input longer than expected!\n  Input must be of length 9.\n  Try again!\n"ANSI_COLOR_RESET);
			printf ("  -----------------------------\n");
			goto repeat;
		} else if (strlen(en) < 9) {
			printf ("  -----------------------------\n");
			printf (ANSI_COLOR_RED"  Input shorter than expected!\n  Input must be of length 9.\n  Try again!\n"ANSI_COLOR_RESET);
			printf ("  -----------------------------\n");
			goto repeat;
		} else en[9] = '\0';
			
	isDigit = checkString(en);
	if (isDigit == -1) {
		printf ("  --------------------------------------\n");
		printf (ANSI_COLOR_RED"  Invalid Input! Input must be integers.\n"ANSI_COLOR_RESET);
		printf ("  --------------------------------------\n");
	} else strcpy (EN, en);
	} while (isDigit != 0);
	free(en);	
}

//	[FUNCTION DEFINITION] This function is used to get the user's allowable units and number of students.
void getLimit (float *unitsAllowedptr, int *studentsAllowedptr, int code) {
	
	char *temp_units; char *temp_students;
	temp_units = (char *) malloc (sizeof(char));
	temp_students = (char *) malloc (sizeof(char));
	int units, students;
	
	repeat1:
		if (code == 1) {
			printf ("  Units Allowed: "); scanf ("%[^\n]s", temp_units); getchar();
		} else if (code == 2) {
			printf ("  Units of Class: "); scanf ("%[^\n]s", temp_units); getchar();
		}
		
		if (strlen(temp_units) == 0 || strlen(temp_units) > 3) {
			printf (ANSI_COLOR_RED"  --------------------------------------\n  Invalid Input! Try Again!\n  --------------------------------------\n"ANSI_COLOR_RESET);
			goto repeat1;
		}
	repeat2:
		if (code == 1) {
			printf ("  Students Allowed: "); scanf ("%[^\n]s", temp_students); getchar();
		} else if (code == 2) {
			printf ("  No. of Students: "); scanf ("%[^\n]s", temp_students); getchar();
		}
		
		if (strlen(temp_students) == 0 || strlen(temp_students) > 3) {
			printf (ANSI_COLOR_RED"  --------------------------------------\n  Invalid Input! Try Again!\n  --------------------------------------\n"ANSI_COLOR_RESET);
			goto repeat2;
		}
		
	temp_units[strlen(temp_units)] = '\0'; temp_students[strlen(temp_students)] = '\0';
	units = checkString(temp_units); students = checkString(temp_students);
	
	if (units == 0 && students == 0) {
		*unitsAllowedptr = atoi(temp_units); *studentsAllowedptr = atoi(temp_students);
	} else if (units != 0) {
		printf (ANSI_COLOR_RED"  --------------------------------------\n  Invalid Input! Try Again!\n  --------------------------------------\n"ANSI_COLOR_RESET);
		goto repeat1;
	} else if (students != 0) {
		printf (ANSI_COLOR_RED"  --------------------------------------\n  Invalid Input! Try Again!\n  --------------------------------------\n"ANSI_COLOR_RESET);
		goto repeat2;
	}
	
	free(temp_units); free (temp_students);
}

//	[FUNCTION DEFINITION] This function is used to get the user's course code and section of a class.
void getCCS (char *CC, char *section) {
	
	char *temp_courseCode; temp_courseCode = (char *) malloc (sizeof(char));
	char *temp_section; temp_section = (char *) malloc (sizeof(char));
	
	repeat1:
		printf ("  Course Code [no spaces]: "); scanf ("%[^\n]s", temp_courseCode); getchar();
		if (strlen(temp_courseCode) == 0) {
			printf (ANSI_COLOR_RED"  --------------------------------------\n  Invalid Input! Try Again!\n  --------------------------------------\n"ANSI_COLOR_RESET);
			goto repeat1;
		}
	repeat2:
		printf ("  Section [ex. UV-1L]: "); scanf ("%[^\n]s", temp_section); getchar();
		if (strlen(temp_section) == 0) {
			printf (ANSI_COLOR_RED"  --------------------------------------\n  Invalid Input! Try Again!\n  --------------------------------------\n"ANSI_COLOR_RESET);
			goto repeat2;
		}
	
	temp_courseCode[strlen(temp_courseCode)] = '\0';	uppercaseString(temp_courseCode);
	temp_section[strlen(temp_section)] = '\0';	uppercaseString(temp_section);
	strcpy(CC, temp_courseCode); strcpy(section, temp_section);
	free (temp_courseCode); free (temp_section);
}

//	[FUNCTION DEFINITION] This function is used to get the class schedule.
void getTime (char *sHour, char *sMin, int *sDaytime, int *sMH, char *eHour, char *eMin, int *eDaytime, int *eMH) {
	

	char *temp_startHr, *temp_startMin, *temp_startDaytime; char *temp_endHr, *temp_endMin, *temp_endDaytime; char *newString;
	temp_startHr = (char *) malloc (sizeof(char)); temp_startMin = (char *) malloc (sizeof(char)); temp_startDaytime = (char *) malloc (sizeof(char));
	temp_endHr = (char *) malloc (sizeof(char)); temp_endMin = (char *) malloc (sizeof(char)); temp_endDaytime = (char *) malloc (sizeof(char));
	newString = (char *) malloc (sizeof(char));
	int timeStartHour, timeStartMin, timeStartDaytime, timeStartMH, timeEndHour, timeEndMin, timeEndDaytime, timeEndMH;
	
	repeat1:
		printf ("  TIME START\n");
		printf ("    Hour: "); scanf ("%[^\n]s", temp_startHr); getchar();
		printf ("    Minutes: "); scanf ("%[^\n]s", temp_startMin); getchar();
		printf ("    Pick: [1] AM | [2] PM: "); scanf ("%[^\n]s", temp_startDaytime); getchar();
		if ((strlen(temp_startHr) == 0 || strlen(temp_startHr) > 3) || (strlen(temp_startMin) == 0 || strlen(temp_startMin) > 3) || (strlen(temp_startDaytime) == 0 || strlen(temp_startDaytime) > 3)) {
			printf (ANSI_COLOR_RED"  --------------------------------------\n  Invalid Input! Try Again!\n  --------------------------------------\n"ANSI_COLOR_RESET);
			goto repeat1;
		}
	repeat2:
		printf ("  TIME END\n");
		printf ("    Hour: "); scanf ("%[^\n]s", temp_endHr); getchar();
		printf ("    Minutes: "); scanf ("%[^\n]s", temp_endMin); getchar();
		printf ("     Pick: [1] AM | [2] PM]: "); scanf ("%[^\n]s", temp_endDaytime); getchar();
		if ((strlen(temp_endHr) == 0 || strlen(temp_endHr) > 3) || (strlen(temp_endMin) == 0 || strlen(temp_endMin) > 3) || (strlen(temp_endDaytime) == 0 || strlen(temp_endDaytime) > 3)) {
			printf (ANSI_COLOR_RED"  --------------------------------------\n  Invalid Input! Try Again!\n  --------------------------------------\n"ANSI_COLOR_RESET);
			goto repeat2;
		}

	temp_startHr[strlen(temp_startHr)] = '\0'; temp_endHr[strlen(temp_endHr)] = '\0';
	temp_startMin[strlen(temp_startMin)] = '\0'; temp_endMin[strlen(temp_endMin)] = '\0';
	temp_startDaytime[1] = '\0'; temp_endDaytime[1] = '\0';
	timeStartHour = checkString(temp_startHr); timeStartMin = checkString(temp_startMin); timeStartDaytime = checkString(temp_startDaytime);
	timeEndHour = checkString(temp_endHr); timeEndMin = checkString(temp_endMin); timeEndDaytime = checkString(temp_endDaytime);
	
	if (timeStartHour == 0 && timeStartMin == 0 && timeStartDaytime == 0 && timeEndHour == 0 && timeEndMin == 0 && timeEndDaytime == 0) {
		*sMH = (atoi(temp_startHr)*100) + atoi(temp_startMin);
			if (atoi(temp_startHr) == 12 && atoi(temp_startDaytime) == 1) *sMH = *sMH * 0;
			else if (atoi(temp_startDaytime) == 1) *sMH = *sMH * 1;
			else if (atoi(temp_startDaytime) == 2) *sMH = *sMH + 1200;
			else printf (ANSI_COLOR_RED"Invalid Daytime!\n"ANSI_COLOR_RESET);
		*eMH = (atoi(temp_endHr)*100) + atoi(temp_endMin);
			if (atoi(temp_endHr) == 12 && atoi(temp_endDaytime) == 1) *eMH = *eMH * 0;
			else if (atoi(temp_endDaytime) == 1) *eMH = *eMH * 1;
			else if (atoi(temp_endDaytime) == 2) *eMH = *eMH + 1200;
			else printf (ANSI_COLOR_RED"Invalid Daytime!\n"ANSI_COLOR_RESET);
		//------------------------------------------------------------------------------------ STRING TRANSFORMATION

		if (strlen(temp_startHr) > 2) temp_startHr[2] = '\0';
		if (strlen(temp_endHr) > 2) temp_endHr[2] = '\0';
		if (strlen(temp_startMin) > 2) temp_startMin[2] = '\0';
		if (strlen(temp_endMin) > 2) temp_endMin[2] = '\0';

		if (atoi(temp_startHr) < 10 && (atoi(temp_startDaytime) == 1 || atoi(temp_startDaytime) == 2)) {
			strcpy(newString,"0"); strcat (newString,temp_startHr); strcpy(temp_startHr, newString);
		} else if (atoi(temp_startHr) == 12 && atoi(temp_startDaytime) == 1) {
			strcpy(newString,"00"); newString[2] = '\0'; strcpy(temp_startHr, newString);
		}
		
		if (atoi(temp_startMin) == 0) {
			strcpy(newString,"00"); newString[2] = '\0'; strcpy(temp_startMin, newString);
		} else if (atoi(temp_startMin) < 10) {
			strcpy(newString,"0"); strcat (newString,temp_startMin); strcpy(temp_startMin, newString);
		}

		if (atoi(temp_endHr) < 10 && (atoi(temp_endDaytime) == 1 || atoi(temp_endDaytime) == 2)) {
			strcpy(newString,"0"); strcat (newString,temp_endHr); strcpy(temp_endHr, newString);
		} else if (atoi(temp_endHr) == 12 && atoi(temp_endDaytime) == 1) {
			strcpy(newString,"00"); newString[2] = '\0'; strcpy(temp_endHr, newString);
		}
		
		if (atoi(temp_endMin) == 0) {
			strcpy(newString,"00"); newString[2] = '\0'; strcpy(temp_endMin, newString);
		} else if (atoi(temp_endMin) < 10) {
			strcpy(newString,"0"); strcat (newString,temp_endMin); strcpy(temp_endMin, newString);
		}

		strcpy(sHour, temp_startHr); strcpy(eHour, temp_endHr);
		strcpy(sMin, temp_startMin); strcpy(eMin, temp_endMin);
		*sDaytime = atoi(temp_startDaytime); *eDaytime = atoi(temp_endDaytime);

	} else if (timeStartHour != 0 || timeStartMin != 0 || timeStartDaytime != 0) {
		printf (ANSI_COLOR_RED"  --------------------------------------\n  Invalid Input! Try Again!\n  --------------------------------------\n"ANSI_COLOR_RESET);
		goto repeat1;
	} else if (timeEndHour != 0 || timeEndMin != 0 || timeEndDaytime != 0) {
		printf (ANSI_COLOR_RED"  --------------------------------------\n  Invalid Input! Try Again!\n  --------------------------------------\n"ANSI_COLOR_RESET);
		goto repeat2;
	}
	
	free(temp_startHr); free (temp_startMin); free (temp_startDaytime);
	free(temp_endHr); free (temp_endMin); free (temp_endDaytime); free (newString);
}

//	[FUNCTION DEFINITION] This function is used to get the classes' day frequency.
void getDays (char *days, int *numberOfDays) {
	
	int i, j, weekdays[6] = {1,2,3,4,5,6}; int choice; char *temp_days = NULL;
	int zeroDone = -1, oneDone = -1, twoDone = -1, threeDone = -1, fourDone = -1, fiveDone = -1;
	printf ("\n  How many days in a week does the subject occur?\n  Answer: "); scanf ("%d", numberOfDays);

	for (i=0; i<(*numberOfDays); i++) {

		repeat3:
		// printing of choices
		printf ("  Days: {");
		for (j=0; j<((sizeof(weekdays))/4); j++) {
			switch (j) {
				case 0: if (zeroDone != 0) {
							printf (" [%d] ", j+1);
							printf("Monday"); } break;
				case 1: if (oneDone != 0) {
						 printf (" [%d] ", j+1);
						printf("Tuesday"); } break;
				case 2: if (twoDone != 0) { printf (" [%d] ", j+1);
						printf("Wednesday"); } break;
				case 3: if (threeDone != 0) { printf (" [%d] ", j+1);
						printf("Thursday"); } break;
				case 4: if (fourDone != 0) { printf (" [%d] ", j+1);
						printf("Friday"); } break;
				case 5:  if (fiveDone != 0) { printf (" [%d] ", j+1);
						printf("Saturday"); } break;
				default: break;
			}
		} printf (" }\n");

		// user input
		printf ("  Choose Day: "); scanf ("%d", &choice);
		if (temp_days == NULL){
			temp_days = (char *) malloc (sizeof(char));
			if (choice == 1) {
				strcpy (temp_days, "M");
				zeroDone = 0;
			} else if (choice == 2) {
				strcpy (temp_days, "T");
				oneDone = 0;
			} else if (choice == 3) {
				strcpy (temp_days, "W");
				twoDone = 0;
			} else if (choice == 4) {
				strcpy (temp_days, "Th");
				threeDone = 0;
			} else if (choice == 5) {
				strcpy (temp_days, "F");
				fourDone = 0;
			} else if (choice == 6) {
				strcpy (temp_days, "S");
				fiveDone = 0;
			} else {
				printf (ANSI_COLOR_RED"  Invalid Input! Try Again!\n"ANSI_COLOR_RESET);
				goto repeat3;
			}
		} else {
			if (choice == 1) {
				strcat (temp_days, "M");
				zeroDone = 0;
			} else if (choice == 2) {
				strcat (temp_days, "T");
				oneDone = 0;
			} else if (choice == 3) {
				strcat (temp_days, "W");
				twoDone = 0;
			} else if (choice == 4) {
				strcat (temp_days, "Th");
				threeDone = 0;
			} else if (choice == 5) {
				strcat (temp_days, "F");
				fourDone = 0;
			} else if (choice == 6) {
				strcat (temp_days, "S");
				fiveDone = 0;
			} else {
				printf (ANSI_COLOR_RED"  Invalid Input! Try Again!\n"ANSI_COLOR_RESET);
				goto repeat3;
			}
		}
	}
	temp_days[strlen(temp_days)] = '\0';
	strcpy(days,temp_days);
}