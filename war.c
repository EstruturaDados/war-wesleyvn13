#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>  

// criando struct.
typedef struct {
    char nome[30];
    char cor[10]; 
    int tropas;
} Territorio;

//Protótipos das Funções.
void limpar_buffer();
void limpar_nova_linha(char *str);
Territorio* cadastrar_territorios(int *tamanho);
void exibir_territorios(Territorio *mapa, int tamanho);
void atacar(Territorio *atacante, Territorio *defensor);
void liberar_memoria(Territorio *mapa);

//criando função de limpeza.

// Limpa o buffer para evitar que o '\n' do scanf interfira no fgets
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Remove o caractere de nova linha '\n' que o fgets adiciona na string
void limpar_nova_linha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

//alocação dinamica e cadastro.

Territorio* cadastrar_territorios(int *tamanho) {
    int num_territorios;
    
    printf("Quantos territorios serao cadastrados? ");
    if (scanf("%d", &num_territorios) != 1 || num_territorios <= 0) {
        printf("Numero de territorios invalido. Encerrando.\n");
        *tamanho = 0;
        return NULL;
    }

    limpar_buffer(); 

    //alocacao dinamica de memoria usando calloc
    Territorio *mapa = (Territorio*)calloc(num_territorios, sizeof(Territorio));
    
    if (mapa == NULL) {
        printf("Erro de alocacao de memoria. Encerrando.\n");
        *tamanho = 0;
        return NULL;
    }
    
    *tamanho = num_territorios;
    
    printf("\n--- Cadastro de Territorios ---\n");
    for (int i = 0; i < num_territorios; i++) {
        printf("\nTerritorio %d:\n", i);
        
        // Uso do ponteiro para acessar o elemento
        
        printf("Nome do Territorio (max 29): ");
        fgets((mapa + i)->nome, sizeof((mapa + i)->nome), stdin);
        limpar_nova_linha((mapa + i)->nome);

        printf("Cor do Exercito (Dono - max 9): ");
        fgets((mapa + i)->cor, sizeof((mapa + i)->cor), stdin);
        limpar_nova_linha((mapa + i)->cor);
        
        printf("Tropas iniciais: ");
        scanf("%d", &(mapa + i)->tropas); // & NECESSARIO para o scanf
        limpar_buffer(); 
    }
    
    return mapa;
}

// Funcao que simula um ataque, alterando os dados dos territorios por meio de ponteiros
void atacar(Territorio *atacante, Territorio *defensor) {
    
    // Validacao: Nao pode atacar um territorio da propria cor
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nERRO: O atacante e o defensor sao da mesma cor (%s). Ataque cancelado.\n", atacante->cor);
        return;
    }

    printf("\n>>> Simulando Batalha entre %s (Atacante) e %s (Defensor) <<<\n",
           atacante->nome, defensor->nome);
    
    // Simulação com dado aleatório (rand() % 6) + 1 -> Valor de 1 a 6
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;
    
    printf("Dado Atacante (%s): %d\n", atacante->cor, dado_atacante);
    printf("Dado Defensor (%s): %d\n", defensor->cor, dado_defensor);
    
    if (dado_atacante > dado_defensor) {
        // Atacante Venceu
        printf("\n*** O atacante (%s) VENCEU A BATALHA! ***\n", atacante->nome);
        
        // 1. O Defensor perde o controle (muda de dono)
        strcpy(defensor->cor, atacante->cor);
        
        // 2. O Atacante envia metade das tropas para o novo território (ou pelo menos 1)
        int tropas_perdidas = atacante->tropas / 2;
        if (tropas_perdidas == 0 && atacante->tropas > 0) {
            tropas_perdidas = 1; // Pelo menos 1 tropa precisa ser enviada para a ocupacao
        }
        
        // Atualiza as tropas: atacante perde, defensor ganha
        atacante->tropas -= tropas_perdidas;
        defensor->tropas = tropas_perdidas;
        
        printf("%s agora e controlado por %s e recebeu %d tropas de ocupacao.\n", 
               defensor->nome, defensor->cor, defensor->tropas);
        
    } else {

        printf("\n-- O defensor (%s) RESISTIU ao ataque! --\n", defensor->nome);
        
        // Atacante perde uma tropa. Defensor nao perde tropas.
        if (atacante->tropas > 0) {
            atacante->tropas -= 1;
            printf("%s perdeu 1 tropa na invasao. Tropas restantes: %d.\n", 
                   atacante->nome, atacante->tropas);
        }
    }
}


// Funcao para exibir os dados dos territorios de forma organizada
void exibir_territorios(Territorio *mapa, int tamanho) {
    printf("\n============================================\n");
    printf("          MAPA ATUAL DE TERRITORIOS\n");
    printf("============================================\n");
    printf(" Indice | Nome (Pais) | Tropas | Cor (Dono)\n");
    printf("--------------------------------------------\n");
    
    for (int i = 0; i < tamanho; i++) {
        // Uso do ponteiro para acessar os dados na posicao i
        printf(" %6d | %15s | %6d | %s\n", 
               i, 
               (mapa + i)->nome,      // Acessa o nome
               (mapa + i)->tropas,    // Acessa as tropas
               (mapa + i)->cor);      // Acessa a cor
    }
    printf("============================================\n");
}

// Funcao para liberar a memoria alocada dinamicamente
void liberar_memoria(Territorio *mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemoria do mapa liberada com sucesso.\n");
    }
}

int main() {
    
    // Inicializa o gerador de numeros aleatorios uma unica vez
    srand(time(NULL)); 
    
    Territorio *mapa;
    int num_territorios = 0;
    
    // Cadastro e alocacao dinamica
    mapa = cadastrar_territorios(&num_territorios);
    
    if (num_territorios == 0 || mapa == NULL) {
        return 1; // Encerra se a alocacao falhar ou o usuario entrar com valor invalido
    }
    
    exibir_territorios(mapa, num_territorios);

    // --- Loop Principal de Ataque ---
    int idx_atacante, idx_defensor;
    char continuar[5];
    
    do {
        printf("\n[SIMULACAO DE ATAQUE]\n");
        printf("Digite o indice do Territorio ATACANTE (0 a %d): ", num_territorios - 1);
        if (scanf("%d", &idx_atacante) != 1) break;
        limpar_buffer(); 

        printf("Digite o indice do Territorio DEFENSOR (0 a %d): ", num_territorios - 1);
        if (scanf("%d", &idx_defensor) != 1) break;
        limpar_buffer();
        
        // Validacao de indices
        if (idx_atacante < 0 || idx_atacante >= num_territorios ||
            idx_defensor < 0 || idx_defensor >= num_territorios ||
            idx_atacante == idx_defensor) 
        {
            printf("\nerro: Indice invalido ou atacante = defensor. Tente novamente.\n");
            continue;
        }

        // Chamada da funcao de ataque, passando os ponteiros para as structs no array
        atacar((mapa + idx_atacante), (mapa + idx_defensor));
        
        // Exibicao dos dados atualizados
        exibir_territorios(mapa, num_territorios);

        printf("Deseja realizar outro ataque? (sim/nao): ");
        fgets(continuar, sizeof(continuar), stdin);
        limpar_nova_linha(continuar);

    } while (strcmp(continuar, "sim") == 0);
    
    // Libera toda a memoria alocada antes de encerrar
    liberar_memoria(mapa);
    
    return 0;
}
