cmake_minimum_required(VERSION 3.16)
project(etat_civil CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Avertissements utiles (equivalent de -Wall -Wextra -pedantic)
if(NOT MSVC)
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_executable(etat_civil
        main.cpp
        Personne.cpp
        Usager.cpp
        AgentEtatCivil.cpp
        OfficierEtatCivil.cpp
        AgentStagiaire.cpp
        CentreEtatCivil.cpp
        ActeCivil.cpp
        DemandeActe.cpp
        DossierEtatCivil.cpp
        GestionEtatCivil.cpp
)
