#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
	Node *links[26];
	bool flag = false;


    Node() 
    {
        for (int i = 0; i < 26; ++i)
        links[i] = nullptr;
    }

	//checks if the reference trie is present or not
	bool containKey(char ch) {
		return (links[ch - 'a'] != NULL);
	}
	//creating reference trie
	void put(char ch, Node *node) {
		links[ch - 'a'] = node;
	}
	//to get the next node for traversal
	Node *get(char ch) {
		return links[ch - 'a'];
	}
	//setting flag to true at the end of the word
	void setEnd() {
		flag = true;
	}
	//checking if the word is completed or not
	bool isEnd() {
		return flag;
	}
};
class Trie {
private:
	Node* root;
public:
	Trie() {
		//creating new obejct
		root = new Node();
	}

	void insert(string word) {
		//initializing dummy node pointing to root initially
		Node *node = root;
		for (int i = 0; i < word.size(); i++) {
			if (!node->containKey(word[i])) {
				node->put(word[i], new Node());
			}
			//moves to reference trie
			node = node->get(word[i]);
		}
		node->setEnd();
	}

	bool search(string word) {
		Node *node = root;
		for (int i = 0; i < word.size(); i++) {
			if (!node->containKey(word[i])) {
				return false;
			}
			node = node->get(word[i]);
		}
		return node->isEnd();
	}

	bool startsWith(string prefix) {
		Node* node = root;
		for (int i = 0; i < prefix.size(); i++) {
			if (!node->containKey(prefix[i])) {
				return false;
			}
			node = node->get(prefix[i]);
		}
		return true;
	}
};
Trie dictionary;
void buildDict()
{
	ifstream Dictfile("Dictionary.txt");
	if(Dictfile.fail()) 
	{
      cout << "Error: Unable to open input file." << endl;
	  return;
	}
	string word;
	while(getline(Dictfile,word))
	{
		dictionary.insert(word);
	}
	Dictfile.close();
}

string getSuggestions(const string& word) 
{ 

   {
	
    // Generate suggestions by changing each character 
for (int i = 0; i < word.length(); ++i) 
{
		for (char c = 'a'; c <= 'z'; c++) 
		{ 
		    string modified = word; 
			modified[i] = c;
            if (dictionary.search(modified)) 
			{
				return modified; // Return immediately if suggestion found
			} 
		}
}
}
// Generate suggestions by inserting each character 
for (int i = 0; i <= word.length(); ++i) 
{
for (char c = 'a'; c <= 'z'; c++) 
		{ 
		    string modified = word; 
			modified.insert(i, 1, c);
			if (dictionary.search(modified)) 
			{
			return modified; // Return immediately if suggestion found 
			}
        } 
}

// Generate suggestions by deleting each character 
for (int i = 0; i < word.length(); ++i) 
{
string modified = word; 
modified.erase(i, 1);
if(dictionary.search(modified)) 
{
return modified; // Return immediately if suggestion found 
}
}

	{
		// Generate suggestions by swapping adjacent characters
	
	for (int i = 0; i < word.length() - 1; ++i) 
	{
	string modified = word;
    swap(modified[i],modified[i + 1]); 
	if(dictionary.search(modified)) 
	{
			return modified; // Return immediately if suggestion found 
	}
    }
	}

}

bool isChar(char x)
{
    if(       
                x == ' '||
                x == ','||
                x == '!'||
                x == '-'||
                x == '_'||
                x == '.'||
                x == '?'||
                x == ':'||
                x == ';'
    )   
	return false;

    else 
    return true;

}
bool isWord(string s)
{
    int no = 0;
    for(int i = 0; i < s.size() ; i++)
    {
        if(isChar(s[i]))
        no++;
    }
    return (no>=1 ? true:false);
}
void clean(string& s)
{
    for(int i = 0; i < s.size() ; i++)
    {
            if(!isChar(s[i]))
            {
                string first_halve , sec_halve;
                first_halve = s.substr(0,i);
                sec_halve = s.substr(i+1 , s.size()-i);
                s = first_halve + sec_halve;
            }
    }
   // return s;
}

void toLower(string &s)
{
    for(int i = 0 ; i < s.size() ; i++)
    {
        s[i] = tolower(s[i]);
    }
}

void replaceword(string& line , string wrong , string replacement)
{
    size_t pos = line.find(wrong);
    if(pos != string::npos)
        line.replace(pos, wrong.length() , replacement);
}

void Replace_2_file(const string& filename)
{
    ifstream read(filename);
    string curLine;
    ofstream out("newfile.txt");

    while(getline(read,curLine))
    {
        istringstream pass(curLine);
        do{
                string word;
                pass >> word;
                if(isWord(word))
                {
                    string origin = word;
                    clean(word);
                    toLower(word);
                    if(!dictionary.search(word))
                    {
                            string replacement = getSuggestions(word);
                            replaceword(curLine , origin, replacement);
                    }
                }
        }while(pass);
        out << curLine << endl;
    }
    out.close();
    read.close();
}

int main() 
{
    buildDict();
	Replace_2_file("Faulty.txt");
     return 0;
}