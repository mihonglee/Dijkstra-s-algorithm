#include "Graph.hpp"
Graph::Graph(){
    // constructor
};
Graph::~Graph() { 
    // destructor
    components.erase(components.begin(), components.end()); 
};

void Graph::addVertex(std::string label){
    unsigned int i = 0;
    while(i < vertices.size()){
        if(vertices[i] == label){ return; }
        i+=1;
    } 
    vertices.push_back(label);
}

void Graph::removeVertex(std::string label){
    unsigned int i = 0;
    while(i <  vertices.size()) {
        if(vertices.at(i) == label) {
            // if the label is found remove it
            vertices.erase(vertices.begin() + i);

            for(unsigned int j = 0; j < components.size(); j++) {
                EV *temp = new EV();
                temp = components.at(j);
                if(temp->u == label || temp->v == label) { components.erase(components.begin() + j); }
            }
        }
        i++;
    }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){
    bool checkA = false, checkB = false;
    // iterate and check if vector contains the labels -> flag them
    for(auto v : vertices) {
        if(v == label1) { checkA = true; }
        if(v == label2) { checkB = true; }      
    }
    // if both labels are in the vector 
    if(checkA && checkB) {
            EV *edge = new EV();
            edge->u = label1;
            edge->v = label2;
            edge->eW = weight;
            components.push_back(edge);
    }
}

void Graph::removeEdge(std::string label1, std::string label2){
    EV* edge = new EV();
//    iterate and delete the matching label 
   for(unsigned int i = 0; i < components.size(); i++) {
       edge = components[i];
       if(edge->u == label1 && edge->v == label2) {
           components.erase(components.begin()+i);
       }
   }
}
// recursive print function to print the path 
void Graph::print(std::map<std::string, std::string> sL, std::string eL, std::vector<std::string> &path){
    if (sL[eL] == " ") { 
        return; 
    } else {
        print(sL, sL[eL], path);
        path.push_back(eL);
    }
}

// shortestPath method to calculate 
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
    using namespace std;
    // using priority queue
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<std::pair<int, std::string>>> priorityQ;
    // map for vertices
    map<string,string> verticesMap;
    // map for weight
    map<string,int> weightMap;
    // iterate through vertices
    for (auto label : vertices) {
        verticesMap[label] = " ";//initialize with empty string
        weightMap[label] = LONG_MAX;//denote the infinity
    }
    
    priorityQ.push(make_pair(0, startLabel)); //add the starting label to pq
    weightMap[startLabel] = 0;//add startLabel to map
    
    // dijkstra
    while (!priorityQ.empty()) {
        string topMost = priorityQ.top().second;
        priorityQ.pop();
      
        string current;
        // checking with all it's adjacent neighbors and their weights...
        for (auto adjacent : components) {
            if(adjacent->v == topMost) { current = adjacent->u; }
            else if(adjacent->u == topMost) { current = adjacent->v; }
            else { continue; }

            // relaxation
            if (weightMap[topMost] + adjacent->eW < weightMap[current]) {
                verticesMap[current] = topMost;
                weightMap[current] = weightMap[topMost] + adjacent->eW;
                priorityQ.push(make_pair(weightMap[current], current));
            }
        }
    }
    path.push_back(startLabel);
    print(verticesMap, endLabel, path);//print the path
    // return the value is the sum of the edges between the start and end vertices on the shortest path
    return weightMap[endLabel];
}
