#include <iostream>

using namespace std;

struct wielomian
{
    double *wsp;
    unsigned int stopien;
    void Pokaz() const;
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
            int s = 1;
            if (napis[i + 1] == '^')
            {
                char *r;
                s = std::strtol(&napis[i + 2], &r, 10);
            }
            if (s > n)
                n = s;
        }
    }
    return n;
}

wielomian alokujPamiec(int s)
{
    wielomian w;
    w.stopien = s;
    w.wsp = new double[s + 1]; // (double *)malloc((s+1) * sizeof(double));

    for (int i = 0; i <= s; i++)
        w.wsp[i] = 0;

    return w;
}

const char *analizujJednomian(const char napis[], wielomian *w)
{
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

    if (*napis == 'x')
        liczbaR = 1;
    else
    {
        char *r;
        liczbaR = std::strtod(napis, &r);

        if (r == napis)
            return napis;

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
            liczbaC = std::strtol(napis, &r, 10);

            if (r == napis)
                return napis;

            napis = r;
        }
        else
            liczbaC = 1;
    }

    if (liczbaC > (int)w->stopien)
        return napis;

    w->wsp[liczbaC] += znak * liczbaR;
    pomidOdstepy(napis);
    return napis;
}

int analizujJednomiany(const char napis[], wielomian *w)
{
    pomidOdstepy(napis);

    while (*napis != '\0')
    {
        const char *nowy = analizujJednomian(napis, w);

        if (nowy == napis)
            return 0;

        napis = nowy;
        pomidOdstepy(napis);

        if (*napis == '\0')
            return 1;

        if (*napis != '+' && *napis != '-')
            return 0;

        napis++;
        pomidOdstepy(napis);

        if (*napis == '\0' || *napis == '+' || *napis == '-')
            return 0;
    }
    return 1;
}

int analizujWielomian(const char napis[], wielomian *w)
{
    int s = rozpoznajStopien(napis);
    *w = alokujPamiec(s);

    if (!analizujJednomiany(napis, w))
    {
        delete[] w->wsp;
        return 0;
    }

    return 1;
}

void wielomian::Pokaz() const
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

    for (int i = 0; i < ile; i++)
    {
        cout << przyklady[i] << " = ";

        wielomian w;

        if (analizujWielomian(przyklady[i], &w))
        {
            w.Pokaz();
            delete[] w.wsp;
        }
        else
        {
            cout << "Niepoprawny wielomian" << endl;
        }
    }

    return 0;
}
