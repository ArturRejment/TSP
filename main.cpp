#include<iostream>
#include<conio.h>
#include<string>
#include"Algorithm/bruteForce.cpp"
#include"Timer/timer.cpp"

using namespace std;

int main()
{
	Graph *graph = new Graph();
	graph->createMatrix("instances/m12.atsp");

	float time = 0;
	Timer timer;
	auto answer = brute_force(*graph);
	time += timer.getTime().count() * 1.0f;

	string path = "";
	vector<int>::iterator it = answer.begin();

	while (it != answer.end())
	{
		path += to_string(*it);
		path += " ";
		it++;
	}

	cout << "Path: " << path << endl;
	cout << "Time: " << time << endl;

	char choice;
	choice = getch();
	return 0;
}