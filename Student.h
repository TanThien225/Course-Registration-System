#pragma once
#ifndef Student_Function
#define  Student_Function

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"GeneralFunc.h"
#include"Course.h"
using namespace std;
#pragma warning(disable: 4996)

struct Student
{
	string StudentID;
	string FirstName;
	string LastName;
	int Gender{};//1: Female  0:male 
	string DateofBirth;
	int SocialID{};
	string email;
	string Class;

	string Username;
	string Password;
	vector<Course> ListStudy;
	int enrollStat = 0;
};

void InputStudent(Student& std);

void OutputStudent(Student &std);

void OutputStdinLine(Student& std);

void ReadFileStudent(Student &std, fstream& File);





#endif

