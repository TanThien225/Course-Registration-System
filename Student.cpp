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

void InputStudent(Student& std)
{
	cout << " - Input Student ID: ";
	cin >> std.Username;
	std.Username = std.StudentID;
	while (getchar() != '\n');
	cout << " - Input First Name of the Student: ";
	getline(cin, std.FirstName);
	cout << " - Input Last Name of the Student: ";
	getline(cin, std.LastName);
	cout << " - Choose Gender of the Student(1: Female, 0: Male): ";
	cin >> std.Gender;
	while (getchar() != '\n');
	cout << " - Input Date of Birth of the Student(DD/MM/YYYY): ";
	getline(cin, std.DateofBirth);
	cout << " - Input Student Social ID: ";
	cin >> std.SocialID;
}


void OutputStudent(Student &std)
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
	std.StudentID = remove_spaces(std.StudentID);
	std.email = std.StudentID + "@student.hcmus.edu.vn";
	cout << "\n - Email :  " << std.email;
}

void OutputStdinLine(Student& std)
{
	std.StudentID = std.Username;
	//std.StudentID = remove_spaces(std.StudentID);
	cout << setw(10) << left << std.StudentID << "\t";
	cout << setw(10) << left << std.FirstName << "\t";
	cout << setw(18) << left << std.LastName << "\t";
	if (std.Gender == 1)
	{
		cout << setw(10) << left << "Female" << "\t";
	}
	else cout << setw(10) << left << "Male" << "\t";
	cout << setw(12) << left << std.DateofBirth << "\t";
	cout << setw(10) << left << std.SocialID<< "\t";
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
