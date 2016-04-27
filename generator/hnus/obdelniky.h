#ifndef OBDELNIKY_H
#define OBDELNIKY_H

#include "../../tema/dlazdicky.h"

class Sektor;
class Tilemap;

class Obdelniky
{
  public:
    Obdelniky(Tilemap* tm_, BLOK vypln_);
    void generuj();

    Tilemap* tm;
    BLOK vypln;
    int zakladni_y, odchylka_y;
    int zakladni_sirka, odchylka_sirky;
    int zakladni_vyska, odchylka_vysky;
    double hustota;

  private:
    int vymysli_pocet();
};

#endif // OBDELNIKY_H
