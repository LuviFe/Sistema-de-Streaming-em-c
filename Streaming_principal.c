#include <stdio.h>
#include <string.h>

/*   FUNCIONALIDADES EXTRAS PARA ADICIONAR:
    -Conectar funções cancela_contrato e gerar_fatura
*/

//////////////////////////////////////////
//DECLARAÇÃO DAS STRUCTS, ENUMS E UNIONS//
//////////////////////////////////////////

//////////////
//AUXILIARES//
//////////////

//ENUMERAÇÕES//

typedef enum e_genero
{
    AVENTURA,COMEDIA,DRAMA,TERROR,ACAO,ROMANCE
}t_genero;

typedef enum e_classificacoes
{
    LIVRE,MAIS10,MAIS12,MAIS14,MAIS16,MAIS18
}t_classificacoes;

typedef enum e_tipo_plano
{
    BASICO,PREMIUM
}t_tipo_plano;

typedef enum e_tipo_pagamento
{
    DEBITO,CREDITO
}t_tipo_pagamento;

typedef enum e_lista_filmes
{
    GENERO,CLASSIFICACAO
}t_lista_filmes;

typedef enum e_status
{
    INATIVO,ATIVO
}t_status;

//STRUCTS//

typedef struct s_basico
{
    int qnt_filmes;
    float valor_base;
    float valor_excedente;
}t_basico;

typedef struct s_premium
{
    float valor_base;
}t_premium;

typedef struct s_credito
{
    int num;
}t_credito;

typedef struct s_debito
{
    int agencia;
    int conta;
}t_debito;

typedef struct s_data
{
    int dia;
    int mes;
}t_data;

typedef struct s_ordenacao_generos
{
    int id;
    int cont;
}t_ordenacao_generos;

//UNIÕES//

typedef union u_dados_cartoes
{
    t_credito credito;
    t_debito debito;
}t_dados_cartoes;

//////////////
//PRINCIPAIS//
//////////////
typedef struct u_strings_enums
{
    char genero[10];
    char classificacao[10];
    char status[10];
}t_strings_enums;


typedef struct s_clientes
{
    int cpf;
    char nome[50];
    char email[50];
    char telefone[15];
    t_status status;
    t_strings_enums status_s;
}t_clientes;

typedef struct s_filme
{
    int cod;
    char nome[50];
    t_genero genero;
    t_classificacoes classificacoes;
    t_strings_enums genero_s;
    t_strings_enums classificacoes_s;
}t_filme;

typedef struct s_planos
{
    t_basico basico;
    t_premium premium;
}t_planos;

typedef struct s_contrato
{
    int cpf;
    t_tipo_plano tipo_plano;
    t_data data_contratacao;
    t_data data_cancelamento;
    t_tipo_pagamento tipo_pagamento;
    t_dados_cartoes dados_cartoes;
}t_contrato;

typedef struct s_historico
{
    int cod_filme;
    t_data data;
    int cpf;
}t_historico;
//////////////////////////
//DECLARAÇÃO DAS FUNÇÕES//
//////////////////////////

//Cadastros//
int cadastra_cliente(t_clientes *clientes, int *cont, int tam); //ok
int cadastra_filme(t_filme *filmes, int *cont, int tam); //ok
void cadastra_basico(t_planos *planos); //ok
void cadastra_premium(t_planos *planos); //ok
int cadastra_contrato(t_contrato *contratos, int *cont, int num, t_clientes *clientes, int cont_cli, int mes); //ok

