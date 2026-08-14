#include "OfficierEtatCivil.hpp"
#include <stdexcept>

OfficierEtatCivil::OfficierEtatCivil()
    : AgentEtatCivil(), m_grade(), m_primeSignature(0.0) {}

OfficierEtatCivil::OfficierEtatCivil(int id, const std::string& nom, const std::string& prenom,
                                     const std::string& telephone, const std::string& matricule,
                                     const std::string& service, double salaireBase,
                                     const std::string& grade, double primeSignature)
    : AgentEtatCivil(id, nom, prenom, telephone, matricule, service, salaireBase),
      m_grade(), m_primeSignature(0.0) {
    setGrade(grade);
    setPrimeSignature(primeSignature);
}

double OfficierEtatCivil::calculerPrime(int nbActes) const {
    // Prime de base (heritee) + prime fixe de signature.
    return AgentEtatCivil::calculerPrime(nbActes) + m_primeSignature;
}

void OfficierEtatCivil::setGrade(const std::string& grade) {
    if (grade.empty())
        throw std::invalid_argument("OfficierEtatCivil : le grade ne doit pas etre vide.");
    m_grade = grade;
}

void OfficierEtatCivil::setPrimeSignature(double primeSignature) {
    if (primeSignature < 0)
        throw std::invalid_argument("OfficierEtatCivil : primeSignature doit etre >= 0.");
    m_primeSignature = primeSignature;
}

void OfficierEtatCivil::afficher(std::ostream& os) const {
    os << "Officier #" << m_id << " | " << m_prenom << " " << m_nom
       << " | Matricule: " << m_matricule
       << " | Grade: " << m_grade
       << " | Prime signature: " << m_primeSignature
       << " | Salaire base: " << m_salaireBase;
}

std::istream& operator>>(std::istream& is, OfficierEtatCivil& o) {
    int id;
    double salaire, prime;
    std::string nom, prenom, tel, matricule, service, grade;

    std::cout << "  id            : "; is >> id;          is.ignore();
    std::cout << "  nom           : "; std::getline(is, nom);
    std::cout << "  prenom        : "; std::getline(is, prenom);
    std::cout << "  telephone     : "; std::getline(is, tel);
    std::cout << "  matricule     : "; std::getline(is, matricule);
    std::cout << "  service       : "; std::getline(is, service);
    std::cout << "  salaire base  : "; is >> salaire;     is.ignore();
    std::cout << "  grade         : "; std::getline(is, grade);
    std::cout << "  prime signature:"; is >> prime;       is.ignore();

    o.setId(id);
    o.setNom(nom);
    o.setPrenom(prenom);
    o.setTelephone(tel);
    o.setMatricule(matricule);
    o.setService(service);
    o.setSalaireBase(salaire);
    o.setGrade(grade);
    o.setPrimeSignature(prime);
    return is;
}
