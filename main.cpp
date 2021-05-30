#include <iostream>
#define endl '\n'
using namespace std;

const int MAXSPEC = 20;
const int MAXQUEUE = 5;
string names[MAXSPEC + 1][MAXQUEUE + 1];
int status[MAXSPEC + 1][MAXQUEUE + 1];
int Max_Queue[MAXSPEC + 1];

int menu()
{
	int choice = -1;
	while (choice == -1)
	{
		cout << "1) Add new patient" << endl
			 << "2) Print all patients" << endl
			 << "3) Get next patient" << endl
			 << "4) Exit" << endl
			 << "Enter your choice: ";
		cin >> choice;
		if (!(choice >= 1 && choice <= 4))
		{
			cout << "Invalid choice, try again" << endl;
			choice = -1;
		}
	}
	return choice;
}

void shift_right(string name[], int spec, int stat[])
{
	int len = Max_Queue[spec];
	for (int i = len - 1; i >= 0; i--)
	{
		name[i + 1] = name[i];
		stat[i + 1] = stat[i];
	}
	Max_Queue[spec]++;
}

void shift_left(string name[], int spec, int stat[])
{
	int len = Max_Queue[spec];
	for (int i = len - 1; i >= 0; i--)
	{
		name[i - 1] = name[i];
		stat[i - 1] = stat[i];
	}
	Max_Queue[spec]--;
}

void add_patient()
{
	int spec;
	string name;
	int stat;
	cout << "Enter Specialization, name, and status: ";
	cin >> spec >> name >> stat;
	cout << endl;
	int len = Max_Queue[spec];
	if (len >= MAXQUEUE)
	{
		cout << "Sorry, we can't add more patient for this specialization" << endl;
		return;
	}
	if (stat) //urgant
	{
		shift_right(names[spec], spec, status[spec]);
		names[spec][0] = name;
		status[spec][0] = stat;
	}
	else // regular
	{
		names[spec][len] = name;
		status[spec][len] = stat;
		Max_Queue[spec]++;
	}
}

void print_patients(int spec, string name[], int stat[])
{
	int len = Max_Queue[spec];
	if (!len)
		return;
	cout << "There are " << len << " Patients in specilaization " << spec << endl;
	for (int i = 0; i < len; i++)
	{
		cout << name[i];
		if (stat[i])
			cout << " urgent" << endl;
		else
			cout << " regular" << endl;
	}
	cout << endl;
}

void print()
{
	cout << "***********************************" << endl;
	for (int spec = 1; spec < MAXSPEC; spec++)
	{
		print_patients(spec, names[spec], status[spec]);
	}
	cout << endl;
}

void next()
{
	int spec;
	cout << "Enter specialization: ";
	cin >> spec;
	int len = Max_Queue[spec];
	if (!len)
	{
		cout << "No Patient at the moment. Have rest, Dr" << endl;
		return;
	}
	cout << names[spec][0] << "Please go with the Dr" << endl;
	shift_left(names[spec], spec, status[spec]);
	cout << endl;
}

void hospital_system()
{
	int choice;
	while (true)
	{
		choice = menu();
		if (choice == 1)
			add_patient();
		else if (choice == 2)
			print();
		else if (choice == 3)
			next();
		else
			break;
	}
}

int main(void)
{
	hospital_system();
	return 0;
}
