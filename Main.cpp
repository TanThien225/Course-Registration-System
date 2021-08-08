#include<iostream>
#include<ctime>
#include<conio.h>
#include<string>
#include<Windows.h>
#include<vector>
#include<fstream>
#include"Student.h"
#include"AcademicStaffMember.h"
#include"GeneralFunc.h"
#include"Course.h"
#include"Score.h"
using namespace std;
#pragma warning(disable: 4996)

struct ClassUni
{
	string Name;
	Student* Mem{};//Array of student
	int n{};
};

struct NODE_Class
{
	ClassUni Data;
	NODE_Class* pNext{};
};

struct ListClass
{
	NODE_Class* pHead;
	NODE_Class* pTail;
};

struct SchoolYear
{
	string Name;
	bool CreatedStat = false;
	//There are 3 semesters in a school year: Semester 1 (Fall), Semester 2 (Summer), and Semester 3(Autumn).
	Semester sem[3]{};
	int typeSemester;// 0 : not created Semester, 1: Semester 1, 2: Semester 2, 3: Semester 3
};


struct stdRegisCourse
{
	Course course;
	vector<Student> enrollSTD;
};

struct listRegisCourse
{
	stdRegisCourse arr[50];
	int n;
};

void PrintStudentInClass(ClassUni Cl)
{
	cout << "  - Name of Class: " << Cl.Name << endl;
	cout <<"\n"<< setw(3) << left << "No" << "\t" << setw(10) << left << "StudentID" << "\t" << setw(10) << left
		<< "First Name" << "\t" << setw(18) << left << "Last Name" << "\t" << setw(10) << left
		<< "Gender" << "\t" << setw(12) << left << "Date of Birth" << "\t" << setw(10) << left
		<< "Social ID" << endl;
	for (int i = 0; i < 110; i++)
	{
		cout << "=";
	}
	cout << endl;
	for (int i = 0; i < Cl.n; i++)
	{
		cout << left << setw(3) << i + 1 << "\t";
		OutputStdinLine(Cl.Mem[i]);
		cout << endl;
	}
	cout << endl;
	cout << endl;	
}

NODE_Class* initializeNodeClass(ClassUni Cl)
{
	NODE_Class* p = new NODE_Class;
	p->Data = Cl;
	p->pNext = NULL;
	return p;
}

void addTailClass(ListClass& LCl, NODE_Class* p)
{
	if (LCl.pHead == NULL)
	{
		LCl.pHead = LCl.pTail = p;
	}
	else {
		LCl.pTail->pNext = p;
		LCl.pTail = p;
	}
}

void PrintListNameClass(ListClass LCl)
{
	if (LCl.pHead == NULL)
	{
		cout << " is EMPTY\n";
	}
	for (NODE_Class* p = LCl.pHead; p != NULL; p = p->pNext)
	{
		cout << " - Class: " << p->Data.Name << endl;
	}
	cout << "\n------------------\n";
}

//Get data from file input
bool Read1stYearClass(ClassUni &FirstCls)
{
	cout << "\n - Input Name of 1st year Class: ";
	getline(cin, FirstCls.Name);

	//FirstCls.Name = remove_spaces(FirstCls.Name);
	string FileClass;
	FileClass = FirstCls.Name + ".txt";
	FileClass = remove_spaces(FileClass);
	FileClass = "Class" + FileClass;//Ex: Class 20CTT1

	string temp;
	fstream Filein;

	Filein.open(FileClass, ios::in);
	if (Filein.fail() == true)
	{
		cout << "\nError File !!.\n";
		return false;
	}
	Filein >> FirstCls.n;
	getline(Filein, temp);
	getline(Filein, temp);
	FirstCls.Mem = new Student[FirstCls.n];
	for (int i = 0; i < FirstCls.n; i++)
	{
		ReadFileStudent(FirstCls.Mem[i], Filein);
	}
	Filein.close();
	return true;
	
}

