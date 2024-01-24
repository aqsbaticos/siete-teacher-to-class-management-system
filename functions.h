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
.			File Description: 	This file contains all functions used for the main program.
*/

// ---------------------------------------------------------------------------------------------------------- FUNCTIONS

//---------- FUNCTION # 1 ----------	[FUNCTION DEFINITION] This function asks for user input about the teacher's information and creates a new node.
struct teacherInfo *createTEACHER(struct teacherInfo *headTeacher) {
	
	int choice, unique; struct teacherInfo *p = NULL;
	
	struct teacherInfo *newTeacher; struct teacherInfo *emptyNode = NULL;
	newTeacher= (struct teacherInfo *) malloc (sizeof(struct teacherInfo));
	newTeacher->next = newTeacher; newTeacher->prev = newTeacher;
	
	do {
	
		//-----------------------------------------------------------------------------------------------------------	USER INPUT
		clear(); newline(); minilinediv();
		printf ("\t     INFORMATION SHEET\n"); minilinediv(); newline();
		getName(newTeacher->person.firstName, newTeacher->person.lastName); getEN(newTeacher->EN); getLimit(&newTeacher->unitsAllowed, &newTeacher->studentsAllowed, 1);
		newTeacher->next = NULL; newTeacher->prev = NULL; newTeacher->subjects = NULL;
		//----------------------------------------------------------------------------------------------------------- CONFIRMATION
		clear(); newline(); minilinediv();
		printf ("\t\tNEW TEACHER\n"); minilinediv();
		printf ("  Name: %s %s\n", newTeacher->person.firstName, newTeacher->person.lastName);
		printf ("  Employee Number: %s\n", newTeacher->EN);
		printf ("  Units Allowed: %.2f\n", newTeacher->unitsAllowed);
		printf ("  Students Allowed: %d\n", newTeacher->studentsAllowed);
		newTeacher->subjectLimit = 3;
		minilinediv();
		printf ("  Are you sure with your input?\n  [1] Yes | [2] No\n  Choice: ");
		scanf ("%d", &choice); getchar();
		
		if (choice == 1) {
			p = headTeacher;
			if (p == NULL) {
				clear(); newline();
				printf ("  --------------------------------------------\n");
				printf (ANSI_COLOR_BLUE"  \t\tINPUT SUCCESSFUL!\n"ANSI_COLOR_RESET);
				printf ("  --------------------------------------------\n  Press <ENTER> to continue...");
				while (getchar()!= '\n');													// First Use in this program: ENTER key
				return newTeacher;
			} else {
				do {
					unique = strcmp(newTeacher->EN, p->EN);
					if (unique == 0) {
						clear(); newline();
						printf ("  --------------------------------------------\n");
						printf (ANSI_COLOR_RED"  INPUT FAILED!\n  EMPLOYEE NUMBER ALREADY IN THE LIST.\n  --------------------------------------------\n"ANSI_COLOR_RESET);
						printf ("  Press <ENTER> to continue...");
						while (getchar()!= '\n');
						return emptyNode;
					}
					p = p->next;
				} while (p!=headTeacher);
				p = NULL; free (p);					// -- frees the allocated memory for traversing
				clear(); newline();
				printf ("  --------------------------------------------\n");
				printf (ANSI_COLOR_BLUE"  \t\tINPUT SUCCESSFUL!\n"ANSI_COLOR_RESET);
				printf ("  --------------------------------------------\n  Press <ENTER> to continue...");
				while (getchar()!= '\n');
				return newTeacher;
			}
		} else {
			repeatQuestion:
				clear(); newline();
				printf (" Do you want to continue?\n [1] Yes | [2] No\n Choice: "); scanf ("%d", &choice); getchar();
				if (choice == 2) {
					p = NULL; free (p);				// -- frees the allocated memory for traversing
					clear(); newline(); minilinediv();
					printf (ANSI_COLOR_RED"  INPUT CANCELLED!\n"ANSI_COLOR_RESET);
					minilinediv();
					printf ("  Press <ENTER> to continue...");
					while (getchar()!= '\n');
					return emptyNode;
				} else if (choice == 1) {
					choice = 0;
				} else goto repeatQuestion;
		}
	} while (choice != 2);
}

