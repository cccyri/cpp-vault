//Building the rational numbers class


#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class Rational
{
public:
	Rational()
	{
		num = 0;
		den = 1;
	}

	Rational(const int& numerator, const int& denominator)
	{
		const long GCD = gcd(abs(numerator), abs(denominator));

		if (numerator * denominator >= 0)
		{
			if (numerator == 0)
			{
				num = numerator;
				den = 1;
			}
			else
			{
				num = abs(numerator) / GCD;
				den = abs(denominator) / GCD;
			}
		}
		else
		{
			if (numerator > 0)
			{
				num = -1 * (numerator / GCD);
			}
			else
			{
				num = numerator / GCD;
			}
			den = abs(denominator) / GCD;
		}
	}

	long Numerator() const
	{
		return num;
	}

	long Denominator() const
	{
		return den;
	}

private:
	int num;
	int den;

	long gcd(long a, long b)
	{
		return (b == 0) ? abs(a) : gcd(b, a % b);
	}
};


istream& operator>>(istream& stream, Rational& rational)
{
	if (stream)
	{
		long denominator, numerator;
		stream >> numerator;
		stream.ignore(1);
		stream >> denominator;
		rational = Rational(numerator, denominator);
		return stream;
	}
}

ostream& operator<<(ostream& stream, const Rational& rational)
{
	if (stream)
	{
		stream << rational.Numerator() << "/" << rational.Denominator();
		return stream;
	}
}

Rational operator+(const Rational& left, const Rational& right)
{
	return Rational(left.Numerator() * right.Denominator() + right.Numerator() * left.Denominator(), right.Denominator() * left.Denominator());
}

Rational operator-(const Rational& left, const Rational& right)
{
	return Rational(left.Numerator() * right.Denominator() - right.Numerator() * left.Denominator(), right.Denominator() * left.Denominator());
}

Rational operator/(const Rational& left, const Rational& right)
{
	return Rational(left.Numerator() * right.Denominator(), right.Numerator() * left.Denominator());
}

Rational operator*(const Rational& left, const Rational& right)
{
	return Rational(left.Numerator() * right.Numerator(), right.Denominator() * left.Denominator());
}

bool operator<(const Rational& left, const Rational& right)
{
	return (left.Numerator() * right.Denominator() < right.Numerator() * left.Denominator());
}

bool operator>(const Rational& left, const Rational& right)
{
	return (left.Numerator() * right.Denominator() > right.Numerator() * left.Denominator());
}

bool operator==(const Rational& left, const Rational& right)
{
	return (left.Numerator() == right.Numerator() && right.Denominator() == left.Denominator());
}

bool operator!=(const Rational& left, const Rational& right)
{
	return (left.Numerator() != right.Numerator() || right.Denominator() != left.Denominator());
}

int main() {

	bool check(string s, const vector<Rational>&expected);

	vector<bool> checks = { check("5%7", {}),
							check("10 / 8", {{5, 4}}),
							check("", {}),
							check("+5 / -4", {{-5, 4}}),
							check("5/7 10 / 8 , 3 / 4", {{5, 7}, {5, 4}}),
							check(",5/7", {}),
							check(" +5 /-4 1/ ", {{-5, 4}}) };



	{
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			return 1;
		}
	}

	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			cout << "5/7 is incorrectly read as " << r << endl;
			return 2;
		}
	}

	{
		istringstream input("");
		Rational r;
		bool correct = !(input >> r);
		if (!correct) {
			cout << "Read from empty stream works incorrectly" << endl;
			return 3;
		}
	}

	{
		istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			return 4;
		}

		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
			return 5;
		}
	}

	{
		istringstream input1("1*2"), input2("1/"), input3("/4");
		Rational r1, r2, r3;
		input1 >> r1;
		input2 >> r2;
		input3 >> r3;
		bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
		if (!correct) {
			cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
				<< r1 << " " << r2 << " " << r3 << endl;
			return 6;
		}
	}

	cout << "OK" << endl;
	return 0;
}
