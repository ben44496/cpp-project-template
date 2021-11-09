#pragma once

#include <string>
#include <tuple>

namespace Parser {
class Edge {
    public:
        Edge(int route_id, int from_node, int to_node, std::string state, std::string country, double km);
        int fromNode() const;
        int toNode() const;
        double km() const;
        std::tuple<int, float> outbound();
    private:
        int route_id_;
        int from_node_;
        int to_node_;
        std::string state_;
        std::string country_;
        double km_;
};
}