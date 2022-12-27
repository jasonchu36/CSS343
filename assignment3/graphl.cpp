#include "graphl.h"
#include <climits>
#include <iomanip>

// --------------------- GraphL -----------------------------------------
// Default constructor
// --------------------------------------------------------------
GraphL::GraphL()
{
    size = 0;

    for (int i = 1; i < MAX_NODES; ++i){
        graph[i].visited = false;
        graph[i].edgeHead = NULL;
        graph[i].data = NULL;
    }
} // end of GraphL()

// --------------------- ~GraphL -----------------------------------------
// Destructor
// Calls makeEmpty() function to clear graph
// --------------------------------------------------------------
GraphL::~GraphL()
{
    makeEmpty();
} // end of ~GraphL()

// --------------------- buildGraph -----------------------------------------
// Function to create graph from .txt file
// --------------------------------------------------------------
void GraphL::buildGraph(ifstream& infile)
{
    infile >> size;            
    string nodeName = "";       
    getline(infile, nodeName); 

    for (int i = 1; i <= size; ++i) 
    {
        getline(infile, nodeName);
        NodeData* tmp = new NodeData(nodeName);
        graph[i].data = tmp;   
    }

    int from, to;

    while (infile >> from >> to)   
    {
        if (from == 0)
        {
            break;
        }

        if (graph[from].edgeHead == NULL)  
        {
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = to;           
            graph[from].edgeHead = node;   
            graph[from].edgeHead->nextEdge  = NULL;
        }
        else 
        {
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = to;            
            node->nextEdge = graph[from].edgeHead;  
            graph[from].edgeHead = node;  
        }
    }
} // end of buildGraph()

// --------------------- displayGraph -----------------------------------------
// function that displays node information and edge in the graph
// --------------------------------------------------------------
void GraphL::displayGraph()
{
    cout << "Graph:" << endl;

    for (int i = 1; i <= size; i++) 
    {
        cout << "Node" << i << "      " << *graph[i].data << endl << endl;

        EdgeNode* current = graph[i].edgeHead; 

        while (current != NULL) 
        {
            cout << setw(7) << "edge " << i << setw(2) << current->adjGraphNode << endl;
            current = current->nextEdge;
        }
    }
} // end of displayGraph()

// --------------------- depthFirstSearch -----------------------------------------
// function that traverses the graph by depth first search
// --------------------------------------------------------------
void GraphL::depthFirstSearch()
{
    cout << "Depth-first ordering: ";

    for (int v = 1; v <= size; ++v)
    {
        if (!graph[v].visited) 
        {
            dfsHelper(v);  
        }
    }

    cout << endl;
} // end of depthFirstSearch()

// --------------------- makeEmpty -----------------------------------------
// Function to make graph empty
// --------------------------------------------------------------
void GraphL::makeEmpty()
{
    for(int i = 1; i <= size; i++) 
    {
        graph[i].visited = false;
        delete graph[i].data;
        graph[i].data = NULL;

        if(graph[i].edgeHead != NULL) 
        {
            EdgeNode* target = graph[i].edgeHead;
            
            while(target != NULL) 
            {
                graph[i].edgeHead = graph[i].edgeHead -> nextEdge;
                delete target;
                target = NULL;
                target = graph[i].edgeHead;
            }
        }
    }
} // end of makeEmpty()

// --------------------- dfsHelper -----------------------------------------
// Helper function for depthFirstSearch() function
// --------------------------------------------------------------
void GraphL::dfsHelper(int vertex) 
{
    cout << "  " << vertex;
    graph[vertex].visited = true;
    EdgeNode* current = graph[vertex].edgeHead;

    while(current != NULL) 
    {
        if(!graph[current -> adjGraphNode].visited) 
        {
            dfsHelper(current -> adjGraphNode);
        }

        current = current -> nextEdge;
    }
} // end of dfsHelper()