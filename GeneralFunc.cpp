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