//---------- FUNCTION # 2 ----------	[FUNCTION DEFINITION] This function will be used to get the print specified information.
void viewAll (struct teacherInfo *headTeacher, int code) {
	
	int choice; struct teacherInfo *p = NULL; struct classInfo *q; int flag = -1, confirmed = -1;
	
	if (code == 1) {	// ===================================== CODE 1: View All Teachers
		if (headTeacher == NULL) {
			clear(); newline();
			printf ("  --------------------------------------------\n");
			printf (ANSI_COLOR_RED"  THERE ARE NO TEACHERS LISTED IN THE PROGRAM.\n"ANSI_COLOR_RESET);
			printf ("  --------------------------------------------\n");
			printf ("  Press <ENTER> to continue...");
		    while (getchar()!= '\n');
		} else {	
			p = headTeacher;
			clear(); newline(); minilinediv(); printf ("\t     LIST OF TEACHERS"); newline(); minilinediv();
			do {
				q = p->subjects;
				newline(); minilinediv();
				printf ("  Name: %s, %s\n", p->person.lastName, p->person.firstName);
				printf ("  Employee Number: %s\n", p->EN);
				printf ("  Units Allowed: %.2f\n", p->unitsAllowed);
				printf ("  Students Allowed: %d", p->studentsAllowed);
				newline();
				printf ("  #---------------- SUBJECTS ----------------#\n");
				if (q == NULL) printf ("  NONE");
				else {
					printf ("  | SUBJECT | SECTION | UNITS | TIME/DAY\n");
					do {
						printf ("  | %s | %s | %.2f | ", q->courseCode, q->section, q->unitsOfClass);
						printf ("%s:%s", q->schedule.timeStart.hour, q->schedule.timeStart.minutes);
						if (q->schedule.timeStart.daytime == 1) printf ("AM"); else printf ("PM");
						printf ("-%s:%s", q->schedule.timeEnd.hour, q->schedule.timeEnd.minutes);
						if (q->schedule.timeEnd.daytime == 1) printf ("AM"); else printf ("PM");
						printf (" %s\n",q->schedule.days);
						q = q->linkForward;
					} while (q != NULL);
				}
				newline(); minilinediv();
				p = p-> next;
			} while (p != headTeacher);
			printf ("  Press <ENTER> to continue...");
			while (getchar()!= '\n');
		}
	} else if (code == 2) {	// ===================================== CODE 2: View All Classes
		if (headTeacher == NULL) {
			clear(); newline();
			printf ("  --------------------------------------------\n");
			printf (ANSI_COLOR_RED"  THERE ARE NO CLASSES LISTED IN THE PROGRAM.\n"ANSI_COLOR_RESET);
			printf ("  --------------------------------------------\n");
			printf ("  Press <ENTER> to continue...");
		    while (getchar()!= '\n');
		} else {	
			p = headTeacher;
			clear(); newline(); minilinediv(); printf ("\t     LIST OF CLASSES"); newline(); minilinediv();
			do {
				q = p->subjects;
				if (q != NULL) {
					flag = 0; confirmed = 0;
				} else flag = -1;

				if (confirmed == -1 && p->next == headTeacher) printf (ANSI_COLOR_RED"  EMPTY!\n"ANSI_COLOR_RESET);
				else if (flag == 0) {
					newline();
					do {
						newline();
						printf ("  Course Code: %s\n", q->courseCode);
						printf ("  Section: %s\n", q->section);
						printf ("  Course Credits: %.2f\n", q->unitsOfClass);
						printf ("  Maximum Students Allowed: %d\n", q->studentsInClass);
						printf ("  Time: %s:%s", q->schedule.timeStart.hour, q->schedule.timeEnd.minutes);
						if (q->schedule.timeStart.daytime == 1) printf ("AM"); else printf ("PM");
						printf ("-%s:%s", q->schedule.timeEnd.hour, q->schedule.timeEnd.minutes);
						if (q->schedule.timeEnd.daytime == 1) printf ("AM\n"); else printf ("PM\n");
						printf ("  Days: %s\n",q->schedule.days);
						printf ("  Professor: %s %s\n", q->linkRoot->person.firstName, q->linkRoot->person.lastName);
						q = q->linkForward;
					} while (q != NULL);
				}
				p = p->next;
			} while (p != headTeacher);
			newline(); minilinediv();
			printf ("  Press <ENTER> to continue...");
			while (getchar()!= '\n');
		}
	}
}

