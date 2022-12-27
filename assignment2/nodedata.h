#ifndef NODEDATA_H
#define NODEDATA_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class NodeData{
    friend ostream &operator<<(ostream &out, const NodeData &N);

    public:
    NodeData();          // default constructor, data is set to an empty string
    ~NodeData();
    NodeData(const string& s);      // data is set equal to parameter
    NodeData(const NodeData& nd);    // copy constructor
    NodeData& operator=(const NodeData& rhs);

    // set class data from data file
    // returns true if the data is set, false when bad data, i.e., is eof
    bool setData(istream& infile);

    bool operator==(const NodeData& rhs) const;
    bool operator!=(const NodeData& rhs) const;
    bool operator<(const NodeData& rhs) const;
    bool operator>(const NodeData& rhs) const;
    bool operator<=(const NodeData& rhs) const;
    bool operator>=(const NodeData& rhs) const;

private:
    string data;
};

#endif // NODEDATA_H