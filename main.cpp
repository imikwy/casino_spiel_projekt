/*
Ein Leistungsprojekt im Unterricht von Herr Behrens erstellt von Pawel Ikwanty

Bei der festlegung der Anforderungen waren gegeben jewils 3 Sachen pro Schüler:
1. Eine verbesserte Optik des Programms durch nutzung von Ascii Code
2. Gewinner/Bestenliste die mit Namen und Coins ausgegeben wird, aber mit mit den meisten Coins absteigend sortiert wird
3. Ein Namenssystem mit der eingabe eines Nutzers, der Nutzer soll überprüft werden auf richtigkeit überprüft und ob sie nicht bereits vorhanden sind
    3.1 Wenn bereits vorhanden soll der User eine Auswahl bekommen ob er sich mit diesem Account anmelden will
    3.2 Wenn nicht soll der Benutzer eine möglichkeit bekommen einen Account zu erstellen

Der Nutzer gibt sein Namen ein, der Name wird in einer Negativliste überprüft, wenn der Name Legitim ist überpüft
das Programm ob der Nutzername bereits vorhanden ist oder nicht, wenn nicht kann der User einen neuen Account anlegen,
wenn es aber so ein Account gibt, muss der User aussuchen ob er mit dem account fortfahren will oder einen neuen erstellen möchte.

Im weiteren Verlauf gelangt der NUtzer in ein Mnu in dem er ein kleines Auswahl Menu bekommt:
1. Casion
2. Abmelden
3. Schlie0en
4. Bestenliste

Je nach Auswahl erfolgt ein weiterer Ablauf von entweder einem Spiel wo eine Zahl automatisch generiert wurde und der Nutzer
sie herrausfinden muss oder einer Abmeldung oder schließung des Programms, der Nutzer hat auch die möglichkeit
sich mit anderen zu vergleichen in einer Bestenliste die auf 10 Nutzer minimiert wurde, welches jedoch mit den unteren
Variablen leicht zu verändern ist.
*/

/*
TO-DO Liste:

- login:                                                                                            fertig
    - alle user aus txt einlesen                                                                    fertig
    - eingegebenen user finden und index des arrays aufnehmen                                       fertig
    - index des users verwenden um ihn als eingeloggt zu haben                                      fertig
    - userdaten abspeichern                                                                         fertig
    - bestenliste implementieren & sortieren                                                        fertig
-benutzer freundlicher aufbauen !                                                                   fertig
    - mehr erklärung hinzugefügt!                                                                   fertig
- für alles eigene funktionen machen wenn geht                                                      fertig
- ascii code schön machen                                                                           fertig
- Negativ Liste verbotene namen blocken                                                             fertig
- Bestenliste aktualiesiert nicht irgendwie
- Wenn der User 2 mal einen negativen Namen eingibt geht der Name durch das ganz böse
- BUUUUUUUUUUUUUUUUGGSGSGSGSG BEHEBEN !!!!!!!! ICH HASSE DAS ALLES HIER
- IMMERNOCH BUGGS UND IMMER MEHR BUGGSS JE MEHR ICH SCHREIBE
    LÖSUNGSANSAZT: AUFHÖREN ZU SCHREIBEN
- beim casino game verlust einbaune weil ganz vergessen irgendwie 828 Zeile
- Ausserdem eine möglichkeit finden was der User machen kann, wenn sein Guthaben gerade bei 0 liegt
*/

/*
Auflistung aller hinzugefügten externen Bibliotheken, fpr die Nutzung des Programms
*/
#include <iostream>     // Bibliothek für die Standart ein und ausgabe in einem cmd fenster
#include <iomanip>      // Bibliothek fpr manipulation von ausgaben
#include <fstream>      // Bibliothek für die Nutzung einer Text Datei als Speicherort für Daten
#include <string>       // Bibliothek für um die Nutzung von strings zu vereinfachen
#include <cstdlib>      // Bibliothek Für Zufallszahlen
#include <ctime>        // Bibliothek Für die time-Funktion
#include <windows.h>    // Bibliothek für die standard windows funktion (wollte ich nutzen um eingaben direkt über tastatur zu machen, am ende hatte ich aber doch keine lust:) )
#include <thread>       // Bibliothek um den sleep_for befehl zu nutzen für die Zeit ermitlung

using namespace std;    // Festlegung des standard namespace

/*
Variablen Liste für ASCII CODE
Doppelter Strich
*/
// Alle Ecken
char koRechts = 187;
char kuRechts = 188;
char kuLinks = 200;
char koLinks = 201;
// GErade mit orhtogonalen mit abzweigung so komisch
char geradeRechts = 204;
char geradeLinks = 185;
// Alle Geraden
char unten = 186;
char gerade = 205;

/*
Variablen Liste für ASCII CODE
Einzelner Strich
*/
// Alle geraden
char linieUnten = 179;
char linieGerade = 196;
//Ecken
char linieObenLinks = 218;
char linieObenRechts = 191;
char linieUntenLinks = 192;
char linieUntenRechts = 217;
//kreuz
char linieKreuz = 197;

/*
Variablen Liste für die notwendigen Daten im Programm

Variablen sind hier in abhängigkeiten aufgeteilt
Bsp: benutzerArray ist abhängig von der maxialen Nutzer anzahl maxuser = 300
*/
string txtDateiName = "Benutzernamen.txt";
const int maxuser = 300;                    // Konstante int (4 Byte) die, die anzahl der maximalen user bestimmt
string benutzerArray[maxuser];              // Eine Array string Variable die text speicher kann, die Anzahl der namen wird hier mit maxuser festgelegt
double benutzerGuthabenArray[maxuser];      // Eine Array double (8 byte) Varaible die Zahlen speichert

