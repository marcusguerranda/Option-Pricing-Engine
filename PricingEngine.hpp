// The design pattern was inspired by Mark Joshi's "C++ Design Patterns and Derivatives Pricing"
// as well as D.Duffy's article "Monte Carlo Methods in Quantitative Finance Generic and Efficient MC Solver in C++"


#ifndef PricingEngine_hpp
#define PricingEngine_hpp

class PricingEngine
{
private:
    //N/A

public:
    PricingEngine();
    PricingEngine(const PricingEngine& source);
    virtual ~PricingEngine();
    PricingEngine& operator = (const PricingEngine& source);

};

#endif //PricingEngine_hpp