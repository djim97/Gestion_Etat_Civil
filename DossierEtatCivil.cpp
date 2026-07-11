#include "DossierEtatCivil.hpp"
#include <stdexcept>

DossierEtatCivil::DossierEtatCivil(int id, std::shared_ptr<DemandeActe> demande,
                                   std::shared_ptr<AgentEtatCivil> agent, int delaiTraitementJours)
    : m_id(id), m_demande(demande), m_agent(agent),
      m_delaiTraitementJours(delaiTraitementJours) {
    if (id <= 0)
        throw std::invalid_argument("DossierEtatCivil : l'id doit etre > 0.");
    if (!demande || !agent)
        throw std::invalid_argument("DossierEtatCivil : demande et agent ne doivent pas etre nullptr.");
    if (delaiTraitementJours < 0)
        throw std::invalid_argument("DossierEtatCivil : delaiTraitementJours doit etre >= 0.");
}

double DossierEtatCivil::calculerCoutTotal() const {
    // Appel polymorphe a calculerPrime() : la bonne surcharge est choisie
    // selon le type reel de l'agent (Officier ou Stagiaire).
    return m_demande->calculerMontant() + m_agent->calculerPrime(1);
}

std::ostream& operator<<(std::ostream& os, const DossierEtatCivil& d) {
    os << "===== DOSSIER FINALISE #" << d.id() << " =====\n"
       << "  " << *d.demande() << "\n"
       << "  Agent traitant  : " << d.agent()->prenom() << " " << d.agent()->nom()
       << " (#" << d.agent()->id() << ")\n"
       << "  Delai (jours)   : " << d.delaiTraitementJours() << "\n"
       << "  COUT TOTAL      : " << d.calculerCoutTotal();
    return os;
}