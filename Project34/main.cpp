#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;

void selectionSort(int* a, int n) {
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (a[j] < a[min])
				min = j;
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}

void printTime(time_t time)
{
	char buffer[26];
	ctime_s(buffer, 26, &time);
	cout << buffer;
}

string generateRandomID(int length)
{
	string characters = "0123456789abcdef";
	string result = "";

	srand(time(nullptr));

	for (int i = 0; i < length; i++)
	{
		int randomIndex = rand() % characters.size();
		result += characters[randomIndex];
	}

	return result;
}

class Myquestion;
class Question;
class Quiz;


class Question {
protected:
	
	string statement;
	
public:
	Question()
	{
		statement = "";
		
	}

public:


	virtual void LoadQuestion(ifstream& fin) {

		cout << "Loading Question";
	}

	virtual void printDetail()
	{
		cout << "----------------------------------" << endl;
		cout << "Question: " << statement<< endl;
	}

	virtual void printQuestionSt()
	{
		cout << "----------------------------------" << endl;
		cout << statement << endl;
	}
	string getStatement()
	{
		return statement;
	}

	virtual int getCorrectOption()
	{
		return 0;
	}
	virtual string* getOption() = 0;
	virtual int gettotalOptions() = 0;
};

class MCQs : public Question {


	string* options;
	int correctOption;
	int totalOptions;

public:
	MCQs() :Question()
	{
		totalOptions = 0;
		options = new string[4];
	}
	int getCorrectOption()
	{
		return correctOption;
	}
	virtual void printQuestionSt()
	{
		Question::printQuestionSt();
		for (int i = 0; i < 4; i++)
		{
			cout << i + 1 << ". ";
			if (i == correctOption) {
				cout << "option:" << options[i].substr(options[i].find(":") + 1) << endl;
			}
			else {
				cout << options[i] << endl;
			}
		}
	}
	virtual int gettotalOptions()override
	{
		return totalOptions;
	}

	virtual string* getOption() override
	{
		return options;
	}
	void printDetail()
	{
		Question::printDetail();
		for (int i = 0; i < 4; i++)
		{
			cout << options[i] << endl;
		}
		
	}
	void LoadQuestion(ifstream& fin) {

		string temp;
		getline(fin, temp);
		int current = 0;
		while (temp != "" && !fin.eof())
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

		totalOptions = current + 1;

		for (int i = 0; i < 4; i++)
		{
			if (options[i].find("dabfac4") != -1) {
				correctOption = i;
				break;
			}
		}

	}

};
class TFalse : public Question {
	string *options;
	int correctOption;
	int totalOptions;
public:
	TFalse() :Question()
	{
		totalOptions = 0;
		options = new string[2];
	}
	int getCorrectOption()
	{
		return correctOption;
	}
	virtual string* getOption() override
	{
		return options;
	}
	virtual int gettotalOptions()override
	{
		return totalOptions;
	}
	virtual void printQuestionSt()
	{
		Question::printQuestionSt();
		for (int i = 0; i < 2; i++)
		{
			cout << i + 1 << ". ";
			if (i == correctOption) {
				cout << "option:" << options[i].substr(options[i].find(":") + 1) << endl;
			}
			else {
				cout << options[i] << endl;
			}
		}
	}

	void printDetail()
	{
		Question::printDetail();
		for (int i = 0; i < 2; i++)
		{
			cout << options[i] << endl;
		}
		
	}

	void LoadQuestion(ifstream& fin) {
		string temp;
		getline(fin, temp);
		int current = 0;
		while (temp != "" && !fin.eof())
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

			totalOptions = current + 1;
		}

		for (int i = 0; i < 2; i++)
		{
			if (options[i].find("dabfac4") != -1) {
				correctOption = i;
				break;
			}
		}
	}


};
class Subjective : public Question {

public:
	virtual string* getOption() override
	{
		return NULL;
	}
	void LoadQuestion(ifstream& fin) {

		string temp;
		getline(fin, temp);
		statement = temp;
		while (temp != "" && !fin.eof())
		{
			statement = statement + temp + " ";
			getline(fin, temp);
		}




	}
	virtual int gettotalOptions() override
	{
		return 0;
	}

};


class Topic {
	string name;
	Question** AllQuestions;
	int count;
public:

