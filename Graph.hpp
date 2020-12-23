#ifndef GRAPH_H
#define GRAPH_H
#include "GraphBase.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <climits>

class EV {
public:
    EV() {
        u = " ";
        v = " ";
        eW = 0;
    };
    ~EV();
    std::string u;
    std::string v;
    unsigned long eW;
};

class Graph : public GraphBase {
public:
    Graph();//constructor
    ~Graph();//desctructor
    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
    // helper function to print the shortest path 
    void print(std::map<std::string, std::string> sL, std::string eL, std::vector<std::string> &path);
private:
    friend class EV;
    std::vector<EV*> components;
    std::vector<std::string> vertices;
};

#endif
