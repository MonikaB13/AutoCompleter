#include "trie.h"
#include <algorithm>

Trie::Trie(){

}
    
Trie::~Trie(){
    
}

shared_ptr<node> Trie::InitNode(bool isRootNode){ //initializes node for a letter
    
    shared_ptr<node> ret(new node);
    ret -> isRoot = isRootNode;
    ret -> isWordEnd = false;
    ret -> symbol = '\0';
    ret -> frequency = 0;
    ret -> next;
    return ret;
}

shared_ptr<node> Trie::InitRoot(){ //initializes the root node
    root=InitNode(true);
    return root;
}

string Trie::ConverttoLower(string str){
    string lowerStr;
    int size = str.size();
    for(int i=0; i<size; i++){
        
        char c = str[0];
        str.erase(0,1);
        if(int(c)<90){
            c = int(c)+32;
        }
        lowerStr.push_back(c);
        

   
    }
    return lowerStr;
}

void Trie::AddWord(string word){ //adds word to the trie
    if (word.size()==0){
        return;
    }
    word = ConverttoLower(word);
    AddWordHelper(word, root);
}

void Trie::AddWordHelper(string word, shared_ptr<node>current){
    if (word.size()==0){ //if you are out of letters
            current->isWordEnd = true; //mark as word end
            current->frequency = current->frequency + 1; //update word frequency
            return;
    }

    for (int i=0; i < current->next.size(); i++){  //loops through the nodes next vector
        if (word[0]==current->next[i]->symbol){  //if the first letter of the word = the letter of the node next[i] points to
            shared_ptr<node> child = current->next[i]; //child is the pointer in next[i]
            return AddWordHelper(word.erase(0,1), child);//recursively call addword helper on the word with the first letter removed and the child
        }
    }
    shared_ptr<node>child = InitNode(false); //letter is not found in current->next create a new node pointed to by child
    child->symbol = word[0]; //childs symbol is the first letter remaining in the word
    current->next.push_back(child); //add child to the current nodes next vector
    AddWordHelper(word.erase(0,1), child); //recursively call addword helper on the child and remaining word less the first letter
}

void Trie::BuildTree(vector<string>buildList){
    if(buildList.size()==0){
        return;
    }
    root=InitRoot();//initiate root node for the tree
    for(int i=0; i<buildList.size(); i++){ //loop to add all words in initial build list
        AddWord(buildList[i]); 
    }
    return;
}

int Trie::LookUpWord(string word){
    word = ConverttoLower(word);
    if(word.size()==0){ //if there is nothing to look up
        return 0; 
    }
    shared_ptr<node> current = LookUpWordHelper(word, root);
    if (current == NULL){ //if lookup word helper returns NULL
        return 0;
    }
    if (current->isWordEnd==true){ //if at word end return frequency
        return current->frequency;
    }
    return 0;
}
        

shared_ptr<node>Trie::LookUpWordHelper(string word, shared_ptr<node> current){
    if(word.size()==0){
        return current;
    }
    for(int i=0; i<current->next.size(); i++){  //iterate through currents next vector
        if (word[0]==current->next[i]->symbol){  //if the node the pointer in current next[i] points to has the same letter as the first letter of the word
            shared_ptr<node> child = current->next[i]; //child equals the pointer in current next[i]
            return LookUpWordHelper(word.erase(0,1), child); //call lookup helper on word minus is it's first letter and child
        }
    }
    return NULL;
}

vector<pair<int, string>> Trie::AutoCompleteHelper(string &str, shared_ptr<node> current, vector<pair<int, string>> &wordlist){

    if (current->isWordEnd==true){ //if it's the end of the word, add it to the wordlist
        wordlist.push_back({current->frequency, str}); 
    }
    for(int i=0; i< current->next.size(); i++){ //iterate through current next 
        shared_ptr<node> child=current->next[i];
        str.push_back(child->symbol); //add symbol to string
        AutoCompleteHelper(str, child, wordlist); 
        str.pop_back(); 
    } 
    return wordlist;  //?????
}   

vector<pair<int, string>> Trie::AutoComplete(string word){
    word = ConverttoLower(word);
    if(word.size()==0){ //if string word is empty
        return {};//return an empty vector
    }
    shared_ptr<node> current = LookUpWordHelper(word, root); //call lookup word helper to traverse through the 3 three letters your trying to autocomplete
    if(current == NULL){ //if current is null there are no suggestions, return an empty vector
        return {};
    }
    string str = word; //pass the 3 letter input into another string
    
    vector<pair<int, string>> wordlist;
    //vector<string>wordlist; //declare vector word list that will save autocomplete suggestions
    wordlist = AutoCompleteHelper(str, current, wordlist); //list of suggestions is returned by autocomplete helper


    return wordlist; //list of suggestions, change this to a dictionary?
}

vector<pair<string, int>> Trie::PrintTrieHelper(string str, shared_ptr<node> current, vector<pair<string, int>>&full_trie){
    if (current->isWordEnd==true){ //if it's the end of the word, add it to the wordlist
        full_trie.push_back({str, current->frequency}); 
    }
    for(int i=0; i< current->next.size(); i++){ //iterate through current next 
        shared_ptr<node> child=current->next[i];
        str.push_back(child->symbol); //add symbol to string
        PrintTrieHelper(str, child, full_trie); 
        str.pop_back(); 
    } 
    return full_trie;
}

void Trie::PrintTrie(){
    string str;
    vector<pair<string, int>> full_trie;
    full_trie=PrintTrieHelper(str, root, full_trie);
    sort(full_trie.begin(), full_trie.end());
    for(int i=0; i<full_trie.size(); i++){
        cout<<full_trie[i].first<<", "<<full_trie[i].second<<endl;
    }
    return;
}





        
