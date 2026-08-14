#include "GestionEtatCivil.hpp"
#include "Usager.hpp"
#include "OfficierEtatCivil.hpp"
#include "AgentStagiaire.hpp"
#include "CentreEtatCivil.hpp"
#include "ActeCivil.hpp"
#include "DemandeActe.hpp"
#include "DossierEtatCivil.hpp"

#include <iostream>
#include <memory>

using namespace std;

static void titre(const string& t) {
    cout << "\n=============================================================\n"
         << " " << t << "\n"
         << "=============================================================\n";
}

int main() {
    try {
        // -------- 1 a 3. Creation en dur (phase silencieuse, sans affichage) --------
        GestionEtatCivil systeme("Mairie de Dakar - Etat Civil");

        // -------- 2. Deux centres en dur (crees sans affichage) --------
        auto centre1 = make_shared<CentreEtatCivil>(1, "Centre Plateau", "Dakar", "Av. Leopold Sedar Senghor");
        auto centre2 = make_shared<CentreEtatCivil>(2, "Centre Medina", "Dakar", "Rue 15 x 22");
        systeme.ajouterCentre(centre1);
        systeme.ajouterCentre(centre2);

        // -------- 3. Trois actes en dur (crees sans affichage) --------
        auto acteNaissance = make_shared<ActeCivil>(1, "Naissance", "ACT-N-2024", 1000.0);
        auto acteMariage   = make_shared<ActeCivil>(2, "Mariage",   "ACT-M-2024", 2000.0);
        auto acteDeces     = make_shared<ActeCivil>(3, "Deces",     "ACT-D-2024", 1500.0);
        systeme.ajouterActe(acteNaissance);
        systeme.ajouterActe(acteMariage);
        systeme.ajouterActe(acteDeces);

        // -------- 4 & 5. Officier + Stagiaire (encadre par l'officier) --------
        auto officier = make_shared<OfficierEtatCivil>(
            10, "Ndiaye", "Awa", "770000010", "MAT-OFF-01",
            "Signature", 250000.0, "Officier principal", 10000.0);

        auto stagiaire = make_shared<AgentStagiaire>(
            11, "Fall", "Modou", "770000011", "MAT-STG-01",
            "Accueil", 90000.0, officier /* encadreur */, 0.4);

        // -------- 6. Ajout polymorphique --------
        systeme.ajouterAgent(officier);
        systeme.ajouterAgent(stagiaire);

        // -------- 7. Affichage + prime pour 5 actes --------
        cout << "Liste des agents :\n";
        systeme.afficherTousAgents();
        cout << "\nPrimes calculees pour 5 actes traites (polymorphisme) :\n";
        for (const auto& a : systeme.agents())
            cout << "  - " << a->prenom() << " " << a->nom()
                 << " => " << a->calculerPrime(5) << " FCFA\n";

        // -------- 8. Saisie d'un usager (operateur >>) --------
        titre("Saisie d'un usager");
        auto usager = make_shared<Usager>();
        cout << "Veuillez saisir les informations de l'usager :\n";
        cin >> *usager;                 // operateur >>
        systeme.ajouterUsager(usager);
        cout << "\nUsager enregistre : " << *usager << "\n"; // operateur <<

        // -------- 10. Centres et actes disponibles --------
        titre("Centres et actes disponibles");
        cout << "Centres :\n";
        for (const auto& c : systeme.centres()) cout << "  " << *c << "\n";
        cout << "Actes :\n";
        for (const auto& a : systeme.actes())   cout << "  " << *a << "\n";

        // -------- 11. Choix centre / acte / copies --------
        titre("Creation d'une demande");
        int idCentre, idActe, nbCopies;
        cout << "Id du centre choisi   : "; cin >> idCentre;
        cout << "Id de l'acte choisi   : "; cin >> idActe;
        cout << "Nombre de copies      : "; cin >> nbCopies;

        auto centreChoisi = systeme.trouverCentre(idCentre);
        auto acteChoisi   = systeme.trouverActe(idActe);

        // -------- 12. Creation de la DemandeActe --------
        auto demande = make_shared<DemandeActe>(100, usager, centreChoisi, acteChoisi, nbCopies);
        systeme.ajouterDemande(demande);
        usager->incrementerDemandes();

        // -------- 13. Montant de la demande --------
        cout << "\n" << *demande << "\n";
        cout << "Montant de la demande : " << demande->calculerMontant() << " FCFA\n";

        // -------- 14. Choix de l'agent traitant --------
        titre("Traitement et dossier finalise");
        cout << "Agents disponibles :\n";
        systeme.afficherTousAgents();          // affichage polymorphique
        int idAgent;
        cout << "Id de l'agent traitant : "; cin >> idAgent;
        auto agentTraitant = systeme.trouverAgent(idAgent);

        // -------- 15. Valider, delivrer, creer le dossier --------
        demande->valider();
        demande->delivrer();
        int delai;
        cout << "Delai de traitement (jours) : "; cin >> delai;
        auto dossier = make_shared<DossierEtatCivil>(500, demande, agentTraitant, delai);
        systeme.ajouterDossier(dossier);

        // -------- 16. Cout total du dossier --------
        cout << "\n" << *dossier << "\n";

        // -------- 17. Acces via [] et () --------
        titre("Acces par operateurs [] et ()");
        auto usagerAcces = systeme[usager->id()];          // operateur []
        auto agentAcces  = systeme(agentTraitant->id());   // operateur ()
        cout << "systeme[" << usager->id() << "]        => " << *usagerAcces << "\n";
        cout << "systeme(" << agentTraitant->id() << ")            => " << *agentAcces << "\n";

        // -------- 18. Resume complet --------
        titre("Resume complet du systeme");
        cout << systeme << "\n";

        // ============================================================
        //  TESTS DES OPERATEURS ET CAS LIMITES
        // ============================================================
        titre("Tests des operateurs de comparaison");
        cout << "centre1 == centre2 ? " << ((*centre1 == *centre2) ? "vrai" : "faux") << "\n";
        cout << "centre1 != centre2 ? " << ((*centre1 != *centre2) ? "vrai" : "faux") << "\n";

        auto usagerBis = make_shared<Usager>(*usager); // meme id -> egaux
        cout << "usager == copie ?  " << ((*usager == *usagerBis) ? "vrai" : "faux") << "\n";
        cout << "usager != officier(par id) ? "
             << ((*usager != *officier) ? "vrai" : "faux") << "\n";

        // ----- Cas d'erreur 1 : nombre de copies negatif -----
        titre("Cas d'erreur 1 : demande avec copies negatives");
        try {
            auto mauvaise = make_shared<DemandeActe>(101, usager, centre1, acteNaissance, -3);
            cout << "ERREUR : aucune exception levee.\n";
        } catch (const exception& e) {
            cout << "Exception attendue : " << e.what() << "\n";
        }

        // ----- Cas d'erreur 2 : stagiaire sans encadreur -----
        titre("Cas d'erreur 2 : stagiaire sans encadreur");
        try {
            AgentStagiaire sansMentor(12, "Sow", "Bineta", "770000012", "MAT-STG-02",
                                      "Accueil", 90000.0, nullptr, 0.4);
            cout << "ERREUR : aucune exception levee.\n";
        } catch (const exception& e) {
            cout << "Exception attendue : " << e.what() << "\n";
        }

        // ----- Cas d'erreur 3 : recherche d'un id inexistant -----
        titre("Cas d'erreur 3 : recherche d'un usager inexistant");
        try {
            auto introuvable = systeme.trouverUsager(9999);
            cout << "ERREUR : aucune exception levee.\n";
        } catch (const exception& e) {
            cout << "Exception attendue : " << e.what() << "\n";
        }

        cout << "\n>>> Fin du scenario. <<<\n";
    }
    catch (const exception& e) {
        cerr << "\n[ERREUR FATALE] " << e.what() << "\n";
        return 1;
    }
    return 0;
}