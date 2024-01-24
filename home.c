/*
.										UNIVERSITY OF THE PHILIPPINES LOS BANOS
.									Computer Science 21 - Fundamentals of Programming
.											First Semester A.Y. 2016-2017
.			Creator:	BATICOS, Andric Quinn Sargento
.					2015-13764 / 09291720966
.					BS Computer Science - College of Arts and Sciences
.					
.			Program Title: SIETE?: Teacher-to-Class Management System 
.			
.			Program Description: This program creates an application that manages the assignment of classes to teachers.
.                                  The application aims to control the number of classes assigned to a teacher depending on the
.							   maximum allowed units a teacher can take for the semester.
*/


// --------------------------------------------------------------------------------------------- Header Files
	// Library Imports
		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>
		#include <ctype.h>
	
	// User-defined Functions
	
		#define ANSI_COLOR_GREEN   "\x1b[32m"
		#define ANSI_COLOR_RED     "\x1b[31m"
		#define ANSI_COLOR_YELLOW  "\x1b[33m"
		#define ANSI_COLOR_BLUE    "\x1b[34m"
		#define ANSI_COLOR_RESET   "\x1b[0m"
		#define clear() printf("\033[H\033[J")
		#define minilinediv() printf(ANSI_COLOR_GREEN"  =========================================\n"ANSI_COLOR_RESET)
		#define linediv() printf(ANSI_COLOR_GREEN"\t=========================================================="ANSI_COLOR_RESET)
		#define newline() printf ("\n")
	
	// File Imports (User-functions from different files)
		#include "input.h"
		#include "structures.h"
		#include "functions.h"

// --------------------------------------------------------------------------------------------- Function Prototypes

	//	TEACHER FUNCTIONS
	struct teacherInfo *createTEACHER(struct teacherInfo *);

	//	CLASS FUNCTIONS
	struct classInfo *createCLASS(struct teacherInfo *);

	//	MULTIPURPOSE FUNCTIONS
	void viewAll (struct teacherInfo *, int code);

