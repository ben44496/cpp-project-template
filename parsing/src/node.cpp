#include "../include/node.h"

using std::string;
using std::vector;

namespace Parser {

Node::Node(double lat, double longitude, int franodeid, string country, string state, int district) : id_(franodeid), country_(country), state_(state), district_(district) {
    latitude_ = lat;
    longitude_ = longitude;
}

std::tuple<double, double> Node::getLoc() {
    return std::tuple<double, double>(latitude_, longitude_);
}

vector<std::tuple<Node*, float>> Node::getOutbound() const {
    return outbound_;
}

vector<std::tuple<Node*, float>> Node::getInbound() const {
    return inbound_;
}

void Node::addOutboundEdge(Node* node, float weight) {
    outbound_.push_back(std::make_tuple(node, weight));
}

void Node::addInboundEdge(Node* node, float weight) {
    inbound_.push_back(std::make_tuple(node, weight));
}

int Node::getId() const {
    return this->id_;
}

// For testing only
string Node::print() {
    string output;
    output += "ID: " + std::to_string(id_) + "\n";
    output += "Lat: " + std::to_string(latitude_) + "\n";
    output += "Long: " + std::to_string(longitude_) + "\n";
    output += "Country: " + country_ + "\n";
    output += "State: " + state_ + "\n";
    output += "District: " + std::to_string(district_) + "\n";
    output += "Outbound Edges: " + std::to_string(outbound_.size()) + "\n";
    return output;
}

}