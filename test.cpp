#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "trie.h"
#include <set>
#include <algorithm>
#include <sstream>



using namespace std;

bool revsort(const pair<int,string> &a,  
               const pair<int,string> &b) 
{ 
       return (a.first > b.first); 
} 

int main(){
    Trie y;
    vector<pair<int, string>> trie_list;
    vector<string> buildList;
    string input;//list of words to build tree
    string UpdateWord;
    string ThreeLetters;
    string yorn;

    cout<<"Enter word list"<<endl;
    getline(cin, input);
	stringstream ss(input);
	string word;
    while (ss >> word) {
		buildList.push_back(word);
	}
    y.BuildTree(buildList);

    cout<<"tree built"<<endl;
    
    y.PrintTrie();

    while (true){
        cout<<"Enter word to update list or q to quit updating:"<<endl;
        cin>>UpdateWord;
        if(UpdateWord =="q" | UpdateWord =="Q"){
            break;
        }
        y.AddWord(UpdateWord);
    }
    //print updated list
    y.PrintTrie();

    while (true){
        cout<<"Enter first 3 letters or enter q to quit"<<endl;
        int n_count=0;
        cin>>ThreeLetters;
        if(ThreeLetters=="q" | ThreeLetters=="Q"){
            break;
        }
        if(ThreeLetters.size()==3){
            trie_list= y.AutoComplete(ThreeLetters);
            sort(trie_list.begin(), trie_list.end(), revsort);
            int list_size=trie_list.size();

            int i=0;
            while (i < min(list_size, 5)){
                cout<<"is "<<trie_list[i].second<<" your word? (y or n)"<<endl;
                cin>>yorn;
                if(yorn=="y"|yorn=="Y"){
                    y.AddWord(trie_list[i].second);
                    break;
                }
                else if(yorn=="n"|yorn=="N"){
                
                    n_count++;
                    i++;
                }
                else{
                    cout<<"input error"<<endl;
                }

            }
            if(n_count==5 | i==list_size){
            cout<<"no more suggestions"<<endl;
            cout<<"please enter full word"<<endl;
            cin>>ThreeLetters;
            y.AddWord(ThreeLetters);
            cout<<"word added"<<endl;
            }
            
        }
    }
    y.PrintTrie();
    
    return 0;
}