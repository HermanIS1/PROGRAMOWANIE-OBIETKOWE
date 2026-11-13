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
    Wielomian &operator-=(const Wielomian &w);
    Wielomian operator-(const Wielomian &w) const;
    Wielomian &operator*=(const Wielomian &w);
    Wielomian operator*(const Wielomian &w) const;
    Wielomian &operator/=(const Wielomian &w);
    Wielomian operator/(const Wielomian &w) const;
    Wielomian &operator=(const Wielomian &w);
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

    cout << "\nTest operatora =\n\n";

    Wielomian e("2x^2+3x+1");
    Wielomian f("5x^3-2");

    e = f;

    cout << "e=f: ";
    e.Pokaz();

    cout << "\nTest operatora -=\n\n";

    Wielomian g("3x^3+2x^2+5");
    Wielomian h("x^2+2x+1");

    g -= h;

    cout << "g -= h: ";
    g.Pokaz();

    cout << "\nTest operatora -\n\n";

    Wielomian j("3x^2+4x+5");
    Wielomian k("x^2+2x+1");

    Wielomian roznica = j - k;

    cout << "j - k: ";
    roznica.Pokaz();

    cout << "\nTest operatora *=\n\n";

    Wielomian l("2x+3");
    Wielomian m("x+2");

    l *= m;

    cout << "l *= m: ";
    l.Pokaz();

    cout << "\nTest operatora *\n\n";

    Wielomian n("x+3");
    Wielomian o("x-2");

    Wielomian iloczyn = n * o;

    cout << "n * o: ";
    iloczyn.Pokaz();

    cout << "\nTest operatora /=\n\n";

    Wielomian p("3x^3+2x^2-5x+6");
    Wielomian q("x+2");

    p /= q;

    cout << "p /= q: ";
    p.Pokaz();

    cout << "\nTest operatora /\n\n";

    Wielomian r("x^3-3x^2+3x-1");
    Wielomian s("x-1");

    Wielomian iloraz = r / s;

    cout << "r / s: ";
    iloraz.Pokaz();

    cout << "\nTest dzielenia przez zero\n\n";

    Wielomian t("x^2+2x+1");
    Wielomian zero("0");

    t /= zero;

    cout << "Czy wynik jest poprawny? " << t.Poprawny() << endl;

    return 0;
}
