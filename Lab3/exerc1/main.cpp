/*******************************
 * Lab 3: uppgift 1             *
 * Frequency table of words     *
 *******************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility> 
#include <fstream>
#include <cassert>
#include <algorithm>

 /*******************************
  * 1. Declarations              *
  ********************************/
//pair för varjr element
using pair = std::pair< std::string, int>;

// A function to test the tables created by the program
void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
    const std::string& file_name, int n);

// Så alla blir lowercase
void lowerCase(std::string& word) {
    //transform + lower finns redan n8ce
    std::transform(word.begin(), word.end(), word.begin(), tolower);
}

bool isPunc(const char& c) {
    // Ta bort alla dessa
    std::string chars = ".,!?:();\"";
    
    // std::string::npos indikerar inge match dvs blir true om den hittar
    return chars.find(c) != std::string::npos;
}

void removeChar(std::string& word) {
    // Remove chars from string,
    //kallar funk  is punc flr varje chaar i våran string
    word.erase(remove_if(word.begin(), word.end(), isPunc), word.end());

}

// Sort by frequency
bool sortBy(const pair& t1, const pair& t2) {
    // Om dde  har samma mängd så ville vi ha bokstavsordning
    if (t1.second == t2.second)
    {
        // sort alphabetically by word
        return(t1.first < t2.first);
    }
    return (t1.second > t2.second);
}
/*******************************
 * 2. Main function             *
 *******************************/

int main() {
    std::string name;
    std::cout << "Text file: ";
    std::cin >> name;

    std::ifstream in_File{"/Users/annagranberg/Desktop/TNG033/Labbar/Lab3/Lab3/exerc1/" + name };

    if (!in_File) {
        std::cout << "Could not open input file!!\n";
        return 0;
    }

    //sakpaar våran map
    std::map<std::string, int> table;
    int counter{ 0 };  // räkna orden
    
    std::string inWord;
    // denna forsäter när den hittar nya ord i filen
    while (in_File >> inWord)
    {

        // Ta bort speciall karaktärer
        removeChar(inWord);
        // minibokstäver
        lowerCase(inWord);

        //ökar våran int i map för vårat inWord
        //om det är samma ord kommer in_word vara lika men sätter inte in enn ny utan ökar enbart int
        table[inWord]++;

        //antal ord tot
        ++counter;
    }

    //gör en vektor med för att kolla freq för varje elemennt i map
    //vaaaarför tho? för aida skrev de kan man inte bara sorta map på dirre
    std::vector<pair> freq;

    // kopiera table to freq, back_inserter sätter in längst bak i freq
    std::copy(table.begin(), table.end(), std::back_inserter(freq));
    
    // Sort freq by frequency
    std::sort(freq.begin(), freq.end(), sortBy);

    /* ************** Testing **************** */
    test(table, freq, name, counter);
}


/*******************************
 * 2. Test implementation      *
 * Do not modify               *
 *******************************/

void test(const std::map<std::string, int>& t, const std::vector<pair>& v,
    const std::string& file_name, int n) {

    std::ifstream file{"/Users/annagranberg/Desktop/TNG033/Labbar/Lab3/Lab3/exerc1/out_" + file_name };

    // Test if stream is in good state
    assert(bool(file) == true);

    std::map<std::string, int> result1;
    std::string word;
    int counter{ 0 };
    int total{ 0 };

    // load expected frequency table sorted alphabetically
    while (file >> word >> counter && counter > 0) {
        result1[word] = counter;
        total += counter;
    }
    
//    std::cout << t.size() << "\n";
//    std::cout << result1.size() << "\n";
//    std::cout << n << "\n";
//    std::cout << total << "\n";
    
    assert(total == n);
    assert(t == result1);

    std::vector<pair> result2;

    // load expected frequency table sorted by frequence
    while (file >> word >> counter) {
        result2.push_back(std::pair{ word, counter });
    }

    assert(v == result2);

    std::cout << "\nPassed all tests successfully!!\n";
}
