#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){
    this->nodesExplored = new NodeList();
}

PathSolver::~PathSolver(){
    delete this->nodesExplored;
}

void PathSolver::forwardSearch(Env env) {
    Node* S = getStartNode(env); //start location of the robot in the environment
    Node* G = getGoalNode(env); //goal location for the robot to get reach

    //Let P be a list of positions the robot can reach, with distances (initially contains S).
    NodeList* P = new NodeList();
    P->addElement(S);

    //Let C be a list of positions the that has already being explored, with distances (initially empty).
    NodeList* C = new NodeList();

    //goal reached flag
    bool goalReached = false;

    //offsets for the 4 directions
    int colOffsets[] = {0, 0, -1, 1};
    int rowOffsets[] = {-1, 1, 0, 0};

    //while P is not empty and the goal has not been reached
    while (P->getLength() > 0 && !goalReached){
        //Select the node p from the open-list P that has the smallest estimated distance to the goal and is not in C
        Node *p = getSmallestDistanceNode(G, P, C);

        bool isGoal = p->isGoal(G);
        goalReached = isGoal;

        int col = p->getCol();
        int row = p->getRow();
        //Each position in E that the robot can reach from p
        for (int i = 0; i < 4; i++) {
            int newRow = row + rowOffsets[i];
            int newCol = col + colOffsets[i];

            //if the neighbour is not a wall or out of bounds add it to P
            if (newRow >= 0 && newRow < ENV_DIM && newCol >= 0 && newCol < ENV_DIM &&
                env[newRow][newCol] != SYMBOL_WALL) {

                //Set the distance_travelled of q to be one more that that of p
                Node* q = new Node(newRow, newCol, p->getDistanceTraveled() + 1);

                if(!C->contains(q) && !P->contains(q)){
                    //Add q to open-list P only if it is not already in it.
                    P->addElement(q);
                } else{
                    delete q;
                }
            }
        }

        //Add p to closed-list C.
        C->addElement(p);

        // Remove p from P
        P->removeElement(p);
    }

    // Store the nodes that have been explored
    delete this->nodesExplored;

    if (!goalReached) {
        std::cout << "Goal not reachable" << std::endl;
        this->nodesExplored = new NodeList();
    }

    else
        this->nodesExplored = new NodeList(*C);

    // Clean up
    delete P;
    delete C;
}

NodeList* PathSolver::getNodesExplored(){
    //return deep copy of nodesExplored
    return new NodeList(*this->nodesExplored);
}

NodeList* PathSolver::getPath(Env env){
    NodeList* path = new NodeList();

    Node* goal = getGoalNodeFromExplored(env);

    if (goal == nullptr) {
        return path;
    }

    Node* curr = goal;
    NodeList* temp = new NodeList();
    temp->addElement(curr);

    //while the distance traveled is greater than 0
    while (curr->getDistanceTraveled() > 0){
        int col = curr->getCol();
        int row = curr->getRow();

        int colOffsets[] = {0, 0, -1, 1};
        int rowOffsets[] = {-1, 1, 0, 0};

        bool validPath = false;

        //check the neighbors of the current node
        for (int i = 0; i < 4; i++) {
            int newRow = row + rowOffsets[i];
            int newCol = col + colOffsets[i];

            //if the neighbor is not a wall or out of bounds
            if (newRow >= 0 && newRow < ENV_DIM && newCol >= 0 && newCol < ENV_DIM &&
                env[newRow][newCol] != SYMBOL_WALL) {

                //check if the neighbor is in the nodesExplored list
                for(int j = 0; j < nodesExplored->getLength(); j++) {
                    Node* node = nodesExplored->getNode(j);

                    //if the node is the neighbor and the distance traveled is one less than the current node means reachable
                    if(node->getRow() == newRow && node->getCol() == newCol &&
                            node->getDistanceTraveled() == curr->getDistanceTraveled() - 1) {
                        curr = node;
                        validPath = true;
                        temp->addElement(curr);
                        break;
                    }
                }
            }

            if(validPath) {
                break;
            }
        }
    }

    //reverse the path
    for (int i = temp->getLength() - 1; i >= 0; i--) {
        path->addElement(temp->getNode(i));
    }

    delete temp;

    return path;
}

//-----------------------------
//create method that return start and goal node
Node* PathSolver::getStartNode(Env env){
    Node* s = nullptr;
    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            if (env[i][j] == SYMBOL_START) {
                s = new Node(i, j, 0);
            }
        }
    }
    return s;
}

Node* PathSolver::getGoalNode(Env env){
    Node* g = nullptr;
    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            if (env[i][j] == SYMBOL_GOAL) {
                g = new Node(i, j, 0);
            }
        }
    }
    return g;
}

Node* PathSolver::getGoalNodeFromExplored(Env env){
    Node* goalNode = nullptr;
    for(int i = 0; i < nodesExplored->getLength(); i++) {
        Node* node = nodesExplored->getNode(i);
        if(env[node->getRow()][node->getCol()] == SYMBOL_GOAL) {
            goalNode = node;
        }
    }

    return goalNode;
}



Node *PathSolver::getSmallestDistanceNode(Node *G,
                                          NodeList *P, NodeList* C) const {
    Node* p = nullptr;
    int smallestDistance = INT_MAX;
    for (int i = 0; i < P->getLength(); i++) {
        Node* node = P->getNode(i);
        if (node != nullptr) {
            //node in c
            if(C->contains(node)){
                continue;
            }

            int estimatedDistance = node->getEstimatedDist2Goal(G);
            if (estimatedDistance < smallestDistance) {
                smallestDistance = estimatedDistance;
                p = node;
            }
        }
    }
    return p;
}