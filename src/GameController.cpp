//
// Created by ilyab on 11.10.2022.
//

#include "GameController.h"
#include <iostream>

GameController::GameController() {
    game_mediator_ = new GameMediator;
    kernel_controller_ = new kernel::KernelController(game_mediator_);
    view_controller_ = new view::ViewController(game_mediator_);
    map_maker_ = new mapmaker::MapMaker(game_mediator_);
    events_controller_ = new events::EventsController(game_mediator_);
    logger_controller_ = new logger::LoggerController(game_mediator_);
}

void GameController::start() {
    logger_controller_->startLogging();
    try {
        game_mediator_->init(
                kernel_controller_, view_controller_, map_maker_,
                events_controller_, logger_controller_
        );
        map_maker_->generate();
    } catch (std::exception &e) {
        logger_controller_->catchException(e);
        game_mediator_->setField(new kernel::Field);
    }
    view_controller_->start();
}

GameController::~GameController() {
    delete game_mediator_;
    delete kernel_controller_;
    delete view_controller_;
    delete map_maker_;
    delete events_controller_;
    delete logger_controller_;
}