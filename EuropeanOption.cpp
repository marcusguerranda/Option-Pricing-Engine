



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
    setS(newS);
    setK(newK);
    setT(newT);
    setR(newR);
    setSig(newSig);
    set_OptionType(new_optiontype);
    set_ExerciseType(new_exercise);

    if(option_data.exercisetype == Exercise_Type::Spot) 
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
EuropeanOption::EuropeanOption(const EuropeanOption& source)   ////////////????????????? rethink whether you just copy the data, or create a new instance?
{
    EuropeanOption();
    EuropeanOption::Copy(source);
    //std::cout << "Overloaded constructor in 'EuropeanOption" used." << std::endl;
}

//Assignment operator
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& source)  
{
    if (this == &source)
    {
        return *this;
    }
    else
    {
        EuropeanOption::Copy(source);
        return *this;
    }
}


EuropeanOption::~EuropeanOption()
{
    //std::cout << "Destructor used in EuropeanOption." << std::endl;
}



//MEMBER FUNCTIONS

void EuropeanOption::Init()
{//Note: list initialization is only for cosntructors.
    option_data.m_id = rand();
    option_data.m_S = 60.0;
    option_data.m_K = 65.0; 
    option_data.m_T = 0.25; 
    option_data.m_R = 0.08; 
    option_data.m_Sig = 0.30; 
    option_data.m_B = option_data.m_R;                  //As is the case for a spot option, default exercise type here.
    option_data.optiontype = Option_Type::Call;
    option_data.exercisetype = Exercise_Type::Spot; 

    //std::cout << "Init function in EuropeanOption being used." << std::endl;
}


void EuropeanOption::Copy(const EuropeanOption& source)
{
    option_data.m_id = source.option_data.m_id;
    option_data.m_S = source.option_data.m_S; 
    option_data.m_K = source.option_data.m_K; 
    option_data.m_T = source.option_data.m_T; 
    option_data.m_R = source.option_data.m_R;
    option_data.m_Sig = source.option_data.m_Sig; 
    option_data.m_B = source.option_data.m_B;
    option_data.optiontype = source.option_data.optiontype;
    option_data.exercisetype = source.option_data.exercisetype;
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

double const& EuropeanOption::getT() const          // Getter function for expiry date of option for asset at hand
{
    return option_data.m_T;
}

double const& EuropeanOption::getR() const          // Getter function for interest rate
{
    return option_data.m_R;
}

double const& EuropeanOption::getSig() const        // Getter function for volatility of asset at hand
{
    return option_data.m_Sig;
}

double const& EuropeanOption::getB() const           //Getter function for cost of carry
{
    return option_data.m_B;
}

int const& EuropeanOption::getID() const            //Getter function to get ID of option instance at hand
{
    return option_data.m_id;
}


std::string EuropeanOption::print_OptionType() const
{
    switch(option_data.optiontype)
    {
        case Option_Type::Call:
            return "CALL";
            break;
        case Option_Type::Put:
            return "PUT";
            break;
        default:
            return "No type handled.";          //XXXXXXXXXXXXXXXXXXXXXXXXXXXX
    }
}

std::string EuropeanOption::print_ExerciseType() const
{
    switch(option_data.exercisetype)
    {
        case Exercise_Type::Spot:
            return "SPOT";
            break;
        case Exercise_Type::Future:
            return "FUTURE";
            break;
        default:
            return "No type handled";           //XXXXXXXXXXXXXXXXXXXXXXXXXXXX
    }
}


std::string EuropeanOption::ToString() const
{
    std::stringstream ss;
    ss << "Type: " << print_OptionType() << " " << print_ExerciseType() << "; S: " << getS() << "; T: " << getT() <<  "; K:" << getK() << "; R: " << getR() << "; Sig: " << getSig() << "; B: " << getB()<< "; ID: " << getID() << "\n";
    ss << "Price of option using the Black-Scholes exact pricing formula is: " << Price_BS();
    return ss.str();
}


std::ostream& operator << (std::ostream &os, const EuropeanOption& source)
{
    os << source.ToString() << "\n";
    os << source.Four_Greeks_BS() << "\n";
    return os;
}


double EuropeanOption::PutCallParity() const   // If the option is a call, it will return the price of the put option when satisfying put-call parity conditions. And vice-versa.
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

std::string EuropeanOption::Parity_checker()     // Checks for parity for a European option using K and T: there is a put-call parity when K = T.
{
    return (Parity_Difference() == 0.0) ? "YES: There is put-call parity." : "NO: There is no put-call parity";
}              


double EuropeanOption::Parity_Difference() 
{
    // Temporary variable which will store the difference between the opposed option type when in put-call parity, and the exact price defined.
    // For example, if I have a call, I wish to know the difference between the exact price for the put version, and when in put call parity. Such a difference will be given in absolute value terms.
    if (option_data.optiontype == Option_Type::Call)
    {
        double tmp = PutCallParity();                       //Return value for put-call parity.
        toggle_optiontype();                                           //Change type 
        return round(abs(tmp - Price_BS()) / 1e-8) * 1e-8;  //Rounding to tolerance error of 1e-8, as suggestd by A.Palley on12/23/21
    }
    else     
    {
        double tmp = PutCallParity(); 
        toggle_optiontype();   
        return round(abs(tmp - Price_BS()) / 1e-8) * 1e-8;    //Rounding to tolerance error of 1e-8, as suggestd by A.Palley on12/23/21
    }
}


std::vector<double> EuropeanOption::vector_data() const
{
    std::vector<double> tmp; 
    tmp.push_back(getS());
    tmp.push_back(getK());
    tmp.push_back(getT());
    tmp.push_back(getR());
    tmp.push_back(getSig());
    tmp.push_back(getB());

    return tmp;
}



//SETTERS

void EuropeanOption::setS(const double& newS) 
{
    option_data.m_S = newS;
}

void EuropeanOption::setK(const double& newK) 
{
    option_data.m_K = newK;
}

void EuropeanOption::setT(const double& newT) 
{
    option_data.m_T = newT;
}

void EuropeanOption::setR(const double& newR) 
{
    option_data.m_R = newR;
}

void EuropeanOption::setSig(const double& newSig) 
{
    option_data.m_Sig = newSig;
}
    

//Toggle() function to change type between call, put, and future.
void EuropeanOption::toggle_optiontype()
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
            /// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX exception handling
            break;
    }
}

