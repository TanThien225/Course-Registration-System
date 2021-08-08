#pragma once
#ifndef COURSE
#define COURSE

#include<iostream>
#include<string>
#include<fstream>
//#include"Student.h"
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
	Date start;
	Date end;

	NODE_Course* pHead;
	NODE_Course* pTail;
};

struct RegisSession
{
	//Check whether the course Registration Session is created
	bool createdStat;
	Date startD;
	Date endD;
};

void createSemester(Semester& semester);

void addCourse(Semester& semester, Course course);

void printSemesterCourses(Semester semester);

void MenuSemester(Semester& semester, RegisSession& regis);

bool conflictSession(Session A, Session B);

//return true if  If 2 sessions of the A course are conflicted with existing B sessions
bool conflictCourse(Course A, Course B);

void deleteHeadCourse(Semester& semester);

void deleteTailCourse(Semester& semester);

//delete course by id
void deleteCoursebyID(Semester& semester, string idCourseDEL);

//delete course by name
void deleteCoursebyName(Semester& semester, string NameCourseDEL);

//delete course by id or name (optional)
void deleteCourse(Semester& semester);

//Check if the course is in this semeter by ID
bool checkCoursebyID(Semester semester, string idCourse);

//Check if the course is in this semeter by name
bool checkCoursebyName(Semester semester, string NameCourse);

//return course find by id or name
NODE_Course* findCourse(Semester& semester);

//update course
void updateCourse(Semester& semester, NODE_Course* update);

//find the course that student want to enroll 
bool findCourseEnrollment(Semester& semester, Course& enrollCourse);



#endif