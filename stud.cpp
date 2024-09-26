#include "Stud.h"

void duomenuived(Studentas &Lok){
    while (true) {
        cout << "Iveskite Varda: ";
        std::getline(cin, Lok.vardas);
        if (Lok.vardas.empty()) {
            cout << "Vardas negali buti tuscias. Bandykite dar karta." << endl;
        } else {
            break;
        }
    }
    while (true) {
        cout << "Iveskite Pavarde: ";
        std::getline(cin, Lok.pavarde);
        if (Lok.pavarde.empty()) {
            cout << "Pavarde negali buti tuscia. Bandykite dar karta." << endl;
        } else {
            break;
        }
    }
    while (true) {
        cout << "Ar norite, kad pazymiai butu generuojami automatiskai? Jeigu Taip iveskite T, jeigu Ne - N: ";
        string ats;
        cin >> ats;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (ats == "T" || ats == "t") {
            atsitiktiniuBaluGeneravimas(Lok);
            break;
        } else if (ats == "N" || ats == "n") {
            int Egz;
            cout << "Iveskite egzamino rezultata (0 - 10): ";
            while (!(cin >> Egz) || Egz < 0 || Egz > 10) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Neteisingai ivedete, bandykite dar karta: ";
            }
            Lok.egz = Egz;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Iveskite Namu Darbu pazymius 1 - 10 (noredami uzbaigti ivedima iveskite 0): \n";
            int x;
            bool ivestasPazymys = false;
            while (true) {
                cout << "Pazymys: ";
                while (!(cin >> x)) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Neteisingai ivedete, bandykite dar karta: ";
                }
                if (x < 0 || x > 10) {
                    cout << "Neteisingai";
                    continue;
                }
                if (x == 0) {
                    if (!ivestasPazymys) {
                        cout << "Turite ivesti bent viena pazymi. \n";
                        continue;
                    }
                    break;
                }
                Lok.NamuDarbai.push_back(x);
                ivestasPazymys = true;
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        } else {
            cout << "Neteisingai ivedete. Prasome iveskite T arba N." << endl;
        }
    }
};

void spausdinimas(const Studentas &Lok){
    cout<< std::setw(15) << std::left << Lok.pavarde
        << std::setw(15) << std::left << Lok.vardas
        << std::setw(20) << std::left << std::fixed << std::setprecision(2) << skaicGalutiniBalaVidur(Lok)
        << std::setw(20) << std::left << std::fixed << std::setprecision(2) << skaicGalutiniBalaMed(Lok) << endl;
};

void valymas(Studentas &Lok){
    Lok.vardas.clear();
    Lok.pavarde.clear();
    Lok.NamuDarbai.clear();
};
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
};
double skaicGalutiniBalaVidur(const Studentas &studentas){
    double vidutinisND = vidurkioSkaic(studentas.NamuDarbai);
    return (vidutinisND * 0.4) + (studentas.egz * 0.6);
};
double skaicGalutiniBalaMed(const Studentas &studentas){
    double medianaND = medianosSkaic(studentas.NamuDarbai);
    return (medianaND * 0.4) + (studentas.egz * 0.6);
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
};
void skaitytiFaila(vector<Studentas> &studentai, const string & failoPavadinimas){
    std::ifstream failas(failoPavadinimas);
    if (!failas) {
        cout<< "Nepavyko nuskaityti failo"<<endl;
        return;
    }
    string failoEilute;
    std::getline(failas, failoEilute);
    while(std::getline(failas, failoEilute)){
        std::istringstream iss(failoEilute);
        Studentas stud;

        iss >> stud.vardas >>stud.pavarde;

        if (iss.fail()){
            cout << "Nepavyko teisingai nuskaityti studento vardo ir pavardes." << endl;
            continue;
        }

        int pazymys;
        while(iss >> pazymys){
            if (pazymys < 0 || pazymys > 10) {
                cout << "Faile neteisingas pazymys studentui: " << stud.vardas << " " << stud.pavarde <<endl;
                continue;
            }
            stud.NamuDarbai.push_back(pazymys);
        }
        if (!stud.NamuDarbai.empty()) {
            stud.egz = stud.NamuDarbai.back();
            stud.NamuDarbai.pop_back();
        } else {
            cout << "Nera pazymiu studentui: " << stud.vardas << " " << stud.pavarde << endl;
            continue;
        }
        studentai.push_back(stud);
    }
    if (studentai.empty()){
        cout << "Ivyko klaida: Nebuvo galima nuskaityti jokiu studentu is failo" << endl;
    }
};
bool rusiavimasPavarde(const Studentas &Lok, const Studentas &stud){
    return Lok.pavarde < stud.pavarde;
};

