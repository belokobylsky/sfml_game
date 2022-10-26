//
// Created by ilyab on 21.09.2022.
//

#include "GameMediator.h"

void GameMediator::init(
        kernel::KernelController *kernel_controller, view::ViewController *view_controller,
        mapmaker::MapMaker *map_maker, events::EventsController *events_controller,
        logger::LoggerController *logger_controller
) {
    kernel_controller_ = kernel_controller;
    view_controller_ = view_controller;
    map_maker_ = map_maker;
    events_controller_ = events_controller;
    logger_controller_ = logger_controller;

    game_state_controller_ = logger_controller_->getProxy(new GameStateController);
    game_state_controller_->setState(IGameState::State::START);
    kernel_controller_->setPlayer(
            logger_controller_->getProxy(kernel_controller_->getPlayer()),
            false
    );
}

const kernel::IField *GameMediator::readField() const {
    return kernel_controller_->getField();
}

kernel::ICreature *GameMediator::getPlayer() {
    return kernel_controller_->getPlayer();
}

std::vector<kernel::ICreature *> GameMediator::getCreatures() {
    return kernel_controller_->getCreatureManager()->getAllCreatures();
}

void GameMediator::movePlayer(kernel::ICreature::Direction direction) {
    kernel::ICreature *player = kernel_controller_->getPlayer();
    Point pos = player->getPoint();
    switch (direction) {
        case kernel::ICreature::Direction::UP:
            pos.y--;
            break;
        case kernel::ICreature::Direction::LEFT:
            pos.x--;
            break;
        case kernel::ICreature::Direction::DOWN:
            pos.y++;
            break;
        case kernel::ICreature::Direction::RIGHT:
            pos.x++;
            break;
        default:
            return;
    }
    try {
        kernel_controller_->moveCreature(player, pos);
    } catch (std::exception &e) {
        logger_controller_->catchException(e);
    }
    kernel_controller_->rotateCreature(player, direction);
}

kernel::IField *GameMediator::getField() {
    return kernel_controller_->getField();
}

events::EventsController *GameMediator::getEventsController() {
    return events_controller_;
}

void GameMediator::update() {
    kernel_controller_->update();
}

GameStateController::State GameMediator::getState() {
    return game_state_controller_->getState();
}

IGameState *GameMediator::getStateController() {
    return game_state_controller_;
}

void GameMediator::setState(GameStateController::State state) {
    game_state_controller_->setState(state);
}

void GameMediator::setField(kernel::IField *field) {
    kernel_controller_->setField(logger_controller_->getProxy(field));
}

std::string GameMediator::askUser(const std::string &question, const std::vector<std::string> &answers) {
    return view_controller_->ask(question, answers);
}

void GameMediator::addCellEvent(Point point, events::EventChainLink *event, kernel::Cell::Tileset tileset) {
    kernel::Cell *cell = kernel_controller_->getField()->getCell(point);
    cell->addListener(logger_controller_->getProxy(event));
    cell->setTileset(tileset);
}

mapmaker::MapMaker *GameMediator::getMapMaker() {
    return map_maker_;
}

GameMediator::~GameMediator() {
    delete game_state_controller_;
}