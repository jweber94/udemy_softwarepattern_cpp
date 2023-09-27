#pragma once

#include "PersonBuilder.hpp"
#include "Person.hpp"


class PersonJobBuilder : public PersonBuilderBase{
	typedef PersonJobBuilder Self; // definition only within the scope of this class
private:

public:
	PersonJobBuilder(Person& person) :
		PersonBuilderBase(person) {
	}

	/* the following return types are needed in order to have a fluent API interface */
	Self& income(std::size_t annualIncome) {
		_person.annual_income = annualIncome;
		return *this;
	}

	Self& company(std::string company) {
		_person.company_name = company;
		return *this;
	}

	Self& position(std::string position) {
		_person.position = position;
		return *this;
	}
};