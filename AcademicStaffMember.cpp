#include"AcademicStaffMember.h"

void OutputAStaff(AcademicStaff st)
{
	cout << "\n - Academic Staff ID: " << st.IDStaff;
	cout << "\n - First Name: " << st.FirstName;
	cout << "\n - Last Name: " << st.LastName;
	if (st.Gender == 1)
	{
		cout << "\n - Gender: Female";
	}
	else cout << "\n - Gender: Male";
	cout << "\n - Date of Birth: " << st.DateofBirth;
	cout << "\n - Social ID :  " << st.SocialID;
	cout << "\n - Email :  " << st.email;
}

void ReadFileAStaff(AcademicStaff& st, fstream& File)
{
	getline(File, st.IDStaff);
	string temp;
	getline(File, temp, ',');
	SplitName(temp, st.FirstName, st.LastName);
	getline(File, temp, ',');
	st.Gender = stoi(temp);
	getline(File, st.DateofBirth, ',');
	File >> st.SocialID;
	getline(File, temp);
	getline(File, st.email);
	getline(File, st.Username);
	getline(File, st.Password);
	st.Password = SplitPassword(st.Password);
	getline(File, temp);
}
