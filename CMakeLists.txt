cmake_minimum_required(VERSION 3.30)
project(SchottenTotten_CPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(SchottenTotten_CPP main.cpp
        Colors.h
        Cards/ShieldBear.h
        Cards/Joker.h
        Cards/Spy.h
        Cards/RusesCards.h
        Cards/MudFight.h
        Cards/BlindMan.h
        Cards/Banshee.h
        Cards/Traitor.h
        Cards/HeadsHunter.h)
