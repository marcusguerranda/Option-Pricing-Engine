//AmericanOption.hpp
//
//Purpose: Defining American option instances, with appropriate data members, and pricing functionalities.
//
//Modification date: 1/20/2023

    
#ifndef AmericanOption_hpp			// Header guards to prevent multiple definitions of same class
#define AmericanOption_hpp
    
#include "BSExactPricingEngine.hpp"	// BSExactPricingEngine 
#include "OptionData.hpp"   		// Header file for struct holding option data, for encapsulation
#include <vector>					// Vector library
#include <sstream>					// For os stream/ << operator overloading
#include <cmath>    				// For pow() function
#include <cstdlib>  				// For rand() function
#include <iostream>	
#include <string>	


class AmericanOption
{
    private:
        OptionData option_data;	// Private struct holding data members for American options (S,K,R,Sig,B)

    public:
    //CONSTRUCTORS AND DESTRUCTOR (canonical header file principles)

        AmericanOption();                                               // Default constructor
        AmericanOption(const double& newS, const double& newK, const double& newR, const double& newSig, const double& newB,const Option_Type& new_optiontype, const Exercise_Type& new_exercise); // Overloaded constructor with provided option parameters
        AmericanOption(const AmericanOption& source);                   // Copy constructor
        ~AmericanOption();                                              // Destructor
        AmericanOption& operator = (const AmericanOption& source);      // Assignment operator

    // MEMBER FUNCTIONS:

        void Init();                                // Rather than tediously list initialize values, we create an Init() function to facilitate default initialization
        void Copy(const AmericanOption& source);    // Rather than tediously implement copying option data members, we centralize this effort with one function doing so. It makes code cleaner.   
            
        std::string print_OptionType() const;       // Print whether it is a call or put
        std::string print_ExerciseType() const;     // Print whether it is a spot option or a future
        std::string ToString() const;               // Printing out all information on the option at hand 

        void toggle_optiontype();                   //  Toggle function to switch option types: call or put
        void toggle_exercisetype();                 //  Toggle exercise types: spot option or future, taking into consideration the changes in value for B.

        void set_OptionType(const Option_Type& source_optiontype);			// Setter function for option type: call or put
        void set_ExerciseType(const Exercise_Type& source_exercisetype);	// Setter function for exercise type: spot or future

        std::vector<double> vector_data() const;    // Vector to store data members efficiently, and be abe to pass them as arguments in functions rather than give individual data members

    //GETTERS
        double const& getS() const;         // Getter function for asset's price
        double const& getK() const;         // Getter function for strike price of asset at hand
        double const& getR() const;         // Getter function for interest rate
        double const& getSig() const;       // Getter function for volatility of asset at hand
        double const& getB() const;         // Getter function for cost of carry
        int const& getID() const;           // Getter ID function      

    //SETTERS:

        void setS(const double& newS);       // Setter function for underlying price of asset at hand
        void setK(const double& newK);       // Setter function for strike price of asset at hand
        void setR(const double& newR);       // Setter function for interest rate
        void setSig(const double& newSig);   // Setter function for volatility of asset at hand
		void setB(const double& newB);		 //Setter function for cost of carry at hand
        //void setAll(const double& ... );   // After careful thought, I believe it does not make sense to have such a function. It would be better to simply create a new instance if deemed appropriate.


    // Exact formula for a perpetual american option


		// Formulae for pricing perpetual american call and put options. I would have created a new pricing engine just for american options, but deemed it 
		// unnecessary for the purpose of this exercise, given it only required only defining two functions
        double Price_American_Perp() const;	  // General pricing function to call, which will call either Price_Call_American_Perp() or Price_Put_American_Perp as a function of the option type. Had I
		// created header and source files for the Pricing of perpetual american options, Price_American_Perp() would have remained in this class, and Price_Call_American_Perp() and Price_Put_American_Perp()
		// would have been called into that PricingEngine file.


		// Call exact pricing formulae for American option
		double Price_Call_American_Perp(const double&S, const double&K, const double&R, const double&Sig, const double&B ) const;	//Taking S,K,R,Sig,B as arguments
		static double Price_Call_American_Perp(std::vector<double>& source_params);	// Taking vector as argument. Static in order to be able to call function before having an instance being created

		// Put exact pricing formulae for American option
		double Price_Put_American_Perp(const double&S, const double&K, const double&R, const double&Sig, const double&B ) const;	//Taking S,K,R,Sig,B as arguments
		static double Price_Put_American_Perp(std::vector<double>& source_params);	// Taking vector as argument. Static in order to be able to call function before having an instance being created
};

std::ostream& operator << (std::ostream &os, const AmericanOption& source);

#endif //AmericanOption_hpp


