#ifndef AGENT_STAGIAIRE_HPP
#define AGENT_STAGIAIRE_HPP

#include "AgentEtatCivil.hpp"
#include <memory>

// Agent en formation encadre par un officier ou un agent experimente.
class AgentStagiaire : public AgentEtatCivil {
private:
    std::shared_ptr<AgentEtatCivil> m_encadreur;
    double                          m_coefficientPrime; // entre 0 et 1

public:
    AgentStagiaire();
    AgentStagiaire(int id, const std::string& nom, const std::string& prenom,
                   const std::string& telephone, const std::string& matricule,
                   const std::string& service, double salaireBase,
                   std::shared_ptr<AgentEtatCivil> encadreur, double coefficientPrime);

    void afficher(std::ostream& os) const override;

    // Applique le coefficient a la prime de base.
    double calculerPrime(int nbActes) const override;

    std::shared_ptr<AgentEtatCivil> encadreur()        const { return m_encadreur; }
    double                          coefficientPrime() const { return m_coefficientPrime; }

    void setEncadreur(std::shared_ptr<AgentEtatCivil> encadreur);
    void setCoefficientPrime(double coefficientPrime);

    // Saisit le stagiaire SAUF le pointeur encadreur (affecte depuis le main).
    friend std::istream& operator>>(std::istream& is, AgentStagiaire& s);
};

#endif // AGENT_STAGIAIRE_HPP