//Menu of Academic manager (function of academic staff) 
void MenuASAcademicManager(ListClass& L, Semester& thisSem, listRegisCourse& LRC)
{
	system("cls");
	//Clear Console
	int choice = -1;
	while (choice)
	{
		cout << "\t\t\t------------------Academic Manager------------------\n";
		cout << "\t\t\t 1. View list of classes. \n";
		cout << "\t\t\t 2. View list of students in a class (for example, 20APCS1...) \n";
		cout << "\t\t\t 3. View list of courses. \n";
		cout << "\t\t\t 4. View list of students in a course \n";
		cout << "\n\n\t\t\t 0. Close \n";
		cout << "\t\t\t----------------------------------------------------\n";
		cout << "\t\t\t\nEnter choice: ";
		cin >> choice;
		switch (choice)
		{
		case 0:
		{
			system("cls");
			break;
		}
		case 1:
		{
			system("cls");
			PrintListNameClass(L);
			break;
		}
		case 2:
		{
			system("cls");
			string name;
			while (getchar() != '\n');
			cout << "\t\t\t 2. View list of students in a class (for example, 20APCS1 ...) \n";
			cout << "\nInput Name class: ";
			getline(cin, name);
			if (L.pHead == NULL)
			{
				cout << "\nList of class is Empty !\n";
			} 
			else{
				for (NODE_Class* p = L.pHead; p != NULL; p = p->pNext)
				{
					if (strcmp(p->Data.Name.c_str(), name.c_str()) == 0)
					{
						PrintStudentInClass(p->Data);
					}
				}
			}
			break;
		}
		case 3:
		{
			system("cls");
			printSemesterCourses(thisSem);
			break;
		}
		case 4:
		{
			system("cls");
			while (getchar() != '\n');
			string keyword;
			cout << " Input Course ID to view: ";
			getline(cin, keyword);
			if (thisSem.pHead == NULL)
			{
				cout << "There aren't any Courses\n";
				return;
			}
			else {
				for (int i = 0; i < LRC.n; i++)
				{
					if (LRC.arr[i].course.id == keyword) {
						cout << "  - Course: " << LRC.arr[i].course.name << endl;
						cout << "\n" << setw(3) << left << "No" << "\t" << setw(10) << left << "StudentID" << "\t" << setw(10) << left
							<< "First Name" << "\t" << setw(18) << left << "Last Name" << "\t" << setw(10) << left
							<< "Gender" << "\t" << setw(12) << left << "Date of Birth" << "\t" << setw(10) << left
							<< "Social ID" << endl;
						for (int i = 0; i < 110; i++)
						{
							cout << "=";
						}
						cout << endl;
						for (int j = 0; j < LRC.arr[i].enrollSTD.size(); j++)
						{
							cout << left << setw(3) << i + 1 << "\t";
							OutputStdinLine(LRC.arr[i].enrollSTD[j]);
							cout << endl;
						}
						cout << endl;
						cout << endl;
					}
				}
			}
			break;
		}
		default:
			break;
		}
	}
}

//function to create 1st classes in beginning of a school year
void MenuCreate1stClassAS(ListClass& L)
{
	system("cls");
	int choice = -1;
	while (choice)
	{
		cout << "\t\t\t------------------Create School Year------------------\n";
		cout << "\t\t\t 1. Create 1st classes and Add new 1st year students. \n";
		cout << "\t\t\t 2. For quick input, Import file containing all students in a specific class \n";
		cout << "\n\t\t\t 0. Return \n";
		cout << "\t\t\t------------------------------------------------------\n";
		cout << "\t\t\t\nEnter choice: ";
		cin >> choice;
		switch (choice)
		{
		case 0:
		{
			system("cls");
			break;
		}
		case 1:
		{
			system("cls");
			cout << "\t\t\t------------------Create 1st classes and Add new 1st year students------------------\n";
			ClassUni first;
			vector<Student> list;
			while (getchar() != '\n');
			cout << "\n - Input Name of 1st year Class: ";
			getline(cin, first.Name);
			cout << "\n - Add new 1st year students to 1st-year classes. \n";
			char ch;
			while (true)
			{
				Student std;
				InputStudent(std);
				//Add student to 1st class
				list.push_back(std);
				while (getchar() != '\n');
				cout << "\nType 'Y' to keep adding or 'N' to confirm to end adding: ";
				cin >> ch;
				//The class is enough to add and Stop adding student
				if ((ch == 'N') || (ch == 'n'))
				{
					first.Mem = &list[0];
					first.n = list.size();
					break;
				}
			}
			cout << "\nSuccessfully created 1st Class\n";
			//PrintStudentInClass(first);
			//add to list of classes
			NODE_Class* p = initializeNodeClass(first);
			addTailClass(L, p);
			break;
		}
		case 2:
		{
			system("cls");
			ClassUni a;
			while (getchar() != '\n');
			bool check = Read1stYearClass(a);
			if (check == true)
			{
				NODE_Class* p = initializeNodeClass(a);
				addTailClass(L, p);
			}
			else cout << "\nError : Do not find any match class name !";
			break;
		}
		default: {
			   cout << "\nError! Please check again.\n";
			   break;
		}
		}
	}
}