//---------- FUNCTION # 3 ----------	[FUNCTION DEFINITION] This function will be search and view/delete a node.
void searchAndDo(struct teacherInfo *headTeacher, int code) {
	
	clear(); newline(); minilinediv();
	int flag = -1, flagOnce, mark1 = -1, mark2 = -1; char *EN_temp; EN_temp = (char *) malloc (sizeof(char));
	char *CC_temp; CC_temp = (char *) malloc (sizeof(char));
	char *S_temp; S_temp = (char *) malloc (sizeof(char));
	
	if (headTeacher == NULL) {
		clear(); newline();
		printf ("  --------------------------------------------\n");
		if (code == 1 || code == 2 || code == 5 || code == 6) printf (ANSI_COLOR_RED"\t\tTEACHER LIST EMPTY.\n"ANSI_COLOR_RESET);
		else if (code ==3 || code == 4) printf (ANSI_COLOR_RED"\t\tCLASS LIST EMPTY.\n"ANSI_COLOR_RESET);
		printf ("  --------------------------------------------\n");
		free (EN_temp); printf ("  Press <ENTER> to continue...");
		while (getchar() != '\n');
	} else {
		if (code == 1) { // ------------------------------------------------------------------------------------------- [VIEW TEACHER]
			printf ("  Enter Employee Number To Be Viewed: "); scanf ("%s", EN_temp); getchar();
			EN_temp[9] = '\0'; minilinediv();
			struct teacherInfo *p = headTeacher; struct classInfo *q;
			
				do {

					flag = strcmp (p->EN, EN_temp);

					if (flag == 0) {
						
						clear(); newline(); minilinediv();
						printf ("\t     SEARCH COMPLETE!\n"); minilinediv();
						printf ("  Name: %s %s\n", p->person.firstName, p->person.lastName);
						printf ("  Employee Number: %s\n", p->EN);
						printf ("  Units Allowed: %.2f\n", p->unitsAllowed);
						printf ("  Students Allowed: %d", p->studentsAllowed);
						newline(); q = p->subjects;
						printf ("  #-------------- SUBJECTS --------------#\n");
						if (q == NULL) printf ("  NONE");
						else {
							printf ("  | SUBJECT | SECTION | UNITS | TIME/DAY\n");
							do {
								printf ("  | %s | %s | %.2f | ", q->courseCode, q->section, q->unitsOfClass);
								printf ("%s:%s", q->schedule.timeStart.hour, q->schedule.timeStart.minutes);
								if (q->schedule.timeStart.daytime == 1) printf ("AM"); else printf ("PM");
								printf ("-%s:%s", q->schedule.timeEnd.hour, q->schedule.timeEnd.minutes);
								if (q->schedule.timeEnd.daytime == 1) printf ("AM"); else printf ("PM");
								printf ("  %s\n",q->schedule.days);
								q = q->linkForward;
							} while (q != NULL);
						}
						minilinediv();
						printf ("  Press <ENTER> to continue...");
						while (getchar() != '\n');
						break;
					}
					p = p-> next;
				} while (p != headTeacher);
				free(EN_temp);
		} else if (code == 2) { // ---------------------------------------------------------------------------------- [DELETE TEACHER]
			printf ("  Enter Employee Number To Be Deleted: "); scanf ("%s", EN_temp); getchar();
			EN_temp[9] = '\0'; minilinediv(); char *fileRemover;
			fileRemover = (char *) malloc (sizeof(char));
			struct teacherInfo *p = headTeacher;
				
				p = headTeacher;
				do {
					flag = strcmp (p->EN, EN_temp);
					if (flag == 0) {
						
						if (p!= headTeacher) {
				            p->next->prev = p->prev;
				            p->prev->next = p->next;
				            free(p);
				        } else {
				        	if (p->next == p && p->prev == p) {
					            free(p);
					            headTeacher = NULL;
					        } else {
					        	headTeacher->next->prev = headTeacher->prev;
					            headTeacher->prev->next = headTeacher->next;
					            headTeacher = headTeacher->next;
					            free(p);
					        } 
				        }

				        strcpy (fileRemover, "classes/");
				        strcat (fileRemover,EN_temp);
				        strcat (fileRemover,".txt");
				        remove (fileRemover);
					
						// USER CONFIRMATION PRINT
						clear(); newline();
						printf ("  TEACHER DELETED!\n");
						printf ("  Press <ENTER> to continue...");
						while (getchar() != '\n');
						break;
					}
					p = p->next;
				} while (p != headTeacher);
				free(EN_temp);
		} else if (code == 3) { // ---------------------------------------------------------------------------------- [VIEW CLASS]
			printf ("  Enter Course Code [no spaces]: "); scanf ("%s", CC_temp); getchar();
			printf ("  Enter Section [ex. UV-1L]: "); scanf ("%s", S_temp); getchar();
			CC_temp[strlen(CC_temp)] = '\0'; S_temp[strlen(S_temp)] = '\0';minilinediv();
			uppercaseString(CC_temp); uppercaseString(S_temp);
			struct teacherInfo *p = headTeacher; struct classInfo *q;
			
				do {
					q = p->subjects;
					while (q!=NULL) {
						mark1 = strcmp (q->courseCode, CC_temp); mark2 = strcmp (q->section, S_temp);
						if (mark1 == 0 & mark2 == 0) {
							clear(); newline(); minilinediv();
							printf ("\t     SEARCH COMPLETE!\n"); minilinediv();
							printf ("  Course Code: %s\n", q->courseCode);
							printf ("  Section: %s\n", q->section);
							printf ("  Course Credits: %.2f\n", q->unitsOfClass);
							printf ("  Maximum Students Allowed: %d\n", q->studentsInClass);
							printf ("  Time: %s:%s", q->schedule.timeStart.hour, q->schedule.timeStart.minutes);
							if (q->schedule.timeStart.daytime == 1) printf ("AM"); else printf ("PM");
							printf ("-%s:%s", q->schedule.timeEnd.hour, q->schedule.timeEnd.minutes);
							if (q->schedule.timeEnd.daytime == 1) printf ("AM\n"); else printf ("PM\n");
							printf ("  Days: %s\n",q->schedule.days);
							printf ("  Professor: %s %s", q->linkRoot->person.firstName, q->linkRoot->person.lastName);
							newline(); minilinediv();
							printf ("  Press <ENTER> to continue...");
							while (getchar() != '\n');
							break;
						}
						q = q->linkForward;
					}
					p = p-> next;
				} while (p != headTeacher);
		} else if (code == 4) { // ---------------------------------------------------------------------------------- [VIEW ALL CLASS OF SUBJECT]
			printf ("  Enter Course Code: "); scanf ("%s", CC_temp); getchar();
			CC_temp[strlen(CC_temp)] = '\0'; minilinediv(); uppercaseString(CC_temp);
			struct teacherInfo *p; struct classInfo *q; flagOnce = -1;
			p = headTeacher;
			clear(); newline(); minilinediv();
			printf ("\t     CLASSES OF %s\n", CC_temp); minilinediv();
				do {
					q = p->subjects;
					while (q!=NULL) {
						mark1 = strcmp (q->courseCode, CC_temp);
						if (mark1 == 0) {
							printf ("  Course Code: %s\n", q->courseCode);
							printf ("  Section: %s\n", q->section);
							printf ("  Course Credits: %.2f\n", q->unitsOfClass);
							printf ("  Maximum Students Allowed: %d\n", q->studentsInClass);
							printf ("  Time: %s:%s", q->schedule.timeStart.hour, q->schedule.timeStart.minutes);
							if (q->schedule.timeStart.daytime == 1) printf ("AM"); else printf ("PM");
							printf ("-%s:%s", q->schedule.timeEnd.hour, q->schedule.timeEnd.minutes);
							if (q->schedule.timeEnd.daytime == 1) printf ("AM\n"); else printf ("PM\n");
							printf ("  Days: %s\n",q->schedule.days);
							printf ("  Professor: %s %s", q->linkRoot->person.firstName, q->linkRoot->person.lastName);
							if (flagOnce == -1) flagOnce = 0;
							newline(); minilinediv();
						}
						q = q->linkForward;
					}
					p = p-> next;
				} while (p != headTeacher);
			printf ("  Press <ENTER> to continue...");
			while (getchar() != '\n');	
		} else if (code == 5) { // ---------------------------------------------------------------------------- [VIEW TEACHER OF A CLASS]
			printf ("  Enter Course Code [no spaces]: "); scanf ("%s", CC_temp); getchar();
			printf ("  Enter Section [ex. UV-1L]: "); scanf ("%s", S_temp); getchar();
			CC_temp[strlen(CC_temp)] = '\0'; S_temp[strlen(S_temp)] = '\0';minilinediv();
			uppercaseString(CC_temp); uppercaseString(S_temp);
			struct teacherInfo *p = headTeacher; struct classInfo *q;
			
				do {
					q = p->subjects;
					while (q!=NULL) {
						mark1 = strcmp (q->courseCode, CC_temp); mark2 = strcmp (q->section, S_temp);
						if (mark1 == 0 & mark2 == 0) {
							clear(); newline(); minilinediv();
							printf ("\t     SEARCH COMPLETE!\n"); minilinediv();
							printf ("  Name: %s %s\n", p->person.firstName, p->person.lastName);
							printf ("  Employee Number: %s\n", p->EN);
							printf ("  Units Allowed: %.2f\n", p->unitsAllowed);
							printf ("  Students Allowed: %d", p->studentsAllowed);
							newline(); q = p->subjects;
							printf ("  #-------------- SUBJECTS --------------#\n");
							if (q == NULL) printf ("  NONE");
							else {
								printf ("  | SUBJECT | SECTION | UNITS | TIME/DAY\n");
								do {
									printf ("  | %s | %s | %.2f | ", q->courseCode, q->section, q->unitsOfClass);
									printf ("%s:%s", q->schedule.timeStart.hour, q->schedule.timeStart.minutes);
									if (q->schedule.timeStart.daytime == 1) printf ("AM"); else printf ("PM");
									printf ("-%s:%s", q->schedule.timeEnd.hour, q->schedule.timeEnd.minutes);
									if (q->schedule.timeEnd.daytime == 1) printf ("AM"); else printf ("PM");
									printf ("  %s\n",q->schedule.days);
									q = q->linkForward;
								} while (q != NULL);
							}
							minilinediv();
							break;
						}
						q = q->linkForward;
					}
					p = p-> next;
				} while (p != headTeacher && (mark1 != 0 && mark2 != 0));
			printf ("  Press <ENTER> to continue...");
			while (getchar() != '\n');	
		} else if (code == 6) { // ----------------------------------------------------------------------- [VIEW TEACHERS W/ THREE SUBJECTS]
			struct teacherInfo *p; struct classInfo *q;
			p = headTeacher;
			clear(); newline(); minilinediv(); printf ("    LIST OF TEACHERS WITH THREE SUBJECTS"); newline(); minilinediv();
			do {
				if (p->subjectLimit == 0) {
					q = p->subjects;
					newline(); minilinediv();
					printf ("  Name: %s, %s\n", p->person.lastName, p->person.firstName);
					printf ("  Employee Number: %s\n", p->EN);
					printf ("  Units Allowed: %.2f\n", p->unitsAllowed);
					printf ("  Students Allowed: %d", p->studentsAllowed);
					newline();
					printf ("  #-------------- SUBJECTS --------------#\n");
					if (q == NULL) printf ("  NONE");
					else {
						printf ("  | SUBJECT | SECTION | UNITS | TIME/DAY\n");
						do {
							printf ("  | %s | %s | %.2f | ", q->courseCode, q->section, q->unitsOfClass);
							printf ("%s:%s", q->schedule.timeStart.hour, q->schedule.timeStart.minutes);
							if (q->schedule.timeStart.daytime == 1) printf ("AM"); else printf ("PM");
							printf ("-%s:%s", q->schedule.timeEnd.hour, q->schedule.timeEnd.minutes);
							if (q->schedule.timeEnd.daytime == 1) printf ("AM"); else printf ("PM");
							printf ("  %s\n",q->schedule.days);
							q = q->linkForward;
						} while (q != NULL);
					}
					minilinediv();
				}
				p = p->next;
			} while (p != headTeacher);
			printf ("  Press <ENTER> to continue...");
			while (getchar()!= '\n');

		} else if (code == 7) { // ---------------------------------------------------------------------------------- [DELETE CLASS]
			printf ("  Enter Course Code [no spaces]: "); scanf ("%s", CC_temp); getchar();
			printf ("  Enter Section [ex. UV-1L]: "); scanf ("%s", S_temp); getchar();
			CC_temp[strlen(CC_temp)] = '\0'; S_temp[strlen(S_temp)] = '\0'; minilinediv();
			uppercaseString(CC_temp); uppercaseString(S_temp);
			struct teacherInfo *p = headTeacher; struct classInfo *q; struct classInfo *r;
				
				p = headTeacher;

				do {
					q = p->subjects;
					while (q!=NULL) {
						mark1 = strcmp (q->courseCode, CC_temp); mark2 = strcmp (q->section, S_temp);

						if (mark1 == 0 & mark2 == 0) {
							clear(); newline(); minilinediv();
							if (q == p->subjects) {
								if (q->linkForward == NULL) {
						            r = q;
						            q = NULL;
						            free(r);
								} else {
									r = q;
									q = q->linkForward;
									free(r);
								}
					        } else {
					        	if (q->linkForward == NULL) {
					        		r = q;
					        		q = p->subjects;
					        		while (q->linkForward != r) {
					        			q = q->linkForward;
					        		} q->linkForward = NULL;
					        		free(r);
					        	} else {
					        		r = q;
					        		q = p->subjects;
					        		while (q->linkForward != r) {
					        			q = q->linkForward;
					        		} q->linkForward = q->linkForward->linkForward;
					        		free(r);
					        	}
					        }
					    }
						
						// USER CONFIRMATION PRINT
						clear(); newline();
						printf ("  CLASS DELETED!\n");
						printf ("  Press <ENTER> to continue...");
						while (getchar() != '\n');
						break;

						q = q->linkForward;
					}
					p = p->next;
				} while (p!=headTeacher);
		}
		
		if ((flag != 0 && (code == 1 || code == 2)) && headTeacher !=NULL) {
			printf (ANSI_COLOR_RED"  TEACHER NOT ON THE LIST!\n"ANSI_COLOR_RESET); minilinediv();
			printf ("  Press <ENTER> to continue...");
			while (getchar() != '\n');
		} else if ((code == 4 && flagOnce != 0) && headTeacher != NULL) {
			printf (ANSI_COLOR_RED"  CLASS NOT ON THE LIST!\n"ANSI_COLOR_RESET); minilinediv();
			printf ("  Press <ENTER> to continue...");
			while (getchar() != '\n');
		} else if (((mark1 != 0 || mark2 != 0) && (code == 3 || code == 5)) && headTeacher != NULL) {
			printf (ANSI_COLOR_RED"  CLASS NOT ON THE LIST!\n"ANSI_COLOR_RESET); minilinediv();
			printf ("  Press <ENTER> to continue...");
			while (getchar() != '\n');
		} 
	}
}

