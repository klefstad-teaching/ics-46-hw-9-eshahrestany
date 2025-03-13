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

int main()
{
    return 0;
}