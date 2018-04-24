// Kassie Wong
// Assignment 11
// Section 1001

#include <string>
#include <vector>

using namespace std;

class socialNetwork {
public:
    socialNetwork();
    ~socialNetwork();
    bool readGraph(string); // read a formatted graph file
    void findConnectedComponents(); // find size of the largest connected component
    void degreeStats(); // find the vertices's degree statistics including...
    void diameter(); // find the graph diameter
    void influencers(int); // find the top n influencer's based on eigenvector centrality
    void triangles(); // find the count of triangles for the graph.
    void printGraph(); // print the formatted graph. Optional, used only for debugging.
    
    
    void graphInformation();
    
private:
    string title;
    int vertexCount;
    int edgeCount;
    int top;
    
    int dia;
    int trianglesCnt;
    int highestDegree;
    int countOfHighestDegree;
    int lowestDegree;
    int countOfLowestDegree;
    int singles;
    double avgDegree;
    int unconnected;
    int largestConnected;
    
    struct edgeStruct {
        int v2;
        int weight;
        edgeStruct *next;
    };
    
    struct influencersStruct {
        int influencerName;
        double influencerValue;
    };
    
    edgeStruct **adjList;
    influencersStruct *influencersArr;
    
    void createGraph();
    void addEdge(int, int, int);
    void DFS(int, bool[], int&);
    void bubbleSort(double[], int);
    void swap(double&, double&);
    
};

