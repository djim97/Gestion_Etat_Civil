#ifndef AGENT_ETAT_CIVIL_HPP
#define AGENT_ETAT_CIVIL_HPP

#include "Personne.hpp"

// Agent de base charge de traiter les demandes.
// Sert de base polymorphique aux agents specialises.
class AgentEtatCivil : public Personne {
protected:
    std::string m_matricule;
    std::string m_service;
    double      m_salaireBase;

public:
    AgentEtatCivil();
    AgentEtatCivil(int id, const std::string& nom, const std::string& prenom,
                   const std::string& telephone, const std::string& matricule,
                   const std::string& service, double salaireBase);

    void afficher(std::ostream& os) const override;

    // Methode virtuelle : prime de base = nbActes * 500.
    virtual double calculerPrime(int nbActes) const;

    // Accesseurs
    const std::string& matricule()   const { return m_matricule; }
    const std::string& service()     const { return m_service; }
    double             salaireBase() const { return m_salaireBase; }

    // Mutateurs avec validation
    void setMatricule(const std::string& matricule);
    void setService(const std::string& service);
    void setSalaireBase(double salaireBase);

    friend std::istream& operator>>(std::istream& is, AgentEtatCivil& a);
};

#endif // AGENT_ETAT_CIVIL_HPP