//Outras//
int carregar_filme(t_historico historico[][30],int *cont_hist, int *cont_cli_hist, t_clientes *clientes,int cont_cli,t_filme *filmes,int cont_filmes,t_contrato *contratos, int cont_cont, t_planos planos,int mes);
int cancela_contrato(t_contrato *contratos, t_clientes *clientes, int cont_cli, int cont_cont,t_historico historico[][30], int cont_cli_hist,int *cont_hist, t_planos planos,int mes);
int gerar_fatura(t_historico historico[][30],int cont_cli_hist,int *cont_hist, t_clientes *clientes,int cont_cli, t_contrato *contratos,int cont_cont, t_filme *filmes,int cont_filmes, t_planos planos,int *mes);
int frequencia_filme(t_historico historico[][30],int *cont_hist, int cont_cli_hist,t_filme *filmes,int cont_filmes); //ok
int recomenda_filme(t_historico historico[][30],int cont_cli_hist,int *cont_hist, t_filme *filmes, int cont_filmes, t_clientes *clientes,int cont_cli);
//Buscadoras//
int busca_cliente(t_clientes *clientes, int chave, int tam); //ok
int busca_filme(t_filme *filmes, int chave, int tam); //ok
int busca_contrato(t_contrato *contratos, int chave, int tam); //ok
int busca_historico(t_historico historico[][30],int chave,int tam); //ok
//listagens//
int lista_cliente(t_clientes *clientes, int cont_cli);
int lista_historico(t_historico historicos[][30], int cont_cli_hist, int *cont_hist, t_clientes *clientes, int cont_cli,t_filme *filmes,int cont_filmes);
int lista_excesso(t_historico historico[][30],int cont_cli_hist,int *cont_hist,t_clientes *clientes, int cont_cli, t_contrato *contratos, int cont_cont,t_planos planos);
//////////////////////////
//////////////////////////
int main()
{
    const int num_cli = 10;
    const int num_filmes = 10;
    const int filmes_mes = 30;

    int op, ret,i; //auxiliares
    int cont_cli=0, cont_filmes=0,cont_cont=0;//contadoras
    int cont_hist[num_cli],cont_cli_hist = 0; //contador vetor
    int mes = 1; //Mês vigente

    for(i=0;i<num_cli;i++) //Zera o vetor contador do histórico
        cont_hist[i] = 0;
    

    t_clientes clientes[num_cli];
    t_filme filmes[num_filmes];
    t_planos planos;
    t_contrato contratos[num_cli];
    t_historico historico[num_cli][filmes_mes];

    /*printf("1: Cadastro de cliente\n");
      printf("2: Cadastrar filme\n");
      printf("3: Cadastrar plano básico\n");
      printf("4: Cadastrar plano premium\n");
      printf("5: Cadastrar contrato\n");
      printf("6: Carregar filme\n");
      printf("7: Cancelar contrato\n");
      printf("8: Gerar fatura\n");
      printf("9: Listar os dados de um dado cliente\n");
      printf("10: Listar o histórico de um dado cliente\n");
      printf("11: Listar clientes que excederam a cota mensal\n");
      printf("12: Frequência de um dado filme\n");
      printf("13: Recomendar filme\n");
      printf("0: Sair\n");
    */
    
    do 
    {
        scanf("%d",&op);

        switch(op)
        {
            case 1: 
                {
                    ret = cadastra_cliente(clientes,&cont_cli,num_cli);

                    if(ret == 1)
                    printf("ERRO: Numero maximo de clientes no sistema atingido\n");

                    if(ret == 2)
                    printf("ERRO: CPF do cliente ja cadastrado\n");

                    if(ret == 3)
                    printf("Cliente cadastrado com sucesso\n");

                    break;
                }

            case 2:
                {
                    ret = cadastra_filme(filmes,&cont_filmes,num_filmes);

                    if(ret == 1)
                    printf("ERRO: Numero maximo de filmes no sistema atingido\n");

                    if(ret == 2)
                    printf("Filme cadastrado com sucesso\n");

                    break;
                }
            case 3:
                {
                    cadastra_basico(&planos);
                    break;
                }
            case 4:
                {
                    cadastra_premium(&planos);
                    break;
                }
            case 5:
                { 
                    ret = cadastra_contrato(contratos,&cont_cont,num_cli,clientes,cont_cli,mes);

                    if(ret == 1)
                    printf("ERRO: Numero maximo de contratos no sistema atingido\n");

                    if(ret == 2)
                    printf("ERRO: Nenhum cliente cadastrado no sistema\n");

                    if(ret == 3)
                    printf("ERRO: Cliente nao cadastrado\n");

                    if(ret == 4)
                    printf("ERRO: Cliente com contrato existente\n");

                    if(ret == 5)
                    printf("Contrato cadastrado com sucesso\n");

                    break;
                }
            case 6:
                {  
                    ret = carregar_filme(historico,cont_hist,&cont_cli_hist,clientes,cont_cli,filmes,cont_filmes,contratos,cont_cont,planos,mes);

                    if(ret == 1)
                    printf("ERRO: Nenhum cliente cadastrado no sistema\n");

                    if(ret == 2)
                    printf("ERRO: Cliente nao cadastrado\n");

                    if(ret == 3)
                    printf("ERRO: Cliente nao ativo\n");

                    if(ret == 4)
                    printf("ERRO: Filme nao encontrado\n");

                    if(ret == 5)
                    printf("ERRO: Taxa adicional negada\n");

                    if(ret == 6)
                    printf("Filme carregado com sucesso\n");

                    break;
                }
            case 7:
                {
                    ret = cancela_contrato(contratos,clientes,cont_cli,cont_cont,historico,cont_cli_hist,cont_hist,planos,mes);

                    if(ret == 1)
                    printf("ERRO: Cliente nao cadastrado\n");

                    if(ret == 2)
                    printf("ERRO: Cliente inativo\n");

                    if(ret == 3)
                    printf("ERRO: Nenhum contrato cadastrado no sistema\n");

                    if(ret == 4)
                    printf("ERRO: Data de cancelamente anteiror a data de contratacao\n");

                    break;
                }
            case 8:
                {
                    ret = gerar_fatura(historico,cont_cli_hist,cont_hist,clientes,cont_cli,contratos,cont_cont,filmes,cont_filmes,planos,&mes);

                    if(ret == 1)
                    printf("ERRO: Nenhum contrato cadastrado no sistema\n");

                    if(ret == 2)
                    printf("ERRO: Cliente nao cadastrado\n");

                    if(ret == 3)
                    printf("ERRO: Cliente nao possui contrato\n");

                    if(ret==5)
                    printf("ERRO: Nenhum cliente cadastrado no sistema\n");

                    break;
                }
            case 9:
                {
                    ret = lista_cliente(clientes,cont_cli);

                    if(ret==1)
                    printf("ERRO: Nenhum cliente cadastrado no sistema\n");

                    if(ret==2)
                    printf("ERRO: Cliente nao cadastrado\n");

                    break;
                }
            case 10:
                {
                    ret = lista_historico(historico,cont_cli_hist,cont_hist,clientes,cont_cli,filmes,cont_filmes);
                    
                    if(ret==1)
                    printf("ERRO: Nenhum cliente cadastrado no sistema\n");

                    if(ret==2)
                    printf("ERRO: Cliente nao cadastrado\n");

                    if(ret==3)
                    printf("ERRO: Nenhum filme assistido\n");

                    break;
                }
            case 11:
                {
                    ret = lista_excesso(historico,cont_cli_hist,cont_hist,clientes,cont_cli,contratos,cont_cont,planos);

                    if(!ret)
                    printf("ERRO: Nenhum cliente excedente\n");

                    break;
                }
            case 12:
                {
                    ret = frequencia_filme(historico,cont_hist,cont_cli_hist,filmes,cont_filmes);

                    if(ret==1)
                    printf("ERRO: Nenhum filme cadastrado no sistema\n");

                    if(ret==2)
                    printf("ERRO: Nenhum filme assistido\n");

                    if(ret==3)
                    printf("ERRO: Codigo invalido\n");

                    break;
                }
            case 13:
                {
                    ret = recomenda_filme(historico,cont_cli_hist,cont_hist,filmes,cont_filmes,clientes,cont_cli);

                    if(ret==1)
                    printf("ERRO: Nenhum cliente cadastrado no sistema\n");

                    if(ret==2)
                    printf("ERRO: Cliente nao cadastrado\n");

                    if(ret==3)
                    printf("ERRO: Cliente nao ativo\n");

                    if(ret==4)
                    printf("ERRO: Nenhum filme assistido\n");

                    if(ret==5)
                    printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");

                    break;
                }
            case 0:
                {
                    printf("Finalizando programa...");
                    break;
                }

            default: printf("ERRO: Opcao invalida\n");
        }
    }while(op != 0);
    

}

