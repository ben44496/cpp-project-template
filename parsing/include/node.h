#include <stdint.h>

namespace Parser {

class Node {
    public:
        Node(T data);

        unsigned getID();
        T getData();

        static unsigned num_nodes;

    private:
        unsigned id_ = 0;
        T data_ = T();
};
}
