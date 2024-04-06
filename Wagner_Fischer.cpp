#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
using namespace std;

int WF_dist(const string& str1,const string& str2){
    int len1 = str1.length();
    int len2 = str2.length();

    if (len1 > len2){
        return WF_dist(str2,str1); //this is done to reduce unneceddary iterations.
    }

    vector <int> curr_row(len1 + 1);
    for(int i = 0; i <= len1; ++i){
        curr_row[i] = i;
    }

    for (int i = 1; i <= len2; ++i){
        vector<int> prev_row = curr_row;
        curr_row[0] = i;
        for (int j = 1; j <= len1; ++j){
            int ins = prev_row[j] + 1;
            int del = curr_row[j-1] + 1;
            int subst = prev_row[j-1] + (str1[j - 1] != str2[i-1] ? 1 : 0);
            curr_row[j] = min(min(ins, del), subst);
        }
    }
        return curr_row[len1];
}