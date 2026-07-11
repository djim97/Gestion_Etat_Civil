#ifndef ACTE_CIVIL_HPP
#define ACTE_CIVIL_HPP

#include <string>
#include <iostream>

// Acte administratif delivre par le centre (naissance, mariage, deces).
class ActeCivil {
private:
    int         m_id;
    std::string m_type;
    std::string m_reference;
    double      m_coutTimbre;
    bool        m_delivre;

public:
    ActeCivil();
    ActeCivil(int id, const std::string& type, const std::string& reference,
              double coutTimbre);

    int                id()         const { return m_id; }
    const std::string& type()       const { return m_type; }
    const std::string& reference()  const { return m_reference; }
    double             coutTimbre() const { return m_coutTimbre; }
    bool               delivre()    const { return m_delivre; }

    void setId(int id);
    void setType(const std::string& type);
    void setReference(const std::string& reference);
    void setCoutTimbre(double coutTimbre);

    void   marquerDelivre();
    // Frais total selon le nombre de copies demandees.
    double calculerFrais(int nombreCopies) const;

    bool operator==(const ActeCivil& autre) const { return m_id == autre.m_id; }
};

// Affichage via les accesseurs publics : pas besoin de friend.
std::ostream& operator<<(std::ostream& os, const ActeCivil& a);

#endif // ACTE_CIVIL_HPP