void exportCourse(listRegisCourse& LRC)
{
	ofstream file;
	while (getchar() != '\n');
	string keyword;
	cout << " Input Course ID to view: ";
	getline(cin, keyword);
	if (LRC.n == 0)
	{
		cout << "There aren't any Courses\n";
		return;
	}
	else {
		for (int i = 0; i < LRC.n; i++)
		{
			if (LRC.arr[i].course.id == keyword) {
				
				string filename = remove_spaces(LRC.arr[i].course.id) +".txt";
				file.open(filename);
				if (file.fail())
				{
					cout << "\nFile error !\n";
				}
				else {
					file << LRC.arr[i].course.name << endl;
					for (int j = 0; j < LRC.arr[i].enrollSTD.size(); j++)
					{
						file << ++j << "," << LRC.arr[i].enrollSTD[j].StudentID << "," << LRC.arr[i].enrollSTD[j].LastName << " " << LRC.arr[i].enrollSTD[j].FirstName << ","
							<< LRC.arr[i].enrollSTD[j].Gender << "," << LRC.arr[i].enrollSTD[j].DateofBirth << "," << LRC.arr[i].enrollSTD[j].SocialID << endl;

					}
				}
				file.close();
			}
		}
	}
}

void MenuASProcessScore(AcademicStaff main, ListClass& L, DateTime& datePresent, SchoolYear& Schoolyr, Semester& thisSem, RegisSession& regis, listRegisCourse& LRC, vector<CourseScore>& scoreList)
{
	system("cls");
	int choice = -1;
	while (choice)
	{
		cout << "\t\t\t------------------Process Score------------------\n";
		cout << "\t\t\t 1. Export list of students in a course to a CSV file. \n";
		cout << "\t\t\t 2. Import the scoreboard of a course. \n";
		cout << "\t\t\t 3. View the scoreboard of a course. \n";
		cout << "\t\t\t 4. Update a student result.\n";
		cout << "\n\t\t\t 0. Return \n";
		cout << "\t\t\t------------------------------------------------------\n";
		cout << "\t\t\t\nEnter choice: ";
		cin >> choice;
		switch (choice)
		{
		case 0:
		{
			system("cls");
			break;
		}
		case 1:
		{
			system("cls");
			exportCourse(LRC);
			break;
		}
		case 2:
		{
			system("cls");
			CourseScore CS;
			while (getchar() != '\n');
			bool check = importScoreboard(CS);
			if (check)
			{
				scoreList.push_back(CS);
				cout << "\nSuccessfully Imported\n";
			}
			else cout << "\nError! Please check again\n";
			
			break;
		}
		case 3:
		{
			system("cls");
			while (getchar() != '\n');
			string keyword;
			cout << " Input Course ID to view: ";
			getline(cin, keyword);
			for (int i = 0; i < scoreList.size(); i++)
			{
				if (scoreList[i].id == keyword)
				{
					viewScoreboard(scoreList[i]);
				}
			}
			
			break;
		}
		default: {
			cout << "\nError! Please check again.\n";
			break;
		}
		}
	}

}

