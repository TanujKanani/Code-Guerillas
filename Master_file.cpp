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

vector<string>* getSuggestions(const string& word) 
{ 
    vector<string>* suggestions = new vector<string>();

    // Generate suggestions by changing each character 
     for (int i = 0; i < word.length(); ++i) 
    {
        for (char c = 'a'; c <= 'z'; c++) 
        { 
            string modified = word; 
            modified[i] = c;
            if (dictionary.search(modified)) 
            {
                suggestions->push_back(modified); // Return immediately if suggestion found
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
                suggestions->push_back(modified); // Return immediately if suggestion found 
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
            suggestions->push_back(modified); // Return immediately if suggestion found 
        }
    }

    // Generate suggestions by swapping adjacent characters
    for (int i = 0; i < word.length()-1; i++) 
    {
        string modified = word;
        swap(modified[i], modified[i + 1]); 
        if(dictionary.search(modified)) 
        {
            suggestions->push_back(modified); // Return immediately if suggestion found 
        }
    }

    // Words with prefixes as prop[i]
    {
        vector<string> prefix = dictionary.getWordsWithPrefix(word);
        for(int p= 0; p < prefix.size() ; p++)
        {
            suggestions->push_back(prefix[p]);
        }
    }
    return suggestions;
}

void correctedVectorString(vector<pair<string,int> >& prop)
{
    for(int i = 0 ; i < prop.size() ; i++)
    {
        if(!dictionary.search(prop[i].first))
        {
            vector<string>* suggestions = getSuggestions(prop[i].first); // Dynamically allocate memory for suggestions
            if(suggestions->empty()){
                cout<<"No suggestions found,the word "<< prop[i].first << " might be a name,so it stays as it is."<<endl;   //for some words that might not be in the dictionary.
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
void putDelim(vector<pair<string,int> >& prop)
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
                write << prop[count].first;
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

int main()
{
	buildDict();
	string fileToBeChecked = "Faulty.txt";
    string intermediary = read_file(fileToBeChecked);
    vector<pair<string,int> > tokenisedFile = split_words(intermediary);
    correctedVectorString(tokenisedFile);
    putDelim(tokenisedFile);
	return 0;
}
