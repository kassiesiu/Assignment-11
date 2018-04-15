// Kassie Wong
// Assignment 11
// Section 1001

//  CS 302 - Assignment #11
//  Social Network Analysis

#include <iostream>
#include <thread>
#include <unistd.h>

#include "socialNetwork.h"

using namespace std;

int main(int argc, char *argv[])
{

// *****************************************************************
//  Headers...

	string	stars, bars, dashes;
	string	fName;
	stars.append(65, '*');
	bars.append(65, '=');
	dashes.append(40,'-');
	const char* bold   = "\033[1m";
	const char* unbold   = "\033[0m";

	cout << stars << endl << bold << "CS 302 - Assignment #11" << endl;
	cout << "Social Network Analysis (SNA) Project" << unbold << endl;
	cout << endl;

// ------------------------------------------------------------------
//  Check argument

    if (argc == 1) {
        cout << "usage: <dataFileName>" << endl;
        return 0;
    }

    if (argc != 2) {
        cout << "main: Error, invalid command line arguments." << endl;
        return 0;
    }

    if (access(argv[1], F_OK) == -1) {
        cout << "main: Error, data file does not exist." << endl;
        return    0;
    }

    fName = string(argv[1]);

// ------------------------------------------------------------------
//  Find social network statistics.
//  Make thread calls to each function so they operate in parallel.

    socialNetwork    myGraph;
    int    topCount = 5;

    if (myGraph.readGraph(fName)) {
        
//        myGraph.printGraph();

        thread t1(&socialNetwork::diameter, &myGraph);
        thread t2(&socialNetwork::findConnectedComponents, &myGraph);
//        thread t3(&socialNetwork::influencers, &myGraph, topCount);
        thread t4(&socialNetwork::triangles, &myGraph);
        thread t5(&socialNetwork::degreeStats, &myGraph);

        t1.join();
        t2.join();
//        t3.join();
        t4.join();
        t5.join();

        myGraph.graphInformation();
    }

// *****************************************************************
//  All done.

	cout << stars << endl;
	cout << "Complete." << endl;

	return 0;
}