///////////
//FUNÇÕES//
///////////

int cadastra_cliente(t_clientes *clientes, int *cont, int tam)
{
    int ret;

    if(*cont >= tam)
    return 1;

    scanf("%d",&clientes[*cont].cpf); //Verifica nos cadastrados até agora

    ret = busca_cliente(clientes,clientes[*cont].cpf,*cont);

    if(ret != 10)
    return 2;

    scanf(" %[^\n]%*c", clientes[*cont].nome);
    scanf(" %s", clientes[*cont].email);
    scanf(" %s", clientes[*cont].telefone);
    clientes[*cont].status = INATIVO; //Enum
    strcpy(clientes[*cont].status_s.status,"inativo"); //Inativo

    *cont = *cont + 1;

    return 3;
}

int cadastra_filme(t_filme *filmes, int *cont, int tam)
{
    int cond=0;

    if(*cont == 0)
    filmes[0].cod = 1001; //Definição do código do primeiro filme no vetor

    if(*cont >= tam)
    return 1;

    if(*cont != 0)
    filmes[*cont].cod = filmes[*cont-1].cod + 1; //incremento do código do vetor

    scanf(" %[^\n]%*c",filmes[*cont].nome);
    do
    {
        scanf("%u",&filmes[*cont].genero);
        if(filmes[*cont].genero != AVENTURA && filmes[*cont].genero != COMEDIA 
          && filmes[*cont].genero != DRAMA && filmes[*cont].genero != TERROR
          && filmes[*cont].genero != ACAO && filmes[*cont].genero != ROMANCE)
            printf("ERRO: Genero invalido\n");
            else cond = 1;       
    }while(!cond);

    switch(filmes[*cont].genero)
    {
        case AVENTURA: strcpy(filmes[*cont].genero_s.genero,"aventura"); break;
        case COMEDIA: strcpy(filmes[*cont].genero_s.genero,"comedia"); break;
        case DRAMA: strcpy(filmes[*cont].genero_s.genero,"drama"); break;
        case TERROR: strcpy(filmes[*cont].genero_s.genero,"terror"); break;
        case ACAO: strcpy(filmes[*cont].genero_s.genero,"acao"); break;
        case ROMANCE: strcpy(filmes[*cont].genero_s.genero,"romance"); break;
    }

    cond = 0;
    do
    {
        scanf("%u",&filmes[*cont].classificacoes);
        if(filmes[*cont].classificacoes != LIVRE && filmes[*cont].classificacoes != MAIS10 
          && filmes[*cont].classificacoes != MAIS12 && filmes[*cont].classificacoes != MAIS14 
          && filmes[*cont].classificacoes != MAIS16 && filmes[*cont].classificacoes != MAIS18)
            printf("ERRO: Classificacao invalida\n");
            else cond = 1;
    }while(!cond);

    switch(filmes[*cont].classificacoes)
    {
        case LIVRE:  strcpy(filmes[*cont].classificacoes_s.classificacao,"livre"); break;
        case MAIS10: strcpy(filmes[*cont].classificacoes_s.classificacao,"+10"); break;
        case MAIS12: strcpy(filmes[*cont].classificacoes_s.classificacao,"+12"); break;
        case MAIS14: strcpy(filmes[*cont].classificacoes_s.classificacao,"+14"); break;
        case MAIS16: strcpy(filmes[*cont].classificacoes_s.classificacao,"+16"); break;
        case MAIS18: strcpy(filmes[*cont].classificacoes_s.classificacao,"+18"); break;
    }

    *cont = *cont + 1;
    return 2;
}

