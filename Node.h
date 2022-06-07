#ifndef NODE_H
#define NODE_H
#include <vector>
#include "GameCondition.h"
#include <memory>

struct AlphaBetaModule {
    int16_t alpha;
    int16_t beta;
};

struct Node {
    GameCondition condition;
    std::vector<bool> openNodes;
    std::vector<std::unique_ptr<Node>> childNodes;
    void addNode(std::unique_ptr<Node>& node);
};

#endif // NODE_H
