#ifndef STUD_H_INCLUDED
#define STUD_H_INCLUDED
#include "Mylib.h"

class Studentas {
private:
    string vardas_;
    string pavarde_;
    vector<int> nd_;
    int egzaminas_;
public:
    double galutinisBalasVidur;
    double galutinisBalasMed;

    Studentas(const string& vardas = "", const string& pavarde = "",
            const vector<int>& nd = {}, int egzaminas = 0,
            double galutinisBalasVidur = 0.0, double galutinisBalasMed = 0.0)
        : vardas_(vardas), pavarde_(pavarde), nd_(nd), egzaminas_(egzaminas),
        galutinisBalasVidur(galutinisBalasVidur), galutinisBalasMed(galutinisBalasMed) {}

    // Copy Constructor
    Studentas(const Studentas& other)
        : vardas_(other.vardas_), pavarde_(other.pavarde_), nd_(other.nd_),
          egzaminas_(other.egzaminas_), galutinisBalasVidur(other.galutinisBalasVidur),
          galutinisBalasMed(other.galutinisBalasMed) {}

    // Copy Assignment Operator
    Studentas& operator=(const Studentas& other) {
        if (this == &other) return *this;
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        nd_ = other.nd_;
        egzaminas_ = other.egzaminas_;
        galutinisBalasVidur = other.galutinisBalasVidur;
        galutinisBalasMed = other.galutinisBalasMed;
        return *this;
    }

    string getVardas() const { return vardas_; }
    string getPavarde() const { return pavarde_; }
    vector<int> getNd() const { return nd_; }
    int getEgz() const { return egzaminas_; }

    void setVardas(const string& v) { vardas_ = v; }
    void setPavarde(const string& p) { pavarde_ = p; }
    void setPazymiai(const vector<int>& pazymiai) { nd_ = pazymiai; }
    void setEgzaminas(int egz) { egzaminas_ = egz; }

    friend istream& operator>>(istream& in, Studentas& s);
    friend ifstream& operator>>(ifstream& in, Studentas& studentas);
    friend std::ostream& operator<<(std::ostream& out, const Studentas& studentas);

    void atsitiktiniuBaluGeneravimas();
    void valymas();

    ~Studentas() {
        vardas_.clear();
        pavarde_.clear();
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
