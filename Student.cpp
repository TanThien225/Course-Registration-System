#include"Student.h"


void ChangePassword(Student std)
{
	string buffer, newPass, check;
	do {
		cout << "\nEnter Current Password : ";
		getline(cin, buffer);
		if (strcmp(buffer.c_str(), std.Password.c_str()) != 0)
		{
			cout << "\n   Incorrect Password. Please enter again !";
		}
	} while (strcmp(buffer.c_str(), std.Password.c_str()) != 0);
	cout << "\nEnter New Password : ";
	getline(cin, newPass);
	do {
		cout << "\nComfirm New Password : ";
		getline(cin, check);
		if (strcmp(newPass.c_str(), check.c_str()) != 0)
		{
			cout << "\n   Password and confirm password does not match. ";
		}
	} while (strcmp(newPass.c_str(), check.c_str()) != 0);
	std.Password = newPass;

}




void OutputStudent(Student std)
{
	std.StudentID = std.Username;
	cout << "\n - Student ID: " << std.StudentID;
	cout << "\n - First Name: " << std.FirstName;
	cout << "\n - Last Name: " << std.LastName;
	if (std.Gender == 1)
	{
		cout << "\n - Gender: Female";
	}
	else cout << "\n - Gender: Male";
	cout << "\n - Date of Birth: " << std.DateofBirth;
	cout << "\n - Social ID :  " << std.SocialID;
	std.email = std.StudentID.insert(8,"@student.hcmus.edu.vn");
	cout << "\n - Email :  " << std.email;
}

string remove_spaces(const string& s)
{
	int last = s.size() - 1;
	while (last >= 0 && s[last] == ' ')
		--last;
	return s.substr(0, last + 1);
}

void ReadFileStudent(Student &std, fstream& File)
{
	getline(File, std.Username);
	std.Username = remove_spaces(std.Username);
	string temp;
	getline(File, temp, ',');
	SplitName(temp, std.FirstName, std.LastName);
	getline(File, temp, ',');
	std.Gender = stoi(temp);
	getline(File, std.DateofBirth, ',');
	File >> std.SocialID;
	getline(File, temp);
	getline(File, std.Password);
	std.Password = SplitPassword(std.Password);
	getline(File, temp);
}
