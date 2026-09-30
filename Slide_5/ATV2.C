
#include <stdio.h>

int main()
{

    float total = 0;
    int i;

    printf("Bem-vindo ao Cofrinho Digital!\n\n");

    /* Repete até o usuário escolher 4 */
    do
    {
        printf("Quanto deseja adicionar: \n");
        printf("1 - R$ 0,50\n");
        printf("2 - R$ 1,00\n");
        printf("3 - R$ 2,00\n");
        printf("4 - Finalizar\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &i);

        /* Adiciona R$ 0,50 */
        if (i == 1)
        {
            printf("R$ 0,50 adicionado ao Cofrinho!\n\n");
            total += 0.50;
        }

        /* Adiciona R$ 1,00 */
        else if (i == 2)
        {
            printf("R$ 1,00 adicionado ao Cofrinho!\n\n");
            total += 1.00;
        }

        /* Adiciona R$ 2,00 */
        else if (i == 3)
        {
            printf("R$ 2,00 adicionados ao Cofrinho!\n\n");
            total += 2.00;
        }

        /* Trata opções diferentes de 1, 2 e 3 */
        else
        {
            printf("Digite uma opção válida!\n\n");
        }

    } while (i != 4);

    /* Mostra o resultado final */
    printf("Programa Encerrado\n");
    printf("Valor total depositado: %.2f", total);

    return 0;
}
