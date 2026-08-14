#ifndef GESTION_ETAT_CIVIL_HPP
#define GESTION_ETAT_CIVIL_HPP

#include "Usager.hpp"
#include "AgentEtatCivil.hpp"
#include "CentreEtatCivil.hpp"
#include "ActeCivil.hpp"
#include "DemandeActe.hpp"
#include "DossierEtatCivil.hpp"
#include <memory>
#include <vector>
#include <string>

// Classe principale qui gere tous les objets du systeme.
class GestionEtatCivil {
private:
    std::string m_nomInstitution;

    // Compteur pour attribuer automatiquement un id unique a chaque usager.
    int m_prochainIdUsager;

    std::vector<std::shared_ptr<Usager>>          m_usagers;
    std::vector<std::shared_ptr<AgentEtatCivil>>  m_agents;   // polymorphique
    std::vector<std::shared_ptr<CentreEtatCivil>> m_centres;
    std::vector<std::shared_ptr<ActeCivil>>       m_actes;
    std::vector<std::shared_ptr<DemandeActe>>     m_demandes;
    std::vector<std::shared_ptr<DossierEtatCivil>> m_dossiers;

public:
    explicit GestionEtatCivil(const std::string& nomInstitution);

    const std::string& nomInstitution() const { return m_nomInstitution; }

    // Gestion des usagers
    void                    ajouterUsager(std::shared_ptr<Usager> u);
    std::shared_ptr<Usager> trouverUsager(int id) const;   // lance si introuvable
    void                    supprimerUsager(int id);

    // Gestion des agents (polymorphisme)
    void                            ajouterAgent(std::shared_ptr<AgentEtatCivil> a);
    std::shared_ptr<AgentEtatCivil> trouverAgent(int id) const;

    // Gestion des centres
    void                             ajouterCentre(std::shared_ptr<CentreEtatCivil> c);
    std::shared_ptr<CentreEtatCivil> trouverCentre(int id) const;

    // Gestion des actes
    void                       ajouterActe(std::shared_ptr<ActeCivil> a);
    std::shared_ptr<ActeCivil> trouverActe(int id) const;

    // Gestion des demandes
    void                         ajouterDemande(std::shared_ptr<DemandeActe> d);
    std::shared_ptr<DemandeActe> trouverDemande(int id) const;

    // Gestion des dossiers
    void ajouterDossier(std::shared_ptr<DossierEtatCivil> d);

    // Affiche chaque agent de maniere polymorphique.
    void afficherTousAgents() const;

    const std::vector<std::shared_ptr<CentreEtatCivil>>& centres() const { return m_centres; }
    const std::vector<std::shared_ptr<ActeCivil>>&       actes()   const { return m_actes; }
    const std::vector<std::shared_ptr<AgentEtatCivil>>&  agents()  const { return m_agents; }

    // Operateurs
    // []  : retourne un usager par son id.
    std::shared_ptr<Usager>         operator[](int id) const;
    // ()  : retourne un agent par son id.
    std::shared_ptr<AgentEtatCivil> operator()(int id) const;

    friend std::ostream& operator<<(std::ostream& os, const GestionEtatCivil& g);
};

#endif // GESTION_ETAT_CIVIL_HPP