	Topic()
	{
		AllQuestions = new Question * [50];
		count = 0;
	}
	 void setName(string n)
	{
		name = n;

	}
	 Question** getAllQuestions() {
		 return AllQuestions;
	 }

	 string Load(ifstream& Input)
	 {
		 Question* temp1;
		 string temp;
		while (temp != "a5380ee" && !Input.eof())
		 {
			 if (temp == "2efcde9")
			 {
				 temp1 = new MCQs();
				 temp1->LoadQuestion(Input);
				 AllQuestions[count] = temp1;
				 count++;
			 }
			 if (temp == "b94d27b")
			 {
				 temp1 = new TFalse();
				 temp1->LoadQuestion(Input);	
				 AllQuestions[count] = temp1;
				 count++;
			 }

			 if (temp == "88f7ace")
			 {
				 temp1 = new Subjective();
				 temp1->LoadQuestion(Input);
				 AllQuestions[count] = temp1;
				 count++;
			 }

			 getline(Input, temp);


		 }
		return temp;

	 }
	
	 string getName()
	 {
		 return name;
	 }

	 void printInfo()
	 {
		 cout << "name of topic is" << name << endl;
		 for (int i = 0; i < count; i++)
		 {
			 AllQuestions[i]->printDetail();

		 }
	}
	 int getTotalQuestions()
	 {
		 return count;
	}
};

class Quiz {
private:
	string quizID;
	Question** questionList;
	int numQuestions;
	int totalTime;
	int totalMarks;
	time_t quizTime;

public:
	

	Quiz()
	{
		questionList = nullptr;
		numQuestions = 0;
		totalTime = 0;
		totalMarks = 0;
	}
	time_t getQuizSchedule()
	{
		return quizTime;
	}

	int getTotalTime()
	{
		return totalTime;
	}

	string getQuizID()
	{
		return quizID;
	}
	string loadQuestion(ifstream& Input, string temp)
	{
		string setId = temp.substr(6);
		quizID =  setId;

		getline(Input, temp);
		int timestamp = stoi(temp);
		quizTime = timestamp;
		getline(Input, temp);
		totalMarks = stoi(temp);
		getline(Input, temp);
		totalTime = stoi(temp);
		getline(Input, temp);
		numQuestions = stoi(temp);

		getline(Input, temp);
		int count = 0;
		questionList = new Question * [20];
		Question* temp1;
		while (temp.find("course") == -1 && temp.find("quiz") == -1 && !Input.eof() )
		{
			if (temp == "2efcde9")
			{
				temp1 = new MCQs();
				temp1->LoadQuestion(Input);
				questionList[count] = temp1;
				count++;
			}
			if (temp == "b94d27b")
			{
				temp1 = new TFalse();
				temp1->LoadQuestion(Input);
				questionList[count] = temp1;
				count++;
			}

			if (temp == "88f7ace")
			{
				temp1 = new Subjective();
				temp1->LoadQuestion(Input);
				questionList[count] = temp1;
				count++;
			}

			getline(Input, temp);
			
			

		}





		return temp;



	}
	
	void generateQuiz(Topic** topics, int totalTopics, int marks, int totalQuestions, time_t quizTime, int maxTime)
	{
		this->quizID = generateRandomID(7);
		this->totalTime = maxTime;
		this->numQuestions = totalQuestions;
		this->quizTime = quizTime;
		this->totalMarks = numQuestions * marks;
		Question** allQuestions = NULL;
		int topicTotalQuestion = 0;
		questionList = new Question * [numQuestions];

		int totalQuestionsInTopics = 0;
		for (int i = 0; i < totalTopics; i++)
		{
			totalQuestionsInTopics += topics[i]->getTotalQuestions();
		}

		bool* added = new bool[totalQuestionsInTopics];
		for (int i = 0; i < totalQuestionsInTopics; i++)
		{
			added[i] = false;
		}

		questionList = new Question * [numQuestions];

		int questionsAdded = 0;
		while (questionsAdded < numQuestions)
		{
			int randomTopic = rand() % totalTopics;
			Question** allQuestions = topics[randomTopic]->getAllQuestions();
			int topicTotalQuestion = topics[randomTopic]->getTotalQuestions();

			int random = rand() % topicTotalQuestion;
			int actualIndex = randomTopic * topicTotalQuestion + random;

			if (!added[actualIndex])
			{
				questionList[questionsAdded++] = allQuestions[random];
				added[actualIndex] = true;
			}
		}
		delete[] added;
	}


