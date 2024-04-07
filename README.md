# Code-Guerillas

Work was done by different members of the group :- 

Tanuj (ID :- 202301474 ) :- 
Implemented a spell checker that would take text from user given file, convert the text into a vector of strings. Each word from this vector would then be checked for spelling mistakes upto 1 letter mistakes. The corrected vector of strings would be then emptied into a newfile , where each word would be separated by a whitespace. Program didn't have provisions for delimeters as well as words in user given file with their first letter capital. This code can be found in the file "Master_file.cpp". 
This commit was initially named "Spell_check_w:o_delims.cpp" , commited on 27th March.
Tanuj also implemented the code for getting words with certain prefix , hence tapping into the "Prefix Trie" property of Tries. Implemented
the function that tokenises the text in user given file in the function "split_words". Also took the job of passing hefty vectors by reference between functions to save space, and prevent unnecessary copying of objects. Tanuj and suryadeep had the idea of making a menu based sysytem for suggestions. Tanuj gave the idea of giving "-1" choice to user , so that the user gets to decide whether to keep incorrect word or not. He replaced integer flags with boolean flags so as to reduce space consumption.


Suryadeep (ID :- 202301463 ) :-
Tried a different approach on Tanuj's work by attempting to account for delimeters in user given file. He tried adding functionality to "getSuggestions" function by taking into account words that end in -ing, -es , -ly ,etc. but failed to do so. In his commit "StillWorkingOnCode.cpp" , he also went for a menu based suggestion system to replace incorrect words, similar to Tanuj's commit. He added a flag to vector of strings, used in functions "split_words" , so as to make the first letter of certain words capital as given in user's file.
To add functionality to "getSuggestions" function, he implemented Wagner_Fischer algorithm to correct words with 2 or more letter mistakes.
This function would be called only if no suggestion is generated using single letter modifications.

Yuva (ID :- 202301426 ) :- 
He gave the function putDelim that'd put delimeters at correct places in the corrected file. He also gave a valuable idea of using unordered_set in getSuggestions function , as our program was giving repeated suggestions. He made the google document submitted in the classroom. Also gave valuable insights on implementing Trie data structure. He provided the sources from where we had to learn various concepts to complete our project.

Dhyey (ID :- 202301253 ) :-
Gave the idea that if the word isn't found in dictionary , then it might be a name, so keep it as it is, in the corrected vector of strings.
He tested the code, and gave us directions as to where to improve.
