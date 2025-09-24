#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// struct für karten

typedef struct {
  int o;
  int r;
  int u;
  int l;
  int rot;
  int used;
} card;

// karten initialisieren

card *newcard(int o, int r, int u, int l) {
  card *k = malloc(sizeof(card));
  k->o = o;
  k->r = r;
  k->u = u;
  k->l = l;
  k->rot = 0;
  k->used = 0;
  return k;
}

void initcards(card c[9]) {
  // kopf +, arsch -
  // orange: 1
  // blau: 2
  // grün: 3
  // braun: 4
  c[0] = *newcard(-4, 2, 1, -3);
  c[1] = *newcard(-4, 3, 1, -2);
  c[2] = *newcard(-1, 3, 4, -3);
  c[3] = *newcard(-1, -4, 3, 2);
  c[4] = *newcard(-1, 3, 2, 4);
  c[5] = *newcard(-4, -1, 2, 3);
  c[6] = *newcard(-3, -4, 2, 1);
  c[7] = *newcard(-2, -1, 3, 4);
  c[8] = *newcard(-2, -4, 2, 1);
}

// rotieren

void rotate(card *c) {
  int temp = c->o;
  c->o = c->r;
  c->r = c->u;
  c->u = c->l;
  c->l = temp;
  c->rot++;
}

// funktionen zum überprüfen

int fits(int i, int j, card field[3][3]) {
  int fit = 1;

  if (field[i][j].o + field[i - 1][j].u == 0 || i == 0 ||
      field[i - 1][j].u == 0) {
  } else {
    fit = 0;
  }

  if (field[i][j].r + field[i][j + 1].l == 0 || j == 2 ||
      field[i][j + 1].l == 0) {
  } else {
    fit = 0;
  }

  if (field[i][j].l + field[i][j - 1].r == 0 || j == 0 ||
      field[i][j - 1].r == 0) {
  } else {
    fit = 0;
  }
  if (field[i][j].u + field[i + 1][j].o == 0 || i == 2 ||
      field[i + 1][j].o == 0) {
  } else {
    fit = 0;
  }

  return fit;
}


void printfield(card f[3][3], int colors[5]) {
  printf("\e[1;1H\e[2J");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      card temp = f[i][j];
      printf("\033[1;%dm   %3d    ", colors[abs(temp.o)], temp.o);

    }
    printf("\n");
    for (int j = 0; j < 3; j++) {
      card temp = f[i][j];

      printf("\033[1;%dm%3d   \033[1;%dm%3d ", colors[abs(temp.l)], temp.l,
             colors[abs(temp.r)], temp.r);


    }
    printf("\n");
    for (int j = 0; j < 3; j++) {
      card temp = f[i][j];

      printf("\033[1;%dm   %3d    ", colors[abs(temp.u)], temp.u);
    }
    printf("\033[1;0m\n");


  }
  printf("-----------------------------------------------------\n");
}

// brute force
//

void brute_force(int current_i, int current_j, card field[3][3], card cards[9],
                 int colors[5]) {
  //  printf("aufgerufen auf %d|%d\n", current_i, current_j);


  int i, j, k, karten_nummer;
  karten_nummer = 0;
  for (i = 0; i < 9; i++) {

    // replace

    if (cards[i].used == 0) {
      field[current_i][current_j] = cards[i];
      cards[karten_nummer].used = 0;
      cards[i].used = 1;
      karten_nummer = i;
    }

    for (j = 0; j < 5; j++) {
      rotate(&field[current_i][current_j]);

      printfield(field, colors);
      usleep(10000);
      if (fits(current_i, current_j, field)) {
        //        printf("yay\n");
        if (current_i < 2) {
          brute_force(current_i + 1, current_j, field, cards, colors);
        } else if (current_j < 2) {
          brute_force(0, current_j + 1, field, cards, colors);


        } else {
          printf("fertig");
          exit(1);
        }
      }
    }
  }

  //  printf("memnsch");

  field[current_i][current_j].l = 0;
  field[current_i][current_j].r = 0;
  field[current_i][current_j].o = 0;
  field[current_i][current_j].u = 0;
  cards[karten_nummer].used = 0;
  return;
}

// feld ausgeben

int main(void) {

  int colors[5];
  colors[0] = 30;
  colors[1] = 33;
  colors[2] = 31;
  colors[3] = 32;
  colors[4] = 36; // should be brown
  card field[3][3] = {0};


  card cards[9];
  initcards(cards);
  //  rotate(&cards[1]);


  brute_force(0, 0, field, cards, colors);


}
