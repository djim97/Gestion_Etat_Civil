#include "GestionEtatCivil.hpp"
#include <stdexcept>
#include <algorithm>

GestionEtatCivil::GestionEtatCivil(const std::string& nomInstitution)
    : m_nomInstitution(nomInstitution), m_prochainIdUsager(1) {
    if (nomInstitution.empty())
        throw std::invalid_argument("GestionEtatCivil : le nom de l'institution ne doit pas etre vide.");
}

// ---------- Usagers ----------
void GestionEtatCivil::ajouterUsager(std::shared_ptr<Usager> u) {
    if (!u) throw std::invalid_argument("ajouterUsager : usager nul.");
    // Le systeme attribue lui-meme un id unique : l'utilisateur ne le saisit pas.
    // Comme le compteur ne fait qu'augmenter, l'unicite est garantie par construction.
    u->setId(m_prochainIdUsager);
    ++m_prochainIdUsager;
    m_usagers.push_back(u);
}

std::shared_ptr<Usager> GestionEtatCivil::trouverUsager(int id) const {
    for (const auto& u : m_usagers)
        if (u->id() == id) return u;
    throw std::runtime_error("trouverUsager : aucun usager avec l'id " + std::to_string(id) + ".");
}

void GestionEtatCivil::supprimerUsager(int id) {
    auto it = std::find_if(m_usagers.begin(), m_usagers.end(),
                           [id](const std::shared_ptr<Usager>& u) { return u->id() == id; });
    if (it == m_usagers.end())
        throw std::runtime_error("supprimerUsager : usager introuvable.");
    m_usagers.erase(it);
}

// ---------- Agents ----------
void GestionEtatCivil::ajouterAgent(std::shared_ptr<AgentEtatCivil> a) {
    if (!a) throw std::invalid_argument("ajouterAgent : agent nul.");
    for (const auto& x : m_agents)
        if (x->id() == a->id())
            throw std::runtime_error("ajouterAgent : id d'agent deja existant.");
    m_agents.push_back(a);
}

std::shared_ptr<AgentEtatCivil> GestionEtatCivil::trouverAgent(int id) const {
    for (const auto& a : m_agents)
        if (a->id() == id) return a;
    throw std::runtime_error("trouverAgent : aucun agent avec l'id " + std::to_string(id) + ".");
}

// ---------- Centres ----------
void GestionEtatCivil::ajouterCentre(std::shared_ptr<CentreEtatCivil> c) {
    if (!c) throw std::invalid_argument("ajouterCentre : centre nul.");
    m_centres.push_back(c);
}

std::shared_ptr<CentreEtatCivil> GestionEtatCivil::trouverCentre(int id) const {
    for (const auto& c : m_centres)
        if (c->id() == id) return c;
    throw std::runtime_error("trouverCentre : aucun centre avec l'id " + std::to_string(id) + ".");
}

// ---------- Actes ----------
void GestionEtatCivil::ajouterActe(std::shared_ptr<ActeCivil> a) {
    if (!a) throw std::invalid_argument("ajouterActe : acte nul.");
    m_actes.push_back(a);
}

std::shared_ptr<ActeCivil> GestionEtatCivil::trouverActe(int id) const {
    for (const auto& a : m_actes)
        if (a->id() == id) return a;
    throw std::runtime_error("trouverActe : aucun acte avec l'id " + std::to_string(id) + ".");
}

// ---------- Demandes ----------
void GestionEtatCivil::ajouterDemande(std::shared_ptr<DemandeActe> d) {
    if (!d) throw std::invalid_argument("ajouterDemande : demande nulle.");
    m_demandes.push_back(d);
}

std::shared_ptr<DemandeActe> GestionEtatCivil::trouverDemande(int id) const {
    for (const auto& d : m_demandes)
        if (d->id() == id) return d;
    throw std::runtime_error("trouverDemande : aucune demande avec l'id " + std::to_string(id) + ".");
}

// ---------- Dossiers ----------
void GestionEtatCivil::ajouterDossier(std::shared_ptr<DossierEtatCivil> d) {
    if (!d) throw std::invalid_argument("ajouterDossier : dossier nul.");
    m_dossiers.push_back(d);
}

// ---------- Affichage polymorphique ----------
void GestionEtatCivil::afficherTousAgents() const {
    for (const auto& a : m_agents)
        std::cout << "  - " << *a << "\n"; // operator<< -> afficher() virtuel
}

// ---------- Operateurs d'acces ----------
std::shared_ptr<Usager> GestionEtatCivil::operator[](int id) const {
    return trouverUsager(id);
}

std::shared_ptr<AgentEtatCivil> GestionEtatCivil::operator()(int id) const {
    return trouverAgent(id);
}

std::ostream& operator<<(std::ostream& os, const GestionEtatCivil& g) {
    os << "########## " << g.m_nomInstitution << " ##########\n"
       << "Usagers  : " << g.m_usagers.size()  << "\n"
       << "Agents   : " << g.m_agents.size()   << "\n"
       << "Centres  : " << g.m_centres.size()  << "\n"
       << "Actes    : " << g.m_actes.size()    << "\n"
       << "Demandes : " << g.m_demandes.size() << "\n"
       << "Dossiers : " << g.m_dossiers.size();
    return os;
}