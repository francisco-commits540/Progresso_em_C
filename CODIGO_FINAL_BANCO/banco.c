#include "meu_banco.h"

void limparEntrada(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) { }
}

void limparTela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar(void) {
    printf("\nPressione ENTER para continuar...");
    limparEntrada();
}

void inicializarBanco(Banco *banco) {
    banco->clientes = NULL;
    banco->quantidadeClientes = 0;
    banco->proximoNumeroConta = 1000;
    banco->aberto = 0;
    banco->sorteioRealizado = 0;
    banco->indiceVencedor = -1;
    banco->valorPremio = 0.0;
}

int buscarConta(Cliente *cliente, int tipo) {
    int i;
    for (i = 0; i < cliente->quantidadeContas; i++)
        if (cliente->contas[i].tipo == tipo)
            return i;
    return -1;
}

double saldoTotalCliente(Cliente *cliente) {
    double total = 0;
    int i;
    for (i = 0; i < cliente->quantidadeContas; i++)
        total += cliente->contas[i].saldo;
    return total;
}

double saldoTotalBanco(Banco *banco) {
    double total = 0;
    int i;
    for (i = 0; i < banco->quantidadeClientes; i++)
        total += saldoTotalCliente(&banco->clientes[i]);
    return total;
}

void registrarMovimento(Cliente *cliente, const char *descricao, double valor) {
    Movimento *novo;
    novo = realloc(cliente->historico,
                   (cliente->quantidadeMovimentos + 1) * sizeof(Movimento));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para o historico.\n");
        return;
    }
    cliente->historico = novo;
    strcpy(cliente->historico[cliente->quantidadeMovimentos].descricao, descricao);
    cliente->historico[cliente->quantidadeMovimentos].valor = valor;
    cliente->quantidadeMovimentos++;
}

void cadastrarClientes(Banco *banco) {
    int quantidade, i, contas, tipo, j;
    Cliente *novo;

    printf("Quantos clientes deseja cadastrar? ");
    scanf("%d", &quantidade);
    limparEntrada();

    if (quantidade <= 0) {
        printf("Quantidade invalida. O sistema iniciara sem clientes.\n");
        return;
    }

    novo = malloc(quantidade * sizeof(Cliente));
    if (novo == NULL) {
        printf("Erro de memoria!\n");
        return;
    }
    banco->clientes = novo;
    banco->quantidadeClientes = quantidade;

    for (i = 0; i < quantidade; i++) {
        Cliente *cliente = &banco->clientes[i];
        cliente->quantidadeContas = 0;
        cliente->possuiEmprestimo = 0;
        cliente->historico = NULL;
        cliente->quantidadeMovimentos = 0;

        printf("\nNome do cliente %d: ", i + 1);
        fgets(cliente->nome, sizeof(cliente->nome), stdin);
        cliente->nome[strcspn(cliente->nome, "\n")] = '\0';

        printf("Quantas contas deseja criar (1 a 3)? ");
        scanf("%d", &contas);
        limparEntrada();
        if (contas < 1) contas = 1;
        if (contas > MAX_CONTAS) contas = MAX_CONTAS;

        for (j = 0; j < contas; j++) {
            printf("Tipo da conta (1-Corrente, 2-Salario, 3-Poupanca): ");
            scanf("%d", &tipo);
            limparEntrada();

            if (tipo < CORRENTE || tipo > POUPANCA) {
                printf("Tipo invalido. Conta nao criada.\n");
                continue;
            }
            if (buscarConta(cliente, tipo) != -1) {
                printf("Esse cliente ja possui esse tipo de conta.\n");
                continue;
            }
            if ((tipo == CORRENTE && buscarConta(cliente, SALARIO) != -1) ||
                (tipo == SALARIO && buscarConta(cliente, CORRENTE) != -1)) {
                printf("Conta corrente e conta-salario nao podem coexistir.\n");
                continue;
            }

            cliente->contas[cliente->quantidadeContas].numero = banco->proximoNumeroConta++;
            cliente->contas[cliente->quantidadeContas].tipo = tipo;
            cliente->contas[cliente->quantidadeContas].saldo = 0.0;
            cliente->contas[cliente->quantidadeContas].possuiTitulo = 0;
            cliente->quantidadeContas++;

            printf("Conta criada: %04d-%02d | saldo R$ 0,00\n",
                   cliente->contas[cliente->quantidadeContas - 1].numero, tipo);
        }
    }
}

