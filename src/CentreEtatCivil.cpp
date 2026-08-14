#include "CentreEtatCivil.hpp"
#include <stdexcept>

CentreEtatCivil::CentreEtatCivil()
    : m_id(0), m_nom(), m_commune(), m_adresse() {}

CentreEtatCivil::CentreEtatCivil(int id, const std::string& nom,
                                 const std::string& commune, const std::string& adresse)
    : m_id(0), m_nom(), m_commune(), m_adresse() {
    setId(id);
    setNom(nom);
    setCommune(commune);
    setAdresse(adresse);
}

void CentreEtatCivil::setId(int id) {
    if (id <= 0)
        throw std::invalid_argument("CentreEtatCivil : l'id doit etre > 0.");
    m_id = id;
}

void CentreEtatCivil::setNom(const std::string& nom) {
    if (nom.empty())
        throw std::invalid_argument("CentreEtatCivil : le nom ne doit pas etre vide.");
    m_nom = nom;
}

void CentreEtatCivil::setCommune(const std::string& commune) {
    if (commune.empty())
        throw std::invalid_argument("CentreEtatCivil : la commune ne doit pas etre vide.");
    m_commune = commune;
}

void CentreEtatCivil::setAdresse(const std::string& adresse) {
    if (adresse.empty())
        throw std::invalid_argument("CentreEtatCivil : l'adresse ne doit pas etre vide.");
    m_adresse = adresse;
}

std::ostream& operator<<(std::ostream& os, const CentreEtatCivil& c) {
    os << "Centre #" << c.id() << " | " << c.nom()
       << " | Commune: " << c.commune()
       << " | Adresse: " << c.adresse();
    return os;
}

std::istream& operator>>(std::istream& is, CentreEtatCivil& c) {
    int id;
    std::string nom, commune, adresse;

    std::cout << "  id      : "; is >> id;   is.ignore();
    std::cout << "  nom     : "; std::getline(is, nom);
    std::cout << "  commune : "; std::getline(is, commune);
    std::cout << "  adresse : "; std::getline(is, adresse);

    c.setId(id);
    c.setNom(nom);
    c.setCommune(commune);
    c.setAdresse(adresse);
    return is;
}