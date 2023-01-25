

#include "EuropeanOption.hpp"       //Include 
#include "BSExactPricingEngine.hpp"
#include "DividedDifferences.hpp"
#include "AmericanOption.hpp"
#include "Mesher.hpp"
#include "Matrix.hpp"
#include <iostream>



int main()
{   

//A. 1. a)

    EuropeanOption option1;                                 // Initializing default European option instance, whose default values take Batch 1 values
    EuropeanOption option2(100.0, 100.00, 1.0, 0.0, 0.2, Option_Type::Call, Exercise_Type::Spot);   // Batch 2 data using overloaded constructor
    EuropeanOption option3(5.0, 10.00, 1.0, 0.12, 0.5, Option_Type::Call, Exercise_Type::Spot);     // Batch 3 data using overloaded constructor
    EuropeanOption option4(100.0, 100.00, 30.0, 0.08, 0.3, Option_Type::Call, Exercise_Type::Spot); // Batch 4 data using overloaded constructor

    EuropeanOption options[4] = {option1, option2, option3, option4};   //Array of 4 call European vanilla option instances

    for(int i=0; i<4; i++)
    {
        std::cout << "\n" << "BATCH " << (i+1) << "\n" << std::endl; //Printing batch number information (Batch 1, Batch 2, Batch 3, Batch 4)
        std::cout << options[i] << std::endl;           // Using << operator, which uses getter, ToString(), and Four_Greeks_BS() functions to print option parameter and greeks information
        options[i].toggle_optiontype();                 // Using toggle() function to switch from "Call" to "Put" in an efficient and fast manner.
        std::cout << options[i] << std::endl;           // Now printing information for the put of the stock option
    }


//A. 1. b)
    
    for(int i=0; i<4; i++)
    {
        std::cout << "\n" << "BATCH " << (i+1) << "\n" << std::endl; //Printing batch number information (Batch 1, Batch 2, Batch 3, Batch 4)
        //Using Parity_Difference() function to calculate the difference between putcall parity prices and exact prices, which uses the PutCallParity() pricing function.

        std::cout << options[i].Parity_checker() << "\n" << std::endl;

        std::cout << "The difference between the exact CALL price of PUT option in BATCH " << (i+1) << " and the price of the call in put-call parity is: " << options[i].Parity_Difference() << std::endl;
        options[i].toggle_optiontype();    // Using toggle() function to switch from "Call" to "Put" in an efficient and fast manner.
        std::cout << "The difference between the exact PUT price of CALL option in BATCH " << (i+1) << " and the price of the put in put-call parity is: " << options[i].Parity_Difference() << std::endl;
    }


//A 1. c)

    std::vector<double> mesh_array1 = Mesh_Generate(10.0, 50.0, 1.0);
    std::vector<double> call_batch4_S, put_batch4_S;


    std::cout << "BATCH 4: " << std::endl;

    std::cout << option4 << std::endl;
    for(int i = 0; i < mesh_array1.size(); i++)
    {
        option4.setS(mesh_array1[i]);        
        call_batch4_S.push_back(option4.Price_BS());  // Call prices for prices from 10 - 50, with mesh size 1
    }

    option4.set_OptionType(Option_Type::Put);

    for(int i = 0; i < mesh_array1.size(); i++)
    {
        option4.setS(mesh_array1[i]);
        put_batch4_S.push_back(option4.Price_BS());  // Put prices for prices from 10 - 50, with mesh size 1
    }

    std::string S="S", K="K", T="T", R="R", Sig="Sig", B="B"; 
    std::cout << "BATCH 4 : CALL OPTION PRICES" << std::endl;
    Print_Vector(mesh_array1, call_batch4_S, Param_Type::S);

    std::cout << "\n" << "BATCH 4 : PUT OPTION PRICES" << std::endl;
    Print_Vector(mesh_array1, put_batch4_S, Param_Type::S);


//A 1. d)

    
    //Storing parameter variables for batches 1 through 4 into vectors. I get the data my instantiated European option instances.
    std::vector<double> batch1 = option1.vector_data(), batch2 = option2.vector_data();


//MATRIX 1: Testing for changing values of expiring time T, for a European call spot option

    //Create matrices with an inputted vector of parameter data, mesh data (start, end, mesh size), and the source type (which parameter to be synced with mesh points? S,K,T,R,Sig?)
    //For my matrix 1, I will take batch 1 vector of parameter data, and make expiry time (T) increase monotically from 0.0 to 0.5 with 0.05 unit increments
    // Create matrix with vector of data parameters, mesh data, and parameter the alter while holding others constant 

    Matrix matrix1(batch1, 0.05, 0.55, 0.05, Param_Type::T, Base_Type::European);   
    // Matrix pricer function which uses the matrix instance created and the stored vector data to call pricing function in BSExactPricingEngine class. The outputted vector is printed with the 
    // function print_VectorwithoutMesher()
    
    matrix1.printer_Vector();   //We can clearly see here, that for all B = R, in the order: S,K,T,R,Sig,B.

    if(matrix1.isSpot()){std::cout << "IS SPOT" << std::endl;} // My isSpot checker works, and points out the fact that B = R condition is respected. It will also be checked in the MatrixPricer functions
    else{std::cout<< "NOT SPOT" << std::endl;}

    if(matrix1.isFuture()){std::cout << "IS FUTURE" << std::endl;}      
    else{std::cout<< "NOT FUTURE" << std::endl;}

    std::vector<double> results_matrix1 = matrix1.MatrixPricer_BS(Option_Type::Call, Exercise_Type::Spot);  //Store results into a vector
    Print_Vector(matrix1.getMesh(), results_matrix1, Param_Type::T);


//MATRIX 2: Testing for changing values of volatility Sig, for a European put spot option (B=R)

    Matrix matrix2(batch2, 0.15, 0.8, 0.05, Param_Type::Sig, Base_Type::European);    //Changing values of sig volatility with mesh points starting at 0.15 and ending at 0.75, with mesh size 0.05.
    matrix2.printer_Vector();                   //Checking for B=R, given Spot exercise type

    std::vector<double> results_matrix2 = matrix2.MatrixPricer_BS(Option_Type::Put, Exercise_Type::Spot);  //Store results into a vector
    Print_Vector(matrix2.getMesh(), results_matrix2, Param_Type::Sig);



//Set option3 and option4 as future options
    option3.set_ExerciseType(Exercise_Type::Future);    //This will set B=0 into the vector of parameters data, and will be checked when using MatrixPricer() function
    option4.set_ExerciseType(Exercise_Type::Future);    //This will set B=0 into the vector of parameters data, and will be checked when using MatrixPricer() function

    std::vector<double> batch3 = option3.vector_data(), batch4 = option4.vector_data(); //Storing parameter data into vectors, for batches 3 and 4

//MATRIX 3: Testing for changing values of strike price K, for a European future option (B=0)
    Matrix matrix3(batch3, 0.0, 20.00, 1.0, Param_Type::K, Base_Type::European);   // Future option with batch 3 data parameters, and mesh creation with mesh points from 0 to 20 with one point increment
    matrix3.printer_Vector();                                   // Checking for B=0
    std::vector<double> results_matrix3 = matrix3.MatrixPricer_BS(Option_Type::Call, Exercise_Type::Future);  //Store results into a vector, computing CALL prices
    Print_Vector(matrix3.getMesh(), results_matrix3, Param_Type::K);


//MATRIX 4: Testing for changing values of interest rate R, for a European future option (B=0)
    Matrix matrix4(batch4, 0.0, 0.15, 0.01, Param_Type::R, Base_Type::European);   // Future option with batch 4 data parameters, and mesh creation with mesh points from 0 to 10 with 1pp interest rate increment
    matrix4.printer_Vector();                                   // Checking for B=0
    std::vector<double> results_matrix4 = matrix4.MatrixPricer_BS(Option_Type::Put, Exercise_Type::Future);  //Store results into a vector, computing PUT PRICES
    Print_Vector(matrix4.getMesh(), results_matrix4, Param_Type::R);

/////////////////////////////////////////////////////////////////////////////////



// OPTION SENSITIVITES

// PART 2:

    EuropeanOption option5(105.0,100.0,0.5,0.1,0.36, Option_Type::Call, Exercise_Type::Future); //This will set B=0 automatically within the computations.

    // << operator overloaded uses Four_Greeks() function, which uses Delta_BS(), Gamma_BS(), Vega_BS(), and Theta_BS(), and uses appropriate functions in BSExactPricingEngine
    // by taking optiontype parameter, which defines the type of option as Call or Put in enum class.
    std::cout << "\n"<< "Batch given in second part of Group A." << "\n" << option5 << std::endl; 
    
    std::vector<double> batch5 = option5.vector_data();                                                     // Storing vector parameters S,K,T,R,Sig,B into a vector
    Matrix matrix5(batch5, 70.0, 120.0, 1.0, Param_Type::S, Base_Type::European);                                                // Monotonically increasing range of values of S to create matrix data
    std::vector<double> results_matrix5 = matrix5.Matrix_Delta_BS(Option_Type::Call, Exercise_Type::Future);// Store results into a vector, computing CALL deltas
    std::vector<double> results_matrix6 = matrix5.Matrix_Delta_BS(Option_Type::Put, Exercise_Type::Future); // Store results into vector, computing PUT deltas
    
    std::cout << "CALL DELTAS for our future option." << std::endl;
    Print_Vector(matrix5.getMesh(), results_matrix5, Param_Type::S);

    std::cout << "\n" << "PUT DELTAS for our future option." << std::endl;
    Print_Vector(matrix5.getMesh(), results_matrix6, Param_Type::S);

// GAMMAS

    std::vector<double> results_matrix7 = matrix5.Matrix_Gamma_BS(Option_Type::Call, Exercise_Type::Future);// Store results into a vector, computing CALL gammas
    std::vector<double> results_matrix8 = matrix5.Matrix_Gamma_BS(Option_Type::Put, Exercise_Type::Future); // Store results into vector, computing PUT gammas

    std::cout << "\n" << "CALL GAMMAS for our future option." << std::endl;
    Print_Vector(matrix5.getMesh(), results_matrix7, Param_Type::S);

    std::cout << "\n" << "PUT GAMMAS for our future option." << std::endl;
    Print_Vector(matrix5.getMesh(), results_matrix8, Param_Type::S);


// DIVIDED DIFFERNECES: CALL AND PUT PRICES, DELTA AND GAMMA

    // Calculating the gamma for call and put future option pricing using the data set:
    // K = 100, S = 105, T = 0.5, r = 0.1, b = 0 and sig = 0.36. (exact delta call = 0.5946, delta put = -0.3566).

    // The vector parameter data will be stored in the matrix, independent of whether it is a call or put. 
    // The matrix will take care of appropriate computations as a function of the specified option type specified.

    //Using overloaded constructor

    double h = 0.1;
    while(h<=10.0)
    {
        std::cout << "Call Delta Divided Diff, with h=" << h << " = " << DividedDifferences::Delta_Call_DividedDiff(105.0, 100.0, 0.5, 0.1, 0.36, 0.0, h) << std::endl;
        h+=0.1;
    }

    h = 0.1;
    while(h<=10.0)
    {
        std::cout << "Put Delta Divided Diff, with h=" << h << " = " << DividedDifferences::Delta_Put_DividedDiff(105.0, 100.0, 0.5, 0.1, 0.36, 0.0, h) << std::endl;
        h+=0.1;
    }

    h = 0.1;
    while(h<=10.0)
    {
        std::cout << "Call/Put Gamma Divided Diff, with h=" << h << " = " << DividedDifferences::Gamma_DividedDiff(105.0, 100.0, 0.5, 0.1, 0.36, 0.0, h) << std::endl;
        h+=0.1;
    }

    
    //Using matrices to output a vector of deltas and gammas with divided differences, and monoticaly increasing values of h
    EuropeanOption option7(105.0,100.0,0.5,0.1,0.36, Option_Type::Call, Exercise_Type::Future); 
    std::vector<double>batch7 = option7.vector_data();
    Matrix matrix7(batch7, 0.1, 10.0, 0.05, Param_Type::h, Base_Type::European);

    std::vector<double> results_matrix9 = matrix7.Matrix_Delta_DividedDiff(Option_Type::Call, Exercise_Type::Future);
    std::vector<double> results_matrix10 = matrix7.Matrix_Delta_DividedDiff(Option_Type::Put, Exercise_Type::Future);
    std::vector<double> results_matrix11 = matrix7.Matrix_Gamma_DividedDiff(Exercise_Type::Future); //No need to specify for which type of option (call or put), as it is the same
    
    
    std::cout << "CALL DELTAS for our future option with DIVIDED DIFFERENCES." << std::endl;
    Print_Vector(matrix7.getMesh(), results_matrix9, Param_Type::h);

    std::cout << "\n" << "PUT DELTAS for our future option with DIVIDED DIFFERENCES." << std::endl;
    Print_Vector(matrix7.getMesh(), results_matrix10, Param_Type::h);

    std::cout << "\n" << "CALL/PUT GAMMAS for our future option with DIVIDED DIFFERENCES." << std::endl;
    Print_Vector(matrix7.getMesh(), results_matrix11, Param_Type::h);

 //////////////////////////////////////////////////


// GROUP B 

    AmericanOption a_option1; //Default constructor with the data provided in the exercise.
    AmericanOption a_option2(110.0, 100.0,0.1,0.1,0.02, Option_Type::Put, Exercise_Type::Spot); //Same data, but using overloaded constructor and setting option as a put

    std::cout << a_option1 << std::endl;    // Using << operator overloaded to print information about both perpetual american options, which have the same data, but one is a call and other a put
    std::cout << a_option2 << std::endl;

    std::cout << "Price for call perpertual american option instance is = " << a_option1.Price_American_Perp() << "\n" << std::endl;
    std::cout << "Price for put perpertual american option instance is = " << a_option2.Price_American_Perp() << "\n" << std::endl;


// GROUP B, Part 2
    std::vector<double>batch_a1 = a_option1.vector_data();    //The data is the same, regardless of whether it is a call or put
    Matrix matrix_a1(batch_a1, 70.0, 120.0, 1.00, Param_Type::S, Base_Type::American);

    std::vector<double> results_matrix_a1 = matrix_a1.Matrix_Pricer_Perp(Option_Type::Call, Exercise_Type::Spot);
    std::vector<double> results_matrix_a2 = matrix_a1.Matrix_Pricer_Perp(Option_Type::Put, Exercise_Type::Spot);

    std::cout << "CALL Perpetual prices for our American Perpetual option are: " << "\n" << std::endl;
    Print_Vector(matrix_a1.getMesh(), results_matrix_a1, Param_Type::S);

    std::cout << "PUT Perpetual prices for our American Perpetual option are: " << "\n" << std::endl;
    Print_Vector(matrix_a1.getMesh(), results_matrix_a2, Param_Type::S);
    
    return 0;
}