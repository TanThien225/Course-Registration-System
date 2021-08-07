#include"GeneralFunc.h"

void SplitName(string ex, string& FirstName, string& LastName)
{
	int n = ex.length();
	for (int i = n - 1; i >= 0; i--)
	{
		if (ex[i] == ' ')
		{
			FirstName = ex.substr(i + 1);
			LastName = ex.substr(0, i);
			break;
		}
	}
}

string remove_spaces(const string& s)
{
	bool check = false;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')
		{
			check = true;
		}
	}
	if (check == true) {
		int last = s.size() - 1;
		while (last >= 0 && s[last] == ' ')
			--last;
		return s.substr(0, last + 1);
	}
	else return s;
}

string SplitPassword(string str)
{
	string Pass;
	int n = str.length();
	for (int i = n - 1; i >= 0; i--)
	{
		if (str[i] == ' ')
		{
			return Pass = str.substr(i + 1);

		}
	}
}

bool in_array(string value, string array[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(value.c_str(), array[i].c_str()) == 0)
		{
			return true;
		}
	}
	return false;
}

bool CheckSpecial(char c)
{
	string Special = "!@#$%^&*()/:_+-=<>?,.";
	for (int i = 0; i <=Special.length(); i++)
	{
		if (c == Special[i])
		{
			return true;
			break;
		}
	}
	return false;
}


void GetDateTime(DateTime& DT)
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

void SettingDateTime(DateTime& DT)
{
	cout << "Please enter Setting Date and Time.\n";
	cout << "Enter Year: "; cin >> DT.Year;
	cout << "Enter Month: "; cin >> DT.Month;
	cout << "Enter Day: "; cin >> DT.Day;
	cout << "Enter Hour Time: "; cin >> DT.T_hour;
	cout << "Enter Minute Time:"; cin >> DT.T_min;
	cout << "Enter second Time:"; cin >> DT.T_sec;
}

void inputDate(Date& D)
{
	cout << "Input Year: ";
	cin >> D.Year;
	cout << "Input Month: ";
	cin >> D.Month;
	cout << "Input Day: ";
	cin >> D.Day;
}

void outputDate(Date D)
{
	cout << D.Day << "/" << D.Month << "/" << D.Year;
}


Date getDate(DateTime DT)
{
	Date d;
	d.Day = DT.Day;
	d.Month = DT.Month;
	d.Year = DT.Year;
	return d;
}

bool afterDate(Date a, Date b)// if Date a after day b return true 
{
	if (a.Year > b.Year)
	{
		return true;
	}
	else if (a.Year == b.Year)
	{
		if (a.Month > b.Month)
		{
			return true;
		}
		else if (a.Month == b.Month)
		{
			if (a.Day > b.Day)
			{
				return true;
			}
		}
	}
	return false;
}