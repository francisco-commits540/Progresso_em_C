#include "meu_banco.h"

int main(void) {
    Banco banco;
    int opcao = 0;

    inicializarBanco(&banco);

    limparTela();
    printf("===== CADASTRO INICIAL DE CLIENTES =====\n\n");
    cadastrarClientes(&banco);
    pausar();

    do {
        limparTela();
        printf("===== CARTEIRA DIGITAL =====\n\n");
        printf("Banco: %s\n\n", banco.aberto ? "ABERTO" : "FECHADO");
        printf("1. Abrir o banco\n");
        printf("2. Consultar historico\n");
        printf("3. Efetuar sorteio\n");
        printf("4. Sair\n");
        printf("\nEscolha: ");
        if (scanf("%d", &opcao) != 1) opcao = 0;
        limparEntrada();

        switch (opcao) {
            case 1:
                banco.aberto = 1;
                menuOperacoes(&banco);
                break;
            case 2:
                limparTela();
                if (!banco.aberto)
                    printf("O banco precisa estar aberto!\n");
                else
                    consultarHistorico(&banco);
                pausar();
                break;
            case 3:
                limparTela();
                printf("===== SORTEIO =====\n\n");
                if (!banco.aberto)
                    printf("O banco precisa estar aberto!\n");
                else
                    efetuarSorteio(&banco);
                pausar();
                break;
            case 4:
                limparTela();
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                pausar();
        }
    } while (opcao != 4);

    liberarBanco(&banco);
    return 0;
}
