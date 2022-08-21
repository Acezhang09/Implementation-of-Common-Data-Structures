#include "polynomial.h"
#include <iostream>
using namespace std;
Polynomial::Polynomial(int A[], int size) {
    size_ = size;

    for (unsigned int i = 0; i < size_; i++) {
        coefficients.insert_back(A[i]);
    }

}
Polynomial* Polynomial::add(Polynomial* rhs) {
    int finalSize;
    if (coefficients.size() > rhs->size_){
        finalSize = coefficients.size();
    }
    else {
        finalSize = rhs->size_;
    }
    int finalArr[finalSize];

    for(unsigned int i = 0; i < finalSize; i++){
        if (i >= rhs->size_){
            finalArr[i] = coefficients.select(i);
        }
        else if (i >= coefficients.size()){
            finalArr[i] = rhs->coefficients.select(i);
        }
        else{
            finalArr[i] = coefficients.select(i) + rhs->coefficients.select(i);
        }
    }
    Polynomial* answer = new Polynomial(finalArr, finalSize);
    return answer;
}
Polynomial* Polynomial::sub(Polynomial* rhs) {
    int finalSize;
    if (coefficients.size() > rhs->size_){
        finalSize = coefficients.size();
    }
    else {
        finalSize = rhs->size_;
    }
    int finalArr[finalSize];

    for(unsigned int i = 0; i < finalSize; i++){
        if (i >= rhs->size_){
            finalArr[i] = coefficients.select(i);
        }
        else if (i >= coefficients.size()){
            finalArr[i] = 0 - rhs->coefficients.select(i);
        }
        else{
            finalArr[i] = coefficients.select(i) - rhs->coefficients.select(i);
        }
    }
    Polynomial* answer = new Polynomial(finalArr, finalSize);
    return answer;
}
Polynomial* Polynomial::mul(Polynomial* rhs) {
    int finalSize = coefficients.size() + rhs->size_ -1;
    int finalArr[finalSize];
    for (unsigned int i = 0; i < finalSize; i++){
        finalArr[i] = 0;
    }
    for (unsigned int a = 0; a < coefficients.size(); a++){
        for (unsigned int b = 0; b < rhs->size_; b++) {
            finalArr[a+b] += coefficients.select(a) * rhs->coefficients.select(b);
        }
    }
    Polynomial* answer = new Polynomial(finalArr, finalSize);
    return answer;
}
void Polynomial::print() {
    string finalString = "";
    for (int i = size_-1; i >=0; i--){
        int value = coefficients.select(i);
        if (value != 0){
            if (value < 0){
                finalString = finalString + "(" + to_string(value) + ")" + "x^" + to_string(i) + " ";
            }
            else{
                finalString = finalString + to_string(value)+ "x^" + to_string(i) + " ";
            }
            if (i != size_){
                finalString += "+ ";
            }
        }
    }
    if (finalString == ""){
        cout << "empty" << endl;
    }
    else {
        cout << finalString << endl;
    }

}
