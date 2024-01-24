/*
.										UNIVERSITY OF THE PHILIPPINES LOS BANOS
.									Computer Science 21 - Fundamentals of Programming
.											First Semester A.Y. 2016-2017
.			Creator:	BATICOS, Andric Quinn Sargento
.					2015-13764 / 09291720966
.					BS Computer Science - College of Arts and Sciences
.			
.			Program Title: SIETE​: Teacher-to-Class Management System (Structures)
.			
.			File Description: 	This file contains all structures used in the program, SIETE.
*/

typedef struct name_tag {		// Structure for Teacher's Name
	char firstName[50];
	char lastName[50];
} NAME;

typedef struct time_tag {		// Structure for Class Time
	char hour[3];
	char minutes[3];
	int daytime;		//--- either [1] AM or [2] PM
	int militaryHour;
} TIME;

typedef struct schedule_tag {	// Structure for Class Schedule
	TIME timeStart;
	TIME timeEnd;
	int numberOfDays;
	char days[8];
} SCHEDULE;

typedef struct classInfo {		// Structure for Class Information
	
	// [REQUIRED MEMBERS]
	char courseCode[10];
	char section[10];
	float unitsOfClass;
	int studentsInClass;
	SCHEDULE schedule;
	
	// [ADDITIONAL MEMBERS]
	struct classInfo *linkForward;
	struct teacherInfo *linkRoot;
	
} CLASS;

typedef struct teacherInfo {	// Structure for Teacher's Information
	
	// [REQUIRED MEMBERS]
	NAME person;
	char EN[10];
	float unitsAllowed;
	int studentsAllowed;
	
	// [ADDITIONAL MEMBERS]
	CLASS *subjects;
	struct teacherInfo *next;
	struct teacherInfo *prev;
	int subjectLimit;
	
} TEACHER;
