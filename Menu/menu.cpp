#include<iostream>
#include<vector>
#include"../Graph/graph.cpp"
#include"../Timer/timer.cpp"
#include"../Algorithm/bruteForce.cpp"

using namespace std;

Graph *graph = new Graph()


void performBruteForce()
{
	float time = 0;
	Timer timer;
	auto answer = bruteForce(*graph);
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
	cout << "Time: " << time << endl;
	return;
}

void menu()
{
	system("cls");
	do
	{
		cout << "[1] Load graph from file\n";
		cout << "[2] Brute Force Algorithm\n";
		cout << "[3] Held-Karp Algorithm\n";
		cout << "[4] Exit\n";

		char choice = getch();

		switch(choice)
		{
		case '1':
			string name = "";
			cout << "Enter filename: " << flush;
			cin >> name;
			graph->createMatrix("instances/" + name)
			break;
		case '2':
			performBruteForce();
			break;
		case '3':
			break;
		case '4':
			return;
			break;
		}

	} while (True);
}