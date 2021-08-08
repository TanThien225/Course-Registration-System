#include "Course.h"

void inputSession(Session& S)
{
	do {
		cout << "\t\t\tInput day of week:\n\t\t\t   [MON: 2]\n\t\t\t   [TUE: 3]\n\t\t\t   [WED: 4]\n\t\t\t   [THU: 5]\n\t\t\t   [FRI: 6]\n\t\t\t   [SAT: 7]\n\t\t\t->";
		cin >> S.day;
		if (S.day < 2 || S.day > 7)
		{
			cout << "\t\t\tInvalid Input. Please Enter again !\n";
		}
	} while (S.day < 2 || S.day > 7);
	do {
		cout << "\t\t\tInput the Shift of course:\n\t\t\t   [1 (07:30)]\n\t\t\t   [2 (09:30)]\n\t\t\t   [3 :(13:30)]\n\t\t\t   [4: (15:30)]\n\t\t\t->";
		cin >> S.shift;
		if (S.shift < 1 || S.shift > 4)
		{
			cout << "\t\t\tInvalid Input. Please Enter again !\n";
		}
	} while (S.shift < 1 || S.shift > 4);
}

void outputSession(Session S)
{
	switch (S.day)
	{
	case 2:
	{
		cout << "Monday";
		break;
	}
	case 3: {
		cout << "Tuesday";
		break;
	}
	case 4: {
		cout << "Wednesday";
		break;
	}
	case 5: {
		cout << "Thursday";
		break;
	}
	case 6: {
		cout << "Friday";
		break;
	}
	case 7: {
		cout << "Saturday";
		break;
	}
	}
	switch (S.shift)
	{
	case 1:
	{
		cout << " (07:30)";
		break;
	}
	case 2:
	{
		cout << " (09:30)";
		break;
	}
	case 3: {
		cout << " (13:30)";
		break;
	}
	case 4: {
		cout << " (15:30)";
		break;
	}
	}
}

void inputCourse(Course& course)
{
	cout << "\t\t\tInput course ID: ";
	getline(cin, course.id);
	cout << "\t\t\tInput Name of the course: ";
	getline(cin, course.name);
	cout << "\t\t\tInput Teacher name: ";
	getline(cin, course.teacherName);
	cout << "\t\t\tInput number of credits: ";
	cin >> course.numCredit;
	cout << "\t\t\tInput the Maximum number of students in the course: ";
	cin >> course.maximumStudent;
	for (int i = 0; i < 2; i++)
	{
		cout << "\t\t\t - Input Session number " << i + 1 << endl;
		inputSession(course.Sessions[i]);
	}
}

void outputCourse(Course& course)
{
	cout << setw(10) << left << course.id << "\t";
	cout << setw(20) << left << course.name << "\t";
	cout << setw(30) << left << course.teacherName << "\t";
	cout << setw(6) << left << course.numCredit << "\t";
	cout << setw(6) << left << course.maximumStudent << "\t";
	//cout << "Course Session: ";
	cout << left; outputSession(course.Sessions[0]);
	cout << ", "; outputSession(course.Sessions[1]); cout << "\t";
}

void createSemester(Semester& semester)
{
	//cout << "\nSemester ";
	cout << "\nInput Start date of the Semester: \n";
	inputDate(semester.start);
	cout << "\nInput End date of the Semester: \n";
	inputDate(semester.end);
	semester.pHead = NULL;
	semester.pTail = NULL;
}

void addCourse(Semester& semester, Course course)
{
	NODE_Course* newC = new NODE_Course;
	newC->data = course;
	newC->pNext = NULL;

	if (semester.pHead == NULL)
	{
		semester.pHead = semester.pTail = newC;
		return;
	}
	semester.pTail->pNext = newC;
	semester.pTail = newC;
}

void printSemesterCourses(Semester semester)
{
	if (semester.pHead == NULL)
	{
		cout << "There aren't any Courses\n";
		return;
	}
	cout << "\n" << setw(3) << left << "No" << "\t" << setw(10) << left << "Course ID " << "\t" << setw(20) << left
		<< "Course Name" << "\t" << setw(30) << left << "Teacher Name" << "\t" << setw(6) << left
		<< "Credits" << "\t" << setw(6) << left << "Max" << "\t" << setw(10) << left
		<< "Dayofweek" << endl;
	for (int i = 0; i < 140; i++)
	{
		cout << "=";
	}
	cout << endl;
	int i = 0;
	for (NODE_Course* p = semester.pHead; p != NULL; p = p->pNext)
	{
		cout << left << setw(3) << ++i << "\t";
		outputCourse(p->data);
		cout << endl;
	}
	cout << endl;	cout << endl;
}

