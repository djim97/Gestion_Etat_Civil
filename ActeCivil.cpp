#include "ActeCivil.hpp"
#include <stdexcept>

ActeCivil::ActeCivil()
    : m_id(0), m_type(), m_reference(), m_coutTimbre(0.0), m_delivre(false) {}

ActeCivil::ActeCivil(int id, const std::string& type, const std::string& reference,
                     double coutTimbre)
    : m_id(0), m_type(), m_reference(), m_coutTimbre(0.0), m_delivre(false) {
    setId(id);
    setType(type);
    setReference(reference);
    setCoutTimbre(coutTimbre);
}

void ActeCivil::setId(int id) {
    if (id <= 0)
        throw std::invalid_argument("ActeCivil : l'id doit etre > 0.");
    m_id = id;
}

void ActeCivil::setType(const std::string& type) {
    if (type.empty())
        throw std::invalid_argument("ActeCivil : le type ne doit pas etre vide.");
    m_type = type;
}

void ActeCivil::setReference(const std::string& reference) {
    if (reference.empty())
        throw std::invalid_argument("ActeCivil : la reference ne doit pas etre vide.");
    m_reference = reference;
}

void ActeCivil::setCoutTimbre(double coutTimbre) {
    if (coutTimbre < 0)
        throw std::invalid_argument("ActeCivil : coutTimbre doit etre >= 0.");
    m_coutTimbre = coutTimbre;
}

void ActeCivil::marquerDelivre() {
    m_delivre = true;
}

double ActeCivil::calculerFrais(int nombreCopies) const {
    if (nombreCopies <= 0)
        throw std::invalid_argument("ActeCivil : le nombre de copies doit etre > 0.");
    return m_coutTimbre * nombreCopies;
}

std::ostream& operator<<(std::ostream& os, const ActeCivil& a) {
    os << "Acte #" << a.id() << " | Type: " << a.type()
       << " | Ref: " << a.reference()
       << " | Timbre: " << a.coutTimbre()
       << " | " << (a.delivre() ? "DELIVRE" : "non delivre");
    return os;
}