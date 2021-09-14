#include <iostream>
#include "Check.hpp"
using namespace std;

int main(){
    // char avai for availability, it is for making sure the array is an Arithmetic progression by asking the user later.
    char avai = 'n';
    // ask the using and guide user to input information we want.
    cout << "Is your array an Arithmetic progression? If yes please press 'Y' or 'y' and press Enter key. If it isn't, please press enter key.\n";
    // save the input from user.
    avai = cin.get();
    // if it is not an Arithmetic progression, we cannot use gauss algorithm.
    double sum_num = gauss(avai);
    //show the answer to the user.
    cout << "The total of your array by gauss algorithm by Gauss algorithm is: \n" << sum_num << "\n(if it is -1, means it is not an Arithmetic progression)\n";
    
    //the second method, always working but resourses costing.
    double total = just_do_it();
    cout <<"The total of your array is: \n" << total << "\n";

    //end the program.
    return 0;
}

// here is how the gauss algorithm method inplments.
// with a correct algorithm, we can boost our program largely when the quantity is huge.
int gauss(char avai){
    //check the availiablity first.
    if (avai != 'Y' and avai !='y'){
        // if it is not, set the result to be -1.
        return -1;
    }
    
    // ini_num for the first number of the array.
    double ini_num; 
    // fin_num for the last number of the array.
    double fin_num; 
    // ele_dev for the element deviation of the array.
    double ele_dev;
    // tell the user it's time to enter the first element.
    cout << "Please enter the first number of your array: \n";
    // take the input from user and save it to the ini_num variable.
    cin >> ini_num;
    // tell the user it's time to enter the last element.
    cout << "Please enter the last number of your array: \n";
    //take the input from user and save it to the fin_num variable. 
    cin >> fin_num;  
    // tell the user it's time to enter the element deviation.
    cout << "Please enter the element deviation of your array here: \n";
    cin >> ele_dev;
    //using the gauss algorithm to get the answer.

    // ele_num for the number of how many elements we are calculating.
    // sum_num for the sum of the elements
    double ele_num, sum_num;

    // the number of the elements is the last element minus the first element, then devided by the element deviation and and one for the minused first element.
    ele_num = (fin_num - ini_num)/ele_dev + 1.0;
    // the number of the sum is the first element adds the last elements then times the number of the elements and finally, devided by two.
    sum_num = (ini_num + fin_num) * ele_num / 2.0;
    // give the answer back to who calls this method.
    return sum_num;
}

// now we are asking for the user to input every single element in the array, and add them up.
int just_do_it(){
    // first of all, we still need to know how many elements in the array.
    // set an variable to store the info.
    int numbers;
    //ask the user for it.
    cout << "Please enter how many elements in your array:\n ";
    // save the data into the variable.
    cin >> numbers;
    //initialize an variable for the sum number.
    double total = 0;
    // using a loop to ask for every element and add it up.
    // the recurring time equals the number of elements in the array.
    for (int i = 0; i < numbers; i++){
        //initalize an variable for a single element.
        double element = 0;
        //ask user for the element.
        cout << "please enter the (next) number: \n";
        //save the data to the variable;
        cin >> element;
        //add every element up.
        total += element;
    }
    //give the total back to who calls the method.
    return total;
}; 