int benutzerAnzahl = 0;                     // verfolgt die Anzahl der angemeldeten nutzer

// maxbestenListe nicht verändern weil sonst echt dolle kapputt
const int maxbestenliste = 25;              // Konstante int (4 Byte) die, die anzahl der maximal Ausgegebnen user aus der bestenliste bestimmt
double bestenlisteGuthaben[maxbestenliste]; // Array in dem die bestenliste gespeicher und ausgegeben wird
string bestenlisteNamen[maxbestenliste];    // array für die dazu gehörigen namen

/*
Variablen Liste für die negativ Liste für die benutzernamen
*/
const string negativListe[] = { "Nigga", "NIGGA", "HITLER", "Hitler", "hitler", "Adolf", "ADOLF", "911", "Penis", "PENIS"};
const int negativListeSize = sizeof(negativListe) / sizeof(negativListe[0]);    // Da die länge der Negativ liste nicht einfach zu ermitelln ist wirds so gemacht

// NICHT ALLE VARIABLEN DIE UNTEN BENUTZT WERDEN SIND HIER! NUR FÜR DIE ÜBERSICHT! SONSNHT ECHT ANSTRENGEDN

int main();// UM KEICHETER ZWISCHEN FUNKTIONEN ZU SRPINGEN

/*
Eine Boolean Funktion die, den vom User ein eingegebnen Nutzernamen bekommt und ihn überprüft
Wenn der Nutzername in der negativLite gefunden wurde kommt ein true (1),
wenn nicht ein false(0)
*/
bool negativSuche(string benutzername)
{
    for (int i = 0; i < negativListeSize; i++)
    {
        if (benutzername == negativListe[i])
        {
            return true; // Benutzername ist in der Negativliste
        }
    }
    return false; // Benutzername ist nicht in der Negativliste
}

/*
Eine void BenutzerEinlesen funktion, die keine Werte ausgibt sonder sie nur aus der Text Datei in die arrays zuteilt
*/
void txtDatenLesen()
{
    ifstream datei(txtDateiName);
    string benutzername;
    double guthaben;

    while (datei >> benutzername >> guthaben)
    {
        benutzerArray[benutzerAnzahl] = benutzername;
        benutzerGuthabenArray[benutzerAnzahl] = guthaben;
        benutzerAnzahl++;
    }

    datei.close();
}

/*
Funktion zum speichern von Benutzerdaten in einer Text Datei, die Daten werden nebeneinander mit einer Leertaste abstand gespeichert

Funktion wird nach jedem mal gespeichert wo der Nutzer das Casino game gespielt hat
*/
void txtDatenSpeichern(string benutzername)
{
    ofstream datei(txtDateiName);

    for (int i = 0; i < benutzerAnzahl; i++)
    {
        datei << benutzerArray[i] << " " << benutzerGuthabenArray[i] << endl;
    }

    datei.close();
}

/*
Eigentlich eine überschüssige funktion jedoch hat sie mir mein leben erleichtert, die Funktion findet den Index des gerade eingegeben Usernamens herraus,
mit diesem Index wird das Programm arbeiten während der Nutzer angemeldet bleibt :)
*/
int findeNutzer(string benutzername)
{
    for (int i = 0; i < benutzerAnzahl; i++)
    {
        if (benutzerArray[i] == benutzername)
        {
            return i;
        }
    }
    return -1;
}

/*
void Funktion das sie keine Ausgaben hat, zum sortieren von den Usern in dem array und in der textdatei
*/
void bestenlisteSortieren()
{
    for (int i = 0; i < benutzerAnzahl; i++)
    {
        bestenlisteGuthaben[i] = benutzerGuthabenArray[i];
        bestenlisteNamen[i] = benutzerArray[i];
    }

    for (int i = 0; i < benutzerAnzahl - 1; i++)
    {
        for (int j = i + 1; j < benutzerAnzahl; j++)
        {
            if (bestenlisteGuthaben[j] > bestenlisteGuthaben[i])
            {
                // Manuelle Sortierung wie im unterricht temp = temporär

                double tempGuthaben = bestenlisteGuthaben[i];
                bestenlisteGuthaben[i] = bestenlisteGuthaben[j];
                bestenlisteGuthaben[j] = tempGuthaben;

                string tempName = bestenlisteNamen[i];
                bestenlisteNamen[i] = bestenlisteNamen[j];
                bestenlisteNamen[j] = tempName;
            }
        }
    }
}

/*
Eine kurze Funktion zum Ausgeben der davor sortierten Bestenliste
*/
void bestenliste()
{
    system("cls");

    bestenlisteSortieren();

    int anzeigen = min(benutzerAnzahl, maxbestenliste); // Anzahl der Spieler in der Bestenliste

    cout << koLinks;
    for (int i = 120 - 2; i > 0; i--) //breite
    {
        cout << gerade;
    }
    cout << koRechts << endl;

    cout << unten << " BBS2 Casino/GuessTheNumber                                                                                       _ x " << unten << endl;

    cout << geradeRechts;
    for (int i = 120 - 2; i > 0; i--) //breite
    {
        cout << gerade;
    }
    cout << geradeLinks << endl;

    cout << unten << "                                                                             ";
    cout << linieObenLinks;
    for (int i = 40 - 2; i > 0; i--) //breite
    {
        cout << linieGerade;
    }
    cout << linieObenRechts;
    cout << " " << unten << endl;

    cout << unten << "                          > BESTENLISTE - TOP 25 <                           " << linieUnten << "      [!]   NICHT ANGEZEIGT   [!]     " << linieUnten << " " << unten << endl;

    cout << unten << "                                                                             ";
    cout << linieUntenLinks;
    for (int i = 40 - 2; i > 0; i--) //breite
    {
        cout << linieGerade;
    }
    cout << linieUntenRechts;
    cout << " " << unten << endl;
    cout << unten << "        Pos." << linieUnten << "           Name " << linieUnten << "           Coins                                                                        " << unten << endl;
    cout << unten << "        "<< linieGerade << linieGerade << linieGerade << linieGerade << linieKreuz << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieKreuz << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << "                             " << linieUnten << " > J zum zueruckkehren zum Menu         " << unten << endl;
    for (int i = 0; i < anzeigen; i++)
    {
        cout << unten << "         " << setw(2) << i + 1 << " " << linieUnten <<" " << setw(14) << bestenlisteNamen[i] << " " << linieUnten << " " << setw(15) << setprecision(14) << benutzerGuthabenArray[i] << "                               " << linieUnten << "                                        " << unten << endl;
    }

    for (int i = anzeigen; i < maxbestenliste; i++)
    {
        cout << unten << "         " << setw(2) << i + 1 << " " << linieUnten << "                " << linieUnten << "                                               " << linieUnten << "                                        " << unten << endl;
    }

    cout << unten << "                                                                             " << linieUnten << "                                        " << unten << endl;
    cout << unten << "                                                                                                                      " << unten << endl;

    cout << kuLinks;

    for (int i = 120 - 2; i > 0; i--) // breite
    {
        cout << gerade;
    }
    cout << kuRechts << endl;
}

