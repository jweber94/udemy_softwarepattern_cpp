#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>

enum class OutputFormat {
	markdown,
	html
};

struct ListStrategy { // using the Interface Segregation Principle (ISP)
	virtual void start(std::ostringstream& oss) {}
	virtual void add_list_item(std::ostringstream& oss, const std::string& item) = 0;
	virtual void end(std::ostringstream& oss) {}
};

struct MarkdownListStrategy : public ListStrategy {
	// only override the add_list_item since we do not need the opening and closing tags in markdown
	void add_list_item(std::ostringstream& oss, const std::string& item) override {
		oss << "* " << item << "\n";
	}
};

struct HtmlListStrategy : public ListStrategy {
	void start(std::ostringstream& oss) override {
		oss << "<ul>\n";
	}
	
	void add_list_item(std::ostringstream& oss, const std::string& item) override {
		oss << "    <li>" << item << "</li>\n";
	}

	void end(std::ostringstream& oss) override {
		oss << "</ul>\n";
	}
};

struct TextProcessor {
	TextProcessor() {
		oss = std::ostringstream{ "" };
	}

	// this is the method to change the format (low level processing) during the runtime of the program
	void set_output_format(const OutputFormat& format)
	{
		switch (format) {
		case OutputFormat::markdown:
			strategy = std::make_unique<MarkdownListStrategy>();
			break;
		case OutputFormat::html:
			strategy = std::make_unique<HtmlListStrategy>(); 
			break;
		}
	}

	void apppend_list(const std::vector<std::string>& items) {
		strategy->start(oss);
		for (auto& item : items) {
			strategy->add_list_item(oss, item);
		}
		strategy->end(oss);
	}

	void clear() {
		oss.str("");
		oss.clear();
	}

	std::string str() const {
		return oss.str();
	}

private:
	OutputFormat format;
	std::ostringstream oss;
	std::unique_ptr<ListStrategy> strategy{ nullptr };
};


int main() {
	std::vector<std::string> items{ "foo", "bar", "baz" };
	TextProcessor tp;
	tp.set_output_format(OutputFormat::markdown);
	tp.apppend_list(items);
	std::cout << tp.str() << std::endl;

	tp.clear();
	tp.set_output_format(OutputFormat::html);
	tp.apppend_list(items);
	std::cout << tp.str() << std::endl;
	return 0;
}