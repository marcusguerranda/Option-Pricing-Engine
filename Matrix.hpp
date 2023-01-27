//Matrix.hpp
//
//Purpose: Matrix class creating instances of matrices, with mesh points generated from Mesher function defined in Mesher.hpp, a vector of parameter data. Other functionalities are 
//         available as to the size of the matrix, the size of each vectors within the vector of vectors, checking functions to see if the matrix of data is that of spot or future option,
//         a printer function to print out information from matrix, as well as functionalities related to Black-Scholes pricing and sensitivities, and divided differences delta and gamma functionalities.
//
//Modification dates: 12/30/2022 - 1/25/2023


#ifndef Matrix_hpp
#define Matrix_hpp

#include "OptionData.hpp"
#include "Mesher.hpp"
#include <vector>
#include <cstdlib>     //For rand() function for ID() generation
#include <iostream>

//Another alternative would have been to create simply a header and source file with two functions: one to create a matrix, and the other to compute prices from the matrix given to the function
// as an argument. I deemed it more appropriate to have a class, as each matrix is an instance of its own, as well as the fact that several appropriate constructors, and operators are to be used.
// Had I used simply the two functions, I would have gone about in the following way:
//
// 1. Create matrix:  std::vector<std::vector<double>>(const std::vector<double>& source_parameter_data, const T& start_mesh, const T& end_mesh, const T& size_mesh);
//  taking as arguments sufficient information to create a mesh, and the appropriate parameter datas to work with.
// 
// 2. Matrix computer/pricer: std::vector<double> MatrixPricer(const std::vector<std::vector<double>>& source_matrix, const Option_Type& optiontype);
//  Computes prices by taking as argument a specified matrix and the option type (to call appropriate pricing functions: call, put, future?)

//The first is automatically generated given the overloaded constructor (or default constructor, with default values), and the second will be implemented below.

enum class Base_Type
{
    European, American
};

class Matrix
{
    private:
        int m_id;                                       // ID of the matrix
        std::vector< std::vector<double>> m_matrixdata; // Data for the matrix as a vector of vectors
        std::vector<double> m_mesh;                     // Mesher instance
        Param_Type m_param_variable;                    // Variable at hand
        Exercise_Type m_exercise_style;                 // Spot or future
        Base_Type m_basetype;                           // American or European

    public:

//CONSTRUCTORS AND DESTRUCTOR
// Note: since I did not create a class for Mesher, I cannot pass it as an objet. Rather, we need to pass on starting and ending points for the mesher, as well as mesh_size as arguments.
// I have also decided that the matrix construction is option type agnostic, and that the matrix only holds the parameter data as such. It is only in the pricing that we specify the type of 
// option type we have at hand.

        Matrix();                                           // Default constructor
        Matrix(const std::vector<double>& source_parameter_data, const double& start_mesh, const double& end_mesh, const double& size_mesh, const Param_Type& source_type, const Base_Type& source_base); //Overloaded constructor
        Matrix(const Matrix& source_matrix);                // Copy constructor
        Matrix operator = (const Matrix& source_matrix);    // Assignment operator
        ~Matrix();  //Destructor

        void Init();                                        // Initializer to default values
        double size_matrix() const;                         // Outputs the size of the matrix at hand / the number of vectors within the vector
        std::vector<double> size_vectorsinmatrix() const;   // Outputs the size of each vector within the vector of vectors/matrix
        void printer_Vector();
        bool isSpot() const;    // Checking function to test whether the data provided is really that of a spot option 
        bool isFuture() const;  // Checking function to test whether the data provided is really that of a future option

        std::vector<double> const& getMesh() const;         // Get mesh data from matrix instance, required when printing the appropriate information about the matrix outputs.


//BLACK-SCHOLES FUNCTIONS
        //Computes option prices, taking as argument a matrix (a vector of vectors of option data parameters)
        std::vector<double> MatrixPricer_BS(const Option_Type& optiontype, const Exercise_Type& exercisetype);  //Function outputting Black-Scholes prices as a function of each vector of parameter data, and outputting results into a vector
        std::vector<double> Matrix_Delta_BS(const Option_Type& optiontype, const Exercise_Type& exercisetype);  //Function outputting Black-Scholes deltas as a function of each vector of parameter data, and outputting results into a vector
        std::vector<double> Matrix_Gamma_BS(const Option_Type& optiontype, const Exercise_Type& exercisetype);  //Function outputting Black-Scholes gammas as a function of each vector of parameter data, and outputting results into a vector
        std::vector<double> Matrix_Vega_BS(const Option_Type& optiontype, const Exercise_Type& exercisetype);   //Function outputting Black-Scholes vegas as a function of each vector of parameter data, and outputting results into a vector
        std::vector<double> Matrix_Theta_BS(const Option_Type& optiontype, const Exercise_Type& exercisetype);  //Function outputting Black-Scholes thetas as a function of each vector of parameter data, and outputting results into a vector

//DIVIDED DIFFERENCES
        std::vector<double> Matrix_Delta_DividedDiff(const Option_Type& optiontype, const Exercise_Type& exercisetype); //Function outputting divided differences deltas as a function of each vector of parameter data, and outputting results into a vector
        std::vector<double> Matrix_Gamma_DividedDiff(const Exercise_Type& exercisetype);        //Function outputting Black-Scholes gammas as a function of each vector of parameter data, and outputting results into a vector

        std::vector<double> Matrix_Pricer_Perp(const Option_Type& optiontype, const Exercise_Type& exercisetype); //Function outputting American perpetual prices as a function of each vector of parameter data, and outputting results into a vector
};



#endif //Matrix_hpp
