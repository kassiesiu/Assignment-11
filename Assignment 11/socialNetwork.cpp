// Kassie Wong
// Assignment 11
// Section 1001

#include "socialNetwork.h"
#include "priorityQueue.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

socialNetwork::socialNetwork() {
    vertexCount = edgeCount = dia = trianglesCnt = singles = countOfHighestDegree = countOfLowestDegree = unconnected = largestConnected = top = 0;
    highestDegree = lowestDegree = -1;
    adjList = NULL;
    influencersArr = NULL;
}
socialNetwork::~socialNetwork() {
     if (adjList != NULL) {
         for (int i = 0; i < vertexCount; i++) {
             // edgeStruct *head = adjList[i];
             // if (adjList[i] != NULL) {
             //     edgeStruct *next = adjList[i]->next->next;
             //     delete head->next;
             //     head->next = next;
             // }
             for (edgeStruct *nextStruct = adjList[i]; nextStruct != NULL; nextStruct = nextStruct) {
                 if (nextStruct->next != NULL)
                     adjList[i] = nextStruct->next;
                 else
                     adjList[i] = NULL;
    
                 delete nextStruct;
    
                 if (adjList[i] == NULL)
                     nextStruct = NULL;
                 else
                     nextStruct = adjList[i];
             }
    
         }
     }
    
    // delete []influencersArr;
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
    for (int i = 0; i < vertexCount; i++) {
        adjList[i] = NULL;
    }
    
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
    
    //    bool visit[vertexCount];
    bool *visit = new bool[vertexCount];
    
    for (int i = 0; i < vertexCount; i++)
        visit[i] = false;
    
    int count = 0;
    
    for (int i = 0; i < vertexCount; i++) {
        if (visit[i] == false) {
            DFS(i, visit, count);
            if (count > largestConnected)
                largestConnected = count;
            //            cout << "Count: " << count << endl << endl;
            count = 0;
        }
    }
    
    delete []visit;
}

