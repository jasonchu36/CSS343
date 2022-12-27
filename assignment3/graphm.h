#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h"
#include <fstream>
#include <iostream>

using namespace std;

int const MAXNODES = 101;

class GraphM
{
    public:
        GraphM();

        void buildGraph(ifstream&);
        void findShortestPath();
        bool insertEdge(int from, int to, int distance);
        bool removeEdge(int from, int to);
        void displayAll();
        void display(int from, int to);
        
    private:
        struct TableType
        {
            bool visited;
            int dist;
            int path;
        };

    NodeData data[MAXNODES];              // data for graph nodes 
    int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
    int size;                             // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path

    void displayPath(int from, int to);
    void displayName(int from, int to);
};

#endif //GRAPHM_H