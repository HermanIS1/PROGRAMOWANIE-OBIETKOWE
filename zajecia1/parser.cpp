#include <iostream>

using namespace std;

struct wielomian
{
    double *wsp;
    unsigned int stopien;

    void Pokaz() const;
};

void pominOdstepy(const char *&napis)
{
    while (*napis == ' ' || *napis == '\t' || *napis == '\n' || *napis == '\r')
        ++napis;
}

bool czyCyfra(char znak)
{
    return znak >= '0' && znak <= '9';
}

double odczytajLiczbe(const char *&napis)
{
    double liczba = 0.0;
    bool odczytanoCyfre = false;

    while (czyCyfra(*napis))
    {
        liczba = liczba * 10.0 + (*napis - '0');
        ++napis;
        odczytanoCyfre = true;
    }

    if (*napis == '.')
    {
        ++napis;
        double miejsceDziesietne = 0.1;
        while (czyCyfra(*napis))
        {
            liczba += (*napis - '0') * miejsceDziesietne;
            miejsceDziesietne *= 0.1;
            ++napis;
            odczytanoCyfre = true;
        }
    }

    if (!odczytanoCyfre)
        throw "Oczekiwano liczby.";
    return liczba;
}

int odczytajWykladnik(const char *&napis)
{
    if (!czyCyfra(*napis))
        throw "Niepoprawny wykladnik.";

    int wykladnik = 0;
    while (czyCyfra(*napis))
    {
        if (wykladnik > 100000)
            throw "Wykladnik jest zbyt duzy.";
        wykladnik = wykladnik * 10 + (*napis - '0');
        ++napis;
    }
    return wykladnik;
}

int rozpoznajStopien(const char napis[])
{
    int n = 0;
    for (int i = 0; napis[i] != '\0'; ++i)
    {
        if (napis[i] == 'x')
        {
            int s = 1;
            int j = i + 1;
            while (napis[j] == ' ' || napis[j] == '\t' || napis[j] == '\n' || napis[j] == '\r')
                ++j;
            if (napis[j] == '^')
            {
                ++j;
                while (napis[j] == ' ' || napis[j] == '\t' || napis[j] == '\n' || napis[j] == '\r')
                    ++j;
                const char *wykladnik = &napis[j];
                s = odczytajWykladnik(wykladnik);
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
    w.wsp = new double[s + 1];
    for (int i = 0; i <= s; ++i)
        w.wsp[i] = 0.0;
    return w;
}

const char *analizujJednomian(const char napis[], wielomian *w)
{
    double liczbaR = 1.0;
    int liczbaC = 0;
    int znak = 1;

    pominOdstepy(napis);

    if (*napis == '-')
    {
        znak = -1;
        napis++;
    }
    else if (*napis == '+')
        napis++;

    pominOdstepy(napis);
    if (*napis == 'x')
    {
        liczbaR = 1;
    }
    else
    {
        liczbaR = odczytajLiczbe(napis);
    }

    pominOdstepy(napis);
    if (*napis == 'x')
    {
        napis++;
        pominOdstepy(napis);
        if (*napis == '^')
        {
            ++napis;
            pominOdstepy(napis);
            liczbaC = odczytajWykladnik(napis);
        }
        else
            liczbaC = 1;
    }

    if (liczbaC > static_cast<int>(w->stopien))
        throw "Wykladnik przekracza stopien wielomianu.";
    w->wsp[liczbaC] += znak * liczbaR;
    pominOdstepy(napis);
    if (*napis != '\0' && *napis != '+' && *napis != '-')
        throw "Niepoprawny znak po jednomianie.";
    return napis;
}

void analizujJednomiany(const char napis[], wielomian *w)
{
    pominOdstepy(napis);
    while (*napis != '\0')
    {
        napis = analizujJednomian(napis, w);
        pominOdstepy(napis);
    }
}

wielomian analizujWielomian(const char napis[])
{
    int s = rozpoznajStopien(napis);
    wielomian w = alokujPamiec(s);
    try
    {
        analizujJednomiany(napis, &w);
    }
    catch (...)
    {
        delete[] w.wsp;
        throw;
    }
    return w;
};

void wielomian::Pokaz() const
{
    bool pierwszy = true;
    for (int i = static_cast<int>(stopien); i >= 0; --i)
    {
        const double wspolczynnik = wsp[i];
        if (wspolczynnik == 0.0)
            continue;

        if (!pierwszy)
            cout << (wspolczynnik < 0 ? " - " : " + ");
        else if (wspolczynnik < 0)
            cout << '-';

        const double wartosc = wspolczynnik < 0 ? -wspolczynnik : wspolczynnik;
        if (i == 0 || wartosc != 1.0)
            cout << wartosc;
        if (i > 0)
        {
            cout << 'x';
            if (i > 1)
                cout << '^' << i;
        }
        pierwszy = false;
    }
    if (pierwszy)
        cout << '0';
    cout << '\n';
}

int main()
{
    const char *przyklady[] = {
        "x^2-2x+5",
        "x^3 - x^2 + 2x - 7.5",
        " 2.5 x ^ 3 + x - 4 ",
        "-x^4 + 3",
        "7",
        "0"};

    for (const char *napis : przyklady)
    {
        cout << napis << " = ";
        wielomian w = analizujWielomian(napis);
        w.Pokaz();
        delete[] w.wsp;
    }

    return 0;
}
