#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "trie.h"
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <ctype.h>
#include <sstream>


using namespace std;


bool revsort(const pair<int,string> &a,  
               const pair<int,string> &b) 
{ 
       return (a.first > b.first); 
} 



int main(){

    cout << "hello" << endl;

    string usrStr;////first 3 letters of a word entered by user
    vector<string> buildList; //list of words to build autocomplete tree
    vector<pair<int, string>> autoCompleteSugg; //auto complete suggestions from autocomplete tree
    char userInput;//y or n
    string usrWord;//full user word, entered in autocomplete fails to suggest proper word
    string input;
    vector<string> suggList;
    Trie x;

    cout<<"Enter word list"<<endl;
    getline(cin, input);
	stringstream ss(input);
	string word;
    while (ss >> word) {
		buildList.push_back(word);
	}
    cout<<"words added"<<endl;

    x.BuildTree(buildList);

    cout<<"tree built"<<endl;

    while (true) {
        
        cout<<"Enter first 3 letters or enter q to quit"<<endl;
        int n_count=0;
        cin>>usrStr;
        if(usrStr=="q"){
            return 0;
        }
        if(usrStr.size()==3){
            autoCompleteSugg = x.AutoComplete(usrStr);
            sort(autoCompleteSugg.begin(), autoCompleteSugg.end(), revsort);
            int list_size=autoCompleteSugg.size();

            int i=0;
            while (i < min(list_size, 5)){
                cout<<"is "<<autoCompleteSugg[i].second<<" your word? (y or n)"<<endl;
                cin>>userInput;
                if(userInput=='y'|userInput=='Y'){
                    x.AddWord(autoCompleteSugg[i].second);
                    break;
                }
                else if(userInput=='n'|userInput=='N'){
                
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
            cin>>usrWord;
            x.AddWord(usrWord);
            cout<<"word added"<<endl;
            }
            
        }
    }   
    return 0;
}