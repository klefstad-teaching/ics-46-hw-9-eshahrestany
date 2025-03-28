#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg);
bool edit_distance_within(const string& str1, const string& str2, int d);
bool is_adjacent(const string& word1, const string& word2);
vector<string> get_adjacent_words(const string& root, const set<string>& word_list); // i honestly hate the pseudocode implementation so im doing this
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list);
void load_words(set<string> & word_list, const string& file_name);
void print_word_ladder(const vector<string>& ladder);
void verify_word_ladder();
