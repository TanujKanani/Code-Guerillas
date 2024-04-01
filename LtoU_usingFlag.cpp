                    //THIS CODE HAS THE NECESSARY CHANGES FOR UPPER CASE LETTERS
//ALSO,MAIN FUNCTION SHOULD BE CHANGED ACCORDING TO THESE FUNCTIONS.
#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
using namespace std;

vector<pair<string,int> > split_words(string& data)
{
    vector<pair<string,int> > toBeChecked;
    char* token, *delim = " .?!:;/\n\t,";
    token = strtok(&data[0], delim);
    // Split the words
    while (token != nullptr)
    {   
        int cflag = 0;
        if(token[0]>='A' && token[0]<='Z'){
            cflag =1;
        }
            char word = token[0];
        // Convert each word ,from file to be corrected, to lower case
        for (int i = 0; i < strlen(token); ++i)
        {
            word = tolower(token[i]);
            token[i] = word;
        }
        toBeChecked.push_back(make_pair(string(token),cflag));
        token = strtok(nullptr, delim);
    }
    token = nullptr;
    delim = nullptr;
    return toBeChecked;
}

void correctedVectorString(vector<pair<string,int> > & prop)
{
    for(int i = 0 ; i < prop.size() ; i++)
    {
        if(!dictionary.search(prop[i].first))
        {
            vector<string> dummy = getSuggestions(prop[i].first);
            int choice = INT_MIN;
            cout << "Your choices for incorrect word : " << prop[i].first << " give index :" <<endl;
            for(int j =0 ; j<dummy.size() ; j++)
            {
                cout << j << " " << dummy[j] << endl;
            }
            cin >> choice;
            prop[i].first = dummy[choice];
            if(prop[i].second == 1){
                prop[i].first[0] = toupper(prop[i].first[0]);
            }
        }
        else if(dictionary.search(prop[i].first))
        {
            if(prop[i].second == 1){
                prop[i].first[0] = toupper(prop[i].first[0]);
            }
        }
        continue;
    }
}
