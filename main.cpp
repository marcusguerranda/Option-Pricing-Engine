
//Main.cpp
//
//Purpose: Includes all functionalities pertaining to creating options, computing their prices, sensitivities, and required functionalities to do so.
//
//Date of submission: 1/27/2023


#include "EuropeanOption.hpp"        
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

    //print_Optiontype() and print_ExerciseType()
    std::cout << "For option1 is a : " << option1.print_OptionType() << " " << option1.print_ExerciseType() << " option." << std::endl; // "For option1 is a CALL SPOT option."


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

    std::vector<double> mesh_array1 = Mesh_Generate(10.0, 50.0, 1.0);   //Generate mesh of points
    std::vector<double> call_batch4_S, put_batch4_S;                    //Vectors to store price results


    std::cout << "BATCH 4: " << std::endl;

    std::cout << option4 << std::endl;                                  //Using << operator overloading to print information about option4 (it uses ToString() and Four_Greeks() functions)
    for(int i = 0; i < mesh_array1.size(); i++)                         //Looping through mesh points
    {
        option4.setS(mesh_array1[i]);                                   //Taking each mesh point and setting new value of S (monotonically increasing value of S)
        call_batch4_S.push_back(option4.Price_BS());  // Call prices for prices from 10 - 50, with mesh size 1. It calculates the price, for each instance with new values of S.
    }

    option4.set_OptionType(Option_Type::Put);                           //Setting option type to Put, rather than Call. I could have also used my toggle_optiontype() function

    for(int i = 0; i < mesh_array1.size(); i++)                         //SAME AS ABOVE, but for option4 as a "put" option now
    {
        option4.setS(mesh_array1[i]);
        put_batch4_S.push_back(option4.Price_BS());  // Put prices for prices from 10 - 50, with mesh size 1
    }

    //Print_vector() function which prints out price results stored in provided vector, and associating to associated mesh points and parameter type (S,K,T,R,Sig,B) 

    std::cout << "BATCH 4 : CALL OPTION PRICES" << std::endl;
    Print_Vector(mesh_array1, call_batch4_S, Param_Type::S);    //Print Black-Scholes call prices for monotically increasing values of S (10->50, with mesh size:1)

    std::cout << "\n" << "BATCH 4 : PUT OPTION PRICES" << std::endl;
    Print_Vector(mesh_array1, put_batch4_S, Param_Type::S);     //Print Black-Scholes put prices for monotically increasing values of S (10->50, with mesh size:1)


//A 1. d)

    
    //Storing parameter variables for batches 1 through 4 into vectors. I get the data my instantiated European option instances.
    std::vector<double> batch1 = option1.vector_data(), batch2 = option2.vector_data();


//MATRIX 1: Testing for changing values of expiring time T, for a European call spot option

    //Create matrices with an inputted vector of parameter data, mesh data (start, end, mesh size), and the source type (which parameter to be synced with mesh points? S,K,T,R,Sig?)
    //For my matrix 1, I will take batch 1 vector of parameter data, and make expiry time (T) increase monotonically from 0.05 to 0.5 with 0.05 unit increments
    // Create matrix with vector of data parameters, mesh data, and parameter the alter while holding others constant 

    //Create matrix instance with mesh points and size, the vector of parameter data, the parameter variable that will be increased monotonically with created mesh points, and the exercise type of the option
    Matrix matrix1(batch1, 0.05, 0.55, 0.05, Param_Type::T, Base_Type::European);   

    //printer_vector is a roughly defined function that prints out all the data stored in each vector with the vector of vectors/matrix.
    matrix1.printer_Vector();   //We can clearly see here, that for all B = R, in the order: S,K,T,R,Sig,B.

    if(matrix1.isSpot()){std::cout << "IS SPOT" << std::endl;} // My isSpot() checker works, and points out the fact that B = R condition is respected. It will also be checked in the MatrixPricer functions
    else{std::cout<< "NOT SPOT" << std::endl;}

    if(matrix1.isFuture()){std::cout << "IS FUTURE" << std::endl;} // My isFuture() checker works, and points out the fact that B = R condition is respected. It will also be checked in the MatrixPricer functions
    else{std::cout<< "NOT FUTURE" << std::endl;}

    // Matrix pricer function which uses the matrix instance created and the stored vector data to call pricing function in BSExactPricingEngine class. The outputted vector is printed with the 
    // function print_VectorwithoutMesher()
    std::vector<double> results_matrix1 = matrix1.MatrixPricer_BS(Option_Type::Call, Exercise_Type::Spot);  //Store results into a vector, after calling MatrixPricer_BS() function, which calls the Black-Scholes pricing function for each vector of parameter data
    Print_Vector(matrix1.getMesh(), results_matrix1,Param_Type::T);    //Printing out results stored into the vector, with monotonically increasing values of T


