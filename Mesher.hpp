//Mesher.hpp
//
//Purpose: Creating a mesh from starting and ending mesh points, and defining mesh point size. There is also << operator overloading and PrintVector() function
//         to print the output results of the matrices after having been stored into a vector. This function sets mesh points with those data points within the vector provided, and prints out
//         the appropriate information.
//Modification dates: 12/30/2022 - 1/25/2023

#ifndef Mesher_hpp
#define Mesher_hpp

#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>

enum class Param_Type //Parameter variables, in order to create appropriate mesh points 
{
    //S=underlying asset price/ K=strike price/R=interest rate/Sig=volatility/T=time to expiry/h=parameter for divided differences
    S,K,R,Sig,T, h       
};

//Create mesh points with starting and ending mesh points, and uniform mesh size
inline std::vector<double> Mesh_Generate(const double& start_mesh, const double& end_mesh, const double& size_mesh) 
{
    std::vector<double> mesh;
    double tmp = start_mesh; //Take starting point and set it as the beginning of the vector of points

	while(tmp <= end_mesh)   //Iterating through increments of mesh points by storing each new mesh point into the vector, and thus iterating till it reaches the end mesh point
    {
        mesh.push_back(tmp);
        tmp+= size_mesh;    //Resetting value of departing mesh point with previous mesh point attained, and incrementing with uniform mesh size
    }

    return mesh;
}
   
// Inline definition or there will be a linking error due to GCC compiler.
// << operator overloading to print out the type of parameter at hand
inline std::ostream& operator << (std::ostream& os, const Param_Type& source_type) {
    switch (source_type) {
        case Param_Type::S:
            os << "S";
            break;
        case Param_Type::K:
            os << "K";
            break;
        case Param_Type::R:
            os << "R";
            break;
        case Param_Type::Sig:
            os << "Sig";
            break;
        case Param_Type::T:
            os << "T";
        case Param_Type::h:
            os << "h";
            break;
    }
    return os;
}

//Takes a mesh array and the results associated, and prints these as a function of the type of values at hand (Strike, Volatility, etc.)
inline void Print_Vector(const std::vector<double>& source_mesh, const std::vector<double>& source_results, const Param_Type& source_type)  
{
    if(source_mesh.size() == source_results.size()) //Verifying if both vectors are of the same size
    {
        for(int i = 0; i < source_mesh.size(); i++) //For-loop iterating through mesh points, and getting associated output results from the vector provided
        {
            std::cout << source_type << " at: " << source_mesh[i] <<" = " << source_results[i] << std::endl;
        }
    }
    else
    {
        std::cout << "Not of the same size. We cannot print appropriate information if they are not of the same size." << std::endl;
    }
}


#endif //Mesher_hpp
