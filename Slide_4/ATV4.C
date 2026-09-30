#include <stdio.h>

int main()
{

    int escolha;
    int valor;

    /* Exibe o menu com as opções disponíveis para o usuário */

    printf("===== MENU ===== \n");
    printf("1 - Verificar número par ou ímpar \n");
    printf("2 - Verificar se é positivo ou negativo \n");
    printf("3 - Calcular o quadrado do número \n");
    printf("4 - Sair \n \n");

    /* Lê a opção escolhida e usa o switch para executar apenas o bloco correspondente */

    printf("Digite uma das opções disponiveis: ");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:
        printf("Selecionado: Verificar número par ou ímpar \n \n");
        printf("Digite um valor: ");
        scanf("%d", &valor);

        /* Se o valor não for zero: verifica par/ímpar pelo resto da divisão por 2
           e, em seguida, positivo/negativo. Se for zero, pede para tentar novamente */

        if (valor != 0)
        {
            if (valor % 2 == 0)
            {
                printf("Valor par ");
            }
            else
            {
                printf("Valor ímpar ");
            }

            if (valor > 0)
            {
                printf("e positivo.");
            }
            else
            {
                printf("e negativo.");
            }
        }
        else
        {
            printf("Valor nulo, tente novamente! \n");
        }
        break;
    case 2:
        printf("Selecionado: Verificar se é positivo ou negativo \n \n");
        printf("Digite um valor: ");
        scanf("%d", &valor);

        /* Valor diferente de zero: maior que 0 é positivo, caso contrário é negativo.
           Valor igual a zero: informa que é nulo */

        if (valor != 0)
        {
            if (valor > 0)
            {
                printf("O valor digitado é positivo!");
            }
            else
            {
                printf("O valor digitado é negativo!");
            }
        }
        else
        {
            printf("O valor digitado é nulo!");
        }
        break;
    case 3:
        printf("Selecionado: Calcular o quadrado do número \n \n");
        printf("Digite um valor: ");
        scanf("%d", &valor);

        /* Se o valor não for zero, exibe o quadrado (valor * valor).
           Caso contrário, informa que é nulo */

        if (valor != 0)
        {
            printf("Valor ao quadrado: %d", valor * valor);
        }
        else
        {
            printf("O valor digitado é nulo!");
        }
        break;
    case 4:
        /* Encerra o programa exibindo uma mensagem de saída */
        printf("Sistema encerrado!");
        break;
    default:
        /* Qualquer opção fora do intervalo 1-4 cai aqui */
        printf("Selecione uma opção válida!");
    }
    return 0;
}