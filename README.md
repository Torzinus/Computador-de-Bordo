# Computador-de-Bordo

Programa em C para simulação de escalonamento de tarefas utilizando os algoritmos **Rate Monotonic (RATE)** e **Earliest Deadline First (EDF)**.

## Arquivos

- `main.c` — responsável pela execução principal do programa, leitura e validação do arquivo de entrada, criação dos arquivos de saída e gerenciamento da memória.
- `escalonador.c` — implementa a simulação dos escalonadores RATE e EDF, além da geração do log de execução e do resumo das tarefas.
- `escalonador.h` — contém as estruturas e declarações utilizadas pelo escalonador.
- `Makefile` — automatiza a compilação e limpeza dos arquivos gerados.

## Compilação

Para compilar o programa, execute no terminal:

```bash
make clean
make
```

## Execução

O programa recebe dois argumentos: o algoritmo de escalonamento e o arquivo de entrada.

Para utilizar o **RATE**:

```bash
./scheduler rate entrada.txt
```

Para utilizar o **EDF**:

```bash
./scheduler edf entrada.txt
```

A execução gera um arquivo de saída correspondente ao algoritmo utilizado:

- `rate_hcs4.out`
- `edf_hcs4.out`

## Testes

Os testes podem ser realizados utilizando arquivos de entrada contendo o tempo total de simulação e as informações das tarefas.

Exemplo:

```text
100
ATT 20 12 8
NAV 50 30 15
```

Após a compilação, execute os dois algoritmos para comparar os resultados:

```bash
./scheduler rate entrada.txt
./scheduler edf entrada.txt
```

Os arquivos de saída apresentam o log da execução e a quantidade de tarefas que tiveram seus deadlines perdidos, foram concluídas ou foram interrompidas ao final da simulação.

## Sistema Operacional

O programa foi implementado e testado no **Ubuntu (Linux)**, utilizando o compilador **GCC**.