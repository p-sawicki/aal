/*
 * Implementacja algorytmu grafowego
 * Autorzy: Piotr Sawicki, Paweł Wieczorek
 */

#include "graph.h"

/*
 * Edges helper class implementation
 */

void Edges::addEdge(size_t to) {
    odds.push_back(to);
}

void Edges::addRange(size_t mStart, size_t mEnd) {
    range.first = mStart;
    range.second = mEnd;
}

bool Edges::contains(ssize_t idx) {
    if(idx >= range.first && idx <= range.second)
        return true;
    else if(std::find(odds.begin(), odds.end(), idx) != odds.end())
        return true;
    else
        return false;
}

Edges::Iterator Edges::begin() {
    if(odds.size() == 0) {
        if(range.first < 0)
            return Iterator(2, *this);
        else
            return Iterator(1, *this);
    } else
        return Iterator(0, *this);
}
Edge Edges::Iterator::operator*() {
    switch(mode) {
        case 0:
            return parent.odds[vec_pos];
            break;
        case 1:
            return range_pos;
            break;
    }
    throw std::invalid_argument("Attempted to access ended iterator");
}
Edges::Iterator& Edges::Iterator::operator++() {
    switch(mode) {
        case 0:
            if(vec_pos < parent.odds.size() - 1)
                vec_pos++;
            else if(parent.range.first >= 0)
                mode++;
            else
                mode = 2;
            break;
        case 1:
            if(range_pos < parent.range.second)
                range_pos++;
            else
                mode++;
            break;
        default:
            break;
    }
    return *this;
}
bool operator==(const Edges::Iterator& a, const Edges::Iterator& b) {
    if(a.mode != b.mode)
        return false;

    if(a.mode == 0)
        return a.vec_pos == b.vec_pos;
    else if(a.mode == 1)
        return a.range_pos == b.range_pos;
    else
        return true;
}
bool operator!=(const Edges::Iterator& a, const Edges::Iterator& b) {
    return !(a == b);
}



/*
 * DAG implementation
 */
void DAG::addNode(double w, double h, double d) {
    nodes.push_back(new Node(w, h, d));
}

size_t DAG::size() {
    return nodes.size();
}

void DAG::addEdge(Edge from, Edge to) {
    nodes[from]->edgesOut.addEdge(to);
}

void DAG::addRange(Edge from, Edge start, Edge end) {
    nodes[from]->edgesOut.addRange(start, end);
}

DAG::~DAG() {
    for (Node* node : nodes)
        delete node;
}


/*
 * Task solver
 */
Tower graph_get_highest_tower(std::istream &stream) {
    size_t n;
    double w, h, d;
    DAG graph;

    stream >> n;
    for(size_t i = 0; i < n; i++) {
        stream >> w >> h >> d;
        graph.addNode(w, h, d);
        graph.addNode(w, d, h);
        graph.addNode(d, h, w);
    }

    std::sort(graph.nodes.begin(), graph.nodes.end(), [](Node*& a, Node*& b) {
        return a->element.width < b->element.width;
    });

    // Connect nodes A,B if A can be put on B, i.e. A < B
    for(size_t i = 0; i < graph.nodes.size(); i++)
        for(size_t j = i; j < graph.nodes.size(); j++) {
            if(graph.nodes[i]->element.height < graph.nodes[j]->element.width) {
                graph.addRange(i, j, graph.nodes.size() - 1);
                break;
            } else if(graph.nodes[i]->element < graph.nodes[j]->element) {
                graph.addEdge(i, j);
            }
        }

    // Sort topologicaly
    // Thanks to the above sort(...) created graph is already topologicaly sorted

    // Find highest piramid
    for(Node* node : graph.nodes) {
        node->topHeight += node->element.depth;

        for(Edge targetIdx : node->edgesOut) {
            Node* target = graph.nodes[targetIdx];
            if(target->topHeight < node->topHeight)
                target->topHeight = node->topHeight;
        }
    }

    double maxHeight = -1;
    Node* topBrick = NULL;
    size_t topBrickIdx = 0, cnt = 0;
    for(Node* node : graph.nodes) {
        if(maxHeight < node->topHeight)
            maxHeight = node->topHeight, topBrick = node, topBrickIdx = cnt;
        cnt++;
    }


    // Backtrack
    std::vector<Node*> nodes;
    nodes.push_back(topBrick);
    
    while(graph.nodes[topBrickIdx]->topHeight > graph.nodes[topBrickIdx]->element.depth) {
        topBrick = graph.nodes[topBrickIdx];

        for(ssize_t curBrickIdx = topBrickIdx - 1; curBrickIdx >= 0; curBrickIdx--) {
            Node* curBrick = graph.nodes[curBrickIdx];
            if(curBrick->edgesOut.contains(topBrickIdx) && 
                        topBrick->element.depth + curBrick->topHeight == topBrick->topHeight) {
                nodes.push_back(curBrick);
                topBrickIdx = curBrickIdx;
                break;
            }
        }
    }

    Tower tower;
    for(auto ir = nodes.rbegin(); ir != nodes.rend(); ++ir) {
        tower.bricks.push_back((*ir)->element);
        tower.depth += (*ir)->element.depth;
    }
    return tower;
}
