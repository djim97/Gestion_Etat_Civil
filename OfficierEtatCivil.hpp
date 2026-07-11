#ifndef OFFICIER_ETAT_CIVIL_HPP
#define OFFICIER_ETAT_CIVIL_HPP

#include "AgentEtatCivil.hpp"

// Agent habilite a valider et signer officiellement les actes.
class OfficierEtatCivil : public AgentEtatCivil {
private:
    std::string m_grade;
    double      m_primeSignature;

public:
    OfficierEtatCivil();
    OfficierEtatCivil(int id, const std::string& nom, const std::string& prenom,
                      const std::string& telephone, const std::string& matricule,
                      const std::string& service, double salaireBase,
                      const std::string& grade, double primeSignature);

    void afficher(std::ostream& os) const override;

    // Ajoute la prime de signature a la prime de base.
    double calculerPrime(int nbActes) const override;

    const std::string& grade()          const { return m_grade; }
    double             primeSignature() const { return m_primeSignature; }

    void setGrade(const std::string& grade);
    void setPrimeSignature(double primeSignature);

    friend std::istream& operator>>(std::istream& is, OfficierEtatCivil& o);
};

#endif // OFFICIER_ETAT_CIVIL_HPP
