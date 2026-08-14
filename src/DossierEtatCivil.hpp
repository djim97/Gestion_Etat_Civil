#ifndef DOSSIER_ETAT_CIVIL_HPP
#define DOSSIER_ETAT_CIVIL_HPP

#include "DemandeActe.hpp"
#include "AgentEtatCivil.hpp"
#include <memory>

// Dossier finalise, traite par un agent et lie a une demande.
// Classe final : elle ne peut pas etre derivee.
class DossierEtatCivil final {
private:
    int                             m_id;
    std::shared_ptr<DemandeActe>    m_demande;
    std::shared_ptr<AgentEtatCivil> m_agent;
    int                             m_delaiTraitementJours;

public:
    DossierEtatCivil(int id, std::shared_ptr<DemandeActe> demande,
                     std::shared_ptr<AgentEtatCivil> agent, int delaiTraitementJours);

    // Montant de la demande + prime de l'agent (polymorphe) pour 1 acte traite.
    double calculerCoutTotal() const;

    int id()                   const { return m_id; }
    int delaiTraitementJours() const { return m_delaiTraitementJours; }
    std::shared_ptr<DemandeActe>    demande() const { return m_demande; }
    std::shared_ptr<AgentEtatCivil> agent()   const { return m_agent; }
};

// Affichage via les accesseurs publics : pas besoin de friend.
std::ostream& operator<<(std::ostream& os, const DossierEtatCivil& d);

#endif // DOSSIER_ETAT_CIVIL_HPP