void cadastra_basico(t_planos *planos)
{
    scanf("%d",&(*planos).basico.qnt_filmes);
    scanf("%f",&(*planos).basico.valor_base);
    scanf("%f",&(*planos).basico.valor_excedente);

    printf("Plano Basico cadastrado com sucesso\n");
}

void cadastra_premium(t_planos *planos)
{
    scanf("%f",&(*planos).premium.valor_base);
    printf("Plano Premium cadastrado com sucesso\n");
}

int cadastra_contrato(t_contrato *contratos, int *cont, int num, t_clientes *clientes, int cont_cli, int mes)
{
    int cpf,cond,ret;

    if(*cont >= num)
    return 1;

    if(cont_cli == 0)
    return 2;

    scanf("%d",&contratos[*cont].cpf);
    cpf = contratos[*cont].cpf;

    ret = busca_cliente(clientes,cpf,cont_cli);

    if(ret == 10)
    return 3; //Cliente não encontrado

    ret = busca_contrato(contratos,cpf,*cont);

    if(ret!=10)
    return 4; //Cliente com contrato já existente
    

    cond = 0;
    do
    {
        scanf("%u",&contratos[*cont].tipo_plano);
        if(contratos[*cont].tipo_plano != BASICO 
        && contratos[*cont].tipo_plano != PREMIUM)
        printf("ERRO: Tipo de plano invalido\n");
        else cond = 1;
    }while(!cond);

    cond = 0;
    do
    {
        scanf("%u",&contratos[*cont].tipo_pagamento);
        if(contratos[*cont].tipo_pagamento != DEBITO 
        && contratos[*cont].tipo_pagamento != CREDITO)
        printf("ERRO: Tipo de pagamento invalido\n");
        else cond = 1;

    }while(!cond);

    if(contratos[*cont].tipo_pagamento == CREDITO)
    scanf("%d",&contratos[*cont].dados_cartoes.credito.num);

    if(contratos[*cont].tipo_pagamento == DEBITO)
    {
        scanf("%d",&contratos[*cont].dados_cartoes.debito.agencia);
        scanf("%d",&contratos[*cont].dados_cartoes.debito.conta);
    }

     cond = 0;
    do
    {   
        scanf("%d",&contratos[*cont].data_contratacao.dia);
        if(contratos[*cont].data_contratacao.dia > 31 || contratos[*cont].data_contratacao.dia < 1)
        printf("ERRO: Dia invalido\n");
        else cond = 1;

    }while(!cond);

    ret = busca_cliente(clientes,cpf,cont_cli);

    contratos[*cont].data_contratacao.mes = mes;
    clientes[ret].status = ATIVO;
    strcpy(clientes[ret].status_s.status,"ativo");

    *cont = *cont + 1;
    return 5;
}

