#include <stdio.h>

int main()
{
    int estoque[10];
    int maisDe20 = 0;
    int maior;
    int produtoMaior;

    /*Cadastro das quantidades*/
    for (int i = 0; i < 10; i++)
    {
        printf("Digite a quantidade do produto %d: ", i + 1);
        scanf("%d", &estoque[i]);
    }

    /*Mostrar quantidade de cada produto*/
    printf("\n=== ESTOQUE DOS PRODUTOS ===\n");

    for (int i = 0; i < 10; i++)
    {
        printf("Produto %d: %d unidades\n", i + 1, estoque[i]);
    }

    /*Inicializando o maior*/
    maior = estoque[0];
    produtoMaior = 0;

    printf("\n=== ESTOQUE BAIXO ===\n");

    for (int i = 0; i < 10; i++)
    {
        /*Estoque baixo*/
        if (estoque[i] < 5)
        {
            printf("Produto %d possui estoque baixo: %d unidades\n",i + 1, estoque[i]);
        }

        /*Produto esgotado*/
        if (estoque[i] == 0)
        {
            printf("Produto %d está ESGOTADO.\n", i + 1);
        }

        /* Mais de 20 unidades*/
        if (estoque[i] > 20)
        {
            maisDe20++;
        }

        /* Maior quantidade*/
        if (estoque[i] > maior)
        {
            maior = estoque[i];
            produtoMaior = i;
        }
    }

    /*Saída para o usuário*/

    printf("\n=== RESULTADOS ===\n");

    printf("Quantidade de produtos com mais de 20 unidades: %d\n", maisDe20);

    printf("Produto com maior estoque: Produto %d\n", produtoMaior + 1);
    printf("Quantidade em estoque: %d unidades\n", maior);

    return 0;
}