//MATRIX 2: Testing for changing values of volatility Sig, for a European put spot option (B=R)

    Matrix matrix2(batch2, 0.15, 0.8, 0.05, Param_Type::Sig, Base_Type::European);    //Changing values of sig volatility with mesh points starting at 0.15 and ending at 0.75, with mesh size 0.05.
    matrix2.printer_Vector();   //Printing out the data stored in each vector of the vector of vectors

    std::vector<double> results_matrix2 = matrix2.MatrixPricer_BS(Option_Type::Put, Exercise_Type::Spot);  //Store results into a vector
    Print_Vector(matrix2.getMesh(), results_matrix2, Param_Type::Sig);  //Print out pricing results computed in previous line



//Set option3 and option4 as future options
    option3.set_ExerciseType(Exercise_Type::Future);    //Set exercise type as "future". This will set B=0 into the vector of parameters data, and will be checked when using MatrixPricer() function
    option4.set_ExerciseType(Exercise_Type::Future);    //Set exercise type as "future". This will set B=0 into the vector of parameters data, and will be checked when using MatrixPricer() function

    std::vector<double> batch3 = option3.vector_data(), batch4 = option4.vector_data(); //Storing parameter data into vectors, for batches 3 and 4

//MATRIX 3: Testing for changing values of strike price K, for a European future option (B=0)
    Matrix matrix3(batch3, 0.0, 20.00, 1.0, Param_Type::K, Base_Type::European);   // Future option with batch 3 data parameters, and mesh creation with mesh points from 0 to 20 with one point increment
    matrix3.printer_Vector();  // Checking for B=0 by printing each value in each vectore of the matrix
    std::vector<double> results_matrix3 = matrix3.MatrixPricer_BS(Option_Type::Call, Exercise_Type::Future);  //Store results into a vector, computing CALL prices
    Print_Vector(matrix3.getMesh(), results_matrix3, Param_Type::K);


//MATRIX 4: Testing for changing values of interest rate R, for a European future option (B=0)
    Matrix matrix4(batch4, 0.0, 0.15, 0.01, Param_Type::R, Base_Type::European);   // Future option with batch 4 data parameters, and mesh creation with mesh points from 0 to 10 with 1pp interest rate increment
    matrix4.printer_Vector(); // Checking for B=0 by printing each value in each vectore of the matrix
    std::vector<double> results_matrix4 = matrix4.MatrixPricer_BS(Option_Type::Put, Exercise_Type::Future);  //Store results into a vector, computing PUT PRICES
    Print_Vector(matrix4.getMesh(), results_matrix4, Param_Type::R);





// OPTION SENSITIVITES

