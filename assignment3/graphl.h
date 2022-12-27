#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h"
#include <iostream>
#include <fstream>

using namespace std;

int const MAX_NODES = 101;

class GraphL
{
    public:
        GraphL();
        ~GraphL();

        void buildGraph(ifstream&);
        void displayGraph();
        void depthFirstSearch();

    private:
        int size;
        struct EdgeNode;      // forward reference for the compiler
        struct GraphNode 
        {    // structs used for simplicity, use classes if desired
            EdgeNode* edgeHead; // head of the list of edges
            NodeData* data;     // data information about each node
            bool visited;                
        };

        struct EdgeNode 
        {
            int adjGraphNode;  // subscript of the adjacent graph node
            EdgeNode* nextEdge;
        };

        GraphNode graph[MAX_NODES];
        void makeEmpty();
        void dfsHelper(int vertex);
};

#endif //GRAPHL_H