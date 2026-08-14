cmake_minimum_required(VERSION 3.16)
project(etat_civil CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MSVC)
    add_compile_options(-Wall -Wextra -pedantic)
endif()

include_directories(include)

add_executable(etat_civil
        src/main.cpp
        src/Personne.cpp
        src/Usager.cpp
        src/AgentEtatCivil.cpp
        src/OfficierEtatCivil.cpp
        src/AgentStagiaire.cpp
        src/CentreEtatCivil.cpp
        src/ActeCivil.cpp
        src/DemandeActe.cpp
        src/DossierEtatCivil.cpp
        src/GestionEtatCivil.cpp
)
