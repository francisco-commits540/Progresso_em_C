#include <stdio.h>

int main()
{

    int passos;
    int passos_t = 0;
    int horas = 0;

    printf("Bem-vindo a UNIPACE!!\n\n");

    /* Repete até atingir 10.000 passos */
    do
    {
        horas++;

        printf("Tempo gasto: %d hora(s)\n", horas);
        printf("Digite a quantidade de passos percorridos: ");
        scanf("%d", &passos);

        /* Verifica se os passos são válidos */
        if (passos < 0)
        {
            printf("Quantidade de passos invalida!\n\n");

            /* Desfaz a hora adicionada */
            horas--;
        }
        else
        {
            /* Soma os passos ao total */
            passos_t += passos;
        }

    } while (passos_t < 10000);

    /* Mostra os resultados finais */
    printf("\nCorrida finalizada!\n");
    printf("Estatísticas abaixo:\n");
    printf("Passos percorridos: %d\n", passos_t);
    printf("Tempo necessário: %d hora(s)", horas);

    return 0;
}
