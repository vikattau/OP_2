#ifndef STUD_H_INCLUDED
#define STUD_H_INCLUDED
#include "Mylib.h"
/**
* \class Zmogus
* \brief Bazine klase, skirta apibrezti zmogu.
*
* Si klase yra abstrakti bazine klase, kuri apraso zmogaus varda ir pavarde.
*/
class Zmogus {
protected:
    string vardas; /** Zmogaus vardas  */
    string pavarde; /** Zmogaus pavarde */
public:
    /**
    * \brief Konstruktorius su numatytomis reiksmemis.
    * \param vardas_ zmogaus vardas (numatyta reiksme: tuscia eilute).
    * \param pavarde_ zmogaus pavardė (numatyta reiksme: tuscia eilute).
    */
    Zmogus(const string vardas_ = "", const string pavarde_ = ""):
        vardas (vardas_), pavarde(pavarde_){}

    string getVardas() const { return vardas; }
    string getPavarde() const { return pavarde; }

    /**
    * \brief Spausdinimo funkcija.
    *
    * Virtuali funkcija, skirta spausdinti objekto informacija.
    * Si funkcija igyvendinta paveldinčioje klaseje.
    */
    virtual void spausdinti() const = 0;
    /**
    * \brief Virtualus destruktorius.
    *
    * Naudoja numatytaja realizacija.
    */
    virtual ~Zmogus() = default;

};
/**
* \class Studentas
* \brief Isvestine klase (is zmogaus klases), skirta apibrezti studenta.
*
* Si klase yra isvestine klase, kuri apraso studento varda, pavarde (paveldetus is Zmogaus klases), namu darbu ir egzamino pazymius, apskaiciuoja galutinius balus.
*/
class Studentas : public Zmogus {
private:
    vector<int> nd_; /** Studento namu darbu pazymiai */
    int egzaminas_; /** Studento egzamino pazymys*/
public:
    double galutinisBalasVidur; /** Apskaiciuojamas galutinis balas su namu darbu vidurkiu */
    double galutinisBalasMed; /** Apskaiciuojamas galutinis balas su namu darbu mediana */

    /**
    * \brief Konstruktorius su numatytomis reiksmemis.
    * \param vardas_ Studento vardas paveldetas is zmogaus klases(numatyta reiksme: tuscia eilute).
    * \param pavarde_ Studento pavardė pavaeldeta is zmogaus klases (numatyta reiksme: tuscia eilute).
    * \param nd Studento namu darbu pazymiu vektorius (numatyta reiksme: tuscias vektorius).
    * \param egzaminas Studento egzamino pazymys (numatyta reiksme: 0).
    * \param galutinisBalasVidur Studento galutinis balas su namu darbu vidurkiu (numatyta reiksme: 0.0).
    * \param galutinisBalasMed Studento galutinis balas su namu darbu mediana (numatyta reiksme: 0.0).
    */
    Studentas(const string& vardas_ = "", const string& pavarde_ = "",
            const vector<int>& nd = {}, int egzaminas = 0,
            double galutinisBalasVidur = 0.0, double galutinisBalasMed = 0.0)
        : Zmogus(vardas_, pavarde_), nd_(nd), egzaminas_(egzaminas),
        galutinisBalasVidur(galutinisBalasVidur), galutinisBalasMed(galutinisBalasMed) {}

    /**
    * \brief Kopijavimo konstruktorius.
    *
    * Sukuria nauja Studentas objekta, kurio reiksmes identiskos perduotam objektui.
    *
    * \param other Kitas Studentas objektas, kurio reiksmes bus nukopijuotos.
    */
    Studentas(const Studentas& other)
        : Zmogus(other), nd_(other.nd_),
          egzaminas_(other.egzaminas_), galutinisBalasVidur(other.galutinisBalasVidur),
          galutinisBalasMed(other.galutinisBalasMed) {}

    /**
    * \brief Kopijavimo priskyrimo operatorius.
    *
    * Leidzia priskirti vieno Studentas objekto reiksmes kitam.
    *
    * \param other Kitas Studentas objektas, kurio reiksmes bus priskirtos.
    * \return Nuoroda i dabartini objekta.
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
    * \brief Nuskaitymo operatorius.
    * Leidzia nuskaityti studento duomenis, kurie buvo ivesti ranka.
    * \param in Ivedimo srautas.
    * \param s Studentas objektas, kuriame bus saugomi nuskaityti duomenys.
    */
    friend istream& operator>>(istream& in, Studentas& s);
    /**
    * \brief Nuskaitymo operatorius duomenims is failo.
    * Leidzia nuskaityti duomenis is failu.
    * \param in Ivesties failo srautas, is kurio bus nuskaitomi duomenis.
    * \param studentas Studentas objektas, kuriame bus saugomi nuskaityti duomenys.
    */
    friend ifstream& operator>>(ifstream& in, Studentas& studentas);
    /**
    * \brief Isvedimo operatorius
    * Leidžia isvesti Studento objekto duomenis i ekrana arba faila.
    * \param out Isvesties srautas, i kuri bus isvedami duomenys.
    * \param studentas Studento objektas, kurio duomenys isvedami.
    */
    friend std::ostream& operator<<(std::ostream& out, const Studentas& studentas);

    /**
    * \brief Funkcija, spausdinanti studento duomenis.
    *
    * Si funkcija realizuoja virtualia funkcija is bazines klases Zmogus.
    */
    void spausdinti() const override {
        cout << "Vardas: " << vardas << ", Pavarde: " << pavarde << endl;
    }
    void atsitiktiniuBaluGeneravimas();
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
double skaicGalutiniBalaVidur(const Studentas &studentas);
double skaicGalutiniBalaMed(const Studentas &studentas);
void generuotiStudentus (int studentuSkaicius, const string &failoPav);
bool rusiavimasPavarde(const Studentas &Lok, const Studentas &stud);
void VectorstudentuSkaidymas(vector<Studentas>& studentai, vector<Studentas>& vargsiukai);
void ListStudentuSkaidymas(list<Studentas> & studentai, list<Studentas>& vargsiukai);
void pademonstruotiTrysMetodus();
#endif // STUD_H_INCLUDED
