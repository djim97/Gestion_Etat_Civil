#include "Personne.hpp"
#include <stdexcept>

Personne::Personne()
    : m_id(0), m_nom(), m_prenom(), m_telephone() {}

Personne::Personne(int id, const std::string& nom,
                   const std::string& prenom, const std::string& telephone)
    : m_id(0), m_nom(), m_prenom(), m_telephone() {
    setId(id);
    setNom(nom);
    setPrenom(prenom);
    setTelephone(telephone);
}

void Personne::setId(int id) {
    if (id <= 0)
        throw std::invalid_argument("Personne : l'id doit etre strictement superieur a 0.");
    m_id = id;
}

void Personne::setNom(const std::string& nom) {
    if (nom.empty())
        throw std::invalid_argument("Personne : le nom ne doit pas etre vide.");
    m_nom = nom;
}

void Personne::setPrenom(const std::string& prenom) {
    if (prenom.empty())
        throw std::invalid_argument("Personne : le prenom ne doit pas etre vide.");
    m_prenom = prenom;
}

void Personne::setTelephone(const std::string& telephone) {
    if (telephone.empty())
        throw std::invalid_argument("Personne : le telephone ne doit pas etre vide.");
    m_telephone = telephone;
}

std::ostream& operator<<(std::ostream& os, const Personne& p) {
    p.afficher(os);
    return os;
}
