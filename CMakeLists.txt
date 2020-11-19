cmake_minimum_required(VERSION 3.17)
project(comp345_risk_copy)

set(CMAKE_CXX_STANDARD 17)

include_directories(headers)
include_directories(src)

add_executable(comp345_risk_copy
        headers/Cards.h
        headers/Map.h
        headers/MapLoader.h
        headers/Orders.h
        headers/Player.h
        headers/GameObservers.h
        maps/brasilBadMap.map
        maps/cologne.map
        maps/europass.map
        maps/europe.map
        maps/germany2.map
        maps/kosova.map
        maps/middleearth.map
        maps/solar.map
        maps/trivia.map
        src/Cards.cpp
        src/CardsDriver.cpp
        src/GameObservers.cpp
        src/main.cpp
        src/Map.cpp
        src/MapDriver.cpp
        src/MapLoader.cpp
        src/MapLoaderDriver.cpp
        src/Orders.cpp
        src/OrdersDriver.cpp
        src/Player.cpp
        src/PlayerDriver.cpp src/Observer.cpp headers/Observer.h src/Subject.cpp headers/Subject.h src/Controller.cpp headers/Controller.h)