void loginNutzer(string benutzername)
{
    if (negativSuche(benutzername))
    {

        system("cls"); // Damits schöner aussieht ... oder so, vlt
        cout << koLinks;
        for (int i = 40 - 2; i > 0; i--) //breite
        {
            cout << gerade;
        }
        cout << koRechts; cout << endl;

        cout << unten << "                                      " << unten << endl;
        cout << unten << "                LOGIN                 " << unten << endl;
        cout << unten << "   ________________________________   " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "     Benutzername: ______________     " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "  [!] Dieser Benutzername ist in der  " << unten << endl;
        cout << unten << "      Negativliste.                   " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "  [!] Bei erneuter falscher Eingabe   " << unten << endl;
        cout << unten << "      kehrst du zum Startzurueck!     " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "  [!] Bitte geben Sie Ihren Namen     " << unten << endl;
        cout << unten << "      erneut ein.                     " << unten << endl;
        cout << unten << "   ________________________________   " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "          " << linieObenLinks << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieObenRechts << "           " << unten << endl;
        cout << unten << "          " << linieUnten << "     ENTER     " << linieUnten << "           " << unten << endl;
        cout << unten << "          " << linieUntenLinks << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieUntenRechts << "           " << unten << endl;
        cout << unten << "                                      " << unten << endl;

        cout << kuLinks;
        for (int i = 40 - 2; i > 0; i--) //breite
        {
            cout << gerade;
        }
        cout << kuRechts; cout << endl;

        cin >> benutzername;
        if (negativSuche(benutzername)) {
            main();
        }
    }

    int index = findeNutzer(benutzername);

    if (index != -1)
    {

        system("cls"); // Damits schöner aussieht ... oder so, vlt

        cout << koLinks;
        for (int i = 40 - 2; i > 0; i--) //breite
        {
            cout << gerade;
        }
        cout << koRechts; cout << endl;

        cout << unten << "                                      " << unten << endl;
        cout << unten << "                LOGIN                 " << unten << endl;
        cout << unten << "   ________________________________   " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "     Benutzername: " << setw(14) << benutzername << "     " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "  [!] Dieser Benutzername wurde       " << unten << endl;
        cout << unten << "      bereits gefunden.               " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "  [!] Moechtest du dich mit diesem    " << unten << endl;
        cout << unten << "      Account anmelden?               " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "       (j) = JA     (n) = NEIN        " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "   ________________________________   " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "       " << linieObenLinks << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieObenRechts << "      " << linieObenLinks << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieObenRechts << "       " << unten << endl;
        cout << unten << "       " << linieUnten << "  (j)  " << linieUnten << "      " << linieUnten << "  (n)  " << linieUnten << "       " << unten << endl;
        cout << unten << "       " << linieUntenLinks << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieUntenRechts << "      " << linieUntenLinks << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieUntenRechts << "       " << unten << endl;
        cout << unten << "                                      " << unten << endl;

        cout << kuLinks;
        for (int i = 40 - 2; i > 0; i--) //breite
        {
            cout << gerade;
        }
        cout << kuRechts; cout << endl;

        char anmeldungAuswahl;
        cout << "Auswahl: ";
        cin >> anmeldungAuswahl;

        if (anmeldungAuswahl == 'j' || anmeldungAuswahl == 'J')
        {

            // Benutzer möchte sich mit dem vorhandenen Benutzer anmelden
            bool zurueckZumMenu = false;
            system("cls");
            while (!zurueckZumMenu)
            {
                cout << koLinks;
                for (int i = 120 - 2; i > 0; i--) //breite
                {
                    cout << gerade;
                }
                cout << koRechts << endl;

                cout << unten << " BBS2 Casino                                                                                                      _ x " << unten << endl;

                cout << geradeRechts;
                for (int i = 120 - 2; i > 0; i--) //breite
                {
                    cout << gerade;
                }
                cout << geradeLinks << endl;

                cout << unten << "                                                                             ";
                cout << linieObenLinks;
                for (int i = 40 - 2; i > 0; i--) //breite
                {
                    cout << linieGerade;
                }
                cout << linieObenRechts;
                cout << " " << unten << endl;

                cout << unten << "                    > WILLKOMMEN IM BBS2 CASINO SPIEL <                      " << linieUnten << "Nutzer:" << setw(14) << benutzerArray[index] << "|" << setw(10) << setprecision(9) << benutzerGuthabenArray[index] << " Coins" << linieUnten << " " << unten << endl;

                cout << unten << "                                                                             ";
                cout << linieUntenLinks;
                for (int i = 40 - 2; i > 0; i--) //breite
                {
                    cout << linieGerade;
                }
                cout << linieUntenRechts;
                cout << " " << unten << endl;
                cout << unten << "                                                                                                                      " << unten << endl;
                cout << unten << "                                                                             " << linieUnten << "                                        " << unten << endl;
                cout << unten << "       Menu:                                                                 " << linieUnten << "                                        " << unten << endl;
                cout << unten << "                                                                             " << linieUnten << "                                        " << unten << endl;
                cout << unten << "            1. Nummer erraten                                                " << linieUnten << "      ,-----.                           " << unten << endl;
                cout << unten << "            2. Comming soon...                                               " << linieUnten << "      |  |) /_                          " << unten << endl;
                cout << unten << "                                                                             " << linieUnten << "      |  .-.  |                         " << unten << endl;
                cout << unten << "                                                                             " << linieUnten << "      |  '--' /                         " << unten << endl;
                cout << unten << "                                                                             " << linieUnten << "      `------'                          " << unten << endl;
                cout << unten << "                                                                             " << linieUnten << "            ,-----.                     " << unten << endl;
                cout << unten << "                                                                             " << linieUnten << "            |  |) /_                    " << unten << endl;
                cout << unten << "            8. Bestenliste anzeigen                                          " << linieUnten << "            |  .-.  |                   " << unten << endl;
                cout << unten << "            9. Abmelden                                                      " << linieUnten << "            |  '--' /                   " << unten << endl;
                cout << unten << "            0. Schliessen                                                    " << linieUnten << "            `------'                    " << unten << endl;
                cout << unten << "                                                                             " << linieUnten << "                   ,---.                " << unten << endl;
                cout << unten << "                                                                             " << linieUnten << "                  '   .-'               " << unten << endl;
                cout << unten << "                                                                             " << linieUnten << "                  `.  `-.               " << unten << endl;
                cout << unten << "                                                                             " << linieUnten << "                  .-'    |              " << unten << endl;
                cout << unten << "                                                                             " << linieUnten << "                  `-----'               " << unten << endl;
                cout << unten << "         ";

                cout << linieObenLinks;
                for (int i = 59 - 2; i > 0; i--) //breite
                {
                    cout << linieGerade;
                }
                cout << linieObenRechts;

                cout << "         " << linieUnten << "                        ,---.           " << unten << endl;
                cout << unten << "         " << linieUnten << " > Waehle eine Option aus                                " << linieUnten << "         " << linieUnten << "                       '.-.  |          " << unten << endl;
                cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                        .-' .'          " << unten << endl;
                cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                       /   '-.          " << unten << endl;
                cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                       '-----'          " << unten << endl;
                cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                cout << unten << "         " << linieUnten << " > Falsche eingabe: Neustart                             " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                cout << unten << "         ";

                cout << linieUntenLinks;
                for (int i = 59 - 2; i > 0; i--) //breite
                {
                    cout << linieGerade;
                }
                cout << linieUntenRechts;

                cout << "         " << linieUnten << "                                        " << unten << endl;
                cout << unten << "                                                                                                                      " << unten << endl;

                cout << kuLinks;

                for (int i = 120 - 2; i > 0; i--) // breite
                {
                    cout << gerade;
                }
                cout << kuRechts << endl;

                cout << "Auswahl: ";

                int auswahl;
                cin >> auswahl;

                if (auswahl == 1)
                {
                    system("cls");
                    // Casino Guess The Number Spiel
                    int zielZahl = rand() % 100 + 1;
                    double guthaben = benutzerGuthabenArray[index];

                    cout << koLinks;
                    for (int i = 120 - 2; i > 0; i--) //breite
                    {
                        cout << gerade;
                    }
                    cout << koRechts << endl;

                    cout << unten << " BBS2 Casino/GuessTheNumber                                                                                       _ x " << unten << endl;

                    cout << geradeRechts;
                    for (int i = 120 - 2; i > 0; i--) //breite
                    {
                        cout << gerade;
                    }
                    cout << geradeLinks << endl;

                    cout << unten << "                                                                             ";
                    cout << linieObenLinks;
                    for (int i = 40 - 2; i > 0; i--) //breite
                    {
                        cout << linieGerade;
                    }
                    cout << linieObenRechts;
                    cout << " " << unten << endl;

                    cout << unten << "                            > GUESS THE NUMBER <                             " << linieUnten << "Nutzer:" << setw(14) << benutzerArray[index] << "|" << setw(10) << setprecision(9) << benutzerGuthabenArray[index] << " Coins" << linieUnten << " " << unten << endl;

                    cout << unten << "                                                                             ";
                    cout << linieUntenLinks;
                    for (int i = 40 - 2; i > 0; i--) //breite
                    {
                        cout << linieGerade;
                    }
                    cout << linieUntenRechts;
                    cout << " " << unten << endl;
                    cout << unten << "                                                                                                                      " << unten << endl;
                    cout << unten << "                                                                             " << linieUnten << "                                        " << unten << endl;
                    cout << unten << "       Ablauf:                                                               " << linieUnten << "                                        " << unten << endl;
                    cout << unten << "                                                                             " << linieUnten << "                                        " << unten << endl;
                    cout << unten << "            [1] Du wettest eine Summe                                        " << linieUnten << "      ,-----.                           " << unten << endl;
                    cout << unten << "            [2] Das Programm generiert Zahl: 1 - 100                         " << linieUnten << "      |  |) /_                          " << unten << endl;
                    cout << unten << "            [3] Du hast 7 Chancen                                            " << linieUnten << "      |  .-.  |                         " << unten << endl;
                    cout << unten << "            [4] Gibst deine gewaehlte Zahl ein                               " << linieUnten << "      |  '--' /                         " << unten << endl;
                    cout << unten << "            [5] Zahl wird geprueft auf richtigkeit                           " << linieUnten << "      `------'                          " << unten << endl;
                    cout << unten << "               [5.1] Wenn gleich: gewonnen                                   " << linieUnten << "            ,-----.                     " << unten << endl;
                    cout << unten << "               [5.2] Wenn nicht: naechste Chance                             " << linieUnten << "            |  |) /_                    " << unten << endl;
                    cout << unten << "                                                                             " << linieUnten << "            |  .-.  |                   " << unten << endl;
                    cout << unten << "                                                                             " << linieUnten << "            |  '--' /                   " << unten << endl;
                    cout << unten << "                                                                             " << linieUnten << "            `------'                    " << unten << endl;
                    cout << unten << "                                                                             " << linieUnten << "                   ,---.                " << unten << endl;
                    cout << unten << "                                                                             " << linieUnten << "                  '   .-'               " << unten << endl;
                    cout << unten << "                                                                             " << linieUnten << "                  `.  `-.               " << unten << endl;
                    cout << unten << "                                                                             " << linieUnten << "                  .-'    |              " << unten << endl;
                    cout << unten << "                                                                             " << linieUnten << "                  `-----'               " << unten << endl;
                    cout << unten << "         ";

                    cout << linieObenLinks;
                    for (int i = 59 - 2; i > 0; i--) //breite
                    {
                        cout << linieGerade;
                    }
                    cout << linieObenRechts;

                    cout << "         " << linieUnten << "                        ,---.           " << unten << endl;
                    cout << unten << "         " << linieUnten << " > Waehle einen Wetteinsatz                              " << linieUnten << "         " << linieUnten << "                       '.-.  |          " << unten << endl;
                    cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                        .-' .'          " << unten << endl;
                    cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                       /   '-.          " << unten << endl;
                    cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                       '-----'          " << unten << endl;
                    cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                    cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                    cout << unten << "         " << linieUnten << " > Falsche eingabe: Neustart                             " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                    cout << unten << "         ";

                    cout << linieUntenLinks;
                    for (int i = 59 - 2; i > 0; i--) //breite
                    {
                        cout << linieGerade;
                    }
                    cout << linieUntenRechts;

                    cout << "         " << linieUnten << "                                        " << unten << endl;
                    cout << unten << "                                                                                                                      " << unten << endl;

                    cout << kuLinks;

                    for (int i = 120 - 2; i > 0; i--) // breite
                    {
                        cout << gerade;
                    }
                    cout << kuRechts << endl;

                    double einsatz;
                    cout << "Wettinsatz: ";
                    cin >> einsatz;

                    if (einsatz > guthaben || einsatz <= 0)
                    {
                        cout << "Falscher Einsatz." << endl;
                    }
                    else {

                        benutzerGuthabenArray[index] = benutzerGuthabenArray[index] - einsatz;
                        guthaben = benutzerGuthabenArray[index];
                        int tipp;
                        for (int versuche = 1; versuche <= 7; versuche++)
                        {
                            system("cls");

                            cout << koLinks;
                            for (int i = 120 - 2; i > 0; i--) //breite
                            {
                                cout << gerade;
                            }
                            cout << koRechts << endl;

                            cout << unten << " BBS2 Casino/GuessTheNumber                                                                                       _ x " << unten << endl;

                            cout << geradeRechts;
                            for (int i = 120 - 2; i > 0; i--) //breite
                            {
                                cout << gerade;
                            }
                            cout << geradeLinks << endl;

                            cout << unten << "                                                                             ";
                            cout << linieObenLinks;
                            for (int i = 40 - 2; i > 0; i--) //breite
                            {
                                cout << linieGerade;
                            }
                            cout << linieObenRechts;
                            cout << " " << unten << endl;

                            cout << unten << "                            > GUESS THE NUMBER <                             " << linieUnten << "Nutzer:" << setw(14) << benutzerArray[index] << "|" << setw(10) << setprecision(9) << benutzerGuthabenArray[index] << " Coins" << linieUnten << " " << unten << endl;

                            cout << unten << "                                                                             ";
                            cout << linieUntenLinks;
                            for (int i = 40 - 2; i > 0; i--) //breite
                            {
                                cout << linieGerade;
                            }
                            cout << linieUntenRechts;
                            cout << " " << unten << endl;
                            cout << unten << "                                                                                                                      " << unten << endl;
                            cout << unten << "                                                                             " << linieUnten << "                                        " << unten << endl;
                            cout << unten << "       Ablauf:                                                               " << linieUnten << "                                        " << unten << endl;
                            cout << unten << "                                                                             " << linieUnten << "                                        " << unten << endl;
                            cout << unten << "            [1] Du wettest eine Summe                                        " << linieUnten << "      ,-----.                           " << unten << endl;
                            cout << unten << "            [2] Das Programm generiert Zahl: 1 - 100                         " << linieUnten << "      |  |) /_                          " << unten << endl;
                            cout << unten << "            [3] Du hast 7 Chancen                                            " << linieUnten << "      |  .-.  |                         " << unten << endl;
                            cout << unten << "            [4] Gibst deine gewaehlte Zahl ein                               " << linieUnten << "      |  '--' /                         " << unten << endl;
                            cout << unten << "            [5] Zahl wird geprueft auf richtigkeit                           " << linieUnten << "      `------'                          " << unten << endl;
                            cout << unten << "               [5.1] Wenn gleich: gewonnen                                   " << linieUnten << "            ,-----.                     " << unten << endl;
                            cout << unten << "               [5.2] Wenn nicht: naechste Chance                             " << linieUnten << "            |  |) /_                    " << unten << endl;
                            cout << unten << "                                                                             " << linieUnten << "            |  .-.  |                   " << unten << endl;
                            cout << unten << "       Informationen:                                                        " << linieUnten << "            |  '--' /                   " << unten << endl;
                            cout << unten << "                                                                             " << linieUnten << "            `------'                    " << unten << endl;
                            cout << unten << "            > Dein Wetteinsatz: " << setw(10) << setprecision(9) << einsatz << "                                   " << linieUnten << "                   ,---.                " << unten << endl;
                            cout << unten << "            > Uebrige Versuche: " << setw(2) << setprecision(7) << (7 - versuche) + 1 << "                                           " << linieUnten << "                  '   .-'               " << unten << endl;

                            if (versuche == 1) {
                                cout << unten << "                                                                             " << linieUnten << "                  `.  `-.               " << unten << endl;
                            }
                            else
                            {
                                cout << unten << "            > Letzte Zahl: " << setw(2) << tipp << "                                                " << linieUnten << "                  `.  `-.               " << unten << endl;
                            }

                            if (versuche == 1) {
                                cout << unten << "                                                                             " << linieUnten << "                  .-'    |              " << unten << endl;
                            }
                            else if (tipp < zielZahl)
                            {
                                // gesuchte zahl ist groesser
                                cout << unten << "            > Hinweis: Gesuchte Zahl ist groesser                            " << linieUnten << "                  .-'    |              " << unten << endl;
                            }
                            else if (tipp > zielZahl)
                            {
                                // gesuchte zahl ist klehner
                                cout << unten << "            > Hinweis: Gesuchte Zahl ist kleiner                             " << linieUnten << "                  .-'    |              " << unten << endl;
                            }
                            cout << unten << "                                                                             " << linieUnten << "                  `-----'               " << unten << endl;
                            cout << unten << "         ";

                            cout << linieObenLinks;
                            for (int i = 59 - 2; i > 0; i--) //breite
                            {
                                cout << linieGerade;
                            }
                            cout << linieObenRechts;

                            cout << "         " << linieUnten << "                        ,---.           " << unten << endl;
                            cout << unten << "         " << linieUnten << " > Tippe ein Zahl                                        " << linieUnten << "         " << linieUnten << "                       '.-.  |          " << unten << endl;
                            cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                        .-' .'          " << unten << endl;
                            cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                       /   '-.          " << unten << endl;
                            cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                       '-----'          " << unten << endl;
                            cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                            cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                            cout << unten << "         " << linieUnten << " > Falsche eingabe: Neustart                             " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                            cout << unten << "         ";

                            cout << linieUntenLinks;
                            for (int i = 59 - 2; i > 0; i--) //breite
                            {
                                cout << linieGerade;
                            }
                            cout << linieUntenRechts;

                            cout << "         " << linieUnten << "                                        " << unten << endl;
                            cout << unten << "                                                                                                                      " << unten << endl;

                            cout << kuLinks;

                            for (int i = 120 - 2; i > 0; i--) // breite
                            {
                                cout << gerade;
                            }
                            cout << kuRechts << endl;

                            cout << "Eingabe: ";
                            cin >> tipp;

                            if (tipp == zielZahl)
                            {
                                double gewinn = einsatz * 2;
                                guthaben += gewinn;
                                benutzerGuthabenArray[index] = guthaben;
                                system("cls");

                                cout << koLinks;
                                for (int i = 120 - 2; i > 0; i--) //breite
                                {
                                    cout << gerade;
                                }
                                cout << koRechts << endl;

                                cout << unten << " BBS2 Casino/GuessTheNumber                                                                                       _ x " << unten << endl;

                                cout << geradeRechts;
                                for (int i = 120 - 2; i > 0; i--) //breite
                                {
                                    cout << gerade;
                                }
                                cout << geradeLinks << endl;

                                cout << unten << "                                                                             ";
                                cout << linieObenLinks;
                                for (int i = 40 - 2; i > 0; i--) //breite
                                {
                                    cout << linieGerade;
                                }
                                cout << linieObenRechts;
                                cout << " " << unten << endl;

                                cout << unten << "                            > GUESS THE NUMBER <                             " << linieUnten << "Nutzer:" << setw(14) << benutzerArray[index] << "|" << setw(10) << setprecision(9) << benutzerGuthabenArray[index] << " Coins" << linieUnten << " " << unten << endl;

                                cout << unten << "                                                                             ";
                                cout << linieUntenLinks;
                                for (int i = 40 - 2; i > 0; i--) //breite
                                {
                                    cout << linieGerade;
                                }
                                cout << linieUntenRechts;
                                cout << " " << unten << endl;
                                cout << unten << "                                                                                                                      " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "                       GLUECKWUNSCH DU HAST GEWONNEN                         " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "            > Dein gewetter Betrag: " << setw(10) << setprecision(9) << einsatz << "                               " << linieUnten << "      ,-----.                           " << unten << endl;
                                cout << unten << "            > Dein gewonnener Betrag " << setw(10) << setprecision(9) << gewinn <<  "                              " << linieUnten << "      |  |) /_                          " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "      |  .-.  |                         " << unten << endl;
                                cout << unten << "            > Viel Glueck und Spass beim weiteren Spielen                    " << linieUnten << "      |  '--' /                         " << unten << endl;
                                cout << unten << "            > Du kehrst mit j zum Menu zurueck                               " << linieUnten << "      `------'                          " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "            ,-----.                     " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "            |  |) /_                    " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "            |  .-.  |                   " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "            |  '--' /                   " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "            `------'                    " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                   ,---.                " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                  '   .-'               " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                  `.  `-.               " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                  .-'    |              " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                  `-----'               " << unten << endl;
                                cout << unten << "         ";

                                cout << linieObenLinks;
                                for (int i = 59 - 2; i > 0; i--) //breite
                                {
                                    cout << linieGerade;
                                }
                                cout << linieObenRechts;

                                cout << "         " << linieUnten << "                        ,---.           " << unten << endl;
                                cout << unten << "         " << linieUnten << " > Druecke j und bestaetige mit Enter                    " << linieUnten << "         " << linieUnten << "                       '.-.  |          " << unten << endl;
                                cout << unten << "         " << linieUnten << "   zum zurueckkehren                                     " << linieUnten << "         " << linieUnten << "                        .-' .'          " << unten << endl;
                                cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                       /   '-.          " << unten << endl;
                                cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                       '-----'          " << unten << endl;
                                cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "         " << linieUnten << " > Falsche eingabe: Neustart                             " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "         ";

                                cout << linieUntenLinks;
                                for (int i = 59 - 2; i > 0; i--) //breite
                                {
                                    cout << linieGerade;
                                }
                                cout << linieUntenRechts;

                                cout << "         " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "                                                                                                                      " << unten << endl;

                                cout << kuLinks;

                                for (int i = 120 - 2; i > 0; i--) // breite
                                {
                                    cout << gerade;
                                }
                                cout << kuRechts << endl;

                                char gewinnAuswahl;

                                cout << "Eingabe: ";
                                cin >> gewinnAuswahl;
                                if (gewinnAuswahl == 'j' || gewinnAuswahl == 'J')
                                {
                                    system("cls");
                                    break;
                                }
                            }
                            else if(versuche >= 7 && tipp != zielZahl)
                            {
                                //verloren

                                system("cls");
                                cout << koLinks;
                                for (int i = 120 - 2; i > 0; i--) //breite
                                {
                                    cout << gerade;
                                }
                                cout << koRechts << endl;

                                cout << unten << " BBS2 Casino/GuessTheNumber                                                                                       _ x " << unten << endl;

                                cout << geradeRechts;
                                for (int i = 120 - 2; i > 0; i--) //breite
                                {
                                    cout << gerade;
                                }
                                cout << geradeLinks << endl;

                                cout << unten << "                                                                             ";
                                cout << linieObenLinks;
                                for (int i = 40 - 2; i > 0; i--) //breite
                                {
                                    cout << linieGerade;
                                }
                                cout << linieObenRechts;
                                cout << " " << unten << endl;

                                cout << unten << "                            > GUESS THE NUMBER <                             " << linieUnten << "Nutzer:" << setw(14) << benutzerArray[index] << "|" << setw(10) << setprecision(9) << benutzerGuthabenArray[index] << " Coins" << linieUnten << " " << unten << endl;

                                cout << unten << "                                                                             ";
                                cout << linieUntenLinks;
                                for (int i = 40 - 2; i > 0; i--) //breite
                                {
                                    cout << linieGerade;
                                }
                                cout << linieUntenRechts;
                                cout << " " << unten << endl;
                                cout << unten << "                                                                                                                      " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "                          DU HAST LEIDER VERLOREN                            " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "            > Dein gewetter Betrag: " << setw(10) << setprecision(9) << einsatz << "                               " << linieUnten << "      ,-----.                           " << unten << endl;
                                cout << unten << "            > Dein neuer Kontostand: " << setw(10) << setprecision(9) << guthaben << "                              " << linieUnten << "      |  |) /_                          " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "      |  .-.  |                         " << unten << endl;
                                cout << unten << "            > Viel Glueck und Spass beim weiteren Spielen                    " << linieUnten << "      |  '--' /                         " << unten << endl;
                                cout << unten << "            > Du kehrst mit j zum Menu zurueck                               " << linieUnten << "      `------'                          " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "            ,-----.                     " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "            |  |) /_                    " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "            |  .-.  |                   " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "            |  '--' /                   " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "            `------'                    " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                   ,---.                " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                  '   .-'               " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                  `.  `-.               " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                  .-'    |              " << unten << endl;
                                cout << unten << "                                                                             " << linieUnten << "                  `-----'               " << unten << endl;
                                cout << unten << "         ";

                                cout << linieObenLinks;
                                for (int i = 59 - 2; i > 0; i--) //breite
                                {
                                    cout << linieGerade;
                                }
                                cout << linieObenRechts;

                                cout << "         " << linieUnten << "                        ,---.           " << unten << endl;
                                cout << unten << "         " << linieUnten << " > Druecke j und bestaetige mit Enter                    " << linieUnten << "         " << linieUnten << "                       '.-.  |          " << unten << endl;
                                cout << unten << "         " << linieUnten << "   zum zurueckkehren                                     " << linieUnten << "         " << linieUnten << "                        .-' .'          " << unten << endl;
                                cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                       /   '-.          " << unten << endl;
                                cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                       '-----'          " << unten << endl;
                                cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "         " << linieUnten << "                                                         " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "         " << linieUnten << " > Falsche eingabe: Neustart                             " << linieUnten << "         " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "         ";

                                cout << linieUntenLinks;
                                for (int i = 59 - 2; i > 0; i--) //breite
                                {
                                    cout << linieGerade;
                                }
                                cout << linieUntenRechts;

                                cout << "         " << linieUnten << "                                        " << unten << endl;
                                cout << unten << "                                                                                                                      " << unten << endl;

                                cout << kuLinks;

                                for (int i = 120 - 2; i > 0; i--) // breite
                                {
                                    cout << gerade;
                                }
                                cout << kuRechts << endl;

                                char verlorenAuswahl;

                                cout << "Eingabe: ";
                                cin >> verlorenAuswahl;
                                if (verlorenAuswahl == 'j' || verlorenAuswahl == 'J')
                                {
                                    system("cls");
                                    break;
                                }
                            }
                        }
                        // Aktualisieren Sie das Guthaben
                        benutzerGuthabenArray[index] = guthaben;
                        txtDatenSpeichern(benutzername);
                    }
                }
                else if (auswahl == 8)
                {
                    // Bestenliste anzeigen
                    bestenliste();
                    cout << "Eingabe: ";
                    char zurueck;
                    cin >> zurueck;
                    if (zurueck == 'j' || zurueck == 'J')
                    {
                        system("cls");
                        continue;
                    }
                }
                else if (auswahl == 9)
                {
                    main();
                    break;  // Beenden Sie die Schleife, um zur erneuten Anmeldung zu gelangen
                }
                else if (auswahl == 1945)
                {
                    benutzerGuthabenArray[index] += 10000;
                    txtDatenSpeichern(benutzername);
                    system("cls");
                }
                else if (auswahl == 0)
                {
                    return;
                }
                else
                {
                    system("cls");
                }
            }
        }
        else
        {
            main();
        }
    }
    else
    {
        system("cls");
        cout << koLinks;
        for (int i = 40 - 2; i > 0; i--) //breite
        {
            cout << gerade;
        }
        cout << koRechts; cout << endl;

        cout << unten << "                                      " << unten << endl;
        cout << unten << "                LOGIN                 " << unten << endl;
        cout << unten << "   ________________________________   " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "     Benutzername: " << setw(14) << benutzername << "     " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "  [!] Dieser Benutzername wurde       " << unten << endl;
        cout << unten << "      nicht gefunden.                 " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "  [!] Moechtest du diesen Benutzer    " << unten << endl;
        cout << unten << "      erstellen?                      " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "       (j) = JA     (n) = NEIN        " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "   ________________________________   " << unten << endl;
        cout << unten << "                                      " << unten << endl;
        cout << unten << "       " << linieObenLinks << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieObenRechts << "      " << linieObenLinks << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieObenRechts << "       " << unten << endl;
        cout << unten << "       " << linieUnten << "  (j)  " << linieUnten << "      " << linieUnten << "  (n)  " << linieUnten << "       " << unten << endl;
        cout << unten << "       " << linieUntenLinks << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieUntenRechts << "      " << linieUntenLinks << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieUntenRechts << "       " << unten << endl;
        cout << unten << "                                      " << unten << endl;

        cout << kuLinks;
        for (int i = 40 - 2; i > 0; i--) //breite
        {
            cout << gerade;
        }
        cout << kuRechts; cout << endl;

        cout << "Eingabe: ";
        char auswahl;
        cin >> auswahl;

        if (auswahl == 'j' || auswahl == 'J')
        {
            benutzerArray[benutzerAnzahl] = benutzername;
            benutzerGuthabenArray[benutzerAnzahl] = 10000.0;  // Startguthaben als Gleitkommazahl
            benutzerAnzahl++;
            txtDatenSpeichern(benutzername);
            cout << "Neuer Benutzer " << benutzername << " erstellt." << endl;

            // Direkt zur Anmeldung weiterleiten
            loginNutzer(benutzername);
        }
        else
        {
            main();
        }
    }
}

