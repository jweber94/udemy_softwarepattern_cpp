#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Neuron;

// CRTP = Curiosly recurring template pattern
template <typename Derived>
struct SomeNeurons {
	template<typename T>
	void connectTo(T& other) {
		// since we use range based for loops, we need our inheriting Derived classes to implement the begin() and end() methods to be able to tread as range based classes
		for (Neuron& from : *static_cast<Derived*>(this)) {
			for (Neuron& to : other) {
				from.outConnections.push_back(&to);
				to.inConnections.push_back(&from);
			}
		}
	}
};


struct Neuron : public SomeNeurons<Neuron>
{
	std::vector<Neuron*> inConnections;
	std::vector<Neuron*> outConnections;
	unsigned int id;

	Neuron() {
		static unsigned int neuronCounter{ 0 };
		id = neuronCounter;
		neuronCounter++;
	}

	/*
	// not needed because we inherit it from the CRTP base class SomeNeurons<Neuron>
	void connectTo(Neuron& other) {
		outConnections.push_back(&other);
		other.inConnections.push_back(this);
	}
	*/

	// make the scalar element to act as a range based element
	Neuron* begin() {
		return this;
	}
	Neuron* end() {
		return this + 1; // address + 1 (address): The address of the end method is not part of the range based element itself
	}

	// enabling print with std::cout of self written class
	friend std::ostream& operator<<(std::ostream& os, const Neuron& neuron) {
		os << "Incoming Connections:" << std::endl;
		for (auto connIn : neuron.inConnections) {
			os << connIn->id << "\t-->\t[" << neuron.id << "]" << std::endl;
		}
		os << "Outgoing Connections" << std::endl;
		for (auto connOut : neuron.outConnections) {
			os << "[" << neuron.id << "]\t-->\t" << connOut->id << std::endl;
		}
		return os;
	}
};

struct NeuronLayer : public std::vector<Neuron>, public SomeNeurons<NeuronLayer> // CAUTION: std::vector does not have a virtual destructor which can lead to memory leaks in real world scenarios
{
	// Because NeuronLayer inherits from std::vector<T>, NeuronLayer itself is a range based element
	NeuronLayer(unsigned int numNeurons) {
		while (numNeurons --> 0) { // arrow operator: numNeurons gets decremented on each loop cycle and the logical (calculation) expression evaluates to true if numNeurons is greater or equal to zero
			emplace_back(Neuron{}); // creation of a new neuron via default constructor and putting it into the vector from which we inherited
		}
	}

	// enabling print with std::cout of self written class
	friend std::ostream& operator<<(std::ostream& os, const NeuronLayer& NL) {
		for (auto& neuron : NL) {
			os << neuron; // recursively call the << operator
		}
		return os;
	}
};

int main()
{
	Neuron n1, n2;
	n1.connectTo(n2);
	std::cout << n1 << n2;

	NeuronLayer nlayer1{ 2 };
	NeuronLayer nlayer2{ 3 };

	n1.connectTo(nlayer1);
	nlayer1.connectTo(n2);
	nlayer1.connectTo(nlayer2);

	std::cout << nlayer2 << std::endl;

	return 0;
}