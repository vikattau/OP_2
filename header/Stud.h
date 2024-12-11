#ifndef STUD_H_INCLUDED
#define STUD_H_INCLUDED
#include "Mylib.h"
/**
* \class Zmogus
* \brief Bazinė klasė, skirta apibrėžti žmogų.
*
* Ši klasė yra abstrakti bazinė klasė, kuri aprašo žmogaus vardą ir pavardę.
* 
*/
class Zmogus {
protected:
    string vardas; /** Žmogaus vardas  */
    string pavarde; /** Žmogaus pavardė */
public:
    /**
    * \brief Konstruktorius su numatytomis reikšmėmis.
    * \param vardas_ žmogaus vardas (numatyta reikšmė: tuščia eilutė).
    * \param pavarde_ žmogaus pavardė (numatyta reikšmė: tuščia eilutė).
    */
    Zmogus(const string vardas_ = "", const string pavarde_ = ""):
        vardas (vardas_), pavarde(pavarde_){}

    string getVardas() const { return vardas; }
    string getPavarde() const { return pavarde; }

    /**
    * \brief Spausdinimo funkcija.
    *
    * Virtuali funkcija, skirta spausdinti objekto informacija.
    * Ši funkcija įgyvendinta paveldinčioje klasėje.
    */
    virtual void spausdinti() const = 0;
    /**
    * \brief Virtualus destruktorius.
    *
    * Naudoja numatytąją realizaciją.
    */
    virtual ~Zmogus() = default;

};
/**
* \class Studentas
* \brief Išvestinė klasė (is Žmogaus klasės), skirta apibrėžti studentą.
*
* Ši klasė yra išvestinė klasė, kuri aprašo studento vardą, pavardę (paveldėtus iš Žmogaus klasės), namų darbų ir egzamino pažymius, apskaičiuoja galutinius balus.
*/
class Studentas : public Zmogus {
private:
    vector<int> nd_; /**< Studento namų darbų pažymiai */
    int egzaminas_; /**< Studento egzamino pažymys*/
public:
    double galutinisBalasVidur; /** Apskaičiuojamas galutinis balas su namų darbų vidurkiu */
    double galutinisBalasMed; /** Apskaičiuojamas galutinis balas su namų darbų mediana */

    /**
    * \brief Konstruktorius su numatytomis reikšmėmis.
    * \param vardas_ Studento vardas, paveldėtas iš žmogaus klasės (numatytoji reikšmė: tuščia eilutė).
    * \param pavarde_ Studento pavardė, paveldėta iš žmogaus klasės (numatytoji reikšmė: tuščia eilutė).
    * \param nd Studento namų darbų pažymių vektorius (numatytoji reikšmė: tuščias vektorius).
    * \param egzaminas Studento egzamino pažymys (numatytoji reikšmė: 0).
    * \param galutinisBalasVidur Studento galutinis balas su namų darbų vidurkiu (numatytoji reikšmė: 0.0).
    * \param galutinisBalasMed Studento galutinis balas su namų darbų mediana (numatytoji reikšmė: 0.0).
    */
    Studentas(const string& vardas_ = "", const string& pavarde_ = "",
            const vector<int>& nd = {}, int egzaminas = 0,
            double galutinisBalasVidur = 0.0, double galutinisBalasMed = 0.0)
        : Zmogus(vardas_, pavarde_), nd_(nd), egzaminas_(egzaminas),
        galutinisBalasVidur(galutinisBalasVidur), galutinisBalasMed(galutinisBalasMed) {}

    /**
    * \brief Kopijavimo konstruktorius.
    *
    * Sukuria naują Studentas objektą, kurio reikšmės identiškos perduotam objektui.
    *
    * \param other Kitas Studentas objektas, kurio reikšmės bus nukopijuotos.
    */
    Studentas(const Studentas& other)
        : Zmogus(other), nd_(other.nd_),
          egzaminas_(other.egzaminas_), galutinisBalasVidur(other.galutinisBalasVidur),
          galutinisBalasMed(other.galutinisBalasMed) {}

    /**
    * \brief Kopijavimo priskyrimo operatorius.
    *
    * Leidžia priskirti vieno Studentas objekto reikšmes kitam.
    *
    * \param other Kitas Studentas objektas, kurio reikšmės bus priskirtos.
    * \return Nuoroda į dabartinį objektą.
    */

    Studentas& operator=(const Studentas& other) {
        if (this == &other) return *this;
        Zmogus::operator = (other);
        nd_ = other.nd_;
        egzaminas_ = other.egzaminas_;
        galutinisBalasVidur = other.galutinisBalasVidur;
        galutinisBalasMed = other.galutinisBalasMed;
        return *this;
    }

