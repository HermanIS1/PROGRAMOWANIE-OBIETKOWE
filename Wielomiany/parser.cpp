#include <iostream>
#include <cstdlib>

using namespace std;

class Wielomian
{
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

    Wielomian &operator+=(const Wielomian &w);
    Wielomian operator+(const Wielomian &w) const;
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

int main()
{
    const char *przyklady[] = {
        "x^2-2x+5",
        "x^3 - x^2 + 2x - 7.5",
        "2.5x^3 + x - 4",
        "-x^4 + 3",
        "7",
        "0",
        "x^2 + 3x^2 - x",
        "x^5 + 2x^2 - 1",
        "x^2 + 1",
        "  x ^ 2 + 3 ",
        "x^2+",
        "x^2++3",
        "x^2+-3",
        "2 3x+1",
        "x^",
        "x^2 abc",
        "x^-2",
        ""};

    int ile = sizeof(przyklady) / sizeof(przyklady[0]);

    cout << "Test parsera\n\n";

    for (int i = 0; i < ile; i++)
    {
        Wielomian w(przyklady[i]);

        cout << przyklady[i] << " = ";

        if (w.Poprawny())
            w.Pokaz();
        else
            cout << "Niepoprawny wielomian" << endl;
    }

    cout << "\nTest konstruktorów\n\n";

    double tab[] = {5, -2, 3};

    Wielomian w1;
    Wielomian w2("3x^2-2x+5");
    Wielomian w3(2, tab);
    Wielomian w4(w2);

    cout << "Bezargumentowy: ";
    w1.Pokaz();

    cout << "Z napisu: ";
    w2.Pokaz();

    cout << "Z tablicy: ";
    w3.Pokaz();

    cout << "Kopiujacy: ";
    w4.Pokaz();

    cout << "\nTest operatora +=\n\n";

    Wielomian a("x^2+2x+1");
    Wielomian b("3x^3+2x+5");

    a += b;

    cout << "a += b: ";
    a.Pokaz();

    cout << "\nTest operatora +\n\n";

    Wielomian c("2x^2+3x+5");
    Wielomian d("x^2-2x+1");

    Wielomian suma = c + d;

    cout << "c + d: ";
    suma.Pokaz();

    return 0;
}
