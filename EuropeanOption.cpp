//EuropeanOption.cpp
//
//Purpose: European option class, to initialize european option instances, with appropriate getter and setter functions for data parameters, functionalities pertaining to printing these informations
//         efficiently. Put-call parity functions to check for parity, as well as computing the difference between exact prices and the price had there been parity. There are also calling functions
//         for pricing these call and puts, their sensitivities with Black-Scholes or divided differences.
//
//Modification dates: 12/30/2022 - 1/25/2023


#include "EuropeanOption.hpp"


//Default constructor
EuropeanOption::EuropeanOption()
{
    Init(); //Initialize with default values pre-determined
    //std::cout << "Default constructor in 'EuropeanOption" used." << std::endl;
}

//Overloaded constructor
EuropeanOption::EuropeanOption(const double& newS, const double& newK, const double& newT, const double& newR, const double& newSig, const Option_Type& new_optiontype, const Exercise_Type& new_exercise)
{
    Init(); //Set random values, most particularly of interest for the ID, that is generated randomly.
            //There are no setID() functions, because I do not believe it makes sense to have such function. It is a better structure to initialize first with random values, and then 
            //use setter functions to set appropriate values for individual data members as well as the option type (call or put)
    setS(newS);                     // Setter function for asset price
    setK(newK);                     // Setter function for strike price
    setT(newT);                     // Setter function for expiry date
    setR(newR);                     // Setter function for interest rate
    setSig(newSig);                 // Setter function for constant volatility parameter
    set_OptionType(new_optiontype); // Setter function for option type: call or put
    set_ExerciseType(new_exercise); // Setter function for exercise type: spot or future

    if(option_data.exercisetype == Exercise_Type::Spot) // Setting values of B (cost of carry), as a function of whether it is a spot or future option. In Black-Scholes, B=R when spot, and B=0 when future
    {
        option_data.m_B = option_data.m_R;
    }
    else  //option_data.exercisetype == Exercise_Type::Future
    {
        option_data.m_B = 0.0;
    }

    //std::cout << "Overloaded constructor used." << std::cout
}

//Copy constructor
EuropeanOption::EuropeanOption(const EuropeanOption& source)   
{
    EuropeanOption();
    EuropeanOption::Copy(source);
    //std::cout << "Overloaded constructor in 'EuropeanOption" used." << std::endl;
}

//Assignment operator
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& source)  
{
    if (this == &source)    // Checking whether instance at hand is the same as source or not, for self-assigning purposes
    {
        return *this;
    }
    else
    {
        EuropeanOption::Copy(source);
        return *this;
    }
}

//Destructor
EuropeanOption::~EuropeanOption()
{
    //std::cout << "Destructor used in EuropeanOption." << std::endl;
}



//MEMBER FUNCTIONS

//Initialization function
void EuropeanOption::Init()
{//Note: list initialization is only for cosntructors.
    option_data.m_id = rand();  // Assign random id value for instance
    option_data.m_S = 60.0;     // Bacth 1 value provided for asset price
    option_data.m_K = 65.0;     // Bacth 1 value provided for strike price
    option_data.m_T = 0.25;     // Bacth 1 value provided for expiry date 
    option_data.m_R = 0.08;     // Bacth 1 value provided for interest rate
    option_data.m_Sig = 0.30;   // Bacth 1 value provided for constant volatility parameter
    option_data.m_B = option_data.m_R;     // As is the case for a spot option, default exercise type here.
    option_data.optiontype = Option_Type::Call;     // Setting default option type as "call"
    option_data.exercisetype = Exercise_Type::Spot; // Setting default exercise type as "put"

    //std::cout << "Init function in EuropeanOption being used." << std::endl;
}


void EuropeanOption::Copy(const EuropeanOption& source)
{
    option_data.m_S = source.option_data.m_S; // Copy source asset price
    option_data.m_K = source.option_data.m_K; // Copy source strike price
    option_data.m_T = source.option_data.m_T; // Copy source expiry date
    option_data.m_R = source.option_data.m_R; // Copy source interest rate
    option_data.m_Sig = source.option_data.m_Sig; // Copy source constant volatility
    option_data.m_B = source.option_data.m_B;     // Copy source cost of carry
    option_data.optiontype = source.option_data.optiontype;     // Copy source option type: 'call' or 'put'
    option_data.exercisetype = source.option_data.exercisetype; // Copy source exercise type: 'spot' or 'future'
    //std::cout << "Copy function in EuropeanOption being used." << std::endl;
}

//GETTERS

double const& EuropeanOption::getS() const        // Getter function for asset's price
{
    return option_data.m_S;
}

double const& EuropeanOption::getK() const        // Getter function for strike price of asset at hand
{
    return option_data.m_K;
}

double const& EuropeanOption::getT() const         // Getter function for expiry date of option for asset at hand
{
    return option_data.m_T;
}

double const& EuropeanOption::getR() const         // Getter function for interest rate
{
    return option_data.m_R;
}

double const& EuropeanOption::getSig() const       // Getter function for volatility of asset at hand
{
    return option_data.m_Sig;
}

