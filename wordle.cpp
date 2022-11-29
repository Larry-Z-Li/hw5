// For debugging
#include <iostream>
// For std::remove
#include <map>
#include <set>
#include <vector>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    int empty = 0;
    vector<int> emptyspaces;
    string floatingtemp = floating;
    string intemp = in;
    string::iterator stritr = floatingtemp.begin();
    set<int> inlist;
    
    //First for-loop to gauge empty spaces and merge strings
    for(int i = 0; i < intemp.size(); i++)
    {
        if(intemp[i] == '-')
        {
            if(stritr == floatingtemp.end())
            {
                empty++;
                emptyspaces.push_back(i);
            }
            else
            {
                intemp[i] = *stritr;
                stritr++;
            }
        }
        else
        {
            inlist.insert(i);
        }
    }
    
    if(stritr != floatingtemp.end())           
    {
        throw out_of_range("Too many floating characters");
    }

    
    set<string> words;
    
    //To fill empty spaces with alphabetical combinations of the original string.
    alphabetcombinations(words, intemp, emptyspaces, empty);
    set<string> permutewords;
    
    //Second for loop
    //To iterate through every string combinations and permute them.
    //This makes every possible string
    for(set<string>::iterator itr = words.begin(); itr != words.end(); ++itr)
    {
        permutations(permutewords, inlist, *itr, 0, itr->size()-1);
    }
    set<string> results;
    
    //Third for loop
    //Dictionary Search
    for(set<string>::iterator itr = permutewords.begin(); itr != permutewords.end(); ++itr)
    {
        if(dict.find(*itr)!=dict.end())
        {
            results.insert(*itr);
        }
    }
    return results;
}


void alphabetcombinations(set<string>& words, string str, vector<int> emptyspaces, int empty)
{
    if(empty == 0)
    {
        words.insert(str);
        return;
    }
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int temp;
    
    //Fourth for loop
    for(int i = 0; i < 26; i++)
    {
        str[emptyspaces[empty-1]] = alphabet[i];
        alphabetcombinations(words, str, emptyspaces, empty-1);
    }
}

//Recursive string permutations finder
void permutations(set<string>& set, ::set<int> inlist, string word, int l, int r)
{
    if(l == r)
    {
        set.insert(word);
        return;
    }
    char tempchar;
    if(inlist.find(l) == inlist.end())                        //only swapping floating elements
    {
        
        //Fifth and last loop
        for(int i = l; i <= r; i++)
        {
            if(inlist.find(i) == inlist.end())                //only swapping floating elements
            {
                tempchar = word[l];
                word[l] = word[i];
                word[i] = tempchar;
                permutations(set, inlist, word, l+1, r);
            }
        }
    }
    else
    {
        permutations(set, inlist, word, l+1, r);
    }
    return;
}