void MenuAcademicStaffMember(AcademicStaff main, ListClass& L, DateTime& datePresent, SchoolYear& Schoolyr, Semester& thisSem, RegisSession& regis, listRegisCourse& LRC, vector<CourseScore>& scoreList)
{
	system("cls");
	int choice = -1;
	while (choice)
	{
		if (Schoolyr.CreatedStat == true)
		{
			cout << "\t\t\tSchool Year: " << Schoolyr.Name << " / ";
		}
		else cout << "\t\t\tSchool Year :None" << " / ";
		if (Schoolyr.typeSemester == 0)
		{
			cout << "Semester :None" << endl;
		}
		else {
			cout << "Semester " << Schoolyr.typeSemester << " : ";
			//Print start date and end date of the Semester
			outputDate(Schoolyr.sem[Schoolyr.typeSemester - 1].start);
			cout << " - ";
			outputDate(Schoolyr.sem[Schoolyr.typeSemester - 1].end);
			cout << endl;
		}
		cout << "\t\t\tCourse registration session: ";
		if (regis.createdStat == true)
		{

			outputDate(regis.startD);
			cout << " - ";
			outputDate(regis.endD);
			cout << endl;
		}
		else {
			cout << " None.\n";
		}
		cout << "\t\t\t------------------Academic Staff Member HCMUS------------------\n";
		if (Schoolyr.CreatedStat == false)
		{
			cout << "\t\t\t 1. Create School Year. \n";
		}
		else cout << "\t\t\t 1. School Year: "<<Schoolyr.Name <<endl;
		cout << "\t\t\t 2. Create 1st Classes. \n";
		cout << "\t\t\t 3. Create The Semester and The Course Registration"<<Schoolyr.typeSemester<<" \n";
		cout << "\t\t\t 4. Academic Manager. \n";
		cout << "\t\t\t 5. Process the Score. \n";
		cout << "\t\t\t 6. View Profile. \n";
		cout << "\n\t\t\t 0. Log out \n";
		cout << "\t\t\t---------------------------------------------------------------\n";
		cout << "\t\t\t\nEnter choice: ";
		cin >> choice;
		switch (choice)
		{
		case 0:
		{
			system("cls");
			break;
		}
		case 1:
		{
			system("cls");
			if (datePresent.Month == 9)
			{
				//Check school yead has been created ?
				if (Schoolyr.CreatedStat == false)
				{
					cout << "\t\t\t------------------Create School Year------------------\n";
					while (getchar() != '\n');
					cout << "\nEnter School year Name: ";
					getline(cin, Schoolyr.Name);
					Sleep(1500);
					cout << "\nCreate school year sucessfully !!\n";
					Schoolyr.CreatedStat = true;
				}
				else cout << "\nSchool Year has been created. Please check again.\n";
			}
			else
			{
				cout << "\nThis month is not September to create school year. \n";
			}
			break;
		}
		case 2:
		{
			system("cls");
			if (datePresent.Month == 9)
			{
				if (Schoolyr.CreatedStat == true)
				{
					MenuCreate1stClassAS(L);
				}
				else cout << "\nNot yet created School Year. Please check again.\n";
			}
			else cout << "\nThis Function is only work in the beginning of School Year(in September)\n";
			break;
		}
		case 3:
		{
			system("cls");
			
			if (Schoolyr.CreatedStat == true)
			{
				//if this is the first semester, no Need to check the start day and end date
				if (Schoolyr.typeSemester == 0) {
					int i = Schoolyr.typeSemester;
					cout << "\t\t\t----- CREATE SEMESTER " << Schoolyr.typeSemester + 1 << " ----- \n";
					createSemester(Schoolyr.sem[i]);
					MenuSemester(Schoolyr.sem[i], regis);
					thisSem = Schoolyr.sem[i];
					int n = 0;
					
					for (NODE_Course* p = Schoolyr.sem[n].pHead; p != NULL; p = p->pNext)
					{
						LRC.arr[n++].course = p->data;
						if (p == thisSem.pTail)
						{
							LRC.n = n + 1;
						}
					}
					Schoolyr.typeSemester++;// Notice that this Semester has been created
				}
				else if ((Schoolyr.typeSemester == 1) || (Schoolyr.typeSemester == 2))//if this is the 2 or 3 Semeter, evaluate the end date of Before Semester
				{
					Date Present = getDate(datePresent);
					//outputDate(Present); cout << "\t";
					//outputDate(Schoolyr.sem[Schoolyr.typeSemester - 1].end);
					if (afterDate(Present, Schoolyr.sem[Schoolyr.typeSemester - 1].end))
					{
						cout << "\t\t\t----- CREATE SEMESTER " << Schoolyr.typeSemester + 1 << " ----- \n";
						createSemester(Schoolyr.sem[Schoolyr.typeSemester]);
						MenuSemester(Schoolyr.sem[Schoolyr.typeSemester], regis);
						thisSem = Schoolyr.sem[Schoolyr.typeSemester];
						int n = 0;
						for (NODE_Course* p = Schoolyr.sem[n].pHead; p != NULL; p = p->pNext)
						{
							LRC.arr[n++].course = p->data;
							if (p == thisSem.pTail)
							{
								LRC.n = n + 1;
							}
						}
						Schoolyr.typeSemester++;// increase the type semester 
					}
					else cout << "\nThis Semester is not End,so Can not created new Semester !\n ";
				}
				else if (Schoolyr.typeSemester > 2)// this school year is overe
				{
					Date Present = getDate(datePresent);
					outputDate(Present);
					if (afterDate(Present, Schoolyr.sem[Schoolyr.typeSemester - 1].end))
					{
						cout << "\nThis School Year is Over. Please Start new School Year !\n ";
						//Restart new school year
						//Schoolyr.typeSemester = 0;
					}
					else cout << "\nThis Semester is not End,so Can not created new Semester !\n ";
				}
			}
			else cout << "\nNot yet created School Year. Please check again.\n";
			
			break;
		}
		case 4:
		{
			system("cls");
			MenuASAcademicManager(L, thisSem, LRC);
			break;
		}
		case 5:
		{
			system("cls");
			cout << "\n-----Process Score-----\n";
			MenuASProcessScore(main, L, datePresent, Schoolyr, thisSem, regis, LRC, scoreList);
			break;
		}
		case 6:
		{
			system("cls");
			OutputAStaff(main);
			cout << endl;
			break;
		}
		default:
			break;
		}
	}
}

