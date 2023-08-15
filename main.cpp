#include <iostream>
#include <iomanip>
using namespace std;


class Fraction{
private:
    int numerator;
    int denominator;

    int greatestCommonDivisor(int a, int b){
        if (b == 0){
            return abs(a);
        }else {
            return abs(greatestCommonDivisor(b, a % b));
        }
    }

    void simplify(){
        if (denominator < 0){
            numerator *= -1;
            denominator *= -1;
        }
        int gcd = greatestCommonDivisor(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }



public:
    Fraction() : numerator(), denominator(){};
    friend ostream& operator<<(ostream& out, const Fraction& fraction);
    friend istream& operator>>(istream& in, Fraction& fraction);
    friend Fraction operator+( Fraction& op1, Fraction& op2);
    friend Fraction operator-(Fraction& op1, Fraction& op2);
    friend Fraction operator*(Fraction& op1, Fraction& op2);
    friend Fraction operator/(Fraction& op1, Fraction& op2);


    Fraction(int numerator, int denominator) {
        this->numerator = numerator;
        this->denominator = denominator;
        simplify();
    };

    operator double() const{
        return double(numerator) / double(denominator);
    }

    Fraction& operator+=(Fraction fraction){
        *this = *this + fraction;
        return *this;
    }

    Fraction& operator-=(Fraction fraction){
        *this = *this - fraction;
        return *this;
    }

    Fraction& operator*=(Fraction fraction){
        *this = *this * fraction;
        return *this;
    }

    Fraction& operator/=(Fraction fraction){
        *this = *this / fraction;
        return *this;
    }

    Fraction& operator++(){
        this->numerator += denominator;
        simplify();
        return *this;
    }

    Fraction operator++(int){
        Fraction temp(*this);
        this->numerator += denominator;
        simplify();
        return temp;
    }

    Fraction& operator--(){
        this->numerator -= denominator;
        simplify();
        return *this;
    }

    Fraction operator--(int){
        Fraction temp(*this);
        this->numerator -= denominator;
        simplify();
        return temp;
    }

};

ostream& operator<<(ostream& out, const Fraction& fraction){
    if (fraction.denominator == 1){
        cout << fraction.numerator;
        return out;
    }else if (fraction.numerator > fraction.denominator){
        int newNumerator;
        int newWholeNumber;
        for (int remainder = fraction.numerator - 1; fraction.numerator > 1; remainder--)
            if (remainder % fraction.denominator == 0){
                newNumerator = fraction.numerator - remainder;
                newWholeNumber = remainder / fraction.denominator;
                out << newWholeNumber <<  "-" << newNumerator << "/" << fraction.denominator;
                return out;
            }
    }else{
        out << fraction.numerator << "/" << fraction.denominator;
        return out;
    }
    return out;
}

istream& operator>>(istream& in, Fraction& fraction){
    char n;
    cout << "Please enter your fraction (n/d): ";
    in >> fraction.numerator >> n >> fraction.denominator;
    fraction.greatestCommonDivisor(fraction.numerator, fraction.denominator);
    fraction.simplify();
    return in;
}

Fraction operator+( Fraction& op1,  Fraction& op2){
    int newNum = op1.numerator * op2.denominator + op2.numerator * op1.denominator;
    int newDenom = op1.denominator * op2.denominator;

    return Fraction(newNum, newDenom);

}

Fraction operator-( Fraction& op1,  Fraction& op2){
    int newNum = op1.numerator * op2.denominator - op2.numerator * op1.denominator;
    int newDenom = op1.denominator * op2.denominator;

    return Fraction(newNum, newDenom);

}

Fraction operator*( Fraction& op1,  Fraction& op2){
    int newNum = op1.numerator * op2.numerator;
    int newDenom = op1.denominator * op2.denominator;

    return Fraction(newNum, newDenom);

}

Fraction operator/( Fraction& op1,  Fraction& op2){
    int newNum = op1.numerator * op2.denominator;
    int newDenom = op1.denominator * op2.numerator;

    return Fraction(newNum, newDenom);
}

int main() {


    Fraction fraction;
    cin >> fraction;
    cout << "Your fraction simplified: " << fraction << endl;
    Fraction fraction1(1, 2);
    Fraction fraction2(3, 4);

    if (fraction1 > fraction2){
        cout << fraction1 << " is greater than " << fraction2 << endl;
    }else if(fraction1 < fraction2){
        cout << fraction1 << " is less than " << fraction2 << endl;
    }else {
        cout << "The fractions are equal." << endl;
    }

    //TODO - simplify fractions
    cout << "Basic arithmetic and conversion:" << endl;
    cout << fraction1 + fraction2 << endl;
    cout << fraction1 - fraction2 << endl;
    cout << fraction1 * fraction2 << endl;
    cout << fraction1 / fraction2 << endl;


    cout << "Fractions to doubles:" << endl;
    cout << double(fraction1)<< endl;
    cout << double(fraction2)<< endl;

    cout << "Compound assignment: ";
    fraction1 += fraction2;
    cout << fraction1 << endl;

    cout << "Compound assignment: ";
    Fraction fraction3(3, 4);
    fraction3 -= Fraction(1, 2);
    cout << fraction3 << endl;

    cout << "Compound assignment: ";
    Fraction fraction4(3,4);
    fraction4 *= Fraction(1,2);
    cout << fraction4 << endl;

    cout << "Compound assignment: ";
    Fraction fraction5(3,4);
    fraction5 /= Fraction(1, 2);
    cout << fraction5 << endl;

    cout << "Increment operations:" << endl;
    Fraction fraction6(4, 7);
    cout << ++fraction6 << endl;
    cout << fraction6 << endl;

    cout << "Increment operations:" << endl;
    Fraction fraction7(4, 7);
    cout << fraction7++ << endl;
    cout << fraction7 << endl;

    cout << "Increment operations:" << endl;
    Fraction fraction8(4, 7);
    cout << --fraction8 << endl;
    cout << fraction8 << endl;

    cout << "Increment operations:" << endl;
    Fraction fraction9(4, 7);
    cout << fraction9-- << endl;
    cout << fraction9 << endl;


    return 0;
}
