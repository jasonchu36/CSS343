#include "graphm.h"
#include <climits>
#include <iomanip>


// --------------------- GraphM -----------------------------------------
// Default constructor
// --------------------------------------------------------------
GraphM::GraphM()
{
    size = 0;

    for (int i = 1; i < MAXNODES; i++)
    {
        for (int j = 1; j < MAXNODES; j++)
        {
            C[i][j] = INT_MAX;
            T[i][j].visited = false;
            T[i][j].dist = INT_MAX;
            T[i][j].path = 0;
        }
    }
} // end of GraphM()

// --------------------- buildGraph -----------------------------------------
// function to build graph from .txt file
// --------------------------------------------------------------
void GraphM::buildGraph(ifstream& infile)
{
    infile >> size;                
    string nodeName = "";           
    getline(infile, nodeName);     

    for (int i = 1; i <= size; ++i)
    {
        data[i].setData(infile);  
    }

    int from, to, distance;

    while (infile >> from >> to >> distance)
    {
        if (from == 0)
        {
            break;  
        }

        C[from][to] = distance; 
    }
} // end of buildGraph()

// --------------------- findShortestPath -----------------------------------------
// function for Dijkstra's algorithm
// --------------------------------------------------------------
void GraphM::findShortestPath()
{
    for(int source = 1; source <= size; source++) 
    {
        T[source][source].dist = 0;

        for(int i = 1; i <=size; i++) 
        {
            int v = -1;
            int minDist = INT_MAX;

            for(int j = 1; j <= size; j++) 
            {
                if(T[source][j].dist <minDist && !T[source][j].visited) 
                {
                    minDist = T[source][j].dist;
                    v = j;
                }
            }

            if(v == -1) 
            {
                break;
            }

            T[source][v].visited = true;

            for(int w = 1; w <= size; w++) 
            {
                if(C[v][w] < INT_MAX && !T[source][w].visited) 
                {
                    if(T[source][v].dist + C[v][w] < T[source][w].dist) 
                    {
                        T[source][w].dist = T[source][v].dist + C[v][w];
                        T[source][w].path = v;
                    }
                }
            }
        }
    }

    for(int i = 1; i <= size; i++) 
    {
        for(int j = 1; j <= size; j++) 
        {
            T[i][j].visited = false;
        }
    }
} // end of findShortestPath()

// --------------------- insertEdge -----------------------------------------
// function that creates an edge between two given nodes
// --------------------------------------------------------------
bool GraphM::insertEdge(int from, int to, int distance)
{
    if (from > size || from < 1)
    {
        return false;
    }

    if (to > size || to < 1)
    {
        return false;
    }


    if (distance != 0 && from == to)
    {
        return false;
    }

    if (distance < 0)
    {
        return false;
    }

    C[from][to] = distance;
    findShortestPath();

    return true;
} // end of insertEdge()

// --------------------- removeEdge -----------------------------------------
// function that removes an edge between two given nodes
// --------------------------------------------------------------
bool GraphM::removeEdge(int from, int to)
{
    if (from > size || from < 1)
    {
        return false;
    }

    if (to > size || to < 1)
    {
        return false;
    }

    C[from][to] = INT_MAX;
    findShortestPath();

    return true;
} // end of removeEdge()

// --------------------- displayAll -----------------------------------------
// function to show Dijkstra's algorithm is working properly
// --------------------------------------------------------------
void GraphM::displayAll()
{
    cout << "Description" << setw(20) << "from node" << setw(10) << "to node" << setw(14) << "Dijkstra's" << setw(7) << "Path" << endl;

    for(int i = 1; i <= size; i++) 
    {
        cout << data[i] << endl;
        for(int j = 1; j <= size; j++) 
        {
            if(i != j) 
            {
                cout << setw(27) << i << setw(10) << j;

                if(T[i][j].dist < INT_MAX) 
                {
                    cout << setw(12) << T[i][j].dist;
                } 
                else 
                {
                    cout << setw(12) << "----";
                }

                cout << setw(10);
                displayPath(i,j);
                cout << endl;
            }
        }
    }
    cout << endl;
} // end of displayAll()

// --------------------- display -----------------------------------------
// function to display shortest path between two vertex
// --------------------------------------------------------------
void GraphM::display(int from, int to)
{
    if(from < 1 || from > size || to < 1 || to > size) 
    {
        return;
    }

    cout << setw(7) << from << setw(7) << to;
    
    if(T[from][to].dist < INT_MAX) 
    {
        cout << setw(12) << T[from][to].dist;
    } 
    else 
    {
        cout << setw(15) << "----";
    }

    cout << setw(15);
    displayPath(from, to);
    cout << endl;
    displayName(from, to);
    cout << endl;
} // end of display()

// --------------------- displayPath -----------------------------------------
// helper function for display() and displayAll() functions
// --------------------------------------------------------------
void GraphM::displayPath(int from, int to)
{
    int vertex = T[from][to].path;

    if(vertex != 0) 
    {
        displayPath(from, vertex);
        cout << to << " ";
    } 
    else if (from == to) 
    {
        cout << to << " ";
    }
} // end of displayPath()

// --------------------- displayName -----------------------------------------
// helper function for display() and displayAll() functions
// --------------------------------------------------------------
void GraphM::displayName(int from, int to)
{
    int vertex = T[from][to].path;

    if(vertex != 0) 
    {
        displayName(from, vertex);
        cout << data[to] << endl;
    } 
    else if (from == to) 
    {
        cout << data[to] << endl;
    }
    cout << endl;
} // end of displayName()