int carregar_filme(t_historico historico[][30],int *cont_hist, int *cont_cli_hist, t_clientes *clientes,int cont_cli,t_filme *filmes,int cont_filmes,t_contrato *contratos, int cont_cont, t_planos planos,int mes)
{
    int cpf,ret,ret2,cond,cod_filme,op,i;
    t_genero generos;
    t_classificacoes classificacoes;
    t_lista_filmes genero_classificacao;
    
    if(cont_cli == 0)
    return 1; //Nenhum cliente cadastrado

    scanf("%d",&cpf);
    ret = busca_cliente(clientes,cpf,cont_cli);

    if(ret == 10) 
    return 2; //cliente não cadastrado

    if(clientes[ret].status == INATIVO)
    return 3; //Cliente não ativo
    
    if(cont_hist[ret] == 0)
     historico[ret][cont_hist[ret]].cpf = cpf; //Inclui o cpf no histórico para conseguir identificar o cliente posteriormente

    if(cont_hist[ret] > 30)
    printf("ERRO: Numero maximo de filmes no sistema atingido\n");
    return 7;
    cond = 0;
    do
    {
        scanf("%d",&historico[ret][cont_hist[ret]].data.dia);
        if(historico[ret][cont_hist[ret]].data.dia < 1 || historico[ret][cont_hist[ret]].data.dia > 31)
        printf("ERRO: Dia invalido\n");
        else cond = 1;
    }while(!cond);

    historico[ret][cont_hist[ret]].data.mes = mes;

    cond = 0;
    do
    {
        scanf("%u",&genero_classificacao);
        if(genero_classificacao != GENERO
        && genero_classificacao != CLASSIFICACAO)
        printf("ERRO: Escolha invalida\n");
        else cond = 1;
    }while(!cond);

    if(genero_classificacao == GENERO)
    {
        cond = 0;
        do
        {
            scanf("%u",&generos);
            if(generos != AVENTURA && generos != COMEDIA
                && generos != DRAMA && generos != TERROR
                && generos != ACAO && generos != ROMANCE)
                printf("ERRO: Escolha invalida\n");
                else cond = 1;
        }while(!cond);
    }

    if(genero_classificacao == CLASSIFICACAO)
    {
        cond = 0;
        do
        {
            scanf("%u",&classificacoes);
            if(classificacoes != LIVRE && classificacoes != MAIS10
                && classificacoes != MAIS12 && classificacoes != MAIS14
                && classificacoes != MAIS16 && classificacoes != MAIS18)
                printf("ERRO: Escolha invalida\n");
                else cond = 1;
        }while(!cond);
    }

    if(genero_classificacao == GENERO)
    {
        for(i=0;i<cont_filmes;i++)
        {
            if(filmes[i].genero == generos)
            {
                printf("Codigo: %d\n",filmes[i].cod);
                printf("Nome: %s\n",filmes[i].nome);
            }
        }
    }

    if(genero_classificacao == CLASSIFICACAO)
    {
        for(i=0;i<cont_filmes;i++)
        {   
            if(filmes[i].classificacoes == classificacoes)
            {
                printf("Codigo: %d\n",filmes[i].cod);
                printf("Nome: %s\n",filmes[i].nome);
            }
        }
    }

    scanf("%d",&cod_filme);
    ret = busca_filme(filmes,cod_filme,cont_filmes);

    if(ret == 10)
    return 4; //Filme não encontrado

     ret = busca_cliente(clientes,cpf,cont_cli);

    historico[ret][cont_hist[ret]].cod_filme = cod_filme;
    ret2 = busca_contrato(contratos,cpf,cont_cont);

    if(contratos[ret2].tipo_plano == BASICO)
    {
        if(cont_hist[ret] > planos.basico.qnt_filmes)
        {
            printf("ERRO: Numero maximo de filmes no sistema atingido\n");
            //printf("Deseja pagar um adicional de %.2f reais para assistir ao filme?",planos.basico.valor_excedente);
            cond = 0;
            do
            {
                scanf("%d",&op);
                if(op != 0 && op != 1) // Não = 0 || Sim = 1
                printf("ERRO: Escolha invalida\n");
                else cond = 1;
                     
            }while(!cond);

            if(!op)
            return 5;
        }
    }
        ret = busca_cliente(clientes,cpf,cont_cli);
        cont_hist[ret] = cont_hist[ret] + 1;
        ret = ret + 1;
         
        return 6; 
}


