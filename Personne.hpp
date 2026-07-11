#ifndef PERSONNE_HPP
#define PERSONNE_HPP

#include <string>
#include <iostream>

// Classe abstraite de base pour toutes les personnes du systeme.
class Personne {
protected:
    int         m_id;
    std::string m_nom;
    std::string m_prenom;
    std::string m_telephone;

    // Constructeur protege : appele uniquement par les classes derivees.
    Personne(int id, const std::string& nom,
             const std::string& prenom, const std::string& telephone);

    // Constructeur par defaut (utilise avant une saisie via operator>>).
    Personne();

public:
    // Destructeur virtuel obligatoire pour une classe polymorphique.
    virtual ~Personne() = default;

    // Methode virtuelle pure : chaque classe concrete doit l'implementer.
    virtual void afficher(std::ostream& os) const = 0;

    // Accesseurs
    int                id()        const { return m_id; }
    const std::string& nom()       const { return m_nom; }
    const std::string& prenom()    const { return m_prenom; }
    const std::string& telephone() const { return m_telephone; }

    // Mutateurs avec validation
    void setId(int id);
    void setNom(const std::string& nom);
    void setPrenom(const std::string& prenom);
    void setTelephone(const std::string& telephone);

    // Operateurs de comparaison par id
    bool operator==(const Personne& autre) const { return m_id == autre.m_id; }
    bool operator!=(const Personne& autre) const { return m_id != autre.m_id; }
};

// Affichage polymorphique : delegue a afficher().
std::ostream& operator<<(std::ostream& os, const Personne& p);

#endif // PERSONNE_HPP
