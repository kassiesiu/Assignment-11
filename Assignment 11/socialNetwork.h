// Kassie Wong
// Assignment 11
// Section 1001

class socialNetwork {
public:
    socialNetwork();
    ~socialNetwork();
    void readGraph(); // read a formatted graph file
    void findConnectedComponents(); // find size of the largest connected component
    void degreeStats(); // find the vertices's degree statistics including...
    void diameter(); // find the graph diameter
    void influencers(); // find the top n influencer's based on eigenvector centrality
    void triangles(); // find the count of triangles for the graph.
    void printGraph(); // print the formatted graph. Optional, used only for debugging.
private:
};
