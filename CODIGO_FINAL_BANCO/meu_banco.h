#ifndef MEU_BANCO_H
#define MEU_BANCO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CORRENTE 1
#define SALARIO 2
#define POUPANCA 3
#define MAX_CONTAS 3

typedef struct {
    int numero;
    int tipo;
    double saldo;
    int possuiTitulo;
} Conta;

typedef struct {
    char descricao[120];
    double valor;
} Movimento;

typedef struct {
    char nome[100];
    Conta contas[MAX_CONTAS];
    int quantidadeContas;
    int possuiEmprestimo;
    Movimento *historico;
    int quantidadeMovimentos;
} Cliente;

typedef struct {
    Cliente *clientes;
    int quantidadeClientes;
    int proximoNumeroConta;
    int aberto;
    int sorteioRealizado;
    int indiceVencedor;
    double valorPremio;
} Banco;

void limparEntrada(void);

void limparTela(void);

void pausar(void);

void inicializarBanco(Banco *banco);

void cadastrarClientes(Banco *banco);

void menuOperacoes(Banco *banco);

void consultarHistorico(Banco *banco);

void efetuarSorteio(Banco *banco);

void liberarBanco(Banco *banco);

int buscarConta(Cliente *cliente, int tipo);

double saldoTotalCliente(Cliente *cliente);

double saldoTotalBanco(Banco *banco);

double limiteEmprestimo(Cliente *cliente);

int clienteAptoEmprestimo(Cliente *cliente);

int clienteAptoTitulo(Cliente *cliente);

int clienteTemTitulo(Cliente *cliente);

void registrarMovimento(Cliente *cliente, const char *descricao, double valor);

void depositar(Cliente *cliente, int indiceConta, double valor);

void sacar(Cliente *cliente, int indiceConta, double valor);

void solicitarEmprestimo(Cliente *cliente);

void comprarTitulo(Cliente *cliente);

void mostrarAlertas(Banco *banco);

int fibonacciModulo(int n, int modulo);

#endif
