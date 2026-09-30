#include <stdio.h>

int main()
{

    int a, b, c;
    int maior_lado = a;
    int soma_quadrados = a * a + b * b + c * c - maior_lado * maior_lado;

    printf("Digite o valor dos lados do triangulo: ");
    scanf("%d %d %d", &a, &b, &c);

    /* Verifica se os valores dos lados são positivos. */

    if (a <= 0 || b <= 0 || c <= 0)
    {
        printf("Os valores devem ser maiores que 0.\n");
    }
    else if (a + b > c && a + c > b && b + c > a)
    {

        printf("O triangulo pode ser formado, ");

        /* Identifica se o triângulo é equilátero, isósceles ou escaleno. */

        if (a == b && b == c)
        {
            printf("sendo equilatero ");
        }
        else if (a == b || b == c || c == a)
        {
            printf("sendo isosceles ");
        }
        else
        {
            printf("sendo escaleno ");
        }

        /* Descobre o maior lado e classifica o ângulo do triângulo. */

        if (b > maior_lado)
        {
            maior_lado = b;
        }

        if (c > maior_lado)
        {
            maior_lado = c;
        }

        if (maior_lado * maior_lado == soma_quadrados)
        {
            printf("e retangulo.\n");
        }
        else if (maior_lado * maior_lado < soma_quadrados)
        {
            printf("e acutangulo.\n");
        }
        else
        {
            printf("e obtusangulo.\n");
        }
    }
    else
    {
        printf("O triangulo nao pode ser formado.\n");
    }

    return 0;
}