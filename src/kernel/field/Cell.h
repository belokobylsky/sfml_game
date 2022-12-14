//
// Created by ilyab on 17.09.2022.
//

#ifndef GAME_CELL_H
#define GAME_CELL_H

#include "../../events/EventChainLink.h"
#include "../../Point.h"

namespace kernel {
    class Cell {
    public:
        enum class Tileset {
            GRASS, HOLE, ROCK, WATER_GLARE, WATER_LILY, WATER_FISH, BUTTON,
            FENCE_VERTICAL, FENCE_HORIZONTAL, SMALL_IRON_PILLAR, AID_KIT,
            TORII, TUNNEL, TREE_OAK, TREE_SPRUCE
        };

        explicit Cell(Point point, bool passable = true);

        Cell(const Cell &cell);

        Cell &operator=(const Cell &obj) = default;

        void addListener(events::EventChainLink *listener, bool delete_previous = true);

        events::EventChainLink *getListener();

        void changeState(bool passable);

        Tileset getTileset() const;

        void setTileset(Tileset tileset);

        bool isPassable() const;

        void dispatchListener();

        void removeListener();

        Point getPoint() const;

        ~Cell();

    protected:
        Point point_;
        bool passable_;
        Tileset tileset_;
        events::EventChainLink *listener_;
    };
}


#endif //GAME_CELL_H
