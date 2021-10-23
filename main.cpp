#include<iostream>
#include<conio.h>
#include"Graph/graph.cpp"

using namespace std;

int main()
{
	Graph *graph = new Graph();
	graph->createMatrix("./m11.txt");
	graph->printMatrix();

	char choice;
	choice = getch();
	return 0;
}