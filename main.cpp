#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;

struct Studentas{
    string vardas, pavarde;
    vector<int> NamuDarbai;
    int egz, rez;
};
void atsitiktiniuBaluGeneravimas(Studentas &Lok){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);

    int NDskaicius = 5;
    for (int i=0; i < NDskaicius; i++){
        Lok.NamuDarbai.push_back(dist(mt));
    }
    Lok.egz = dist(mt);
}
void duomenuived(Studentas &Lok){
    cout<<"Iveskite Varda, Pavarde: ";
    cin>>Lok.vardas>>Lok.pavarde;
    cout<<"Ar norite, kad pazymiai butu generuojami automatiskai? Jeigu Taip iveskite T, jeigu Ne - N: ";
    string ats;
    cin>> ats;
    if (ats == "T" || ats == "t"){
        atsitiktiniuBaluGeneravimas(Lok);
    } else if (ats == "N" || ats == "n"){
        cout<<"Iveskite egzamino rezultata: ";
        cin>> Lok.egz;
        cout<<"Iveskite Namu Darbu pazymius (noredami uzbaigti ivedima iveskite 0): \n";
        int x;
        while(true){
            cout<<"Pazymys: ";
            cin>> x;
            if (x == 0) break;
            Lok.NamuDarbai.push_back(x);
        }
    }
};
void valymas(Studentas &Lok){
    Lok.vardas.clear();
    Lok.pavarde.clear();
    Lok.NamuDarbai.clear();
}
double vidurkioSkaic(const vector<int> &pazymiai){
    int suma = 0;
    for(int pazymys : pazymiai){
        suma += pazymys;
    };
    return suma/static_cast<double>(pazymiai.size());
};
double medianosSkaic(vector<int> pazymiai){
    std::sort(pazymiai.begin(), pazymiai.end());
    int kiekis = pazymiai.size();
    if (kiekis % 2 == 0){
        return (pazymiai[kiekis / 2 - 1] + pazymiai[kiekis / 2]) / 2.0;
    } else {
        return pazymiai[kiekis /2];
    }
}
double skaicGalutiniBalaVidur(const Studentas &studentas){
    double vidutinisND = vidurkioSkaic(studentas.NamuDarbai);
    return (vidutinisND * 0.4) + (studentas.egz * 0.6);
};
double skaicGalutiniBalaMed(const Studentas &studentas){
    double medianaND = medianosSkaic(studentas.NamuDarbai);
    return (medianaND * 0.4) + (studentas.egz * 0.6);
}
void spausdinimas(Studentas Lok){
    cout<< std::setw(15) << std::left << Lok.pavarde
        << std::setw(15) << std::left << Lok.vardas
        << std::setw(20) << std::left << std::fixed << std::setprecision(2) << skaicGalutiniBalaVidur(Lok)
        << std::setw(20) << std::left << std::fixed << std::setprecision(2) << skaicGalutiniBalaMed(Lok) << endl;
};
int main()
{
    vector<Studentas> Vec1;
    Studentas A;
    cout<<"Kiek studentu ivesite?: ";
    int skaicius;
    cin>>skaicius;
    for(int i=0; i<skaicius; i++){
        cout<<"Iveskite informacija: "<<endl;
        duomenuived(A);
        Vec1.push_back(A);
        valymas(A);
    }
    cout << std::setw(15) << std::left << "Pavarde"
         << std::setw(15) << std::left << "Vardas"
         << std::setw(20) << std::left << "Galutinis (Vid.)"
         << std::setw(20) << std::left << "Galutinis (Med.)" << endl;

    cout << string(70, '-') << endl;

    for(int i=0; i<skaicius; i++){
        spausdinimas(Vec1.at(i));
        cout<<endl;
    }
    return 0;
};

