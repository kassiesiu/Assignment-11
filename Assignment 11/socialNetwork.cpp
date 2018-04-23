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
    vertexCount = edgeCount = dia = trianglesCnt = singles = countOfHighestDegree = countOfLowestDegree = unconnected = largestConnected = 0;
    highestDegree = lowestDegree = -1;
    adjList = NULL;
    degrees = NULL;
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
    degrees = new int[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        adjList[i] = NULL;
        degrees[i] = 0;
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
    
    bool visit[vertexCount];
    
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
}

void socialNetwork::DFS(int v, bool visit[], int &count) {
    visit[v] = true;
    count++;
//    cout << v << " ";
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
            continue;
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
//    bool *visit = new bool[vertexCount];
//    int **shortestPaths = new int*[vertexCount];
//    for (int i = 0; i < vertexCount; i++) {
//        shortestPaths[i] = new int[vertexCount];
//        visit[i] = false;
//    }
//
//    for (int s = 0; s < vertexCount; s++) {
//        for (int v = 0; v < vertexCount; v++) {
//            visit[v] = false;
//        }
//
//        priorityQueue<int> myQueue(MIN, vertexCount);
//        visit[s] = true;
//        myQueue.insert(s, s);
//        shortestPaths[s][s] = 0;
//
//        while (!myQueue.isEmpty()) {
//            unsigned int v = 0;
//            int throwaway = 0;
//            myQueue.deleteMin(throwaway, v);
//
//
//        }
//
//
//    }
}
void socialNetwork::influencers(int topCount) { // find the top n influencer's based on eigenvector centrality
    
    int whenToStop = 0;
    
    if (vertexCount < 100)
        whenToStop = 10;
    else
        whenToStop = 100;
    
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
//    double x[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
//        cout << i << ": " << (v[i] / double(sum))*100 << endl;
//        x[i] = (v[i]/double(sum))*10;
    }
    
    cout << endl;
    
    //                     find top n values in v[]
//    bubbleSort(x, topCount);
//
//    for (int i = 0; i < topCount; i++) {
//        cout << x[i] << endl;
//    }


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
    
    
    
    
//    for (int i = 0; i < vertexCount; i++) {
    
//        if (degrees[i] < 1)
//            continue;

//        if (adjList[i] == NULL)
//            continue;
//
//        if (adjList[i] != NULL)
//            if (adjList[i]->next == NULL)
//                continue;
//
//        edgeStruct *iCurr = adjList[i];
//        for (int j = iCurr->v2; iCurr != NULL; iCurr = iCurr->next) {
//            j = iCurr->v2;
//            edgeStruct *jCurr = adjList[j];
//            for (int k = jCurr->v2; jCurr != NULL; jCurr = jCurr->next) {
//                k = jCurr->v2;
//                edgeStruct *kCurr = adjList[k];
//                if (kCurr->v2 == i) {
//                    trianglesCnt++;
//                    break;
//                }
//            }
//        }
//
        
//        for (edgeStruct *jCurr = adjList[adjList[i]->v2]; jCurr != NULL; jCurr = jCurr->next) {
//
//            if (jCurr->v2 == i) { // if the pair is two nodes that point to e/o
//                continue;
//            }
//
//            for (edgeStruct *lCurr = adjList[jCurr->v2]; lCurr != NULL; lCurr = lCurr->next) {
//
//                if (lCurr->v2 == i)
//                    trianglesCnt++;
//
//            }
//        }
        
        
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
    cout << "Graph Density: " << double(2*edgeCount)/(vertexCount * (vertexCount - 1)) << endl;
    
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
    
    cout << "Top 5 influencer's:" << endl;
    
    cout << endl;
    
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
    int temp = x;
    x = y;
    y = temp;
}
