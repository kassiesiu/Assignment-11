// Kassie Wong
// Assignment 11
// Section 1001

#include "socialNetwork.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

socialNetwork::socialNetwork() {
    vertexCount = edgeCount = dia = trianglesCnt = singles = countOfHighestDegree = countOfLowestDegree = unconnected = 0;
    highestDegree = lowestDegree = -1;
    adjList = NULL;
}
socialNetwork::~socialNetwork() {
    
}
bool socialNetwork::readGraph(string fileName) { // read a formatted graph file
    ifstream in;
    in.open(fileName);
    
    if (!in.is_open())
        return false;
    
    getline(in, title);
    in >> vertexCount;
    in >> edgeCount;
    edgeCount = 0;
    
    createGraph();
    
    
    int v1, v2, weight;
    v1 = v2 = weight = 0;
    
    while (in >> v1) {
        in >> v2;
        in >> weight;
        
        addEdge(v1, v2, weight);
        addEdge (v2, v1, weight);
    }
    
    edgeCount /= 2; // because undirected graph
    
    return true;
}
void socialNetwork::createGraph() {
    
    // initializes array and sets all the pointers to NULL
    adjList = new edgeStruct*[vertexCount];
    for (int i = 0; i < vertexCount; i++)
        adjList[i] = NULL;
    
}

void socialNetwork::addEdge(int src, int dest, int weightVal) {
    edgeStruct *temp = new edgeStruct;
    temp->v2 = dest;
    temp->weight = weightVal;
    temp->next = NULL;
    
    edgeStruct *curr = adjList[src];
    
    if (adjList[src] == NULL) { // if this is the first edge
        adjList[src] = temp;
    } else {
        while (curr->next != NULL) {
            if (curr->next == NULL)
                break;
            
            curr = curr->next;
        }
        curr->next = temp;
    }
    
    edgeCount++;
}
void socialNetwork::findConnectedComponents() { // find size of the largest connected component
}
void socialNetwork::degreeStats() { // find the vertices's degree statistics
    
    int currDegree = 0;
    int sum = 0;
    
    for (int i = 0; i < vertexCount; i++) {
        
        // checks for singles
        if (adjList[i] != NULL) {
            if (adjList[i]->next == NULL)
                singles++;
        } else {
            unconnected++;
            continue;
        }
            
        
        for (edgeStruct *curr = adjList[i]; curr != NULL; curr = curr->next) { // traverses through adjacent nodes
            
            currDegree++;
            
        }
    
        // after done traversing through adjacent nodes
        
        if (highestDegree == currDegree)
            countOfHighestDegree++;
        
        if (lowestDegree == currDegree)
            countOfLowestDegree++;
        
        if (highestDegree == -1 && lowestDegree == -1) { // if first time
            highestDegree = lowestDegree = currDegree;
            countOfHighestDegree = 1;
            countOfLowestDegree = 1;
        }
        else if (currDegree > highestDegree) {
            highestDegree = currDegree;
            countOfHighestDegree = 1;
        } else if (currDegree < lowestDegree) {
            lowestDegree = currDegree;
            countOfLowestDegree = 1;
        }
        
        sum += currDegree;
        currDegree = 0;
    }
    
    avgDegree = double(sum)/vertexCount;
    
}
void socialNetwork::diameter() { // find the graph diameter
    
}
void socialNetwork::influencers() { // find the top n influencer's based on eigenvector centrality
}
void socialNetwork::triangles() { // find the count of triangles for the graph.
    
//    // find combination of every two nodes
//    // go through every vertex
//    for (int i = 0; i < vertexCount; i++) {
//        for (edgeStruct *srcCurr = adjList[adjList[i]->v2]; srcCurr != NULL; srcCurr = srcCurr->next) {
//
//
//            if (srcCurr->v2 == i) { // if the pair is two nodes that point to e/o
//                continue;
//            }
//
//            for (edgeStruct *destCurr = adjList[srcCurr->v2]; destCurr != NULL; destCurr = destCurr->next) {
//
//                if (destCurr->v2 == i) {
//                    trianglesCnt++;
//                    break;
//                }
//
//            }
//        }
//    }
//
//    trianglesCnt = trianglesCnt / 3;
}
void socialNetwork::printGraph() { // print the formatted graph. Optional, used only for debugging.
    
    for (int i = 0; i < vertexCount; i++) {
        edgeStruct *curr = adjList[i];
        while (curr != NULL) {
            cout << i << " " << curr->v2 << " " << curr->weight << endl;
            curr = curr->next;
        }
    }
    
}
void socialNetwork::graphInformation() {
    cout << "Graph title: " << title << endl;
    cout << "Vertex Count: " << vertexCount << endl;;
    cout << "Edge Count: " << edgeCount << endl;;
    cout << "Edges/Nodes Ratio: " << fixed << setprecision(6) << double(edgeCount)/vertexCount << endl;
    cout << "Graph Density: " << double(2*edgeCount)/(vertexCount * (vertexCount - 1)) << endl;
    
    cout << endl;
    
    cout << "Highest Degree: " << highestDegree << endl;
    cout << "Lowest Degree: " << lowestDegree << endl;
    cout << "Count of Singles: " << singles << endl;
    cout << "Count of Highest Degree: " << countOfHighestDegree << endl;
    cout << "Count of Lowest Degree: " << countOfLowestDegree << endl;
    cout << "Average Degree: " << avgDegree << endl;
    
    cout << endl;
    
    cout << "The largest connected component contains " << "nodes." << endl;
    cout << "There are " << unconnected << " unconnected nodes" << endl;
    
    cout << endl;
    
    cout << "Triangles: " << trianglesCnt << endl;
    
    cout << endl;
    
    cout << "Top 5 influencer's:" << endl;
    
    cout << endl;
    
}
