#include <iostream>
#include <vector>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi;
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>> &veze, Tah &tah) {
    int from = tah.z - 'A';
    int to = tah.na - 'A';

    if (!veze[from].empty()) {
        tah.disk = veze[from].back(); // Získáme horní disk
        veze[from].pop_back();        // Odebereme ho z původní věže
        veze[to].push_back(tah.disk); // Přidáme ho na cílovou věž
    }

    tah.stavVezi = veze; // Uložení aktuálního stavu věží po tahu
}


// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {
    if (n <= 0) return; // Pokud je počet disků 0 nebo záporný, nic neděláme

    if (n == 1) {
        Tah tah = {n, z, cil, {}}; // Inicializace tahu
        provedTah(veze, tah);      // Provedení tahu
        tahy.push_back(tah);       // Uložení tahu
        return;
    }

    hanoi(n - 1, z, cil, pomocny, veze, tahy); // Přesun n-1 disků na pomocný kolík

    Tah tah = {n, z, cil, {}}; // Přesun největšího disku na cílový kolík
    provedTah(veze, tah);
    tahy.push_back(tah);

    hanoi(n - 1, pomocny, z, cil, veze, tahy); // Přesun n-1 disků na cílový kolík
}


// Funkce pro zobrazení stavu věží
void zobrazVeze(const vector<vector<int>> &veze) {

    int maxHeight = 0;
    for (const auto &vez : veze) {
        maxHeight = max(maxHeight, static_cast<int>(vez.size()));
    }
    
    for (int i = maxHeight - 1; i >= 0; i--) {
        for (const auto &vez : veze) {
            if (i < vez.size()) {
                cout << string(vez[i], '=') << "\t";
            } else {
                cout << "|\t";
            }
        }
        cout << endl;
    }
    cout << "A\tB\tC" << endl;
    cout << "--------------------" << endl;
}

#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;
    cin.ignore();
    
    if (n <= 0) {
        cout << "Počet disků musí být kladné číslo!" << endl;
        return 1;
    }
    
    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }
    
    vector<Tah> tahy;
    hanoi(n, 'A', 'B', 'C', veze, tahy);
    
    // Zobrazení tahů a stavů věží
    for (const Tah &tah : tahy) {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi);
    }
    
    return 0;
}
#endif