//---------- FUNCTION # 4 ----------	//	[FUNCTION DEFINITION] This function asks for user input about the class' information and creates a new node.
struct classInfo *createCLASS(struct teacherInfo *headTeacher) {
	
	int choice, unique1, unique2, unique3, unique4, unique5;
	int available = -1; struct teacherInfo *p = NULL; struct classInfo *q = NULL;
	char EN_choice[10];
	
	struct classInfo *newClass; struct classInfo *emptyNode = NULL;
	newClass= (struct classInfo *) malloc (sizeof(struct classInfo));
	
	do {
	
		//-----------------------------------------------------------------------------------------------------------	USER INPUT
		clear(); newline(); minilinediv();
		printf ("\t     INFORMATION SHEET\n"); minilinediv(); newline();
		getCCS(newClass->courseCode, newClass->section);
		getLimit (&newClass->unitsOfClass, &newClass->studentsInClass, 2);
		getTime(newClass->schedule.timeStart.hour, newClass->schedule.timeStart.minutes, &newClass->schedule.timeStart.daytime, &newClass->schedule.timeStart.militaryHour, newClass->schedule.timeEnd.hour, newClass->schedule.timeEnd.minutes, &newClass->schedule.timeEnd.daytime, &newClass->schedule.timeEnd.militaryHour);
		getDays(newClass->schedule.days, &newClass->schedule.numberOfDays);
		newClass->linkForward = NULL;
		//----------------------------------------------------------------------------------------------------------- CONFIRMATION
		clear(); newline(); minilinediv();
		printf ("\t\tNEW CLASS\n"); minilinediv();
		printf ("  Course Code: %s\n", newClass->courseCode);
		printf ("  Section: %s\n", newClass->section);
		printf ("  Units: %.2f\n", newClass->unitsOfClass);
		printf ("  No. of Students: %d\n", newClass->studentsInClass);
		printf ("  Time: %s:%s", newClass->schedule.timeStart.hour, newClass->schedule.timeStart.minutes);
		if (newClass->schedule.timeStart.daytime == 1) printf ("AM"); else printf ("PM");
		printf ("-%s:%s", newClass->schedule.timeEnd.hour, newClass->schedule.timeEnd.minutes);
		if (newClass->schedule.timeEnd.daytime == 1) printf ("AM\n"); else printf ("PM\n");
		printf ("  Days: %s\n", newClass->schedule.days);
		minilinediv();
		printf ("  Are you sure with your input?\n  [1] Yes | [2] No\n  Choice: ");
		scanf ("%d", &choice); getchar();
		
		if (choice == 1) {
			
			// ---------------------------------------------------------------------------------------------- CHECKING
			p = headTeacher;
			// [BLOCK DEFINITION] This block of code checks if the teachers' list is empty. The creation cancels when there are no teacher's in the list.
			if (p == NULL) {
				clear(); newline();
				printf ("  --------------------------------------------\n");
				printf (ANSI_COLOR_RED"  THERE ARE NO TEACHERS LISTED IN THE PROGRAM.\n"ANSI_COLOR_RESET);
				printf ("  --------------------------------------------\n");
				printf ("  Press <ENTER> to continue..."); while (getchar()!='\n');
				return emptyNode;	
			} else {

				//------------------------------------------------------------------------------------------------------BASIC CHECKS
				do {
					q = p->subjects;
					if (q != NULL) {
						do {
							unique1 = strcmp(newClass->courseCode, q->courseCode);
							unique2 = strcmp(newClass->section,q->section);
							if (unique1 == 0 && unique2 == 0) {
								clear(); newline();
								printf (ANSI_COLOR_RED" INPUT FAILED!\n CLASS ALREADY EXISTS.\n"ANSI_COLOR_RESET);
								printf (" Press <ENTER> to continue...");
								while (getchar()!= '\n');
								return emptyNode;
							}
							q = q->linkForward;
						} while (q!=NULL);
					}
					p = p->next;
				} while (p!=headTeacher);

				// [BLOCK DEFINITION] This block of code checks if there is an available teacher for the class.
				p = headTeacher;
				do {
					if ((p->unitsAllowed)-(newClass->unitsOfClass) < 0  || ((p->studentsAllowed)-(newClass->studentsInClass) < 0)) { 
							p = p->next;
					} else { // The loop stops here if it finds a teacher available for the class.
						available = 0;
						break;
					}
				} while (p!=headTeacher && available != 0);
					
				if (available != 0) {
					clear(); newline();
					printf (ANSI_COLOR_RED" INPUT FAILED!\n THERE ARE NO TEACHERS AVAILABLE FOR THE CLASS.\n"ANSI_COLOR_RESET);
					printf ("Press <ENTER> to continue...");
					while (getchar()!= '\n');
					return emptyNode;
				} else {
					clear(); newline();
					printf ("  --------------------------------------------\n");
					printf ("  |     AVAILABLE TEACHERS FOR THE SUBJECT   |\n");
					printf ("  --------------------------------------------\n");
					p = headTeacher;
					
					do {	//--------------- This block of code prints all the available teachers for the class.
						if ((p->unitsAllowed)-(newClass->unitsOfClass) >= 0  && ((p->studentsAllowed)-(newClass->studentsInClass) >= 0)) {
							newline();
							printf ("  Name: %s %s\n",p->person.firstName, p->person.lastName);
							printf ("  Employee Number: %s\n", p->EN);
							printf ("  Units Available: %.2f\n", p->unitsAllowed);
							printf ("  Allowable Students Left: %d\n", p->studentsAllowed);
						}
						p = p->next;
					} while (p!=headTeacher);
						
					minilinediv(); newline(); getEN(EN_choice);

					// This block of code executes when the user has chosen the employee number for the class.
					p = headTeacher;
					do {
						if (strcmp(EN_choice, p->EN) == 0) {	//-- program enters to this block of code if it sees a match.

							q = p->subjects; //------------------------------------------------------------- SECONDARY CHECKING
							
							unique4 = -1;	//==============# CHECK 1 [This block checks if the teacher will exceed his/her 3-subject limit.]
							
							if (q!=NULL) {
								do {
									unique3 = strcmp(q->courseCode, newClass->courseCode);
									if (unique3 == 0) unique4 = 0;
									q = q->linkForward;
								} while (q!=NULL);
										
								if (p->subjectLimit == 0) {
									if (unique4 != 0) {
										clear(); newline();
										printf (ANSI_COLOR_RED"  INPUT FAILED!\n  TEACHER'S SUBJECT is already on its limit.\n"ANSI_COLOR_RESET);
										printf ("  Press <ENTER> to continue...");
										while (getchar()!='\n');
										return emptyNode;
									}
								} else p->subjectLimit = p->subjectLimit-1;
							}  else p->subjectLimit = p->subjectLimit-1;

							q = p->subjects;
							unique5 = -1;	//===============# CHECK 2 [This block checks if the teacher will conflict the teacher's current time schedule.]
							if (q!=NULL) {
								do {
									if ((newClass->schedule.timeStart.militaryHour > q->schedule.timeStart.militaryHour && newClass->schedule.timeStart.militaryHour < q->schedule.timeEnd.militaryHour) ||
										(newClass->schedule.timeEnd.militaryHour > q->schedule.timeStart.militaryHour && newClass->schedule.timeEnd.militaryHour < q->schedule.timeEnd.militaryHour)) {
										if (strcmp(newClass->schedule.days,q->schedule.days) == 0) {
											clear(); newline();
											printf (ANSI_COLOR_RED"  INPUT FAILED!\n  Time/Day conflicts teacher's schedule.\n"ANSI_COLOR_RESET);
											printf ("  Press <ENTER> to continue...");
											while (getchar()!='\n');
											return emptyNode;
										}
									}
									q = q->linkForward;
								} while (q!=NULL);
							}


							clear(); newline();
							printf (" INPUT SUCCESSFUL!\n Press <ENTER> to continue...");

							// --- accessing the subject pointer in the node where the class is to be added
							q = p->subjects;
							if (q == NULL) {
								p->subjects = newClass;
								p->subjects->linkForward = NULL;
								p->subjects->linkRoot = p;
								p->subjects->linkRoot->unitsAllowed = p->subjects->linkRoot->unitsAllowed - newClass->unitsOfClass;
								p->subjects->linkRoot->studentsAllowed = p->subjects->linkRoot->studentsAllowed - newClass->studentsInClass;
								while (getchar()!= '\n');
								return newClass;
							} else {

								do {
									if (q->linkForward != NULL) q = q->linkForward;
								} while (q->linkForward != NULL); // ends if the traversing has finished

								q->linkForward = newClass;
								q = q->linkForward;
								q->linkForward = NULL;
								q->linkRoot = p;
								p->unitsAllowed = p->unitsAllowed - q->unitsOfClass;
								p->studentsAllowed = p->studentsAllowed - q->studentsInClass;
									
								while (getchar()!= '\n');
								return newClass;
							}
						}
						p = p->next;	
					} while (p!= headTeacher);

					clear(); newline();
					printf (ANSI_COLOR_RED" EMPLOYEE NUMBER NOT IN THE LIST.\n"ANSI_COLOR_RESET);
					printf (" INPUT FAILED!\n Press <ENTER> to continue...");
					while (getchar()!= '\n');
					return emptyNode;
				}
			}
		} else {
			repeatQuestion:
				clear(); newline();
				printf (" Do you want to continue?\n [1] Yes | [2] No\n Choice: "); scanf ("%d", &choice); getchar();
				if (choice == 2) {
					p = NULL; free (p); q = NULL; free (q);
					clear(); newline(); minilinediv();
					printf (ANSI_COLOR_RED"  INPUT CANCELLED!\n"ANSI_COLOR_RESET);
					minilinediv();
					printf ("  Press <ENTER> to continue...");
					while (getchar()!= '\n');
					return emptyNode;
				} else if (choice == 1) choice = 0;
				else goto repeatQuestion;
		}
	} while (choice != 2);
}