void enrollInCourse(Student& std, Course enrollCourse, listRegisCourse& LRC)
{
	if (std.ListStudy.empty())
	{
		std.ListStudy.push_back(enrollCourse);
		for (int i = 0; i < LRC.n; i++)
		{
			if (LRC.arr[i].course.id == enrollCourse.id) {
				LRC.arr[i].enrollSTD.push_back(std);
			}
		}
		std.enrollStat++;
		return ;
	}
	else {
		for (int i = 0; i < std.ListStudy.size(); i++)
		{
			
			if (!conflictCourse(std.ListStudy[i], enrollCourse))
			{
				std.ListStudy.push_back(enrollCourse);
				for (int k = 0; k < LRC.n; k++)
				{
					if (LRC.arr[k].course.id == enrollCourse.id) {
						LRC.arr[k].enrollSTD.push_back(std);
					}
				}
				std.enrollStat++;
				return;
			}
			else {
				cout << "\nCan not Enroll in the Course as the new course are conflicted with existing enrolled course sessions!\n";
				return;
			}
		}
	}
}

void viewEnrollCourse(Student& std)
{
	if (std.ListStudy.empty())
	{
		cout << "\nList of enrolled Course is Empty.\n";
		return;
	}
	else {
		cout << "\n" << setw(3) << left << "No" << "\t" << setw(10) << left << "Course ID " << "\t" << setw(20) << left
			<< "Course Name" << "\t" << setw(30) << left << "Teacher Name" << "\t" << setw(6) << left
			<< "Credits" << "\t" << setw(6) << left << "Max" << "\t" << setw(10) << left
			<< "Dayofweek" << endl;
		for (int i = 0; i < 140; i++)
		{
			cout << "=";
		}
		cout << endl;
		int no = 0;
		for (vector<Course>::iterator i = std.ListStudy.begin(); i != std.ListStudy.end(); ++i)
		{
			cout << left << setw(3) << ++no << "\t";
			outputCourse(*i);
			cout << endl;
		}
		cout << endl;
		cout << endl;
	}
}

void removeCourse(Student& std, listRegisCourse& LRC)
{
	while (getchar() != '\n');
	string keyword;
	cout << " Input Course ID to delete: ";
	getline(cin, keyword);
	int pos;
	bool check = false;
	for (int i = 0; i < std.ListStudy.size(); i++)
	{
		if (std.ListStudy[i].id == keyword)
		{
			pos = i;
			check = true;
		}
	}
	if (check)
	{
		std.ListStudy.erase(std.ListStudy.begin() + pos);
		for (int i = 0; i < LRC.n; i++)
		{
			if (LRC.arr[i].course.id == keyword) {
				LRC.arr[i].enrollSTD.erase(LRC.arr[i].enrollSTD.begin() + i);
			}
		}
		std.enrollStat--;
	}
	else {
		cout << "Can not find any Course related to this ID!\n";
	}
}