    string getVardas() const { return vardas; }
    string getPavarde() const { return pavarde; }
    vector<int> getNd() const { return nd_; }
    int getEgz() const { return egzaminas_; }

    void setVardas(const string& v) { vardas = v; }
    void setPavarde(const string& p) { pavarde = p; }
    void setPazymiai(const vector<int>& pazymiai) { nd_ = pazymiai; }
    void setEgzaminas(int egz) { egzaminas_ = egz; }

    /**
    * \brief Apskaičiuoja galutinį balą su namų darbų vidurkiu.
    *
    * Ši funkcija apskaičiuoja galutinį balą studentui.
    * Pirmiausia apskaičiuojamas namų darbų pažymių vidurkis, tada pagal formulę ndVidurkis * 0.4 + egzaminoPazymys * 0.6 apskaičiuojamas galutinis balas.
    * \param studentas Studentas objektas, kurio galutinis balas bus skaičiuojamas.
    * \return Galutinis balas pagal namų darbų vidurkį.
    */
    friend double skaicGalutiniBalaVidur(const Studentas& student);

    /**
    * \brief Apskaičiuoja galutinį balą su namų darbų mediana.
    *
    * Ši funkcija apskaičiuoja galutinį balą studentui.
    * Pirmiausia apskaičiuojama namų darbų pažymių mediana, tada pagal formulę ndMediana * 0.4 + egzaminoPazymys * 0.6 apskaičiuojamas galutinis balas.
    * \param studentas Studentas objektas, kurio galutinis balas bus skaičiuojamas.
    * \return Galutinis balas pagal namų darbų medianą.
    */
    friend double skaicGalutiniBalaMed(const Studentas& student);

