/**
 * \mainpage Projekto dokumentacija
 *
 * \section intro Įvadas
 *
 * Šis projektas skirtas studentų informacijos tvarkymui ir analizei.
 * Čia pateikiama informacija apie projekto struktūrą, funkcijas ir klases.
 *
 * \section features Funkcionalumas
 * - Studentų duomenų nuskaitymas iš failo ir ivedimas ranka.
 * - Galutinio balo apskaičiavimas (vidurkis ir mediana).
 * - Duomenų spausdinimas į konsolę arba failą.
 */
#include "Mylib.h"
#include "Stud.h"
#include "templates.h"

int main(){

    cout<< "Pasirinkite programa: \n" <<
        "0 - jei norite studentu duomenis ivesite ranka, \n" <<
        "1 - jei norite studentu duomenis nuskaityti nuo failo, \n" <<
        "2 - jei norite generuoti failus su studentu duomenimis, \n" <<
        "3 - jei norite atlikti programos veikimo greicio analize, \n" <<
        "4 - jei norite demonstruoti kaip veikia triju metodu taisykle, \n" <<
        "5 - jei norite demonstruoti Zmogaus klase: \n"
        << endl;
    int ats;
    while(!(cin >> ats) || (ats != 1 && ats != 0 && ats != 2 && ats != 3 && ats != 4 && ats != 5)){
        cout << "Netinkama ivestis. Bandykite dar karta: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (ats == 1 || ats == 0 || ats == 3){
        cout << "Kuri konteineri norite naudoti? \n"
        << "1 - vector\n"
        << "2 - list\n";
        int konteineris;
        while(!(cin >> konteineris) || (konteineris != 1 && konteineris != 2)){
            cout << "Netinkama ivestis. Bandykite dar karta: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (konteineris == 1){
            vector<Studentas> Vec1;
            programosPasirinkimas(ats, Vec1);
        } else if (konteineris == 2){
            list<Studentas> List1;
            programosPasirinkimas(ats, List1);
        }
    } else if (ats == 2){
        cout << "Kiek studentu norite sugeneruoti? (iveskite atitinkama skaiciu): \n" <<
                "1 - 1000 studentu \n" <<
                "2 - 10000 studentu \n" <<
                "3 - 100000 studentu \n" <<
                "4 - 1000000 studentu \n" <<
                "5 - 10000000 studentu \n" << endl;
        int skaicius;
        while(!(cin >> skaicius) || (skaicius != 1 && skaicius != 2 && skaicius != 3 && skaicius != 4 && skaicius != 5)){
            cout << "Netinkama ivestis. Bandykite dar karta: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        string failoPav;
        if (skaicius == 1){
            failoPav = "studentai_1000.txt";
            generuotiStudentus(1000, failoPav);
        }else if (skaicius == 2){
            failoPav = "studentai_10000.txt";
            generuotiStudentus(10000, failoPav);
        }else if (skaicius == 3){
            failoPav = "studentai_100000.txt";
            generuotiStudentus(100000, "studentai_100000.txt");
        }else if (skaicius == 4) {
            failoPav = "studentai_1000000.txt";
            generuotiStudentus(1000000, failoPav);
        }else if (skaicius == 5) {
            failoPav = "studentai_10000000.txt";
            generuotiStudentus(10000000, failoPav);
        }else{
            cout << "Klaida" << endl;
        }
    } else if (ats == 4){
        cout << "Demonstruojama Triju metodu taisykle" << endl;
        pademonstruotiTrysMetodus();
    } else if (ats == 5){
        cout << "Demonstruojama Zmogaus klase" << endl;
        //Zmogus zmogus;
        Zmogus* zmogus = new Studentas("Jonas", "Jonaitis");

        cout << zmogus->getVardas() << " " << zmogus->getPavarde() << endl;
        zmogus->spausdinti();

        delete zmogus;
    }
    system("pause");
    return 0;
};

