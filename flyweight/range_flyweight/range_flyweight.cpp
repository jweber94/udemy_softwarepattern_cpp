#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

/*
// This is a very memory inefficient way of implementing text with the possability to format it via methods
class FormatedText {
	std::string _plainText;
	bool* _caps;

public:
	FormatedText(const std::string& plainText) :
		_plainText(plainText)
	{
		_caps = new bool[_plainText.length()];
		memset(_caps, 0, _plainText.length());
	}

	~FormatedText() {
		delete _caps;
	}

	void capitalize(int start, int end) {
		for (int i = start; i <= end; i++) {
			_caps[i] = true;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const FormatedText& obj) {
		std::string resultStr;
		char tmpElem;
		for (int i = 0; i < obj._plainText.length(); i++) {
			tmpElem = obj._plainText[i];
			obj._caps[i] ? resultStr += std::toupper(tmpElem) : resultStr += tmpElem;
		}
		return os << resultStr;
	}
};
*/

class FlyweightFormatedText {
	
	// nested class or struct for defining the formating of ranges
	struct TextRange { // in this example, the TextRange is the flyweight, since it stores all information how to format the text without allocate for every text property a boolean mask with the length of the complete text
		int _start;
		int _end;

		bool _capitalize;
		// bool _italic, _bold, ...;
		
		bool covers(int position) const {
			return (position >= _start) && (position <= _end);
		}
	};


	std::string _plainText;
	std::vector<TextRange> _formating; // this approach also scales better then the fixed array approach if we add something to the string after the creation of the text object

public:
	TextRange& getRange(int start, int end) { // We return the range object so that we are able to set its properties
		// TODO: If we have more then one property that can be set, we need to check if a range is already added to the vector (or map in this case would probably be better)
		_formating.emplace_back(TextRange{start, end}); // emplace because we want to be efficient and need to create the copy operation. push_back will always invoke the copy operation while emplace_back will do this inline
		return *_formating.rbegin(); // last element within the vector with the possibility of iterating from back to front via c++ iterators
	}

	FlyweightFormatedText(const std::string& plainText) :
		_plainText(plainText)
	{}

	friend std::ostream& operator<<(std::ostream& os, const FlyweightFormatedText& obj) {
		std::string result;
		char tmpElem;
		for (int i = 0; i < obj._plainText.length(); i++) {
			tmpElem = obj._plainText[i];
			for (const auto& rng : obj._formating) {
				if (rng.covers(i) && rng._capitalize) {
					tmpElem = std::toupper(tmpElem);
				}
				result += tmpElem;
			}
		}
		return os << result;
	}
};


int main()
{
	/*
	FormatedText ft{"This is a brave new world"};
	ft.capitalize(10, 15);
	std::cout << ft << std::endl;
	*/

	FlyweightFormatedText fft{ "this is a brave new world" };
	fft.getRange(10, 15)._capitalize = true;
	std::cout << fft << std::endl;
	return 0;
}