void MenuSemester(Semester& semester, RegisSession& regis)
{
	int choice = -1;
	while (choice)
	{
		cout << "\t\t\t------------------Create The Semester and The Course Registration------------------\n";
		cout << "\t\t\t 1. Create a course registration session. \n";
		cout << "\t\t\t 2. View List of Courses. \n";
		cout << "\t\t\t 3. Add Course. \n";
		cout << "\t\t\t 4. Update course information. \n";
		cout << "\t\t\t 5. Delete a course. \n";
		cout << "\n\t\t\t 0. Done \n";
		cout << "\t\t\t\nEnter choice: ";
		cin >> choice;
		switch (choice)
		{
		case 0:
		{
			system("cls");
			cout << setw(20) << "\nType 'Y' to confirm or any other to cancel: ";
			char ch;
			cin >> ch;//get confirmation
			if (ch == 'y' || ch == 'Y') {
				break;
			}
			else {
				system("cls");
				MenuSemester(semester, regis);
			}
			break;
		}
		case 1:
		{	
			system("cls");
			if (regis.createdStat == false) {
				cout << "\t\t\t---------Create a course Registration Session---------\n";
				cout << " - Input Start date: ";
				inputDate(regis.startD);
				cout << "\n - Input End date: ";
				inputDate(regis.endD);
				regis.createdStat = true;
			}
			else cout << "\nThe course Registration Session has been created !\n";
			break;
		}
		case 2:
		{
			system("cls");
			printSemesterCourses(semester);
			break;
		}
		case 3:
		{
			system("cls");
			Course course;
			while (getchar() != '\n');
			inputCourse(course);
			addCourse(semester, course);
			break;
		}
		case 4:
		{
			system("cls");
			NODE_Course* update = new NODE_Course;
			update = findCourse(semester);
			if (update == NULL)
			{
				cout << "Can not find any Course related to the ID or Name!\n";
			}
			else {
				updateCourse(semester, update);
			}
			break;
		}
		case 5:
		{
			system("cls");
			printSemesterCourses(semester);
			deleteCourse(semester);
			break;
		}
		default:
			break;
		}
	}
}


bool conflictSession(Session A, Session B)
{
	if (A.day == B.day && A.shift == B.shift)
	{
		return true;
	}
	return false;
}

bool conflictCourse(Course A, Course B)
{
	bool check = false;
	for (int i = 0; i < 2; i++)
	{
		if (conflictSession(A.Sessions[0], B.Sessions[i]))
		{
			check = true;
			return check;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (conflictSession(A.Sessions[1], B.Sessions[i]))
		{
			check = true;
			return check;
		}
	}
	return check;

}

void deleteHeadCourse(Semester& semester)
{
	if (semester.pHead == NULL)
	{
		return;
	}
	NODE_Course* p = semester.pHead;
	semester.pHead = semester.pHead->pNext;
	delete p;
}

void deleteTailCourse(Semester& semester)
{
	if (semester.pHead == NULL)
	{
		return;
	}
	if (semester.pHead->pNext == NULL)
	{
		deleteHeadCourse(semester);
		return;
	}
	for (NODE_Course* p = semester.pHead; p != NULL; p = p->pNext)
	{
		if (p->pNext == semester.pTail)
		{
			delete semester.pTail;
			p->pNext = NULL;
			semester.pTail = p;
			return;
		}
	}
}

void deleteCoursebyID(Semester& semester, string idCourseDEL)
{
	if (semester.pHead == NULL)
	{
		cout << "\n List of Courses is Empty!\n";
		return;
	}
	if (semester.pHead->data.id == idCourseDEL)
	{
		deleteHeadCourse(semester);
	}
	if (semester.pTail->data.id == idCourseDEL)
	{
		deleteTailCourse(semester);
	}
	NODE_Course* temp = new NODE_Course;
	NODE_Course* prev = new NODE_Course;
	for (NODE_Course* p = semester.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.id == idCourseDEL)
		{
			temp = p;
			prev->pNext = p->pNext;
			p = prev;
			delete temp;
		}
		prev = p;
	}
}

void deleteCoursebyName(Semester& semester, string NameCourseDEL)
{
	if (semester.pHead == NULL)
	{
		cout << "\n List of Courses is Empty!";
		return;
	}
	if (semester.pHead->data.name == NameCourseDEL)
	{
		deleteHeadCourse(semester);
	}
	if (semester.pTail->data.name == NameCourseDEL)
	{
		deleteTailCourse(semester);
	}
	NODE_Course* temp = new NODE_Course;
	NODE_Course* prev = new NODE_Course;
	for (NODE_Course* p = semester.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.name == NameCourseDEL)
		{
			temp = p;
			prev->pNext = p->pNext;
			p = prev;
			delete temp;
		}
		prev = p;
	}
}

