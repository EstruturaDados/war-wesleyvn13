#include <stdio.h>
#include <string.h>

// Criando Struct do exercito.
typedef struct {
    char nome[50];
    char cor[10];
    int tropas;
} Exercito;

#define NUMERO_DE_EXERCITOS 1 // Definindo um constante global para o numero de exercitos.

// Funcao que le e descarta todos os caracteres no buffer de entrada (stdin)
void limpar_buffer() {
    int c;
    
    // Continua lendo enquanto o caractere nao for '\n' E nao for EOF (fim do arquivo)
    while ((c = getchar()) != '\n' && c != EOF) {

    }
}

// Funcao auxiliar para remover o '\n' (nova linha) que o fgets() adiciona
void limparNovaLinha(char *str) {
    size_t len = strlen(str);
    // Verifica se o ultimo caractere e um '\n' e, se for, o substitui por '\0'
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}


int main() {

    Exercito exercitos[NUMERO_DE_EXERCITOS]; // Crinando o Array do tipo exercito (Struct).

    // Inicio do cadastro dos territorios.
    printf("---- Cadastrando os 5 Territorios ----");

    // Loop para colher os dados do usuario e atribuir as devidas variaveis.
    for (int i = 0; i < NUMERO_DE_EXERCITOS; i++) {

        printf("\nCadastrando territorio %d \n" , i+1); 

        printf("Nome do Territorio: ");
        fgets(exercitos[i].nome, sizeof(exercitos[i].nome), stdin); // Atribuindo os valores a variavel.
        limparNovaLinha(exercitos[i].nome);
        printf("Cor do Exercito: ");
        fgets(exercitos[i].cor, sizeof(exercitos[i].cor), stdin); // Atribuindo os valores a variavel.
        limparNovaLinha(exercitos[i].cor); // substitui o \n por \0
        
        printf("Quantidade de Tropas: ");
        scanf("%d", &exercitos[i].tropas); // Atribuindo os valores a variavel.
        limpar_buffer(); //Limpa o buffer.

    }

    printf("\nCadastro inicial concluido com sucesso!\n");
    
    printf("\n======================================\n");
    printf("     MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("======================================\n");

    // Imprimindo os dados colhido anteriormente.
    for (int i = 0; i < NUMERO_DE_EXERCITOS; i++) {

        printf("------------------------\n");
        printf("TERRITORIO %d\n", i+1);
    
        printf("\nNome: %s\n", exercitos[i].nome); // Imprime o nome do territorio.
        printf("Dominado por: Exercito %s\n", exercitos[i].cor); // Imprime a cor do exercito do territorio.
        printf("Numero de Tropas: %d\n", exercitos[i].tropas); // Imprime a quantidade de tropas do territorio.

    }

    return 0; // Retorna 0 (zero) se tudo ocorrer bem.
}
