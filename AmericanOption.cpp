//AmericanOption.cpp
//
//Purpose: Defining American option instances, with appropriate data members, and pricing functionalities.
//
//Modification date: 1/20/2023


#include "AmericanOption.hpp"   //Include AmericanOption header file where functions and constructors are defined
#include <iostream>             //Iostream library 
#include <cmath>                //Cmath library for math functions such as pow(x,y) and sqrt()


//Default constructor
AmericanOption::AmericanOption()
{
    Init(); //Initialize with default values pre-determined
    //std::cout << "Default constructor in 'AmericanOption" used." << std::endl;
}

//Overloaded constructor
AmericanOption::AmericanOption(const double& newS, const double& newK, const double& newR, const double& newSig, const double& newB, const Option_Type& new_optiontype, const Exercise_Type& new_exercise)
{
    Init(); //Set random values, most particularly of interest for the ID, that is generated randomly.
            //There are no setID() functions, because I do not believe it makes sense to have such function. It is a better structure to initialize first with random values, and then 
            //use setter functions to set appropriate values for individual data members as well as the option type (call or put)
    setS(newS); // Use setter function to set value of underlying asset price
    setK(newK); // Use setter function to set value of strike price
    setR(newR); // Use setter function to set value of inteerest rate
    setSig(newSig); // Use setter function to set value of constant volatility parameter
    setB(newB);     // Use setter function to set value of cost-of-carry parameter
    set_OptionType(new_optiontype); // Use setter function to set value of option type: call or put
    set_ExerciseType(new_exercise); // Use setter functio to set value of exercise type: american or european

    //std::cout << "Overloaded constructor used." << std::cout
}

//Copy constructor
AmericanOption::AmericanOption(const AmericanOption& source)  
{
    AmericanOption();   //Initialize a default instance, and then copy elements from provided source instance
    AmericanOption::Copy(source);
    //std::cout << "Overloaded constructor in 'AmericanOption" used." << std::endl;
}

//Assignment operator
AmericanOption& AmericanOption::operator = (const AmericanOption& source)  
{
    if (this == &source)                // Checking whether source is the same/ self-assignment
    {
        return *this;
    }
    else                    
    {
        AmericanOption::Copy(source);   // Copying data from source, if instance is different from that of instance at hand
        return *this;
    }
}


AmericanOption::~AmericanOption()
{
    //std::cout << "Destructor used in AmericanOption." << std::endl;
}



//MEMBER FUNCTIONS

void AmericanOption::Init()
{//Note: list initialization is only for cosntructors.
    option_data.m_id = rand();  // Initialize random id value
    option_data.m_S = 110.0;    // Set S with value provided in Group B exercise 
    option_data.m_K = 100.0;    // Set K with value provided in Group B exercise
    option_data.m_R = 0.1;      // Set R with value provided in Group B exercise
    option_data.m_Sig = 0.1;    // Set Sig with value provided in Group B exercise
    option_data.m_B = 0.02;     // Set B withvalue provided in Group B exercise 
    option_data.optiontype = Option_Type::Call; // Set option type as call as default
    option_data.exercisetype = Exercise_Type::Spot;     // Set exercise type as spot as default

    //std::cout << "Init function in AmericanOption being used." << std::endl;
}


void AmericanOption::Copy(const AmericanOption& source)
{
    //option_data.m_id = source.option_data.m_id; 
    option_data.m_S = source.option_data.m_S;   // Copy element S from option_data struct from source 
    option_data.m_K = source.option_data.m_K;   // Copy element K from option_data struct from source 
    option_data.m_R = source.option_data.m_R;   // Copy element R from option_data struct from source 
    option_data.m_Sig = source.option_data.m_Sig; // Copy element Sig from option_data struct from source 
    option_data.m_B = source.option_data.m_B;   // Copy element B from option_data struct from source 
    option_data.optiontype = source.option_data.optiontype; // Copy option type from option_data struct from source 
    option_data.exercisetype = source.option_data.exercisetype; // Copy exercise type from option_data struct from source 
    //std::cout << "Copy function in AmericanOption being used." << std::endl;  
}

//GETTERS

double const& AmericanOption::getS() const        // Getter function for asset's price
{
    return option_data.m_S;
}