void deleteCourse(Semester& semester)
{
	int choice=-1;
	system("cls");
	printSemesterCourses(semester);
	while (choice) {
		cout << "\t\t\t---------------- DELETE COURSE ----------------\n";
		cout << "\t\t\t 1. Delete by Course id\n";
		cout << "\t\t\t 2. Delete by Course Name\n";
		cout << "\t\t\t 0. Return\n";
		cout << "\t\t\t------------------------------------------------\n";
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
			//system("cls");
			while (getchar() != '\n');
			string idCourseDel;
			cout << " Input Id of the Course to delete: ";
			getline(cin, idCourseDel);
			deleteCoursebyID(semester, idCourseDel);
			break;
		}
		case 2:
		{
			//system("cls");
			while (getchar() != '\n');
			string NameCourseDel;
			cout << " Input Name of the Course to delete: ";
			getline(cin, NameCourseDel);
			deleteCoursebyName(semester, NameCourseDel);
			break;
		}
		default:
		{
			cout << "\t\t\tInvalid Input. Please Enter again !\n";
			break;
		}
		}
	}
}

bool checkCoursebyID(Semester semester, string idCourse)
{
	if (semester.pHead == NULL)
	{
		return false;
	}
	for (NODE_Course* p = semester.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.id == idCourse)
		{
			return true;
		}
	}
	return false;

}

bool checkCoursebyName(Semester semester, string NameCourse)
{
	if (semester.pHead == NULL)
	{
		return false;
	}
	for (NODE_Course* p = semester.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.name == NameCourse)
		{
			return true;
		}
	}
	return false;

}

NODE_Course* findCourse(Semester& semester)
{
	while (getchar() != '\n');
	string keyword;
	cout << " Input Course ID or Course Name to update: ";
	getline(cin, keyword);
	if (checkCoursebyID(semester, keyword))
	{
		for (NODE_Course* p = semester.pHead; p != NULL; p = p->pNext)
		{
			if (p->data.id == keyword)
			{
				return p;
			}
		}
	}
	else if (checkCoursebyName(semester, keyword))
	{
		for (NODE_Course* p = semester.pHead; p != NULL; p = p->pNext)
		{
			if (p->data.name == keyword)
			{
				return p;
			}
		}
	}
	else {
		return NULL;
	}
}
void updateCourse(Semester& semester, NODE_Course* update)
{
	int choice = -1;
	system("cls");
	outputCourse(update->data);
	while (choice) {
		cout << "\t\t\t---------------- UPDATE COURSE ----------------\n";
		cout << "\t\t\t 1. Update Teacher name\n";
		cout << "\t\t\t 2. Update the Number of Credits\n";
		cout << "\t\t\t 3. Update the maximum number of students\n";
		cout << "\t\t\t 4. Update day of the week, and the session that the course will be performed\n";
		cout << "\t\t\t 0. Return\n";
		cout << "\t\t\t------------------------------------------------\n";
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
			system("cls");
			while (getchar() != '\n');
			string change;
			cout << " Input Teacher name to Update: ";
			getline(cin, change);
			update->data.teacherName = change;
			break;
		}
		case 2:
		{
			system("cls");
			while (getchar() != '\n');
			int change;
			cout << " Input the Number of Credits to Update: ";
			cin >> change;
			update->data.numCredit = change;
			break;
		}
		case 3:
		{
			system("cls");
			while (getchar() != '\n');
			int change;
			cout << " Input the maximum number of students to Update: ";
			cin >> change;
			update->data.maximumStudent = change;
			break;
		}
		case 4:
		{
			system("cls");
			while (getchar() != '\n');
			Session sessions[2];
			cout << " Input day of the week, and the session to Update: \n";
			for (int i = 0; i < 2; i++)
			{
				cout << "\t\t\t - Input Session Change number " << i + 1 << endl;
				inputSession(sessions[i]);
			}
			update->data.Sessions[0] = sessions[0];
			update->data.Sessions[1] = sessions[1];
			break;
		}
		default:
		{
			cout << "\t\t\tInvalid Input. Please Enter again !\n";
			break;
		}
		}
	}
}

bool findCourseEnrollment(Semester& semester, Course& enrollCourse)
{
	Course enroll;
	while (getchar() != '\n');
	string keyword;
	cout << " Input Course ID or Course Name to enroll: ";
	getline(cin, keyword);
	if (checkCoursebyID(semester, keyword))
	{
		for (NODE_Course* p = semester.pHead; p != NULL; p = p->pNext)
		{
			if (p->data.id == keyword)
			{
				enrollCourse = p->data;
				return true;
			}
		}
	}
	else if (checkCoursebyName(semester, keyword))
	{
		for (NODE_Course* p = semester.pHead; p != NULL; p = p->pNext)
		{
			if (p->data.name == keyword)
			{
				enrollCourse = p->data;
				return true;
			}
		}
	}
	return false;
}

