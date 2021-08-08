#include "Score.h"

void readScore(stdScore& S, fstream& file)
{
	string temp;
	getline(file, temp, ',');
	getline(file, S.std.StudentID, ',');
	getline(file, temp, ',');
	SplitName(temp, S.std.FirstName, S.std.LastName);
	getline(file, temp, ',');
	S.totalMark = atof(temp.c_str());
	getline(file, temp, ',');
	S.finalMark = atof(temp.c_str());
	getline(file, temp, ',');
	S.midtermMark = atof(temp.c_str());
	getline(file, temp);
	S.otherMark = atof(temp.c_str());
}

void outputScore(stdScore S)
{
	cout << setw(10) << left << S.std.StudentID << "\t";
	cout << setw(10) << left << S.std.FirstName << "\t";
	cout << setw(15) << left << S.std.LastName << "\t";
	cout << setw(5) << left << S.midtermMark << "\t";
	cout << setw(5) << left << S.finalMark << "\t";
	cout << setw(5) << left << S.otherMark << "\t";
	cout << setw(5) << left << S.totalMark << "\t";
}

bool importScoreboard(CourseScore& CS)
{
	string idCourse;
	cout << "\n - Input ID Course : ";
	getline(cin, idCourse);

	//FirstCls.Name = remove_spaces(FirstCls.Name);
	string FileCourse;
	CS.id = idCourse;
	FileCourse = idCourse + "_Score.txt";
	FileCourse = remove_spaces(FileCourse);

	string temp;
	fstream Filein;

	Filein.open(FileCourse, ios::in);
	if (Filein.fail() == true)
	{
		cout << "\nError File !!.\n";
		return false;
	}
	int n;
	Filein >> CS.n;
	CS.scr = new stdScore[CS.n];
	for (int i = 0; i < CS.n; i++)
	{
		readScore(CS.scr[i], Filein);
	}


	Filein.close();
}
void viewScoreboard(CourseScore CS)
{
	cout << "\n" << setw(3) << left << "No" << "\t" << setw(10) << left << "StudentID" << "\t" << setw(10) << left
		<< "First Name" << "\t" << setw(15) << left << "Last Name" << "\t" << setw(5) << left
		<< "Mid" << "\t" << setw(5) << left << "Final" << "\t" << setw(5) << left
		<< "Other" << "\t" << setw(5) << left << "Total" << endl;
	for (int i = 0; i < 110; i++)
	{
		cout << "=";
	}
	cout << endl;
	for (int i = 0; i < CS.n; i++)
	{
		cout << left << setw(3) << i + 1 << "\t";
		outputScore(CS.scr[i]);
		cout << endl;
	}
	cout << endl;
	cout << endl;
}