                                                                    //group rating data output.
                                                                    //data entry via files.
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

short sub_count = 0, st_count = 0;

class subject {
	string sub_name = "Unnamed subject";
public:                              //set- & get- functions
	string get_sub_name() {
		return sub_name;
	}        
	void set_sub_name(string Name) {
		sub_name = Name;
	}
};

class student {
	string st_name = "Unnamed student";
	short* marks = nullptr;
public:                              //set- & get- functions
	student() {
		marks = new short[sub_count]{0};    //act a dynamic array of marks to each object
	}
	void set_marks(short Mark,int i) {
		marks[i] = Mark;
	}
	void set_st_name(string Name) {
		st_name = Name;
	}
	string get_st_name() {
		return st_name;
	}
	short get_marks(int i) {
		return marks[i];
	}
	~student() {
		delete[]marks;
	}    
};

class group {
	string group_name = "Unnamed group";
	student *students=nullptr;
	subject* subjects = nullptr;
public:
	group(string name) {
		group_name = name;
		ifstream fin;
		string file_name; //variable to take file names
		string str;    //variable to take names of subjects and students
		bool temp=0;
		short count = 0;  //variable to save count of subjects and students

		while (!temp) {
			cout << "\n\nPut full name of file with list of subjects: ";
			cin >> file_name;
			fin.open(file_name);
			if (!fin.is_open()) { cout << "\n\nError of file oppening..."; }  //check the file
			else {
				temp = 1;
				while (!fin.eof()) {   //counting subjects
					str = "";
					getline(fin, str);
					count++;
				}
				fin.close();
				sub_count = count;
				subjects = new subject[count];   //act a dynamic array of subjects
				fin.open("E:\Subs.txt");
				for (int i = 0; i < count; i++) {
					str = "";
					getline(fin, str);
					subjects[i].set_sub_name(str);  //save names of subjects in array
				}
				fin.close();
			}
		}
		temp = 0;
		while (!temp) {
			cout << "\n\nPut full name of file with list of students: ";    //check the file
			cin >> file_name;
			fin.open(file_name);
			count = 0;
			if (!fin.is_open()) { cout << "\nError of file oppening..."; }
			else {
				temp = 1;
				while (!fin.eof()) {   //counting subjects
					str = "";
					getline(fin, str);
					count++;
				}
				fin.close();
				st_count = count;
				students = new student[count];  //act a dynamic array of students
				fin.open("E:\Studs.txt");
				for (int i = 0; i < count; i++) {
					str = "";
					getline(fin, str);
					students[i].set_st_name(str);  //save names of students in array
				}
				fin.close();
			}
		}
		temp = 0;
		while (!temp) {
			cout << "\n\nPut full name of file with list of marks: ";    //check the file
			cin >> file_name;
			fin.open(file_name);
			short mark;  //variable to take marks
			if (!fin.is_open()) { cout << "\nError of file oppening..."; }
			else {
				temp = 1;
				for (int i = 0; i < st_count; i++) {
					for (int j = 0; j < sub_count; j++) {
						mark = 0;
						fin >> mark;
						students[i].set_marks(mark, j);  //save marks to each oject
					}
				}
			}
			fin.close();
		}		
	};
	void show_marks() {
		cout << endl;
		for (int j = 0; j < sub_count; j++) {
			cout << "\t\t" << subjects[j].get_sub_name();
		}
		cout << endl;
		for (int j = 0; j < st_count; j++) {
			cout << students[j].get_st_name() << "\t\t";
			for (int i = 0; i < sub_count; i++) {
				cout << students[j].get_marks(i) << "\t\t";
			}
			cout << endl;
		}
	}
	void show_average_st() {
		cout << endl;
		for (int j = 0; j < st_count; j++) {
			cout << students[j].get_st_name() << "\t\taverage mark - ";
			float aver = 0;   //variable to take average mark
			for (int i = 0; i < sub_count; i++) {
				aver += students[j].get_marks(i);
			}
			cout << round((aver / sub_count) * 10) / 10<< endl; //rounding the average markt to 10'
		}
	}
	void show_average_sub() {
		cout << endl;
		for (int j = 0; j < sub_count; j++) {
			cout << subjects[j].get_sub_name() << "\t\taverage mark - ";
			float aver = 0;  //variable to take average mark
			for (int i = 0; i < st_count; i++) {
				aver += students[i].get_marks(j);
			}
			cout << round((aver / st_count) * 10) / 10 << endl;  //rounding the average markt to 10'
		}
	}
	void show_average_gr() {
		cout << endl<< group_name << "\t\taverage mark - ";
		float aver1 = 0; //1st variable to take average mark
		for (int j = 0; j < sub_count; j++) {
			float aver = 0;  //2st variable to take average mark
			for (int i = 0; i < st_count; i++) {
				aver += students[i].get_marks(j);
			}
			aver1+=aver/st_count;
		}
		cout << round((aver1 / sub_count) * 100) / 100<< endl;;  //rounding the average markt to 100'
	}
	
	void max_min() {    //too hard to explain method
		cout << endl;
		short max = 0, min = 0;
		string max_st, min_st;
		for (int i = 0; i < sub_count; i++) {
			max = 0;
			max_st = "";
			for (int j = 0; j < st_count; j++) {
					if (students[j].get_marks(i) > max) {
						max = students[j].get_marks(i);
						max_st = "";
						max_st = students[j].get_st_name();
					}
					else {
						if (students[j].get_marks(i) == max) {
							max_st += ", " + students[j].get_st_name();
						}
					}
			}
			cout<< endl << "The highest mark of "<<subjects[i].get_sub_name()<<" has "<< max_st << " - " << max;
		}
		cout << endl;
		for (int i = 0; i < sub_count; i++) {
			min = students[0].get_marks(i);
			min_st = students[0].get_st_name();
			for (int j = 1; j < st_count; j++) {
				if (students[j].get_marks(i) <min) {
					min = students[j].get_marks(i);
					min_st = "";
					min_st = students[j].get_st_name();
				}
				else {
					if (students[j].get_marks(i) == min) {
						min_st += ", " + students[j].get_st_name();
					}
				}
			}
			cout << endl << "The lowest mark of " << subjects[i].get_sub_name() << " has " << min_st << " - " << min;
		}
		cout << endl;
	}
	~group() {
		delete[]subjects;
		delete[]students;
	}
};

int main() {
	string group_name;
	cout << "Put name of the group: ";
	getline(cin, group_name);
	group Group(group_name);

	short choose;
	while (1) {
		cout << endl << "Choose an action: ";
		cout << endl << "1) Show mark list";
		cout << endl << "2) Show avarege marks of students";
		cout << endl << "3) Show avarage marks of subjects";
		cout << endl << "4) Show avarage mark of group";
		cout << endl << "5) show max & min marks of subjects" << endl;
		cin >> choose;
		switch (choose) {
		case 1:
			Group.show_marks();
			break;
		case 2:
			Group.show_average_st();
			break;
		case 3:
			Group.show_average_sub();
			break;
		case 4:
			Group.show_average_gr();
			break;
		case 5:
			Group.max_min();
			break;
		default:
			cout << "Wrong number!";
			break;
		}
	}
	cout << endl << endl;
	return 0;
}