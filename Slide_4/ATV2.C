#include <stdio.h>

int main()
{

    int cedulas[] = {200, 100, 50, 20, 10, 5};
    int quantidade[] = {2, 3, 2, 3, 4, 2};
    int usadas[] = {0, 0, 0, 0, 0, 0};

    int saque;
    int restante;
    int total_cedulas = 0;

    printf("=================================\n");
    printf("       SISTEMA DE SAQUES UNIPE\n");
    printf("=================================\n");

    printf("Digite o valor que deseja sacar: ");
    scanf("%d", &saque);

    if (saque <= 0 || saque % 5 != 0)
    {
        printf("\nValor invalido para saque.\n");
        return 0;
    }

    restante = saque;

    /* Percorre cada tipo de cedula e calcula quanto usar. */

    for (int i = 0; i < 6; i++)
    {

        usadas[i] = restante / cedulas[i];

        if (usadas[i] >= quantidade[i])
        {
            usadas[i] = quantidade[i] - 1;
        }

        restante = restante - (usadas[i] * cedulas[i]);
    }

    /* Verifica se foi possivel completar o saque. */

    if (restante != 0)
    {
        printf("\nNao foi possivel realizar o saque.\n");
        printf("Cedulas disponiveis nao permitem esse valor.\n");
        return 0;
    }

    printf("\nSaque realizado com sucesso!\n");
    printf("\nCedulas utilizadas:\n");

    /* Mostra somente as cedulas que foram utilizadas. */

    for (int i = 0; i < 6; i++)
    {

        if (usadas[i] > 0)
        {
            printf("R$ %d: %d cedula(s)\n", cedulas[i], usadas[i]);
            total_cedulas += usadas[i];
        }
    }

    printf("\nTotal de cedulas: %d\n", total_cedulas);
    printf("Retire suas cedulas abaixo.\n");

    return 0;
}