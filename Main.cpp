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

bool CheckSpecial(char c)
{
	string Special = "!@#$%^&*()/:_+-=<>?,.";
	for (int i = 0; i <=
		Special.length(); i++)
	{
		if (c == Special[i])
		{
			return true;
			break;
		}
	}
	return false;
}

struct DateTime
{
	int Year, Month, Day, T_hour, T_min, T_sec;
};

void GetDateTime(DateTime &DT)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	DT.Year = 1900 + ltm->tm_year;//tm_year year since 1900
	DT.Month = 1 + ltm->tm_mon;
	DT.Day = ltm->tm_mday;
	DT.T_hour = 1 + ltm->tm_hour;
	DT.T_min = 1 + ltm->tm_hour;
	DT.T_sec = 1 + ltm->tm_sec;
}

void DisplayDateTime(DateTime DT)
{
	cout << "\nYear: " << DT.Year << endl;
	cout << "Month: " << DT.Month << endl;
	cout << "Day: " << DT.Day << endl;
	cout << "Time: " << DT.T_hour << ":";
	cout << DT.T_min << ":";
	cout << DT.T_sec << endl;
}

void SettingDateTime(DateTime &DT)
{
	cout << "Please enter Setting Date and Time.\n";
	cout << "Enter Year: "; cin >> DT.Year;
	cout << "Enter Month: "; cin >> DT.Month;
	cout << "Enter Day: "; cin >> DT.Day;
	cout << "Enter Hour Time: "; cin >> DT.T_hour;
	cout << "Enter Minute Time:"; cin >> DT.T_min;
	cout << "Enter second Time:"; cin >> DT.T_sec;
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
			ClearScreen();
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