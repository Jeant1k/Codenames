#include <iostream>

#include "word_map.hpp"
#include "parser.hpp"

using namespace std;

// TODO: возрастание коэффициентов в процессе игры
// TODO: нормировать веса. Прибавить ко всем 1.
// TODO: найти такие коэффициенты, чтобы на каждом раунде было по 2-3 слова
// TODO: предобработать датасет. Сделать столбец с 0/1 неоднокоренная/однокоренная ассоциация 

int main() {

    Parser parser;

    // parser.prepareFile("assoc.csv", "prep_assoc.csv");

    auto data = parser.parseFile("prep_assoc.csv");

    WordMap wordMap;

    wordMap.addWords(data);

    while (true) {

        cout << "Введите количество слов: ";

        int numWords = 0;
        cin >> numWords;

        cout << "Введите слова: ";

        string word;
        unordered_set<string> words;
        for (int i = 0; i < numWords; ++i) {
            cin >> word;
            words.insert(word);
        }

        cout << "--- Поиск ассоциаций к словам: ";
        for (const auto& word : words) cout << word << ' ';
        cout << endl;

        auto association = wordMap.findAssociation(words);

        cout << association.first << ' ' << association.second << endl << endl;

    }

    return 0;

}