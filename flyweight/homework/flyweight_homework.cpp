#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <optional>

using namespace std;

struct Sentence
{
    // range flyweight implementation
    struct WordToken
    {
        WordToken(unsigned int start, unsigned int end, bool caps) : // needed for the unit test on udemy
            capitalize(caps),
            startIdx(start),
            endIdx(end)
        {}

        unsigned int startIdx;
        unsigned int endIdx;
        bool capitalize;
        // other properties for the word token
    
        // methods
        bool covers(unsigned int idx) {
            return ((idx >= startIdx) && (idx <= endIdx)) ? true : false;
        }
    };

    // members
    std::string m_plainText;
    std::vector<WordToken> m_words;
    unsigned int m_numWords;

    Sentence(const string& text) :
        m_plainText(text)
    {
        // read through the given text and create word tokens from them
        std::istringstream iss(m_plainText);
        std::string word;
        unsigned int tmpStartIdx;
        while (iss >> word) {
            tmpStartIdx = m_plainText.find(word);
            if (std::string::npos != tmpStartIdx) { // check if the word is found within the string - validity check
                m_words.emplace_back(tmpStartIdx, (tmpStartIdx + (word.length() - 1)), false); // emplace_back in order to create the object on the fly
            }
        }
        m_numWords = m_words.size();
    }

    WordToken& operator[](size_t index)
    {
        if (index > m_numWords) {
            std::cerr << "Invalid word index - deliver back the first element." << std::endl;
            return m_words.at(0);
        }
        return m_words.at(index);
    }

    string str() const
    {
        std::string result{};
        bool idxCovered = false;
        for (std::size_t i = 0; i < m_plainText.length(); i++) {
            idxCovered = false;
            for (auto it : m_words) { // this loop will get more complex if we have multiple attributes that are associated with the flyweight
                if (it.covers(i) && it.capitalize) {
                    result += std::toupper(m_plainText[i]);
                    idxCovered = true;
                    break;
                }
                else if (it.covers(i) && !it.capitalize) {
                    result += m_plainText[i];
                    idxCovered = true;
                }
                else {
                    // not convered by the range object
                }
            }
            if (!idxCovered) {
                result += m_plainText[i];
            }
        }
        return result;
    }
};

int main() {
    Sentence sentence("hello world");
    sentence[1].capitalize = true;
    cout << sentence.str() << std::endl; // prints "hello WORLD"
    return 0;
}