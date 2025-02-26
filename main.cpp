#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);

//global file variable
std::ifstream file;
std::ofstream outputFile;
std::string filename;

int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
//    std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
//    testNode();
//    testNodeList();
//    std::cout << "DONE TESTING" << std::endl << std::endl;

    //from argv[1] get the filename
    filename = argv[1];
    //pass filename to file
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    // Load Environment 
    Env env;
    readEnvStdin(env);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);

    delete pathSolver;
    delete exploredPositions;
    delete solution;

}

void readEnvStdin(Env env) {
    //read and store the environment
    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            char c;
            //read from file
            file >> c;
            env[i][j] = c;
        }
    }
}

void printEnvStdout(Env env, NodeList* solution) {
    std::string outfilename = filename.substr(0, filename.find_last_of('.')) + "_actual.out";
    outputFile.open(outfilename);


    // Create a copy of the environment to modify and print
    Env envCopy;
    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            envCopy[i][j] = env[i][j];
        }
    }

    // Iterate over the solution NodeList
    for (int i = 0; i < solution->getLength() - 1; i++) {
        Node* currentNode = solution->getNode(i);
        Node* nextNode = solution->getNode(i + 1);

        // Determine the direction from the current node to the next node
        // Skip if the current node is the start node or goal node
        if (env[currentNode->getRow()][currentNode->getCol()] != 'S' &&
                env[currentNode->getRow()][currentNode->getCol()] != 'G'){

            // Update the copy of the environment with the direction
            if (nextNode->getCol() > currentNode->getCol())
                envCopy[currentNode->getRow()][currentNode->getCol()] = '>';
            //if the next node is to the left of the current node
            else if (nextNode->getCol() < currentNode->getCol())
                envCopy[currentNode->getRow()][currentNode->getCol()] = '<';

            //if the next node is below the current node
            else if (nextNode->getRow() > currentNode->getRow())
                envCopy[currentNode->getRow()][currentNode->getCol()] = 'v';

            //if the next node is above the current node
            else if (nextNode->getRow() < currentNode->getRow())
                envCopy[currentNode->getRow()][currentNode->getCol()] = '^';
        }
    }

    // Print the modified environment
    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            std::cout << envCopy[i][j];
            outputFile << envCopy[i][j];
        }
        std::cout << std::endl;
        outputFile << std::endl;
    }

    outputFile.close();
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}