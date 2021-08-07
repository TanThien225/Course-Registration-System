#pragma once

#ifndef General_Function
#define  General_Function

#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;
#pragma warning(disable: 4996)


void SplitName(string ex, string& FirstName, string& LastName);

string SplitPassword(string str);

bool in_array(string value, string array[], int n);

bool CheckSpecial(char c);

struct DateTime
{
	int Year, Month, Day, T_hour, T_min, T_sec;
};

struct Date
{
	int Year, Month, Day;
};

void GetDateTime(DateTime& DT);

void DisplayDateTime(DateTime DT);

void SettingDateTime(DateTime& DT);

string remove_spaces(const string& s);

void inputDate(Date& D);
void outputDate(Date D);

//Get date from date and time
Date getDate(DateTime DT);

// if Date a after day b return true 
bool afterDate(Date a, Date b);

#endif

