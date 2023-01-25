//OptionData.hpp 
//
//Purpose: Struct file to encapsulate option data
//
//Modification dates: 1/15/2023


#ifndef OptionData_hpp
#define OptionData_hpp

enum class Option_Type 
{
    Call, Put
};

enum class Exercise_Type
{
    Spot, Future
};


/* //For future extension
enum class Asset_class
{
    Commodity, stock, index
}*/

struct OptionData
{
    int m_id;           //ID of option instance
    double m_S;         // Underlying asset price
    double m_K;         // Strike price
    double m_T;         // Time to expiry
    double m_R;         // Risk-free interest rate
    double m_Sig;       // Constant volatility
    double m_B;         // Cost of carry 

    Option_Type optiontype;         //Type of the option at hand: for the moment, we only deal with puts cand call.
    Exercise_Type exercisetype;     //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
};

#endif //OptionData_hpp