//
// Created by Antonio Silva Paucar on 2020-08-27.
//

#include <stdio.h>
#include <string.h>
#define SIZE 10
typedef struct
{
    int a;
    int b;
    int c;
}prueba;


int main()
{

    prueba uno[SIZE];
    uno[0].a = 1;
    uno[0].b = 2;
    uno[0].c = 3;


    uno[1].a = 11;
    uno[1].b = 21;
    uno[1].c = 31;

    printf("%d %d %d\n",uno[1].a, uno[1].b, uno[1].c);
    printf("%d %d %d\n",uno[0].a, uno[0].b, uno[0].c);

    prueba dos[SIZE];
    memcpy(dos, uno, SIZE*sizeof(prueba));

    printf("dos %d %d %d\n",dos[1].a, dos[1].b, dos[1].c);
    printf("dos %d %d %d\n",dos[0].a, dos[0].b, dos[0].c);

    prueba tres = uno[1];
    tres.a = 333;
    tres.b = 4544;
    printf("copia %d %d %d\n",tres.a, tres.b, tres.c);
    printf("%d %d %d\n",uno[1].a, uno[1].b, uno[1].c);


    return 0;
}