// PART 2:

    EuropeanOption option5(105.0,100.0,0.5,0.1,0.36, Option_Type::Call, Exercise_Type::Future); //This will set B=0 automatically within the computations, given it is a future option
    
    // << operator overloaded uses Four_Greeks() function, which uses Delta_BS(), Gamma_BS(), Vega_BS(), and Theta_BS(), and uses appropriate functions in BSExactPricingEngine
    // by taking optiontype parameter, which defines the type of option as Call or Put in enum class.
    std::cout << "\n"<< "Batch given in second part of Group A for CALL FUTURE" << "\n" << option5 << std::endl; 
    option5.toggle_optiontype();
    std::cout << "\n"<< "Batch given in second part of Group A for PUT FUTURE" << "\n" << option5 << std::endl; 
    
    std::vector<double> batch5 = option5.vector_data();                                                     // Storing vector parameters S,K,T,R,Sig,B into a vector
    Matrix matrix5(batch5, 70.0, 120.0, 1.0, Param_Type::S, Base_Type::European);                           // Monotonically increasing range of values of S to create matrix data
    std::vector<double> results_matrix5 = matrix5.Matrix_Delta_BS(Option_Type::Call, Exercise_Type::Future);// Store results into a vector, computing CALL deltas
    std::vector<double> results_matrix6 = matrix5.Matrix_Delta_BS(Option_Type::Put, Exercise_Type::Future); // Store results into vector, computing PUT deltas
    
    std::cout << "CALL DELTAS for our future option." << std::endl;
    Print_Vector(matrix5.getMesh(), results_matrix5, Param_Type::S);    //Printing out deltas computed and stored in results_matrix5 vector

    std::cout << "\n" << "PUT DELTAS for our future option." << std::endl;
    Print_Vector(matrix5.getMesh(), results_matrix6, Param_Type::S);    //Printing out deltas computed and stored in results_matrix6 vector

// GAMMAS

    std::vector<double> results_matrix7 = matrix5.Matrix_Gamma_BS(Option_Type::Call, Exercise_Type::Future);// Store results into a vector, computing CALL gammas
    std::vector<double> results_matrix8 = matrix5.Matrix_Gamma_BS(Option_Type::Put, Exercise_Type::Future); // Store results into vector, computing PUT gammas

    std::cout << "\n" << "CALL GAMMAS for our future option." << std::endl;
    Print_Vector(matrix5.getMesh(), results_matrix7, Param_Type::S);    //Printing out gammas computed and stored in results_matrix7 vector

    std::cout << "\n" << "PUT GAMMAS for our future option." << std::endl;
    Print_Vector(matrix5.getMesh(), results_matrix8, Param_Type::S);    //Printing out deltas computed and stored in results_matrix8 vector



// DIVIDED DIFFERNECES: CALL AND PUT PRICES, DELTA AND GAMMA

    // Calculating the gamma for call and put future option pricing using the data set:
    // K = 100, S = 105, T = 0.5, r = 0.1, b = 0 and sig = 0.36. (exact delta call = 0.5946, delta put = -0.3566).

    // The vector parameter data will be stored in the matrix, independent of whether it is a call or put. 
    // The matrix will take care of appropriate computations as a function of the specified option type specified.


