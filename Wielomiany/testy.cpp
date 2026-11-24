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

    cout << "  bezargumentowy:      " << w1;
    cout << "  z napisu:            " << w2;
    cout << "  z tablicy {5,-2,3}:  " << w3;
    cout << "  kopiujacy (z W2):    " << w4;

    cout << "\n[3] DODAWANIE, ODEJMOWANIE, MNOZENIE\n";

    Wielomian a("2x^2+3x+4");
    Wielomian b("x^2+5x+2");

    cout << "  A = " << a;
    cout << "  B = " << b;
    cout << "\n";
    cout << "  A + B = " << a + b;
    cout << "  A - B = " << a - b;
    cout << "  A * B = " << a * b;

    Wielomian c1 = a;
    c1 += b;
    cout << "  C = A, C += B  ->  C = " << c1;

    Wielomian c2 = a;
    c2 -= b;
    cout << "  C = A, C -= B  ->  C = " << c2;

    Wielomian c3 = a;
    c3 *= b;
    cout << "  C = A, C *= B  ->  C = " << c3;

    cout << "\n[4] DZIELENIE\n";

    Wielomian p("x^3+2x^2+5");
    Wielomian q("x+1");

    cout << "  P = " << p;
    cout << "  Q = " << q;
    cout << "\n";
    cout << "  P / Q = " << p / q;
    cout << "  P % Q = " << p % q;

    Wielomian d1 = p;
    d1 /= q;
    cout << "  D = P, D /= Q  ->  D = " << d1;

    Wielomian d2 = p;
    d2 %= q;
    cout << "  D = P, D %= Q  ->  D = " << d2;

    cout << "  sprawdzenie: Q * (P / Q) + (P % Q) = " << q * (p / q) + p % q;

    cout << "\n[5] DZIALANIA Z LICZBAMI\n";

    Wielomian k("2x^2+3x+1");

    cout << "  K = " << k;
    cout << "\n";
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

    cout << "  przed:  I = " << i;
    cout << "          J = " << j;
    i = j;
    cout << "  po I = J:  I = " << i;

    cout << "\n[7] POCHODNA\n";

    Wielomian n("3x^3+2x^2+4x+5");
    cout << "  W  = " << n;
    cout << "  W' = " << n.Pochodna();

    cout << "\n[8] OPERATORY () i []\n";

    Wielomian m("2x^3+3x^2+4x+5");
    cout << "  W = " << m;
    cout << "  W(2) = " << m(2) << "    (wartosc dla x = 2)\n";
    cout << "  W[3] = " << m[3] << ", W[2] = " << m[2] << ", W[1] = " << m[1]
         << ", W[0] = " << m[0] << "    (wspolczynniki)\n";
    cout << "  W[7] = " << m[7] << "    (poza stopniem)\n";

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