// --------------------------------------------------------------------------------------------- Main Program
int main () {
	
	//	====================================================================================== Linked List Initialization

		//	TEACHER LIST --> [This will initialize an empty list of teachers that will serve as the storage for information.]
			TEACHER *headTeacher; TEACHER *newNodeT; CLASS *newNodeC;
			headTeacher = NULL; TEACHER *p; CLASS *q;
	
	//	Initialization
	int mainChoice, viewChoice, linkedlistCount = 0;
	char newfile[25]; char newstring[100];

	// ----------------------------------------------------------------------------- FILE LOADING
	FILE *fPointer = NULL;
	int i, limitLoop = 0, size = 0;

	fPointer = fopen ("teachers.txt", "r");

	if (fPointer != NULL) {
		fscanf (fPointer, "%d", &size);
		p = headTeacher;
		while (!feof(fPointer)) {

			newNodeT = (struct teacherInfo *) malloc (sizeof(struct teacherInfo));
			fscanf (fPointer,"%s", newNodeT->person.firstName);
			fscanf (fPointer,"%s", newNodeT->person.lastName);
			fscanf (fPointer,"%s", newNodeT->EN);
			fscanf (fPointer,"%f", &newNodeT->unitsAllowed);
			fscanf (fPointer,"%d", &newNodeT->studentsAllowed);
			q = newNodeT->subjects;

	        if(headTeacher == NULL){
	            p = headTeacher = newNodeT;
	        } else {
	            p = p->next = newNodeT;
	            newNodeT->next = headTeacher; headTeacher->prev = newNodeT;
	        }
			if (limitLoop == size) break;
			else limitLoop++;
    	}

	} else printf (ANSI_COLOR_RED"File does not exist!\n"ANSI_COLOR_RESET);

	fclose (fPointer);
	
	do {
		clear(); newline(); linediv(); newline();
		printf ("\t\tSIETE: Teacher-to-Class Management System\n"ANSI_COLOR_RESET); linediv(); newline();
		printf ("\t[1] Add a Teacher\n\t[2] Add a Class\n\t[3] View Teachers\n\t[4] View Classes\n\t[5] Delete Teacher\n\t[6] Delete Classes\n\t[7] Exit\n");
		linediv(); newline(); printf ("\tChoice: "); scanf ("%d", &mainChoice);  getchar();
		
		switch (mainChoice) {
			case 1: 	newNodeT = createTEACHER(headTeacher); // creates a new node to be inserted with teacher info
						if (newNodeT != NULL) {

							if (headTeacher == NULL) {
								headTeacher = newNodeT;
								headTeacher->next = newNodeT; headTeacher->prev = newNodeT;
							} else if (headTeacher->next == headTeacher) {
								newNodeT->next = headTeacher; newNodeT->prev = headTeacher;
								headTeacher->next = newNodeT; headTeacher->prev = newNodeT;
							} else {
								p = headTeacher;
								while (p->next != headTeacher) p = p->next;
								p->next = newNodeT; newNodeT->prev = p;
								headTeacher->prev = newNodeT; newNodeT->next = headTeacher;
							}
							//---------------------------------------------- NEW FILE MAKING
							FILE *fPointer = NULL;
							strcpy (newfile, "classes/");
							strcat (newfile, newNodeT->EN);
							strcat (newfile, ".txt");
							newfile[strlen(newfile)] = '\0';
							fPointer = fopen (newfile, "w");
							fclose (fPointer);

						} else free(newNodeT);
						break;
			case 2:		newNodeC = createCLASS(headTeacher); // creates a new node to be inserted with class info
						struct teacherInfo *p; struct classInfo *q;
						if (newNodeC == NULL) {
							free(newNodeC);
						} else {
							//---------------------------------------------- NEW FILE MAKING
							FILE *fPointerC = NULL;
							strcpy (newfile, "classes/");
							strcat (newfile, newNodeC->linkRoot->EN);
							strcat (newfile, ".txt");
							newfile[strlen(newfile)] = '\0';
							fPointerC = fopen (newfile, "w");
							//--------------------------------------------------------------- COUNTING OF TOTAL NUMBER OF CLASSES
							linkedlistCount = 0; q = newNodeC->linkRoot->subjects;
							if (q == NULL) {
								linkedlistCount = 0;
							} else if (q->linkForward == NULL) {
								linkedlistCount = 1;
							} else if (q != NULL) {
								do {
									linkedlistCount = linkedlistCount + 1;
									q = q->linkForward;
								} while (q != NULL);
							}

							fprintf (fPointerC, "%d\n", linkedlistCount);

							//--------------------------------------------------------------- APPENDING ALL CLASS INFO
							if (linkedlistCount > 0) {
								q = newNodeC->linkRoot->subjects;
								do {
									fprintf (fPointerC, "%s\n", q->courseCode);
									fprintf (fPointerC, "%s\n", q->section);
									fprintf (fPointerC, "%.2f\n", q->unitsOfClass);
									fprintf (fPointerC, "%d\n", q->studentsInClass);
									fprintf (fPointerC, "%s:%s", q->schedule.timeStart.hour, q->schedule.timeStart.minutes);
									if (q->schedule.timeStart.daytime == 1) fprintf (fPointerC,"AM"); else fprintf (fPointerC,"PM");
									fprintf (fPointerC,"-%s:%s", q->schedule.timeEnd.hour, q->schedule.timeEnd.minutes);
									if (q->schedule.timeEnd.daytime == 1) fprintf (fPointerC,"AM\n"); else fprintf (fPointerC,"PM\n");
									fprintf (fPointerC, "%d-%d\n", q->schedule.timeStart.militaryHour, q->schedule.timeEnd.militaryHour);
									fprintf (fPointerC, "%s\n",q->schedule.days);
									q = q->linkForward;
								} while (q != NULL);
							}
							fclose (fPointerC);
						}
						break;
			case 3:		do {	// sub-menu for viewing teachers
							clear(); newline(); linediv(); newline();
							printf ("\t\tSIETE: Teacher-to-Class Management System\n\t\t\t     VIEW TEACHERS\t\n"); linediv(); newline();
							printf ("\t[1] View All Teachers\n\t[2] View Specific Teacher\n\t[3] View Teacher of Class\n\t[4] View Teachers who already have 3 subjects\n\t[5] Exit\n");
							linediv(); newline(); printf ("\tChoice: "); scanf ("%d", &viewChoice); getchar();
							
							switch (viewChoice) {
								case 1: viewAll(headTeacher,1); break;
								case 2: searchAndDo(headTeacher,1); break;
								case 3: searchAndDo(headTeacher,5); break;
								case 4: searchAndDo(headTeacher,6); break;
								case 5: break;
								default: viewChoice = 0; break;
							}
							
						} while (viewChoice != 5); break;
			case 4:		do {	// sub-menu for viewing class
							clear(); newline(); linediv(); newline();
							printf ("\t\tSIETE: Teacher-to-Class Management System\n\t\t\t     VIEW CLASSES\t\n"); linediv(); newline();
							printf ("\t[1] View All Classes\n\t[2] View Specific Class\n\t[3] View Classes of Subjects\n\t[4] Exit\n");
							linediv(); newline(); printf ("\tChoice: "); scanf ("%d", &viewChoice); getchar();
							
							switch (viewChoice) {
								case 1: viewAll(headTeacher,2); break;
								case 2: searchAndDo(headTeacher,3); break;
								case 3: searchAndDo(headTeacher,4); break;
								case 4: break;
								default: viewChoice = 0; break;
							}
							
						} while (viewChoice != 4); break;
			case 5:		searchAndDo(headTeacher,2); break; // delete teacher
			case 6:		searchAndDo(headTeacher,7); break; // delete class
			case 7: 	break;
			default:	mainChoice = 0; break;
		}

		if (headTeacher != NULL) {
			//------------------------------------------------------------------------------------------------------	FIlE UPDATING

			FILE *fPointer = NULL;
			fPointer = fopen ("teachers.txt", "w");

			//--------------------------------------------------------------- COUNTING OF TOTAL NUMBER OF TEACHERS
			linkedlistCount = 0; p = headTeacher;
			if (headTeacher == NULL) {
				linkedlistCount = 0;
			} else if (headTeacher->next == headTeacher) {
				linkedlistCount = 1;
			} else if (headTeacher != NULL) {
				do {
					linkedlistCount = linkedlistCount + 1;
					p = p->next;
				} while (p != headTeacher);
			}

			fprintf (fPointer, "%d\n", linkedlistCount);

			//--------------------------------------------------------------- APPENDING ALL TEACHER INFO
			if (linkedlistCount > 0) {
				p = headTeacher;
				do {
					fprintf (fPointer, "%s\n", p->person.firstName);
					fprintf (fPointer, "%s\n", p->person.lastName);
					fprintf (fPointer, "%s\n", p->EN);
					fprintf (fPointer, "%.2f\n", p->unitsAllowed);
					fprintf (fPointer, "%d\n", p->studentsAllowed);
					p = p->next;
				} while (p != headTeacher);
			}

			fclose (fPointer);
	}

	} while (mainChoice != 7);

	//------------------------------------------------------------------------ FREEING NODES
	p = headTeacher; struct teacherInfo *freeT; struct classInfo *freeC;
	if (p!=NULL) {
		do {
			q = p->subjects;
			if (q!=NULL) {
				do {
					freeC = q;
					q = q->linkForward;
					free (freeC);
				} while (q=NULL);
			}
			freeT = p;
			p = p->next;
		} while (p!=headTeacher);
	}

	clear();
	return 0;
	
}