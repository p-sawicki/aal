#ifndef GRAPH_H
#define GRAPH_H

#include "utils.h"

using Edge = size_t;

class Edges {
    // Range represented as [from(inc.); to(inc.)]
    std::pair<ssize_t, ssize_t> range;
    std::vector<size_t> odds;

public:
    Edges() : range(-1, -2) {};
    void addEdge(size_t to);
    void addRange(size_t mStart, size_t mEnd);
    bool contains(ssize_t idx);

    struct Iterator {
        Iterator(int _mode, Edges& _parent) : mode(_mode), parent(_parent), range_pos(parent.range.first), vec_pos(0) {};
        Edge operator*();
        Iterator& operator++();
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; };

        friend bool operator== (const Iterator& a, const Iterator& b);
        friend bool operator!= (const Iterator& a, const Iterator& b);  
    private:
        int mode;
        Edges& parent;
        ssize_t range_pos;
        size_t vec_pos;
    };

    Iterator begin();
    Iterator end() { return Iterator(2, *this); };
};

struct Node {
    Brick element;
    Edges edgesOut;
    double topHeight;

    Node(double w, double h, double d) : 
        element({w, h, d}), topHeight(0) {};
};

class DAG {
    size_t maxTopoIdx = 0;
    
public:
    std::vector<Node*> nodes;

    void addNode(double, double, double);
    size_t size();
    void addEdge(Edge, Edge);
    void addRange(Edge, Edge, Edge);
    ~DAG();
};

Tower graph_get_highest_tower(std::istream &stream = std::cin);

#endif //GRAPH_H