#include "AgentStagiaire.hpp"
#include <stdexcept>

AgentStagiaire::AgentStagiaire()
    : AgentEtatCivil(), m_encadreur(nullptr), m_coefficientPrime(0.5) {}

AgentStagiaire::AgentStagiaire(int id, const std::string& nom, const std::string& prenom,
                               const std::string& telephone, const std::string& matricule,
                               const std::string& service, double salaireBase,
                               std::shared_ptr<AgentEtatCivil> encadreur, double coefficientPrime)
    : AgentEtatCivil(id, nom, prenom, telephone, matricule, service, salaireBase),
      m_encadreur(nullptr), m_coefficientPrime(0.5) {
    setEncadreur(encadreur);
    setCoefficientPrime(coefficientPrime);
}

double AgentStagiaire::calculerPrime(int nbActes) const {
    // Prime de base * coefficient reduit.
    return AgentEtatCivil::calculerPrime(nbActes) * m_coefficientPrime;
}

void AgentStagiaire::setEncadreur(std::shared_ptr<AgentEtatCivil> encadreur) {
    if (!encadreur)
        throw std::invalid_argument("AgentStagiaire : l'encadreur ne doit pas etre nullptr.");
    m_encadreur = encadreur;
}

void AgentStagiaire::setCoefficientPrime(double coefficientPrime) {
    if (coefficientPrime < 0.0 || coefficientPrime > 1.0)
        throw std::invalid_argument("AgentStagiaire : coefficientPrime doit etre compris entre 0 et 1.");
    m_coefficientPrime = coefficientPrime;
}

void AgentStagiaire::afficher(std::ostream& os) const {
    os << "Stagiaire #" << m_id << " | " << m_prenom << " " << m_nom
       << " | Matricule: " << m_matricule
       << " | Service: " << m_service
       << " | Coef prime: " << m_coefficientPrime
       << " | Encadreur: ";
    if (m_encadreur)
        os << m_encadreur->prenom() << " " << m_encadreur->nom()
           << " (#" << m_encadreur->id() << ")";
    else
        os << "aucun";
}

std::istream& operator>>(std::istream& is, AgentStagiaire& s) {
    int id;
    double salaire, coef;
    std::string nom, prenom, tel, matricule, service;

    std::cout << "  id           : "; is >> id;         is.ignore();
    std::cout << "  nom          : "; std::getline(is, nom);
    std::cout << "  prenom       : "; std::getline(is, prenom);
    std::cout << "  telephone    : "; std::getline(is, tel);
    std::cout << "  matricule    : "; std::getline(is, matricule);
    std::cout << "  service      : "; std::getline(is, service);
    std::cout << "  salaire base : "; is >> salaire;    is.ignore();
    std::cout << "  coef prime   : "; is >> coef;       is.ignore();

    s.setId(id);
    s.setNom(nom);
    s.setPrenom(prenom);
    s.setTelephone(tel);
    s.setMatricule(matricule);
    s.setService(service);
    s.setSalaireBase(salaire);
    s.setCoefficientPrime(coef);
    // L'encadreur est affecte depuis le main via setEncadreur().
    return is;
}
