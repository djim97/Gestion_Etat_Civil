# Gestion d'État Civil — Application console C++

Application console de gestion des demandes d'actes d'état civil (naissance, mariage, décès),
écrite en **C++ moderne** et pensée comme une démonstration complète de la
**programmation orientée objet**.

Le programme modélise un mini système de mairie : des usagers déposent des demandes
d'actes auprès de centres, des agents traitent ces demandes, et chaque dossier finalisé
calcule automatiquement son coût. Toute la logique métier (validations, calculs de primes,
gestion des demandes) est encapsulée dans des classes reliées par héritage, composition
et polymorphisme.

## Aperçu

L'exécution déroule un scénario complet dans une interface console soignée :

```
+================================================================+
|                       AGENTS ENREGISTRES                       |
+================================================================+

  - Officier #10 | Awa Ndiaye | Grade: Officier principal | ...
  - Stagiaire #11 | Modou Fall | Coef prime: 0.4 | Encadreur: Awa Ndiaye (#10)

  Primes pour 5 actes traites (polymorphisme) :
   - Awa Ndiaye         :    12500 FCFA
   - Modou Fall         :     1000 FCFA
```

Le même appel `calculerPrime(5)` produit deux résultats différents selon le type réel de
l'agent : c'est le polymorphisme en action.

## Fonctionnalités

- Enregistrement d'usagers avec attribution automatique d'un identifiant unique.
- Catalogue de centres d'état civil et d'actes civils.
- Dépôt d'une demande : choix du centre, de l'acte et du nombre de copies.
- Traitement d'une demande par un agent, avec calcul de prime propre à son grade.
- Génération d'un dossier finalisé et calcul de son coût total.
- Validation stricte des données à la création (exceptions en cas d'erreur).
- Recherche d'entités par identifiant via des opérateurs dédiés.

## Concepts C++ mis en œuvre

| Concept | Illustration dans le projet |
|---|---|
| Classe abstraite | `Personne` avec la méthode virtuelle pure `afficher()` |
| Héritage | `Usager`, `AgentEtatCivil` → `OfficierEtatCivil`, `AgentStagiaire` |
| Polymorphisme | `calculerPrime()` redéfinie, collection `vector<shared_ptr<AgentEtatCivil>>` |
| Pointeurs intelligents | `shared_ptr` pour éviter le slicing et gérer la mémoire |
| Surcharge d'opérateurs | `<<`, `>>`, `==`, `!=`, `[]` (usager par id), `()` (agent par id) |
| Encapsulation | attributs privés/protégés, accès via accesseurs et mutateurs validés |
| Exceptions | contrôles levant `std::invalid_argument` / `std::runtime_error` |
| Classe non dérivable | `DossierEtatCivil` marquée `final` |

## Architecture

Chaque classe est répartie sur un couple `.hpp` / `.cpp`.

```
Personne (abstraite)
├── Usager
└── AgentEtatCivil
      ├── OfficierEtatCivil
      └── AgentStagiaire

CentreEtatCivil · ActeCivil · DemandeActe · DossierEtatCivil (final)
GestionEtatCivil  ← orchestre l'ensemble
main.cpp          ← scénario de démonstration
```

`GestionEtatCivil` joue le rôle de façade : elle possède les listes d'objets (composition)
et fournit les méthodes d'ajout, de recherche et d'affichage.

## Prérequis

- Un compilateur C++ supportant **C++17** (g++ 9+, Clang, MSVC/MinGW).
- **CMake 3.16+** (fourni avec CLion).

## Compilation et exécution

### Avec CMake (ligne de commande)

```bash
cmake -S . -B build
cmake --build build
./build/etat_civil        # etat_civil.exe sous Windows
```

### Avec CLion

Ouvrir le dossier du projet (CLion détecte automatiquement `CMakeLists.txt`),
puis lancer la configuration `etat_civil`.

### Avec g++ directement

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -o etat_civil *.cpp
./etat_civil
```

Le programme est interactif : il demande quelques informations au clavier
(nom de l'usager, choix du centre et de l'acte, agent traitant, etc.).

## Utilisation

Une fois lancé, laissez-vous guider par les invites. Exemple de saisies :

| Invite | Exemple |
|---|---|
| Informations usager | Djimouna, BADJI, 770000001, Dakar, CNI-99 |
| Id du centre | 1 |
| Id de l'acte | 1 |
| Nombre de copies | 2 |
| Id de l'agent traitant | 10 |
| Délai de traitement | 4 |

Le programme affiche ensuite la demande, le dossier finalisé, un résumé du système,
puis une série de tests des opérateurs et de gestion d'erreurs.

## Structure du dépôt

```
.
├── *.hpp / *.cpp        # les classes du domaine
├── main.cpp             # point d'entrée et scénario
├── CMakeLists.txt       # configuration de build
└── README.md
```

## Auteur

**Djimouna Bacary BADJI** — étudiant en informatique (ISI Dakar, filière DITI).

Projet réalisé dans le cadre d'un module de programmation orientée objet en C++.
