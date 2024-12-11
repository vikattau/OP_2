#include "Stud.h"

void Studentas::valymas(){
    vardas.clear();
    pavarde.clear();
    nd_.clear();
    egzaminas_ = 0;
};

double skaicGalutiniBalaVidur(const Studentas &studentas){
    double vidutinisND = 0.0;
    for (int grade : studentas.getNd()) {
        vidutinisND += grade;
    }
    vidutinisND /= studentas.getNd().size();
    return (vidutinisND * 0.4) + (studentas.getEgz() * 0.6);
}
double skaicGalutiniBalaMed(const Studentas &studentas){
    if (studentas.getNd().empty()) return 0.0;

    vector<int> sortedNd = studentas.getNd();
    sort(sortedNd.begin(), sortedNd.end());

    size_t size = sortedNd.size();
    double medianaNd;
    if (size % 2 == 0) {
        medianaNd = (sortedNd[size / 2 - 1] + sortedNd[size / 2]) / 2.0;
    } else {
        medianaNd = sortedNd[size / 2];
    }

    return (medianaNd * 0.4) + (studentas.getEgz() * 0.6);
}
void Studentas::atsitiktiniuBaluGeneravimas() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);

    int NDskaicius = 5;
    for (int i=0; i < NDskaicius; i++){
        nd_.push_back(dist(mt));
    }
    egzaminas_ = dist(mt);
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
    return Lok.getPavarde() < stud.getPavarde();
};

void VectorstudentuSkaidymas(vector<Studentas>& studentai, vector<Studentas>& vargsiukai){
    auto it = std::remove_if(studentai.begin(), studentai.end(), [&](const Studentas& s) {
        if (skaicGalutiniBalaVidur(s) < 5.0) {
            vargsiukai.push_back(s);
            return true;
        }
            return false;
        });
    studentai.erase(it, studentai.end());
}
void ListStudentuSkaidymas(list<Studentas> & studentai, list<Studentas>& vargsiukai){
    auto it = std::remove_if(studentai.begin(), studentai.end(), [&](const Studentas& s) {
        if (skaicGalutiniBalaVidur(s) < 5.0) {
            vargsiukai.push_back(s);
            return true;
        }
            return false;
        });
    studentai.erase(it, studentai.end());
}
void pademonstruotiTrysMetodus() {
    Studentas a;
    cin >> a;
    Studentas b;
    b = a;
    Studentas c(b);
    cout << a << "\n" << b << "\n" << c << endl;

}
