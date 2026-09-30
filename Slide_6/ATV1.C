#include <stdio.h>

int main()
{
    int num[10];
    int posicoes[10];
    int busca;
    int quantidade = 0;

    /*Preenchendo o vetor*/
    for (int i = 0; i < 10; i++)
    {
        printf("Adicione um valor inteiro para seu vetor: ");
        scanf("%d", &num[i]);
    }

    /*Número que queremos procurar*/
    printf("\nQual valor gostaria de buscar no seu vetor?: ");
    scanf("%d", &busca);

    /*Procurando o número*/
    for (int i = 0; i < 10; i++)
    {
        if (busca == num[i])
        {
            posicoes[quantidade] = i;
            quantidade++;
        }
    }

    /*Mostrando o resultado*/
    if (quantidade == 0)
    {
        printf("\nO numero %d nao foi encontrado.\n", busca);
    }
    else
    {

        printf("\nO numero %d foi encontrado %d vezes.\n", busca, quantidade);
        printf("Posicoes encontradas: ");

        for (int i = 0; i < quantidade; i++)
        {
            printf("%d ", posicoes[i]);
        }
        printf("\n");
    }

    return 0;
}