#include "AgentEtatCivil.hpp"
#include <stdexcept>

AgentEtatCivil::AgentEtatCivil()
    : Personne(), m_matricule(), m_service(), m_salaireBase(1.0) {}

AgentEtatCivil::AgentEtatCivil(int id, const std::string& nom, const std::string& prenom,
                               const std::string& telephone, const std::string& matricule,
                               const std::string& service, double salaireBase)
    : Personne(id, nom, prenom, telephone),
      m_matricule(), m_service(), m_salaireBase(1.0) {
    setMatricule(matricule);
    setService(service);
    setSalaireBase(salaireBase);
}

double AgentEtatCivil::calculerPrime(int nbActes) const {
    if (nbActes < 0)
        throw std::invalid_argument("AgentEtatCivil : nbActes ne doit pas etre negatif.");
    return nbActes * 500.0;
}

void AgentEtatCivil::setMatricule(const std::string& matricule) {
    if (matricule.empty())
        throw std::invalid_argument("AgentEtatCivil : le matricule ne doit pas etre vide.");
    m_matricule = matricule;
}

void AgentEtatCivil::setService(const std::string& service) {
    if (service.empty())
        throw std::invalid_argument("AgentEtatCivil : le service ne doit pas etre vide.");
    m_service = service;
}

void AgentEtatCivil::setSalaireBase(double salaireBase) {
    if (salaireBase <= 0)
        throw std::invalid_argument("AgentEtatCivil : le salaireBase doit etre strictement positif.");
    m_salaireBase = salaireBase;
}

void AgentEtatCivil::afficher(std::ostream& os) const {
    os << "Agent #" << m_id << " | " << m_prenom << " " << m_nom
       << " | Matricule: " << m_matricule
       << " | Service: " << m_service
       << " | Salaire base: " << m_salaireBase;
}

std::istream& operator>>(std::istream& is, AgentEtatCivil& a) {
    int id;
    double salaire;
    std::string nom, prenom, tel, matricule, service;

    std::cout << "  id          : "; is >> id;            is.ignore();
    std::cout << "  nom         : "; std::getline(is, nom);
    std::cout << "  prenom      : "; std::getline(is, prenom);
    std::cout << "  telephone   : "; std::getline(is, tel);
    std::cout << "  matricule   : "; std::getline(is, matricule);
    std::cout << "  service     : "; std::getline(is, service);
    std::cout << "  salaire base: "; is >> salaire;       is.ignore();

    a.setId(id);
    a.setNom(nom);
    a.setPrenom(prenom);
    a.setTelephone(tel);
    a.setMatricule(matricule);
    a.setService(service);
    a.setSalaireBase(salaire);
    return is;
}
