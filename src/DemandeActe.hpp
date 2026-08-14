#ifndef DEMANDE_ACTE_HPP
#define DEMANDE_ACTE_HPP

#include "Usager.hpp"
#include "CentreEtatCivil.hpp"
#include "ActeCivil.hpp"
#include <memory>
#include <string>

// Etat d'avancement d'une demande.
enum class StatutDemande { EN_ATTENTE, VALIDEE, REJETEE, DELIVREE };
std::string statutVersTexte(StatutDemande s);

// Demande deposee par un usager pour obtenir un acte civil.
class DemandeActe {
private:
    int                              m_id;
    std::shared_ptr<Usager>          m_usager;
    std::shared_ptr<CentreEtatCivil> m_centre;
    std::shared_ptr<ActeCivil>       m_acte;
    int                              m_nombreCopies;
    StatutDemande                    m_statut;

public:
    DemandeActe(int id, std::shared_ptr<Usager> usager,
                std::shared_ptr<CentreEtatCivil> centre,
                std::shared_ptr<ActeCivil> acte, int nombreCopies);

    // Frais de l'acte selon le nombre de copies.
    double calculerMontant() const;

    void valider();
    void rejeter();
    void delivrer();

    int                              id()           const { return m_id; }
    StatutDemande                    statut()       const { return m_statut; }
    int                              nombreCopies() const { return m_nombreCopies; }
    std::shared_ptr<Usager>          usager()       const { return m_usager; }
    std::shared_ptr<CentreEtatCivil> centre()       const { return m_centre; }
    std::shared_ptr<ActeCivil>       acte()         const { return m_acte; }

    bool operator==(const DemandeActe& autre) const { return m_id == autre.m_id; }
};

// Affichage via les accesseurs publics (id(), usager(), statut()...) :
// operator<< n'a plus besoin d'etre friend, l'encapsulation est preservee.
std::ostream& operator<<(std::ostream& os, const DemandeActe& d);

#endif // DEMANDE_ACTE_HPP