int main()
{
    srand(static_cast<unsigned>(time(0)));  // Zufallszahlengenerator initialisieren

    txtDatenLesen();

    system("cls"); // Damits schöner aussieht ... vlt

    cout << koLinks;
    for (int i = 40 - 2; i > 0; i--) //breite
    {
        cout << gerade;
    }
    cout << koRechts; cout << endl;

    cout << unten << "                                      " << unten << endl;
    cout << unten << "                LOGIN                 " << unten << endl;
    cout << unten << "   ________________________________   " << unten << endl;
    cout << unten << "                                      " << unten << endl;
    cout << unten << "                                      " << unten << endl;
    cout << unten << "                                      " << unten << endl;
    cout << unten << "                                      " << unten << endl;
    cout << unten << "                                      " << unten << endl;
    cout << unten << "     Benutzername: ______________     " << unten << endl;
    cout << unten << "                                      " << unten << endl;
    cout << unten << "  [!] Bevor Sie fortfahren, bitte     " << unten << endl;
    cout << unten << "      das Fenster gross machen!       " << unten << endl;
    cout << unten << "                                      " << unten << endl;
    cout << unten << "                                      " << unten << endl;
    cout << unten << "                                      " << unten << endl;
    cout << unten << "                                      " << unten << endl;
    cout << unten << "                                      " << unten << endl;
    cout << unten << "                                      " << unten << endl;
    cout << unten << "   ________________________________   " << unten << endl;
    cout << unten << "                                      " << unten << endl;
    cout << unten << "          " << linieObenLinks << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieObenRechts << "           " << unten << endl;
    cout << unten << "          " << linieUnten << "     ENTER     " << linieUnten << "           " << unten << endl;
    cout << unten << "          " << linieUntenLinks << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieGerade << linieUntenRechts << "           " << unten << endl;
    cout << unten << "                                      " << unten << endl;

    cout << kuLinks;
    for (int i = 40 - 2; i > 0; i--) //breite
    {
        cout << gerade;
    }
    cout << kuRechts; cout << endl;

    string benutzername;
    cout << "Benutzernamen: ";
    cin >> benutzername;

    loginNutzer(benutzername);

    return 0;
}


// Beim Auskommentierten Code könnten paar Fehler vorlegen, einfach nicht beachten bitte, danke
// Ausserdem werde ich niewieder mit ascii code arbeiten, erstens ich versuche es immer zu gut zu machen und es geht mir auf den senkel
// zweitens es fucked tooooooodes ab (NIE WIEDER! BITTE!)
