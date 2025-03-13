#include "ladder.h"

// misc

void error(string word1, string word2, string msg)
{
    cout << msg << "; word1: " << word1 << ", word2: " << word2 << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

void print_word_ladder(const vector<string>& ladder)
{
    for (const string& word : ladder)
        cout << word << " ";
}

// helpers
vector<string> get_adjacent_words(const string& root, const set<string>& word_list) {
    vector<string> result;
    string candidate;

    // replace
    for (size_t i = 0; i < root.size(); i++) {
        candidate = root;
        char original = candidate[i];
        for (char c = 'a'; c <= 'z'; c++) {
            if (c == original) continue;
            candidate[i] = c;
            if (word_list.contains(candidate)) {
                result.push_back(candidate);
            }
        }
    }

    // delete
    for (size_t i = 0; i < root.size(); i++) {
        candidate = root.substr(0, i) + root.substr(i + 1);
            if (word_list.contains(candidate)) {
            result.push_back(candidate);
        }
    }

    // insert
    for (size_t i = 0; i <= root.size(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            candidate = root.substr(0, i) + c + root.substr(i);
            if (word_list.contains(candidate)) {
                result.push_back(candidate);
            }
        }
    }

    return result;
}

int main()
{
    return 0;
}