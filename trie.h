#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>


using namespace std;

struct node {
    bool isRoot;
    bool isWordEnd;
    char symbol;
    int frequency;
    vector <shared_ptr<node>> next;
};

class Trie {

    public:
    
        Trie();
    
       ~Trie();
    
        shared_ptr<node> InitNode(bool isRootNode);//initializes trie nodes
    
        void AddWord(string word);//add words to the trie

        void BuildTree(vector<string>buildList);//builds an initial trie from a list a of words
    
        int LookUpWord(string word);//looks up a word in the trie
    
        vector<pair<int, string>> AutoComplete(string word); //autcompletes a word

        shared_ptr<node> InitRoot();//initializes the root node

        void PrintTrie();//prints the current trie

        string ConverttoLower(string str); // converts upper case letter to lower case letters

    
    private:
    
        void AddWordHelper(string word, shared_ptr<node> current);
    
        shared_ptr<node> LookUpWordHelper(string word, shared_ptr<node> current);
    
        vector<pair<int, string>>  AutoCompleteHelper(string &str, shared_ptr<node> current, vector<pair<int, string>> &wordlist);

        vector<pair<string, int>> PrintTrieHelper(string str, shared_ptr<node> current, vector<pair<string, int>>&full_trie);

        shared_ptr<node> root;

};