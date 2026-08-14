#ifndef USAGER_HPP
#define USAGER_HPP

#include "Personne.hpp"

// Citoyen qui demande un acte d'etat civil.
class Usager : public Personne {
private:
    std::string m_adresse;
    std::string m_numeroCNI;
    int         m_nombreDemandes;

public:
    Usager();
    Usager(int id, const std::string& nom, const std::string& prenom,
           const std::string& telephone, const std::string& adresse,
           const std::string& numeroCNI, int nombreDemandes = 0);

    void afficher(std::ostream& os) const override;

    void incrementerDemandes();

    // Accesseurs specifiques
    const std::string& adresse()        const { return m_adresse; }
    const std::string& numeroCNI()      const { return m_numeroCNI; }
    int                nombreDemandes() const { return m_nombreDemandes; }

    // Mutateurs avec validation
    void setAdresse(const std::string& adresse);
    void setNumeroCNI(const std::string& numeroCNI);

    friend std::istream& operator>>(std::istream& is, Usager& u);
};

#endif // USAGER_HPP
