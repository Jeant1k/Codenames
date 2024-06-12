#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <locale>
#include <codecvt>
#include <algorithm>

using namespace std;

class Parser {
public:
    Parser(bool safeMod = false, bool noun = true, bool adj = true, bool verb = true,
           bool adverb = true, bool noTag = true, bool phrase = true)
        : safeMod(safeMod)
        , noun(noun)
        , adj(adj)
        , verb(verb)
        , adverb(adverb)
        , noTag(noTag)
        , phrase(phrase)
    {}

    vector<pair<pair<string, string>, double>> parseFile(const string& fileName);
    void prepareFile(const string& fileName, const string& newFileName);

private:
    string replaceAll(string str, const string& from, const string& to);
    string lower(const string& input);

    bool safeMod;
    bool noun;
    bool adj;
    bool verb;
    bool adverb;
    bool noTag;
    bool phrase;
};