int clienteAptoEmprestimo(Cliente *cliente) {
    /* Exige conta corrente + conta-poupanca COM saldo positivo. */
    int poupanca = buscarConta(cliente, POUPANCA);
    return poupanca != -1 &&
           cliente->contas[poupanca].saldo > 0 &&
           buscarConta(cliente, CORRENTE) != -1 &&
           !cliente->possuiEmprestimo;
}

double limiteEmprestimo(Cliente *cliente) {
    return saldoTotalCliente(cliente) * 10.0 * 0.25;
}

int clienteAptoTitulo(Cliente *cliente) {
    int indice = buscarConta(cliente, SALARIO);
    if (indice == -1) return 0;
    return cliente->contas[indice].saldo >= 1000.0 &&
           cliente->contas[indice].saldo <= 1500.0 &&
           !cliente->contas[indice].possuiTitulo;
}

int clienteTemTitulo(Cliente *cliente) {
    int i;
    for (i = 0; i < cliente->quantidadeContas; i++)
        if (cliente->contas[i].possuiTitulo) return 1;
    return 0;
}

void depositar(Cliente *cliente, int indiceConta, double valor) {
    if (valor <= 0) {
        printf("Valor deve ser maior que zero.\n");
        return;
    }
    cliente->contas[indiceConta].saldo += valor;
    registrarMovimento(cliente, "Deposito", valor);
    printf("Deposito realizado.\n");
}

void sacar(Cliente *cliente, int indiceConta, double valor) {
    if (valor <= 0) {
        printf("Valor deve ser maior que zero.\n");
        return;
    }
    cliente->contas[indiceConta].saldo -= valor;
    registrarMovimento(cliente, "Saque", -valor);
    printf("Saque realizado. (Saldo negativo permitido para testar o alerta.)\n");
}

void solicitarEmprestimo(Cliente *cliente) {
    double valor;
    int conta;
    if (!clienteAptoEmprestimo(cliente)) {
        printf("Cliente nao atende aos requisitos (conta corrente + saldo na poupanca)\n");
        printf("ou ja possui emprestimo.\n");
        return;
    }
    valor = limiteEmprestimo(cliente);
    printf("Emprestimo permitido: R$ %.2f\n", valor);
    if (valor <= 0) {
        printf("Saldo total precisa ser positivo para gerar limite.\n");
        return;
    }
    conta = buscarConta(cliente, CORRENTE);
    cliente->contas[conta].saldo += valor;
    cliente->possuiEmprestimo = 1;
    registrarMovimento(cliente, "Emprestimo concedido", valor);
    printf("Emprestimo concedido e creditado na conta corrente.\n");
}

void comprarTitulo(Cliente *cliente) {
    int conta = buscarConta(cliente, SALARIO);
    if (conta == -1) {
        printf("Cliente nao possui conta-salario.\n");
        return;
    }
    if (!clienteAptoTitulo(cliente)) {
        printf("Nao apto: saldo deve estar entre R$ 1.000,00 e R$ 1.500,00 e nao ter titulo.\n");
        return;
    }
    cliente->contas[conta].possuiTitulo = 1;
    registrarMovimento(cliente, "Compra de titulo de capitalizacao", 0);
    printf("Titulo adquirido!\n");
}

void mostrarAlertas(Banco *banco) {
    int i, conta;
    for (i = 0; i < banco->quantidadeClientes; i++) {
        conta = buscarConta(&banco->clientes[i], CORRENTE);
        if (conta != -1 && banco->clientes[i].contas[conta].saldo < 0)
            printf("ALERTA: %s esta com saldo negativo (R$ %.2f).\n",
                   banco->clientes[i].nome,
                   banco->clientes[i].contas[conta].saldo);
    }
    printf("\n");
}

