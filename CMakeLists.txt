cmake_minimum_required(VERSION 3.30)
project(SchottenTotten_CPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(SchottenTotten_CPP main.cpp
Cards/Cards.h
Cards/ClanCards.cpp
Cards/ClanCards.h
        Collections/Set.cpp
        Collections/Set.h
Colors.h
Cards/ShieldBear.h
Cards/Joker.h
Cards/Spy.h
Cards/RusesCards.h
Cards/MudFight.h
Cards/BlindMan.h
Cards/Banshee.h
Cards/Traitor.h
        Rules/Rules.cpp
Rules/Rules.h
StoneTiles/StoneTiles.cpp
StoneTiles/StoneTiles.h
        Display/Display.h
        Display/DisplayConsole.cpp
        Display/DisplayConsole.h
        Factory/TacticalCardsFactory.h
        Cards/Stratege.cpp
        Cards/Stratege.h
        Player/Player.h
        Player/Player.cpp
        Player/Human.h
        Player/Human.cpp
        Player/AI.h
        Player/AIEasy.cpp
        Player/AIEasy.h
        Cards/Joker.cpp
        GameBoard/GameBoard.cpp
        Display/DisplayManager.h
        Display/DisplayManager.cpp
        Cards/Joker.cpp
        GameBoard/GameBoard.h
        GameBoard/GameBoard.cpp
        Cards/Traitor.cpp
        Cards/Banshee.cpp
Cards/tacticalCards.cpp
Cards/RusesCards.cpp
Cards/Recruiter.h
Cards/Recruiter.cpp
        Cards/Spy.cpp
Logic/GameLogic.h
Logic/GameLogic.cpp
        Cards/ShieldBear.cpp
        CustomException/CustomException.h
        Cards/BlindMan.cpp)
