// PricingEngine.hpp
//
//Purpose: Base class for other pricing engines: BSExactPricingEngine, DividedDifferences, etc.
//
//Modification dates: 12/30/2022 - 1/25/2023

// The design pattern was inspired by Mark Joshi's "C++ Design Patterns and Derivatives Pricing"
// as well as D.Duffy's article "Monte Carlo Methods in Quantitative Finance Generic and Efficient MC Solver in C++"


#ifndef PricingEngine_hpp
#define PricingEngine_hpp

class PricingEngine
{
private:
    //N/A

public: 
    PricingEngine();                            // Default constructor
    PricingEngine(const PricingEngine& source); // Copy constructor
    ~PricingEngine();                           // Destructor
    PricingEngine& operator = (const PricingEngine& source);    //Assignment operator

};

#endif //PricingEngine_hpp
