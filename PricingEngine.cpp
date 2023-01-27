// PricingEngine.hpp
//
// Purpose: Base class for other pricing engines: BSExactPricingEngine, DividedDifferences, etc.
//
// Modification dates: 12/30/2022 - 1/25/2023

// The design pattern was inspired by Mark Joshi's "C++ Design Patterns and Derivatives Pricing"
// as well as D.Duffy's article "Monte Carlo Methods in Quantitative Finance Generic and Efficient MC Solver in C++"

#ifndef PricingEngine_cpp
#define PricingEngine_cpp

#include "PricingEngine.hpp"

//Default constructor
PricingEngine::PricingEngine()
{
    //std::cout << "Default constructor in 'PricingEngine' used." << std::endl;
}

//Copy constructor
PricingEngine::PricingEngine(const PricingEngine& source)
{
    //std::cout << "Copy constructor in 'PricingEngine' used." << std::endl;
}

//Assignment operator
PricingEngine& PricingEngine::operator = (const PricingEngine& source)
{
    if (this == &source)    //Checking for self-assignment
    {
        return *this;
    }
    else
    {
        return *this;
    }
}

//Destructor
PricingEngine::~PricingEngine()
{
    //std::cout << "Destructor in 'PricingEngine' used." << std::endl;
}


#endif //PricingEngine_cpp
