#pragma once

#ifndef SCORE 
#define SCORE

#include<iostream>
#include<string>
#include<fstream>
#include"Student.h"
#include"AcademicStaffMember.h"
#include"GeneralFunc.h"
#include"Course.h"
using namespace std;

struct stdScore
{
	Student std;
	float totalMark;
	float finalMark;
	float midtermMark;
	float otherMark;
};

struct CourseScore
{
	string id;
	stdScore* scr;
	int n;
};

void readScore(stdScore& S, fstream& file);

void outputScore(stdScore S);

bool importScoreboard(CourseScore& CS);
void viewScoreboard(CourseScore CS);


#endif