#pragma once
#ifndef Academic_Staff_Member
#define Academic_Staff_Member

#include<iostream>
#include<string>
#include<fstream>
#include"GeneralFunc.h"
using namespace std;
#pragma warning(disable: 4996)

struct AcademicStaff
{
	string IDStaff;
	string FirstName;
	string LastName;
	int Gender;
	string DateofBirth;
	int SocialID;
	string email;

	string Username;
	string Password;
};

void OutputAStaff(AcademicStaff st);

void ReadFileAStaff(AcademicStaff& st, fstream& File);





#endif 
