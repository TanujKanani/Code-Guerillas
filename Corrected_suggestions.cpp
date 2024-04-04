#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

vector<string>* getSuggestions(const string& word) 
{ 
    vector<string>* suggestions = new vector<string>();
    unordered_set<string> seenSuggestions; 

    // Generate suggestions by changing each character 
    for (int i = 0; i < word.length(); ++i) 
    {
        for (char c = 'a'; c <= 'z'; c++) 
        { 
            string modifiedWord = word; 
            modifiedWord[i] = c;
            if (dictionary.search(modifiedWord) && (seenSuggestions.find(modifiedWord) == seenSuggestions.end())) 
            {
                suggestions->push_back(modifiedWord);
                seenSuggestions.insert(modifiedWord);
            } 
        }
    }

    // Generate suggestions by inserting each character 
    for (int i = 0; i <= word.length(); ++i) 
    {
        for (char c = 'a'; c <= 'z'; c++) 
        { 
            string modifiedWord = word; 
            modifiedWord.insert(i, 1, c);
            if (dictionary.search(modifiedWord) && (seenSuggestions.find(modifiedWord) == seenSuggestions.end())) 
            {
                suggestions->push_back(modifiedWord);
                seenSuggestions.insert(modifiedWord);
            }
        } 
    }

    // Generate suggestions by deleting each character 
    for (int i = 0; i < word.length(); ++i) 
    {
        string modifiedWord = word; 
        modifiedWord.erase(i, 1);
        if(dictionary.search(modifiedWord) && (seenSuggestions.find(modifiedWord) == seenSuggestions.end())) 
        {
            suggestions->push_back(modifiedWord);
            seenSuggestions.insert(modifiedWord);
        }
    }

    // Generate suggestions by swapping adjacent characters
    for (int i = 0; i < word.length()-1; i++) 
    {
        string modifiedWord = word;
        swap(modifiedWord[i], modifiedWord[i + 1]); 
        if(dictionary.search(modifiedWord) && (seenSuggestions.find(modifiedWord) == seenSuggestions.end())) 
        {
            suggestions->push_back(modifiedWord);
            seenSuggestions.insert(modifiedWord);
        }
    }

    // Words with prefixes as suggestions
    {
        vector<string> prefixSuggestions = dictionary.getWordsWithPrefix(word);
        for(int p= 0; p < prefixSuggestions.size() ; p++)
        {
            if ((seenSuggestions.find(prefixSuggestions[p]) == seenSuggestions.end())) {
                suggestions->push_back(prefixSuggestions[p]);
                seenSuggestions.insert(prefixSuggestions[p]);
            }
        }
    }
    return suggestions;
}
