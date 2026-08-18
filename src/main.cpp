#include "GestionEtatCivil.hpp"
#include "Usager.hpp"
#include "OfficierEtatCivil.hpp"
#include "AgentStagiaire.hpp"
#include "CentreEtatCivil.hpp"
#include "ActeCivil.hpp"
#include "DemandeActe.hpp"
#include "DossierEtatCivil.hpp"

#include <iostream>
#include <iomanip>
#include <limits>
#include <memory>
#include <string>

using namespace std;

// ===================== Helpers d'affichage (ASCII pur) =====================
static const int L = 66; // largeur des encadres

static void bord() { cout << '+' << string(L - 2, '=') << "+\n"; }

// Ecrit une ligne de texte centree entre deux bordures verticales.
static void centre(const string& t) {
    int inner = L - 2;
    if ((int)t.size() >= inner) { cout << "| " << t << " |\n"; return; }
    int esp = inner - (int)t.size();
    int g = esp / 2, d = esp - g;
    cout << '|' << string(g, ' ') << t << string(d, ' ') << "|\n";
}

// Titre de section encadre.
static void titre(const string& t) {
    cout << '\n';
    bord();
    centre(t);
    bord();
    cout << '\n';
}

// Invite de saisie avec label aligne.
static void invite(const string& label) {
    cout << "  " << left << setw(26) << label << ": ";
}

// Ligne "label : montant FCFA" alignee.
static void montant(const string& label, double m) {
    cout << "  " << left << setw(26) << label << ": "
         << right << setw(10) << (long long)m << " FCFA\n";
}

// Pose une question fermee (o/n) jusqu'a obtenir une reponse valide.
static bool demanderOuiNon(const string& question) {
    string rep;
    while (true) {
        cout << "\n  " << question << " (o/n) : ";
        std::getline(cin, rep);
        if (!rep.empty() && (rep[0] == 'o' || rep[0] == 'O')) return true;
        if (!rep.empty() && (rep[0] == 'n' || rep[0] == 'N')) return false;
        cout << "  Reponse non reconnue, veuillez taper 'o' ou 'n'.\n";
    }
}

