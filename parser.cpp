#include "parser.hpp"

vector<pair<pair<string, string>, double>> Parser::parseFile(const string& fileName) {

    cout << "--- Начинаю читать файл базы данных" << endl;

    vector<pair<pair<string, string>, double>> data;

    ifstream file(fileName);
    string line;

    getline(file, line);

    while (getline(file, line)) {

        stringstream ss(line);

        string word, assoc, posTag, dir;
        double weight, mirrorWeight;
        int isSafe;

        getline(ss, word, ';');
        getline(ss, assoc, ';');
        getline(ss, posTag, ';');
        getline(ss, dir, ';');
        ss >> weight;
        ss.ignore(1, ';');
        ss >> mirrorWeight;
        ss.ignore(1, ';');
        ss >> isSafe;

        if (safeMod && isSafe == 0 || !noun && posTag == "NOUN" || !adj && posTag == "ADJ" ||
            !verb && posTag == "VERB" || !adverb && posTag == "ADVERB" || !noTag && posTag == "NO_TAG" ||
            !phrase && posTag == "PHRASE") continue;
        
        if (dir != "REV") data.push_back(make_pair(make_pair(word, assoc), weight));

    }

    file.close();

    cout << "--- Файл базы данных прочтен успешно!" << endl;

    return data;

}

void Parser::prepareFile(const string& fileName, const string& newFileName) {

    cout << "--- Начинаю подготавливать файл базы данных" << endl;

    ifstream file(fileName);
    ofstream newFile(newFileName);
    string line;

    getline(file, line);
    newFile << line << endl;

    while (getline(file, line)) {

        stringstream ss(line);

        string word, assoc, posTag, dir;
        double weight, mirrorWeight;
        int isSafe;

        getline(ss, word, ';');
        getline(ss, assoc, ';');
        getline(ss, posTag, ';');
        getline(ss, dir, ';');
        ss >> weight;
        ss.ignore(1, ';');
        ss >> mirrorWeight;
        ss.ignore(1, ';');
        ss >> isSafe;

        word = lower(word);
        assoc = lower(assoc);

        word = replaceAll(word, "ё", "е");
        assoc = replaceAll(assoc, "ё", "е");

        newFile << word << ';' << assoc << ';' << posTag << ';' << dir << ';' << weight << ';' << mirrorWeight << ';' << isSafe << endl;

    }

    file.close();
    newFile.close();

    cout << "--- Файл базы данных подготовлен успешно!" << endl;

}

string Parser::replaceAll(string str, const string& from, const string& to) {

    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }

    return str;

}

string Parser::lower(const string& input) {

    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
    wstring wide = converter.from_bytes(input);

    locale loc("ru_RU.UTF-8");
    for (auto& ch : wide) {
        ch = tolower(ch, loc);
    }

    return converter.to_bytes(wide);

}
