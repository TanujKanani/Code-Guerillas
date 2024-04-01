#include<iostream>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

void putDelim(vector<string>& prop)
{
    ifstream read("Faulty.txt");
    ofstream write("newfile.txt");
    char ch;
    int count = 0;
    int flag = 0;
    while(read.get(ch))
    {
        if(isalpha(ch)) // Check if character is alphabetic
        {
            if(flag == 0)
            {
                write << prop[count];
                count++;
                flag = 1;
            }
            else if(flag == 1)
                continue;
        }
        else if(isblank(ch) || ispunct(ch) || isspace(ch)) // Check if character is a space, punctuation, or whitespace
        {
            if(flag == 1)
            {
                flag = 0;
                write << ch;
            }
            else
                write << ch;
        }
    }
    read.close();
    write.close();
}