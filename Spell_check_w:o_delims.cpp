#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
using namespace std;

struct Node {
	Node *links[26];
	bool flag = false;
	
    Node() 
    {
        for (int i = 0; i < 26; ++i)
        links[i] = nullptr;
    }

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

	bool search(string word){
		Node *node = root;
		for (int i = 0; i < word.size(); i++) {
			if (!node->containKey(word[i])) {
				return false;
			}
			node = node->get(word[i]);
		}
		return node->isEnd();
	}

	bool startsWith(string prefix){
		Node* node = root;
		for (int i = 0; i < prefix.size(); i++) {
			if (!node->containKey(prefix[i])) {
				return false;
			}
			node = node->get(prefix[i]);
		}
		return true;
	}

	vector<string> getWordsWithPrefix(string prefix) {
        vector<string> result;
        Node* node = root;
        for (char ch : prefix) {
            if (!node->containKey(ch)) {
                return result; // Prefix not found
            }
            node = node->get(ch);
        }
        findAllWords(node, prefix, result);
        return result;
    }

    void findAllWords(Node* node, string prefix, vector<string>& result) {
        if (node->isEnd()) {
            result.push_back(prefix);
        }
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (node->containKey(ch)) {
                findAllWords(node->get(ch), prefix + ch, result);
            }
        }
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

vector<string> getSuggestions(const string& word) 
{ 
    vector<string> suggestions;

    // Generate suggestions by changing each character 
     for (int i = 0; i < word.length(); ++i) 
    {
		for (char c = 'a'; c <= 'z'; c++) 
		{ 
		    string modified = word; 
			modified[i] = c;
            if (dictionary.search(modified)) 
			{
				suggestions.push_back(modified); // Return immediately if suggestion found
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
			suggestions.push_back(modified); // Return immediately if suggestion found 
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
                    suggestions.push_back(modified); // Return immediately if suggestion found 
                }
            }

	
	// Generate suggestions by swapping adjacent characters
	for (int i = 0; i < word.length()-1; i++) 
	{
	string modified = word;
    swap(modified[i],modified[i + 1]); 
	if(dictionary.search(modified)) 
	{
			suggestions.push_back(modified); // Return immediately if suggestion found 
	}
    }

	//words with prefixes as prop[i]
	{
		vector<string> prefix = dictionary.getWordsWithPrefix(word);
		for(int p= 0; p < prefix.size() ; p++)
		{
			suggestions.push_back(prefix[p]);
		}
	}
	return suggestions;
}

void correctedVectorString(vector<string>& prop)
{
    for(int i = 0 ; i < prop.size() ; i++)
    {
        if(!dictionary.search(prop[i]))
        {
            vector<string> dummy = getSuggestions(prop[i]);
            int choice = -1;
            cout << "Your choices for incorrect word : " << prop[i] << " give index :" <<endl;
            for(int j =0 ; j<dummy.size() ; j++)
            {
                cout << j << " " << dummy[j] << endl;
            }
            cin >> choice;
            prop[i] = dummy[choice];
        }
        else if(dictionary.search(prop[i]))
        continue;
    }
}

void newFile(vector<string>& prop)
{
    ofstream output("newfile.txt");
    if(!output.fail())
    {
        for(int i=0 ; i<prop.size() ; i++)
        {
            output << prop[i] << " ";
        }
    }
}
int main()
{
	buildDict();
	string fileToBeChecked = "Faulty.txt";
    string intermediary = read_file(fileToBeChecked);
    vector<string> tokenisedFile = split_words(intermediary);
    correctedVectorString(tokenisedFile);
    newFile(tokenisedFile);
	return 0;
}