void menuOperacoes(Banco *banco) {
    int opcao = 0, clienteIndex, contaIndex, tipo;
    double valor;
    Cliente *cliente;

    do {
        limparTela();
        printf("===== OPERACOES DO BANCO =====\n\n");
        mostrarAlertas(banco);
        printf("1. Depositar\n");
        printf("2. Sacar\n");
        printf("3. Solicitar emprestimo\n");
        printf("4. Comprar titulo\n");
        printf("5. Voltar ao menu principal\n");
        printf("\nOpcao: ");
        if (scanf("%d", &opcao) != 1) opcao = 0;
        limparEntrada();

        if (opcao == 5) break;

        if (opcao < 1 || opcao > 4) {
            printf("\nOpcao invalida.\n");
            pausar();
            continue;
        }

        printf("Numero do cliente (1 a %d): ", banco->quantidadeClientes);
        if (scanf("%d", &clienteIndex) != 1) clienteIndex = 0;
        limparEntrada();
        clienteIndex--;

        if (clienteIndex < 0 || clienteIndex >= banco->quantidadeClientes) {
            printf("\nCliente invalido.\n");
            pausar();
            continue;
        }
        cliente = &banco->clientes[clienteIndex];
        printf("\n");

        if (opcao == 3) {
            solicitarEmprestimo(cliente);
        } else if (opcao == 4) {
            comprarTitulo(cliente);
        } else {
            printf("Tipo de conta (1-Corrente, 2-Salario, 3-Poupanca): ");
            if (scanf("%d", &tipo) != 1) tipo = 0;
            limparEntrada();
            contaIndex = buscarConta(cliente, tipo);
            if (contaIndex == -1) {
                printf("\nCliente nao possui essa conta.\n");
            } else {
                printf("Valor: R$ ");
                if (scanf("%lf", &valor) != 1) valor = 0;
                limparEntrada();
                printf("\n");
                if (opcao == 1) depositar(cliente, contaIndex, valor);
                else sacar(cliente, contaIndex, valor);
            }
        }
        pausar();
    } while (opcao != 5);
}

void consultarHistorico(Banco *banco) {
    int i, j, conta, tipo;
    printf("===== HISTORICO DO BANCO =====\n\n== Saldo Total do banco ==\n");
    printf("%d | R$ %.2f\n", banco->quantidadeClientes, saldoTotalBanco(banco));

    printf("\n== Clientes Aptos a Emprestimos ==\n");
    for (i = 0; i < banco->quantidadeClientes; i++) {
        Cliente *cliente = &banco->clientes[i];
        if (clienteAptoEmprestimo(cliente))
            printf("%s | ", cliente->nome),
            printf("%04d-%02d | R$ %.2f\n",
                    cliente->contas[buscarConta(cliente, CORRENTE)].numero,
                    CORRENTE, limiteEmprestimo(cliente));
    }

    printf("\n== Clientes com Saldo Negativo na Conta Corrente ==\n");
    for (i = 0; i < banco->quantidadeClientes; i++) {
        Cliente *cliente = &banco->clientes[i];
        conta = buscarConta(cliente, CORRENTE);
        if (conta != -1 && cliente->contas[conta].saldo < 0)
            printf("%s | %04d-%02d | R$ %.2f\n", cliente->nome,
                    cliente->contas[conta].numero, CORRENTE,
                    cliente->contas[conta].saldo);
    }

    printf("\n== Clientes Aptos a Compra de Titulos ==\n");
    for (i = 0; i < banco->quantidadeClientes; i++) {
        Cliente *cliente = &banco->clientes[i];
        conta = buscarConta(cliente, SALARIO);
        if (clienteAptoTitulo(cliente))
            printf("%s | %04d-%02d | R$ %.2f\n", cliente->nome,
                    cliente->contas[conta].numero, SALARIO,
                    cliente->contas[conta].saldo);
    }

    printf("\n== Clientes Contemplados no Sorteio ==\n");
    if (banco->sorteioRealizado && banco->indiceVencedor >= 0) {
        Cliente *vencedor = &banco->clientes[banco->indiceVencedor];
        conta = buscarConta(vencedor, SALARIO);
        if (conta == -1) conta = 0;
        printf("%s | %04d-%02d | R$ %.2f\n", vencedor->nome,
                vencedor->contas[conta].numero,
                vencedor->contas[conta].tipo, banco->valorPremio);
    } else {
        printf("Nenhum sorteio realizado.\n");
    }

    printf("\n== Movimentacoes dos Clientes ==\n");
    for (i = 0; i < banco->quantidadeClientes; i++) {
        Cliente *cliente = &banco->clientes[i];
        printf("\n%s:\n", cliente->nome);
        if (cliente->quantidadeMovimentos == 0)
            printf("Sem movimentacoes.\n");
        for (j = 0; j < cliente->quantidadeMovimentos; j++)
            printf("- %s | R$ %.2f\n",
                    cliente->historico[j].descricao,
                    cliente->historico[j].valor);
        for (j = 0; j < cliente->quantidadeContas; j++) {
            tipo = cliente->contas[j].tipo;
            printf("Conta %04d-%02d: saldo R$ %.2f | Titulo: %s\n",
                    cliente->contas[j].numero, tipo, cliente->contas[j].saldo,
                    cliente->contas[j].possuiTitulo ? "Sim" : "Nao");
        }
    }
}

