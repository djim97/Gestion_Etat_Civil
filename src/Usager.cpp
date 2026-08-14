#include "Usager.hpp"
#include <stdexcept>

Usager::Usager()
    : Personne(), m_adresse(), m_numeroCNI(), m_nombreDemandes(0) {}

Usager::Usager(int id, const std::string& nom, const std::string& prenom,
               const std::string& telephone, const std::string& adresse,
               const std::string& numeroCNI, int nombreDemandes)
    : Personne(id, nom, prenom, telephone),
      m_adresse(), m_numeroCNI(), m_nombreDemandes(0) {
    setAdresse(adresse);
    setNumeroCNI(numeroCNI);
    if (nombreDemandes < 0)
        throw std::invalid_argument("Usager : nombreDemandes ne doit jamais etre negatif.");
    m_nombreDemandes = nombreDemandes;
}

void Usager::incrementerDemandes() {
    ++m_nombreDemandes;
}

void Usager::setAdresse(const std::string& adresse) {
    if (adresse.empty())
        throw std::invalid_argument("Usager : l'adresse ne doit pas etre vide.");
    m_adresse = adresse;
}

void Usager::setNumeroCNI(const std::string& numeroCNI) {
    if (numeroCNI.empty())
        throw std::invalid_argument("Usager : le numeroCNI ne doit pas etre vide.");
    m_numeroCNI = numeroCNI;
}

void Usager::afficher(std::ostream& os) const {
    os << "Usager #" << m_id << " | " << m_prenom << " " << m_nom
       << " | Tel: " << m_telephone
       << " | CNI: " << m_numeroCNI
       << " | Adresse: " << m_adresse
       << " | Demandes: " << m_nombreDemandes;
}

std::istream& operator>>(std::istream& is, Usager& u) {
    std::string nom, prenom, tel, adresse, cni;

    // L'id n'est PAS saisi : il est attribue automatiquement par
    // GestionEtatCivil::ajouterUsager(). L'utilisateur ne fournit que
    // les donnees qu'il connait reellement.
    std::cout << "  nom           : "; std::getline(is, nom);
    std::cout << "  prenom        : "; std::getline(is, prenom);
    std::cout << "  telephone     : "; std::getline(is, tel);
    std::cout << "  adresse       : "; std::getline(is, adresse);
    std::cout << "  numero CNI    : "; std::getline(is, cni);

    // Validation via les mutateurs (peut lancer une exception).
    // Pas de setId ici : l'id est affecte par le systeme lors de l'ajout.
    u.setNom(nom);
    u.setPrenom(prenom);
    u.setTelephone(tel);
    u.setAdresse(adresse);
    u.setNumeroCNI(cni);
    // Un nouvel usager n'a encore fait aucune demande : compteur force a 0.
    // Ce compteur est gere par le programme (incrementerDemandes), pas saisi.
    u.m_nombreDemandes = 0;
    return is;
}