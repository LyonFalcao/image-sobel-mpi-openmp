# Processamento de Imagens com Sobel utilizando MPI e OpenMP

## Sobre o projeto

Este projeto implementa o processamento de imagens utilizando o operador de Sobel para detecção de bordas, combinando técnicas de paralelismo distribuído e paralelismo em memória compartilhada.

A aplicação utiliza:

* **MPI (Message Passing Interface)** para distribuição do processamento entre diferentes processos e máquinas;
* **OpenMP** para paralelização interna utilizando múltiplas threads em cada processo;
* Linguagem **C** para implementação do processamento.

O objetivo é demonstrar a aplicação de computação paralela no processamento de imagens em escala de cinza, utilizando uma arquitetura híbrida MPI + OpenMP.

---

## Funcionamento

O processamento segue as seguintes etapas:

1. Leitura da imagem de entrada no formato PGM (Portable Gray Map);
2. Distribuição das linhas da imagem entre os processos MPI;
3. Aplicação do filtro Sobel em paralelo utilizando threads OpenMP;
4. Reunião dos blocos processados;
5. Geração da imagem final com as bordas detectadas.

A divisão da imagem é realizada horizontalmente, onde cada processo MPI recebe uma parte das linhas da imagem para processamento independente.

---

## Estrutura do projeto

```
image-sobel-mpi-openmp/
│
├── images/
│   └── entrada.pgm
│
├── output/
│   └── sobel_mpi.pgm
│
├── src/
│   ├── main_mpi.c
│   ├── image.c
│   ├── image.h
│   ├── sobel_block.c
│   ├── sobel_block.h
│   ├── mpi_utils.c
│   └── mpi_utils.h
│
├── Makefile
└── README.md
```

---

## Requisitos

Para compilar e executar o projeto são necessários:

* Compilador C;
* Biblioteca MPI (OpenMPI);
* Suporte a OpenMP;
* Sistema Linux ou ambiente compatível.

---

## Compilação

Na raiz do projeto:

```bash
make
```

O comando irá gerar o executável:

```
imageproc_mpi
```

Para limpar arquivos gerados:

```bash
make clean
```

---

## Execução

A aplicação recebe a imagem de entrada como argumento.

Exemplo utilizando três processos MPI:

```bash
export OMP_NUM_THREADS=4

mpirun \
-np 3 \
--host master,worker-1,worker-2 \
./imageproc_mpi images/entrada.pgm
```

Onde:

* `-np 3` define a quantidade de processos MPI;
* `--host` define os nós utilizados no processamento distribuído;
* `OMP_NUM_THREADS=4` define a quantidade de threads OpenMP utilizadas por processo.

---

## Entrada de dados

A imagem utilizada como entrada deve estar no formato:

```
PGM P5
```

e em escala de cinza.

Exemplo:

```
images/entrada.pgm
```

A aplicação permite utilizar diferentes imagens sem necessidade de alteração no código-fonte.

---

## Testes realizados

O projeto foi validado utilizando a plataforma Xivoco com processamento distribuído entre três nós:

```
master
worker-1
worker-2
```

Configuração utilizada:

```
Processos MPI: 3
Threads OpenMP por processo: 4
```

Imagem utilizada:

```
Resolução: 3456 x 5184 pixels
Formato: PGM (P5)
```

Execução realizada:

```bash
export OMP_NUM_THREADS=4

mpirun \
-np 3 \
--host master,worker-1,worker-2 \
./imageproc_mpi images/entrada.pgm
```

Resultado:

```
Imagem: 3456x5184
Processos: 3
Imagem salva em output/sobel_mpi.pgm
```

---

## Tecnologias utilizadas

* C
* MPI / OpenMPI
* OpenMP
* Linux
* Git e GitHub
* Xivoco (ambiente de execução distribuída)

---

## Autores

Projeto desenvolvido como parte de estudos em Introdução ao Processamento Paralelo e Pistribuído

```
Lyon Falcão
```