	void printQuiz()
	{
		cout << "====Quiz Information====" << endl;

		cout << "Scheduled On: "; printTime(quizTime);
		cout << endl;
		cout << "Total Marks: " << totalMarks << endl;
		cout << "Time Limit: " << totalTime << endl;
		cout << "No of Questions: " << numQuestions << endl;
		cout << "Questions:" << endl;
		for (int i = 0; i < numQuestions; i++)
		{
			questionList[i]->printDetail();
		}
	}
	int getMarksofEachQ()
	{
		return  totalMarks / numQuestions;
	}
	int getTotalQuestions()
	{
		return numQuestions;
	}

	Question* getSingleQuestion(int i)
	{
		return questionList[i];
	}

	void saveQuizToFile(ofstream& fout)
	{
		fout << "quiz: " << quizID << endl;
		fout << quizTime << endl;
		fout << totalMarks << endl;
		fout << totalTime << endl;
		fout << numQuestions << endl;
		fout << endl;	
		for (int i = 0; i < numQuestions; i++)
		{
			Question* q = questionList[i];
			MCQs* mcq = dynamic_cast<MCQs*>(q);
			TFalse* tFalse = dynamic_cast<TFalse*>(q);
			Subjective* subjective = dynamic_cast<Subjective*>(q);
			int qoptions = 0;
			string id = "";
			if (mcq != nullptr) 
			{
				id = "2efcde9";
				qoptions = 4;
			}
			else if (tFalse != nullptr) {
				id = "b94d27b";
				qoptions = 2;
			}
			else if (subjective != nullptr) {
				id = "88f7ace";
				qoptions = 0;
			}
			fout << id << endl;
			fout << q->getStatement();
			fout << endl;
			string* op = q->getOption();
			for (int x = 0; x < qoptions; x++)
			{
				fout << op[x];
				if(x != qoptions -1 )
					fout << endl;
			}

			fout << endl;
			fout << endl;
			
		}
	}
};

class Course {

private:
	string name;
	string courseId;
	Quiz** allQuizzes;
	Topic** allTopics;
	int noQuizzes;
	int tTopics;

public:



	void getScoreStats(Quiz* selectedQuiz,int& avg,int& tstud) {
		string quizID = selectedQuiz->getQuizID();
		string answerSheetFileName = "AnswerSheet_" + quizID + ".txt";
		ifstream answerSheet(answerSheetFileName);
		if (!answerSheet) {
			cout << "Answer sheet file does not exist." << endl;
			return;
		}
		double score=0;
		double totalScore = 0;
		int numStudents = 0;
		while (!answerSheet.eof()) {
			string name, temp, score_str, correctAns;
			
			getline(answerSheet, name);
			if (name.empty()) {
				continue;
			}
			getline(answerSheet, temp); // read Quiz ID line
			getline(answerSheet, score_str); // read Score line
			getline(answerSheet, correctAns); // read Correct Answers line
			
			string substr2 = score_str.substr( 7);
			score = stod(substr2);

			totalScore += score;
			numStudents++;
		}
		answerSheet.close();
		
		avg = totalScore / numStudents;
		tstud = numStudents;
	}
	string getId()
	{

		return courseId;

	}
	Course()
	{
		allQuizzes = new Quiz * [40];
		allTopics = new Topic * [40];
		tTopics = 0;
		noQuizzes = 0;
	}

	
	Topic* getSpecificTopic(int index)
	{
		return allTopics[index - 1];
	}

	void addQuiz(Quiz* quiz)
	{
		allQuizzes[noQuizzes] = quiz;
		noQuizzes++;
		updateQuizzesInFile();
	}
	int getTotalTopics()
	{
		return tTopics;
	}
	void updateQuizzesInFile()
	{
		ofstream fout;
		fout.open("quizzes.txt", std::ios_base::app);
		fout <<"course: " << courseId << endl;
		for (int i = 0; i < noQuizzes; i++)
		{
			allQuizzes[i]->saveQuizToFile(fout);
		}
		fout.close();
	}

