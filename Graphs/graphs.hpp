#pragma once 

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>



class Graph {
private:

    std::unordered_map<std::string, std::unordered_set<std::string, int>> adjList;

public:
    bool addVertex(std::string vertex) {
        if (adjList.count(vertex) == 0) {
            adjList[vertex];
            return true;
        }
        return false;
    }

    bool addEdge(std::string vertex1, std::string vertex2) {
        if(adjList.count(vertex1) != 0 && adjList.count(vertex2) != 0){
        adjList.at(vertex1).insert(vertex2);
        adjList.at(vertex2).insert(vertex1);
        return true;
        }
        return false;
    }
};