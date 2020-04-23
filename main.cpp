#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <cmath>
#define dmax 1000000000
using namespace std;
string in = {"data10.txt"};

class zadanie {
public:
    int n; // numer zadania
    int p; // czas wykonania
    int w; // waga kary
    int d; // deadline
};

class lista_zadan {
    vector<zadanie> zbior_zadan;
public:
    void wczytaj(vector<zadanie> wczytane);

    void wczytaj();

    void wypisz();

    void usun();

    void sortD();

    int obliczkare();

    zadanie zwroc_zadanie(int ID_zadania) const;

    void usun_zadanie(int ID_zadania);

    void dodaj_zadanie(zadanie oper_zadanie);

    int bruteForceI();

    int bruteForceR(lista_zadan a, lista_zadan b);

    bool czypusta() const;

    int zwroc_wielkosc() const;

    int dynamicznaIteracja();

};

bool D(const zadanie &zad_1, const zadanie &zad_2) {
    return (zad_1.d < zad_2.d);
}

int main() {
    lista_zadan pomocnicza;
    lista_zadan moj_zbiorzadan;
    string tablica_nazw[11] = {"data10.txt", "data11.txt", "data12.txt", "data13.txt", "data14.txt", "data15.txt",
                               "data16.txt", "data17.txt", "data18.txt", "data19.txt", "data20.txt",};

    cout << "po sortowaniu lalal" << endl;



    // int tmp = moj_zbiorzadan.obliczkare();
    //cout << "Fpi = " << tmp << endl;
    //cout << endl;


    for (int i = 0; i < 11; i++) {
        moj_zbiorzadan.usun();
        in = tablica_nazw[i];
        cout << in << endl;
        moj_zbiorzadan.wczytaj();
        //moj_zbiorzadan.wypisz();
        auto poczatek = chrono::high_resolution_clock::now();

        //cout << "BruteR Fpi dla " << in << " wynosi " << moj_zbiorzadan.bruteForceR(moj_zbiorzadan,pomocnicza)<< endl;

        auto koniec = chrono::high_resolution_clock::now();
        auto delta = chrono::duration_cast<chrono::seconds>(koniec - poczatek).count();

        //  cout << "Czas BruteR dla " << in << " wyniosl: " << delta << "s" << endl;

        auto poczatek1 = chrono::high_resolution_clock::now();

        cout << "PDiter Fpi dla " << in << " wynosi " << moj_zbiorzadan.dynamicznaIteracja() << endl;

        auto koniec1 = chrono::high_resolution_clock::now();
        auto delta1 = chrono::duration_cast<chrono::milliseconds>(koniec1 - poczatek1).count();

        cout << "PDiter  dla " << in << " wyniosl: " << delta1 << "ms" << endl;


        //moj_zbiorzadan.wypisz();

        // moj_zbiorzadan.wypisz();


        /* auto poczatek = chrono::high_resolution_clock::now();
         cout << moj_zbiorzadan.bruteForceR(moj_zbiorzadan, pomocnicza );
         auto koniec = chrono::high_resolution_clock::now();
         auto delta = chrono::duration_cast<chrono::seconds>(koniec - poczatek).count();
         cout << "Czas sortowania wyniosl: " << delta << "s" << endl;*/



    }


    return 0;
}

void lista_zadan::wczytaj() {
    ifstream plik(in);
    if (plik.good() == true) {
        int n, k;
        zadanie zad;                  //obiekt tymczasowy do wrzucania danych do wektora
        plik >> n;                    //ilosc zadan
        plik >> k;
        for (int i = 0; i < n; i++) {
            zad.n = i;                //przypisanie numeru zadania
            plik >> zad.p;            //wczytanie p
            plik >> zad.w;            //wczytanie w
            plik >> zad.d;            //wczytanie d
            zbior_zadan.push_back(zad);                    //wrzucenie calego obiektu na koniec
        }
        cout << "Plik odczytany" << endl;
        cout << "liczba zadan = " << n << endl;
        cout << "liczba parametrow = " << k << endl;
        plik.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku" << endl;
    }
}