	string loadQuizzesFromFile(ifstream & Input)
	{
		string temp="t";

		int count = 0;
		while (temp.find("course") == -1 && !Input.eof())
		{
			getline(Input, temp);
			if (temp.find("quiz")!=-1)
			{
				Quiz* t = new Quiz();
				temp = t->loadQuestion(Input, temp);
				
				allQuizzes[noQuizzes++] = t;
				

			
			}

		}
		/*for (int i = 0; i < noQuizzes; i++)
		{

			allQuizzes[i]->printQuiz();

		}*/


		return temp;




	}

	void LoadAllTopics(string filename)
	{
		string temp;
		Topic* tempTopic;
		ifstream Input(filename);
		if (Input.is_open())
		{

			getline(Input, temp);
			while (!Input.eof())
			{
				
				if (temp == "a5380ee")
				{
					getline(Input, temp);
					tempTopic = new Topic();
					tempTopic->setName(temp);
					temp = tempTopic->Load(Input);
					allTopics[tTopics++] = tempTopic;
				}
		
			}
		}


	}
	void setName(string n)
	{
		name = n;
	}

	void setCode(string c)
	{
		courseId = c;
	}
	Quiz* getSpecificQuiz(int index)
	{
		return allQuizzes[index - 1];
	}
	void printQuizzesList()
	{
		for (int i = 0; i < noQuizzes; i++)
		{
			cout << i + 1 << ". ";
			cout << "Course: " << name << " Quiz ID: " << allQuizzes[i]->getQuizID() << " Starting Time: ";
			time_t t = allQuizzes[i]->getQuizSchedule();
			printTime(t);
			
		}
	}
	void printCourseNames()
	{
		cout << name << " " << courseId << endl;
	}
	string getName()
	{
		return name;
	}

	void printCourseTopics()
	{
		cout <<"Course: " << name << " " << courseId << endl;
		for (int i = 0; i < tTopics; i++)
		{
			cout<<i+1<<". "<< allTopics[i]->getName()<< " Available Questions: "<< allTopics[i]->getTotalQuestions()<<endl;
		}
	}
	int getTotalQuiz()
	{
		return noQuizzes;
	}

	void setTotalQuiz(int noQuizzes)
	{
		this->noQuizzes = noQuizzes;
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

	void LoadQuizes(Course* allCourse, int count )
	{
		ifstream Input("quizzes.txt");
		if (Input.is_open())
		{

			string temp;
			getline(Input, temp);
			while (!Input.eof()) {
				int position = temp.find("course");
				if (position != -1)
				{
					string courseId = temp.substr(8);
					int couseIndex = 0;
					for (int i = 0; i < count; i++)
					{
						string t = allCourse[i].getId();

						if (t == courseId)
						{
							couseIndex = i;
							break;
						}
					}
					temp=allCourse[couseIndex].loadQuizzesFromFile(Input);


					

				}

			}





		}





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
				string file = "testbank" + to_string(i) +".txt";
				mycourse[i].LoadAllTopics(file);
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
			userCourses[i]->printCourseNames();
		}
		cout << endl;
	}

	void printQuizCourse()
	{
		cout << "Available quizzes:" << endl;
		for (int i = 0; i < totalCourses; i++) 
		{
			userCourses[i]->printQuizzesList();
		}
		cout << endl;
	}
	int getTotalAvailableQuizzes()
	{
		int sum = 0;
		for (int i = 0; i < totalCourses; i++)
		{
			sum += userCourses[i]->getTotalQuiz();
		}
		return sum;
	}

	void printData()
	{
		cout << id << " " << name << " " << password << endl;
		//printCourses();

	};
	virtual void printMenu(string name)
	{
		cout << "----------------------------------" << endl;
		cout << "Hello Dear " << name;
		cout << "What would you like to do today?" << endl;
	}

	virtual ~User() {}
};


