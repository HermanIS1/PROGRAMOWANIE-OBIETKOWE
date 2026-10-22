#include <iostream>

using namespace std;

struct wielomian
{
    double *wsp;
    unsigned int stopien;
};

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
    return w;
}

const char *analizujJednomian(const char napis[], wielomian)
{
    double liczbaR;
    int liczbaC;
    int znak = 1;

    if (*napis == '-')
    {
        znak = -1;
        napis++;
    }
    else if (*napis == '+')
        napis++;

    if (*napis == 'x')
    {
        liczbaR = 1;
    }
    else
        liczbaR = std::strtol(napis, (char **)&napis, 10);

    if (*napis != 'x')
        liczbaC = 0;
    else
    {
        napis++;
        if (*napis == '^')
            liczbaC = strtod(napis, (char **)&napis);
        else
            liczbaC = 1;
    }
    w->wsp[liczbaC] += znak * liczbaR;
}

wielomian analizujJednomiany(const char napis[], wielomian *w)
{
    const char *wsk = napis;
    while (*napis != 0)
        napis = analizujJednomian(napis, w);
}

wielomian analizujWielomian(const char napis[])
{
    int s = rozpoznajStopien(napis[]);
    wielomian w = alokujPamiec(s);
    analizujJednomiany(napis, &w);
    return w;
};

int main()
{
    wielomian w = analizujWielomian("x^2-2x+5");
    w.pokaz();

    return 0;
}

// stutod, stutol
// dopisz pokaz i czy wsyzstko dziala poprawanie i dodanie obslugi odstepow
