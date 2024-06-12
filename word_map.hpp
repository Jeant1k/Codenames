#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

class WordMap {
public:
    void addWords(const vector<pair<pair<string, string>, double>>& data);
    pair<string, int> findAssociation(const unordered_set<string>& words);
    vector<string> getLastAssociatedWords() const;

private:
    void addAssociation(const string& word1, const string& word2, double weight);

    unordered_map<string, vector<pair<string, double>>> wordMap;
    vector<string> lastAssociatedWords;

    double assocCntRatio = 2.0;
    double minAssocWeight = 0.01;

};

// Best: assocCntRatio = 10.0, minAssocWeight = 0.05

/*

Количество слов:    2       3

assocCntRatio:      6.0     1.0

minAssocWeight:     0.015   0.075

*/
