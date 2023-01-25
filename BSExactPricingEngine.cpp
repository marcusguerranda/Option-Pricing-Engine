//BSExactPricingEngine.cpp
// The design pattern was inspired by Mark Joshi's "C++ Design Patterns and Derivatives Pricing"
//
//Purpose: Black-Scholes pricing engine for the computing of: exact prices for calls and puts, and computing of greeks: delta, gamma, vega, theta. 
//
//Modification date: 1/15/2023

#include "BSExactPricingEngine.hpp"             //Header file for BSExactPricingEngine 
#include <boost/math/distributions/normal.hpp>  //Using normal distribution from Boost library
#include <iostream>
	
using namespace boost::math;                    //Namespace declaration for using boost/math functionalities relevant to this exercise
    
double BSExactPricingEngine::D1(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B) 
{

	double Tmp = Sig * sqrt(T);                             //Temporary double value 
	return (log(S / K) + (B + (Sig*Sig)*0.5) * T) / Tmp;
}

double BSExactPricingEngine::D2(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B) 
{
	double Tmp = Sig * sqrt(T);                             //Temporary double value 
	return (D1(S,K,T,R,Sig,B) - Tmp);
}

double BSExactPricingEngine::N(const double& x) 
{
   	normal_distribution<> myNormal(0, 1);
	return cdf(myNormal, x);
}

double BSExactPricingEngine::n(const double& x) 
{
    normal_distribution<> myNormal(0, 1); // m = 0, sd = 1
	return pdf(myNormal, x);
}



//CONSTRUCTORS AND DESTRUCTOR

//Default constructor
BSExactPricingEngine::BSExactPricingEngine(): PricingEngine()
{
    //std::cout << "Default constructor in BSExactPricingEngine used." << std::endl;
}

//Destructor
BSExactPricingEngine::~BSExactPricingEngine()
{
    //std::cout << "Destructor in 'BSExactPricingEngine' used." << std::endl;
}                                       



//CALL/PUT PRICE
double BSExactPricingEngine::Call_Price_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B) 
{
    return (S * exp((B - R) * T) * N(D1(S,K,T,R,Sig,B))) - (K * exp(-R * T) * N(D2(S,K,T,R,Sig,B)));
}

double BSExactPricingEngine::Call_Price_BS(const std::vector<double>& source_params)  
{
    //Vector of parameter data goes as such:
    //source_params[0]  = S variable
    //source_params[1]  = K variable
    //source_params[2]  = T variable
    //source_params[3]  = R variable
    //source_params[4]  = Sig variable
    //source_params[5]  = B variable

    //Reproducing the following, but referring to appropriate parameters within the vector: return (S * exp((B - R) * T) * N(D1(S,K,T,R,Sig,B))) - (K * exp(-R * T) * N(D2(S,K,T,R,Sig,B)));

    return (source_params[0]* exp((source_params[5]-source_params[3])*source_params[2])                             // S * exp((B - R) * T)
    *N(D1(source_params[0],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5]))   // * N(D1(S,K,T,R,Sig,B)))
    -(source_params[1]*exp(-source_params[3]*source_params[2])                                                      // - (K * exp(-R * T)
    *N(D2(source_params[0],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5]))));// * N(D2(S,K,T,R,Sig,B))
}




double BSExactPricingEngine::Put_Price_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B) 
{
    return ((K * exp(-R * T)) * N(-D2(S,K,T,R,Sig,B))) - S * exp((B - R) * T) * N(-D1(S,K,T,R,Sig,B));
}

double BSExactPricingEngine::Put_Price_BS(const std::vector<double>& source_params)
{
    //Vector of parameter data goes as such:
    //source_params[0]  = S variable
    //source_params[1]  = K variable
    //source_params[2]  = T variable
    //source_params[3]  = R variable
    //source_params[4]  = Sig variable
    //source_params[5]  = B variable
    
    //Reproducing the following, but referring to appropriate parameters within the vector: return ((K * exp(-R * T)) * N(-D2(S,K,T,R,Sig,B))) - S * exp((B - R) * T) * N(-D1(S,K,T,R,Sig,B));
    return ((source_params[1]*exp(-source_params[3]*source_params[2]))                                              // (K * exp(-R * T))
    *N(-D2(source_params[0],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5]))  //  N(-D2(S,K,T,R,Sig,B))
    - source_params[0]* exp((source_params[5]-source_params[3])*source_params[2])                                   // -S * exp((B - R) * T)
    *N(-D1(source_params[0],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5])));   // *N(-D1(S,K,T,R,Sig,B))
    
}


//DELTA
double BSExactPricingEngine::Call_Delta_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B) 
{
    return exp((B - R) * T) * N(D1(S,K,T,R,Sig,B));
}

double BSExactPricingEngine::Call_Delta_BS(const std::vector<double>& source_params)
{
    //Vector of parameter data goes as such:
    //source_params[0]  = S variable
    //source_params[1]  = K variable
    //source_params[2]  = T variable
    //source_params[3]  = R variable
    //source_params[4]  = Sig variable
    //source_params[5]  = B variable

    return (exp((source_params[5]-source_params[3])*source_params[2])                                                   // exp((B - R) * T)
    *N(D1(source_params[0],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5])));     // N(D1(S,K,T,R,Sig,B))

}

