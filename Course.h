#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"Student.h"
#include"AcademicStaffMember.h"
#include"GeneralFunc.h"
using namespace std;

//the session that the course will be performed
struct Session
{
	int day; //day of week (MON / TUE / WED / THU / FRI / SAT)
	int shift; // S1 (07:30), S2(09:30), S3(13:30) and S4(15:30)
};


struct Course
{
	string id;
	string name;
	string teacherName;
	int numCredit; // So tin chi
	int maximumStudent; // default: 50 the maximum number of students in the course
	Session Sessions[2];  //  A course will be taught in 2 sessions in a week
	//Student* Mem;
};

void inputSession(Session& S);
void outputSession(Session S);


void inputCourse(Course& course);
void outputCourse(Course& course);

struct NODE_Course
{
	Course data;
	NODE_Course* pNext;
};

struct Semester
{
	int Type;
	int SchoolYear;
	Date start;
	Date end;

	NODE_Course* pHead;
	NODE_Course* pTail;
};

void createSemester(Semester& semester);

void addCourse(Semester& semester, Course course);

void printSemesterCourses(Semester semester);

void MenuSemester(Semester& semester);

bool conflictSession(Session A, Session B);

