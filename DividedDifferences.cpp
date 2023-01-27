// DividedDifferences.cpp
//
// Purpose: Black-Scholes pricing engine for the computing of: exact prices for calls and puts, and computing of greeks: delta, gamma, vega, theta. 
//
// Modification date: 1/15/2023


#include "DividedDifferences.hpp"   // DividedDifferences header file
#include <cmath>

// Default constructor
DividedDifferences::DividedDifferences():PricingEngine()         //Including PricingEngine base class part  
{
    //std::cout << "Default constructor in DivididedDifferences used." << std::endl;
}

// Destructor
DividedDifferences::~DividedDifferences()          
{
    //std::cout << "Destructor in DividedDifferences used." << std::endl;
}

//Approximate/ divided differences:



// CALL - DELTAS

//Call delta computation using divided differences, and taking as arguments S,K,T,R,Sig,B, and parameter h.
double DividedDifferences::Delta_Call_DividedDiff(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B, const double& h)  
{
    // B = R when facing a stock option model. However, B=0 when it is a futures option model. 

    // DELTA_DIVIDEDDIFF =  ( V(S+h) - V(S-h) ) / 2h            
  
    return (BSExactPricingEngine::Call_Price_BS(S+h, K,T,R,Sig,B)   // V(S+h)
    - BSExactPricingEngine::Call_Price_BS(S-h,K,T,R,Sig,B))         // - V(S-h)
    / (2.0*h);                                                      // / 2h 
}


//Taking vector of parameters as argument
//While the user could input a vector of size 7 parameters, he/she would consciously need to say that the last parameter is parameter h for divided differences
double DividedDifferences::Delta_Call_DividedDiff(const std::vector<double>& source_params, const Param_Type& source_type)
{
    if(source_params.size() != 7 || source_type != Param_Type::h){throw std::invalid_argument("Error: Vector of wrong size or of wrong param type to compute divided differences.");}
    
    // DELTA_DIVIDEDDIFF =  ( V(S+h) - V(S-h) ) / 2h
    //Vector of parameter data goes as such:
    //source_params[0]  = S variable
    //source_params[1]  = K variable
    //source_params[2]  = T variable
    //source_params[3]  = R variable
    //source_params[4]  = Sig variable
    //source_params[5]  = B variable
    //source_params[6] = h parameter for divided differences

    return (BSExactPricingEngine::Call_Price_BS(source_params[0] + source_params[6],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5]) // V(S+h)
    - BSExactPricingEngine::Call_Price_BS(source_params[0] - source_params[6],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5]))      // - V(S-h)
    / (2.0*source_params[6]);                                                                                                                                             // /2h
}




// PUT - DELTAS


//Put delta computation using divided differences, and taking as arguments S,K,T,R,Sig,B, and parameter h.
double DividedDifferences::Delta_Put_DividedDiff(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B, const double& h)  
{   
    // B = R when facing a stock option model. However, B=0 when it is a futures option model. 

    // DELTA_DIVIDEDDIFF =  ( V(S+h) - V(S-h) ) / 2h

    return (BSExactPricingEngine::Put_Price_BS(S+h,K,T,R,Sig,B) // V(S+h)
    - BSExactPricingEngine::Put_Price_BS(S-h,K,T,R,Sig,B))      // - V(S-h)
    / (2.0*h);                                                  // /2h
}


//Taking vector of parameters as argument,  as well as parameter h
double DividedDifferences::Delta_Put_DividedDiff(const std::vector<double>& source_params, const Param_Type& source_type)  
{   
    if(source_params.size() != 7 || source_type != Param_Type::h){throw std::invalid_argument("Error: Vector of wrong size or of wrong param type to compute divided differences.");}
    // DELTA_DIVIDEDDIFF =  ( V(S+h) - V(S-h) ) / 2h

    //Vector of parameter data goes as such:
    //source_params[0]  = S variable
    //source_params[1]  = K variable
    //source_params[2]  = T variable
    //source_params[3]  = R variable
    //source_params[4]  = Sig variable
    //source_params[5]  = B variable
    //source_params[6] =  h parameter for divided differences

    return (BSExactPricingEngine::Put_Price_BS(source_params[0] + source_params[6],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5])   // V(S+h)
    - BSExactPricingEngine::Put_Price_BS(source_params[0] - source_params[6],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5]))        // - V(S-h)
    / (2.0*source_params[6]);                                                                                                                                              // /2h
}



// GAMMAS

//Gamma computation using divided differences, and taking as arguments S,K,T,R,Sig,B,and parameter h.
double DividedDifferences::Gamma_DividedDiff(const double& S, const double& K, const double& T, const double& R, const double& Sig, const double& B, const double& h) 
{
    //GAMMA_DIVIDEDDIFF = ( V(S+h) - 2V(S) + V(S-h)) / ( h^2 )
    //It is the same for calls and puts
    
    return (BSExactPricingEngine::Call_Price_BS(S+h,K,T,R,Sig,B)   // V(S+h)
    - 2.0*BSExactPricingEngine::Call_Price_BS(S,K,T,R,Sig,B)       // - 2V(S)
    +BSExactPricingEngine::Call_Price_BS(S-h,K,T,R,Sig,B) )        // + V(S-h)
    / pow(h,2.0);                                                  // / ( h^2 )     
}


//Taking vector of parameters as argument,  as well as parameter h
double DividedDifferences::Gamma_DividedDiff(const std::vector<double>& source_params, const Param_Type& source_type) 
{
    if(source_params.size() != 7 || source_type != Param_Type::h){throw std::invalid_argument("Error: Vector of wrong size or of wrong param type to compute divided differences.");}
    //GAMMA_DIVIDEDDIFF = ( V(S+h) - 2V(S) + V(S-h)) / ( h^2 )
    //It is the same for calls and puts
    
    //Vector of parameter data goes as such:
    //source_params[0]  = S variable
    //source_params[1]  = K variable
    //source_params[2]  = T variable
    //source_params[3]  = R variable
    //source_params[4]  = Sig variable
    //source_params[5]  = B variable
    //source_params[6] = h parameter for divided differences

    return (BSExactPricingEngine::Call_Price_BS(source_params[0] + source_params[6],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5])   // V(S+h)
    - 2.0*BSExactPricingEngine::Call_Price_BS(source_params[0],source_params[1],source_params[2],source_params[3],source_params[4],source_params[5])                        //- 2V(S)
    +BSExactPricingEngine::Call_Price_BS(source_params[0] - source_params[6], source_params[1],source_params[2],source_params[3],source_params[4],source_params[5]) )        //+ V(S-h)
    / pow(source_params[6], 2.0);                                                                                                                                            // / ( h^2 )     
}



