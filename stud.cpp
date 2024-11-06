#include "Stud.h"

void duomenuived(Studentas &Lok){
    while (true) {
        cout << "Iveskite Varda: ";
        getline(cin, Lok.vardas);
        if (Lok.vardas.empty()) {
            cout << "Vardas negali buti tuscias. Bandykite dar karta." << endl;
        } else {
            break;
        }
    }
    while (true) {
        cout << "Iveskite Pavarde: ";
        getline(cin, Lok.pavarde);
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (ats == "T" || ats == "t") {
            atsitiktiniuBaluGeneravimas(Lok);
            break;
        } else if (ats == "N" || ats == "n") {
            int Egz;
            cout << "Iveskite egzamino rezultata (0 - 10): ";
            while (!(cin >> Egz) || Egz < 0 || Egz > 10) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Neteisingai ivedete, bandykite dar karta: ";
            }
            Lok.egz = Egz;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Iveskite Namu Darbu pazymius 1 - 10 (noredami uzbaigti ivedima iveskite 0): \n";
            int x;
            bool ivestasPazymys = false;
            while (true) {
                cout << "Pazymys: ";
                while (!(cin >> x)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Neteisingai ivedete, bandykite dar karta: ";
                }
                if (x < 0 || x > 10) {
                    cout << "Neteisingas pazymys";
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        } else {
            cout << "Neteisingai ivedete. Prasome iveskite T arba N." << endl;
        }
    }
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
    sort(pazymiai.begin(), pazymiai.end());
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
void generuotiStudentus (int studentuSkaicius, const string &failoPav){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);

    auto start = high_resolution_clock::now();

    ofstream failas(failoPav);
    if (!failas){
        cerr << "Nepavyko atidaryti failo " << failoPav << endl;
        return;
    }
    failas << setw(20) << left << "Vardas"
           << setw(20) << left << "Pavarde";
    for (int i = 1; i <= 5; ++i) {
        failas << setw(10) << left << "ND" + to_string(i);
    }
    failas << setw(10) << left << "Egz." << endl;

    for (int i = 0; i < studentuSkaicius; i++) {
        string pavarde = "Pavarde" + to_string(i);
        string vardas = "Vardas" + to_string(i);

        failas << setw(20) << left << vardas
               << setw(20) << left << pavarde;
        for (int j=0; j<5; j++){
            failas << setw(10) << left << dist(mt);
        }
        failas << setw(10) << left << dist(mt) << endl;
    }
    failas.close();
    auto end = high_resolution_clock::now();
    duration<double> laikas = end - start;
    cout << "Sukurtas failas: " << failoPav << " su " << studentuSkaicius << " studentais. "
        << "Uztruko: " << laikas.count() << " sekundes." << endl;
}
bool rusiavimasPavarde(const Studentas &Lok, const Studentas &stud){
    return Lok.pavarde < stud.pavarde;
};

void VectorstudentuSkaidymasIstrinant(vector<Studentas>& studentai, vector<Studentas>& vargsiukai){
    vargsiukai.reserve(studentai.size()); // Avoid reallocations

    auto it = std::remove_if(studentai.begin(), studentai.end(), [&](const Studentas& s) {
        if (skaicGalutiniBalaVidur(s) < 5.0) {
            vargsiukai.push_back(s);
            return true;
        }
            return false;
        });
    studentai.erase(it, studentai.end());
}

