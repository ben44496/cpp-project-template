#include <stdint.h>
#include <string>

namespace Parser {

class Node {
    public:
        Node(std::string data);

        unsigned getID();
        std::string getData();

        static unsigned num_nodes_;

    private:
        unsigned id_ = 0;
        std::string data_ = "";
};
}
