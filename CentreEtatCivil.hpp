#ifndef CENTRE_ETAT_CIVIL_HPP
#define CENTRE_ETAT_CIVIL_HPP

#include <string>
#include <iostream>

// Centre ou mairie ou les demandes sont deposees et traitees.
class CentreEtatCivil {
private:
    int         m_id;
    std::string m_nom;
    std::string m_commune;
    std::string m_adresse;

public:
    CentreEtatCivil();
    CentreEtatCivil(int id, const std::string& nom,
                    const std::string& commune, const std::string& adresse);

    int                id()      const { return m_id; }
    const std::string& nom()     const { return m_nom; }
    const std::string& commune() const { return m_commune; }
    const std::string& adresse() const { return m_adresse; }

    void setId(int id);
    void setNom(const std::string& nom);
    void setCommune(const std::string& commune);
    void setAdresse(const std::string& adresse);

    bool operator==(const CentreEtatCivil& autre) const { return m_id == autre.m_id; }
    bool operator!=(const CentreEtatCivil& autre) const { return m_id != autre.m_id; }

    // operator>> reste friend : il ecrit dans l'objet lors de la saisie.
    friend std::istream& operator>>(std::istream& is, CentreEtatCivil& c);
};

// Affichage via les accesseurs publics : operator<< n'a pas besoin d'etre friend.
std::ostream& operator<<(std::ostream& os, const CentreEtatCivil& c);

#endif // CENTRE_ETAT_CIVIL_HPP