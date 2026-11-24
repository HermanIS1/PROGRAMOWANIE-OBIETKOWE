#include <iostream>
#include <cstdlib>

using namespace std;

class Wielomian
{
private:
    double *wsp;
    int stopien;
    bool poprawny;

public:
    Wielomian();
    Wielomian(const char *napis);
    Wielomian(int stopien, const double wsp[]);
    Wielomian(const Wielomian &w);
    ~Wielomian();

    int Stopien() const { return stopien; }
    bool Poprawny() const { return poprawny; }

    void Pokaz() const;

    Wielomian Pochodna() const;
    Wielomian &operator+=(const Wielomian &w);
    Wielomian operator+(const Wielomian &w) const;
    Wielomian &operator-=(const Wielomian &w);
    Wielomian operator-(const Wielomian &w) const;
    Wielomian &operator*=(const Wielomian &w);
    Wielomian operator*(const Wielomian &w) const;
    Wielomian &operator/=(const Wielomian &w);
    Wielomian operator/(const Wielomian &w) const;
    Wielomian &operator=(const Wielomian &w);

    double operator()(double punkt) const;
};

void pomidOdstepy(const char *&napis)
{
    while (*napis == ' ' || *napis == '\t')
        napis++;
}

int rozpoznajStopien(const char napis[])
{
    int n = 0;

    for (int i = 0; napis[i] != '\0'; ++i)
    {
        if (napis[i] == 'x')
        {
            int j = i + 1;

            while (napis[j] == ' ' || napis[j] == '\t')
                j++;

            int s = 1;

            if (napis[j] == '^')
            {
                j++;

                while (napis[j] == ' ' || napis[j] == '\t')
                    j++;

                char *r;
                s = strtol(&napis[j], &r, 10);

                if (r == &napis[j] || s < 0)
                    return -1;
            }

            if (s > n)
                n = s;
        }
    }

    return n;
}

const char *analizujJednomian(const char napis[], int stopien, double wsp[])
{
    const char *poczatek = napis;

    double liczbaR = 1;
    int liczbaC = 0;
    int znak = 1;

    pomidOdstepy(napis);

    if (*napis == '-')
    {
        znak = -1;
        napis++;
    }
    else if (*napis == '+')
        napis++;

    pomidOdstepy(napis);

    if (*napis == '+' || *napis == '-' || *napis == '\0')
        return poczatek;

    if (*napis == 'x')
        liczbaR = 1;
    else
    {
        char *r;
        liczbaR = strtod(napis, &r);

        if (r == napis)
            return poczatek;

        napis = r;
    }

    pomidOdstepy(napis);

    if (*napis == 'x')
    {
        napis++;
        pomidOdstepy(napis);

        if (*napis == '^')
        {
            napis++;
            pomidOdstepy(napis);

            char *r;
            liczbaC = strtol(napis, &r, 10);

            if (r == napis || liczbaC < 0)
                return poczatek;

            napis = r;
        }
        else
            liczbaC = 1;
    }

    if (liczbaC > (int)stopien)
        return poczatek;

    wsp[liczbaC] += znak * liczbaR;

    pomidOdstepy(napis);

    return napis;
}

int analizujJednomiany(const char napis[], int stopien, double wsp[])
{
    pomidOdstepy(napis);

    if (*napis == '\0')
        return 0;

    while (*napis != '\0')
    {
        const char *nowy = analizujJednomian(napis, stopien, wsp);

        if (nowy == napis)
            return 0;

        napis = nowy;
        pomidOdstepy(napis);

        if (*napis == '\0')
            return 1;

        if (*napis != '+' && *napis != '-')
            return 0;
    }

    return 1;
}

Wielomian Wielomian::Pochodna() const
{
    if (stopien == 0)
    {
        double tab[1] = {0};
        return Wielomian(0, tab);
    }

    double *nowaWsp = new double[stopien];

    for (int i = 1; i <= stopien; i++)
        nowaWsp[i - 1] = wsp[i] * i;

    Wielomian wynik(stopien - 1, nowaWsp);
    delete[] nowaWsp;
    return wynik;
}

Wielomian::Wielomian()
{
    stopien = 0;
    wsp = new double[1];
    wsp[0] = 0;
    poprawny = true;
}

Wielomian::Wielomian(const char *napis)
{
    int s = rozpoznajStopien(napis);

    if (s < 0)
    {
        stopien = 0;
        wsp = new double[1];
        wsp[0] = 0;
        poprawny = false;
        return;
    }

    stopien = s;
    wsp = new double[stopien + 1];

    for (int i = 0; i <= stopien; i++)
        wsp[i] = 0;

    poprawny = analizujJednomiany(napis, stopien, wsp);

    if (!poprawny)
    {
        delete[] wsp;

        stopien = 0;
        wsp = new double[1];
        wsp[0] = 0;
    }
}

