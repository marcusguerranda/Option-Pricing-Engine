//BSExactPricingEngine.hpp
// The design pattern was inspired by Mark Joshi's "C++ Design Patterns and Derivatives Pricing"
//
//Purpose: Black-Scholes pricing engine for the computing of: exact prices for calls and puts, and computing of greeks: delta, gamma, vega, theta. 
//
//Modification date: 1/15/2023

#ifndef BSExactPricingEngine_hpp
#define BSExactPricingEngine_hpp


#include "PricingEngine.hpp"    //PricingEngine base class
#include <vector>

class BSExactPricingEngine: public PricingEngine
{
private:
		
	static double D1(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B);   // D1 argument needed for the computation of Black Scholes formulae
	static double D2(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B);   // D2 argument needed for the computation of Black Scholes formulae

	static double N(const double& x);            // CDF of normal distribution
	static double n(const double& x);            // PDF of normal distribution

public:

    BSExactPricingEngine();                      // Default constructor
    virtual ~BSExactPricingEngine();             // Destructor

// PRICING & GREEKS/SENSITIVITIES

    // Call exact price using Black-Scholes formula
    static double Call_Price_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B); // Takes S,K,T,R,Sig,B as arguments 
    static double Call_Price_BS(const std::vector<double>& source_params); // Taking a vector of parameter data as argument
    
    //Put exact price using Black-Scholes formula
    static double Put_Price_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B);  // Takes S,K,T,R,Sig,B as arguments 
    static double Put_Price_BS(const std::vector<double>& source_params); // Taking a vector of parameter data as argument

    // Call delta formula using Black-Scholes formula
    static double Call_Delta_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B);  // Takes S,K,T,R,Sig,B as arguments 
    static double Call_Delta_BS(const std::vector<double>& source_params); // Taking a vector of parameter data as argument
    
    // Put delta formula using Black-Scholes formula
    static double Put_Delta_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B);  // Takes S,K,T,R,Sig,B as arguments 
    static double Put_Delta_BS(const std::vector<double>& source_params); // Taking a vector of parameter data as argument

    // Gamma formula for call and put using Black-Scholes formula
    static double Gamma_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B);      // Takes S,K,T,R,Sig,B as arguments 
    static double Gamma_BS(const std::vector<double>& source_params); // Taking a vector of parameter data as argument

    // Vega formula for call and put using Black-Scholes formula
    static double Vega_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B);       // Takes S,K,T,R,Sig,B as arguments 
    static double Vega_BS(const std::vector<double>& source_params); // Taking a vector of parameter data as argument

    // Call theta formula using Black-Scholes formula
    static double Call_Theta_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B);  // Takes S,K,T,R,Sig,B as arguments 
    static double Call_Theta_BS(const std::vector<double>& source_params); // Taking a vector of parameter data as argument

    // Put delta formula using Black-Scholes formula
    static double Put_Theta_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B);   // Takes S,K,T,R,Sig,B as arguments 
    static double Put_Theta_BS(const std::vector<double>& source_params); // Taking a vector of parameter data as argument

    //Add additional Greeks: First-order: rho, lambda, epsilon, 
    //                       Second-order: vanna, charm, vomma, veta, vera, 
    //                       Third-order:  speed, zomma, color, ultima


};

#endif //PricingEngine_hpp