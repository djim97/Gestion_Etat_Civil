#include "DemandeActe.hpp"
#include <stdexcept>

std::string statutVersTexte(StatutDemande s) {
    switch (s) {
        case StatutDemande::EN_ATTENTE: return "EN_ATTENTE";
        case StatutDemande::VALIDEE:    return "VALIDEE";
        case StatutDemande::REJETEE:    return "REJETEE";
        case StatutDemande::DELIVREE:   return "DELIVREE";
    }
    return "INCONNU";
}

DemandeActe::DemandeActe(int id, std::shared_ptr<Usager> usager,
                         std::shared_ptr<CentreEtatCivil> centre,
                         std::shared_ptr<ActeCivil> acte, int nombreCopies)
    : m_id(id), m_usager(usager), m_centre(centre), m_acte(acte),
      m_nombreCopies(nombreCopies), m_statut(StatutDemande::EN_ATTENTE) {
    if (id <= 0)
        throw std::invalid_argument("DemandeActe : l'id doit etre > 0.");
    if (!usager || !centre || !acte)
        throw std::invalid_argument("DemandeActe : usager, centre et acte ne doivent pas etre nullptr.");
    if (nombreCopies <= 0)
        throw std::invalid_argument("DemandeActe : le nombre de copies doit etre > 0.");
}

double DemandeActe::calculerMontant() const {
    return m_acte->calculerFrais(m_nombreCopies);
}

void DemandeActe::valider()  { m_statut = StatutDemande::VALIDEE; }
void DemandeActe::rejeter()  { m_statut = StatutDemande::REJETEE; }

void DemandeActe::delivrer() {
    if (m_statut != StatutDemande::VALIDEE)
        throw std::runtime_error("DemandeActe : la demande doit etre VALIDEE avant d'etre DELIVREE.");
    m_statut = StatutDemande::DELIVREE;
    m_acte->marquerDelivre();
}

std::ostream& operator<<(std::ostream& os, const DemandeActe& d) {
    // Utilise uniquement les accesseurs publics : aucun besoin d'etre friend.
    os << "Demande #" << d.id()
       << " | Usager: " << d.usager()->prenom() << " " << d.usager()->nom()
       << " | Centre: " << d.centre()->nom()
       << " | Acte: " << d.acte()->type()
       << " | Copies: " << d.nombreCopies()
       << " | Statut: " << statutVersTexte(d.statut())
       << " | Montant: " << d.calculerMontant();
    return os;
}