Wielomian::Wielomian(int stopien, const double tab[])
{
    this->stopien = stopien;
    wsp = new double[stopien + 1];

    for (int i = 0; i <= stopien; i++)
        wsp[i] = tab[i];

    poprawny = true;
}

Wielomian::Wielomian(const Wielomian &w)
{
    stopien = w.stopien;
    wsp = new double[stopien + 1];

    for (int i = 0; i <= stopien; i++)
        wsp[i] = w.wsp[i];

    poprawny = w.poprawny;
}

Wielomian::~Wielomian()
{
    delete[] wsp;
}

void Wielomian::Pokaz() const
{
    bool pierwszy = true;

    for (int i = (int)stopien; i >= 0; i--)
    {
        double wspolczynnik = wsp[i];

        if (wspolczynnik == 0)
            continue;

        if (!pierwszy)
            cout << (wspolczynnik < 0 ? " - " : " + ");
        else if (wspolczynnik < 0)
            cout << "-";

        double wartosc = wspolczynnik < 0
                             ? -wspolczynnik
                             : wspolczynnik;

        if (i == 0 || wartosc != 1)
            cout << wartosc;

        if (i > 0)
        {
            cout << "x";

            if (i > 1)
                cout << "^" << i;
        }

        pierwszy = false;
    }

    if (pierwszy)
        cout << "0";

    cout << endl;
}

double Wielomian::operator()(double punkt) const
{
    double wynik = wsp[stopien];

    for (int i = stopien - 1; i >= 0; i--)
        wynik = wynik * punkt + wsp[i];

    return wynik;
}

Wielomian &Wielomian::operator+=(const Wielomian &w)
{
    if (stopien < w.stopien)
    {
        double *nowaT = new double[w.stopien + 1];

        for (int i = 0; i <= stopien; ++i)
            nowaT[i] = wsp[i];

        for (int i = stopien + 1; i <= w.stopien; i++)
            nowaT[i] = 0;

        delete[] wsp;

        wsp = nowaT;
        stopien = w.stopien;
    }

    for (int i = 0; i <= w.stopien; i++)
        wsp[i] += w.wsp[i];

    poprawny = poprawny && w.poprawny;

    return *this;
}

Wielomian Wielomian::operator+(const Wielomian &w) const
{
    Wielomian wynik(*this);

    wynik += w;

    return wynik;
}

Wielomian &Wielomian::operator-=(const Wielomian &w)
{
    if (stopien < w.stopien)
    {
        double *nowaT = new double[w.stopien + 1];

        for (int i = 0; i <= stopien; i++)
            nowaT[i] = wsp[i];

        for (int i = stopien + 1; i <= w.stopien; i++)
            nowaT[i] = 0;

        delete[] wsp;

        wsp = nowaT;
        stopien = w.stopien;
    }

    for (int i = 0; i <= w.stopien; i++)
        wsp[i] -= w.wsp[i];

    poprawny = poprawny && w.poprawny;

    return *this;
}

Wielomian Wielomian::operator-(const Wielomian &w) const
{
    Wielomian wynik(*this);

    wynik -= w;

    return wynik;
}

Wielomian &Wielomian::operator*=(const Wielomian &w)
{
    double *nowaT = new double[stopien + w.stopien + 1];

    for (int i = 0; i <= stopien + w.stopien; i++)
        nowaT[i] = 0;

    for (int i = 0; i <= stopien; i++)
    {
        for (int j = 0; j <= w.stopien; j++)
        {
            nowaT[i + j] += wsp[i] * w.wsp[j];
        }
    }

    delete[] wsp;

    wsp = nowaT;
    stopien = stopien + w.stopien;
    poprawny = poprawny && w.poprawny;

    return *this;
}

Wielomian Wielomian::operator*(const Wielomian &w) const
{
    Wielomian wynik(*this);

    wynik *= w;

    return wynik;
}

