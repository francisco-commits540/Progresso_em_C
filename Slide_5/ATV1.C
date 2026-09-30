#include <stdio.h>

int main()
{

    int i = 0;
    float consumo;
    float consumo_t = 0;

    /* Repete para 5 moradores */
    while (i < 5)
    {

        /* Recebe o consumo do morador */
        printf("Digite o consumo mensal do morador: ");
        scanf("%f", &consumo);

        /* Verifica se passou de 20 m³ */
        if (consumo > 20)
        {
            printf("Morador consumiu acima da média! \n");
        }

        /* Soma o consumo ao total */
        consumo_t = consumo + consumo_t;

        /* Passa para o próximo morador */
        i++;
    }

    /* Calcula e mostra a média */
    printf("Consumo médio geral: %.2f m³", consumo_t / 5);

    return 0;
}
