#include "Wielomian.h"
#include <iostream>

using namespace std;

int main()
{

    cout << "[1] PARSER\n";

    const char *napisy[] = {"x^2-2x+5", "2.5x^3+x-4", "-x^4+3", "7", "0",
                            "x^2+3x^2-x", "x^2-x^2+3", "x^2+", "x^2++3", "x^-2"};

    for (const char *s : napisy)
    {
        Wielomian w(s);
        cout << "  " << s << "  ->  ";

        if (w.Poprawny())
            cout << w;
        else
            cout << "niepoprawny\n";
    }

    cout << "\n[2] KONSTRUKTORY\n";

    double tab[] = {5, -2, 3};
    Wielomian w1;
    Wielomian w2("3x^2-2x+5");
    Wielomian w3(2, tab);
    Wielomian w4(w2);

    cout << "  bezargumentowy: " << w1;
    cout << "  z napisu:       " << w2;
    cout << "  z tablicy:      " << w3;
    cout << "  kopiujacy:      " << w4;

    cout << "\n[3] OPERATORY ARYTMETYCZNE\n";

    Wielomian a("2x^2+3x+4");
    Wielomian b("x^2+5x+2");

    cout << "  A = " << a;
    cout << "  B = " << b;
    cout << "  A + B = " << a + b;
    cout << "  A - B = " << a - b;
    cout << "  A * B = " << a * b;

    Wielomian c = a;
    c += b;
    cout << "  A += B  ->  " << c;
    c -= b;
    cout << "  ... -= B  ->  " << c;
    c *= b;
    cout << "  ... *= B  ->  " << c;

    cout << "\n[4] DZIELENIE\n";

    Wielomian p("x^3+2x^2+5");
    Wielomian q("x+1");

    cout << "  P = " << p;
    cout << "  Q = " << q;
    cout << "  P / Q = " << p / q;
    cout << "  P % Q = " << p % q;

    Wielomian d = p;
    d /= q;
    cout << "  P /= Q  ->  " << d;
    d = p;
    d %= q;
    cout << "  P %= Q  ->  " << d;

    cout << "\n[5] DZIALANIA Z LICZBAMI\n";

    Wielomian k("2x^2+3x+1");

    cout << "  K = " << k;
    cout << "  K + 5 = " << k + 5;
    cout << "  5 + K = " << 5 + k;
    cout << "  K - 5 = " << k - 5;
    cout << "  5 - K = " << 5 - k;
    cout << "  K * 3 = " << k * 3;
    cout << "  3 * K = " << 3 * k;
    cout << "  K / 2 = " << k / 2;

    cout << "\n[6] PRZYPISANIE\n";

    Wielomian i("2x^2+3x+1");
    Wielomian j("5x^3-2");
    i = j;
    cout << "  I = J  ->  " << i;

    cout << "\n[7] POCHODNA\n";

    Wielomian n("3x^3+2x^2+4x+5");
    cout << "  W  = " << n;
    cout << "  W' = " << n.Pochodna();

    cout << "\n[8] OPERATORY () i []\n";

    Wielomian m("2x^3+3x^2+4x+5");
    cout << "  W = " << m;
    cout << "  W(2) = " << m(2) << endl;
    cout << "  W[3] = " << m[3] << ", W[1] = " << m[1] << ", W[0] = " << m[0]
         << ", W[7] = " << m[7] << endl;

    cout << "\n[9] OPERATOR >>\n";

    Wielomian z;
    cout << "  Podaj wielomian: ";
    cin >> z;

    if (z.Poprawny())
        cout << "  Wczytano: " << z;
    else
        cout << "  Niepoprawny wielomian\n";

    return 0;
}