double const& EuropeanOption::getB() const          //Getter function for cost of carry
{
    return option_data.m_B;
}

int const& EuropeanOption::getID() const            //Getter function to get ID of option instance at hand
{
    return option_data.m_id;
}


// Printer function to print option type as a string
std::string EuropeanOption::print_OptionType() const
{
    switch(option_data.optiontype)
    {
        case Option_Type::Call: //If "Call"
            return "CALL";
            break;
        case Option_Type::Put:  //If "Put"
            return "PUT";
            break;
        default:
            throw std::invalid_argument("Error: Incorrect option type provided.");          
    }
}

// Printer function to print exercise type as a string
std::string EuropeanOption::print_ExerciseType() const
{
    switch(option_data.exercisetype)
    {
        case Exercise_Type::Spot:   //If "Spot"
            return "SPOT";
            break;
        case Exercise_Type::Future: //If "Future"
            return "FUTURE";
            break;
        default:
            throw std::invalid_argument("Error: Incorrect exercise type provided.");
    }
}

//ToString function to print out information on European option instance
std::string EuropeanOption::ToString() const
{
    std::stringstream ss;
    ss << "Type: " << print_OptionType() << " " << print_ExerciseType() << "; S: " << getS() << "; T: " << getT() <<  "; K:" << getK() << "; R: " << getR() << "; Sig: " << getSig() << "; B: " << getB()<< "; ID: " << getID() << "\n";
    ss << "Price of option using the Black-Scholes exact pricing formula is: " << Price_BS();
    return ss.str();
}


// << operator overloading to print out european option instance pertaining to parameter data, using ToString() function, andoption sensitivities, using Four_Greeks_BS() function
std::ostream& operator << (std::ostream &os, const EuropeanOption& source)
{
    os << source.ToString() << "\n";
    os << source.Four_Greeks_BS() << "\n";
    return os;
}

//Calculates the opposite's option type put-call parity price
// If the option is a call, it will return the price of the put option when satisfying put-call parity conditions. And vice-versa.
double EuropeanOption::PutCallParity() const   
{
    double B = option_data.m_R; // B = R for spot options. For futures options, the put-call parity is different, and I would extend such a function for futures options by checking for
                                // futures options
    if(option_data.optiontype == Option_Type::Call)
    {
        return (Price_BS() + (option_data.m_K)* exp(-option_data.m_R * option_data.m_T) - (option_data.m_S));
    }
    else  //option_data.optiontype == Option_Type::Put
    {
        return (Price_BS() + (option_data.m_S) - (option_data.m_K)* exp(-option_data.m_R * option_data.m_T));
    }
}

//Checking function to see if there is parity between put and call prices, usng Parity_Difference() function
std::string EuropeanOption::Parity_checker()     
{
    return (Parity_Difference() == 0.0) ? "YES: There is put-call parity." : "NO: There is no put-call parity";
}              

//Funcion which checks whether these is any difference between put and call prices, rounding tolerance error to 1e-8
double EuropeanOption::Parity_Difference() 
{
    // Temporary variable which will store the difference between the opposed option type when in put-call parity, and the exact price defined.
    // For example, if I have a call, I wish to know the difference between the exact price for the put version, and when in put call parity. Such a difference will be given in absolute value terms.
    if (option_data.optiontype == Option_Type::Call)
    {
        double tmp = PutCallParity();                       //Return value for put-call parity.
        toggle_optiontype();                                //Change type 
        return round(abs(tmp - Price_BS()) / 1e-8) * 1e-8;  //Rounding to tolerance error of 1e-8, as suggestd by A.Palley on 12/23/21
    }
    else     
    {
        double tmp = PutCallParity(); 
        toggle_optiontype();   
        return round(abs(tmp - Price_BS()) / 1e-8) * 1e-8;    //Rounding to tolerance error of 1e-8, as suggestd by A.Palley on 12/23/21
    }
}

//Function which gets parameter data and stores into a vector
std::vector<double> EuropeanOption::vector_data() const
{
    std::vector<double> tmp; 
    tmp.push_back(getS());  //Stores underlying asset price S as firt element in vector
    tmp.push_back(getK());  //Stores strike price K as second element in vector
    tmp.push_back(getT());  //Stores expiry time T as third element in vector
    tmp.push_back(getR());  //Stores interest rate R as fourth element in vector
    tmp.push_back(getSig());//Stores constant volatility parameter as fifth element in vector
    tmp.push_back(getB());  //Stores cost of carry parameter as sixth element in vector

    return tmp;
}



//SETTERS

//Setter function for asset price
void EuropeanOption::setS(const double& newS) 
{
    option_data.m_S = newS;
}

//Setter function for strike price 
void EuropeanOption::setK(const double& newK) 
{
    option_data.m_K = newK;
}

//Setter function for expiry time 
void EuropeanOption::setT(const double& newT) 
{
    option_data.m_T = newT;
}

//Setter function for interest rate 
void EuropeanOption::setR(const double& newR) 
{
    option_data.m_R = newR;
}

