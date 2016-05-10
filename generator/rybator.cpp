#include "rybator.h"

#include "random.h"

#include "../level/tilemap.h"

Rybator::Rybator(Tilemap *tm_):
  tm(tm_),
  w(tm->sirka),
  h(tm->vyska)
{
}

int Rybator::vymysli_pocet() {
  return (w / 10) * (h / 10);
}

void Rybator::nasekej_ryby() {
  int i, x, y;
  for (i = vymysli_pocet(); i; i--) {
    x = nahodne(w);
    y = nahodne(h);
    if (nahodne(10)) {
      switch (tm->bloky[x][y]) {
        default:
          break;
        case 11:
          tm->bloky[x][y] = 19;
          break;
        case 305:
          tm->bloky[x][y] = 312;
          break;
        case 1009:
          tm->bloky[x][y] = 1010;
          break;
        case 1869:
          tm->bloky[x][y] = 1870;
          break;
        case 1432:
          tm->bloky[x][y] = 1433;
          break;
      }
    } else {
      if (x == w-1 || y == h-1) {
        continue;
      }
      if (tm->bloky[x][y] == 11 && tm->bloky[x+1][y] == 11 &&
          tm->bloky[x][y+1] == 11 && tm->bloky[x+1][y+1] == 11) {
        tm->bloky[x][y] = 115;
        tm->bloky[x+1][y] = 116;
        tm->bloky[x][y+1] = 117;
        tm->bloky[x+1][y+1] = 118;
      }
    }
 }
}