//Toggle exercise types: spot option or future, taking into consideration the changes in value for B.
void EuropeanOption::toggle_exercisetype()
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
            /// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX exception handling
             break;
    }
}

void EuropeanOption::set_OptionType(const Option_Type& source_optiontype)
{
    option_data.optiontype = source_optiontype;
}

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
// Virtual Greek functions, which were declared as pure virtual member functions in abstract base class "Option"
            
double EuropeanOption::Price_BS() const
{
    //B = R when facing a stock option model. However, B=0 when it is a futures option model. For the moment, I use an if else and check whether we have a put or call. In the future, when
    //extending our model, I would rather use a switch/case in order to check if Option_Type optiontype is a call/put or future, and assign a tempory value for B as a function of what is 
    //apporpriate.

    if(option_data.optiontype == Option_Type::Call)
    {   
        return BSExactPricingEngine::Call_Price_BS(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B);
    }
    else
    {
        return BSExactPricingEngine::Put_Price_BS(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B);
    }
}


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


double EuropeanOption::Gamma_BS() const
{   //Gamma is the same for both calls and puts
    //See comment above for appropriate defining of B "cost-of-carry" variable.
    return BSExactPricingEngine::Gamma_BS(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B);
}


double EuropeanOption::Vega_BS() const
{   //Theta is the same for both calls and puts
    //See comment above for appropriate defining of B "cost-of-carry" variable.
    return BSExactPricingEngine::Vega_BS(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B);
}


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

std::string EuropeanOption::Four_Greeks_BS() const
{
    std::stringstream ss;
    ss << "Delta: " << Delta_BS() << " Gamma: " << Gamma_BS() << "; Theta: " << Theta_BS() <<  "; Vega: " << Vega_BS();
    return ss.str();
}


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


double EuropeanOption::Gamma_DividedDiff(const double& h) const
{
    //Gamma is the same for both calls and puts
    //See comment above for appropriate defining of B "cost-of-carry" variable.
    return DividedDifferences::Gamma_DividedDiff(option_data.m_S, option_data.m_K,option_data.m_T,option_data.m_R, option_data.m_Sig, option_data.m_B, h);
}

