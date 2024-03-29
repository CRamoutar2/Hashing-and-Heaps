// Chethram Ramoutar
// spell_check.cc: A simple spell checker.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "double_hashing.h"
using namespace std;

// You can add more functions here.

// Creates and fills double hashing hash table with all words from
// dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file) {
  HashTableDouble<string> dictionary_hash;
  dictionary_hash.MakeEmpty(); //create empty hash table
  string dict_insert;

  ifstream dict_file;
  dict_file.open(dictionary_file); //stream the file into a variable
  while(getline(dict_file, dict_insert)){ //grab words from the file included and inserts into the hash table
    dictionary_hash.Insert(dict_insert);
  }
  return dictionary_hash; //returns the hash table
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary,
		  const string &document_file) {

      ifstream doc_file;
      doc_file.open(document_file);
      string doc_check;
      vector<string> word_container;
      string word_ = "";
      while(getline(doc_file, doc_check)){
        transform(doc_check.begin(),doc_check.end(), doc_check.begin(), ::tolower); //changes every character in the string to lower case

        
        //end above's for, unable to complete
          if(dictionary.Contains(doc_check)){
            cout << "Correct" << "\n";
          }
          else{
            cout << "Incorrect" << "\n";
          }
    }
}

// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);
  
  return 0;
}