void MenuStudentRegister(Student& main, ListClass& L, DateTime& datePresent, SchoolYear& Schoolyr, Semester& thisSem, RegisSession& regis, listRegisCourse& LRC)
{
	system("cls");
	int choice = -1;
	while (choice)
	{
		cout << "\t\t\t------------------REGISTER FOR THE COURSE------------------\n";
		cout << "\t\t\t 1. Enroll in Courses. \n";
		cout << "\t\t\t 2. View list of enrolled courses. \n";
		cout << "\t\t\t 3. Remove a course from the enrolled list. \n";

		cout << "\n\t\t\t 0. Return \n";
		cout << "\t\t\t------------------------------------------------------------\n";
		cout << "\t\t\t\nEnter choice: ";
		cin >> choice;
		switch (choice)
		{
		case 0:
		{
			system("cls");
			break;
		}
		case 1:
		{
			system("cls");
			printSemesterCourses(thisSem);
			Course enroll;
			if (main.enrollStat < 5) {
				if (findCourseEnrollment(thisSem, enroll))
				{
					enrollInCourse(main, enroll, LRC);
				}
				else cout << "Can not find any Course related to the ID or Name!\n";
			}
			else cout << "You can only enroll in at most 5 courses in a semester.";
			break;
		}
		case 2:
		{
			system("cls");
			viewEnrollCourse(main);
			break;
		}
		case 3:
		{
			system("cls");
			removeCourse(main, LRC);
			break;
		}
		default:
			system("cls");
			break;
		}
	}
}

void MenuStudentAcademicManager(Student& main, ListClass& L, Semester& thisSem, listRegisCourse& LRC)
{
	system("cls");
	//Clear Console
	int choice = -1;
	while (choice)
	{
		cout << "\t\t\t------------------ACADEMIC MANAGER------------------\n";
		cout << "\t\t\t 1. View list of my courses in this semester. \n";
		cout << "\t\t\t 2. View list of classes \n";
		cout << "\t\t\t 3. View list of students in a class (for example, 20APCS1…). \n";
		cout << "\t\t\t 4. View list of courses. \n";
		cout << "\t\t\t 5. View list of students in a course. \n";

		cout << "\n\t\t\t 0. Return \n";
		cout << "\t\t\t----------------------------------------------------\n";
		cout << "\t\t\t\nEnter choice: ";
		cin >> choice;
		switch (choice)
		{
		case 0:
		{
			system("cls");
			break;
		}
		case 1:
		{
			system("cls");
			viewEnrollCourse(main);
			break;
		}
		case 2:
		{
			system("cls");
			PrintListNameClass(L);
			break;
		}
		case 3:
		{
			system("cls");
			string name;
			while (getchar() != '\n');
			cout << "\t\t\t 2. View list of students in a class (for example, 20APCS1 ...) \n";
			cout << "\nInput Name class: ";
			getline(cin, name);
			if (L.pHead == NULL)
			{
				cout << "\nList of class is Empty !\n";
			}
			else {
				for (NODE_Class* p = L.pHead; p != NULL; p = p->pNext)
				{
					if (strcmp(p->Data.Name.c_str(), name.c_str()) == 0)
					{
						PrintStudentInClass(p->Data);
					}
				}
			}
			break;
		}
		case 4:
		{
			system("cls");
			printSemesterCourses(thisSem);
			/*
			cout << "\n-------\n";
			for (int i = 0; i < LRC.n; i++)
			{
				outputCourse(LRC.arr[i].course);
				cout << endl;
			}
			cout << endl;
			cout << endl;
			*/
			break;
		}
		case 5:
		{
			system("cls");
			while (getchar() != '\n');
			string keyword;
			cout << " Input Course ID to view: ";
			getline(cin, keyword);
			if (thisSem.pHead == NULL)
			{
				cout << "There aren't any Courses\n";
				return;
			}
			else {
				for (int i = 0; i < LRC.n; i++)
				{
					if (LRC.arr[i].course.id == keyword) {
						cout << "  - Course: " << LRC.arr[i].course.name << endl;
						cout << "\n" << setw(3) << left << "No" << "\t" << setw(10) << left << "StudentID" << "\t" << setw(10) << left
							<< "First Name" << "\t" << setw(18) << left << "Last Name" << "\t" << setw(10) << left
							<< "Gender" << "\t" << setw(12) << left << "Date of Birth" << "\t" << setw(10) << left
							<< "Social ID" << endl;
						for (int i = 0; i < 110; i++)
						{
							cout << "=";
						}
						cout << endl;
						for (int j = 0; j < LRC.arr[i].enrollSTD.size(); j++)
						{
							cout << left << setw(3) << i + 1 << "\t";
							OutputStdinLine(LRC.arr[i].enrollSTD[j]);
							cout << endl;
						}
						cout << endl;
						cout << endl;
					}
				}
			}
			break;
		}
		default:
			system("cls");
			break;
		}
	}
}