int main() {
    try {
        // -------- 1 a 3. Creation en dur (silencieuse) --------
        GestionEtatCivil systeme("Mairie de Dakar - Etat Civil");

        auto centre1 = make_shared<CentreEtatCivil>(1, "Centre Plateau", "Dakar", "Av. Leopold Sedar Senghor");
        auto centre2 = make_shared<CentreEtatCivil>(2, "Centre Medina", "Dakar", "Rue 15 x 22");
        systeme.ajouterCentre(centre1);
        systeme.ajouterCentre(centre2);

        auto acteNaissance = make_shared<ActeCivil>(1, "Naissance", "ACT-N-2024", 1000.0);
        auto acteMariage   = make_shared<ActeCivil>(2, "Mariage",   "ACT-M-2024", 2000.0);
        auto acteDeces     = make_shared<ActeCivil>(3, "Deces",     "ACT-D-2024", 1500.0);
        systeme.ajouterActe(acteNaissance);
        systeme.ajouterActe(acteMariage);
        systeme.ajouterActe(acteDeces);

        // -------- 4 a 6. Officier + Stagiaire (encadre par l'officier) --------
        auto officier = make_shared<OfficierEtatCivil>(
            10, "Ndiaye", "Awa", "770000010", "MAT-OFF-01",
            "Signature", 250000.0, "Officier principal", 10000.0);
        auto stagiaire = make_shared<AgentStagiaire>(
            11, "Fall", "Modou", "770000011", "MAT-STG-01",
            "Accueil", 90000.0, officier /* encadreur */, 0.4);
        systeme.ajouterAgent(officier);
        systeme.ajouterAgent(stagiaire);

        // -------- 7. Affichage + prime pour 5 actes --------
        titre("AGENTS ENREGISTRES");
        systeme.afficherTousAgents();
        cout << "\n  Primes pour 5 actes traites (polymorphisme) :\n";
        for (const auto& a : systeme.agents())
            cout << "   - " << left << setw(18) << (a->prenom() + " " + a->nom())
                 << " : " << right << setw(8) << (long long)a->calculerPrime(5) << " FCFA\n";

        // Variables qui doivent rester accessibles APRES la boucle (pour les
        // etapes 17-18 et les tests finaux, qui portent sur le dernier usager
        // et le dernier agent traites).
        shared_ptr<Usager>           usager;
        shared_ptr<AgentEtatCivil>   agentTraitant;
        shared_ptr<DossierEtatCivil> dossier;

        // Compteurs d'identifiants pour demandes et dossiers : incrementes a
        // chaque tour de boucle pour eviter deux demandes/dossiers avec le
        // meme numero (l'id de l'usager, lui, est deja auto-genere par
        // GestionEtatCivil::ajouterUsager()).
        int idDemandeCourant = 100;
        int idDossierCourant = 500;
        int numeroUsager = 1;

        // Petite fonction locale (lambda) qui saisit un nouvel usager au
        // clavier et l'enregistre dans le systeme. Evite de dupliquer ce
        // bloc dans les deux branches du menu ci-dessous.
        auto saisirNouvelUsager = [&]() {
            usager = make_shared<Usager>();
            cout << "  Veuillez saisir les informations de l'usager :\n";
            cin >> *usager;                 // operateur >>
            systeme.ajouterUsager(usager);
            cout << "\n  Usager enregistre :\n   -> " << *usager << "\n";
        };

        // -------- Boucle : saisie usager -> demande -> dossier --------
        bool continuer = true;
        while (continuer) {

            // -------- 8-9. Choix ou saisie de l'usager --------
            titre("USAGER #" + to_string(numeroUsager));
            if (numeroUsager == 1 || systeme.usagers().empty()) {
                // Premier passage : pas encore d'usager existant a reutiliser.
                saisirNouvelUsager();
            } else {
                cout << "  1. Enregistrer un nouvel usager\n";
                cout << "  2. Faire une nouvelle demande pour un usager deja enregistre\n";

                // Redemande tant que la reponse n'est ni 1 ni 2, au lieu de
                // laisser un choix invalide se propager plus loin.
                int choixUsager = 0;
                while (choixUsager != 1 && choixUsager != 2) {
                    invite("Votre choix (1 ou 2)"); cin >> choixUsager;
                    if (choixUsager != 1 && choixUsager != 2)
                        cout << "  Choix invalide, veuillez taper 1 ou 2.\n";
                }
                // Purge le '\n' laisse par ce cin >>, indispensable si la
                // branche "nouvel usager" est choisie (elle lit avec getline).
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (choixUsager == 2) {
                    cout << "\n  Usagers deja enregistres :\n";
                    for (const auto& u : systeme.usagers()) cout << "   - " << *u << "\n";

                    // Redemande l'id tant qu'il ne correspond a aucun usager,
                    // au lieu de laisser l'exception interrompre tout le
                    // scenario pour une simple faute de frappe.
                    bool trouve = false;
                    while (!trouve) {
                        int idUsagerExistant;
                        cout << "\n";
                        invite("Id de l'usager"); cin >> idUsagerExistant;
                        try {
                            usager = systeme.trouverUsager(idUsagerExistant);
                            trouve = true;
                        } catch (const exception& e) {
                            cout << "  [Erreur] " << e.what() << " Reessayez.\n";
                        }
                    }
                    cout << "\n  Usager selectionne :\n   -> " << *usager << "\n";
                } else {
                    saisirNouvelUsager();
                }
            }

            // -------- 10. Centres et actes disponibles --------
            titre("CENTRES ET ACTES DISPONIBLES");
            cout << "  Centres :\n";
            for (const auto& c : systeme.centres()) cout << "   - " << *c << "\n";
            cout << "\n  Actes :\n";
            for (const auto& a : systeme.actes())   cout << "   - " << *a << "\n";

            // -------- 11-13. Creation d'une demande --------
            titre("CREATION D'UNE DEMANDE");

            // Redemande l'id du centre tant qu'il ne correspond a aucun centre,
            // au lieu de laisser l'exception interrompre tout le programme.
            shared_ptr<CentreEtatCivil> centreChoisi;
            bool centreTrouve = false;
            while (!centreTrouve) {
                int idCentre;
                invite("Id du centre choisi"); cin >> idCentre;
                try {
                    centreChoisi = systeme.trouverCentre(idCentre);
                    centreTrouve = true;
                } catch (const exception& e) {
                    cout << "  [Erreur] " << e.what() << " Reessayez.\n";
                }
            }

            // Meme principe pour l'acte choisi.
            shared_ptr<ActeCivil> acteChoisi;
            bool acteTrouve = false;
            while (!acteTrouve) {
                int idActe;
                invite("Id de l'acte choisi"); cin >> idActe;
                try {
                    acteChoisi = systeme.trouverActe(idActe);
                    acteTrouve = true;
                } catch (const exception& e) {
                    cout << "  [Erreur] " << e.what() << " Reessayez.\n";
                }
            }

            int nbCopies;
            invite("Nombre de copies");     cin >> nbCopies;

            auto demande = make_shared<DemandeActe>(idDemandeCourant, usager, centreChoisi, acteChoisi, nbCopies);
            systeme.ajouterDemande(demande);
            usager->incrementerDemandes();
            ++idDemandeCourant;

            cout << "\n  Demande creee :\n   -> " << *demande << "\n\n";
            montant("Montant de la demande", demande->calculerMontant());

            // -------- 14-16. Traitement et dossier finalise --------
            titre("TRAITEMENT ET DOSSIER FINALISE");
            cout << "  Agents disponibles :\n";
            systeme.afficherTousAgents();          // affichage polymorphique
            cout << "\n";
            int idAgent;
            // Redemande tant que l'id ne correspond a aucun agent.
            bool agentTrouve = false;
            while (!agentTrouve) {
                invite("Id de l'agent traitant"); cin >> idAgent;
                try {
                    agentTraitant = systeme.trouverAgent(idAgent);
                    agentTrouve = true;
                } catch (const exception& e) {
                    cout << "  [Erreur] " << e.what() << " Reessayez.\n";
                }
            }

            demande->valider();
            demande->delivrer();
            int delai;
            invite("Delai de traitement (jours)"); cin >> delai;
            dossier = make_shared<DossierEtatCivil>(idDossierCourant, demande, agentTraitant, delai);
            systeme.ajouterDossier(dossier);
            ++idDossierCourant;

            cout << "\n" << *dossier << "\n";

            // Purge le '\n' laisse par le dernier "cin >> delai" : sans cela,
            // la prochaine lecture par getline() (question oui/non, ou saisie
            // du prochain usager) lirait une ligne vide au lieu d'attendre
            // une vraie reponse.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continuer = demanderOuiNon("Voulez-vous traiter un autre usager (nouveau ou deja enregistre) ?");
            ++numeroUsager;
        }

        // -------- Menu d'exploration : consulter les demandes/dossiers a la demande --------
        bool explorer = true;
        while (explorer) {
            titre("EXPLORATION DES DONNEES");
            cout << "  1. Voir les demandes faites par un usager\n";
            cout << "  2. Voir les dossiers traites par un agent\n";
            cout << "  3. Continuer vers le resume final\n";

            int choixExploration = 0;
            while (choixExploration < 1 || choixExploration > 3) {
                invite("Votre choix (1-3)"); cin >> choixExploration;
                if (choixExploration < 1 || choixExploration > 3)
                    cout << "  Choix invalide, veuillez taper 1, 2 ou 3.\n";
            }

            if (choixExploration == 1) {
                // ---- Demandes faites par un usager choisi ----
                cout << "\n  Usagers enregistres :\n";
                for (const auto& u : systeme.usagers()) cout << "   - " << *u << "\n";

                shared_ptr<Usager> u;
                bool trouve = false;
                while (!trouve) {
                    int idU;
                    cout << "\n";
                    invite("Id de l'usager"); cin >> idU;
                    try {
                        u = systeme.trouverUsager(idU);
                        trouve = true;
                    } catch (const exception& e) {
                        cout << "  [Erreur] " << e.what() << " Reessayez.\n";
                    }
                }

                cout << "\n  Demandes de " << u->prenom() << " " << u->nom()
                     << " (#" << u->id() << ") :\n";
                bool aucune = true;
                for (const auto& d : systeme.demandes())
                    if (d->usager()->id() == u->id()) {
                        cout << "   - " << *d << "\n";
                        aucune = false;
                    }
                if (aucune) cout << "   (aucune demande)\n";

            } else if (choixExploration == 2) {
                // ---- Dossiers traites par un agent choisi ----
                cout << "\n  Agents enregistres :\n";
                systeme.afficherTousAgents();

                shared_ptr<AgentEtatCivil> a;
                bool trouve = false;
                while (!trouve) {
                    int idA;
                    cout << "\n";
                    invite("Id de l'agent"); cin >> idA;
                    try {
                        a = systeme.trouverAgent(idA);
                        trouve = true;
                    } catch (const exception& e) {
                        cout << "  [Erreur] " << e.what() << " Reessayez.\n";
                    }
                }

                cout << "\n  Dossiers traites par " << a->prenom() << " " << a->nom()
                     << " (#" << a->id() << ") :\n";
                bool aucun = true;
                double total = 0.0;
                for (const auto& d : systeme.dossiers())
                    if (d->agent()->id() == a->id()) {
                        cout << "   - Dossier #" << d->id() << " (Demande #" << d->demande()->id()
                             << ") -> " << (long long)d->calculerCoutTotal() << " FCFA\n";
                        total += d->calculerCoutTotal();
                        aucun = false;
                    }
                if (aucun) cout << "   (aucun dossier traite)\n";
                else cout << "   => total genere : " << (long long)total << " FCFA\n";

            } else {
                explorer = false;
            }
        }

        // -------- 17. Acces via [] et () (sur le dernier usager/agent) --------
        titre("ACCES PAR OPERATEURS [] ET ()");
        auto usagerAcces = systeme[usager->id()];          // operateur []
        auto agentAcces  = systeme(agentTraitant->id());   // operateur ()
        cout << "  systeme[" << usager->id() << "]  -> " << *usagerAcces << "\n";
        cout << "  systeme(" << agentTraitant->id() << ") -> " << *agentAcces << "\n";

        // -------- 18. Resume complet --------
        titre("RESUME COMPLET DU SYSTEME");
        cout << systeme << "\n";

        // -------- Demandes regroupees par usager --------
        titre("DEMANDES PAR USAGER");
        for (const auto& u : systeme.usagers()) {
            cout << "  " << u->prenom() << " " << u->nom() << " (#" << u->id() << ") - "
                 << u->nombreDemandes() << " demande(s) :\n";
            for (const auto& d : systeme.demandes())
                if (d->usager()->id() == u->id())
                    cout << "   - " << *d << "\n";
            cout << "\n";
        }

        // -------- Dossiers regroupes par agent (polymorphisme : calculerCoutTotal()
        // appelle en interne l'agent->calculerPrime() reelle de chaque agent) --------
        titre("DOSSIERS TRAITES PAR AGENT");
        for (const auto& a : systeme.agents()) {
            cout << "  " << a->prenom() << " " << a->nom() << " (#" << a->id() << ") :\n";
            double totalGenere = 0.0;
            int nbTraites = 0;
            for (const auto& d : systeme.dossiers()) {
                if (d->agent()->id() == a->id()) {
                    cout << "   - Dossier #" << d->id() << " (Demande #" << d->demande()->id()
                         << ") -> cout total : " << (long long)d->calculerCoutTotal() << " FCFA\n";
                    totalGenere += d->calculerCoutTotal();
                    ++nbTraites;
                }
            }
            if (nbTraites == 0)
                cout << "   (aucun dossier traite)\n";
            else
                cout << "   => " << nbTraites << " dossier(s), total genere : "
                     << (long long)totalGenere << " FCFA\n";
            cout << "\n";
        }

        // -------- Chiffre d'affaires total (tous agents, tous dossiers confondus) --------
        titre("CHIFFRE D'AFFAIRES TOTAL");
        double chiffreAffairesTotal = 0.0;
        for (const auto& d : systeme.dossiers()) chiffreAffairesTotal += d->calculerCoutTotal();
        cout << "  Chiffre d'affaires total : " << (long long)chiffreAffairesTotal << " FCFA\n";

        // ===================== TESTS DES OPERATEURS =====================
        titre("TESTS DES OPERATEURS DE COMPARAISON");
        cout << "  centre1 == centre2         ? " << ((*centre1 == *centre2) ? "vrai" : "faux") << "\n";
        cout << "  centre1 != centre2         ? " << ((*centre1 != *centre2) ? "vrai" : "faux") << "\n";
        auto usagerBis = make_shared<Usager>(*usager); // meme id -> egaux
        cout << "  usager  == copie (par id)  ? " << ((*usager == *usagerBis) ? "vrai" : "faux") << "\n";
        cout << "  usager  != officier(par id)? " << ((*usager != *officier) ? "vrai" : "faux") << "\n";

        // ----- Cas d'erreur 1 : nombre de copies negatif -----
        titre("CAS D'ERREUR 1 : copies negatives");
        try {
            auto mauvaise = make_shared<DemandeActe>(idDemandeCourant + 1, usager, centre1, acteNaissance, -3);
            cout << "  ERREUR : aucune exception levee.\n";
        } catch (const exception& e) {
            cout << "  [OK] Exception attendue : " << e.what() << "\n";
        }

        // ----- Cas d'erreur 2 : stagiaire sans encadreur -----
        titre("CAS D'ERREUR 2 : stagiaire sans encadreur");
        try {
            AgentStagiaire sansMentor(12, "Sow", "Bineta", "770000012", "MAT-STG-02",
                                      "Accueil", 90000.0, nullptr, 0.4);
            cout << "  ERREUR : aucune exception levee.\n";
        } catch (const exception& e) {
            cout << "  [OK] Exception attendue : " << e.what() << "\n";
        }

        // ----- Cas d'erreur 3 : recherche d'un id inexistant -----
        titre("CAS D'ERREUR 3 : usager inexistant");
        try {
            auto introuvable = systeme.trouverUsager(9999);
            cout << "  ERREUR : aucune exception levee.\n";
        } catch (const exception& e) {
            cout << "  [OK] Exception attendue : " << e.what() << "\n";
        }

        cout << '\n';
        bord();
        centre("FIN DU SCENARIO");
        bord();
    }
    catch (const exception& e) {
        cerr << "\n[ERREUR FATALE] " << e.what() << "\n";
        return 1;
    }
    return 0;
}