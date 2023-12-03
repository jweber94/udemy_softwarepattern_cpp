#include <iostream>

// proxy interface
struct Image {
	virtual void draw() = 0;
};

// basic object implementation
struct Bitmap : Image {
	Bitmap(const std::string& filename) {
		std::cout << "Loading bitmap from " << filename << std::endl;
	}

	void draw() override {
		std::cout << "Drawing bitmap" << std::endl;
	}
};

// lazy proxy
struct LazyBitmap : Image {
	LazyBitmap(const std::string& filename) :
		filename(filename) // caching the filename to be able to construct the actual bitmap afterwards
	{
		// no real bitmap construction
	}

	~LazyBitmap() {
		if (bmp) {
			delete bmp;
		}
	}

	void draw() override {
		if (!bmp) {
			bmp = new Bitmap(filename); // initialization of the actual bitmap only on demand
		}
		bmp->draw();
	}

private:
	std::string filename;
	Bitmap* bmp{ nullptr };
};

int main() {
	// normal bitmap use
	Bitmap map{"FooBar.png"};
	map.draw();

	// using the lazy virtual proxy
	LazyBitmap map2{ "FooBar.png" }; // Just one line needs to be changed in order to use the proxy - this is typical for proxys
	map2.draw();

	return 0;
}