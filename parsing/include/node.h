#pragma once

#include <vector>
#include <tuple>
#include <string>

namespace Parser {
class Node {
    public:
        Node(double lat, double longitude, int franodeid, std::string country, std::string state, int district);        
        std::tuple<double, double> getLoc();
        int getId() const;

        std::vector<std::tuple<Node*, float>> getOutbound() const;
        std::vector<std::tuple<Node*, float>> getInbound() const;

        void addOutboundEdge(Node* node, float weight);  
        void addInboundEdge(Node* node, float weight);        

        // TODO: Need to redo this function to overload << operator
        std::string print();
        
    private:
        int id_;
        double latitude_;
        double longitude_;
        std::string country_;
        std::string state_;
        int district_;
        std::vector<std::tuple<Node*, float>> outbound_;
        std::vector<std::tuple<Node*, float>> inbound_;
};
}