void MenuStudent(Student main, ListClass& L, DateTime& datePresent, SchoolYear& Schoolyr, Semester& thisSem, RegisSession& regis, listRegisCourse& LRC, vector<CourseScore> &scoreList)
{
	system("cls");
	//Clear Console
	int choice = -1;
	while (choice)
	{
		if (Schoolyr.CreatedStat == true)
		{
			cout << "\t\t\tSchool Year: " << Schoolyr.Name << " / ";
		}
		else cout << "\t\t\tSchool Year :None" << " / ";
		if (Schoolyr.typeSemester == 0)
		{
			cout << "Semester :None" << endl;
		}
		else {
			cout << "Semester " << Schoolyr.typeSemester << " : ";
			//Print start date and end date of the Semester
			outputDate(Schoolyr.sem[Schoolyr.typeSemester - 1].start);
			cout << " - ";
			outputDate(Schoolyr.sem[Schoolyr.typeSemester - 1].end);
			cout << endl;
		}
		cout << "\t\t\tCourse registration session :";
		if (regis.createdStat == true)
		{
			
			outputDate(regis.startD);
			cout << " - ";
			outputDate(regis.endD);
			cout << endl;
		}
		else {
			cout << "None\n";
		}
		cout << "\t\t\t------------------STUDENT HCMUS------------------\n";
		cout << "\t\t\t 1. Register for the course. \n";
		cout << "\t\t\t 2. Academic Manager. \n";
		cout << "\t\t\t 3. View Score. \n";
		cout << "\t\t\t 4. View Profile. \n";

		cout << "\n\t\t\t 0. Log out \n";
		cout << "\t\t\t-------------------------------------------------\n";
		cout << "\t\t\t\nEnter choice: ";
		cin >> choice;
		switch (choice)
		{
		case 0:
		{
			system("cls");
			break;
		}
		case 1:
		{
			system("cls");
			Date Present = getDate(datePresent);
			if (regis.createdStat == true)
			{
				//if today in period registration session after start date and before end date, you will able to enroll in the course
				if ((afterDate(Present, regis.startD)) && (afterDate(regis.endD, Present)))
				{
					MenuStudentRegister(main, L, datePresent, Schoolyr, thisSem, regis, LRC);
				}
			}
			else cout << "\n The course registration session is not created\n";
			break;
		}
		case 2:
		{
			system("cls");
			MenuStudentAcademicManager(main, L, thisSem,LRC);
			break;
		}
		case 3:
		{
			system("cls");
			system("cls");
			while (getchar() != '\n');
			string keyword;
			cout << " Input Course ID to view: ";
			getline(cin, keyword);
			for (int i = 0; i < scoreList.size(); i++)
			{
				if (scoreList[i].id == keyword)
				{
					viewScoreboard(scoreList[i]);
				}
			}

			break;
			break;
		}
		case 4:
		{
			system("cls");
			OutputStudent(main);
			cout << endl;
			break;
		}
		default:
			break;
		}
	}
}



