#include<iostream>
#include<string>
#include<bits/stdc++.h>
using namespace std;

bool prcd(char a,char b)
{
    char op1 = a;
    char op2 = b;
    if( a == '(')
    return false;

    if( b == '(')
    return false;

    if( b == ')' && a!='(')
    return true;

    if( a == ')')
     exit(1);

    if(a=='*' && b=='+')
    return true;
    else if(a=='/' && b=='+') 
    return true;
     else if(a=='/' && b=='-') 
    return true;
     else if(a=='*' && b=='-') 
    return true;
     else if(a=='^' && b=='+') 
    return true;
     else if(a=='^' && b=='*') 
    return true;
     else if(a=='^' && b=='-') 
    return true;
     else if(a=='^' && b=='/') 
    return true;
     else if(a=='^' && b=='^') 
    return false;
     else if(a=='-' && b=='+') 
    return true;
     else if(a=='+' && b=='-') 
    return true;
     else if(a=='*' && b=='/') 
    return true;
    else if(a=='/' && b=='*') 
    return true;
    else 
    return false;

    if(b == '^')
    return false;
    
}
void conversion(string symb)
{
    stack<char> opstk;
    char pstfix[20]={0};
    int i=0;
    char topsymb;
    for(auto ch: symb)
    {
        if(ch!='+'&&ch!='-'&&ch!='/'&&ch!='*'&&ch!='^'&&ch!='('&&ch!=')')
            {
                pstfix[i]=ch;
                i++;
            }

        else
        {
            while(!opstk.empty() && prcd(opstk.top(),ch))
            {
                topsymb = opstk.top();
                opstk.pop();
                pstfix[i]=topsymb;
                i++;
            }
            if(opstk.empty() || ch != ')')
            {
                opstk.push(ch);
            }
            else
            {
                topsymb = opstk.top();
                opstk.pop();
            }
        }
    }
    
    while(!opstk.empty())
    {
        topsymb = opstk.top();
        opstk.pop();
        pstfix[i]= topsymb;
        i++;
    }

    cout << "Postfix Expression is: " << endl;
    cout << pstfix << endl;
}

int validity(string exp)
{
    string temp(exp);
    int cnt = 0;
    for(auto ch: temp)
    {
        if(ch == '(')
            cnt++;
        else if (ch == ')')
            cnt--;

        if(cnt < 0)
            return 1;
    }

    if(cnt != 0) 
    {return 1;} 
    
    return 0;
}

int main()
{
    cout << "Enter string to be validated :" << endl;
    string exp;
    getline(cin, exp); 
    int res = validity(exp);
    if(res == 0)
        cout<< "Valid " << endl;
    else
        cout<< "Invalid "<< endl;
    if(res == 0)conversion(exp);
    return 0;
}