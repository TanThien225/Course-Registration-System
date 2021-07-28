#include "Course.h"

void inputSession(Session& S)
{
	do {
		cout << "\t\t\tInput day of week(MON: 2 / TUE: 3 / WED: 4 / THU: 5 / FRI: 6 / SAT: 7): ";
		cin >> S.day;
		if (S.day < 2 || S.day > 7)
		{
			cout << "\t\t\tInvalid Input. Please Enter again !\n";
		}
	} while (S.day < 2 || S.day > 7);
	do {
		cout << "\t\t\tInput the Shift of course [1 (07:30)] [2 (09:30)] [3 :(13:30)] and [4: (15:30)]:";
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
	}
	for (NODE_Course* p = semester.pHead; p != NULL; p = p->pNext)
	{
		outputCourse(p->data);
		cout << endl;
	}
	cout << "\n------------------\n";
}

void MenuSemester(Semester& semester)
{
	int choice = -1;
	while (choice)
	{
		cout << "\t\t\t------------------Academic Staff Member HCMUS------------------\n";
		cout << "\t\t\t 1. Print List of Course. \n";
		cout << "\t\t\t 2. Add Course. \n";
		cout << "\t\t\t 3. XXXXXX. \n";
		cout << "\t\t\t 4. XXXXXX. \n";
		cout << "\n\n\t\t\t 0. Return \n";
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
			printSemesterCourses(semester);
			break;
		}
		case 2:
		{
			system("cls");
			Course course;
			while (getchar() != '\n');
			inputCourse(course);
			addCourse(semester, course);
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