void socialNetwork::DFS(int v, bool visit[], int &count) {
    visit[v] = true;
    count++;
    
    //    cout << v << endl;
    
    //    for (int i = 0; i < vertexCount; i++)
    //        if (visit[adjList[i]->v2] == false)
    //            DFS(adjList[i]->v2, visit, count);
    
    for (edgeStruct *curr = adjList[v]; curr != NULL; curr = curr->next)
        if (visit[curr->v2] == false)
            DFS(curr->v2, visit, count);
    
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
        }
        
        
        for (edgeStruct *curr = adjList[i]; curr != NULL; curr = curr->next) { // traverses through adjacent nodes
            
            currDegree++;
            
        }
        
        // after done traversing through adjacent nodes
        
        //        degrees[i] = currDegree; // for triangle use
        
        if (highestDegree == currDegree)
            countOfHighestDegree++;
        
        if (lowestDegree == currDegree)
            countOfLowestDegree++;
        
        if (highestDegree == -1 && lowestDegree == -1) { // if first time
            highestDegree = lowestDegree = currDegree;
            countOfHighestDegree = 1;
            countOfLowestDegree = 1;
        } else if (currDegree > highestDegree) {
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
    //bool *visit = new bool[vertexCount];
    bool visit[vertexCount];
    int trueCounter = 0;
    
    // int **shortestPaths = new int*[vertexCount]; /// make a 2d array
    // for (int i = 0; i < vertexCount; i++)
    //     shortestPaths[i] = new int[vertexCount];
    
    int *shortestPaths = new int[vertexCount];
    
    // initialize to -1
    
    // initialize empty myQueue
    priorityQueue<int> myQueue(MIN, vertexCount); // initialize empty myQueue
    
    
    // for each source vertex s
    for (int s = 0; s < vertexCount; s++) {
        trueCounter = 0;
        
        // cout << s << endl;
        
        // initialize visited to false
        for (int v = 0; v < vertexCount; v++) {
            shortestPaths[v] = -1;
            visit[v] = false;
        }
        
        
        visit[s] = true;
        myQueue.insert(s, s);
        shortestPaths[s] = 0;
        
        //        while (!myQueue.isEmpty()) {
        //            int v = 0;
        //            myQueue.deleteMin(v, v);
        //
        //            // for each w adjacent to v
        //            for (edgeStruct *w = adjList[v]; w != NULL; w = w->next) {
        //                if (trueCounter == vertexCount)
        //                    break;
        //
        //                if (visit[w->v2] == false) {
        //                    visit[w->v2] = true;
        //                    trueCounter++;
        //                    shortestPaths[s][w->v2] = shortestPaths[s][v] + 1;
        //                    myQueue.insert(w->v2, w->v2);
        //                }
        //
        //            }
        //        }
        
        while (!myQueue.isEmpty()) {
            int v = 0;
            myQueue.deleteMin(v, v);
            
            // for each w adjacent to v
            for (edgeStruct *w = adjList[v]; w != NULL; w = w->next) {
                if (trueCounter == vertexCount)
                    break;
                
                if (visit[w->v2] == false) {
                    visit[w->v2] = true;
                    trueCounter++;
                    shortestPaths[w->v2] = shortestPaths[v] + 1;
                    myQueue.insert(w->v2, shortestPaths[w->v2]);
                    if (shortestPaths[w->v2] > dia)
                        dia = shortestPaths[w->v2];
                }
                
            }
        }
        
    }
    
    
    
    
    // for (int i = 0; i < vertexCount; i++) {
    //     for (int j = 0; j < vertexCount; j++) {
    //         if (shortestPaths[i][j] > dia)
    //             dia = shortestPaths[i][j];
    //     }
    //  }
    
    
    //    cout << "     ";
    //    for (int i = 0; i < vertexCount; i++) { // print horizontal axis
    //            cout << setw(4) << right << i;
    //    }
    //    cout << endl;
    //
    //    for (int rows = 0; rows < vertexCount; rows++) {
    //        cout << setw(3) << right << rows << "| ";
    //        for (int column = 0; column < vertexCount; column++) {
    //            if (rows == column)
    //                cout << setw(4) << right << "0";
    //            else if (shortestPaths[rows][column] == 0)
    //                cout << setw(4) << right << "--";
    //            else
    //                cout << setw(4) << right << shortestPaths[rows][column];
    //        }
    //        cout << " " << endl;
    //    }
    
    delete []shortestPaths;
    
    
}
void socialNetwork::influencers(int topCount) { // find the top n influencer's based on eigenvector centrality
    
    top = topCount;
    
    //    create v[|V|] and initialize all to 1
    //    create w[|V|]
    unsigned long long v[vertexCount];
    unsigned long long w[vertexCount];
    //    int *v = new int[vertexCount];
    //    int *w = new int[vertexCount];
    
    for (int i = 0; i < vertexCount; i++)
        v[i] = 1;
    
    //    Repeat 100 times
    for (int j = 0; j < 10; j++) {
        //    initialize all w[|V| to 0
        for (int i = 0; i < vertexCount; i++)
            w[i] = 0;
        
        // for every vertex i, in graph, G=(V,E)
        for (int i = 0; i < vertexCount; i++) {
            // for every adjacent u of i
            for (edgeStruct *adjOfI = adjList[i]; adjOfI != NULL; adjOfI = adjOfI->next) {
                //                     w[u] += v[i]
                w[adjOfI->v2] += v[i];
            }
        }
        
        
        //                     set v[] = w[]
        for (int i = 0; i < vertexCount; i++)
            v[i] = w[i];
        
        //        for (int i = 0; i < 6; i++)
        //            cout << i << ": " << v[i] << endl;
    }
    
    
    //                     sum = sum of the entries of v[]
    unsigned long long sum = 0;
    for (int i = 0; i < vertexCount; i++)
        sum += v[i];
    
    //                     divide each entry of v[] by sum
    double x[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        //             cout << i << ": " << (v[i] / double(sum)) << endl;
        x[i] = (v[i]/double(sum));
    }
    
    //                     find top n values in v[]
    
    priorityQueue<double> myQueue(MIN, topCount);
    for (int i = 0; i < topCount; i++)
        myQueue.insert(i, x[i]);
    
    int throwaway1 = 0;
    double throwaway2 = 0;
    
    for (int i = 4; i < vertexCount; i++) {
        if (x[i] > myQueue.retMin()) {
            myQueue.deleteMin(throwaway1, throwaway2);
            myQueue.insert(i, x[i]);
        }
    }
    
    influencersArr = new influencersStruct[topCount];
    for (int i = 0; i < topCount; i++)
        myQueue.deleteMin(influencersArr[i].influencerName, influencersArr[i].influencerValue);
    
    //    myQueue.printHeap();
    
    //         bubbleSort(x, vertexCount);
    //
    //         for (int i = 0; i < topCount; i++) {
    //             cout << i << " " << x[i] << endl;
    //         }
    
    
}
void socialNetwork::triangles() { // find the count of triangles for the graph.
    
    //    // find combination of every two nodes
    //    // go through every vertex
    
    
    
    for (int i = 0; i < vertexCount; i++) {
        
        for (edgeStruct *iCurr = adjList[i]; iCurr != NULL; iCurr = iCurr->next) { // goes through all the adjacent edges of every vertex
            
            for (edgeStruct *jCurr = adjList[iCurr->v2]; jCurr != NULL; jCurr = jCurr->next) { // goes through all the adjacent edges of the adjacent edges of every vertex
                
                for (edgeStruct *kCurr = adjList[jCurr->v2]; kCurr != NULL; kCurr=kCurr->next) {
                    if (kCurr->v2 == i) {
                        trianglesCnt++;
                        break;
                    }
                }
            }
        }
    }
    
    trianglesCnt = trianglesCnt / 6;
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
    unsigned int vertexTimes = vertexCount * (vertexCount - 1);
    cout << "Graph Density: " << (double(2)*edgeCount)/vertexTimes << endl;
    
    cout << endl;
    
    cout << "Highest Degree: " << highestDegree << endl;
    cout << "Lowest Degree: " << lowestDegree << endl;
    cout << "Count of Singles: " << singles << endl;
    cout << "Count of Highest Degree: " << countOfHighestDegree << endl;
    cout << "Count of Lowest Degree: " << countOfLowestDegree << endl;
    cout << "Average Degree: " << avgDegree << endl;
    
    cout << endl;
    
    cout << "The largest connected component contains " << largestConnected << " nodes." << endl;
    cout << "There are " << unconnected << " unconnected nodes" << endl;
    
    cout << endl;
    
    cout << "Triangles: " << trianglesCnt << endl;
    
    cout << endl;
    
    cout << "Graph diameter: " << dia << endl;
    
    cout << endl;
    
    cout << "Top 5 influencer's: " << endl;
    for (int i = top - 1; i >= 0; i--)
        cout << influencersArr[i].influencerName << " (" << influencersArr[i].influencerValue << ")  ";
    
    cout << endl << endl;
    
}

void socialNetwork::bubbleSort(double myArray[], int top) {
    for (int i = 0; i < top; i++) {
        bool swapped = false;
        for (int j = 0; j < vertexCount - i - 1; j++) {
            if (myArray[j] < myArray[j+1]) { // swap
                //                int temp = myArray[j];
                //                myArray[j] = myArray[j+1];
                //                myArray[j+1] = temp;
                swap(myArray[j], myArray[j+1]);
                swapped = true;
            }
        }
        
        if (!swapped)
            break;
    }
}

void socialNetwork::swap(double& x, double&y) {
    double temp = x;
    x = y;
    y = temp;
}

