#include<iostream>
#include<vector>
#include"../Graph/graph.cpp"
#include"../Timer/timer.cpp"
#include"../Algorithm/bruteForce.cpp"
#include"../Algorithm/heldKarp.cpp"

using namespace std;

Graph *graph = new Graph();

void performBruteForce()
{
	float time = 0;
	Timer timer;
	auto answer = brute_force(*graph);
	time += timer.getTime().count() * 1.0f;

	string path = "";
	vector<int>::iterator it = answer.begin();

	while(it != answer.end())
	{
		path += to_string(*it);
		path += " ";
		it++;
	}

	cout << "Path: " << path << endl;
	cout << "Time: " << time << " s" << endl;
	return;
}

void performHeldKarp()
{
	float time = 0;
	Timer timer;
	int answer = heldKarp(graph);
	time += timer.getTime().count() * 1.0f;

	cout << "Answer: " << answer << endl;
	cout << "Time: " << time << " s" << endl;
	return;
}

void menu()
{
	system("cls");
	do
	{
		cout << "[1] Load graph from file\n";
		cout << "[2] Print graph\n";
		cout << "[3] Brute Force Algorithm\n";
		cout << "[4] Held-Karp Algorithm\n";
		cout << "[5] Exit\n";

		char choice = getch();

		string name = "";
		switch(choice)
		{
		case '1':
			cout << "Enter filename: " << flush;
			cin >> name;
			graph->createMatrix("instances/" + name);
			graph->printMatrix();
			break;
		case '2':
			system("cls");
			graph->printMatrix();
			break;
		case '3':
			system("cls");
			performBruteForce();
			break;
		case '4':
			system("cls");
			performHeldKarp();
			break;
		case '5':
			return;
			break;
		}

	} while (true);
}