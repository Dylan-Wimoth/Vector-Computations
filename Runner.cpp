#ifndef RUNNER_CPP
#define RUNNER_CPP

#include <cstdlib>
#include "Vector.cpp"
using namespace std;


template <class T>
class Runner {
public:
    // Name: Default Constructor
    // Precondition: None
    // Postcondition: Initiates state/environment
    Runner(Vector<T>*, Vector<T>*);
    
    // Name: mainMenu
    // Desc: Main Menu
    // Precondition: Existing Vectors
    // Postcondition: Handles various menu commands
    int mainMenu();
    
private:
    Vector<T> m_vector1;
    Vector<T> m_vector2;
};

// **** Add class definition below ****

template <class T>
// Precondition: None
// Postcondition: Initiates state/environment
Runner<T>::Runner(Vector<T>* vector1, Vector<T>* vector2){
    m_vector1 = vector1; 
    m_vector2 = vector2;

    int userChoice = 0; //Sets the user's menu option choice

    do{
        userChoice = mainMenu();

        if (userChoice == 1){
            cout << "Vector 1: ";
            m_vector1.Display();
            cout << "Vector 2: ";
            m_vector2.Display();
        }else if(userChoice == 2){
            Vector<char>* truths = m_vector1 < m_vector2;
            cout << "Vector1 < Vector2: ";
            truths->Display();
            delete truths;
        }else if(userChoice == 3){
            Vector<char>* truths = m_vector1 == m_vector2;
            cout << "Vector1 == Vector2: ";
            truths->Display();
            delete truths;
        }else if(userChoice == 4){
            Vector<T>* sums = m_vector1 + m_vector2;
            cout << "Vector1 + Vector2: ";
            sums->Display();
            delete sums;
        }else if(userChoice == 5){
            Vector<T>* products = m_vector1 * m_vector2;
            cout << "Vector1 * Vector2: ";
            products->Display();
            delete products;
        }else if(userChoice == 6){
            cout << "Vector1 median: " << m_vector1.Median() << endl;
            cout << "Vector2 median: " << m_vector2.Median() << endl;
        }else if(userChoice == 7){
            cout << "Vector1 mean: " << m_vector1.Mean() << endl;
            cout << "Vector2 mean: " << m_vector2.Mean() << endl;
        }else if(userChoice == 8){
            cout << "Vector1 stdev: " << m_vector1.StDev() << endl;
            cout << "Vector2 stdev: " << m_vector2.StDev() << endl;
        }else if (userChoice !=9){
            cout << "Invalid Choice";
        }
        cout << endl;
    }while(userChoice != 9);

}


// Precondition: Existing Vectors
// Postcondition: Handles various menu commands
template <class T>
int Runner<T>::mainMenu(){
    int userChoice = 0; //Keeps track of the user's choice

    while ((userChoice > 9) || (userChoice < 1)){
        cout << "Choose an option\n";
        cout << "1. Display Vectors\n";
        cout << "2. Vector comparison (<)\n";
        cout << "3. Vector comparison (==)\n";
        cout << "4. Vector addition\n";
        cout << "5. Vector multiplication\n";
        cout << "6. Compute median\n";
        cout << "7. Compute mean\n";
        cout << "8. Compute Standard Deviation\n";
        cout << "9. Exit\n";
        cin >> userChoice;
    }

    return userChoice;
}

#endif /* Runner_h */