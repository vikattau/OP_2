#ifndef TEMPLATES_H_INCLUDED
#define TEMPLATES_H_INCLUDED
#include "Mylib.h"
#include "Stud.h"

/**
* \brief Spausdina studentu lentele su ju galutiniais balais.
* Si funkcija naudojama spausdinti studentu informacija (t.y varda, pavarde, galutini bala pagal vidurki bei mediana).
* Sio programaoje naudojama vektoriams ir listam.
*
* \tparam Container Konteinerio tipas
* \param stud Konteineris, kuriame saugomi studentai.
*/
template <typename Container>
void spausdinimas(const Container &stud){
    cout << setw(15) << left << "Pavarde"
         << setw(15) << left << "Vardas"
         << setw(20) << left << "Galutinis (Vid.)"
         << setw(20) << left << "Galutinis (Med.)" << endl;

    cout << string(70, '-') << endl;

    for (const auto& Lok : stud){
        cout << Lok << endl;
    }

};
/**
* \brief Nuskaito duomenis is failo i konteineri
* Si funkcija nuskaito duomenis apie studentus is failo ir saugo konteineryje.
* Jei failas neatidaromas, bus isvedamas klaidos pranesimas.
*
* \tparam Container Konteinerio tipas
* \param studentai Konteineris, kuriame saugomi nuskaityti studentai.
* \param failoPavadinimas Tekstinio failo pavadinimas, is kurio bus nuskaitomi duomenis.
*/
template <typename Container>
void skaitytiFaila(Container &studentai, const string & failoPavadinimas){
    ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        cout<< "Nepavyko nuskaityti failo"<<endl;
        return;
    }
   string failoEilute;
    getline(failas, failoEilute);
    Studentas studentas;

    while (failas >> studentas) {
        studentai.push_back(studentas);
    }

    if (studentai.empty()) {
        cout << "Ivyko klaida: Nebuvo galima nuskaityti jokiu studentu is failo" << endl;
    }

   failas.close();
};
/**
* \brief Skisto studentus i vargsiukus ir galvocius
*
* Jei galutinis balas mazesnis uz 5 studentas yra pridedamas prie vargsiuku vektoriaus\listo.
* Kitu atveju pridedamas prie galvociu konteinerio.
* \tparam Container Konteinerio tipas.
* \param studentai Konteineris, kuriame saugomi studentai
* \param vargsiukai Konteineris, kuriame saugomi vargsiukai studentai
* \param galvociai Konteineris, kuriame saugomi galvociai studentai.
*/
template <typename Container>
void studentuSkirstymas(const Container &studentai, Container &vargsiukai, Container &galvociai) {
    for (const auto& stud : studentai) {
        if (skaicGalutiniBalaVidur(stud) < 5.0) {
            vargsiukai.push_back(stud);
        } else {
            galvociai.push_back(stud);
        }
    }
}
/**
* \brief Studentai irasomi i faila.

* Si funkcija konteineryje esanciu studentu duomenis iraso i faila lenteles forma.
*
* \tparam Container Konteinerio tipas
* \param failoPav Failo i kuri rasomi duomenis pavadinimas.
*/
template <typename Container>
void rasytiIFaila(const Container& stud, const string& failoPav) {
    ofstream failas(failoPav);
    if (!failas) {
        cerr << "Nepavyko atidaryti failo " << failoPav << endl;
        return;
    }

    failas << setw(17) << left << "Pavarde"
           << setw(15) << left << "Vardas"
           << setw(20) << left << "Galutinis (Vid.)"
           << setw(20) << left << "Galutinis (Med.)" << endl;

    failas << string(70, '-') << endl;

    for (const auto& s : stud) {
       failas << s << endl;
    }
    failas.close();
}