//Using overloaded constructor and while loop, rather than using matrix functionalities, creating an associated mesh instance, etc.

    double h = 0.1; //Values of h, for divided differences, going from 0.1 -> 10.00
    while(h<=10.0)
    {   
        //Printing out information on call deltas with dividend differences, with monotonically increasing values of h
        std::cout << "Call Delta Divided Diff, with h=" << h << " = " << DividedDifferences::Delta_Call_DividedDiff(105.0, 100.0, 0.5, 0.1, 0.36, 0.0, h) << std::endl;
        h+=0.1; 
    }

    h = 0.1;
    while(h<=10.0) //Values of h, for divided differences, going from 0.1 -> 10.00
    {
        //Printing out information on put deltas with dividend differences, with monotonically increasing values of h
        std::cout << "Put Delta Divided Diff, with h=" << h << " = " << DividedDifferences::Delta_Put_DividedDiff(105.0, 100.0, 0.5, 0.1, 0.36, 0.0, h) << std::endl;
        h+=0.1;
    }

    h = 0.1;
    while(h<=10.0) //Values of h, for divided differences, going from 0.1 -> 10.00
    {
        //Printing out information on call/put gammas with dividend differences, with monotonically increasing values of h
        std::cout << "Call/Put Gamma Divided Diff, with h=" << h << " = " << DividedDifferences::Gamma_DividedDiff(105.0, 100.0, 0.5, 0.1, 0.36, 0.0, h) << std::endl;
        h+=0.1;
    }


    //Using matrices to output a vector of deltas and gammas with divided differences, and monoticaly increasing values of h
    EuropeanOption option7(105.0,100.0,0.5,0.1,0.36, Option_Type::Call, Exercise_Type::Future);     //Create European call future option instance with overloaded constructor
    std::vector<double>batch7 = option7.vector_data();                              // Store parameter data of option7 into a vector
    Matrix matrix7(batch7, 0.1, 10.0, 0.05, Param_Type::h, Base_Type::European);    //Creating matrix instance with monotonically increasing values of h, mesh points created with MeshGenerate() with Matrix instance creation

    std::vector<double> results_matrix9 = matrix7.Matrix_Delta_DividedDiff(Option_Type::Call, Exercise_Type::Future);   //Storing results of computations for delta call dividend differences into a vector
    std::vector<double> results_matrix10 = matrix7.Matrix_Delta_DividedDiff(Option_Type::Put, Exercise_Type::Future);   //Storing results of computations for put call dividend differences into a vector
    std::vector<double> results_matrix11 = matrix7.Matrix_Gamma_DividedDiff(Exercise_Type::Future); //No need to specify for which type of option (call or put), as it is the same
    
    
    std::cout << "CALL DELTAS for our future option with DIVIDED DIFFERENCES." << std::endl;
    Print_Vector(matrix7.getMesh(), results_matrix9, Param_Type::h);    //Print call delta with divided differences results

    std::cout << "\n" << "PUT DELTAS for our future option with DIVIDED DIFFERENCES." << std::endl;
    Print_Vector(matrix7.getMesh(), results_matrix10, Param_Type::h);   //Print put delta with divided differences results

    std::cout << "\n" << "CALL/PUT GAMMAS for our future option with DIVIDED DIFFERENCES." << std::endl;
    Print_Vector(matrix7.getMesh(), results_matrix11, Param_Type::h);   //Print call/put gammas with divided differences results

 //////////////////////////////////////////////////


// GROUP B 

    AmericanOption a_option1; //Default constructor with the data provided in the exercise, which is automatically a "call" and "spot" option
    AmericanOption a_option2(110.0, 100.0,0.1,0.1,0.02, Option_Type::Put, Exercise_Type::Spot); //Same data, but using overloaded constructor and setting option as a put

    std::cout << a_option1 << std::endl;    // Using << operator overloaded to print information about both perpetual american options, which have the same data, but one is a call and other a put
    std::cout << a_option2 << std::endl;

    std::cout << "Price for call perpertual american option instance is = " << a_option1.Price_American_Perp() << "\n" << std::endl;    //Using american perpetual call function pricer directly
    std::cout << "Price for put perpertual american option instance is = " << a_option2.Price_American_Perp() << "\n" << std::endl;     //Using american perpetual put function pricer directly


// GROUP B, Part 2
    std::vector<double>batch_a1 = a_option1.vector_data();    //The data is the same, regardless of whether it is a call or put
    Matrix matrix_a1(batch_a1, 70.0, 120.0, 1.00, Param_Type::S, Base_Type::American);  //Create matrix instance with monotonically increasing values of S, which creates a mesh instance, and associates it with the instantiation of a matrix instance

    std::vector<double> results_matrix_a1 = matrix_a1.Matrix_Pricer_Perp(Option_Type::Call, Exercise_Type::Spot);   //Store call spot American perpetual option prices into a vector
    std::vector<double> results_matrix_a2 = matrix_a1.Matrix_Pricer_Perp(Option_Type::Put, Exercise_Type::Spot);    //Store put spot American perpetual option prices into a vector

    std::cout << "CALL Perpetual prices for our American Perpetual option are: " << "\n" << std::endl;
    Print_Vector(matrix_a1.getMesh(), results_matrix_a1, Param_Type::S);    //Print results for call spot American perpetual option prices stored into a vector

    std::cout << "PUT Perpetual prices for our American Perpetual option are: " << "\n" << std::endl;
    Print_Vector(matrix_a1.getMesh(), results_matrix_a2, Param_Type::S);    //Print results for put spot American perpetual option prices stored into a vector

    return 0;
}