double const& AmericanOption::getK() const        // Getter function for strike price of asset at hand
{
    return option_data.m_K;
}

double const& AmericanOption::getR() const          // Getter function for interest rate
{
    return option_data.m_R;
}

double const& AmericanOption::getSig() const        // Getter function for volatility of asset at hand
{
    return option_data.m_Sig;
}

double const& AmericanOption::getB() const           //Getter function for cost of carry
{
    return option_data.m_B;
}

int const& AmericanOption::getID() const            //Getter function to get ID of option instance at hand
{
    return option_data.m_id;
}


std::string AmericanOption::print_OptionType() const    //Getter function to print out the type of option at hand: call or put
{
    switch(option_data.optiontype)
    {
        case Option_Type::Call: //If 'Call'
            return "CALL";
            break;
        case Option_Type::Put: //If 'Put'
            return "PUT";
            break;
        default:
            throw std::invalid_argument("Error: Incorrect option type provided.");          
    }
}

std::string AmericanOption::print_ExerciseType() const //Getter function to print out the exercise type: spot or future
{
    switch(option_data.exercisetype)
    {
        case Exercise_Type::Spot:   //If 'Spot
            return "SPOT";
            break;
        case Exercise_Type::Future: //If 'Future'
            return "FUTURE";
            break;
        default:
            throw std::invalid_argument("Error: Incorrect exercise type provided.");          
    }
}


std::string AmericanOption::ToString() const    //ToString() function to print out information on American option instance at hand
{
    std::stringstream ss;
    ss << "Type: " << print_OptionType() << " " << print_ExerciseType() << "; S: " << getS() <<  "; K:" << getK() << "; R: " << getR() << "; Sig: " << getSig() << "; B: " << getB()<< "; ID: " << getID() << "\n";
    return ss.str();
}


std::ostream& operator << (std::ostream &os, const AmericanOption& source)  // << operator overloading, which calls ToString() function
{
    os << source.ToString() << "\n";
    return os;
}


std::vector<double> AmericanOption::vector_data() const //Function to get vector of data by storing in parameter data: S,K,R,Sig,B
{
    std::vector<double> tmp; 
    tmp.push_back(getS());
    tmp.push_back(getK());
    tmp.push_back(getR());
    tmp.push_back(getSig());
    tmp.push_back(getB());

    return tmp;
}



//SETTERS

void AmericanOption::setS(const double& newS)   //Setter function to asset price
{
    option_data.m_S = newS;
}

void AmericanOption::setK(const double& newK) //Setter function for strike price
{
    option_data.m_K = newK;
}

void AmericanOption::setR(const double& newR) //Setter function for interes rate
{
    option_data.m_R = newR;
}

void AmericanOption::setSig(const double& newSig) //Setter function for constant volatility parameter
{
    option_data.m_Sig = newSig;
}

void AmericanOption::setB(const double& newB)  //Setter function for cost of carry
{
    option_data.m_B = newB;
}
    

//Toggle() function to change type between call, put, and future.
void AmericanOption::toggle_optiontype()    //Option which enables to toggle between option types: if call, then toggle to put, and vice versa
{
    switch(option_data.optiontype)
    {
        case Option_Type::Call:
            option_data.optiontype = Option_Type::Put;
            break;
        case Option_Type::Put:
            option_data.optiontype = Option_Type::Call;
            break;
        default:
            throw std::invalid_argument("Error: Incorrect option type provided.");  
            break;
    }
}

//Toggle exercise types: spot option or future, taking into consideration the changes in value for B.
void AmericanOption::toggle_exercisetype() //Option which enables to toggle between exercise types: if spot, then toggle to future, and vice versa
{
    switch(option_data.exercisetype)
    {
        case (Exercise_Type::Spot):
            option_data.exercisetype = Exercise_Type::Future;
            option_data.m_B = 0.0;              // Indeed, if we have a future option, B = 0 in the Black-Scholes model
            break;
        case (Exercise_Type::Future):
            option_data.exercisetype = Exercise_Type::Spot;
            option_data.m_B = option_data.m_R;  //If we have a have spot option now, B = R in the Black-Scholes model
            break;
        default:
            throw std::invalid_argument("Error: Incorrect exercise type provided."); 
            break;
    }
}