/**
* \brief Studentu skirstimas pagal pazymi 2 strategija
*
* Si funkcija pirma isrusiuoja studentus pagal galutini vidurki, tada studentus, kuriu galutinis balas mazesnis uz 5 prideda prie vargsiuku konteinerio.
* O studentus, kuriu galutinis balas aukstesnis, istrina is studentu konteinerio.
* \tparam Container Konteinerio tipas.
* \param studentai Konteineris, kuriame saugomi studentai
* \param vargsiukai Konteineris, kuriame bus saugomi vargsiukai studentai.
*/
template <typename Container>
void studentuSkaidymasIstrinant(Container& studentai, Container& vargsiukai){

    if constexpr (std::is_same_v<Container, std::list<typename Container::value_type>>) {
        studentai.sort([](const auto& a, const auto& b) {
            return a.galutinisBalasVidur < b.galutinisBalasVidur;
        });
    } else {
        std::sort(studentai.begin(), studentai.end(), [](const auto& a, const auto& b) {
            return a.galutinisBalasVidur < b.galutinisBalasVidur;
        });
    }

    auto boundary = studentai.begin();
    while (boundary != studentai.end() && boundary->galutinisBalasVidur < 5.0) {
        ++boundary;
    }

    vargsiukai.insert(vargsiukai.end(), studentai.begin(), boundary);

    studentai.erase(studentai.begin(), boundary);
}
/**
* \brief Skirtingi rusiavimo budai
* Priklausomai nuo naudotojo pasirinkimo vykdomas rusiavimas.
* 1 - rusiavimas pavarde.
* 2 - rusiavimas mazejancia tvarka pagal galutini bala.
* 3 - rusiavimas didejancia tvarka pagal galutini bala.
* \tparam Container Konteinerio tipas.
* \param stud Konteineris, kuriame esantys duomenys bus rusiuojami.
* \param rusiavimoPasirinkimas Naudotojo pasirinktas rusiavimo budas.
*/
template <typename Container>
void rusiavimoBudai(Container& stud, int rusiavimoPasirinkimas ){
    if (rusiavimoPasirinkimas == 1){
            if constexpr (is_same<Container, vector<Studentas>>::value) {
                sort(stud.begin(), stud.end(), rusiavimasPavarde);
            } else if constexpr (is_same<Container, list<Studentas>>::value) {
                stud.sort(rusiavimasPavarde);
            }
    } else if (rusiavimoPasirinkimas == 2) {
            if constexpr (is_same<Container, vector<Studentas>>::value) {
                sort(stud.begin(), stud.end(), [](const Studentas& a, const Studentas& b) {
                    return a.galutinisBalasVidur > b.galutinisBalasVidur;
            });
            } else if constexpr (is_same<Container, list<Studentas>>::value) {
            stud.sort([](const Studentas& a, const Studentas& b) {
                return a.galutinisBalasVidur > b.galutinisBalasVidur;
            });
            }
    } else {
            if constexpr (is_same<Container, vector<Studentas>>::value) {
                sort(stud.begin(), stud.end(), [](const Studentas& a, const Studentas& b) {
                    return a.galutinisBalasVidur < b.galutinisBalasVidur;
            });
            } else if constexpr (is_same<Container, list<Studentas>>::value) {
                stud.sort([](const Studentas& a, const Studentas& b) {
                    return a.galutinisBalasVidur < b.galutinisBalasVidur;
            });
            }
        }
}
/**
* \brief Patikrinama kiek vietos uzima konteineriai
*
* Si funkcija spausdina, kiek koks konteineris uzima vietos.
* \tparam Container Konteinerio tipas.
* \param studentai Konteineris, kurio uzimama vieta bus apskaiciuojama
* \param vargsiukai Konteineris, kurio uzimama vieta bus apskaiciuojama
* \param galvociai Konteineris, kurio uzimama vieta bus apskaiciuojama
*/
template <typename Container>
void patikrintiAtmintiesNaudojima(const Container& studentai, const Container& vargsiukai, const Container& galvociai) {
    size_t bendrasDydis = studentai.size() * sizeof(typename Container::value_type);
    size_t vargsiukaiDydis = vargsiukai.size() * sizeof(typename Container::value_type);
    size_t galvociaiDydis = galvociai.size() * sizeof(typename Container::value_type);

    std::cout << "Bendro studentu konteinerio dydis: " << bendrasDydis << " baitu\n";
    std::cout << "Vargsiuku konteinerio dydis: " << vargsiukaiDydis << " baitu\n";
    std::cout << "Kietiaku konteinerio dydis: " << galvociaiDydis << " baitu\n";
    std::cout << "Bendra uzimama atmintis po suskirstymo: "
              << (bendrasDydis + vargsiukaiDydis + galvociaiDydis) << " baitu\n" << endl;
}
/**
* \brief Patikrinama kiek vietos uzima konteineriai
*
* Si funkcija spausdina, kiek koks konteineris uzima vietos.
* \tparam Container Konteinerio tipas.
* \param studentai Konteineris, kurio uzimama vieta bus apskaiciuojama
* \param vargsiukai Konteineris, kurio uzimama vieta bus apskaiciuojama
*/
template <typename Container>
void patikrintiAtmintiesNaudojimaBeGalv(const Container& studentai, const Container& vargsiukai) {
    size_t bendrasDydis = studentai.size() * sizeof(typename Container::value_type);
    size_t vargsiukaiDydis = vargsiukai.size() * sizeof(typename Container::value_type);

    std::cout << "Bendro studentu konteinerio dydis: " << bendrasDydis << " baitu\n";
    std::cout << "Vargsiuku konteinerio dydis: " << vargsiukaiDydis << " baitu\n";
    std::cout << "Bendra uzimama atmintis po suskirstymo: "
              << (bendrasDydis + vargsiukaiDydis) << " baitu\n" << endl;
}
/**
* \brief Programos greicio analize
* Si funkcija matuoja kiek laiko uztrunka, kol failas yra nuskaitomas, isrusiuojami duomenis, isskirstomi studentai ir irasomi i vargsiuku ir galvociu failus.
*
* \tparam Container Konteinerio tipas.
* \param failoPav Failo, kuris bus testuojamas, pavadinimas.
* \param stud Konteineris, i kuri bus irasomi duomenys
* \param rusiavimoPasirinkimas Naudotojo pasirinkimas, kaip rusiuoti duomenis.
* \param strategijosPasirinkimas Naudotojo pasirinkimas, kokia strategija naudoti skistant studentus i vargsiukus ir galvocius.
*/
template <typename Container>
void failuTestavimas(string failoPav, Container& stud, int rusiavimoPasirinkimas, int strategijosPasirinkimas) {
    stud.clear();
    auto start = high_resolution_clock::now();
    skaitytiFaila(stud, failoPav);
    auto end = high_resolution_clock::now();
    auto failoSkaitymas = duration_cast<milliseconds>(end - start).count();
    cout << "Failo is " << stud.size() << " irasu nuskaitymo laikas: " << fixed << setprecision(6) << failoSkaitymas / 1000.0 << " s" << endl;

    if (strategijosPasirinkimas == 1){
        start = high_resolution_clock::now();
        rusiavimoBudai(stud, rusiavimoPasirinkimas);
        end = high_resolution_clock::now();
        auto rusiavimoLaikas = duration_cast<milliseconds>(end - start).count();
        cout << "Rusiavimo laikas: " << fixed << setprecision(6) << rusiavimoLaikas / 1000.0 << " s" << endl;

        Container vargsiukai, galvociai;
        start = high_resolution_clock::now();
        studentuSkirstymas(stud, vargsiukai, galvociai);
        end = high_resolution_clock::now();
        auto skirstymoLaikas = duration_cast<milliseconds>(end - start).count();
        cout << "Dalijimo i dvi grupes laikas: " << fixed << setprecision(6) << skirstymoLaikas / 1000.0 << " s" << endl;

        string vargsiukaiFailas = failoPav + "_vargsiukai.txt";
        string galvociaiFailas = failoPav + "_galvociai.txt";

        start = high_resolution_clock::now();
        rasytiIFaila(vargsiukai, vargsiukaiFailas);
        end = high_resolution_clock::now();
        auto vfailoIsvedimoLaikas = duration_cast<milliseconds>(end - start).count();
        cout << "Irasymo i " << vargsiukaiFailas << " faila laikas: " << fixed << setprecision(6) << vfailoIsvedimoLaikas / 1000.0 << " s" << endl;

        start = high_resolution_clock::now();
        rasytiIFaila(galvociai, galvociaiFailas);
        end = high_resolution_clock::now();
        auto gfailoIsvedimoLaikas = duration_cast<milliseconds>(end - start).count();
        cout << "Irasymo i " << galvociaiFailas << " faila laikas: " << fixed << setprecision(6) << gfailoIsvedimoLaikas / 1000.0 << " s" << endl;

        auto visasLaikas = failoSkaitymas + rusiavimoLaikas + skirstymoLaikas + vfailoIsvedimoLaikas + gfailoIsvedimoLaikas;
        cout << stud.size() << " irasu testo laikas: " << fixed << setprecision(6) << visasLaikas / 1000.0 << " s" << endl << endl;

        //patikrintiAtmintiesNaudojima(stud, vargsiukai, galvociai);

    } else if (strategijosPasirinkimas == 2){
        Container vargsiukai;
        start = high_resolution_clock::now();
        studentuSkaidymasIstrinant(stud, vargsiukai);
        end = high_resolution_clock::now();
        auto skirstymoLaikas = duration_cast<milliseconds>(end - start).count();
        cout << "Dalijimo i dvi grupes laikas: " << fixed << setprecision(6) << skirstymoLaikas / 1000.0 << " s" << endl;

        start = high_resolution_clock::now();
        rusiavimoBudai(stud, rusiavimoPasirinkimas);
        rusiavimoBudai(vargsiukai, rusiavimoPasirinkimas);
        end = high_resolution_clock::now();
        auto rusiavimoLaikas = duration_cast<milliseconds>(end - start).count();
        cout << "Rusiavimo laikas: " << fixed << setprecision(6) << rusiavimoLaikas / 1000.0 << " s" << endl;

        string vargsiukaiFailas = failoPav + "_v.txt";
        string galvociukaiFailas = failoPav + "_g.txt";

        start = high_resolution_clock::now();
        rasytiIFaila(vargsiukai, vargsiukaiFailas);
        end = high_resolution_clock::now();
        auto vfailoIsvedimoLaikas = duration_cast<milliseconds>(end - start).count();
        cout << "Irasymo i " << vargsiukaiFailas << " faila laikas: " << fixed << setprecision(6) << vfailoIsvedimoLaikas / 1000.0 << " s" << endl;

        start = high_resolution_clock::now();
        rasytiIFaila(stud, galvociukaiFailas);
        end = high_resolution_clock::now();
        auto originalFailoIsvedimoLaikas = duration_cast<milliseconds>(end - start).count();
        cout << "Irasymo i " << galvociukaiFailas << " faila laikas: " << fixed << setprecision(6) << originalFailoIsvedimoLaikas / 1000.0 << " s" << endl;

        auto visasLaikas = failoSkaitymas  + skirstymoLaikas + rusiavimoLaikas + vfailoIsvedimoLaikas + originalFailoIsvedimoLaikas;
        cout << stud.size() + vargsiukai.size() << " irasu testo laikas: " << fixed << setprecision(6) << visasLaikas / 1000.0 << " s" << endl << endl;

        //patikrintiAtmintiesNaudojimaBeGalv(stud, vargsiukai);

    } else if (strategijosPasirinkimas == 3){
        start = high_resolution_clock::now();
        rusiavimoBudai(stud, rusiavimoPasirinkimas);
        end = high_resolution_clock::now();
        auto rusiavimoLaikas = duration_cast<milliseconds>(end - start).count();
        cout << "Rusiavimo laikas: " << fixed << setprecision(6) << rusiavimoLaikas / 1000.0 << " s" << endl;

        if constexpr (is_same<Container, vector<Studentas>>::value) {
            vector<Studentas> vargsiukai;
            start = high_resolution_clock::now();
            VectorstudentuSkaidymas(stud, vargsiukai);
            end = high_resolution_clock::now();
            auto skirstymoLaikas = duration_cast<milliseconds>(end - start).count();
            cout << "Dalijimo i dvi grupes laikas: " << fixed << setprecision(6) << skirstymoLaikas / 1000.0 << " s" << endl;

            string vargsiukaiFailas = failoPav + "_v.txt";
            string galvociukaiFailas = failoPav + "_g.txt";

            start = high_resolution_clock::now();
            rasytiIFaila(vargsiukai, vargsiukaiFailas);
            end = high_resolution_clock::now();
            auto vfailoIsvedimoLaikas = duration_cast<milliseconds>(end - start).count();
            cout << "Irasymo i " << vargsiukaiFailas << " faila laikas: " << fixed << setprecision(6) << vfailoIsvedimoLaikas / 1000.0 << " s" << endl;

            start = high_resolution_clock::now();
            rasytiIFaila(stud, galvociukaiFailas);
            end = high_resolution_clock::now();
            auto originalFailoIsvedimoLaikas = duration_cast<milliseconds>(end - start).count();
            cout << "Irasymo i " << galvociukaiFailas << " faila laikas: " << fixed << setprecision(6) << originalFailoIsvedimoLaikas / 1000.0 << " s" << endl;

            auto visasLaikas = failoSkaitymas + rusiavimoLaikas + skirstymoLaikas + vfailoIsvedimoLaikas + originalFailoIsvedimoLaikas;
            cout << stud.size() + vargsiukai.size() << " irasu testo laikas: " << fixed << setprecision(6) << visasLaikas / 1000.0 << " s" << endl << endl;

          //  patikrintiAtmintiesNaudojimaBeGalv(stud, vargsiukai);

        }else if constexpr (is_same<Container, list<Studentas>>::value) {
            list<Studentas> vargsiukai;
            start = high_resolution_clock::now();
            ListStudentuSkaidymas(stud, vargsiukai);
            end = high_resolution_clock::now();
            auto skirstymoLaikas = duration_cast<milliseconds>(end - start).count();
            cout << "Dalijimo i dvi grupes laikas: " << fixed << setprecision(6) << skirstymoLaikas / 1000.0 << " s" << endl;

            string vargsiukaiFailas = failoPav + "_v.txt";
            string galvociukaiFailas = failoPav + "_g.txt";

            start = high_resolution_clock::now();
            rasytiIFaila(vargsiukai, vargsiukaiFailas);
            end = high_resolution_clock::now();
            auto vfailoIsvedimoLaikas = duration_cast<milliseconds>(end - start).count();
            cout << "Irasymo i " << vargsiukaiFailas << " faila laikas: " << fixed << setprecision(6) << vfailoIsvedimoLaikas / 1000.0 << " s" << endl;

            start = high_resolution_clock::now();
            rasytiIFaila(stud, galvociukaiFailas);
            end = high_resolution_clock::now();
            auto originalFailoIsvedimoLaikas = duration_cast<milliseconds>(end - start).count();
            cout << "Irasymo i " << galvociukaiFailas << " faila laikas: " << fixed << setprecision(6) << originalFailoIsvedimoLaikas / 1000.0 << " s" << endl;

            auto visasLaikas = failoSkaitymas + rusiavimoLaikas + skirstymoLaikas + vfailoIsvedimoLaikas + originalFailoIsvedimoLaikas;
            cout << stud.size() + vargsiukai.size() << " irasu testo laikas: " << fixed << setprecision(6) << visasLaikas / 1000.0 << " s" << endl << endl;

    }
    }
}
/**
* \brief Naudotojo pasirinktos programos vykdymas
*
* Funkcijoje vykdomos funkcijos priklausomai nuo naudotojo pasirinkimo, kai pasirenkama programa turi veikti ir su vektoriais, ir su listais:
* 0 - Duomenu ivedimas ranka
* 1 - Duomenu nuskaitymas nuo failo
* 3 - Programos greicio analize
* \tparam
* \param
*/
template <typename Container>
void programosPasirinkimas(int ats, Container &studentai){
    try {
    if (ats == 1){
        cout<< "Kuri faila norite nuskaityti? (Pasirinkite skaiciu): \n"<<
                "1 - kursiokai.txt \n"<<
                "2 - studentai_1000.txt \n"<<
                "3 - studentai_10000.txt \n"<<
                "4 - studentai_100000.txt \n"<<endl;
        int failas;
        cin >> failas;
        string failoPav;
        switch (failas) {
            case 1: failoPav = "kursiokai.txt"; break;
            case 2: failoPav = "studentai_1000.txt"; break;
            case 3: failoPav = "studentai_10000.txt"; break;
            case 4: failoPav = "studentai_100000.txt"; break;
            default: cout << "Tokio failo nera" << endl; return;
        }
        skaitytiFaila(studentai, failoPav);
        if constexpr (is_same<Container, vector<Studentas>>::value) {
            sort(studentai.begin(), studentai.end(), rusiavimasPavarde);
        } else if constexpr (is_same<Container, list<Studentas>>::value) {
            studentai.sort(rusiavimasPavarde);
        }
        spausdinimas(studentai);

    }else if (ats == 0){
        cout<<"Kiek studentu ivesite?: ";
        int skaicius;
        while (!(cin >> skaicius) || skaicius <= 0){
            cout << "Netinkama ivesti, bandykite dar karta: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        for(int i=0; i<skaicius; i++){
            cout<<"Iveskite informacija: "<<endl;
            Studentas A;
            cin >> A;
            studentai.push_back(A);
            cout << "Studento objektas saugomas adresu: " << &studentai.back() << endl;
            A.valymas();
        }
        if constexpr (is_same<Container, vector<Studentas>>::value) {
            sort(studentai.begin(), studentai.end(), rusiavimasPavarde);
        } else if constexpr (is_same<Container, list<Studentas>>::value) {
            studentai.sort(rusiavimasPavarde);
        }

        spausdinimas(studentai);

    }else if (ats == 3){
        cout << "Kaip norite rusiuoti studentus?: \n"
            << "1 - pagal pavardes \n"
            << "2 - pagal galutini bala mazejancia tvarka \n"
            << "3 - pagal galutini bala didejancia tvarka \n" << endl;
        int rusiavimoPasirinkimas;
        cin >> rusiavimoPasirinkimas;
        cout << "Kaip norite isskirtyti studentus?: \n"
            << "1 - Sukuriant du naujus vargsiuku ir galvociu konteinerius \n"
            << "2 - Sukuriant nauja vargsiuku konteineri ir istrinant tuos studentus is studentai konteinerio \n"
            <<"3 - Panaudojant 2 strategija i ja itraukus efektyvesnius metodus \n" << endl;
        int strategijosPasirinkimas;
        cin >> strategijosPasirinkimas;

        vector<string> testuojamiFailai = {
            "studentai_1000.txt",
            "studentai_10000.txt",
            "studentai_100000.txt",
            "studentai_1000000.txt",
            "studentai_10000000.txt"
            };

        if constexpr (is_same<Container, vector<Studentas>>::value) {
            for (const auto& failoPav : testuojamiFailai) {
                cout << "Testuojamas failas: " << failoPav << endl;
                failuTestavimas(failoPav, studentai, rusiavimoPasirinkimas, strategijosPasirinkimas);
            }
        } else if constexpr (is_same<Container, list<Studentas>>::value) {
            for (const auto& failoPav : testuojamiFailai) {
                cout << "Testuojamas failas: " << failoPav << endl;
                failuTestavimas(failoPav, studentai, rusiavimoPasirinkimas, strategijosPasirinkimas);
            }
        }
        }
    } catch (const std::runtime_error &e){
        cout << "Klaida: " << e.what() << endl;
    } catch (...){
        cout << "Ivyko nezinoma klaida." << endl;
    }
}

#endif // TEMPLATES_H_INCLUDED