int cancela_contrato(t_contrato *contratos, t_clientes *clientes, int cont_cli, int cont_cont,t_historico historico[][30], int cont_cli_hist,int *cont_hist, t_planos planos,int mes)
{
    int ret,ret2,cpf,cond;
    float extrato;

    if(cont_cont==0)
    return 3;

    scanf("%d",&cpf);
    ret = busca_cliente(clientes,cpf,cont_cli);

    if(ret==10)
    return 1;

    if(clientes[ret].status == INATIVO)
    return 2;

    ret = busca_contrato(contratos,cpf,cont_cont);
    cond = 0;
    do
    {
        scanf("%d",&contratos[ret].data_cancelamento.dia);
        if(contratos[ret].data_cancelamento.dia < 1 || contratos[ret].data_cancelamento.dia > 31)
        printf("ERRO: Dia invalido\n");
        else {
            if(contratos[ret].data_cancelamento.dia < contratos[ret].data_contratacao.dia)
            return 4;
            else cond = 1;
        }
    }while(!cond);

    contratos[ret].data_cancelamento.mes = mes;

     ret2 = busca_historico(historico,cpf,cont_cli_hist);
     if(ret2==10)
     return 6;

        if(contratos[ret].tipo_plano == BASICO)
        {
            if(cont_hist[ret2] > planos.basico.qnt_filmes)
            extrato = ((float)(cont_hist[ret2] - planos.basico.qnt_filmes)*planos.basico.valor_excedente) + planos.basico.valor_base;
            else extrato = planos.basico.valor_base;
        }
        if(contratos[ret].tipo_plano == PREMIUM)
        extrato = planos.premium.valor_base;
    
    printf("Valor devido: %.2f\n",extrato);
    printf("Cancelamento feito com sucesso\n");

    ret = busca_cliente(clientes,cpf,cont_cli);
    clientes[ret].status = INATIVO;
    strcpy(clientes[ret].status_s.status,"inativo");

    return 5;//Apenas retorna ao menu(sem print)
}

int gerar_fatura(t_historico historico[][30],int cont_cli_hist,int *cont_hist, t_clientes *clientes,int cont_cli, t_contrato *contratos,int cont_cont, t_filme *filmes,int cont_filmes, t_planos planos, int *mes)
{
    int op,cond,cpf,ret,ret2,i;
    float extrato;

    //printf("Fatura específica ou de todos os clientes?[0/1]");
    do
    {
        scanf("%d",&op);
        if(op != 0 && op != 1)
        printf("ERRO: Escolha invalida\n");
        else cond = 1;
    }
    while(!cond);

    if(op == 0) //Fatura específica
    {
        if(cont_cli==0)
        return 5;

        if(cont_cont==0)
        return 1; //Nenhum contrato cadastrado no sistema

        scanf("%d",&cpf);
        ret = busca_cliente(clientes,cpf,cont_cli);
        if(ret==10)
        return 2; //printf("ERRO: Cliente nao cadastrado\n");

        ret = busca_contrato(contratos,cpf,cont_cont);
        if(ret == 10)
        return 3; //printf("ERRO: Cliente nao possui contrato\n");

        ret2 = busca_historico(historico,cpf,cont_cli_hist);
        if(ret2==10)
        return 6;

        if(contratos[ret].tipo_plano == BASICO)
        {
            if(cont_hist[ret2] > planos.basico.qnt_filmes)
            extrato = (cont_hist[ret2] - planos.basico.qnt_filmes)*planos.basico.valor_excedente + planos.basico.valor_base;
            else extrato = planos.basico.valor_base;
        }

        if(contratos[ret].tipo_plano == PREMIUM)
        extrato = planos.premium.valor_base;
 
        for(i=0;i<cont_hist[ret];i++) //Fixa o cliente e percorre seus filmes assistidos.
        {
            ret = busca_filme(filmes,historico[ret2][i].cod_filme,cont_filmes);
            
            printf("Nome: %s\n",filmes[ret].nome); //nome do filme
            printf("Data: %d/%d\n",historico[ret2][i].data.dia,historico[ret2][i].data.mes); //data do carregamento
            printf("Valor devido: %.2f\n",extrato);
        }
    }

    if(op == 1)//Todos os clientes
    {
        for(i=0;i<cont_cli_hist;i++)
        {
            
            ret = busca_contrato(contratos,historico[i][0].cpf,cont_cont);
            if(ret==10)
            return 6;

            if(contratos[ret].tipo_plano == BASICO)
            {
                if(cont_hist[i] > planos.basico.qnt_filmes)
                extrato = (cont_hist[i] - planos.basico.qnt_filmes)*planos.basico.valor_excedente + planos.basico.valor_base;
                else extrato = planos.basico.valor_base;
            }

            if(contratos[ret].tipo_plano == PREMIUM)
            extrato = planos.premium.valor_base;

            ret = busca_cliente(clientes,historico[i][0].cpf,cont_cli);
            if(ret == 10)
            return 6;
            ret2 = busca_contrato(contratos,historico[i][0].cpf,cont_cont);

            printf("CPF: %d\n", historico[i][0].cpf);
            printf("Nome: %s\n", clientes[ret].nome); //nome do cliente
            printf("Valor devido: %.2f\n", extrato);
            printf("Mes vigente apos a fatura: %d\n", contratos[ret2].data_contratacao.mes=contratos[ret2].data_contratacao.mes + 1);

            cont_hist[i] = 0; //Zera o histórico do cliente 
        }

            *mes = *mes + 1;
            printf("Mes vigente apos a fatura: %d\n",*mes);   
    }

    return 4;//Volta ao menu(sem print)
}