int fibonacciModulo(int n, int modulo) {
    int a = 0, b = 1, proximo, i;
    if (modulo <= 0) return 0;
    if (n <= 0) return 0;
    for (i = 2; i <= n; i++) {
        proximo = (a + b) % modulo;
        a = b;
        b = proximo;
    }
    return b % modulo;
}

void efetuarSorteio(Banco *banco) {
    int indices[5], quantos = 0, i, j, escolhido, temp, conta;
    int candidatos[5], numeroCandidatos = 0;
    double premio;
    time_t agora;

    if (banco->quantidadeClientes < 5) {
        printf("Sorteio exige pelo menos cinco clientes cadastrados.\n");
        return;
    }

    /* Seleciona os cinco maiores saldos usando ordenacao simples. */
    for (i = 0; i < banco->quantidadeClientes; i++) {
        escolhido = -1;
        for (j = 0; j < quantos; j++)
            if (saldoTotalCliente(&banco->clientes[i]) >
                saldoTotalCliente(&banco->clientes[indices[j]])) {
                escolhido = j;
                break;
            }
        if (quantos < 5) {
            indices[quantos++] = i;
        } else if (escolhido != -1) {
            for (j = 4; j > escolhido; j--) indices[j] = indices[j - 1];
            indices[escolhido] = i;
        }
        /* Reordena os cinco selecionados do maior para o menor. */
        for (j = 0; j < quantos - 1; j++) {
            int k;
            for (k = j + 1; k < quantos; k++) {
                if (saldoTotalCliente(&banco->clientes[indices[k]]) >
                    saldoTotalCliente(&banco->clientes[indices[j]])) {
                    temp = indices[j]; indices[j] = indices[k]; indices[k] = temp;
                }
            }
        }
    }

    for (i = 0; i < 5; i++)
        if (clienteTemTitulo(&banco->clientes[indices[i]]))
            candidatos[numeroCandidatos++] = indices[i];

    if (numeroCandidatos == 0) {
        printf("Nenhum dos cinco maiores saldos possui titulo. Sorteio cancelado.\n");
        return;
    }

    /* Fibonacci: usa o horario como indice e reduz o resultado ao grupo elegivel. */
    agora = time(NULL);
    escolhido = fibonacciModulo((int)(agora % 20) + 2, numeroCandidatos);
    banco->indiceVencedor = candidatos[escolhido];

    /* O premio vai para a conta-salario, onde fica o titulo de capitalizacao. */
    Cliente *vencedor = &banco->clientes[banco->indiceVencedor];
    conta = buscarConta(vencedor, SALARIO);
    if (conta == -1) {
        printf("Erro: vencedor sem conta-salario.\n");
        return;
    }
    premio = vencedor->contas[conta].saldo * 10.0;
    vencedor->contas[conta].saldo += premio;
    banco->valorPremio = premio;
    banco->sorteioRealizado = 1;

    registrarMovimento(vencedor, "Premio do sorteio", premio);
    printf("\nSORTEIO REALIZADO!\n");
    printf("Vencedor: %s\n", vencedor->nome);
    printf("Conta creditada: %04d-%02d (conta-salario)\n",
            vencedor->contas[conta].numero, SALARIO);
    printf("Premio: R$ %.2f (10 vezes o saldo da conta-salario antes do premio)\n", premio);
}

void liberarBanco(Banco *banco) {
    int i;
    for (i = 0; i < banco->quantidadeClientes; i++)
        free(banco->clientes[i].historico);
    free(banco->clientes);
    banco->clientes = NULL;
    banco->quantidadeClientes = 0;
}