void lista_zadan::wczytaj(vector<zadanie> wczytane) {
    zbior_zadan = wczytane;
}

void lista_zadan::wypisz() {
    int tmp_p, tmp_w, tmp_d;

    for (auto i = 0; i < zbior_zadan.size(); i++) {
        tmp_p = zbior_zadan[i].p;
        tmp_w = zbior_zadan[i].w;
        tmp_d = zbior_zadan[i].d;
        cout << tmp_p << " " << tmp_w << " " << tmp_d << endl;

    }
}

void lista_zadan::sortD() {
    // auto poczatek = chrono::high_resolution_clock::now();
    sort(zbior_zadan.begin(), zbior_zadan.end(), D);
    //  auto koniec = chrono::high_resolution_clock::now();
    // auto delta = chrono::duration_cast<chrono::nanoseconds>(koniec - poczatek).count();
    // cout << "Czas sortowania wyniosl: " << delta << "ms" << endl;
}

int lista_zadan::obliczkare() {
    int czas = 0;
    int kara = 0;

    for (auto i = 0; i < zbior_zadan.size(); i++) {
        czas = czas + zbior_zadan[i].p;
        kara = kara + (zbior_zadan[i].w * max(0, czas - zbior_zadan[i].d));
    }
    return kara;
}

int lista_zadan::bruteForceI() {
    sortD();
    int kara = dmax;
    while (next_permutation(zbior_zadan.begin(), zbior_zadan.end(), D)) {
        kara = min(kara, obliczkare());
    }
    return kara;
}

zadanie lista_zadan::zwroc_zadanie(int ID_zadania) const {
    return zbior_zadan[ID_zadania];
}

void lista_zadan::usun_zadanie(int ID_zadania) {
    zbior_zadan.erase(zbior_zadan.begin() + ID_zadania);
}

void lista_zadan::usun() {
    zbior_zadan.erase(zbior_zadan.begin(), zbior_zadan.end());
}

void lista_zadan::dodaj_zadanie(zadanie oper_zadanie) {
    zbior_zadan.push_back(oper_zadanie);
}

bool lista_zadan::czypusta() const {
    return zbior_zadan.empty();
}

int lista_zadan::zwroc_wielkosc() const {
    return zbior_zadan.size();
}

int lista_zadan::bruteForceR(lista_zadan dozrobienia, lista_zadan gotowe) {
    int kara = dmax;
    zadanie zad;

    if (dozrobienia.czypusta())
        return gotowe.obliczkare();

    for (auto i = 0; i < dozrobienia.zwroc_wielkosc(); i++) {
        lista_zadan lz_dozrobienia = dozrobienia;
        lista_zadan lz_gotowe = gotowe;

        zad = lz_dozrobienia.zwroc_zadanie(i);
        lz_dozrobienia.usun_zadanie(i);
        lz_gotowe.dodaj_zadanie(zad);

        kara = min(kara, bruteForceR(lz_dozrobienia, lz_gotowe));
    }
    return kara;
}

int lista_zadan::dynamicznaIteracja(){
    vector<int> podproblemy (pow(2, zbior_zadan.size()));
    podproblemy[0] = 0;
    int czas_trwania, podproblem, poprzednie, kara;
    
    for (int i = 1; i < podproblemy.size(); i++){
        podproblem = dmax; //najwieksza kara
        
        for (int j = 0; j < zbior_zadan.size(); j++){ //
            if (i & (1<<j)){
                czas_trwania = 0;
                
                for (int k = 0; k < zbior_zadan.size(); k++){
                    if (i & (1<<k)){
                        czas_trwania += zbior_zadan[k].p;
                    }
                }
                kara = zbior_zadan[j].w * max(0, czas_trwania - zbior_zadan[j].d);
                poprzednie = i & (~(1<<j));
                podproblem = min(podproblem, kara + podproblemy[poprzednie]);
            }
        }
        podproblemy[i] = podproblem;
    }
    return podproblemy.back();
}
