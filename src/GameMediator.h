//
// Created by ilyab on 21.09.2022.
//

#ifndef GAME_GAMEMEDIATOR_H
#define GAME_GAMEMEDIATOR_H

class GameMediator;

#include <string>
#include <iostream>
#include "view/ViewController.h"
#include "kernel/KernelController.h"
#include "events/EventsController.h"
#include "Point.h"
#include "mapmaker/MapMaker.h"
#include "GameStateController.h"
#include "logger/LoggerController.h"

class GameMediator {
public:
    void init(
            kernel::KernelController *, view::ViewController *, mapmaker::MapMaker *, events::EventsController *,
            logger::LoggerController *
    );

    void update();

    events::EventsController *getEventsController();

    const kernel::IField *readField() const;

    kernel::IField *getField();

    void movePlayer(kernel::ICreature::Direction direction);

    kernel::ICreature *getPlayer();

    std::vector<kernel::ICreature *> getCreatures();

    void setField(kernel::IField *field);

    GameStateController::State getState();

    void setState(GameStateController::State state);

    IGameState *getStateController();

    std::string askUser(const std::string &question, const std::vector<std::string> &answers);

    void addCellEvent(
            Point point, events::EventChainLink *event, kernel::Cell::Tileset tileset = kernel::Cell::Tileset::GRASS
    );

    mapmaker::MapMaker *getMapMaker();

    ~GameMediator();

protected:
    kernel::KernelController *kernel_controller_ = nullptr;
    view::ViewController *view_controller_ = nullptr;
    mapmaker::MapMaker *map_maker_ = nullptr;
    events::EventsController *events_controller_ = nullptr;
    logger::LoggerController *logger_controller_ = nullptr;
    IGameState *game_state_controller_ = nullptr;
};


#endif //GAME_GAMEMEDIATOR_H