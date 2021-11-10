
namespace Parser {

template <class T>
class Node {
    public:
        Node(T);

        uint getID();
        T getData();

        static uint num_nodes = 0;

    private:
        uint id_ = 0;
        T data_ = T();
}
}