class Teacher : public User {

private:
	static int totalTeachers;

public:
	void printCoursesStats()
	{
		int courseNo = 0;
		cout << "Please select the course you would like to select the individual quiz: " << endl;
		printCourses();
		cin >> courseNo;
		while (courseNo > totalCourses || courseNo <= 0)
		{
			cout << "Invalid Input, please try again" << endl;
			cin >> courseNo;
		}
		Course* course = userCourses[courseNo - 1];

		int totalQuiz = course->getTotalQuiz();
		if (totalQuiz <= 0)
		{
			cout << "No Quiz is Available in the following course." << endl;

		}
		else
		{
			int score = 0;
			int totalstud = 0;
			double average = 0;
			for (int i = 0; i < totalQuiz; i++)
			{

				Quiz* selectedQuiz = course->getSpecificQuiz(i+1);
				course->getScoreStats(selectedQuiz,score,totalstud);
				cout << "Total " << totalstud << " attends this quiz"<<endl;
				average = average + score;
			}
			cout << "total average of the whole course quizes is " << average / totalQuiz;



		}

	}
	void printOneQuiz()
	{
		
		int courseNo = 0;
		cout << "Please select the course you would like to select the individual quiz: " << endl;
		printCourses();
		cin >> courseNo;
		while (courseNo > totalCourses || courseNo <= 0)
		{
			cout << "Invalid Input, please try again" << endl;
			cin >> courseNo;
		}
		Course* course = userCourses[courseNo - 1];


		int totalQuiz = course->getTotalQuiz();
		if (totalQuiz <= 0)
		{
			cout << "No Quiz is Available in the following course."<<endl;
			
		}
		else
		{
			int quizNo = 0;
			cout << "Available Quizzes: " << endl;
			course->printQuizzesList();
			cout << "Enter the no of the quiz you want to select: ";
			cin >> quizNo;

			while (quizNo > totalQuiz || quizNo <= 0)
			{
				cout << "Invalid Input, please try again" << endl;
				cin >> quizNo;
			}
			int avg = 0, tstud = 0;
			Quiz* selectedQuiz = course->getSpecificQuiz(quizNo);
			course->getScoreStats(selectedQuiz,avg,tstud);
			cout << "Quiz ID: " << selectedQuiz->getQuizID() << endl;
			cout << "Number of students: " << tstud << endl;
			cout << "average score: " << avg << endl;
		}

	}
	void makeQuiz()
	{
		int courseNo = 0;
		cout << "Please select the course you would like to make the quiz for: " << endl;
		printCourses();

		cin >> courseNo;
		while (courseNo > totalCourses || courseNo <= 0)
		{
			cout << "Invalid Input, please try again" << endl;
			cin >> courseNo;
		}
		Course* course = userCourses[courseNo - 1];
		cout << "---------------------------------------" << endl;
		cout << "This Course has the following topics:" << endl;
		course->printCourseTopics();
		cout << "---------------------------------------" << endl;
		cout << "Please enter how many topics you want to choose: " << endl;
		int n = 0;
		int totalTopics = course->getTotalTopics();
		cin >> n;
		while (n > totalTopics || n <= 0)
		{
			cout << "Invalid Input, please try again" << endl;
			cin >> n;
		}

		cout << "Please select the topic numbers you want to include in quiz: " << endl;
		int* topics = new int[n];

		for (int i = 0; i < n; i++)
			topics[i] = -1;

		for (int i = 0; i < n; i++)
		{
			int c = 0;
			cin >> c;

			while (c > totalTopics || c <= 0)
			{
				cout << "Invalid Topic Number Entered!, Try again!" << endl;
				cin >> c;
			}

			// Check if the topic has already been selected
			for (int j = 0; j < i; j++)
			{
				if (topics[j] == c)
				{
					cout << "You have already selected topic number " << c << ". Please select a different topic." << endl;
					cin >> c;

					// Restart the loop with the new topic input
					j = -1;
				}
			}

			topics[i] = c;
		}

		selectionSort(topics, n);
		Topic** selectedTopics = new Topic*[n];
		int availableQuestions = 0;

		for (int i = 0; i < n; i++)
		{
			selectedTopics[i] = course->getSpecificTopic(topics[i]);
			availableQuestions += selectedTopics[i]->getTotalQuestions();
		}
	
		int totalQ = 0;
		cout << "Please enter total no of questions in the quiz" << endl;
		cin >> totalQ;

		while (totalQ > availableQuestions || totalQ <= 0)
		{
			cout << "Invalid Input, please try again" << endl;
			cin >> totalQ;
		}
		
		int marks = 0;
		cout << "Please enter marks of each question" << endl;
		cin >> marks;
		while (marks <= 0)
		{
			cout << "Invalid Input, please try again" << endl;
			cin >> marks;
		}
		
		struct tm quizTime = {};
		time_t currentTime;
		time(&currentTime);
		time_t quizTime_t = time(NULL);
		do {
			cout << "Please enter the date and time for the quiz (in format YYYY MM DD HH MM): ";
			cin >> quizTime.tm_year >> quizTime.tm_mon >> quizTime.tm_mday >> quizTime.tm_hour >> quizTime.tm_min;
			quizTime.tm_year -= 1900;
			quizTime.tm_mon -= 1;
			time_t quizTime_t = mktime(&quizTime);
			
			// Check if the quiz time is set in the future
			if (quizTime_t <= currentTime) {
				cout << "Invalid quiz time! Please enter a time in the future." << endl;
			}
			else {
				// Print the quiz time to confirm
			
			cout << "The quiz time is set as: ";
			printTime(quizTime_t); cout<< endl;
				break;
			}
		} while (true);

		cout << "Please enter the maximum time allowed for the quiz (in minutes): ";
		int maxTime;
		cin >> maxTime;
		while (maxTime <= 0) {
			cout << "Invalid input. Please enter a positive integer: ";
			cin >> maxTime;
		}

		Quiz* newQuiz = new Quiz();
		newQuiz->generateQuiz(selectedTopics, n, marks, totalQ, quizTime_t, maxTime);

		userCourses[courseNo - 1]->addQuiz(newQuiz);
		newQuiz->printQuiz();
	}

