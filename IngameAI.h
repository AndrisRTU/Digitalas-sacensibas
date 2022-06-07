#ifndef IngameAI_H
#define IngameAI_H
#include <QThread>
#include <utility>
#include "Node.h"
#include "GameScene.h"
#include "VisualGameArea.h"

class IngameAI : public QObject {
    Q_OBJECT
private:
    uint8_t foresightCount;
    const GameScene& scene;
    bool isStopped;
    int16_t scoreDifferenceHeuristic(const Node& node);
    int16_t NodeSequenceHeuristic(const Node& node, uint8_t depth);
    int16_t minimax(Node& node, uint8_t depth, bool isMax, AlphaBetaModule alphaBeta);
    using Position = std::pair<uint8_t, uint8_t>;
    std::vector<std::pair<int16_t, Position>> getHeuristics();
    void getHeuristicScore(Node& node, uint8_t depth);
    void addNode(Node& node);
    void setNodeData(Node& node, const std::vector<bool>& openNodes, const GameCondition& condition, Position position);
public:
    IngameAI(uint8_t foresightCount, const GameScene& scene);
    void calculatePosition();
    void setDifficulty(uint8_t foresightCount);
    void abort();
signals:
    void positionCalculated(Position position);
};

#endif // IngameAI_H