int busca_cliente(t_clientes *clientes, int chave, int tam)
{
    int i;

    for(i=0;i<tam;i++)
    {
        if(clientes[i].cpf == chave)
        return i; 
    }

    return 10; 
}

int busca_filme(t_filme *filmes, int chave, int tam)
{
    int i;

    for(i=0;i<tam;i++)
    {
        if(filmes[i].cod == chave)
        return i;
    }

    return 10;
}

int busca_contrato(t_contrato *contratos, int chave, int tam)
{
    int i;

    for(i=0;i<tam;i++)
    {
        if(contratos[i].cpf == chave)
        return i;
    }

    return 10;
}

int busca_historico(t_historico historico[][30],int chave,int tam)
{
    int i;

    for(i=0;i<tam;i++)
    {  
        if(historico[i][0].cpf == chave) //O cpf só precisa ser localizado levando em conta as linhas
        return i; //Achou a posição na matriz de um determinado cliente
    }

    return 10;
}

int lista_cliente(t_clientes *clientes, int cont_cli)
{
    int cpf,ret;

    if(cont_cli==0)
    return 1;

    scanf("%d",&cpf);
    ret = busca_cliente(clientes,cpf,cont_cli);

    if(ret==10)
    return 2;

    printf("Nome: %s\n", clientes[ret].nome);
    printf("Email: %s\n", clientes[ret].email);
    printf("Telefone: %s\n", clientes[ret].telefone);
    printf("Status: %d\n", (int)clientes[ret].status);
    return 3;
}

int lista_historico(t_historico historicos[][30], int cont_cli_hist, int *cont_hist, t_clientes *clientes, int cont_cli,t_filme *filmes,int cont_filmes)
{
    int ret,ret2,cpf,i;

    if(cont_cli==0)
    return 1;

    scanf("%d",&cpf);

    ret = busca_cliente(clientes,cpf,cont_cli);

    if(ret==10)
    return 2;

    printf("Estado: %s\n",clientes[ret].status_s.status);

    ret = busca_historico(historicos,cpf,cont_cli_hist);
    if(ret==10)
    return 5;

    if(cont_hist[ret]==0)
    return 3;

    for(i=0;i<cont_hist[ret];i++)
    {
        ret2 = busca_filme(filmes,historicos[ret][i].cod_filme,cont_filmes);

        printf("Codigo: %d\n",filmes[ret2].cod); //codigo do filme
        printf("Nome: %s\n",filmes[ret2].nome); //nome do filme
        printf("Genero: %s\n", filmes[ret2].genero_s.genero);
        printf("Classificacao: %s\n", filmes[ret2].classificacoes_s.classificacao); 
        printf("Data do carregamento: %d/%d\n\n",historicos[ret][i].data.dia,historicos[ret][i].data.mes);
    }
    return 4;
}

int lista_excesso(t_historico historico[][30],int cont_cli_hist,int *cont_hist,t_clientes *clientes, int cont_cli, t_contrato *contratos, int cont_cont,t_planos planos)
{
    int i,ret,ret2,cont=0;
    float valor;

    for(i=0;i<cont_cont;i++)
    {
        if(contratos[i].tipo_plano==BASICO) //Filtra os clientes de plano básico no vetor de contratos
        {
            ret = busca_historico(historico,contratos[i].cpf,cont_cli_hist); //Pega a posição do cliente na matriz histórico
            if(ret==10)
            return 2;

            if(cont_hist[ret] > planos.basico.qnt_filmes)
            {
                valor = (float)(cont_hist[ret] - planos.basico.qnt_filmes)*planos.basico.valor_excedente;
                ret2 = busca_cliente(clientes,contratos[i].cpf,cont_cli); //Acha a posicao no vetor de clientes
        
                printf("CPF: %d\n", clientes[ret2].cpf);
                printf("Nome: %s\n",clientes[ret2].nome);
                printf("Valor excedente: %.2f\n\n",valor); 
                cont++;
            }
        }
    }
    if(!cont) //nenhum cliente excedente
    return 0;

    return 1;
}

int frequencia_filme(t_historico historico[][30],int *cont_hist, int cont_cli_hist,t_filme *filmes,int cont_filmes)
{
    int cod,ret,i,j,achou=0;
    int num=0,denom=0;

    if(cont_filmes==0)
    return 1;

    for(i=0;i<cont_cli_hist;i++)
    if(cont_hist[i]!=0)
    {
        achou=1; //Indica se tem filme assistido em todo histórico
        break;
    }
        scanf("%d",&cod);
        ret = busca_filme(filmes,cod,cont_filmes);
        if(ret==10)
        return 3;
    

    if(!achou)
    return 2;

    for(i=0;i<cont_cli_hist;i++) //Percorre os clientes
    {   for(j=0;j<cont_hist[i];j++) //Percorre apenas os filmes assistidos para aquele determinado cliente
        {
            if(historico[i][j].cod_filme == cod) //Acha apenas o filme procurado para todos os filmes assistidos dos clientes
            num++; //Incrementa a quantidade do filme estudado que foi assistida
            denom++;//Incrementa o total de filmes assistidos
        }
    }

    printf("Frequencia: %.2f%%\n",(float)num/denom*100);
    return 4;
}

