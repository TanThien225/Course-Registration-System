#pragma once
#ifndef Student_Function
#define  Student_Function

#include<iostream>
#include<string>
#include<fstream>
#include"GeneralFunc.h"
using namespace std;
#pragma warning(disable: 4996)

struct Student
{
	string StudentID;
	string FirstName;
	string LastName;
	int Gender;//1: Female  0:male 
	string DateofBirth;
	int SocialID;
	string email;
	string Class;

	string Username;
	string Password;
};

void OutputStudent(Student std);

void ReadFileStudent(Student &std, fstream& File);

string remove_spaces(const string& s);



#endif