void AmericanOption::set_OptionType(const Option_Type& source_optiontype)
{
    option_data.optiontype = source_optiontype;     // Setter function to set option type (call or put)
}

void AmericanOption::set_ExerciseType(const Exercise_Type& source_exercisetype)
{
    option_data.exercisetype = source_exercisetype; // Setter function to set exercise type (spot or future)
}

// OPTION SENSITIVITIES/ GREEKS
// Virtual Greek functions, which were declared as pure virtual member functions in abstract base class "Option"
            
double AmericanOption::Price_American_Perp() const
{
    //Calling of appropriate perpetual American exact option formulae, when determining whether is it is a call or put
    if(option_data.optiontype == Option_Type::Call) //If Call
    {   
        return AmericanOption::Price_Call_American_Perp(option_data.m_S, option_data.m_K,option_data.m_R, option_data.m_Sig, option_data.m_B);
    }
    else    //If Put
    {
        return AmericanOption::Price_Put_American_Perp(option_data.m_S, option_data.m_K,option_data.m_R, option_data.m_Sig, option_data.m_B);
    }
}

//Formula for pricing perpetual american call option. I would have created a new pricing engine just for american options, but deemed it 
//unnecessary for the purpose of this exercise, given it only required only defining two functions
double AmericanOption::Price_Call_American_Perp(const double&S, const double&K, const double&R, const double&Sig, const double&B) const
{
    // Formula for exact price for perpetual american call option, taking (S,K,R,Sig,B) as arguments
    double y1 = (1.0/2.0) - (B/(pow(Sig, 2.0))) + sqrt( pow((B/(pow(Sig, 2.0)) - (1.0/2.0)), 2.0) + (2.0*R)/(pow(Sig,2.0))) ;
    double C = (K/(y1-1))* pow((((y1-1)/y1)* (S/K)), y1);
    return C;
}	

double AmericanOption::Price_Call_American_Perp(std::vector<double>& source_params) 
{
    //Vector of parameter data goes as such:
    //source_params[0]  = S variable
    //source_params[1]  = K variable
    //source_params[2]  = R variable
    //source_params[3]  = Sig variable
    //source_params[4]  = B variable

    // Formula for exact price for perpetual american option taking as argument a vector of parameter data
    double y1 = (1.0/2.0) - (source_params[4]/(pow(source_params[3], 2.0))) + sqrt( pow((source_params[4]/(pow(source_params[3], 2.0)) - (1.0/2.0)), 2.0) + (2.0*source_params[2])/(pow(source_params[3],2.0))) ;
    double C = (source_params[1]/(y1-1))* pow((((y1-1)/y1)* (source_params[0]/source_params[1])), y1);
    return C;
}



double AmericanOption::Price_Put_American_Perp(const double&S, const double&K, const double&R, const double&Sig, const double&B ) const	
{
    // Formula for exact price for perpetual american put option, taking (S,K,R,Sig,B) as arguments
    double y2 = (1.0/2.0) - (B/(pow(Sig, 2.0))) - sqrt( pow((B/(pow(Sig, 2.0)) - (1.0/2.0)), 2.0) + (2.0*R)/(pow(Sig,2.0))) ;
    double P = (K/(1-y2))* pow((((y2-1)/y2)* (S/K)), y2);
    return P;
}

double AmericanOption::Price_Put_American_Perp(std::vector<double>& source_params) 
{
    //Vector of parameter data goes as such:
    //source_params[0]  = S variable
    //source_params[1]  = K variable
    //source_params[2]  = R variable
    //source_params[3]  = Sig variable
    //source_params[4]  = B variable

    // Formula for exact price for perpetual american option taking as argument a vector of parameter data
    double y2 = (1.0/2.0) - (source_params[4]/(pow(source_params[3], 2.0))) - sqrt(pow((source_params[4]/(pow(source_params[3], 2.0)) - (1.0/2.0)), 2.0) + (2.0*source_params[2])/(pow(source_params[3],2.0)));
    double P = (source_params[1]/(1-y2))* pow((((y2-1)/y2)* (source_params[0]/source_params[1])), y2);
    return P;
}


