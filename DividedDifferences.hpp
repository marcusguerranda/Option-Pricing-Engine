// DividedDifferences.hpp
//
// Purpose: Black-Scholes pricing engine for the computing of: exact prices for calls and puts, and computing of greeks: delta, gamma, vega, theta. 
//
// Modification date: 1/15/2023


#ifndef DividedDifferences_hpp
#define DividedDifferences_hpp

#include "PricingEngine.hpp"        // Pricing Engine base class
#include "BSExactPricingEngine.hpp" // Header file containing definitions for Black-Scholes formulae (pricing and greeks/sensitivities)
#include "Mesher.hpp"               // Mesher file contaning functionalities pertaining to the generation of mesh points
#include <vector>
#include <iostream>


class DividedDifferences: public PricingEngine
{
//DIVIDED Differences
public:

    DividedDifferences();           // Default constructor
    virtual ~DividedDifferences();  // Destructor

    //Delta call approximation by divided differences
    static double Delta_Call_DividedDiff(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B, const double& h);  // Takes S,K,T,R,Sig,B as arguments
    static double Delta_Call_DividedDiff(const std::vector<double>& source_params, const Param_Type& source_type);  // Taking vector of parameter data as argument

    //Put call approximation by divided differences
    static double Delta_Put_DividedDiff(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B, const double& h); // Takes S,K,T,R,Sig,B as arguments
    static double Delta_Put_DividedDiff(const std::vector<double>& source_params, const Param_Type& source_type);   // Taking vector of parameter data as argument

    static double Gamma_DividedDiff(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B, const double& h);   // Takes S,K,T,R,Sig,B as arguments
    static double Gamma_DividedDiff(const std::vector<double>& source_params, const Param_Type& source_type);       // Taking vector of parameter data as argument
};
#endif //PricingEngine_hpp
