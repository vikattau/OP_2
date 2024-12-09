#ifndef TEMPLATES_H_INCLUDED
#define TEMPLATES_H_INCLUDED
#include "Mylib.h"
#include "Stud.h"

/**
* \brief Spausdina studentų lentelę su jų galutiniais balais.
* Ši funkcija spausdina studentų informaciją, įskaitant vardą, pavardę, galutinį balą pagal vidurkį ir mediana.
* Funkcija veikia tiek su vektoriais, tiek su sąrašais.
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
* \brief Nuskaito duomenis iš failo į konteinerį.
* Ši funkcija nuskaito studentų duomenis iš tekstinio failo ir saugo juos nurodytame konteineryje.
* Jei failas negali būti atidarytas, bus išvedamas klaidos pranešimas.
*
* \tparam Container Konteinerio tipas.
* \param studentai Konteineris, kuriame bus saugomi nuskaityti studentai.
* \param failoPavadinimas Tekstinio failo pavadinimas, iš kurio bus nuskaitomi duomenys.
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
* \brief Skirsto studentus į vargšiukus ir galvočius pagal galutinį balą.
*
* Jei studento galutinis balas mažesnis už 5, jis pridedamas prie vargšiukų konteinerio.
* Jei galutinis balas yra 5 ar didesnis, studentas pridedamas prie galvočių konteinerio.
*
* \tparam Container Konteinerio tipas.
* \param studentai Konteineris, kuriame saugomi visi studentai.
* \param vargsiukai Konteineris, kuriame bus saugomi studentai su galutiniu balu mažesniu už 5.
* \param galvociai Konteineris, kuriame bus saugomi studentai su galutiniu balu 5 ir didesniu.
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
* \brief Įrašo studentų duomenis į failą lentelės formatu.
*
* Ši funkcija įrašo konteineryje esančius studentų duomenis į tekstinį failą. Duomenys yra pateikiami lentelės formatu,
* kuriame kiekvienas studento duomenų laukas (pvz., vardas, pavardė, galutinis balas) išvedamas atitinkamose stulpeliuose.
*
* \tparam Container Konteinerio tipas
* \param failoPav Tekstinio failo pavadinimas, į kurį bus įrašyti studentų duomenys.
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
* \brief Studentų skirstymas pagal pažymį: 2 strategija.
*
* Ši funkcija pirmiausia išrūšiuoja studentus pagal jų galutinį vidurkį, tada studentus, kurių galutinis balas yra mažesnis už 5,
* prideda prie „vargšiukų“ konteinerio. Studentai, kurių galutinis balas yra aukštesnis, lieka originaliame konteineryje,
* tačiau jų nebebus, kadangi jie bus pašalinti iš studentų konteinerio.
*
* \tparam Container Konteinerio tipas
* \param studentai Konteineris, kuriame saugomi visi studentai.
* \param vargsiukai Konteineris, kuriame bus saugomi vargšiukai studentai.
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
* \brief Skirtingi rūšiavimo būdai.
* Priklausomai nuo naudotojo pasirinkimo vykdomas rūšiavimas.
* 1 - rūšiavimas pagal pavardę abėcėlės tvarka.
* 2 - rūšiavimas pagal galutinį balą mažėjimo tvarka (nuo didžiausio iki mažiausio).
* 3 - rūšiavimas pagal galutinį balą didėjimo tvarka (nuo mažiausio iki didžiausio).
*
* \tparam Container Konteinerio tipas
* \param stud Konteineris, kuriame esantys duomenys bus rūšiuojami.
* \param rusiavimoPasirinkimas Naudotojo pasirinktas rūšiavimo būdas (1 - pavardė, 2 - mažėjanti tvarka pagal galutinį balą, 3 - didėjanti tvarka pagal galutinį balą).
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
* \brief Patikrinama, kiek vietos užima konteineriai.
*
* Ši funkcija apskaičiuoja ir išveda kiek vietos užima kiekvienas iš pateiktų konteinerių (pvz., std::vector, std::list) atmintyje.
* Užimama vieta gali būti įvertinta pagal konteinerio dydį ir elementų kiekį, taip pat atsižvelgiant į tam tikras optimizacijas, pavyzdžiui, vietos rezervavimą.
*
* \tparam Container Konteinerio tipas
* \param studentai Konteineris, kurio užimama vieta bus apskaičiuojama.
* \param vargsiukai Konteineris, kurio užimama vieta bus apskaičiuojama.
* \param galvociai Konteineris, kurio užimama vieta bus apskaičiuojama.
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
* \brief Patikrinama, kiek vietos užima konteineriai.
*
* Ši funkcija apskaičiuoja ir išveda, kiek atminties užima nurodyti konteineriai. Tai apima tiek struktūrą, tiek elementus, esančius konteineryje.
* Funkcija spausdins kiekvieno konteinerio užimamą vietą atmintyje.
*
* \tparam Container Konteinerio tipas (pvz., std::vector, std::list).
* \param studentai Konteineris, kurio užimama vieta bus apskaičiuojama.
* \param vargsiukai Konteineris, kurio užimama vieta bus apskaičiuojama.
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
* \brief Programos greičio analizė.
*
* Ši funkcija matuoja, kiek laiko užtrunka atlikti šiuos veiksmus:
* 1. Nuskaityti duomenis iš failo.
* 2. Išrūšiuoti duomenis pagal nurodytą kriterijų.
* 3. Skirstyti studentus į vargšiukus ir galvočius pagal pasirinktą strategiją.
* 4. Įrašyti atitinkamus studentus į vargšiukų ir galvočių failus.
*
* \tparam Container Konteinerio tipas (pvz., std::vector, std::list), kuriame bus saugomi studentai.
* \param failoPav Failo pavadinimas, kurį bus testuojama.
* \param stud Konteineris, kuriame bus saugomi ir įrašomi duomenys.
* \param rusiavimoPasirinkimas Naudotojo pasirinktas rusiavimo metodas (pvz., pagal pavardę, pagal balą).
* \param strategijosPasirinkimas Naudotojo pasirinkta strategija studentų skirstymui į vargšiukus ir galvočius.
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
* \brief Naudotojo pasirinktos programos vykdymas.
*
* Ši funkcija vykdo veiksmus, priklausomai nuo naudotojo pasirinkimo. Programa turi veikti tiek su vektoriais, tiek su listais.
* Galimi pasirinkimai:
*  - 0: Duomenų įvedimas ranka.
*  - 1: Duomenų nuskaitymas iš failo.
*  - 3: Programos greičio analizė.
*
* \tparam Container Konteinerio tipas (pvz., std::vector, std::list), su kuriuo bus atliekami veiksmai.
* \param pasirinkimas Naudotojo pasirinktas veiksmas, kuris nusako, kokia funkcija bus vykdoma (0 - rankinis įvedimas, 1 - nuskaitymas iš failo, 3 - greičio analizė).
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
