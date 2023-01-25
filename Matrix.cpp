//Matrix.cpp

#ifndef Matrix_cpp
#define Matrix_cpp

#include "Matrix.hpp"
#include "BSExactPricingEngine.hpp"
#include "DividedDifferences.hpp"
#include "AmericanOption.hpp"


// Default constructor

Matrix::Matrix(): m_id(rand())  
{
    Init();
    m_mesh = Mesh_Generate(0.0, 0.0, 0.0);
    m_param_variable = Param_Type::S;
    m_exercise_style = Exercise_Type::Spot;
    m_basetype = Base_Type::European;
}

//Overloaded constructor
Matrix::Matrix(const std::vector<double>& source_parameter_data, const double& start_mesh, const double& end_mesh, const double& size_mesh, const Param_Type& source_type, const Base_Type& source_base)  
{
    m_id = rand();
    m_param_variable = source_type;   //Setting for S,K,T,R,Sig if European option, for example
    m_mesh = Mesh_Generate(start_mesh, end_mesh, size_mesh);      // Create mesh with inputted arguments: start and end of mesh, as well as the mesh size.
    m_basetype = source_base;         //American or European

    std::vector<double> current_vector = source_parameter_data; // Take the vector of vector parameter data and store it temporarily, so that we can modify a variable with mesh points

    if(m_basetype == Base_Type::European)
    {
        switch(m_param_variable)
        {
            case (Param_Type::S):
                for(int i = 0; i < m_mesh.size(); i++)
                {
                    current_vector[0] = m_mesh[i];
                    m_matrixdata.push_back(current_vector);
                }
                
                break;
            
            case (Param_Type::K):
                for(int i =0; i < m_mesh.size(); i++)
                {
                    current_vector[1] = m_mesh[i];
                    m_matrixdata.push_back(current_vector);
                }
                break;

            case (Param_Type::T):
                for(int i =0; i < m_mesh.size(); i++)
                {
                    current_vector[2] = m_mesh[i];
                    m_matrixdata.push_back(current_vector);
                }
                break;
            
            case (Param_Type::R):
                for(int i =0; i < m_mesh.size(); i++)
                {
                    current_vector[3] = m_mesh[i];
                    m_matrixdata.push_back(current_vector);
                }
                break;
                        
            case (Param_Type::Sig):
                for(int i =0; i < m_mesh.size(); i++)
                {
                    current_vector[4] = m_mesh[i];
                    m_matrixdata.push_back(current_vector);
                }
                break;

                //5th element is B, but is either = R, and if not, is set to 0.

            case (Param_Type::h):
                current_vector.push_back(m_mesh[0]);
                for(int i =0; i < m_mesh.size(); i++)
                {
                    current_vector[6] = m_mesh[i];
                    m_matrixdata.push_back(current_vector);
                }

            default:
                /// ERROR HANDLING
                break;
        }
    }
    else if (m_basetype == Base_Type::American)
    {
        switch(m_param_variable)
        {
            case (Param_Type::S):
            for(int i = 0; i < m_mesh.size(); i++)
            {
                current_vector[0] = m_mesh[i];
                m_matrixdata.push_back(current_vector);
            }
            break;

            default:
            break;
        }
    }
    else
    {
        throw std::invalid_argument("Error: BASE TYPE inappropriate for matrix function.");
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& source_matrix): m_id(rand()), m_matrixdata(source_matrix.m_matrixdata), m_mesh(source_matrix.m_mesh), 
m_param_variable(source_matrix.m_param_variable), m_exercise_style(source_matrix.m_exercise_style), m_basetype(source_matrix.m_basetype)
{
    // std::cout << "Copy constructor in Matrix header file used << std::endl;
}               


// Assignment operator
Matrix Matrix::operator = (const Matrix& source_matrix)     
{
    if (this == &source_matrix)
	{
		return *this;
	}
	else
	{
	    m_matrixdata = source_matrix.m_matrixdata;          // Assigning same matrix data
        m_mesh = source_matrix.m_mesh;                      // Assigning mesh points
        m_param_variable = source_matrix.m_param_variable;    // Assigning variable (S,K,T,R,Sig)
        m_exercise_style = source_matrix.m_exercise_style;  // Assigning exercise style (spot, future)
        m_basetype = source_matrix.m_basetype;              //Assigning base type (American or European)

		return *this;
	}
}

//Destructor
Matrix::~Matrix() 
{
    //std::cout << "Destructor in Matrix class used." << std::endl;
}


//FUNCTIONS

//Computes option prices, taking as argument a matrix (a vector of vectors of option data parameters)
std::vector<double> Matrix::MatrixPricer_BS(const Option_Type& optiontype, const Exercise_Type& exercisetype)
{
    if(m_basetype != Base_Type::European){return{};}
   //Checking if of European option type, and returns nothing if not.

    std::vector<double> results;    // Vector containing the prices

    if(exercisetype == Exercise_Type::Spot && isSpot() || (exercisetype == Exercise_Type::Future && isFuture()))
    { 
        if(optiontype == Option_Type::Call)
        {
            for(int i=0; i < m_matrixdata.size(); i++)
            {
                results.push_back(BSExactPricingEngine::Call_Price_BS(m_matrixdata[i])); 
            }
            return results;
        }
        else // (optiontype == Option_Type::Put)
        {
            for(int i=0; i < m_matrixdata.size(); i++)
            {
                results.push_back(BSExactPricingEngine::Put_Price_BS(m_matrixdata[i])); 
            }
            return results;
        }
    }
    else
    {
        throw std::invalid_argument("Error: EXERCISE TYPE inappropriate for pricing function.");
    }
    
}


std::vector<double> Matrix::Matrix_Delta_BS(const Option_Type& optiontype, const Exercise_Type& exercisetype)
{
    if(m_basetype != Base_Type::European){return{};}
   //Checking if of European option type, and returns nothing if not.

    std::vector<double> results;    // Vector containing the prices

    if(exercisetype == Exercise_Type::Spot && isSpot() || (exercisetype == Exercise_Type::Future && isFuture()))
    {
        if(optiontype == Option_Type::Call)
        {
            for(int i=0; i < m_matrixdata.size(); i++)
            {
                results.push_back(BSExactPricingEngine::Call_Delta_BS(m_matrixdata[i])); 
            }
        }
        else // (optiontype == Option_Type::Put)
        {
            for(int i=0; i < m_matrixdata.size(); i++)
            {
                results.push_back(BSExactPricingEngine::Put_Delta_BS(m_matrixdata[i])); 
            }
        }
    }
    else
    {
        throw std::invalid_argument("Error: EXERCISE TYPE inappropriate for pricing function.");
    }
    return results;   
}


std::vector<double> Matrix::Matrix_Gamma_BS(const Option_Type& optiontype, const Exercise_Type& exercisetype)
{
    if(m_basetype != Base_Type::European){return{};}
   //Checking if of European option type, and returns nothing if not.

    std::vector<double> results;    // Vector containing the prices

    if(exercisetype == Exercise_Type::Spot && isSpot() || (exercisetype == Exercise_Type::Future && isFuture()))
    {
       for(int i=0; i < m_matrixdata.size(); i++)
        {
            results.push_back(BSExactPricingEngine::Gamma_BS(m_matrixdata[i])); 
        }
    }
    else
    {
        throw std::invalid_argument("Error: EXERCISE TYPE inappropriate for pricing function.");
    }
    return results;
}





void Matrix::Init()
{
    m_matrixdata.push_back(std::vector<double>());
    m_matrixdata[0].assign(6, 0.0);
}


double Matrix::size_matrix() const
 {
    return m_matrixdata.size();
 }

std::vector<double> Matrix::size_vectorsinmatrix() const
{
    std::vector<double> sizes;
    for(int i=0; i< size_matrix(); i++)
    {
        sizes.push_back(m_matrixdata[i].size());
    }
    return sizes;
}


bool Matrix::isSpot() const
{
    bool result = true;
    if(m_basetype == Base_Type::European)
    {
        for(int i=0; i < m_matrixdata.size(); i++)
        {
            //Checking for B = R condition necessary for a stock spot option
            if(m_matrixdata[i][5] != m_matrixdata[i][3]) 
            {
                result = false;
                break;
            }
        }
        return result;
    }
    else if(m_basetype == Base_Type::American)
    {
        for(int i=0; i < m_matrixdata.size(); i++)
        {
        // Not certain of conditions to check whether Amrican option is spot or future
        }
        return result;
    }
    else{throw std::invalid_argument("Error: BASE TYPE inappropriate for function.");}
}

bool Matrix::isFuture() const
{
    bool result = true;
    if(m_basetype == Base_Type::European)
    {
        for(int i=0; i < m_matrixdata.size(); i++)
        {
            if(m_matrixdata[i][5] != 0.0) //Checking for B = R condition necessary for a stock spot option
            {
                result = false;
                break;
            }
        }
        return result;
    }
    else if(m_basetype == Base_Type::American)
    {
        for(int i=0; i < m_matrixdata.size(); i++)
        {
        // Not certain of conditions to check whether Amrican option is spot or future
        }
        return result;
    }
    else{throw std::invalid_argument("Error: BASE TYPE inappropriate for function.");}
}

std::vector<double> const& Matrix::getMesh() const  //Returns mesh vector data points
{
    return m_mesh;
}

void Matrix::printer_Vector()
{
    for (const auto &row : m_matrixdata) {
            for (const auto &element : row) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
}


// DIVIDED DIFFERENCE


std::vector<double> Matrix::Matrix_Delta_DividedDiff(const Option_Type& optiontype, const Exercise_Type& exercisetype)
{
    if(m_param_variable != Param_Type::h){std::invalid_argument("Error: Matrix of wrong param type to compute divided differences.");}
    //Checking if the matrix used is of the right type 

    std::vector<double> results;    // Vector containing the prices

    if(exercisetype == Exercise_Type::Spot && isSpot() || (exercisetype == Exercise_Type::Future && isFuture()))
    {
        if(optiontype == Option_Type::Call)
        {
            for(int i=0; i < m_matrixdata.size(); i++)
            {
                results.push_back(DividedDifferences::Delta_Call_DividedDiff(m_matrixdata[i],Param_Type::h)  ); 
            }
        }
        else // (optiontype == Option_Type::Put)
        {
            for(int i=0; i < m_matrixdata.size(); i++)
            {
                results.push_back(DividedDifferences::Delta_Put_DividedDiff(m_matrixdata[i],Param_Type::h)  ); 
            }
        }
    }
    else
    {
        throw std::invalid_argument("Error: EXERCISE TYPE inappropriate for pricing function.");
    }
    return results;   
}


std::vector<double> Matrix::Matrix_Gamma_DividedDiff(const Exercise_Type& exercisetype)
{
    if(m_param_variable != Param_Type::h){std::invalid_argument("Error: Matrix of wrong param type to compute divided differences.");}
    //Checking if the matrix used is of the right type 

    std::vector<double> results;    // Vector containing the prices

    if(exercisetype == Exercise_Type::Spot && isSpot() || (exercisetype == Exercise_Type::Future && isFuture()))
    {
        for(int i=0; i < m_matrixdata.size(); i++)
        {
            results.push_back(DividedDifferences::Gamma_DividedDiff(m_matrixdata[i], Param_Type::h) ); 
        }
    }
    else
    {
        throw std::invalid_argument("Error: EXERCISE TYPE inappropriate for pricing function.");
    }
    return results;
}


std::vector<double> Matrix::Matrix_Pricer_Perp(const Option_Type& optiontype, const Exercise_Type& exercisetype)
{
    if(m_basetype != Base_Type::American){return{};}
   //Checking if of European option type, and returns nothing if not.

    std::vector<double> results;    // Vector containing the prices

    if(exercisetype == Exercise_Type::Spot  || (exercisetype == Exercise_Type::Future ))
    { 
        if(optiontype == Option_Type::Call)
        {
            for(int i=0; i < m_matrixdata.size(); i++)
            {
                results.push_back(AmericanOption::Price_Call_American_Perp(m_matrixdata[i])); 
            }
            return results;
        }
        else // (optiontype == Option_Type::Put)
        {
            for(int i=0; i < m_matrixdata.size(); i++)
            {
                results.push_back(AmericanOption::Price_Put_American_Perp(m_matrixdata[i])); 
            }
            return results;
        }
    }
    else
    {
        throw std::invalid_argument("Error: EXERCISE TYPE inappropriate for pricing function.");
    }
    
}


#endif //Matrix_cpp