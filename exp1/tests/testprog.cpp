/*
 * Author: MHY-Silence
 * Date: 2019-12-1
 * Content: Test program of experiment 1
 */ 
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
const char sufname[] = "_report.txt";

using namespace std;

const int testNum = 67;
const int moduleNum = 17;

const char name[20][moduleNum] = {"input&print", "copy", "add",
								  "minus", "multiply", "evaluate",
								  "destroy", "clear", "differential",
								  "infi integral", "defi integral",
								  "GCD", "LCM", "division", "mod",
								  "power"};
const int bound[moduleNum] = {0, 6, 9, 15, 19, 23, 30, 33, 35, 38, 41, 45, 48, 52, 58, 62, testNum};
const double value[testNum] = {
	1, 3, 2, 1, 2, 1,			  //create
	2.5, 3, 2.5,				  //copy
	1, 1, 1, 1, 1, 1,			  //add
	1, 2, 2, 1,					  //minus
	5, 5, 5, 5,					  //multiply
	1, 1, 2, 1, 1, 1, 1,		  //evaluate
	2, 2, 1,					  //destroy
	2, 3,						  //clear
	2, 2, 1,					  //differential
	2, 2, 1,					  //ind integral
	2, 2, 1, 1,					  //def integral
	1, 0.5, 0.5,				  //GCD
	1, 1, 0.5, 0.5,				  //LCM
	0.5, 0.5, 0.5, 0.5, 0.5, 0.5, //divide
	0.5, 0.5, 0.5, 0.5,			  //mod
	1, 1.5, 1.5, 0.5, 0.5		  //power
};

double PrintReportLine(ostream &output, int testNo, bool isCorrect)
{
	int linelen = 30;
	for (int pos = 0; pos < moduleNum; pos++)
		if (testNo >= bound[pos] && testNo < bound[pos + 1])
		{
			output << name[pos] << testNo - bound[pos];
			linelen -= strlen(name[pos]);
			break;
		}

	for (int i = 0; i < linelen; i++)
		output << "-";
	output << value[testNo] << "pts--";

	if (isCorrect)
	{
		output << "OK!" << endl;
		return value[testNo];
	}
	else
	{
		output << "FAIL!" << endl;
		return 0;
	}
}

string GetStuNo(string stuName)
{
	int i;
	for (i = 0; stuName[i] != 'P' && stuName[i] != 'p'; i++);
	return string(stuName, i, 10);
}

int main()
{
	system("dir .\\targets\\*.exe /b > files.txt");

	ifstream getName("files.txt");
	ofstream scoreForm("scoreform.txt");

	for (string path; getName >> path; system("del polyn.out"))
	{
		string stuNo = GetStuNo(path);
		string progPath = "targets\\" + path + " >nul";
		string reportPath = "reports\\" + stuNo + "_report.txt";

		float score = 1;
		ifstream stdAns("polynstd.out");
		ofstream stuReport(reportPath);

		system("dir .\\tests\\*.in /b /on > .\\tests\\tests.txt");
		ifstream getTests(".\\tests\\tests.txt");

		for (int i = 0; i < testNum; i++)
		{
			//copy test file to polyn.in
			string testPath;
			getTests >> testPath;
			string copyCommand = "copy .\\tests\\" + testPath + " polyn.in";
			system(copyCommand.c_str());

			//run the program
			cout << "running " << path << " with test file: " << testPath << endl;
			system(progPath.c_str());

			//read polyn.out
			ifstream stuAns("polyn.out");
			char stuline[1000], stdline[1000];
			memset(stuline, 0, sizeof(char));
			if (stuAns.peek() != EOF)
				stuAns.getline(stuline, 1000);
			stdAns.getline(stdline, 1000);

			score += PrintReportLine(stuReport, i, !strcmp(stuline, stdline));

			stuAns.close();
			system("del polyn.out");
			system("del polyn.in");
		}

		stuReport << "total score: " << score << endl;
		scoreForm << stuNo << " score: " << score << endl;

		stdAns.close();
		stuReport.close();
	}
	getName.close();
	system("del files.txt");
	return 0;
}