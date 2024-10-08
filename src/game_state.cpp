#include <include/game_state.h>

GameState::GameState()
{

    adjMatrix->addEdges();
    adjMatrix->placeObstacles();
    adjMatrix->printAdjMatrix();
    std::cout << "\nRunning Dijkstra's algorithm from node 0..." << std::endl;
    /*SinglyLinkedList<pairNode> result = */adjMatrix->dijkstra(0);

    // Print the results (distances from node 0)
    // auto* current = result.getHead();
    // while (current != nullptr) {
    //     std::cout << "Node: " << current->data.nodeIndex
    //               << " - Distance from source: " << current->data.distance << std::endl;
    //     current = current->next;
    // }
}

int GameState::rows = 3;

int GameState::columns = 4;

AdjacencyMatrix<int>* GameState::adjMatrix  = new AdjacencyMatrix<int>(rows,columns);