	void printMenu(string name)
	{
		User::printMenu(name);
		cout << "1. Make A Quiz" << endl;
		cout << "2. Show Individual Quiz stats" << endl;
		cout << "3. Print Whole Course Quiz stats" << endl;
	}
};

class Student : public User {
private:
	static int totalStudents;

public:
	void printMenu(string name)
	{
		User::printMenu(name);
		cout << "1. Give Quiz" << endl;
	}

	void saveScoreToFile(double score, int* correctAnswers, Quiz* selectedQuiz)
	{
		string quizID = selectedQuiz->getQuizID();
		string fileName = "AnswerSheet_" + quizID + ".txt";
		ofstream fout(fileName, ios::app);
		if (!fout.is_open())
		{
			cout << "Failed to open file!" << endl;
			return;
		}
		fout << "Student Name: " << name << endl;
		fout << "Quiz ID: " << quizID << endl;
		fout << "Score: " << score << endl;
		fout << "Correct Answers: ";
		int totalQuestions = selectedQuiz->getTotalQuestions();
		for (int i = 0; i < totalQuestions; i++)
		{
			fout << correctAnswers[i] << " ";
		}
		fout << endl;
		fout.close();
		cout << "Score saved to file: " << fileName << endl;
	}

	bool checkAnswer(Question* question, int selected_option)
	{
		int correctOption = question->getCorrectOption();

		if (correctOption == selected_option - 1)
		{
			return true;
		}
	}

	double startQuiz(Quiz* selectedQuiz)
	{
		double score = 0;
		int totalQuestions = selectedQuiz->getTotalQuestions();
		int marks = selectedQuiz->getMarksofEachQ();
		int* correctAnswers = new int[totalQuestions];
		cout << marks<<endl;
		for (int i = 0; i < totalQuestions; i++)
		{
			int ans = 0;
			string ans_subj = "";

			Question* question = selectedQuiz->getSingleQuestion(i);
			question->printQuestionSt();
			int temp = question->getCorrectOption();
			cout<<temp+1<< endl;
			if (MCQs* mcq = dynamic_cast<MCQs*>(question))
			{

				cin >> ans;
				while (ans > 4 || ans <= 0)
				{
					cout << "Invalid Input, please try again" << endl;
					cin >> ans;
				}
				if (checkAnswer(mcq, ans))
				{
					score += marks;
					correctAnswers[i] = 1;
				}
				else {
					correctAnswers[i] = 0;
				}
			}
			else if (TFalse* truefalse = dynamic_cast<TFalse*>(question))
			{
				cin >> ans;
				while (ans > 2 || ans <= 0)
				{
					cout << "Invalid Input, please try again" << endl;
					cin >> ans;
				}
				if (checkAnswer(truefalse, ans))
				{
					correctAnswers[i] = 1;
					score += marks;
				}
				else {
					correctAnswers[i] = 0;

				}
			}
			else
			{
				cin >> ans_subj;
				int wordCount = 0;
				for (int i = 0; i < ans_subj.length(); i++) {
					if (ans_subj[i] == ' ') {
						wordCount++;
					}
				}
				wordCount++; 
				score += wordCount * 0.01;
				temp = score;
				correctAnswers[i] = score;
			}
			
			
		}
		saveScoreToFile(score, correctAnswers, selectedQuiz);
		return score;
	}
	void readAnswerSheet(Quiz* selectedQuiz) {
		string quizID = selectedQuiz->getQuizID();
		string answerSheetFileName = "AnswerSheet_" + quizID + ".txt";
		ifstream answerSheet(answerSheetFileName);
		if (!answerSheet) {
			
			return;
		}
		cout << "Quiz ID: " << quizID << endl;
		cout << "Student Name\tScore" << endl;
		while (!answerSheet.eof()) {
			string name, temp, score_str, correctAns;
			double score;
			getline(answerSheet, name);
			getline(answerSheet, temp); // read Quiz ID line
			getline(answerSheet, score_str); // read Score line
			getline(answerSheet, correctAns); // read Correct Answers line
			
				
			cout << name << "\t" << score_str << endl;
			
		}
		answerSheet.close();
	}

