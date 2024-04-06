#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
using namespace std;

struct Node {
	Node *letter[26];
	bool flag = false;
	
    Node() 
    {
        for (int i = 0; i < 26; ++i)
        letter[i] = nullptr;
    }

	bool containKey(char ch) {
		return (letter[ch - 'a'] != NULL);
	}
	//creating reference trie
	void put(char ch, Node *node) {
		letter[ch - 'a'] = node;
	}
	//to get the next node for traversal
	Node *get(char ch) {
		return letter[ch - 'a'];
	}
	//setting flag to true at the end of the word
	void setEnd() {
		flag = true;
	}
	//checking if the word is completed or not
	bool isEndofWord() {
		return flag;
	}
};

class Trie {
private:
	Node* root;
public:
	Trie() {
		//constructor for new object
		root = new Node();
	}

	void insertAword(string word) {
		//this tempororay node pointer points to root initially
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

	bool searchAword(string word){
		Node *node = root;
		for (int i = 0; i < word.size(); i++) {
			if (!node->containKey(word[i])) {
				return false;
			}
			node = node->get(word[i]);
		}
		return node->isEndofWord();
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

	vector<string> getsWordsW_Prefix(string prefix) {
        vector<string> result;
        Node* node = root;
        for (char ch : prefix) {
            if (!node->containKey(ch)) {
                return result; // If words with prefix not found
            }
            node = node->get(ch);
        }
        findAllWords(node, prefix, result);
        return result;
    }

    void findAllWords(Node* node, string prefix, vector<string>& result) {
        if (node->isEndofWord()) {
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
		dictionary.insertAword(word);
	}
	Dictfile.close();
}

string read_file(const string& filename)
{
    ifstream read(filename);
    
    if(!read.fail())
    {
        string singleString;
        read.seekg(0,read.end);
        singleString.resize(read.tellg());
        read.seekg(0,read.beg);
        read.read(&singleString[0], singleString.size());
        read.close();
        return singleString;
    }
    else 
    return string("");
}

vector<pair<string,bool> > split_words(string& data)
{
    vector<pair<string,bool> > toBeChecked;
    char* token, *delim = " .?-!:;/\n\t\'\",";
    token = strtok(&data[0], delim);
    // Split the words on the basis of above delimeters
    while (token != nullptr)
    {   
        bool cflag = false;                         // flag used to store the info., whether first letter is capital or not.
        if(token[0]>='A' && token[0]<='Z'){
            cflag = true;
        }
        char word;
        // Convert each word ,from file to be corrected to lower case
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

int WF_dist(const string& str1,const string& str2){
    int len1 = str1.length();
    int len2 = str2.length();

    if (len1 > len2){
        return WF_dist(str2,str1);                      //this is done to reduce unnecessary iterations.
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
            if (dictionary.searchAword(modifiedWord) && (seenSuggestions.find(modifiedWord) == seenSuggestions.end())) 
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
            if (dictionary.searchAword(modifiedWord) && (seenSuggestions.find(modifiedWord) == seenSuggestions.end())) 
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
        if(dictionary.searchAword(modifiedWord) && (seenSuggestions.find(modifiedWord) == seenSuggestions.end())) 
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
        if(dictionary.searchAword(modifiedWord) && (seenSuggestions.find(modifiedWord) == seenSuggestions.end())) 
        {
            suggestions->push_back(modifiedWord);
            seenSuggestions.insert(modifiedWord);
        }
    }

    // Words with prefixes as suggestions
    {
        vector<string> prefixSuggestions = dictionary.getsWordsW_Prefix(word);
        for(int p= 0; p < prefixSuggestions.size() ; p++)
        {
            if ((seenSuggestions.find(prefixSuggestions[p]) == seenSuggestions.end())) {
                suggestions->push_back(prefixSuggestions[p]);
                seenSuggestions.insert(prefixSuggestions[p]);
            }
        }
    }

    if(suggestions->empty()){
        const int max_dist = 2;
        ifstream dictFile("dictionary.txt");
        string dict_word;
        while(getline(dictFile,dict_word)){
            int dist = WF_dist(word,dict_word);
            if(seenSuggestions.find(dict_word) == seenSuggestions.end()){
                if(dist <= max_dist){
                suggestions->push_back(dict_word);
                seenSuggestions.insert(dict_word);
                }
            }   
        }
        dictFile.close();
    }

    return suggestions;
}

void correctedVectorString(vector<pair<string,bool> >& prop)
{
    for(int i = 0 ; i < prop.size() ; i++)
    {
        if(!dictionary.searchAword(prop[i].first))
        {
            vector<string>* suggestions = getSuggestions(prop[i].first); // Dynamically allocate memory for suggestions
            if(suggestions->empty()){
                cout<<"No suggestions found,the word "<< prop[i].first << " isn't in the dictionary,so it stays as it is."<<endl;   //for some words that might not be in the dictionary.
                continue;                                                                                        
            }
            int choice = INT_MIN;
            cout << "Your choices for incorrect word : " << prop[i].first << " give index :" <<endl;
            cout << "-1 Don't change.Keep as it is." << endl;            //I replaced integer flags with boolean flags for vector<pair<string,int> > in the function split_words. This reduces space taken. Also introduced the option of keeping an incorrect word as it is, for the user.
            for(int j = 0 ; j < suggestions->size() ; j++)
            {
                cout << j << " " << (*suggestions)[j] << endl;
            }
            cin >> choice;                          // Update prop[i].first with the chosen suggestion
            if(choice != -1)
            {
                prop[i].first = (*suggestions)[choice];
            }
                // Convert the first character to uppercase if necessary
            if(prop[i].second == 1)
            {
                prop[i].first[0] = toupper(prop[i].first[0]);
            }

            delete suggestions; // Free dynamically allocated memory
        }
        else if(dictionary.searchAword(prop[i].first))
        {
            // Convert the first character to uppercase if necessary
            if(prop[i].second == 1){
                prop[i].first[0] = toupper(prop[i].first[0]);
            }
        }
    }
}
void putDelim(vector<pair<string,bool> >& prop, const string& fname)
{
    ifstream read(fname);
    ofstream write("newfile.txt");
    char ch;
    int count = 0;
    bool flag = false;
    while(read.get(ch))
    {
        if(isalpha(ch)) // Check if character is alphabetic
        {
            if(flag == false)
            {
                write << prop[count].first;
                count++;
                flag = true;
            }
            else if(flag == true)
            continue;
        }
        else if(isblank(ch) || ispunct(ch) || isspace(ch)) // Check if character is a space, punctuation, or whitespace
        {
            if(flag == true)
            {
                flag = false;
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
	string fileToBeChecked;
    cout << "Enter the filename that you wish to check :- " << endl;
    cin >> fileToBeChecked;
    string intermediary = read_file(fileToBeChecked);
    vector<pair<string,bool> > tokenisedFile = split_words(intermediary);
    correctedVectorString(tokenisedFile);
    putDelim(tokenisedFile,fileToBeChecked);
	return 0;
}