    /**
    * \brief Nuskaitymo operatorius.
    * Leidžia nuskaityti studento duomenis, kurie buvo įvesti ranka.
    * \param in Įvedimo srautas.
    * \param s Studentas objektas, kuriame bus saugomi nuskaityti duomenys.
    */
    friend istream& operator>>(istream& in, Studentas& studentas) {
        cout << "Iveskite Varda: ";
        in >> studentas.vardas;
        cout << "Iveskite Pavarde: ";
        in >> studentas.pavarde;

        while (true) {
            cout << "Ar norite, kad pazymiai butu generuojami automatiskai? Jeigu Taip iveskite T, jeigu Ne - N: ";
            string ats;
            in >> ats;
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            if (ats == "T" || ats == "t") {
                studentas.atsitiktiniuBaluGeneravimas();
                break;
            }
            else if (ats == "N" || ats == "n") {
                cout << "Iveskite egzamino rezultata (0 - 10): ";
                while (!(in >> studentas.egzaminas_) || studentas.egzaminas_ < 0 || studentas.egzaminas_ > 10) {
                    in.clear();
                    in.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Neteisingai ivedete, bandykite dar karta: ";
                }
                cout << "Iveskite Namu Darbu pazymius 1 - 10 (noredami uzbaigti ivedima iveskite 0): \n";
                studentas.nd_.clear();
                int x;
                bool ivestasPazymys = false;
                while (true) {
                    cout << "Pazymys: ";
                    while (!(in >> x) || x < 0 || x > 10) {
                        in.clear();
                        in.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Neteisingai ivedete, bandykite dar karta: ";
                    }

                    if (x == 0) {
                        if (!ivestasPazymys) {
                            cout << "Turite ivesti bent viena pazymi. \n";
                            continue;
                        }
                        break;
                    }
                    studentas.nd_.push_back(x);
                    ivestasPazymys = true;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            else {
                cout << "Neteisingai ivedete. Prasome iveskite T arba N." << endl;
            }
        }
        studentas.galutinisBalasVidur = skaicGalutiniBalaVidur(studentas);
        studentas.galutinisBalasMed = skaicGalutiniBalaMed(studentas);

        return in;
    }

    /**
    * \brief Nuskaitymo operatorius duomenims iš failo.
    * Leidžia nuskaityti duomenis iš failo.
    * \param in Įvesties failo srautas, iš kurio bus nuskaitomi duomenys.
    * \param studentas Studentas objektas, kuriame bus saugomi nuskaityti duomenys.
    */
    friend ifstream& operator>>(ifstream& in, Studentas& studentas) {
        std::string line;
        std::getline(in, line);
        if (line.empty()) return in;

        std::stringstream ss(line);
        ss >> studentas.vardas >> studentas.pavarde;

        studentas.nd_.resize(5);
        for (int& grade : studentas.nd_) {
            ss >> grade;
        }

        ss >> studentas.egzaminas_;
        studentas.galutinisBalasVidur = skaicGalutiniBalaVidur(studentas);
        studentas.galutinisBalasMed = skaicGalutiniBalaMed(studentas);

        return in;
    }

    /**
    * \brief Išvedimo operatorius.
    * Leidžia išvesti Studento objekto duomenis į ekraną arba failą.
    * \param out Išvesties srautas, į kurį bus išvedami duomenys.
    * \param studentas Studento objektas, kurio duomenys išvedami.
    */
    friend std::ostream& operator<<(std::ostream& out, const Studentas& studentas) {
        out << setw(15) << left << studentas.pavarde
            << setw(15) << left << studentas.vardas
            << setw(20) << left << fixed << setprecision(2)
            << studentas.galutinisBalasVidur
            << setw(20) << left << fixed << setprecision(2)
            << studentas.galutinisBalasMed;

        return out;
    }

    /**
    * \brief Funkcija, spausdinanti studento duomenis.
    *
    * Ši funkcija realizuoja virtualią funkciją iš bazinės klasės Zmogus.
    */
    void spausdinti() const override {
        cout << "Vardas: " << vardas << ", Pavarde: " << pavarde << endl;
    }

    /**
    * \brief Generuoja atsitiktinius pažymius.
    *
    * Ši funkcija Studentas objektui generuoja atsitiktinius 5 namų darbų ir egzamino pažymius.
    */
    void atsitiktiniuBaluGeneravimas();

    /**
    * \brief Ištrina duomenis.
    *
    * Ištrina (išvalo) Studentas objekto duomenis.
    */
    void valymas();

    /**
    * \brief Destruktorius.
    *
    * Atlaisvina atminties resursus.
    */
    ~Studentas() {
        vardas.clear();
        pavarde.clear();
        nd_.clear();
    }
};

/**
* \brief Generuojami studentų failai.
* Šia funkcija generuojami failai su pasirinktu studentų skaičiumi (1 tūkst., 10 tūkst., 100 tūkst., 1 mln., 10 mln.).
* Sukuriamas atitinkamas skaičius atsitiktinai generuotų studentų su vardais ir pavardėmis bei atsitiktiniais namų darbų ir egzamino pažymiais.
* Studentai įrašomi į failą lentelės forma.
*
* \param studentuSkaicius Skaičius, kiek studentų bus generuojama.
* \param failoPav Sukurto failo su studentais pavadinimas.
*/
void generuotiStudentus (int studentuSkaicius, const string &failoPav);

/**
* \brief Studentai išrūšiuojami pagal pavardes.
* Ši funkcija išrūšiuoja studentus pagal pavardes abėcėlės tvarka.
*
* \param Lok Studento objektas, kuris bus lyginamas su kitu.
* \param stud Kitas Studento objektas, kuris bus lyginamas su pirmu.
*/
bool rusiavimasPavarde(const Studentas &Lok, const Studentas &stud);

/**
* \brief Studentų grupavimas skaidymo būdu (vector).
* Ši funkcija pereina per visus vektoriuje esančius studentus ir skirsto juos pagal galutinį pažymį.
* Jei galutinis balas mažesnis už 5, studentai pridedami prie vargšiukų vektoriaus ir ištrinami iš studentų vektoriaus.
*
* \param studentai Vektorius, kuriame saugomi visi studentai
* \param vargsiukai Vektorius, kuriame bus visi vargšiukai studentai.
*/
void VectorstudentuSkaidymas(vector<Studentas>& studentai, vector<Studentas>& vargsiukai);

/**
* \brief Studentų grupavimas skaidymo būdu (list).
* Ši funkcija pereina per visus liste esančius studentus ir skirsto juos pagal galutinį pažymį.
* Jei galutinis balas mažesnis už 5, studentai pridedami prie vargšiukų listo ir ištrinami iš studentų listo.
*
* \param studentai Listas, kuriame saugomi visi studentai
* \param vargsiukai Listas, kuriame bus visi vargšiukai studentai.
*/
void ListStudentuSkaidymas(list<Studentas> & studentai, list<Studentas>& vargsiukai);

/**
* \brief Trijų metodų taisyklių demonstravimas.
* Ši funkcija demonstruoja, kaip veikia klasės trijų metodų taisyklės (konstruktorius, kopijavimo konstruktorius, kopijavimo priskyrimo operatorius).
*/
void pademonstruotiTrysMetodus();
#endif // STUD_H_INCLUDED
