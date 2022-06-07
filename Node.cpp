#include "Node.h"

void Node::addNode(std::unique_ptr<Node>& node) {
    childNodes.push_back(std::move(node));
}
