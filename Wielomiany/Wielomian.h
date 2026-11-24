#include <iostream>

class Wielomian
{
private:
    double *wsp;
    int stopien;
    bool poprawny;

    void Normalizuj();

public:
    Wielomian();
    Wielomian(const char *napis);
    Wielomian(const double tab[], int liczba);
    Wielomian(const Wielomian &w);
    ~Wielomian();

    int Stopien() const { return stopien; }
    bool Poprawny() const { return poprawny; }

    void Pokaz(std::ostream &wyj = std::cout) const;

    Wielomian Pochodna() const;

    Wielomian &operator+=(const Wielomian &w);
    Wielomian operator+(const Wielomian &w) const;

    Wielomian &operator-=(const Wielomian &w);
    Wielomian operator-(const Wielomian &w) const;

    Wielomian &operator*=(const Wielomian &w);
    Wielomian operator*(const Wielomian &w) const;

    Wielomian &operator/=(const Wielomian &w);
    Wielomian operator/(const Wielomian &w) const;

    Wielomian &operator%=(const Wielomian &w);
    Wielomian operator%(const Wielomian &w) const;

    Wielomian &operator=(const Wielomian &w);

    double operator()(double punkt) const;
    double operator[](int i) const;
};

Wielomian operator+(const Wielomian &w, double liczba);
Wielomian operator+(double liczba, const Wielomian &w);

Wielomian operator-(const Wielomian &w, double liczba);
Wielomian operator-(double liczba, const Wielomian &w);

Wielomian operator*(const Wielomian &w, double liczba);
Wielomian operator*(double liczba, const Wielomian &w);

Wielomian operator/(const Wielomian &w, double liczba);

std::ostream &operator<<(std::ostream &wyj, const Wielomian &w);
std::istream &operator>>(std::istream &wej, Wielomian &w);

void pomidOdstepy(const char *&napis);
int rozpoznajStopien(const char napis[]);
const char *analizujJednomian(const char napis[], int stopien, double wsp[]);
int analizujJednomiany(const char napis[], int stopien, double wsp[]);
