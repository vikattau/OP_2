#ifndef STUD_H_INCLUDED
#define STUD_H_INCLUDED
#include "Mylib.h"
/**
* \class Žmogus
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
    /**
    * \brief Generuoja atsitiktinius pazymius
    *
    * Si funkcija Studentas objektui generuoja atsitiktinius 5 namu darbu ir egzamino pazymius.
    */
    void atsitiktiniuBaluGeneravimas();
    /**
    * \brief Istrina duomenis
    *
    * Istrina (isvalo) Studentas objekto duomeis.
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
* \brief Apskaiciuoja galutini bala su namu darbu vidurkiu
*
* Si funkcija apskaiciuoja galutini bala studentui.
* Pirma apskaiciuojamas namu darbu pazymiu vidurkis, tada pagal formule ndVidurkis * 0.4 + egzaminoPazymys * 0.6 apskaiciuojamas galutinis balas.
* \param studentas Studentas objektas, kurio galutinis balas bus skaiciuojamas.
* \return Galutinis balas pagal namu darbu vidurki.
*/
double skaicGalutiniBalaVidur(const Studentas &studentas);
/**
* \brief Apskaiciuoja galutini bala su namu darbu mediana.
*
* Si funkcija apskaiciuoja galutini bala studentui.
* Pirma apskaiciuojama namu darbu pazymiu mediana, tada pagal formule ndMediana * 0.4 + egzaminoPazymys * 0.6 apskaiciuojamas galutinis balas.
* \param studentas Studentas objektas, kurio galutinis balas bus skaiciuojamas.
* \return Galutinis balas pagal namu darbu mediana.
*/
double skaicGalutiniBalaMed(const Studentas &studentas);
/**
* \brief Generuojami studentu failai
* Sia funkcija generuojami failai su pasirinktu studentu skaiciumi (1tukst., 10tukst., 100tukst., 1mln., 10mln.).
* Sukuriamas atitinkamas skaicius atsitiktinai generuotu studentu su vardas ir pavardemis bei atsitiktiniais namu darbu ir egzamino pazymiais.
* Studenta irasomi i faila lenteles forma.
*
* \param studentuSkaicius Skaicius, kiek studentu bus generuojama.
* \param failoPav Sukurto failo su studentais pavadinimas
*/
void generuotiStudentus (int studentuSkaicius, const string &failoPav);
/**
* \brief Studentai isrusiuojami pagal pavardes
*Si funkcija isrusiuoja studentus pagal pavardes abeceles tvarka.
*
* \param Lok Studento objektas, kuris bus lyginamas su kitu.
* \param stud Kitas Studnento objektas, kuris bus lyginamas su pirmu.
*/
bool rusiavimasPavarde(const Studentas &Lok, const Studentas &stud);
/**
* \brief Studentu grupavimas skaidymo budu (vector)
* Si funkcija pereina per visus vektoriuje esancius studentus ir skirsto juos pagal galutini pazymi.
* Jei galutinis balas mazesnis uz 5, studentai pridedami prie vargsiuku vektoriaus ir istrinami is studentu vektoriaus.
*
* \param studentai Vektorius, kuriame saugomi visi studentai
* \param vargsiukai Vektorius, kuriame bus visi vargsiukai studentai.
*/
void VectorstudentuSkaidymas(vector<Studentas>& studentai, vector<Studentas>& vargsiukai);
/**
* \brief Studentu grupavimas skaidymo budu (list)
* Si funkcija pereina per visus liste esancius studentus ir skirsto juos pagal galutini pazymi.
* Jei galutinis balas mazesnis uz 5, studentai pridedami prie vargsiuku listo ir istrinami is studentu listo.
*
* \param studentai Listas, kuriame saugomi visi studentai
* \param vargsiukai Listas, kuriame bus visi vargsiukai studentai.
*/
void ListStudentuSkaidymas(list<Studentas> & studentai, list<Studentas>& vargsiukai);
/**
* \brief Triju metodu taisykles demonstravimas
* Funkcija, demonstruoja klases triju metodu taisykles veikima.
*/
void pademonstruotiTrysMetodus();
#endif // STUD_H_INCLUDED
