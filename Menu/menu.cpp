#include<iostream>
#include<vector>
#include"../Graph/graph.cpp"
#include"../Timer/timer.cpp"
#include"../Algorithm/bruteForce.cpp"
#include"../Algorithm/heldKarp.cpp"
#include"../Algorithm/simulatedAnnealing.cpp"
#include "../Algorithm/geneticAlgorithm.cpp"

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
	cout << "Optimal path weight: " << graph->getOptimumPath() << endl;
	cout << "Time: " << time << " s\n\n";
	return;
}

void performHeldKarp()
{
	float time = 0;
	Timer timer;
	int answer = heldKarp(graph);
	time += timer.getTime().count() * 1.0f;

	cout << "Answer: " << answer << endl;
	cout << "Expected answer: " << graph->getOptimumPath() << endl;
	cout << "Time: " << time << " s\n\n";
	return;
}

void performSimmulatedAnnealing()
{
	float time = 0;
	pair<vector<int>, int> answer;

	Timer timer;
	answer = simmulatedAnnealing(graph);
	time += timer.getTime().count() * 1.0f;

	double prd = double(100 * (answer.second - graph->getOptimumPath())) / graph->getOptimumPath();

	cout << "Weight: " << answer.second << endl;
	cout << "Optimum Weight: " << graph->getOptimumPath() << endl;
	cout << fixed << setprecision(4) << "Mistake: " << prd << "%" << endl;
	cout << "Path: ";
	for (int i = 0; i < answer.first.size() - 1; i++)
		cout << answer.first[i] << " " << flush;
	cout << "Time: " << time << endl;
}

void performGeneticAlgorithm()
{
    float time = 0;
    pair<vector<int>, int> answer;

    Timer timer;
    answer = geneticAlgorithm(graph);
    time += timer.getTime().count() * 1.0f;

    double prd = double (100 * (answer.second - graph->getOptimumPath())) / graph->getOptimumPath();

    cout << "Weight: " << answer.second << endl;
    cout << "Optimum Weight: " << graph->getOptimumPath() << endl;
    cout << fixed << setprecision(4) << "Mistake: " << prd << "%" << endl;
    cout << "Path: ";
    for(int i = 0; i < answer.first.size() - 1; i++)
        cout << answer.first[i] << " " << flush;
    cout << "\nTime: " << time << endl;
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
		cout << "[5] Simmulated Annealing\n";
		cout << "[6] Genetic Algorithm\n";
		cout << "[9] Exit\n";

		char choice = getch();

		string name = "";
		switch(choice)
		{
		case '1':
			cout << "Enter filename: " << flush;
			cin >> name;
			graph->createMatrix("instances/" + name);
			break;
		case '2':
			system("cls");
			graph->printMatrix();
			break;
		case '3':
			system("cls");
			performBruteForce();
			cout << "Press any key to continue...\n";
			choice = getch();
			return;
			break;
		case '4':
			system("cls");
			performHeldKarp();
			cout << "Press any key to continue...\n";
			choice = getch();
			return;
			break;
		case '5':
			system("cls");
			performSimmulatedAnnealing();
			cout << "Press any key to continue...\n";
			choice = getch();
			return;
			break;
        case '6':
            system("cls");
            performGeneticAlgorithm();
            cout << "Press any key to continue...\n";
            return;
            break;
		case '9':
			return;
			break;
		}


	} while (true);
}