//Setter function for constant volatility parameter
void EuropeanOption::setSig(const double& newSig) 
{
    option_data.m_Sig = newSig;
}
    

//Toggle() function to change type between call, and put
void EuropeanOption::toggle_optiontype()
{
    switch(option_data.optiontype)
    {
        case Option_Type::Call: //If call, toggle to put option type
            option_data.optiontype = Option_Type::Put;
            break;
        case Option_Type::Put:  //If put, toggle to call option type
            option_data.optiontype = Option_Type::Call;
            break;
        default:
            throw std::invalid_argument("Error: Incorrect option type provided.");
            break;
    }
}

//Toggle exercise types: spot option or future, taking into consideration the changes in value for B.
void EuropeanOption::toggle_exercisetype()
{
    switch(option_data.exercisetype)
    {
        case (Exercise_Type::Spot):  //If spot, toggle to future exercise type and set value of B to 0, as per BS model
            option_data.exercisetype = Exercise_Type::Future;
            option_data.m_B = 0.0;              // Indeed, if we have a future option, B = 0 in the Black-Scholes model
            break;
        case (Exercise_Type::Future): //If future, toggle to spot exercise type and set value of B to R, as per BS model
            option_data.exercisetype = Exercise_Type::Spot;
            option_data.m_B = option_data.m_R;  //If we have a have spot option now, B = R in the Black-Scholes model
            break;
        default:
            throw std::invalid_argument("Error: Incorrect exercise type provided.");
             break;
    }
}

//Option type setter function
void EuropeanOption::set_OptionType(const Option_Type& source_optiontype)
{
    option_data.optiontype = source_optiontype;
}


//Exercise type setter function
void EuropeanOption::set_ExerciseType(const Exercise_Type& source_exercisetype)
{
    option_data.exercisetype = source_exercisetype;

    if(option_data.exercisetype == Exercise_Type::Spot) 
    {
        option_data.m_B = option_data.m_R;
    }
    else // option_data.exercisetype == Exercise_Type::Future
    {
        option_data.m_B = 0.0;
    }
}

// OPTION SENSITIVITIES/ GREEKS


//Function which calls appropriate call and put pricing functions in BSExactPricingEngine as a function of whether the option type is call or put
double EuropeanOption::Price_BS() const
{
    //B = R when facing a stock option model. However, B=0 when it is a futures option model. For the moment, I use an if else and check whether we have a put or call. 

    if(option_data.optiontype == Option_Type::Call) //If call
    {   
        return BSExactPricingEngine::Call_Price_BS(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B);
    }
    else    //If put
    {
        return BSExactPricingEngine::Put_Price_BS(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B);
    }
}


//Function which calls appropriate call and put delta functions in BSExactPricingEngine as a function of whether the option type is call or put
double EuropeanOption::Delta_BS() const
{
    if(option_data.optiontype == Option_Type::Call)
    {   
        return BSExactPricingEngine::Call_Delta_BS(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B);
    }
    else
    {
        return BSExactPricingEngine::Put_Delta_BS(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B);
    }
}   

//Function which calls appropriate gamma function in BSExactPricingEngine 
double EuropeanOption::Gamma_BS() const
{   //Gamma is the same for both calls and puts
    //See comment above for appropriate defining of B "cost-of-carry" variable.
    return BSExactPricingEngine::Gamma_BS(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B);
}

//Function which calls appropriate vega function in BSExactPricingEngine
double EuropeanOption::Vega_BS() const
{   //Theta is the same for both calls and puts
    //See comment above for appropriate defining of B "cost-of-carry" variable.
    return BSExactPricingEngine::Vega_BS(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B);
}


//Function which calls appropriate call and put theta functions in BSExactPricingEngine as a function of whether the option type is call or put
double EuropeanOption::Theta_BS() const
{
    if(option_data.optiontype == Option_Type::Call)
    {
        return BSExactPricingEngine::Call_Theta_BS(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B);
    }
    else
    {   
        return BSExactPricingEngine::Put_Theta_BS(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B);
    }
}

//Function which prints out information on the instance's greeks: delta, gamma, vega, theta
std::string EuropeanOption::Four_Greeks_BS() const
{
    std::stringstream ss;
    ss << "Delta: " << Delta_BS() << " Gamma: " << Gamma_BS() << "; Theta: " << Theta_BS() <<  "; Vega: " << Vega_BS();
    return ss.str();
}


//Calling delta divided differences method in DividedDifferences files as a function of whether the instance is a call or put
double EuropeanOption::Delta_DividedDiff(const double& h) const
{
    if(option_data.optiontype == Option_Type::Call)
    {   
        return DividedDifferences::Delta_Call_DividedDiff(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B, h);
    }
    else
    {
        return DividedDifferences::Delta_Put_DividedDiff(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B, h);
    }
}

//Calling gamma divided differences method in DividedDifferences files 
double EuropeanOption::Gamma_DividedDiff(const double& h) const
{
    //Gamma is the same for both calls and puts
    //See comment above for appropriate defining of B "cost-of-carry" variable.
    return DividedDifferences::Gamma_DividedDiff(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B, h);
}

