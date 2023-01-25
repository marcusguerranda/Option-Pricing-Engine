//Mesher.hpp


#ifndef Mesher_hpp
#define Mesher_hpp

#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>

enum class Param_Type
{
    //S=underlying asset price/ K=strike price/R=interest rate/Sig=volatility/T=time to expiry/h=parameter for divided differences
    S,K,R,Sig,T,h       
};

inline std::vector<double> Mesh_Generate(const double& start_mesh, const double& end_mesh, const double& size_mesh) 
{
    std::vector<double> mesh;
    double tmp = start_mesh; 

	while(tmp <= end_mesh)
    {
        mesh.push_back(tmp);
        tmp+= size_mesh;
    }

    return mesh;
}
   
// Inline definition or there will be a linking error due to GCC compiler.
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
        for(int i = 0; i < source_mesh.size(); i++)
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