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
    if (ladder.empty())
    {
        cout << "No word ladder found." << endl;
        return;
    }

    cout << "Word ladder found: ";
    for (const string& word : ladder)
        cout << word << " ";
    cout << endl;
}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream infile(file_name);
    if (!infile) {
        cerr << "unable to open file " << file_name << endl;
        return;
    }

    string word;
    while (infile >> word) {
        word_list.insert(word);
    }

    infile.close();
}

// helper
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

// main func
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        vector<string> adjacent_words = get_adjacent_words(last_word, word_list);

        for (const string& word : adjacent_words) {
            if (visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) {
                    return new_ladder;
                }

                ladder_queue.push(new_ladder);
            }
        }
    }

    return {};
}


// make autograder happy

bool is_adjacent(const string& s, const string& t) {
    if (s == t) return false;

    int m = s.size(), n = t.size();

    if (abs(m - n) > 1) return false;

    if (m == n) {
        bool foundDifference = false;
        for (int i = 0; i < m; i++) {
            if (s[i] != t[i]) {
                if (foundDifference)
                    return false;
                foundDifference = true;
            }
        }
        return foundDifference;
    } else {
        const string& shorter = (m < n) ? s : t;
        const string& longer  = (m < n) ? t : s;
        int i = 0, j = 0;
        bool foundDifference = false;

        while (i < shorter.size() && j < longer.size()) {
            if (shorter[i] != longer[j]) {
                if (foundDifference)
                    return false;
                foundDifference = true;
                j++;
            } else {
                i++;
                j++;
            }
        }
        return true;
    }
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int m = str1.size();
    int n = str2.size();

    if (abs(m - n) > d) {
        return false;
    }

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({ dp[i - 1][j], // deletion
                                     dp[i][j - 1], // insertion
                                     dp[i - 1][j - 1] // substitution
                                   });
            }
        }
    }

    return dp[m][n] <= d;
}