int recomenda_filme(t_historico historico[][30],int cont_cli_hist,int *cont_hist, t_filme *filmes, int cont_filmes, t_clientes *clientes,int cont_cli)
{   
    const int generos = 6;
    int aux,aux2,aux3,cpf,i,j,k,achou;
    t_ordenacao_generos ordenacao_generos[generos];
    int vet_cod_genero[10];

    for(i=0;i<generos;i++)
    {
        ordenacao_generos[i].id = i; //Guarda a posição do vetor(id do genero) 
        ordenacao_generos[i].cont = 0;
    }

    if(cont_cli==0)
    return 1;

    scanf("%d",&cpf);
    aux2 = busca_cliente(clientes,cpf,cont_cli);

    if(aux2==10)
    return 2;

    if(clientes[aux2].status==INATIVO)
    return 3;

    aux3=busca_historico(historico,cpf,cont_cli_hist);

    if(aux3==10)
    return 7;

    if(cont_hist[aux3]==0) //Nenhum filme assistido pelo cliente procurado
    return 4;

    for(i=0;i<cont_hist[aux3];i++) //Fazer contagem de generos
    {
        aux2 = busca_filme(filmes,historico[aux3][i].cod_filme,cont_filmes); //retorna a posição do filme em questão
        aux3 = (int)filmes[aux2].genero; //Pega o número do gênero
        ordenacao_generos[aux3].cont = ordenacao_generos[aux3].cont + 1; //Para o genero do filme, o contador é incrementado
    }

    //Bubble sort para organizar em ordem crescente//
    for(i=0;i<generos;i++)
    {   for(j=0;j<generos-1;j++)
        {
            if(ordenacao_generos[i].cont < ordenacao_generos[j+1].cont)
            {
                aux = ordenacao_generos[i].cont; //aux recebe contagem de generos do menor
                aux2 = ordenacao_generos[i].id; //aux2 recebe id do menor
                ordenacao_generos[i].cont = ordenacao_generos[j+1].cont; //O menor recebe a contagem maior
                ordenacao_generos[i].id = ordenacao_generos[j+1].id; //O menor recebe o id do maior;
                ordenacao_generos[j+1].cont = aux; //O antigo maior recebe o aux
                ordenacao_generos[j+1].id = aux2; //O antigo maior recebe o aux2
            }
        }
    }

    //Checagem de quantos empates//
    aux3=1;
    for(i=0;i<generos;i++)
    {   for(j=0;j<generos-1;j++)
        {
            if(ordenacao_generos[i].cont == ordenacao_generos[j+1].cont)
            aux3++; 
        }
    }
    
    for(i=0;i<aux3;i++) //Faz para todos os empates
    {
        aux=0;
        for(j=0;j<cont_filmes;j++)
        {
            if((int)filmes[j].genero == ordenacao_generos[i].id) //checa quantos filmes tem de um certo gênero
            {
                vet_cod_genero[aux] = filmes[j].cod; //Pega os códigos de todos os filmes daquele gênero que foram assistidos
                aux++; 
            }
        }
        if(ordenacao_generos[i].cont < aux)
        {
            for(j=0;j<aux;j++)
            {   aux2 = busca_historico(historico,cpf,cont_cli_hist);
                if(aux2==10)
                return 7;
                achou = 0;
                for(k=0;k<cont_hist[aux2];k++) //Enquanto o código do filme no vetor está parado
                {
                    if(historico[aux2][k].cod_filme == vet_cod_genero[j]) //Verifica se, para aqule gênero, o código do filme em questão existe no histórico do cliente 
                    {
                        achou = 1; //Se existir, ele achou
                        break;
                    }
                }
                if(!achou) //Caso não tenha achado, as informações do filme são printadas
                {
                    aux2 = busca_filme(filmes,vet_cod_genero[j],cont_filmes);
                    printf("Codigo: %d\n",filmes[aux2].cod);
                    printf("Nome: %s\n",filmes[aux2].nome);
                    printf("Genero: %s\n", filmes[aux2].genero_s.genero);//escrito por extenso (exemplo: aventura, comedia, ...)
                    printf("Classificacao: %s\n", filmes[aux2].classificacoes_s.classificacao); 
                }
            }
        }
        if(ordenacao_generos[i].cont == aux) //Verifica se a contagem de filmes para um certo gênero é igual a contagem de filmes do gênero
        return 5; //Todos os filmes do genero foram assistidos;
        
    }
    return 6;
}