	void giveQuiz()
	{
		selectCourse: int courseNo = 0;
		printCourses();
		cout << "Enter the no of the course you want to take a quiz in: ";
		cin >> courseNo;

		while (courseNo > totalCourses || courseNo <= 0)
		{
			cout << "Invalid Input, please try again" << endl;
			cin >> courseNo;
		}
		Course* course = userCourses[courseNo - 1];
		
		int totalQuiz = course->getTotalQuiz();
		if (totalQuiz <= 0)
		{
			cout << "No Quiz is Available in the following course. please select another"<<endl<<endl;
			goto selectCourse;
		}
		else
		{
			int quizNo = 0;
			cout << "Available Quizzes: " << endl;
			course->printQuizzesList();
			cout << "Enter the no of the quiz you want to give: ";
			cin >> quizNo;

			while (quizNo > totalQuiz || quizNo <= 0)
			{
				cout << "Invalid Input, please try again" << endl;
				cin >> quizNo;
			}

			Quiz* selectedQuiz = course->getSpecificQuiz(quizNo);

			time_t quizScheduledTime = selectedQuiz->getQuizSchedule();
			time_t currentTime;
			time(&currentTime);
			time_t now = time(0);
			int quizTime = selectedQuiz->getTotalTime();

			time_t quizEndTime = quizScheduledTime + quizTime * 60;
				
			time_t unixQuizTime = time(nullptr) + (quizTime * 60);

			printTime(difftime(quizScheduledTime, currentTime));
			cout << endl;
			printTime(unixQuizTime);
			if (now >= quizScheduledTime && now <= quizEndTime)
			{
				
				double score = startQuiz(selectedQuiz);
				cout << score;
				
			}
			else {
				cout << "Quiz is expired";
				cout << endl;
				readAnswerSheet(selectedQuiz);
				
			}
		}
	}


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
		coursesList = NULL;
		currentUser = NULL;
	}

	void loadData(string teacher_fileName, string student_file)
	{
		AllCourses Temp;
		this->coursesList = Temp.LoadCourse(student_file);
		int totalC = Temp.getTotalCourses();
		Temp.LoadQuizes(coursesList, totalC);


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
				teacher->printMenu(currentUser->getName());
				cin >> n;
				if (n == 1)
				{
					teacher->makeQuiz();
				}
				if (n == 2)
				{
					teacher->printOneQuiz();


				}
				if (n == 3)
				{
					teacher->printCoursesStats();


				}
			}
			else if (Student* student = dynamic_cast<Student*>(currentUser)) {
				int n = 0;
				student->printMenu(currentUser->getName());
				cin >> n;

				if (n == 1)
				{
					student->giveQuiz();
				}
			}
		}
		else
		{
			cout << "invalid pass entered";
		}
	}
};


int main() {

	srand(time(NULL));
	System s;
	s.loadData("teachers_list.csv", "courses_offering_list.csv");
	s.generateLogins();
	s.login();
	/*Course Temp; 
	Temp.LoadAllTopics("testbank10.txt");
	Temp.printInfo();*/
	/*QuestionBank myquestions;
	myquestions.MakeBank("testbank.txt");*/

	system("pause");
	return 0;
}