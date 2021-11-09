#include "../include/edge.h"

using std::string;
using std::tuple;

namespace Parser {

Edge::Edge(int route_id, int from_node, int to_node, string state, string country, double km) : route_id_(route_id), from_node_(from_node),
                                                                            to_node_(to_node), state_(state), country_(country), km_(km) {}

int Edge::fromNode() const {
    return from_node_;
}

int Edge::toNode() const {
    return to_node_;
}

double Edge::km() const {
    return km_;
}

tuple<int, float> Edge::outbound() {
    return tuple<int, float>(to_node_, (float)km_);
}

}