#include <stdio.h>

int main()
{

    int a;
    int b;
    int c;

    /* Lê os três valores inteiros digitados pelo usuário */

    printf("Digite o valor de 'a': ");
    scanf("%d", &a);
    printf("Digite o valor de 'b': ");
    scanf("%d", &b);
    printf("Digite o valor de 'c': ");
    scanf("%d", &c);

    /* Maior valor: começa assumindo 'a' e atualiza se 'b' ou 'c' forem maiores */

    int maior_valor = a;

    if (b > maior_valor)
    {
        maior_valor = b;
    }
    if (c > maior_valor)
    {
        maior_valor = c;
    }

    /* Menor valor: começa assumindo 'c' e atualiza se 'b' ou 'a' forem menores */

    int menor_valor = c;

    if (b < menor_valor)
    {
        menor_valor = b;
    }
    if (a < menor_valor)
    {
        menor_valor = a;
    }

    /* Intermediário: soma de todos menos o maior e o menor */

    int intermediario = (a + b + c) - maior_valor - menor_valor;

    printf("Organização dos valores: \n");
    printf("Maior valor: %d \n", maior_valor);
    printf("Menor valor: %d \n", menor_valor);
    printf("Valor intermediario: %d \n", intermediario);

    /* Compara os pares de valores: se algum par for igual, há repetição.
       Depois, se a == b e b == c, todos são iguais */

    if (a == b || b == c || a == c)
    {
        printf("Existem valores repetidos ");
        printf("\n");
    }
    else
    {
        printf("Não existem valores repetidos! \n");
    }
    if (a == b && b == c)
    {
        printf("e todos são iguais! \n");
    }

    /* Ordem: a > b > c é decrescente; a < b < c é crescente;
       qualquer outro caso é considerado desordenado */

    if (a > b && b > c)
    {
        printf("Os valores estão em ordem decrescente.");
    }
    else if (a < b && b < c)
    {
        printf("Os valores estão em ordem crescente.");
    }
    else
    {
        printf("Os valores estão desordenados");
    }

    return 0;
}