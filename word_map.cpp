#include "word_map.hpp"

void WordMap::addAssociation(const string& word1, const string& word2, double weight) {

    if (weight > 0.0) wordMap[word1].push_back(make_pair(word2, weight));

}

void WordMap::addWords(const vector<pair<pair<string, string>, double>>& data) {

    cout << "--- Начинаю добавлять ассоциации в карту слов" << endl;

    for (auto& [words, weight] : data)
        addAssociation(words.first, words.second, weight);
    
    cout << "--- Ассоциации успешно добавлены!" << endl;

}

pair<string, int> WordMap::findAssociation(const unordered_set<string>& words) {

    cout << "--- Начинаю искать ассоциацию к словам" << endl;

    queue<string> wordQueue;
    unordered_set<string> visitedWords;

    string startWord;
    for (const auto& [word, associations] : wordMap) {
        if (words.find(word) == words.end()) {
            startWord = word;
            break;
        }
    }

    map<double, pair<string, unordered_set<string>>, greater<double>> associationVariants;

    wordQueue.push(startWord);
    visitedWords.insert(startWord);

    while (!wordQueue.empty()) {

        string word = wordQueue.front();
        wordQueue.pop();

        if (wordMap.find(word) != wordMap.end()) {

            double sumWeightAssociated = 0.0;
            unordered_set<string> associatedWords;

            for (const auto& [association, weight] : wordMap.at(word)) {

                if (words.find(association) != words.end() && weight > minAssocWeight) {

                    sumWeightAssociated += weight;
                    associatedWords.insert(association);

                } else if (wordMap.find(association) != wordMap.end()) {

                    for (const auto& [intermedAssociation, intermedWeight] : wordMap.at(association)) {
                        
                        if (words.find(intermedAssociation) != words.end() && intermedWeight * weight > minAssocWeight) {
                            sumWeightAssociated += intermedWeight * weight;
                            associatedWords.insert(intermedAssociation);
                        }

                    }

                }

            }

            sumWeightAssociated *= pow(associatedWords.size(), assocCntRatio);
            if (sumWeightAssociated > minAssocWeight)
                associationVariants[sumWeightAssociated + 1.0] = make_pair(word, associatedWords);

            for (const auto& [association, weight] : wordMap.at(word)) {
                if (visitedWords.find(association) == visitedWords.end()) {
                    wordQueue.push(association);
                    visitedWords.insert(association);
                }
            }
        
        }

    }

    int cnt = 0;
    for (const auto& [weight, associations] : associationVariants) {
        cout << "--- " << associations.first << " (" << weight << "): ";
        for (const auto& word : associations.second)
            cout << word << ' ';
        cout << endl;
        if (++cnt == 20) break;
    }

    if (associationVariants.size() > 0) cout << "--- Ассоциации успешно найдены!" << endl;
    else cout << "--- Ассоциации не найдены!" << endl;

    return make_pair(associationVariants.begin()->second.first, associationVariants.begin()->second.second.size());

}

vector<string> WordMap::getLastAssociatedWords() const { return lastAssociatedWords; }
