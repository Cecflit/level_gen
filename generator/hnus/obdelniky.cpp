#include "obdelniky.h"

#include "../random.h"
#include "../../level/tilemap.h"

Obdelniky::Obdelniky(Tilemap* tm_, BLOK vypln_) :
  tm(tm_),
  vypln(vypln_),
  zakladni_y(),
  odchylka_y(),
  zakladni_sirka(),
  odchylka_sirky(),
  zakladni_vyska(),
  odchylka_vysky(),
  hustota()
{
  zakladni_y = tm->vyska - 10;
  odchylka_y = nahodne(5) + 5;
  zakladni_sirka = nahodne(7) + 2;
  odchylka_sirky = nahodne(9) + 7;
  zakladni_vyska = nahodne(5) + 2;
  odchylka_vysky = nahodne(5) + 5;
  hustota = nahodne_d(3) + 0.2;
}

int Obdelniky::vymysli_pocet() {
  return tm->sirka * odchylka_y * hustota / odchylka_sirky;
}

void Obdelniky::generuj() {
  int x, y, w, h;
  for (int i = vymysli_pocet(); i; i--) {
    x = nahodne(tm->sirka);
    y = zakladni_y + signed_xp_rand(odchylka_y);
    w = zakladni_sirka + signed_xp_rand(odchylka_sirky);
    h = zakladni_vyska + signed_xp_rand(odchylka_vysky);
    if (w < 0) {
      x += w;
      w = -w;
    }
    if (h < 0) {
      y += h;
      h = -h;
    }
    tm->obdelnik(vypln, x, x+w, y, y+h);
  }
}
