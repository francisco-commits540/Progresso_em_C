#include <stdio.h>

int main()
{

    float nota;
    float soma = 0;
    float media;

    printf("Sistema de Analise de Notas\n\n");

    /* Repete para 10 clientes */
    for (int i = 0; i < 10; i++)
    {

        /* Repete até receber uma nota válida */
        do
        {
            printf("Digite a nota do cliente %d: ", i + 1);
            scanf("%f", &nota);

            /* Verifica se a nota está entre 0 e 10 */
            if (nota < 0 || nota > 10)
            {
                printf("Nota invalida! Digite uma nota entre 0 e 10.\n");
            }

        } while (nota < 0 || nota > 10);

        /* Soma a nota ao total */
        soma += nota;
    }

    /* Calcula a média */
    media = soma / 10;

    printf("\nMedia geral: %.2f\n", media);

    /* Verifica se a média está abaixo de 7 */
    if (media < 7)
    {
        printf("Alerta! Média de avaliações abaixo do mínimo tolerado!\n");
    }
    else
    {
        printf("Continue com o bom trabalho!\n");
    }

    return 0;
}
