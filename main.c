#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int o;
    int r;
    int u;
    int l;
    int rot;
} card;

card * newcard(int o, int r, int u, int l) {
    card *k=malloc(sizeof(card));
    k->o=o;
    k->r=r;
    k->u=u;
    k->l=l;
    k->rot=0;
    return k;
}

void rotate(card *c) {
    int temp=c->o;
    c->o=c->r;
    c->r=c->u;
    c->u=c->l;
    c->l=temp;
    c->rot++;
}

int fitsright(card *c, card *r) {
    if (c->r+r->l==0) {
        return 1;
    }
    return 0;
}

int fitsbelow(card *c, card *b) {
    if (c->u+b->o==0) {
        return 1;
    }
    return 0;
}

void initcards(card c[9]) {
    //kopf +, arsch -
    //orange: 1
    //blau: 2
    //grün: 3
    //braun: 4
    c[0]=*newcard(-4,2,1,-3);
    c[1]=*newcard(-4,3,1,-2);
    c[2]=*newcard(-1,3,4,-3);
    c[3]=*newcard(-1,-4,3,2);
    c[4]=*newcard(-1,3,2,4);
    c[5]=*newcard(-4,-1,2,3);
    c[6]=*newcard(-3,-4,2,1);
    c[7]=*newcard(-2,-1,3,4);
    c[8]=*newcard(-2,-4,2,1);

}

void printfield(card f[3][3]) {
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            card temp=f[i][j];
            printf("   %d    ", temp.o);
        }
        printf("\n");
        for (int j=0; j<3; j++) {
            card temp=f[i][j];
            printf("%d     %d ", temp.l, temp.r);
        }
        printf("\n");
        for (int j=0; j<3; j++) {
            card temp=f[i][j];
            printf("   %d    ", temp.u);
        }
        printf("\n");
    }
}




int main(void) {
    card field[3][3] ={0};

    card cards[9];
    initcards(cards);
    rotate(&cards[1]);

    int placed1=0;

    while (placed1<3) {
        int i=1;
        field[0][0]=cards[i-1];
        while (i<9) {
            int j=0;
            do {
                if (fitsright(&cards[0], &cards[i])==1) {
                    field[0][1]=cards[i];
                    placed1++;
                    break;
                }
                rotate(&cards[i]);
                j++;
            }while (j<3);

            i++;
        }
    }


    /*printf("%d\n",cards[0].o);
    printf("%d\n",cards[0].r);
    printf("%d\n",cards[0].u);
    printf("%d\n",cards[0].l);
    rotate(&cards[0]);
    printf("%d\n",cards[0].o);
    printf("%d\n",cards[0].r);
    printf("%d\n",cards[0].u);
    printf("%d\n",cards[0].l);
    printf("%d\n",karte->r);
    printf("%d\n",karte->u);
    printf("%d\n",karte->l);
    printf("%d\n",karte->rot);
    rotate(karte);
    printf("%d\n",karte->o);
    printf("%d\n",karte->r);
    printf("%d\n",karte->u);
    printf("%d\n",karte->l);
    printf("%d\n",karte->rot);*/
    printfield(field);
}