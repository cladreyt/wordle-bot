#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <unordered_set>

using namespace std;

// Function to compute the Jaccard similarity coefficient between two strings
double jaccard_similarity(const string& s1, const string& s2) {
    unordered_set<char> set1(s1.begin(), s1.end());
    unordered_set<char> set2(s2.begin(), s2.end());
    int intersection = 0;
    for (char c : set1) {
        if (set2.count(c)) {
            intersection++;
        }
    }
    int union_size = set1.size() + set2.size() - intersection;
    return static_cast<double>(intersection) / union_size;
}

// Function to sort a vector of strings based on their average similarity to the other strings
vector<string> sort_strings_by_similarity(vector<string>& strings) {
    int n = strings.size();
    vector<double> avg_similarities(n);
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += jaccard_similarity(strings[i], strings[j]);
            }
        }
        avg_similarities[i] = sum / (n - 1);
    }
    vector<pair<double, string>> pairs(n);
    for (int i = 0; i < n; i++) {
        pairs[i] = make_pair(avg_similarities[i], strings[i]);
    }
    sort(pairs.begin(), pairs.end(), greater<pair<double, string>>());
    vector<string> sorted_strings(n);
    for (int i = 0; i < n; i++) {
        sorted_strings[i] = pairs[i].second;
    }
    return sorted_strings;
}
//start new code
int countCommonLetters(string s1, string s2) {
    int count = 0;
    for (int i = 0; i < s1.length(); i++) {
        for (int j = 0; j < s2.length(); j++) {
            if (s1[i] == s2[j]) {
                count++;
                break;
            }
        }
    }
    return count;
}

bool cmp(string s1, string s2, const vector<string>& vec) {
    int count1 = 0, count2 = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (countCommonLetters(s1, vec[i]) > countCommonLetters(s2, vec[i])) {
            count1++;
        } else if (countCommonLetters(s1, vec[i]) < countCommonLetters(s2, vec[i])) {
            count2++;
        }
    }
    return count1 > count2;
}

void sort_strings_by_common_letters(vector<string>& vec) {
    sort(vec.begin(), vec.end(), [&vec](string s1, string s2){ return cmp(s1, s2, vec); });
}
//end new code

// to run use g++ -std=c++11 solver.cpp -o solver
// ./solver
bool isPossible(string word, vector<vector<pair<char, char>>> &savedOutput){
    for(int guessNum = 0; guessNum < savedOutput.size(); guessNum++){
        for(int charIndex = 0; charIndex < 5; charIndex++){
            if(savedOutput[guessNum][charIndex].second == 'g'){//green (g)
                if(word[charIndex] != savedOutput[guessNum][charIndex].first){ return false; }
            }else if(savedOutput[guessNum][charIndex].second == 'y'){//yellow (y)
                int findChar = word.find(savedOutput[guessNum][charIndex].first);
                if(findChar == -1 || findChar == charIndex){ return false; }

                bool inWord = false;
                for(int i = 0; i < 5; i++){
                    if(word[i] == savedOutput[guessNum][charIndex].first){
                        if(i == charIndex){ return false; }
                        if(!(savedOutput[guessNum][i].first == word[i] && savedOutput[guessNum][i].second == 'g')){ 
                            inWord = true;
                        }
                    }
                }
                //edgecase for words with same letter and guess has one green and one yellow
                //yellow letter must be in different index from the green letter (that is the same letter)
            }else if(word.find(savedOutput[guessNum][charIndex].first) != -1){//letter savedOutput[guessNum][charIndex].second is gray (letter charIndex is gray in guess #guessNum)
                //if word contains this and this guess doesn't have this letter in green or yellow, throw it out
                
                //the word has the grayed out letter in it, must make sure it's in an index where it's green
                for(int i = 0; i < 5; i++){
                    if(word[i] == savedOutput[guessNum][charIndex].first){//word[i] is the one grayed out in guess charIndex
                        if(i == charIndex){ return false; }
                        if(savedOutput[guessNum][i].second != 'g'){
                            bool foundYellow = false;
                            for(int j = 0; j < 5; j++){
                                if(savedOutput[guessNum][j].first == word[i] && savedOutput[guessNum][j].second == 'y'){
                                    foundYellow = true;
                                }
                            }
                            if(!foundYellow){ return false; }
                        }
                    }
                }
            }
        }
    }
    return true;

}

void getPossWords(vector<vector<pair<char, char>>> &savedOutput, vector<string> &answers) {
    vector<string> updatedAns;
    for(string word : answers){
        if(isPossible(word, savedOutput)){
            updatedAns.push_back(word);
        }
    }

    answers = updatedAns;
    for(vector<pair<char, char>> vec : savedOutput){
        for(pair<char, char> pair : vec){
            cout << "<" << pair.first << "," << pair.second << "> ";
        }
        cout << "\n";
    }
}

int main() {
    ifstream wordsFile("words.txt");
    vector<string> answers;
    vector<vector<pair<char, char>>> savedOutput;
    string word;
    while(wordsFile >> word){
        answers.push_back(word);
    }
    wordsFile.close();

    cout << "\n-- Wordle Bot --\n";
    for(int guess = 0; guess < 6; guess++){
        string guessWord, wordleOutput;
        cout << "Enter guess " << guess + 1 << ": ";
        cin >> guessWord;
        cout << "\nEnter Wordle output (g/y/x): ";
        cin >> wordleOutput;

        savedOutput.push_back(vector<pair<char, char>>());

        for(int i = 0; i < 5; i++){
            pair<char, char> pair(guessWord[i], wordleOutput[i]);
            savedOutput[guess].push_back(pair);
        }

        getPossWords(savedOutput, answers);

        //sort_strings_by_similarity(answers);
        sort_strings_by_common_letters(answers);
        for(string word : answers){ cout << word << "\n"; }
    }
}
