#include "ladder.h"

void error(string word1, string word2, string msg)
{
    std::cout << word1 << " : " << word2 << " : " << msg << "\n";
}

bool edit_distance_within(const string & str1, const string & str2, int d)
{
    int str1_length = str1.length();
    int str2_length = str2.length();
    int count = 0;

    if (str1_length == str2_length){
        for (int i = 0; i < str1_length; ++i){
            if (str1[i] != str2[i])
                ++count;
        }
        return count <= d;
    }

    else if (abs(str1_length - str2_length) == d){
        string shorter = str1;
        string longer = str2;
        if (str1_length > str2_length){
            shorter = str2;
            longer = str1;
        }

        for (int i = 0, j = 0; i < shorter.length() && j < longer.length();){
            if (shorter[i] != longer[j]){
                ++count;
                ++j;
            }
            else{
                ++i;
                ++j;
            }
        }
        return count <= d;

    }
    return false;
}

bool is_adjacent(const string & word1, const string & word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string & begin_word, const string & end_word, const set<string> & word_list)
{
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (string word : word_list){
            if (is_adjacent(last_word, word)){
                if (visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string & file_name)
{
    ifstream in(file_name);
    string word;
    while (in >> word)
        word_list.insert(word);
    in.close();
}

void print_word_ladder(const vector<string> & ladder)
{
    for (string word : ladder)
        std::cout << word << " ";
    std::cout << "\n";
}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    std::cout << (generate_word_ladder("cat", "dog", word_list).size() == 4) << std::endl;
    std::cout << (generate_word_ladder("marty", "curls", word_list).size() == 6) << std::endl;
    std::cout << (generate_word_ladder("code", "data", word_list).size() == 6) << std::endl;
    std::cout << (generate_word_ladder("work", "play", word_list).size() == 6) << std::endl;
    std::cout << (generate_word_ladder("sleep", "awake", word_list).size() == 8) << std::endl;
    std::cout << (generate_word_ladder("car", "cheat", word_list).size() == 4) << std::endl;
}