Wielomian &Wielomian::operator/=(const Wielomian &w)
{
    bool zerowy = true;

    for (int i = 0; i <= w.stopien; i++)
    {
        if (w.wsp[i] != 0)
            zerowy = false;
    }

    if (zerowy || !w.poprawny)
    {
        poprawny = false;
        return *this;
    }

    if (w.wsp[w.stopien] == 0)
    {
        poprawny = false;
        return *this;
    }

    if (stopien < w.stopien)
    {
        delete[] wsp;

        wsp = new double[1];
        wsp[0] = 0;
        stopien = 0;
        poprawny = poprawny && w.poprawny;

        return *this;
    }

    double *nowaT = new double[stopien - w.stopien + 1];
    double *dzielna = new double[stopien + 1];

    int aktStopien = stopien;

    for (int i = 0; i <= stopien - w.stopien; i++)
        nowaT[i] = 0;

    for (int i = 0; i <= stopien; i++)
        dzielna[i] = wsp[i];

    while (aktStopien >= w.stopien)
    {
        nowaT[aktStopien - w.stopien] = dzielna[aktStopien] / w.wsp[w.stopien];

        for (int i = 0; i <= w.stopien; i++)
        {
            dzielna[i + (aktStopien - w.stopien)] -= w.wsp[i] * nowaT[aktStopien - w.stopien];
        }

        while (aktStopien >= 0 && dzielna[aktStopien] == 0)
            aktStopien--;
    }

    delete[] wsp;
    delete[] dzielna;
    wsp = nowaT;
    stopien -= w.stopien;
    poprawny = poprawny && w.poprawny;

    return *this;
}

Wielomian Wielomian::operator/(const Wielomian &w) const
{
    Wielomian wynik(*this);

    wynik /= w;

    return wynik;
}

Wielomian &Wielomian::operator=(const Wielomian &w)
{
    if (this == &w)
        return *this;

    delete[] wsp;

    stopien = w.stopien;
    wsp = new double[stopien + 1];

    for (int i = 0; i <= stopien; i++)
        wsp[i] = w.wsp[i];

    poprawny = w.poprawny;

    return *this;
}

Wielomian operator+(const Wielomian &w, double liczba)
{
    double tab[1] = {liczba};
    Wielomian staly(0, tab);

    return w + staly;
}

Wielomian operator+(double liczba, const Wielomian &w)
{
    return w + liczba;
}

Wielomian operator-(const Wielomian &w, double liczba)
{
    double tab[1] = {liczba};
    Wielomian staly(0, tab);

    return w - staly;
}

Wielomian operator-(double liczba, const Wielomian &w)
{
    double tab[1] = {liczba};
    Wielomian staly(0, tab);

    return staly - w;
}

Wielomian operator*(const Wielomian &w, double liczba)
{
    double tab[1] = {liczba};
    Wielomian staly(0, tab);

    return w * staly;
}

Wielomian operator*(double liczba, const Wielomian &w)
{
    return w * liczba;
}

Wielomian operator/(const Wielomian &w, double liczba)
{
    double tab[1] = {liczba};
    Wielomian staly(0, tab);

    return w / staly;
}

