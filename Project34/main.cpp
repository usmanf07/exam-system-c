#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

class Myquestion;
class Question;
class Quiz;

class Course {

private:
	string name;
	string courseId;
	Quiz** quiz;
	int noQuizzes;

public:

	void setName(string n)
	{
		name = n;

	}
	void setCode(string c)
	{
		courseId = c;
	}
	void printInfo()
	{
		cout << name << " " << courseId << endl;
	}
};

class AllCourses {
	Course* mycourse;
	static int totalCourses;

public:
	AllCourses()
	{
		totalCourses = 0;
	}
	Course* LoadCourse(string file) {
		ifstream Input(file);
		string temp;
		string courseNames[20];
		string courseCode[20];
		if (Input.is_open())
		{
			getline(Input, temp);
			string copy = temp;
			stringstream ss(temp);

			string temp1;
			int count = 0;

			while (getline(ss, temp1, ',')) {
				if (temp1 != "")
				{
					courseNames[count] = temp1;
					count++;
				}
			}
			getline(Input, temp);
			stringstream s1(temp);
			int c = 0, i = 0;
			while (getline(s1, temp1, ',')) {
				if (temp1 != "" && i > 2)
				{
					courseCode[c] = temp1;
					c++;

				}
				i++;
			}
			mycourse = new Course[count];
			for (int i = 0; i < count; i++)
			{
				mycourse[i].setCode(courseCode[i]);
				mycourse[i].setName(courseNames[i]);
			}



			totalCourses = count;

			Input.close();
		}
		else {

			cout << "error in opening file";
		}

		return mycourse;
	}
	int getTotalCourses()
	{
		return totalCourses;
	}
};

class Quiz {
private:
	Question** questionList;
	int numQuestions;
	int totalTime;
public:
	Quiz() 
	{
		questionList = nullptr;
		numQuestions = 0;
		totalTime = 0;
	}


};

class User
{
protected:
	string id;
	string name;
	string password;
	Course** userCourses;
	int totalCourses;

public:
	User() {
	}
	User(string id, string name)
	{
		this->name = name;
	}

	string getID()
	{
		return id;
	}

	string getName()
	{
		return name;
	}

	string getPassword()
	{
		return password;
	}

	void setPassword(string pass)
	{
		this->password = pass;
	}

	void setDetails(string line, Course* allCourses)
	{
		string tempCourses[20];
		string id, name, serial;
		stringstream ss(line);

		getline(ss, serial, ','); //Skip Serial
		getline(ss, id, ',');	//get Id from file
		getline(ss, name, ',');	//get name from file

		//set id and name
		this->id = id;
		this->name = name;
		string temp1;
		int c = 0;

		//load each user courses from file
		while (getline(ss, temp1, ','))
		{
			if (temp1 != "")
			{
				tempCourses[c] = temp1;
				c++;
			}
		}

		//find courses that they have
		int k = 0;
		for (int i = 0; i < c; i++)
		{
			if (tempCourses[i] == "1")
			{
				k++;
			}
		}

		this->totalCourses = k;	//set total courses user have
		this->userCourses = new Course * [totalCourses];	//initialize user courses array

		//set user courses
		for (int i = 0, j = 0; i < c; i++)
		{
			if (tempCourses[i] == "1")
			{
				this->userCourses[j] = &allCourses[i];
				j++;
			}
		}
	}

	void printCourses()
	{
		for (int i = 0; i < totalCourses; i++)
		{
			cout << i + 1 << ". ";
			userCourses[i]->printInfo();
		}
		cout << endl;
	}

	void printData()
	{
		cout << id << " " << name << " " << password << endl;
		//printCourses();

	};
	virtual ~User() {}
};


class Teacher : public User {

private:
	static int totalTeachers;

public:
	void makeQuiz()
	{
		int n = 0;
		cout << "Please select the course you would like to make the quiz for: " << endl;
		printCourses();
		cin >> n;
		Course* course = userCourses[n - 1];
		
	}
	void printTeacherMenu(string name)
	{
		cout << "Welcome Dear " << name << endl;
		cout << "What would you like to do today?" << endl;
		cout << "1. Make A Quiz" << endl;
	}
};

class Student : public User {
private:
	static int totalStudents;

public:
	
};

int Teacher::totalTeachers = 0;
int Student::totalStudents = 0;
int AllCourses::totalCourses = 0;

class System
{
private:

	User** usersList;
	Course* coursesList;
	int totalUsers;
	User* currentUser;

public:

	System()
	{
		usersList = new User * [250];
		totalUsers = 0;

	}

