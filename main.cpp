#include<iostream>
#include<conio.h>
#include<string>
#include"Algorithm/bruteForce.cpp"

using namespace std;

int main()
{
	Graph *graph = new Graph();
	graph->createMatrix("instances/m12.atsp");

	auto answer = brute_force(*graph);
	string path = "";
	vector<int>::iterator it = answer.begin();

	while (it != answer.end())
	{
		path += to_string(*it);
		path += " ";
		it++;
	}

	cout << path;

	char choice;
	choice = getch();
	return 0;
}