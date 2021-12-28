/*****************************************
 * Lab 3: exercise 2                      *
 * Anagrams table                         *
 ******************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <set>
#include <iterator>
#include <iomanip>

//instead of vector use set, then we dont need to remove duplicates
using Table = std::map<std::string, std::vector<std::string>>;

// Define a testing function to check the contents of the anagrams table
void testing(const Table& T, const std::string& file_name);

struct insert_table{
    //Constructor
    insert_table(Table& t) : T(t){
    }
    
    void operator()(const std::string& word){
        std::string key{word};
        std::sort(key.begin(), key.end());
        
        auto it = std::find(T[key].begin(), T[key].end(), word);

        //this wouldnt be needed if we used set instead of vector
        if(it == T[key].end()){
            T[key].push_back(word);
        };
        std::sort(T[key].begin(), T[key].end());
    };
    
private:
    Table& T;
};

struct print{
    void operator()(const std::pair<const std::string, const std::vector<std::string>>& T){
        if(T.second.size() >= 2) {
            std::for_each(T.second.begin(), T.second.end(), [](const std::string &w){
                std::cout << w << " ";
            });
            std::cout << " --> " << T.second.size() << "\n";
        };
    };
};

/*******************************
 *     Main function          *
 *******************************/

int main() {
   
    // Skriva in och läsa filen
    std::string name;
    std::cout << "Text file: ";
    std::cin >> name;

    std::ifstream in_File{"/Users/annagranberg/Desktop/TNG033/Labbar/Lab3/Lab3/exerc2/" + name };
    
    if (!in_File) {
        std::cout << "Could not open input file!!\n";
        return 0;
    }
    /* ************** Lägga in ord + sortera **************** */
    std::vector<std::string> words_key;
    
    //Läser in varje ord i filen samt kopierar till words_key
    std::copy(std::istream_iterator<std::string>{in_File}, std::istream_iterator<std::string>{}, inserter(words_key, words_key.end()));

    //std::unique(std::remove_if(words_key.begin(), words_key.end())); //denna kan vi ej använda
    //Sorterar varje Char i bokstavsordning //naje de knasar då
    
    //Skapa Table
    Table anagram;
    //Constructor för att inistalisera så vi kan använda operator()
    insert_table newtable(anagram);
    
    //Lägger in våra key + ord
    std::for_each(words_key.begin(), words_key.end(), newtable);
    
    std::cout << "Number of words = " << words_key.size() << "\n\n" << "-- ANAGRAMS --\n";
    
    //skickar in vaarje element/pair i print()
    std::for_each(anagram.begin(), anagram.end(), print());

    //testaa jäkeln
    testing(anagram, name);
}

void testing(const Table& T, const std::string& file_name){
    std::ifstream file{"/Users/annagranberg/Desktop/TNG033/Labbar/Lab3/Lab3/exerc2/out_" + file_name };
    
    //Test om filen är nice
    assert(bool(file) == true);
    
    Table result1;
    //insert_table newmtf(result1);
    std::string out_anagram;
    //std::vector<std::string> totwords;
    
    while (file >> out_anagram) {
        std::string temp = out_anagram;
        
        // Sortera alfsabetiskt så vi får en "key"
        std::sort(std::begin(temp), std::end(temp));
        //totwords.push_back(out_anagram);

        //lägg ej yill om ordet redan finns i vektorn
        auto it = std::find(result1[temp].begin(), result1[temp].end(), out_anagram);

        if(it == result1[temp].end()){
            result1[temp].push_back(out_anagram);
        };
        
        //sortera vektorn i ordning så de ej blir nå knas
        std::sort(result1[temp].begin(), result1[temp].end());
    }
    
//    for (auto& i:result1){
//        std::cout << i.first << "-->";
//        for(std::string s : i.second){
//            std::cout << s << " ";
//        }
//        std::cout << "\n";
//    }
    
    assert(T == result1);
    //assert(n == totwords.size());
    
    std::cout << "\nU made it, jul nu!!\n\n";
}
