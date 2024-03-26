#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
using namespace std;

string read_file(const string& filename)
{
    ifstream read(filename);
    
    if(!read.fail())
    {
        string data;
        read.seekg(0,read.end);
        data.resize(read.tellg());
        read.seekg(0,read.beg);
        read.read(&data[0], data.size());
        read.close();
        return data;
    }
    else return string("");
}

vector<string> split_words(string& data)
{
    vector<string> toBeChecked;
    char* token, *delim = " .?!:;/\n\t,";
    token = strtok(&data[0], delim);
    // Split the words
    while (token != nullptr)
    {
        // Convert each word ,from file to be corrected, to lower case
        for (int i = 0; i < strlen(token); ++i)
        {
            char word = tolower(token[i]);
            token[i] = word;
        }
        toBeChecked.push_back(token);
        token = strtok(nullptr, delim);
    }
    token = nullptr;
    delim = nullptr;
    return toBeChecked;
}
