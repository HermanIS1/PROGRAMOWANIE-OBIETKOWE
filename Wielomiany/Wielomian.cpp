#include "Wielomian.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void pomidOdstepy(const char *&napis)
{
    while (*napis == ' ' || *napis == '\t')
        napis++;
}

void Wielomian::Normalizuj()
{
    while (stopien > 0 && wsp[stopien] == 0)
        stopien--;
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

    Normalizuj();
}

Wielomian::Wielomian(int stopien, const double tab[])
{
    this->stopien = stopien;
    wsp = new double[stopien + 1];

    for (int i = 0; i <= stopien; i++)
        wsp[i] = tab[i];

    poprawny = true;

    Normalizuj();
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

void Wielomian::Pokaz(ostream &wyj) const
{
    bool pierwszy = true;

    for (int i = (int)stopien; i >= 0; i--)
    {
        double wspolczynnik = wsp[i];

        if (wspolczynnik == 0)
            continue;

        if (!pierwszy)
            wyj << (wspolczynnik < 0 ? " - " : " + ");
        else if (wspolczynnik < 0)
            wyj << "-";

        double wartosc = wspolczynnik < 0
                             ? -wspolczynnik
                             : wspolczynnik;

        if (i == 0 || wartosc != 1)
            wyj << wartosc;

        if (i > 0)
        {
            wyj << "x";

            if (i > 1)
                wyj << "^" << i;
        }

        pierwszy = false;
    }

    if (pierwszy)
        wyj << "0";

    wyj << endl;
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

    Normalizuj();

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

    Normalizuj();

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

    Normalizuj();

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

    for (int i = 0; i <= stopien - w.stopien; i++)
        nowaT[i] = 0;

    for (int i = 0; i <= stopien; i++)
        dzielna[i] = wsp[i];

    for (int k = stopien - w.stopien; k >= 0; k--)
    {
        nowaT[k] = dzielna[k + w.stopien] / w.wsp[w.stopien];

        for (int i = 0; i <= w.stopien; i++)
        {
            dzielna[i + k] -= w.wsp[i] * nowaT[k];
        }

        dzielna[k + w.stopien] = 0;
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

Wielomian &Wielomian::operator%=(const Wielomian &w)
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
        poprawny = poprawny && w.poprawny;
        return *this;
    }

    double *reszta = new double[stopien + 1];
    int aktStopien = stopien;

    for (int i = 0; i <= stopien; i++)
        reszta[i] = wsp[i];

    for (int k = aktStopien - w.stopien; k >= 0; k--)
    {
        double mnoznikDzielnika = reszta[k + w.stopien] / w.wsp[w.stopien];

        for (int i = 0; i <= w.stopien; i++)
        {
            reszta[i + (k)] -= w.wsp[i] * mnoznikDzielnika;
        }

        reszta[k + w.stopien] = 0;
    }

    aktStopien = w.stopien - 1;

    delete[] wsp;

    if (aktStopien == -1)
    {
        stopien = 0;
        wsp = new double[1];
        wsp[0] = 0;
    }
    else
    {
        stopien = aktStopien;
        wsp = new double[stopien + 1];

        for (int i = 0; i <= stopien; i++)
            wsp[i] = reszta[i];
    }

    poprawny = poprawny && w.poprawny;

    delete[] reszta;
    Normalizuj();
    return *this;
}

Wielomian Wielomian::operator%(const Wielomian &w) const
{
    Wielomian wynik(*this);
    wynik %= w;

    return wynik;
}

double Wielomian::operator()(double punkt) const
{
    double wynik = wsp[stopien];

    for (int i = stopien - 1; i >= 0; i--)
        wynik = wynik * punkt + wsp[i];

    return wynik;
}

double Wielomian::operator[](int i) const
{
    if (i < 0 || i > stopien)
        return 0;

    return wsp[i];
}

ostream &operator<<(ostream &wyj, const Wielomian &w)
{
    w.Pokaz(wyj);
    return wyj;
}

istream &operator>>(istream &wej, Wielomian &w)
{
    string napis;
    getline(wej >> ws, napis);
    w = Wielomian(napis.c_str());
    return wej;
}