int main()
{

    cout << "\n[1] TEST PARSERA\n";
    cout << "--------------------------------------------\n";

    const char *przyklady[] = {
        "x^2-2x+5",
        "x^3-x^2+2x-7.5",
        "2.5x^3+x-4",
        "-x^4+3",
        "7",
        "0",
        "x^2+3x^2-x",
        "x^2+",
        "x^2++3",
        "x^-2"};

    int ile = sizeof(przyklady) / sizeof(przyklady[0]);

    for (int i = 0; i < ile; i++)
    {
        Wielomian w(przyklady[i]);

        cout << "\nNapis: " << przyklady[i] << "\n";
        cout << "Wynik: ";

        if (w.Poprawny())
            w.Pokaz();
        else
            cout << "Niepoprawny wielomian";

        cout << "\n";
    }

    cout << "\n\n[2] TEST KONSTRUKTOROW\n";
    cout << "--------------------------------------------\n";

    double tab[] = {5, -2, 3};

    Wielomian w1;
    Wielomian w2("3x^2-2x+5");
    Wielomian w3(2, tab);
    Wielomian w4(w2);

    cout << "\nKonstruktor bezargumentowy:\n";
    cout << "W1 = ";
    w1.Pokaz();

    cout << "\n\nKonstruktor z napisu:\n";
    cout << "W2 = ";
    w2.Pokaz();

    cout << "\n\nKonstruktor z tablicy:\n";
    cout << "W3 = ";
    w3.Pokaz();

    cout << "\n\nKonstruktor kopiujacy:\n";
    cout << "W4 = ";
    w4.Pokaz();

    cout << "\n";

    cout << "\n\n[3] DODAWANIE WIELOMIANOW\n";
    cout << "--------------------------------------------\n";

    Wielomian a("2x^2+3x+4");
    Wielomian b("x^2+5x+2");

    cout << "\nPierwszy wielomian:\nA(x) = ";
    a.Pokaz();

    cout << "\nDrugi wielomian:\nB(x) = ";
    b.Pokaz();

    Wielomian suma = a + b;

    cout << "\n\nDzialanie: A(x) + B(x)\n";
    cout << "Wynik: ";
    suma.Pokaz();

    Wielomian suma2("2x^2+3x+4");
    suma2 += b;

    cout << "\n\nDzialanie: A(x) += B(x)\n";
    cout << "Nowy A(x) = ";
    suma2.Pokaz();

    cout << "\n\n[4] ODEJMOWANIE WIELOMIANOW\n";
    cout << "--------------------------------------------\n";

    Wielomian c("2x^2+3x+4");
    Wielomian d("x^2+5x+2");

    cout << "\nC(x) = ";
    c.Pokaz();

    cout << "\nD(x) = ";
    d.Pokaz();

    Wielomian roznica = c - d;

    cout << "\n\nDzialanie: C(x) - D(x)\n";
    cout << "Wynik: ";
    roznica.Pokaz();

    Wielomian roznica2("2x^2+3x+4");
    roznica2 -= d;

    cout << "\n\nDzialanie: C(x) -= D(x)\n";
    cout << "Nowy C(x) = ";
    roznica2.Pokaz();

    cout << "\n\n[5] MNOZENIE WIELOMIANOW\n";
    cout << "--------------------------------------------\n";

    Wielomian e("2x+3");
    Wielomian f("x+4");

    cout << "\nE(x) = ";
    e.Pokaz();

    cout << "\nF(x) = ";
    f.Pokaz();

    Wielomian iloczyn = e * f;

    cout << "\n\nDzialanie: E(x) * F(x)\n";
    cout << "Wynik: ";
    iloczyn.Pokaz();

    Wielomian iloczyn2("2x+3");
    iloczyn2 *= f;

    cout << "\n\nDzialanie: E(x) *= F(x)\n";
    cout << "Nowy E(x) = ";
    iloczyn2.Pokaz();

    cout << "\n\n[6] DZIELENIE WIELOMIANOW\n";
    cout << "--------------------------------------------\n";

    Wielomian g("3x^3+2x^2-5x+6");
    Wielomian h("x+2");

    cout << "\nG(x) = ";
    g.Pokaz();

    cout << "\nH(x) = ";
    h.Pokaz();

    Wielomian iloraz = g / h;

    cout << "\n\nDzialanie: G(x) / H(x)\n";
    cout << "Wynik: ";
    iloraz.Pokaz();

    Wielomian iloraz2("3x^3+2x^2-5x+6");
    iloraz2 /= h;

    cout << "\n\nDzialanie: G(x) /= H(x)\n";
    cout << "Nowy G(x) = ";
    iloraz2.Pokaz();

    cout << "\n\n[7] OPERATOR PRZYPISANIA\n";
    cout << "--------------------------------------------\n";

    Wielomian i("2x^2+3x+1");
    Wielomian j("5x^3-2");

    cout << "\nPrzed przypisaniem:\n";
    cout << "I(x) = ";
    i.Pokaz();

    cout << "\nJ(x) = ";
    j.Pokaz();

    i = j;

    cout << "\n\nDzialanie: I = J\n";
    cout << "Po przypisaniu I(x) = ";
    i.Pokaz();

    cout << "\n\n[8] DZIALANIA Z LICZBAMI\n";
    cout << "--------------------------------------------\n";

    Wielomian k("2x^2+3x+1");

    cout << "\nK(x) = ";
    k.Pokaz();

    cout << "\n\nK(x) + 5 = ";
    (k + 5).Pokaz();

    cout << "\n5 + K(x) = ";
    (5 + k).Pokaz();

    cout << "\nK(x) - 5 = ";
    (k - 5).Pokaz();

    cout << "\n5 - K(x) = ";
    (5 - k).Pokaz();

    cout << "\nK(x) * 3 = ";
    (k * 3).Pokaz();

    cout << "\n3 * K(x) = ";
    (3 * k).Pokaz();

    cout << "\nK(x) / 2 = ";
    (k / 2).Pokaz();

    cout << "\n\n[9] POCHODNA\n";
    cout << "--------------------------------------------\n";

    Wielomian n("3x^3+2x^2+4x+5");

    cout << "\nWielomian:\nW(x) = ";
    n.Pokaz();

    Wielomian pochodna = n.Pochodna();

    cout << "\nPochodna W'(x) = ";
    pochodna.Pokaz();

    cout << "\n";

    cout << "\n[10] OPERATOR ()\n";
    cout << "--------------------------------------------\n";

    Wielomian m("2x^3+3x^2+4x+5");

    double x = 2;

    cout << "Wielomian: ";
    m.Pokaz();

    cout << "Wartosc dla x = " << x << ": " << m(x) << endl;

    return 0;
}

// wielomian.cpp
// wielomian.h
// dane z testami