	void loadData(string teacher_fileName, string student_file)
	{
		AllCourses Temp;
		this->coursesList = Temp.LoadCourse(student_file);
		int totalC = Temp.getTotalCourses();

		int total = 0;
		int countTeachers = 0;
		int countStudents = 0;

		ifstream teacherFile(teacher_fileName);
		if (teacherFile.is_open())
		{
			string line;
			getline(teacherFile, line); // skip first line
			getline(teacherFile, line); // skip second line

			while (!teacherFile.eof())
			{
				getline(teacherFile, line);
				User* teacher = new Teacher();
				teacher->setDetails(line, this->coursesList);
				usersList[total] = teacher;
				total++;
			}
			countTeachers = total;
			teacherFile.close();
		}


		ifstream studentFile(student_file);
		if (studentFile.is_open())
		{
			string line;
			getline(studentFile, line); // skip first line
			getline(studentFile, line); // skip second line

			while (!studentFile.eof())
			{
				getline(studentFile, line);
				int check = line.find("Total no of Students");
				if (check == -1)
				{
					User* student = new Student();
					student->setDetails(line, this->coursesList);
					usersList[total] = student;
					total++;
				}

			}
			countStudents = total - countTeachers;
			studentFile.close();
		}
		totalUsers = total;
	}
	void generateLogins()
	{
		string filename = "logins.csv";
		ifstream file(filename);
		if (!file.is_open())
		{
			ofstream fout("logins.csv");
			for (int i = 0; i < totalUsers; i++)
			{
				string username = usersList[i]->getID();
				string password = "123456";
				fout << username << "," << password;
				if (i != totalUsers - 1)
					fout << endl;
			}
			fout.close();

		}
		file.close();
		ifstream logs(filename);
		if (logs.is_open())
		{
			int i = 0;
			while (!logs.eof())
			{
				string line;
				getline(logs, line);
				string user, pass;
				stringstream ss(line);
				getline(ss, user, ',');
				getline(ss, pass);
				usersList[i]->setPassword(pass);
				i++;
			}
			logs.close();

		}

	}

	int verifyLogin(string u, string p)
	{
		for (int i = 0; i < totalUsers; i++)
		{
			string user = usersList[i]->getID();
			string password = usersList[i]->getPassword();

			if (u == user && p == password)
			{
				return i;
			}

		}
		return -1;
	}

	void login()
	{
		string user, pass;
		cout << "Enter Username" << endl;
		//cin >> user;
		user = "t46905";
		cout << "Enter Password" << endl;
		pass = "123456";
		//cin >> pass;
		int n = verifyLogin(user, pass);
		if (n != -1)
		{
			currentUser = usersList[n];
			if (Teacher* teacher = dynamic_cast<Teacher*>(currentUser)) 
			{
				int n = 0;
				teacher->printTeacherMenu(currentUser->getName());
				cin >> n;
				if (n == 1)
				{
					teacher->makeQuiz();
				}
			}
			else if (Student* student = dynamic_cast<Student*>(currentUser)) {
				cout << "Current user is a Student." << endl;
			}
		}
		else
		{
			cout << "invalid pass entered";
		}
	}
};

class Question {
protected:
	string topic;
	string statement;
public:
	Question()
	{
		statement = "";
	}

public:

	void setTopic(string t)
	{
		topic = t;
	}
	virtual void LoadQuestion(ifstream& fin) {

		cout << "Loading Question";
	}
	virtual void printDetail()
	{
		cout << "Statement of Question " << statement;
		cout << endl;
		cout << "Topic of this Question " << topic;
		cout << endl;
	}
};

class MCQs : public Question {


	string options[4];
	int correctOption;


public:
	void printDetail()
	{
		Question::printDetail();
		cout << "Options for this Question are ";
		for (int i = 0; i < 4; i++)
		{
			cout << options[i] << endl;

		}
	}
	void LoadQuestion(ifstream& fin) {

		string temp;
		getline(fin, temp);
		int current = 0;
		while (temp != "")
		{
			int position = temp.find("option");
			if (position == -1)
			{
				statement = statement + temp + " ";
			}
			else {


				options[current] = temp;
				current++;


			}
			getline(fin, temp);


		}




	}

};
class TFalse : public Question {
	string options[2];
	int correctOption;

public:
	void printDetail()
	{
		Question::printDetail();
		cout << "Options for this Question are ";
		for (int i = 0; i < 2; i++)
		{
			cout << options[i] << endl;

		}
	}

	void LoadQuestion(ifstream& fin) {
		string temp;
		getline(fin, temp);
		int current = 0;
		while (temp != "")
		{
			int position = temp.find("option");
			if (position == -1)
			{
				statement = statement + temp + " ";
			}
			else {


				options[current] = temp;
				current++;


			}
			getline(fin, temp);


		}




	}


};
class Subjective : public Question {

public:
	void LoadQuestion(ifstream& fin) {

		string temp;
		getline(fin, temp);

		while (temp != "")
		{
			statement = statement + temp + " ";
			getline(fin, temp);


		}




	}


};




class QuestionBank
{
	Question** AllQuestions;

	int count;

public:
	QuestionBank()
	{
		AllQuestions = new Question * [100];
		count = 0;
	}
	void MakeBank(string filename)
	{
		ifstream Input(filename);	
		string temp;
		string topic;
		Question* temp1;
		if (Input.is_open())
		{


			while (!Input.eof())
			{
				getline(Input, temp);


				if (temp == "a5380ee")
				{
					getline(Input, topic);
				}
				if (temp == "2efcde9")
				{
					temp1 = new MCQs();
					temp1->LoadQuestion(Input);
					temp1->setTopic(topic);
					AllQuestions[count] = temp1;

					count++;
				}
				if (temp == "b94d27b")
				{
					temp1 = new TFalse();
					temp1->LoadQuestion(Input);
					temp1->setTopic(topic);
					AllQuestions[count] = temp1;
					count++;
				}

				if (temp == "88f7ace")
				{
					temp1 = new Subjective();
					temp1->LoadQuestion(Input);
					temp1->setTopic(topic);
					AllQuestions[count] = temp1;
					count++;
				}

			}


			for (int i = 0; i < count; i++)
			{
				AllQuestions[i]->printDetail();
				cout << endl;
				cout << endl;
			}
		}
		else {
			cout << "Error Opening File";
		}


	}
};

void main() {

	System s;
	s.loadData("teachers_list.csv", "courses_offering_list.csv");
	s.generateLogins();
	s.login();


	/*QuestionBank myquestions;
	myquestions.MakeBank("testbank.txt");*/


}