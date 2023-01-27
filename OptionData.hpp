//OptionData.hpp 
//
//Purpose: OptionData with struct to encapsulate option data, as well as enum classes to define option types (call or put) and exercise types (spot and future)
//
//Modification dates: 12/30/2022 - 1/25/2023


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
    Exercise_Type exercisetype;     //Exercise type: spot or future
};

#endif //OptionData_hpp
