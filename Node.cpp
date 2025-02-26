#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
    //implementing the constructor
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

Node::~Node(){
    this->row = 0;
    this->col = 0;
    this->dist_traveled = 0;
}

int Node::getRow(){
    return this->row;
}

int Node::getCol(){
    return this->col;
}

int Node::getDistanceTraveled(){
    return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    //Estimated distance = distance_travelled of node p + Manhattan distance from p to G
    //Manhattan_distance = |colp − colG| + |rowp − rowG|
    double manhattan_distance = abs(this->col - goal->getCol()) + abs(this->row - goal->getRow());

    return this->dist_traveled + manhattan_distance;
}
    
//--------------------------------
bool Node::isGoal(Node* goal) {
    return row == goal->getRow() && col == goal->getCol();
}