double BSExactPricingEngine::Put_Delta_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B) 
{
	return BSExactPricingEngine::Call_Delta_BS(S,K,T,R,Sig,B) - exp((B - R) * T);
}

double BSExactPricingEngine::Put_Delta_BS(const std::vector<double>& source_params)
{
    //Vector of parameter data goes as such:
    //source_params[0]  = S variable
    //source_params[1]  = K variable
    //source_params[2]  = T variable
    //source_params[3]  = R variable
    //source_params[4]  = Sig variable
    //source_params[5]  = B variable

    return (BSExactPricingEngine::Call_Delta_BS(source_params[0],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5])  // Call_Delta_BS(S,K,T,R,Sig,B)
    *exp((source_params[5]-source_params[3])*source_params[2]));                                                                                        // exp((B - R) * T)
}       


//GAMMA
double BSExactPricingEngine::Gamma_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B) 
{
    return n(D1(S,K,T,R,Sig,B))* exp((B - R) * T) / (S * Sig * sqrt(T));
}

double BSExactPricingEngine::Gamma_BS(const std::vector<double>& source_params)
{
    //Vector of parameter data goes as such:
    //source_params[0]  = S variable
    //source_params[1]  = K variable
    //source_params[2]  = T variable
    //source_params[3]  = R variable
    //source_params[4]  = Sig variable
    //source_params[5]  = B variable

    return ( n(D1(source_params[0],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5]))   // n(D1(S,K,T,R,Sig,B))
    * exp((source_params[5]-source_params[3])*source_params[2])                                                             // exp((B - R) * T)
    / (source_params[0]*source_params[4]*sqrt(source_params[2])));                                                          // / (S * Sig * sqrt(T))
}

//VEGA
double BSExactPricingEngine::Vega_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B) 
{
    return S*sqrt(T) * exp((B-R)*T) * n(D1(S,K,T,R,Sig,B));
}

double BSExactPricingEngine::Vega_BS(const std::vector<double>& source_params)
{
    //Vector of parameter data goes as such:
    //source_params[0]  = S variable
    //source_params[1]  = K variable
    //source_params[2]  = T variable
    //source_params[3]  = R variable
    //source_params[4]  = Sig variable
    //source_params[5]  = B variable

    return (source_params[0]*sqrt(source_params[2])                                                                 // S*sqrt(T)
    * exp((source_params[5]-source_params[3])*source_params[2]))                                                    // exp((B - R) * T)
    * n(D1(source_params[0],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5])); // n(D1(S,K,T,R,Sig,B))
}


//THETA
double BSExactPricingEngine::Call_Theta_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B) 
{
    return -1.0*(S*Sig*exp((B- R)*T)) * n(D1(S,K,T,R,Sig,B)) / (2.0* sqrt(T)) - (B - R)*S*exp((B-R)*T)*N(D1(S,K,T,R,Sig,B)) - R*K*exp(-R*T)*N(D2(S,K,T,R,Sig,B));
}

double BSExactPricingEngine::Call_Theta_BS(const std::vector<double>& source_params)
{
    //Vector of parameter data goes as such:
    //source_params[0]  = S variable
    //source_params[1]  = K variable
    //source_params[2]  = T variable
    //source_params[3]  = R variable
    //source_params[4]  = Sig variable
    //source_params[5]  = B variable

    return -1.0*(source_params[0]*source_params[4]*exp((source_params[5]-source_params[3])*source_params[2]))               // -1.0*(S*Sig*exp((B- R)*T))
    * n(D1(source_params[0],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5]))          // *n(D1(S,K,T,R,Sig,B))
    /(2.0* sqrt(source_params[2]))                                                                                          // /(2.0* sqrt(T))
    -(source_params[5] - source_params[3])*source_params[0]*exp((source_params[5] - source_params[3])*source_params[2])*N(D1(source_params[0],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5]))
    -source_params[3]*source_params[1]*exp(-source_params[3]*source_params[2])                                              // -R*K*exp(-R*T)
    *N(D2(source_params[0],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5]));          // *N(D2(S,K,T,R,Sig,B))

}


double BSExactPricingEngine::Put_Theta_BS(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B) 
{
    return Call_Theta_BS(S,K,T,R,Sig,B) + R*K*exp(-R*T) + S*exp((B - R)*T)*(B - R);
}

double BSExactPricingEngine::Put_Theta_BS(const std::vector<double>& source_params)
{
    //Vector of parameter data goes as such:
    //source_params[0]  = S variable
    //source_params[1]  = K variable
    //source_params[2]  = T variable
    //source_params[3]  = R variable
    //source_params[4]  = Sig variable
    //source_params[5]  = B variable

    return BSExactPricingEngine::Call_Theta_BS(source_params[0],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5]) // Call_Theta_BS(S,K,T,R,Sig,B)
    + source_params[3]*source_params[1]*exp(-source_params[3]*source_params[2])                                                                      // + R*K*exp(-R*T)
    + source_params[0]*exp((source_params[5]-source_params[3])*source_params[2])*(source_params[5]*source_params[3]);                                // S*exp((B - R)*T)*(B - R)
}

