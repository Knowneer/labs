#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <map>
#include <string>

void addWord(std::map<std::string, std::string>& dict);
void translateWord(const std::map<std::string, std::string>& dict);
void removeWord(std::map<std::string, std::string>& dict);
void showDictionary(const std::map<std::string, std::string>& dict);
bool containsWord(const std::map<std::string, std::string>& dict, const std::string& word);

#endif // DICTIONARY_HPP
