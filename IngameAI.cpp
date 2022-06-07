#include "IngameAI.h"
#include <future>

int getElementPlainVector(int x, int y, int size) {
    return x * size + y;
}

IngameAI::IngameAI(uint8_t foresightCount, const GameScene& scene) :
    foresightCount(foresightCount),
    scene(scene),
    isStopped(false) {

}

void IngameAI::setDifficulty(uint8_t foresightCount) {
    this->foresightCount = foresightCount;
}

void IngameAI::abort() {
    isStopped = true;
}

int16_t IngameAI::scoreDifferenceHeuristic(const Node &node) {
    if (scene.getGameCondition().getTurn() == GameTurn::FirstPlayer) {
        return node.condition.getFirstPlayerScore() - node.condition.getSecondPlayerScore();
    }
    return node.condition.getSecondPlayerScore() - node.condition.getFirstPlayerScore();
}

int16_t IngameAI::NodeSequenceHeuristic(const Node& node, uint8_t depth) {
    if (depth == foresightCount) {
        return 0;
    }
    if (node.condition.getFirstPlayerScore() > node.condition.getSecondPlayerScore()) {
        if (scene.getGameCondition().getTurn() == GameTurn::FirstPlayer) {
            return 9999 / depth;
        }
        return -9999 / depth;
    }
    if (node.condition.getSecondPlayerScore() > node.condition.getFirstPlayerScore()) {
        if (scene.getGameCondition().getTurn() == GameTurn::FirstPlayer) {
            return -9999 / depth;
        }
        return 9999 / depth;
    }
    return 0;
}

int16_t IngameAI::minimax(Node& node, uint8_t depth, bool isMax, AlphaBetaModule alphaBeta) {
    if (isStopped) {
        return 0;
    }
    if (depth++ < foresightCount) {
        addNode(node);
    }
    if (node.childNodes.size() == 0) {
        return scoreDifferenceHeuristic(node) + NodeSequenceHeuristic(node, depth);
    }
    if (isMax) {
        int16_t bestVal = -9999;
        for (auto& childNode : node.childNodes) {
            int16_t Heuristic = minimax(*childNode, depth, false, alphaBeta);
            bestVal = std::max(bestVal, Heuristic);
            alphaBeta.alpha = std::max(alphaBeta.alpha, Heuristic);
            if (alphaBeta.beta <= alphaBeta.alpha) {
                break;
            }
        }
        return bestVal;
    }
    else {
        int16_t bestVal = 9999;
        for (auto& childNode : node.childNodes) {
            int16_t Heuristic = minimax(*childNode, depth, true, alphaBeta);
            bestVal = std::min(bestVal, Heuristic);
            alphaBeta.beta = std::min(alphaBeta.beta, Heuristic);
            if (alphaBeta.beta <= alphaBeta.alpha) {
                break;
            }
        }
        return bestVal;
    }
}

std::vector<std::pair<int16_t, std::pair<uint8_t, uint8_t>>> IngameAI::getHeuristics() {
    std::vector<std::pair<int16_t, std::pair<uint8_t, uint8_t>>> heuristics;
    const int size = scene.getBoard().getSize();
    const auto& cells = scene.getBoard().getBoard();

    std::vector<bool> openNodes;
    openNodes.resize(size * size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            openNodes[getElementPlainVector(i, j, size)] = true;
            if (cells[i][j].isSelected()) {
                openNodes[getElementPlainVector(i, j, size)] = false;
            }
        }
    }

    const GameCondition& condition = scene.getGameCondition();
    const uint8_t x = condition.getPosition().first;
    const uint8_t y = condition.getPosition().second;
    if (condition.getMovement() == Movement::Horizontal) {
        for (uint8_t i = 0; i < size; i++) {
            if (openNodes[getElementPlainVector(x, i, size)]) {
                std::unique_ptr<Node> node = std::make_unique<Node>();
                setNodeData(*node, openNodes, condition, {x, i});
                int16_t score = minimax(*node, 1, false, {-9999, 9999});
                heuristics.push_back({score, {x, i}});
            }
        }
    }
    else {
        for (uint8_t i = 0; i < size; i++) {
            if (openNodes[getElementPlainVector(i, y, size)]) {
                std::unique_ptr<Node> node = std::make_unique<Node>();
                setNodeData(*node, openNodes, condition, {i, y});
                int16_t score = minimax(*node, 1, false, {-9999, 9999});
                heuristics.push_back({score, {i, y}});
            }
        }
    }

    return heuristics;
}

void IngameAI::addNode(Node& node) {
    const uint8_t x = node.condition.getPosition().first;
    const uint8_t y = node.condition.getPosition().second;
    const uint8_t size = scene.getBoard().getSize();
    if (node.condition.getMovement() == Movement::Horizontal) {
        for (uint8_t i = 0; i < size; i++) {
            if (node.openNodes[getElementPlainVector(x, i, size)]) {
                std::unique_ptr<Node> newNode = std::make_unique<Node>();
                setNodeData(*newNode, node.openNodes, node.condition, {x, i});
                node.addNode(newNode);
            }
        }
    }
    else {
        for (uint8_t i = 0; i < size; i++) {
            if (node.openNodes[getElementPlainVector(i, y, size)]) {
                std::unique_ptr<Node> newNode = std::make_unique<Node>();
                setNodeData(*newNode, node.openNodes, node.condition, {i, y});
                node.addNode(newNode);
            }
        }
    }
}

void IngameAI::setNodeData(Node& node, const std::vector<bool>& openNodes, const GameCondition& condition, Position position) {
    const uint8_t x = position.first;
    const uint8_t y = position.second;
    node.openNodes = openNodes;
    node.condition = condition;
    node.openNodes[getElementPlainVector(x, y, scene.getBoard().getSize())] = false;
    const int8_t number = scene.getBoard().getBoard()[x][y].getNumber();
    node.condition.scoreChanged(number);
    node.condition.gameTurnChanged();
    node.condition.movementChanged();
    node.condition.positionChanged(position);
}

void IngameAI::calculatePosition() {
    std::future<bool> isWaiting = std::async(std::launch::async, [](){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return true;
    });

    auto nodeValues = getHeuristics();
    Position position = nodeValues[0].second;
    int16_t bestValue = nodeValues[0].first;

    for (const auto& values : nodeValues) {
        if (values.first > bestValue) {
            bestValue = values.first;
            position = values.second;
        }
    }
    if (isStopped) {
        return;
    }
    isWaiting.get();

    emit positionCalculated(position);
}
