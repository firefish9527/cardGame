#include "GameModelFromLevelGenerator.h"
#include "models/CardModel.h"

GameModel* GameModelFromLevelGenerator::generate(const LevelConfig& config)
{
    auto kGameModel = GameModel::create();
    if (!kGameModel) return nullptr;

    for (const auto& kCfg : config.playfieldCards) 
    {
        auto kCard = new (std::nothrow) CardModel(
            static_cast<CardModel::FaceType>(kCfg.cardFace),
            static_cast<CardModel::SuitType>(kCfg.cardSuit),
            kCfg.position);
        kCard->area = CardModel::PlayField;
        kCard->autorelease();
        kGameModel->addChild(kCard);
        kGameModel->playfieldCards.pushBack(kCard);
    }
    for (const auto& kCfg : config.stackCards)
    {
        auto kCard = new (std::nothrow) CardModel(
            static_cast<CardModel::FaceType>(kCfg.cardFace),
            static_cast<CardModel::SuitType>(kCfg.cardSuit),
            kCfg.position);
        kCard->area = CardModel::Stack;   
        kCard->autorelease();
        kGameModel->addChild(kCard);
        kGameModel->stackCards.pushBack(kCard);
    }
    return kGameModel;
}