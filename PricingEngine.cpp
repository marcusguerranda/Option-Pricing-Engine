// The design pattern was inspired by Mark Joshi's "C++ Design Patterns and Derivatives Pricing"
// as well as D.Duffy's article "Monte Carlo Methods in Quantitative Finance Generic and Efficient MC Solver in C++"

#ifndef PricingEngine_cpp
#define PricingEngine_cpp

#include "PricingEngine.hpp"

PricingEngine::PricingEngine()
{
    //std::cout << "Default constructor in 'PricingEngine' used." << std::endl;
}

PricingEngine::PricingEngine(const PricingEngine& source)
{
    //std::cout << "Copy constructor in 'PricingEngine' used." << std::endl;
}

PricingEngine& PricingEngine::operator = (const PricingEngine& source)
{
    if (this == &source)
    {
        return *this;
    }
    else
    {
        return *this;
    }
}

PricingEngine::~PricingEngine()
{
    //std::cout << "Destructor in 'PricingEngine' used." << std::endl;
}


#endif //PricingEngine_cpp