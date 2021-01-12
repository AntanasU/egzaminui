#include"funkcijos.h"

bool patikra(char c) {
    return !isalpha(c);
}

void zodziu_kiekis(string pav) {
	ifstream failas(pav);
    int eilute = 0;
    map<string, pair<int, vector<int>>> zodziai;
    string s;
    while (getline(failas, s))
    {
        eilute++;
        //visas raides pakeicia i mazasias raides
        transform(s.begin(), s.end(), s.begin(), tolower);
        // ne raides pakeicia i tarpus
        replace_if(s.begin(), s.end(), patikra, ' ');
        istringstream ss(s);
        while (ss >> s) {
            zodziai[s].first++;
            zodziai[s].second.push_back(eilute);
        }
    }
    for (auto z : zodziai) {
        if (z.second.first > 1) {
            cout << "Zodis: " << left << setw(15) << z.first << " kiekis " << left << setw(4) << z.second.first << "vietos: ";
            for (auto t : z.second.second)
                cout << t << ", ";
            cout << endl;
        }
    }
    failas.close();
}

void puslapiai(string pav) {
    ifstream failas(pav);
    string eilute;
    vector<string> puslapiai = {};
    while (getline(failas, eilute)) {
        istringstream eilute(eilute);
        string zodis;
        //patikrina ar zodis yra svetaine
        while (eilute >> zodis) {
            if (regex_match(zodis, regex("^(https?:\\/\\/)?([\\da-z\\.-]+)\\.([a-z\\.]{2,6})([\\/\\w \\.-]*)*\\/?$")) ||
                regex_match(zodis, regex("(http|https)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)")))
                    puslapiai.push_back(zodis);
        }
    }
    failas.close();
    ofstream rez("rezultatai.txt");
    rez << "rastos internetines svetaines:" << endl;
    for (auto p : puslapiai) {
        rez << p << endl;
    }
    rez.close();
    
}