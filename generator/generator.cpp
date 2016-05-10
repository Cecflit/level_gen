#include <math.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>

#include "generator.h"

#include "cilovnik.h"
#include "ledove_pozadi.h"
#include "lesni_podlaha.h"
#include "otaznitor.h"
#include "rybator.h"
#include "strop.h"
#include "zlej.h"

#include "hnus/obdelniky.h"

#include "../level/level.h"
#include "../level/sektor.h"
#include "../level/tilemap.h"

#include "../tema/dlazdickoraj.h"
#include "../tema/zlejsci.h"

SadaDlazdic spravna_sada(Sektor *s) {
  switch (s->level->tema.biom) {
    default:
    case TemaLevelu::Tledovec:
    case TemaLevelu::Tkrystaly:
      return PoleDlazdic::led;
    case TemaLevelu::Tles:
    case TemaLevelu::Tdzungle:
      return PoleDlazdic::les;
    case TemaLevelu::Tducholes:
      return PoleDlazdic::ducholes;
  }
}

const double* spravni_zlejsci(Sektor *s) {
  switch (s->level->tema.biom) {
    default:
    case TemaLevelu::Tledovec:
    case TemaLevelu::Tkrystaly:
      return ledovi_zlejsci;
    case TemaLevelu::Tles:
    case TemaLevelu::Tdzungle:
      return lesni_zlejsci;
    case TemaLevelu::Tducholes:
      return ducholesni_zlejsci;
  }
}

void gen_ledove_pozadi(Sektor *s) {
  LedovePozadi lp(s);
}

void gen_lesni_podlaha(Sektor *s) {
  LesniPodlaha lp(s, spravna_sada(s));
  lp.generuj();
}

void gen_jeskyne1(Sektor *s) {
  LesniPodlaha lp(s, spravna_sada(s));
  lp.set_min_y(s->intact2->vyska/2 + 3);
  Strop st(s, PoleDlazdic::led);
  st.max_y = s->intact2->vyska/2 - 2;
  lp.generuj();
  st.generuj();
}

void gen_start(Sektor *s, int x, int y) {
  Cilovnik c(s);
  c.udelej_start(x, y);
}

void gen_cil(Sektor *s, int x, int y) {
  Cilovnik c(s);
  c.udelej_cil(x, y);
}

void gen_ulozovaky(Sektor *s) {
  Cilovnik c(s);
  c.nasekej_ulozovaky();
}

void gen_otazniky(Sektor *s) {
  Otaznitor o(s);
  o.nasekej_otazniky();
  o.nasekej_mince();
}

void gen_zlejsky(Sektor *s) {
  Zlej z(s, spravni_zlejsci(s));
  z.nasekej_zlejsky();
}

void gen_ryby(Tilemap *tm) {
  Rybator r(tm);
  r.nasekej_ryby();
}

void gen_obdelniky(Sektor *s) {
  SadaDlazdic sd = spravna_sada(s);
  Obdelniky o(s->intact2, sd.konvexni[7]);
  o.generuj();
}

void gen_prkna(Tilemap *tm) {
  Obdelniky o(tm, 28);
  o.zakladni_vyska = 0;
  o.odchylka_vysky = 0;
  o.zakladni_y = tm->vyska - 20;
  o.hustota /= 50;
  o.generuj();
}

void gen_teren(Sektor *s) {
  SadaDlazdic sd = spravna_sada(s);
  Obdelniky o(s->intact2, sd.konvexni[7]);
  {
    Obdelniky ob(s->intact2, sd.konvexni[7]);
    ob.hustota /= 10;
    float z_x = ob.zakladni_sirka;
    float z_y = ob.zakladni_vyska;
    float z_r = ob.hustota;
    if (s->level->tema.vyskopis == TemaLevelu::Tnebe ||
        s->level->tema.vyskopis == TemaLevelu::Tpodzemi) {
      for ( int i = s->intact2->vyska/20; i > 0; i--) {
        ob.zakladni_y = i*20;
        ob.odchylka_sirky = int(z_x / s->intact2->vyska * 20 * i);
        ob.odchylka_vysky = int(z_y / s->intact2->vyska * 20 * i);
        ob.hustota = z_r / s->intact2->vyska * 20 * i;
        ob.generuj();
      }
    } else {
      for ( int i = s->intact2->vyska/40; i > 0; i--) {
        ob.zakladni_y = i*40;
        ob.odchylka_sirky = int(z_x / s->intact2->vyska * 20 * i);
        ob.odchylka_vysky = int(z_y / s->intact2->vyska * 20 * i);
        ob.hustota = z_r / s->intact2->vyska * 20 * i;
        ob.generuj();
      }
    }
  }
  if (s->level->tema.vyskopis != TemaLevelu::Tnebe) {
    o.generuj();
  } else {
    return;
  }
  if (s->level->tema.vyskopis == TemaLevelu::Tpodzemi) {
    for ( int i = s->intact2->vyska/50; i >= 0; i--) {
      o.zakladni_y = i*50;
      o.generuj();
    }
    return;
  }
  switch (s->level->tema.biom) {
    default:
    case TemaLevelu::Tledovec:
    case TemaLevelu::Tkrystaly:
    case TemaLevelu::Tles:
      break;
    case TemaLevelu::Tdzungle:
      o.vypln = 305;
      o.zakladni_y = 0;
      o.generuj();

      o.hustota /= 3;
      o.odchylka_vysky = 3;
      o.zakladni_vyska = 3;
      for ( int i = s->intact2->vyska/20; i; i--) {
        o.zakladni_y = i*20;
        o.generuj();
      }
    case TemaLevelu::Tducholes:
      break;
  }
}
