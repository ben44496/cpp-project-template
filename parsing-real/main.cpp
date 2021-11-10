#include "include/node.h"

int main() {
    Node<int> n(5);
    Node<int> n(6);

    std::cout << n.getID() << ", " << n.getData()
}