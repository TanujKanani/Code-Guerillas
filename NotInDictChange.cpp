#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
using namespace std;

void correctedVectorString(vector<pair<string,int> >& prop)
{
    for(int i = 0 ; i < prop.size() ; i++)
    {
        if(!dictionary.search(prop[i].first))
        {
            vector<string>* suggestions = getSuggestions(prop[i].first); // Dynamically allocate memory for suggestions
            if(suggestions->empty()){    //changes for word not found in dictionary
                cout<<"No suggestions found,the word "<< prop[i].first << " might be a name,so it stays as it is."<<endl;
                continue;
            }
            int choice = INT_MIN;
            cout << "Your choices for incorrect word : " << prop[i].first << " give index :" <<endl;
            for(int j = 0 ; j < suggestions->size() ; j++)
            {
                cout << j << " " << (*suggestions)[j] << endl;
            }
            cin >> choice;

            // Update prop[i].first with the chosen suggestion
            prop[i].first = (*suggestions)[choice];

            // Convert the first character to uppercase if necessary
            if(prop[i].second == 1){
                prop[i].first[0] = toupper(prop[i].first[0]);
            }

            delete suggestions; // Free dynamically allocated memory
        }
        else if(dictionary.search(prop[i].first))
        {
            // Convert the first character to uppercase if necessary
            if(prop[i].second == 1){
                prop[i].first[0] = toupper(prop[i].first[0]);
            }
        }
    }
}
