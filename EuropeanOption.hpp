//EuropeanOption.cpp
//
//Purpose: European option class, to initialize european option instances, with appropriate getter and setter functions for data parameters, functionalities pertaining to printing these informations
//         efficiently. Put-call parity functions to check for parity, as well as computing the difference between exact prices and the price had there been parity. There are also calling functions
//         for pricing these call and puts, their sensitivities with Black-Scholes or divided differences.
//
//Modification dates: 12/30/2022 - 1/25/2023


#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp

#include "BSExactPricingEngine.hpp"
#include "DividedDifferences.hpp"
#include "OptionData.hpp"           // Header file for struct holding option data, for encapsulation
#include <cmath>                    // For pow() function
#include <cstdlib>                  // For rand() function
#include <string>
#include <vector>
#include <iostream>
#include <sstream>



class EuropeanOption
{
    private:
        OptionData option_data;

    public:
    //CONSTRUCTORS AND DESTRUCTOR (canonical header file principles)

        EuropeanOption();                                               // Default constructor
        EuropeanOption(const double& newS, const double& newK, const double& newT, const double& newR, const double& newSig, const Option_Type& new_optiontype, const Exercise_Type& new_exercise); // Overloaded constructor with provided option parameters
        EuropeanOption(const EuropeanOption& source);                   // Copy constructor
        ~EuropeanOption();                                              // Destructor
        EuropeanOption& operator = (const EuropeanOption& source);      // Assignment operator

    // MEMBER FUNCTIONS:

        void Init();                                // Rather than tediously list initialize values, we create an Init() function to facilitate default initialization
        void Copy(const EuropeanOption& source);    // Rather than tediously implement copying option data members, we centralize this effort with one function doing so. It makes code cleaner.   
            
        std::string print_OptionType() const;       // Print whether it is a call or put
        std::string print_ExerciseType() const;     // Print whether it is a spot option or a future
        std::string ToString() const;               // Printing out all information on the option at hand 

        void toggle_optiontype();                   //  Toggle function to switch option types: call or put
        void toggle_exercisetype();                 //  Toggle exercise types: spot option or future, taking into consideration the changes in value for B.

        void set_OptionType(const Option_Type& source_optiontype);
        void set_ExerciseType(const Exercise_Type& source_exercisetype);

        double PutCallParity() const;       // If the option is a call, it will return the price of the put option when satisfying put-call parity conditions. And vice-versa.
        double Parity_Difference();         // Calculates the difference between the put call parity prices, and the exact price.
        std::string Parity_checker();       // Checks for parity for a European option 

        std::vector<double> vector_data() const;   // Vector to store data members efficiently, and be abe to pass them as arguments in functions rather than give individual data members

    //GETTERS
        double const& getS() const;         // Getter function for asset's price
        double const& getK() const;         // Getter function for strike price of asset at hand
        double const& getT() const;         // Getter function for expiry date of option for asset at hand
        double const& getR() const;         // Getter function for interest rate
        double const& getSig() const;       // Getter function for volatility of asset at hand
        double const& getB() const;         // Getter function for cost of carry
        int const& getID() const;           // Getter ID function      

        //SETTERS:

        void setS(const double& newS);       // Setter function for underlying price of asset at hand
        void setK(const double& newK);       // Setter function for strike price of asset at hand
        void setT(const double& newT);       // Setter function for expiry date of option for asset at hand
        void setR(const double& newR);       // Setter function for interest rate
        void setSig(const double& newSig);   // Setter function for volatility of asset at hand
        //void setAll(const double& ... );   // After careful thought, I believe it does not make sense to have such a function. It would be better to simply create a new instance if deemed appropriate.


        // OPTION SENSITIVITIES/ GREEKS with exact formula BS:

        double Price_BS() const;             //Black-Scholes pricing function which will call appropriate functions in BSExactPricingEngine as a function of whether instance is a call or put 
        double Delta_BS() const;             //Black-Scholes delta function which will call appropriate functions in BSExactPricingEngine as a function of whether instance is a call or put 
        double Gamma_BS() const;             //Black-Scholes gamma function which will call appropriate function in BSExactPricingEngine  
        double Theta_BS() const;             //Black-Scholes theta function which will call appropriate functions in BSExactPricingEngine as a function of whether instance is a call or put 
        double Vega_BS() const;              //Black-Scholes vega function which will call appropriate function in BSExactPricingEngine  

        std::string Four_Greeks_BS() const;     // Outputting the values of the four greeks we are interested in one go.
         

        //Call and Gamma : divided differences 
        double Delta_DividedDiff(const double& h) const; // Delta divided differences function which will call appropriate functions in DividedDifferences class as a function of whether instance is call or put
        double Gamma_DividedDiff(const double& h) const; // Gamma divided differences function which will call appropriate function in DividedDifferences class
};

std::ostream& operator << (std::ostream &os, const EuropeanOption& source); // << operator overloading 

#endif //EuropeanOption_hpp