string EnterPassword()
{

	string Pass;
	char x;	
	cout << "Password : ";
	while (true)
	{
		x = getch();
		if (x == 13)
		{
				break;
		}
		else if (x == 8) // backspace thi xoa di 1 ki tu ở cuoi tren console va xoa ki tu cuoi pass
		{
			Pass.pop_back();
			cout << "\b \b";
		}
		else if ((x >= '0' && x <= '9') || (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || CheckSpecial(x))
		{
			if (Pass.length() < 16)
			{
				cout << x;
				Sleep(150);
				cout << "\b \b";
				cout << "*";
				Pass.push_back(x);//them cuoi
		     }
		}
		
	}
	
	return Pass;
}


int Login(string& username, string& password, AcademicStaff AS[], Student std[])
{
	int check = 0;
	int COUNT = 0;
	
	fstream Filein;
	Filein.open("AcademicStaffAccount.txt", ios::in | ios::out | ios::app);
	int n_AS;
	Filein >> n_AS;
	string temp;
	getline(Filein, temp); getline(Filein, temp);
	for (int i = 0; i < n_AS; i++)
	{
		ReadFileAStaff(AS[i], Filein);
	}
	Filein.close();

	fstream Filein1;
	Filein1.open("AccountStudent.txt", ios::in | ios::out | ios::app);
	int n_std;
	Filein1 >> n_std;
	getline(Filein1, temp);
	getline(Filein1, temp);
	for (int i = 0; i < n_std; i++)
	{
		ReadFileStudent(std[i], Filein1);
	}
	Filein1.close();

	string DataUsername[5] = { AS[0].Username, AS[1].Username, std[0].Username, std[1].Username, std[2].Username };
	
	while (getchar() != '\n');
	do {
		cout << "\nEnter username: ";
		getline(cin, username);
		if (in_array(username, DataUsername, 5) == false)
		{
			cout << "\nError : Do not find any match username !\n";
		}
	} while (in_array(username, DataUsername, 5) == false);

	//if the password is third wrong. Quit the program
	do{
		password = EnterPassword();
		for (int i = 0; i < n_AS; i++)
		{
			if ((strcmp(password.c_str(), AS[i].Password.c_str()) == 0) && (strcmp(username.c_str(), AS[i].Username.c_str()) == 0))
			{
				check = 1;
				cout << "\nLogin successfully\n";
				return check;
			}
		}
		for (int i = 0; i < n_std; i++)
		{
			if ((strcmp(password.c_str(), std[i].Password.c_str()) == 0) && (strcmp(username.c_str(), std[i].Username.c_str()) == 0))
			{
				check = 0;
				cout << "\nLogin successfully\n";
				return check;
			}
		}
		
		COUNT++;
		cout << "\nPassword was wrong. Please check again!\n";
		//password = "";

	}while (COUNT < 3);

	check = -1;
	if (COUNT == 3)
		cout << "\n";
	return check;
}


void MenuSTART()
{
	ListClass L;
	L.pHead = L.pTail = NULL;
	int choice = -1;
	DateTime DT;
	GetDateTime(DT);
	SchoolYear Schoolyr;
	Semester thisSem;
	Schoolyr.typeSemester = 0;
	Student accountSTD[3];
	AcademicStaff accountAS[2];

	RegisSession regis;
	regis.createdStat = false;

	listRegisCourse LRC;

	vector<CourseScore> scoreList;

	while (choice)
	{
		DisplayDateTime(DT);
		cout << "\t\t\t------------------PORTAL HCMUS------------------\n";
		cout << "\t\t\t 1. Sign in";
		cout << "\t\t\t 2. Setting Date and Time";
		cout << "\n\n\t\t\t 0. Close ";
		cout << "\n\t\t\t------------------------------------------------\n";
		cout << "\t\t\t\nEnter choice: ";
		cin >> choice;
		switch (choice)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			string User;
			string Pass;
			int Check = Login(User, Pass, accountAS, accountSTD);
			if (Check == 1)
			{
				AcademicStaff MAIN;
				cout << "\n===============MENU ADMIN===============\n";
				for (int i = 0; i < 2; i++)
				{
					if (accountAS[i].Username == User)
					{
						MAIN = accountAS[i];
					}
				}
				MenuAcademicStaffMember(MAIN, L, DT, Schoolyr, thisSem, regis, LRC, scoreList);
			}
			else if (Check == 0)
			{
				Student MAIN;
				cout << "\n===============MENU STUDENT===============\n";
				for (int i = 0; i < 3; i++)
				{
					if (accountSTD[i].Username == User)
					{
						MAIN = accountSTD[i];
					}
				}
				MenuStudent(MAIN, L, DT, Schoolyr, thisSem, regis, LRC, scoreList);
			}
			else {
				cout << "\nIncorrect PIN too many times. To try again, restart your device.\n";
				exit(0);
			}
			system("cls");
			break;
		}
		case 2:
		{
			SettingDateTime(DT);
			system("cls");
			break;
		}
		}
	}
}


int main()
{
	system("mode 150");//Set console size
	SetConsoleTitle(TEXT("University Student Management System"));// Set console window's title
	//system("COLOR F0");//Sets the background & text color

	
	MenuSTART();

 
	return 0;
}