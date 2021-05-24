#include<iostream>
#include<ctime>
#include<conio.h>
#include<string>
#include<Windows.h>
#include<fstream>
#include"Student.h";
#include"AcademicStaffMember.h";
#include"GeneralFunc.h";
using namespace std;
#pragma warning(disable: 4996)

struct ClassUni
{
	string Name;
	Student* Mem;//Array of student
	int n;
};

struct NODE_Class
{
	ClassUni Data;
	NODE_Class* pNext;
};

struct ListClass
{
	NODE_Class* pHead;
	NODE_Class* pTail;
};

void PrintStudentInClass(ClassUni Cl)
{
	cout << "Name of Class: " << Cl.Name;
	for (int i = 0; i < Cl.n; i++)
	{
		cout << "\n+ Student number " << i + 1;
		OutputStudent(Cl.Mem[i]);
		cout << endl;
	}
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
void Read1stYearClass()
{
	ClassUni FirstCls;
	cout << "\n - Input Name of 1st year Class: ";
	getline(cin, FirstCls.Name);

	//FirstCls.Name = remove_spaces(FirstCls.Name);
	string FileClass;
	FileClass = FirstCls.Name + ".txt";
	FileClass = remove_spaces(FileClass);
	FileClass = "Class" + FileClass;//Ex: Class 20CTT1

	string temp;
	fstream Filein;

	Filein.open(FileClass, ios::in | ios::app);
	if (Filein.fail() == true)
	{
		cout << "\nError File !!.";
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
}

void MenuAcademicStaffMember()
{
	system("cls");
	//Clear Console
	int choice = -1;
	//while (choice)
	{
		cout << "\t\t\t------------------Academic Staff Member HCMUS------------------\n";
		cout << "\t\t\t 1. Create School Year. \n";
		cout << "\t\t\t 2. Create Semester. \n";
		cout << "\t\t\t 3. View List. \n";
		cout << "\t\t\t 4. Process the Score. \n";
		cout << "\n\n\t\t\t 0. Close \n";
		cout << "\t\t\t\nEnter choice: ";
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





int Login(string username, string password, AcademicStaff AS[], Student std[])
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
			cout << "\nError : Do not find any match username !";
		}
	} while (in_array(username, DataUsername, 5) == false);


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

void ClearScreen()
{
	cout << string(100, '\n');
}
void MenuSTART()
{
	int choice = -1;
	DateTime DT;
	GetDateTime(DT);
	
	Student STD[3];
	AcademicStaff AS[2];

	while (choice)
	{
		cout << "\t\t\t============================================================";
		DisplayDateTime(DT);
		cout << "\t\t\t------------------PORTAL HCMUS------------------\n";
		cout << "\t\t\t 1. Sign in";
		cout << "\t\t\t 2. Setting Date and Time";
		cout << "\n\n\t\t\t 0. Close ";
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
			int Check = Login(User, Pass, AS, STD);
			if (Check == 1)
			{
				cout << "\n===============MENU ADMIN===============\n";
				MenuAcademicStaffMember();
			}
			else if (Check == 0) {
				cout << "\n===============MENU STUDENT===============\n";
			}
			else {
				cout << "\nIncorrect PIN too many times. To try again, restart your device.\n";
				exit(0);
			}
			ClearScreen();
			break;
		}
		case 2:
		{
			SettingDateTime(DT);
			system("cls");//Clear Console
			//ClearScreen();
			break;
		}
		}
	}
}


int main()
{
	MenuSTART();

	return 0;
}