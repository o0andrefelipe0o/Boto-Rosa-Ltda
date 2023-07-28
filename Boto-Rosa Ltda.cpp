/*
O perfil de admin está quase pronto, nele é possivel cadastrar novos(as) usuários(os), excluir existentes, editar nomes e senhas ou resetar as senhas individuais de cada perfil para os(as) usuários(as) criarem uma nova senha na hora de logar
Os menus de passageiros e tripulação ainda não começaram a ser criandos
*/

// Declarando funções
void multiplicarPrintf(const char *caracter, int multiplicarPor); //Exibir linhas
void logo(int quantidadeEspacos); //Exibir o nome da empresa "Boto-Rosa Ltda"

//Incluindo bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <conio.h>

//Declarando constantes (criando defines)
#define MAX_USUARIOS 12 // Definindo o máximo de valores que a struct 'usuario' vai receber
#define MAX_CARGAS 60 // Definindo o máximo de valores que a struct 'cargas' vai receber

//Declarando variáveis globais
//login usuário
int quantidadeDeValoresNoArray_usuario;
char loginID[6]; //5 caracteres + 1 que é '\0' (caracter nulo)
char loginSenha[13]; //12 caracteres + 1 que é '\0' (caracter nulo)
char confirmarSenha[13]; //12 caracteres + 1 que é '\0' (caracter nulo)
int contadorUsuario;
//Variáveis usuário
char opcaoMenuPrincipal[1];
int intOpcaoMenuPrincipal;
//Variáveis carga
int quantidadeDeValoresNoArray_carga;
char opcaoMenuCargas[1];
int intOpcaoMenuCargas;
char codigoCarga[100];
char larguraCarga[4]; //Máximo de dígitos float %.2f
char alturaCarga[4]; //Máximo de dígitos float %.2f
char profundidadeCarga[4]; //Máximo de dígitos float %.2f
char pesoCarga[4];//Máximo de dígitos gerais
char confirmarCadastroNovaCarga[1];
int intConfirmarCadastroNovaCarga;
char opcaoSobreporCarga[1];
int intOpcaoSobreporCarga;
char confirmarSobreporCarga[1];
int intConfirmarSobreporCarga;
char charTamanhoConsoleListarCargas[100];
char excluirCargas[100];
char opcaoExcluirCarga[1];
int intOpcaoExcluirCarga;
int sairMenuCarga;
//Variáveis ajuda
char opcaoAjuda[1];
int intOpcaoAjuda;
int sairMenuAjuda;

// Declarando structs (estruturas de matrizes)
//Struct matriz usuários
struct usuarios{
	char NOME[100];
	char ID[6]; // 5 caracteres + 1 que é '\0' (caracter nulo)
	char SENHA[13];// 12 caracteres + 1 que é '\0' (caracter nulo)
};
//Dimensões das cargas da struct matriz cargas
struct dimensoesCarga{
    float altura;
    float largura;
    float profundidade;
};
//Struct matriz cargas
struct cargas{ //(Código de embarque, Descrição, Dimensões, Peso, Local de Embarque, Local de Desembarque).
    char CODIGO_CARGA[100];
    char DESCRICAO_CARGA[100];
    struct dimensoesCarga DIMENSOES_CARGA; //Puxando a struct dimensoesCarga para a cargas com nome DIMENSOES_CARGA
    float PESO_CARGA;
    char EMBARQUE_CARGA[100];
    char DESEMBARQUE_CARGA[100];
};

//Programa
int main(int argc, char *argv[]) { //Iniciar programa
	int fecharPrograma;
		
	//Aceitar acentos / Configuração de idioma
	unsigned int CPAGE_UTF8 = 65001;
	unsigned int CPAGE_DEFAULT = GetConsoleOutputCP();
	SetConsoleOutputCP(CPAGE_UTF8);
	
	//Chamando structs matrizes
	//Struct matriz usuários
	struct usuarios usuario[MAX_USUARIOS] = {
		{"9", "9", "9"}, //Mecanismo para deslogar admin na primeira tela do admin
		{"Admin", "admin", "admin"}, //Login admin
		
		// Cadastro {NOME, ID, SENHA} --> Para ID padrão sempre 5 dígitos e SENHA com limite máximo de 12 dígitoses e valor o zero ("0") permite que o usuário crie sua própria senha ao logar pela primeira vez
		// Ex: {"A1212", "Cleberson", "0"},
		{"SENAI", "senai", "0"},
	};
	//Struct matriz cargas
	struct cargas carga[MAX_CARGAS] = {
		// Cadastro {CODIGO_CARGA, DESCRICAO_CARGA, DIMENSOES_CARGA, PESO_CARGA, EMBARQUE_CARGA, DESEMBARQUE_CARGA} --> DIMENSOES_CARGA = (LARGURAcm/ALTURAcm/PORFUNDIDADEcm) - (na unidade de medida centímetros)
		// Ex: {"77777", "Carga de eletrônicos", {'largura':2.50, 'altura':1.00, 'profundidade':1.00}, 500.00, "São Paulo", "Belo Horizonte"},
		/*
		{"01", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		{"02", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		{"03", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		{"04", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		{"05", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		{"06", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		{"07", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		{"08", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		{"09", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		{"10", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		...
		{"20", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		...
		{"30", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		...
		{"40", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		...
		{"50", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"},
		...
		{"60", "n", {'largura':0.00, 'altura':0.00, 'profundidade':0.00}, 0.00, "n", "n"}
		*/
	};
	do{
		
		//int quantidadeDeValoresNoArray_usuario = sizeof(usuario) / sizeof(struct usuarios); // Retorna quantos elementos tem a função 'usuario', quando é definido máximo de valoes dentro dos colchetes "[]" da função, a função é preenchida com valores vazios ("") e eles contam
		//Contar quantos elementos tem a função 'usuario' com valores diferentes de vazio ("")
		int contadorquantidadeDeValoresNoArray_usuario = 0;
		quantidadeDeValoresNoArray_usuario = 0;
		while (contadorquantidadeDeValoresNoArray_usuario < MAX_USUARIOS){
			if (strcmp(usuario[contadorquantidadeDeValoresNoArray_usuario].ID, "") != 0){
				quantidadeDeValoresNoArray_usuario += 1;
			}
			contadorquantidadeDeValoresNoArray_usuario += 1;
		}
		
		// Deletar usuário IDs repetidos, deixando apenas um, o primeiro da da função 'usuario'
		for (int contadorPrimeiroUsuarioRepetido = 2; contadorPrimeiroUsuarioRepetido < MAX_USUARIOS; contadorPrimeiroUsuarioRepetido++) {
		    for (int contadorSegundoUsuarioRepetido = contadorPrimeiroUsuarioRepetido + 1; contadorSegundoUsuarioRepetido < MAX_USUARIOS; contadorSegundoUsuarioRepetido++) { // Compara o ID do usuário atual com todos os IDs subsequentes
		        if (strcmp(usuario[contadorPrimeiroUsuarioRepetido].ID, usuario[contadorSegundoUsuarioRepetido].ID) == 0) {
		            usuario[contadorSegundoUsuarioRepetido] = (struct usuarios){"", "", ""}; // Exclui um dos usuários com ID repetido (nesse exemplo, o segundo usuário)
		        }
		    }
		}
		
		//Deletar usuários com ID diferente de cinco (5) dígitos
		for (int contadorApagarUsuarioComIdDiferenteDeCincoDigitos = 2; contadorApagarUsuarioComIdDiferenteDeCincoDigitos < MAX_USUARIOS; contadorApagarUsuarioComIdDiferenteDeCincoDigitos++){
			if (strlen(usuario[contadorApagarUsuarioComIdDiferenteDeCincoDigitos].ID) != 5){
				strcpy(usuario[contadorApagarUsuarioComIdDiferenteDeCincoDigitos].NOME, "");
				strcpy(usuario[contadorApagarUsuarioComIdDiferenteDeCincoDigitos].ID, "");
				strcpy(usuario[contadorApagarUsuarioComIdDiferenteDeCincoDigitos].SENHA, "");
			}
		}
		
		//Redefinir para "0" senhas maiores do que doze (12) dígitos
		for (int contadorRedefinirSenhasMaioresQueDozeDigitos = 2; contadorRedefinirSenhasMaioresQueDozeDigitos < MAX_USUARIOS; contadorRedefinirSenhasMaioresQueDozeDigitos++){
			if (strlen(usuario[contadorRedefinirSenhasMaioresQueDozeDigitos].SENHA) > 12){
				strcpy(usuario[contadorRedefinirSenhasMaioresQueDozeDigitos].SENHA, "0");
			}
		}
		
		//Contar quantos elementos tem a função 'carga' com valores diferentes de vazio ("")
		int contadorquantidadeDeValoresNoArray_carga = 0;
		quantidadeDeValoresNoArray_carga = 0;
		while (contadorquantidadeDeValoresNoArray_carga < MAX_CARGAS){
			if (strcmp(carga[contadorquantidadeDeValoresNoArray_carga].CODIGO_CARGA, "") != 0){
				quantidadeDeValoresNoArray_carga += 1;
			}
			contadorquantidadeDeValoresNoArray_carga += 1;
		}
		
		//Contar quantos cabem na função 'larguraCarga'
		int maximoDeValoresNoArray_larguraCarga = sizeof(larguraCarga) / sizeof(larguraCarga[0]);
		
		//Contar quantos cabem na função 'alturaCarga'
		int maximoDeValoresNoArray_alturaCarga = sizeof(alturaCarga) / sizeof(alturaCarga[0]);
		
		//Contar quantos cabem na função 'profundidadeCarga'
		int maximoDeValoresNoArray_profundidadeCarga = sizeof(profundidadeCarga) / sizeof(profundidadeCarga[0]);
		
		//Contar quantos cabem na função 'pesoCarga'
		int maximoDeValoresNoArray_pesoCarga = sizeof(pesoCarga) / sizeof(pesoCarga[0]);
		
		//Tela de login
		int sucessoLogin = 0;
		do{
			//Pedir ID de login do(a) usuário(a)
			system("mode con:cols=122 lines=9"); //Definindo tamanho do console
			system("color B0"); //Definindo cor do console
			system("cls");
			logo(54);//(cols(largura da página) - 14) / 2
			printf("\n Informe o ID de login:");
			scanf("%s", &loginID);
			
			//Corrigir erros do pedir ID de login
			contadorUsuario = 0;
			while (strcmp(loginID, usuario[contadorUsuario].ID) != 0 || strcmp(loginID, usuario[0].ID) == 0 || strcmp(usuario[contadorUsuario].ID, "") == 0){ //Compara se duas variáveis são diferentes e iguais e se uma string tem um valor específico
				contadorUsuario += 1;
				if (contadorUsuario == quantidadeDeValoresNoArray_usuario){
					system("mode con:cols=122 lines=9"); //Definindo tamanho do console
					system("color B0"); //Definindo cor do console
					system("cls");
					logo(54); //(cols(largura da página) - 14) / 2
					printf("\n ERRO! ID de login NÃO CADASTRADO!:");
					scanf("%s", &loginID);
					contadorUsuario = 0;
				}
			}
			
			if (strcmp(usuario[contadorUsuario].SENHA, "0") == 0){
				do{
					
					//Pedir para o(a) usuário(a) criar senha
					system("mode con:cols=122 lines=13"); //Definindo tamanho do console
					system("color B0"); //Definindo cor do console
					system("cls");
					logo(54); //(cols(largura da página) - 14) / 2
					printf("\n Olá %s, bem vindo(a)! \n", usuario[contadorUsuario].NOME);
					multiplicarPrintf("-", 122);
					printf("\n Crie uma senha:");
					scanf("%s", usuario[contadorUsuario].SENHA);
					
					//Bloquear senha com mais de doze (12) dígitos
					if (strlen(usuario[contadorUsuario].SENHA) > 12){ //Comparar se uma variável tem um valor específico igual
						do{
							system("mode con:cols=122 lines=13"); //Definindo tamanho do console
							system("color B0"); //Definindo cor do console
							system("cls");
							logo(54); //(cols(largura da página) - 14) / 2
							printf("\n Olá %s, bem vindo(a)! \n", usuario[contadorUsuario].NOME);
							multiplicarPrintf("-", 122);
							printf("\n ERRO! senhas com mais de doze (12) dígitos serão BLOQUEADAS!:");
							scanf("%s", usuario[contadorUsuario].SENHA);
						}while (strlen(usuario[contadorUsuario].SENHA) > 12); //Comparar se uma variável tem um valor específico igual
					}
					
					//Bloquear senha "0"
					if (strcmp(usuario[contadorUsuario].SENHA, "0") == 0){ //Comparar se uma variável tem um valor específico igual
						do{
							system("mode con:cols=122 lines=13"); //Definindo tamanho do console
							system("color B0"); //Definindo cor do console
							system("cls");
							logo(54); //(cols(largura da página) - 14) / 2
							printf("\n Olá %s, bem vindo(a)! \n", usuario[contadorUsuario].NOME);
							multiplicarPrintf("-", 122);
							printf("\n ERRO! senha BLOQUEADA!:");
							scanf("%s", usuario[contadorUsuario].SENHA);
							
							//Bloquear senha com mais de doze (12) dígitos
							if (strlen(usuario[contadorUsuario].SENHA) > 12){ //Comparar se uma variável tem um valor específico igual
								do{
									system("mode con:cols=122 lines=13"); //Definindo tamanho do console
									system("color B0"); //Definindo cor do console
									system("cls");
									logo(54); //(cols(largura da página) - 14) / 2
									printf("\n Olá %s, bem vindo(a)! \n", usuario[contadorUsuario].NOME);
									multiplicarPrintf("-", 122);
									printf("\n ERRO! senhas com mais de doze (12) dígitos serão BLOQUEADAS!:");
									scanf("%s", usuario[contadorUsuario].SENHA);
								}while (strlen(usuario[contadorUsuario].SENHA) > 12); //Comparar se uma variável tem um valor específico igual
							}
							
						}while (strcmp(usuario[contadorUsuario].SENHA, "0") == 0); //Comparar se uma variável tem um valor específico igual
					}
					
					//Pedir para o(a) usuário(a) confirmar senha criada
					system("mode con:cols=122 lines=13"); //Definindo tamanho do console
					system("color B0"); //Definindo cor do console
					system("cls");
					logo(54); //(cols(largura da página) - 14) / 2
					printf("\n Olá %s, bem vindo(a)! \n", usuario[contadorUsuario].NOME);
					multiplicarPrintf("-", 122);
					printf("\n Confirme sua senha:");
					scanf("%s", confirmarSenha);
					
					//Sair da tela de Login
					if (strcmp(usuario[contadorUsuario].SENHA, confirmarSenha) == 0){ //Compara se duas variáveis são iguais
						sucessoLogin = 1;
					}
				}while(strcmp(usuario[contadorUsuario].SENHA, confirmarSenha) != 0); //Comparar se duas variável são diferentes
			}else{
					int contadorTentativasLoginSenha = 3;
					
					//Pedir senha já registrada do(a) usuário(a)
					system("mode con:cols=122 lines=14"); //Definindo tamanho do console
					system("color B0"); //Definindo cor do console
					system("cls");
					logo(54); //(cols(largura da página) - 14) / 2
					printf("\n Olá %s, bem vindo(a)! \n", usuario[contadorUsuario].NOME);
					multiplicarPrintf("-", 122);
					printf("\n (Tentativas: %i)", contadorTentativasLoginSenha);
					printf("\n Senha:");
					scanf("%s", &loginSenha);
					contadorTentativasLoginSenha--;
					
					//Corrigir erros pedir senha já registrada
					if (strcmp(loginSenha, usuario[contadorUsuario].SENHA) != 0){
						
						//Limitar tentativas de senha no login
						do{
							system("mode con:cols=122 lines=14"); //Definindo tamanho do console
							system("color B0"); //Definindo cor do console
							system("cls");
							logo(54); //(cols(largura da página) - 14) / 2
							printf("\n Olá %s, bem vindo(a)! \n", usuario[contadorUsuario].NOME);
							multiplicarPrintf("-", 122);
							printf("\n (Tentativas: %i)", contadorTentativasLoginSenha);
							printf("\n ERRO! senha INVÁLIDA!:");
							scanf("%s", &loginSenha);
							contadorTentativasLoginSenha--;
						}while (contadorTentativasLoginSenha != 0 && strcmp(loginSenha, usuario[contadorUsuario].SENHA) != 0);
					}
					
					//Sair da tela de Login
					if (strcmp(loginSenha, usuario[contadorUsuario].SENHA) == 0){ //Compara se duas variáveis são iguais
						sucessoLogin = 1;
					}
				}
		}while (sucessoLogin != 1);
		
		//Se logar como admin
		if (strcmp(loginID, usuario[1].ID) == 0){ //Compara se duas variáveis são iguais
		
			//Em construção
			system("mode con:cols=122 lines=37"); //Definindo tamanho do console
			system("color 0A"); //Definindo cor do console
			system("cls");
			printf("\n\n EM CONSTRUÇÃO... \n\n");
			system("pause");
			
		//Se logar como usuário
		}else{
			
			//Deslogar usuário se ele for índice '0' --> {"9","9","9"}
			if (strcmp(loginID, usuario[0].ID) == 0){ //Compara se duas variáveis são iguais
				break;
			}
			
			do{
				
				//Menu Usuário(a)
				system("mode con:cols=122 lines=37"); //Definindo tamanho do console
				system("color B0"); //Definindo cor do console
				system("cls");
				logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
				printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
				multiplicarPrintf("=", 122);
				printf("\n 1 - Passageiros(as) \n");
				multiplicarPrintf("-", 122);
				printf("\n 2 - Cargas \n");
				multiplicarPrintf("-", 122);
				printf("\n 3 - Tripulação \n");
				multiplicarPrintf("-", 122);
				printf("\n 4 - Ajuda \n");
				multiplicarPrintf("-", 122);
				printf("\n 5 - Sobre \n");
				multiplicarPrintf("-", 122);
				printf("\n 9 - Deslogar \n");
				multiplicarPrintf("=", 122);
				printf("\n Selecione uma opção (1, 2, 3, 4, 5 ou 9):");
				scanf("%s", &opcaoMenuPrincipal);
				intOpcaoMenuPrincipal = atoi(opcaoMenuPrincipal);
				
				//Corrigir erros pedir uma opção para o usuário
				while (intOpcaoMenuPrincipal != 1 && intOpcaoMenuPrincipal != 2 && intOpcaoMenuPrincipal != 3 && intOpcaoMenuPrincipal != 4 && intOpcaoMenuPrincipal != 5 && intOpcaoMenuPrincipal != 9){
					system("mode con:cols=122 lines=37"); //Definindo tamanho do console
					system("color B0"); //Definindo cor do console
					system("cls");
					logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
					printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
					multiplicarPrintf("=", 122);
					printf("\n 1 - Passageiros(as) \n");
					multiplicarPrintf("-", 122);
					printf("\n 2 - Cargas \n");
					multiplicarPrintf("-", 122);
					printf("\n 3 - Tripulação \n");
					multiplicarPrintf("-", 122);
					printf("\n 4 - Ajuda \n");
					multiplicarPrintf("-", 122);
					printf("\n 5 - Sobre \n");
					multiplicarPrintf("-", 122);
					printf("\n 9 - Deslogar \n");
					multiplicarPrintf("=", 122);
					printf("\n ERRO! selecione uma opção VÁLIDA! (1, 2, 3, 4, 5 ou 9):");
					fflush(stdin); //Sem limpar o buffer de entrada entra em um loop infinito
					scanf("%s", &opcaoMenuPrincipal);
					intOpcaoMenuPrincipal = atoi(opcaoMenuPrincipal);
				}
				
				//Decisões do usuário
				switch(intOpcaoMenuPrincipal){
					case 1:
						
						//Menu Passageiros
						system("mode con:cols=122 lines=37"); //Definindo tamanho do console
						system("color E0"); //Definindo cor do console
						system("cls");
						printf("\n\n EM CONSTRUÇÃO... \n\n");
						system("pause");
						break;
						
					case 2:
						sairMenuCarga = 0;
						do{
							
							//Menu Cargas
							system("mode con:cols=122 lines=29"); //Definindo tamanho do console
							system("color B0"); //Definindo cor do console
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
							multiplicarPrintf("=", 122);
							printf("\n 1 - Cadastrar nova carga \n");
							multiplicarPrintf("-", 122);
							printf("\n 2 - Listar todas as cargas \n");
							multiplicarPrintf("-", 122);
							printf("\n 3 - Excluir carga \n");
							multiplicarPrintf("-", 122);
							printf("\n 0 - Voltar \n");
							multiplicarPrintf("=", 122);
							printf("\n Selecione uma opção (1, 2, 3, ou 0):");
							scanf("%s", &opcaoMenuCargas);
							intOpcaoMenuCargas = atoi(opcaoMenuCargas);
							
							//Corrigir erros pedir uma opção para o usuário
							while (intOpcaoMenuCargas != 1 && intOpcaoMenuCargas != 2 && intOpcaoMenuCargas != 3 && intOpcaoMenuCargas != 0){
								system("mode con:cols=122 lines=29"); //Definindo tamanho do console
								system("color B0"); //Definindo cor do console
								system("cls");
								logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
								printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
								multiplicarPrintf("=", 122);
								printf("\n 1 - Cadastrar nova carga \n");
								multiplicarPrintf("-", 122);
								printf("\n 2 - Listar todas as cargas \n");
								multiplicarPrintf("-", 122);
								printf("\n 3 - Excluir carga \n");
								multiplicarPrintf("-", 122);
								printf("\n 0 - Voltar \n");;
								multiplicarPrintf("=", 122);
								printf("\n ERRO! selecione uma opção VÁLIDA! (1, 2, 3, ou 0):");
								fflush(stdin); //Sem limpar o buffer de entrada entra em um loop infinito
								scanf("%s", &opcaoMenuCargas);
								intOpcaoMenuCargas = atoi(opcaoMenuCargas);
							}
							
							//Cadastrar novas cargas
							if (intOpcaoMenuCargas == 1){
								int refazerCadastroNovaCarga;
								do{
									//Encontrar espaços vazios para cadastrar novas cargas
									int indiceCodigoCarga = -1; //inicializa com -1, indicando que não há elementos com código zero
									for (int contadorCodigoCarga = 0; contadorCodigoCarga < MAX_CARGAS; contadorCodigoCarga++){
									    if (strcmp(carga[contadorCodigoCarga].CODIGO_CARGA, "") == 0){ //Compara se uma variável tem um valor específico
									        indiceCodigoCarga = contadorCodigoCarga;
									        break;
									    }
									}
									
									//Se não encontrar espaços vazios para cadastrar novas cargas
									if (indiceCodigoCarga == -1){
										system("mode con:cols=122 lines=17"); //Definindo tamanho do console
										system("color B0"); //Definindo cor do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
										multiplicarPrintf("=", 122);
										printf("\n ERRO! infelizmente o sistema já atingiu o número máximo de cadastros de cargas! \n");
										multiplicarPrintf("=", 122);
										printf("\n Pressione qualquer tecla para voltar:");
										getch();
										refazerCadastroNovaCarga = 1;
										
									//Se encontrar espaços vazios para cadastrar novas cargas
									}else if(indiceCodigoCarga != -1){
										
										//Código
										system("mode con:cols=122 lines=13"); //Definindo tamanho do console
										system("color B0"); //Definindo cor do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
										multiplicarPrintf("=", 122);
										printf("\n Código de embarque:");
										scanf("%s", codigoCarga);
										
										//Verifica se o código de embarque já está cadastrado
										int condigoCargaJaCadastrado = 0;
										int indiceCondigoCargaJaCadastrado = 0;
										for (int contadorCondigoCargaJaCadastrado = 0; contadorCondigoCargaJaCadastrado < MAX_CARGAS; contadorCondigoCargaJaCadastrado++){
										    if (strcmp(carga[contadorCondigoCargaJaCadastrado].CODIGO_CARGA, codigoCarga) == 0){ //Compara se duas variáveis são iguais
										        condigoCargaJaCadastrado = 1;
										        indiceCondigoCargaJaCadastrado = contadorCondigoCargaJaCadastrado;
										        break;
										    }
										}
										
										intOpcaoSobreporCarga = 2;
										
										//Se o código de embarque já estiver cadastrado, pede para o usuário digitar outro código de embarque
										while (condigoCargaJaCadastrado == 1){
											system("mode con:cols=122 lines=45"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
											multiplicarPrintf("-", 122);
											printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
											multiplicarPrintf("=", 122);
										    printf("\n Código de embarque JÁ CADASTRADO! ");
										    printf("\n Deseja excluir o cadastro para sobrepor outro com o mesmo código de embarque?\n 1 - Sim, sobrepor cadastro\n 2 - Não, informar outro código de embarque\n 0 - Voltar \n");
										    multiplicarPrintf("=", 122);
										    printf("\n Selecione uma opção (1, 2 ou 0):");
										    scanf("%s", opcaoSobreporCarga);
										    intOpcaoSobreporCarga = atoi(opcaoSobreporCarga);
										    
										    while (intOpcaoSobreporCarga != 1 && intOpcaoSobreporCarga != 2 && intOpcaoSobreporCarga != 0){
												system("mode con:cols=122 lines=45"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
												multiplicarPrintf("-", 122);
												printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
												multiplicarPrintf("=", 122);
											    printf("\n Código de embarque JÁ CADASTRADO! ");
											    printf("\n Deseja excluir o cadastro para sobrepor outro com o mesmo código de embarque?\n 1 - Sim, sobrepor cadastro\n 2 - Não, informar outro código de embarque\n 0 - Voltar \n");
											    multiplicarPrintf("=", 122);
												printf("\n ERRO! selecione uma opção VÁLIDA! (1, 2 ou 0):");
												scanf("%s", opcaoSobreporCarga);
												intOpcaoSobreporCarga = atoi(opcaoSobreporCarga);
											}
										    
											if (intOpcaoSobreporCarga == 1){
										    	break;
												
											}else if (intOpcaoSobreporCarga == 2){
												system("mode con:cols=122 lines=13"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
											    printf("\n Informe outro código de embarque que NÃO esteja cadastrado: ");
											    scanf("%s", codigoCarga);
											    
											    //Verifica se o código de embarque já está cadastrado
												condigoCargaJaCadastrado = 0;
												indiceCondigoCargaJaCadastrado = 0;
												for (int contadorCondigoCargaJaCadastrado = 0; contadorCondigoCargaJaCadastrado < MAX_CARGAS; contadorCondigoCargaJaCadastrado++){
												    if (strcmp(carga[contadorCondigoCargaJaCadastrado].CODIGO_CARGA, codigoCarga) == 0){ //Compara se duas variáveis são iguais
												        condigoCargaJaCadastrado = 1;
												        indiceCondigoCargaJaCadastrado = contadorCondigoCargaJaCadastrado;
												        break;
												    }
												}
											}else if (intOpcaoSobreporCarga == 0){
												break;
											}
										}
										
										if(intOpcaoSobreporCarga == 1){
											int refazerSobreporCarga;
											do{
												strcpy(carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA, codigoCarga);
												
												//Descrição
												system("mode con:cols=122 lines=37"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
												multiplicarPrintf("-", 122);
												printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n Descrição:");
												scanf("%s", &carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
												
												//Dimensões
												float floatLarguraCarga;
												float floatAlturaCarga;
												float floatProfundidadeCarga;
												//Largura
												system("mode con:cols=122 lines=38"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
												multiplicarPrintf("-", 122);
												printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm):");
												printf("\n Largura em centímetros:");
												scanf("%s", &larguraCarga);
												
												//trocar virgula por ponto
											    for (int contadorAceitarVirgulaLarguraCarga = 0; contadorAceitarVirgulaLarguraCarga < maximoDeValoresNoArray_larguraCarga; contadorAceitarVirgulaLarguraCarga++){
											    	if(larguraCarga[contadorAceitarVirgulaLarguraCarga] == ','){
											    		larguraCarga[contadorAceitarVirgulaLarguraCarga] = '.';
													}
												}
											    floatLarguraCarga = atof(larguraCarga);
											    
											    //Aceitar somente valores flutuantes
											    while (sscanf(larguraCarga, "%f", &floatLarguraCarga) != 1){
											    	system("mode con:cols=122 lines=38"); //Definindo tamanho do console
													system("color B0"); //Definindo cor do console
													system("cls");
													logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
													printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
													multiplicarPrintf("=", 122);
													printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
													multiplicarPrintf("-", 122);
													printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
													multiplicarPrintf("=", 122);
													printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm):");
													printf("\n Erro! largura em centímetros INVÁLIDA!:");
													scanf("%s", &larguraCarga);
											        
											        //trocar virgula por ponto
												    for (int contadorAceitarVirgulaLarguraCarga = 0; contadorAceitarVirgulaLarguraCarga < maximoDeValoresNoArray_larguraCarga; contadorAceitarVirgulaLarguraCarga++){
												    	if(larguraCarga[contadorAceitarVirgulaLarguraCarga] == ','){
												    		larguraCarga[contadorAceitarVirgulaLarguraCarga] = '.';
														}
													}
												    floatLarguraCarga = atof(larguraCarga);
											    }
											    
											    //Altura
											    system("mode con:cols=122 lines=38"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
												multiplicarPrintf("-", 122);
												printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/", floatLarguraCarga);
												printf("\n Altura em centímetros:");
												scanf("%s", &alturaCarga);
											    
											    //trocar virgula por ponto
											    for (int contadorAceitarVirgulaAlturaCarga = 0; contadorAceitarVirgulaAlturaCarga < maximoDeValoresNoArray_alturaCarga; contadorAceitarVirgulaAlturaCarga++){
											    	if(alturaCarga[contadorAceitarVirgulaAlturaCarga] == ','){
											    		alturaCarga[contadorAceitarVirgulaAlturaCarga] = '.';
													}
												}
											    floatAlturaCarga = atof(alturaCarga);
											    
											    //Aceitar somente valores flutuantes
											    while (sscanf(alturaCarga, "%f", &floatAlturaCarga) != 1){
											    	system("mode con:cols=122 lines=38"); //Definindo tamanho do console
													system("color B0"); //Definindo cor do console
													system("cls");
													logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
													printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
													multiplicarPrintf("=", 122);
													printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
													multiplicarPrintf("-", 122);
													printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
													multiplicarPrintf("=", 122);
													printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/", floatLarguraCarga);
													printf("\n Erro! altura em centímetros INVÁLIDA!:");
													scanf("%s", &alturaCarga);
											        
											        //trocar virgula por ponto
												    for (int contadorAceitarVirgulaAlturaCarga = 0; contadorAceitarVirgulaAlturaCarga < maximoDeValoresNoArray_alturaCarga; contadorAceitarVirgulaAlturaCarga++){
												    	if(alturaCarga[contadorAceitarVirgulaAlturaCarga] == ','){
												    		alturaCarga[contadorAceitarVirgulaAlturaCarga] = '.';
														}
													}
												    floatAlturaCarga = atof(alturaCarga);
											    }
											    //Profundidade
											    system("mode con:cols=122 lines=38"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
												multiplicarPrintf("-", 122);
												printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/", floatLarguraCarga, floatAlturaCarga);
												printf("\n Profundidade em centímetros:");
												scanf("%s", &profundidadeCarga);
												
											    //trocar virgula por ponto
											    for (int contadorAceitarVirgulaProfundidadeCarga = 0; contadorAceitarVirgulaProfundidadeCarga < maximoDeValoresNoArray_profundidadeCarga; contadorAceitarVirgulaProfundidadeCarga++){
											    	if(profundidadeCarga[contadorAceitarVirgulaProfundidadeCarga] == ','){
											    		profundidadeCarga[contadorAceitarVirgulaProfundidadeCarga] = '.';
													}
												}
											    floatProfundidadeCarga = atof(profundidadeCarga);
											    
											    //Aceitar somente valores flutuantes
											    while (sscanf(profundidadeCarga, "%f", &floatProfundidadeCarga) != 1){
											    	system("mode con:cols=122 lines=38"); //Definindo tamanho do console
													system("color B0"); //Definindo cor do console
													system("cls");
													logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
													printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
													multiplicarPrintf("=", 122);
													printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
													multiplicarPrintf("-", 122);
													printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
													multiplicarPrintf("=", 122);
													printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/", floatLarguraCarga, floatAlturaCarga);
													printf("\n Erro! profundidade em centímetros INVÁLIDA!:");
													scanf("%s", &profundidadeCarga);
											        
											        //trocar virgula por ponto
												    for (int contadorAceitarVirgulaProfundidadeCarga = 0; contadorAceitarVirgulaProfundidadeCarga < maximoDeValoresNoArray_profundidadeCarga; contadorAceitarVirgulaProfundidadeCarga++){
												    	if(profundidadeCarga[contadorAceitarVirgulaProfundidadeCarga] == ','){
												    		profundidadeCarga[contadorAceitarVirgulaProfundidadeCarga] = '.';
														}
													}
												    floatProfundidadeCarga = atof(profundidadeCarga);
											    }
											    
											    carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura = floatLarguraCarga;
												carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura = floatAlturaCarga;
												carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade = floatProfundidadeCarga;
												
												//Peso
												float floatPesoCarga;
												system("mode con:cols=122 lines=37"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
												multiplicarPrintf("-", 122);
												printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
												multiplicarPrintf("=", 122);
											    printf("\n Peso em quilograma:");
											    scanf("%s", &pesoCarga);
											    
											    //trocar virgula por ponto
											    for (int contadorAceitarVirgulaPesoCarga = 0; contadorAceitarVirgulaPesoCarga < maximoDeValoresNoArray_pesoCarga; contadorAceitarVirgulaPesoCarga++){
											    	if(pesoCarga[contadorAceitarVirgulaPesoCarga] == ','){
											    		pesoCarga[contadorAceitarVirgulaPesoCarga] = '.';
													}
												}
											    floatPesoCarga = atof(pesoCarga);
											    
											    //Aceitar somente valores flutuantes
											    while (sscanf(pesoCarga, "%f", &floatPesoCarga) != 1){
											    	system("mode con:cols=122 lines=37"); //Definindo tamanho do console
													system("color B0"); //Definindo cor do console
													system("cls");
													logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
													printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
													multiplicarPrintf("=", 122);
													printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
													multiplicarPrintf("-", 122);
													printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
													multiplicarPrintf("=", 122);
											        printf("\n ERRO! peso em quilograma INVÁLIDO!:");
											        scanf("%s", &pesoCarga);
											        
											        //trocar virgula por ponto
												    for (int contadorAceitarVirgulaPesoCarga = 0; contadorAceitarVirgulaPesoCarga < maximoDeValoresNoArray_pesoCarga; contadorAceitarVirgulaPesoCarga++){
												    	if(pesoCarga[contadorAceitarVirgulaPesoCarga] == ','){
												    		pesoCarga[contadorAceitarVirgulaPesoCarga] = '.';
														}
													}
											        floatPesoCarga = atof(pesoCarga);
											    }
											    
												carga[indiceCondigoCargaJaCadastrado].PESO_CARGA = floatPesoCarga;
												
												//Local de Embarque
												system("mode con:cols=122 lines=37"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
												multiplicarPrintf("-", 122);
												printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n Local de embarque:");
												scanf("%s", &carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
												
												//Local de Desembarque
												system("mode con:cols=122 lines=37"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
												multiplicarPrintf("-", 122);
												printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n Local de desembarque:");
												scanf("%s", &carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
												
												//Confirmar sobreposição de cadastro de carga
												system("mode con:cols=122 lines=45"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
												multiplicarPrintf("-", 122);
												printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n 1 - Confirmar sobreposição do cadastro \n");
												multiplicarPrintf("-", 122);
												printf("\n 2 - Refazer sobreposição do cadastro \n");
												multiplicarPrintf("=", 122);
												printf("\n Selecione uma opção (1 ou 2):");
												scanf("%s", &confirmarSobreporCarga);
												intConfirmarSobreporCarga = atoi(confirmarSobreporCarga);
												
												//Corrigir erros confirmar sobreposição de cadastro de carga
												while (intConfirmarSobreporCarga != 1 && intConfirmarSobreporCarga != 2){
											    	system("mode con:cols=122 lines=45"); //Definindo tamanho do console
													system("color B0"); //Definindo cor do console
													system("cls");
													logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
													printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
													multiplicarPrintf("=", 122);
													printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.altura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.largura, carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA.profundidade);
													multiplicarPrintf("-", 122);
													printf("\n Peso: %.2fkg \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
													multiplicarPrintf("=", 122);
													printf("\n 1 - Confirmar sobreposição do cadastro \n");
													multiplicarPrintf("-", 122);
													printf("\n 2 - Refazer sobreposição \n");
													multiplicarPrintf("=", 122);
													printf("\n ERRO! selecione uma opção VÁLIDA! (1 ou 2):");
													scanf("%s", &confirmarSobreporCarga);
													intConfirmarSobreporCarga = atoi(confirmarSobreporCarga);
											    }
												
												if (intConfirmarSobreporCarga == 1){
													//Contar quantos elementos tem a função 'carga' com valores diferentes de vazio ("")
													contadorquantidadeDeValoresNoArray_carga = 0;
													quantidadeDeValoresNoArray_carga = 0;
													while (contadorquantidadeDeValoresNoArray_carga < MAX_CARGAS){
														if (strcmp(carga[contadorquantidadeDeValoresNoArray_carga].CODIGO_CARGA, "") != 0){
															quantidadeDeValoresNoArray_carga += 1;
														}
														contadorquantidadeDeValoresNoArray_carga += 1;
													}
													refazerSobreporCarga = 1;
													
												}else if (intConfirmarSobreporCarga == 2){
													refazerSobreporCarga = 0;
												}
											}while (refazerSobreporCarga != 1);
											refazerCadastroNovaCarga = 1;
										
										}else if (intOpcaoSobreporCarga == 2){
											strcpy(carga[indiceCodigoCarga].CODIGO_CARGA, codigoCarga);
											
											//Descrição
											system("mode con:cols=122 lines=17"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
											multiplicarPrintf("=", 122);
											printf("\n Descrição:");
											scanf("%s", &carga[indiceCodigoCarga].DESCRICAO_CARGA);
											
											//Dimensões
											float floatLarguraCarga;
											float floatAlturaCarga;
											float floatProfundidadeCarga;
											//Largura
											system("mode con:cols=122 lines=22"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
											multiplicarPrintf("=", 122);
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm):");
											printf("\n Largura em centímetros:");
											scanf("%s", &larguraCarga);
											
											//trocar virgula por ponto
										    for (int contadorAceitarVirgulaLarguraCarga = 0; contadorAceitarVirgulaLarguraCarga < maximoDeValoresNoArray_larguraCarga; contadorAceitarVirgulaLarguraCarga++){
										    	if(larguraCarga[contadorAceitarVirgulaLarguraCarga] == ','){
										    		larguraCarga[contadorAceitarVirgulaLarguraCarga] = '.';
												}
											}
										    floatLarguraCarga = atof(larguraCarga);
										    
										    //Aceitar somente valores flutuantes
										    while (sscanf(larguraCarga, "%f", &floatLarguraCarga) != 1){
										    	system("mode con:cols=122 lines=22"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm):");
												printf("\n Erro! largura em centímetros INVÁLIDA!:");
												scanf("%s", &larguraCarga);
										        
										        //trocar virgula por ponto
											    for (int contadorAceitarVirgulaLarguraCarga = 0; contadorAceitarVirgulaLarguraCarga < maximoDeValoresNoArray_larguraCarga; contadorAceitarVirgulaLarguraCarga++){
											    	if(larguraCarga[contadorAceitarVirgulaLarguraCarga] == ','){
											    		larguraCarga[contadorAceitarVirgulaLarguraCarga] = '.';
													}
												}
											    floatLarguraCarga = atof(larguraCarga);
										    }
											
											//Altura
											system("mode con:cols=122 lines=22"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
											multiplicarPrintf("=", 122);
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/", floatLarguraCarga);
											printf("\n Altura em centímetros:");
											scanf("%s", &alturaCarga);
											
											//trocar virgula por ponto
											for (int contadorAceitarVirgulaAlturaCarga = 0; contadorAceitarVirgulaAlturaCarga < maximoDeValoresNoArray_alturaCarga; contadorAceitarVirgulaAlturaCarga++){
										    	if(alturaCarga[contadorAceitarVirgulaAlturaCarga] == ','){
										    		alturaCarga[contadorAceitarVirgulaAlturaCarga] = '.';
												}
											}
										    floatAlturaCarga = atof(alturaCarga);
										    
										    //Aceitar somente valores flutuantes
										    while (sscanf(alturaCarga, "%f", &floatAlturaCarga) != 1){
										    	system("mode con:cols=122 lines=22"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/", floatLarguraCarga);
												printf("\n Erro! altura em centímetros INVÁLIDA!:");
												scanf("%s", &alturaCarga);
										        
										        //trocar virgula por ponto
											    for (int contadorAceitarVirgulaAlturaCarga = 0; contadorAceitarVirgulaAlturaCarga < maximoDeValoresNoArray_alturaCarga; contadorAceitarVirgulaAlturaCarga++){
											    	if(alturaCarga[contadorAceitarVirgulaAlturaCarga] == ','){
											    		alturaCarga[contadorAceitarVirgulaAlturaCarga] = '.';
													}
												}
											    floatAlturaCarga = atof(alturaCarga);
										    }
											//Profundidade
										    system("mode con:cols=122 lines=22"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
											multiplicarPrintf("=", 122);
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/", floatLarguraCarga, floatAlturaCarga);
											printf("\n Profundidade em centímetros:");
											scanf("%s", &profundidadeCarga);
											
										    //trocar virgula por ponto
										    for (int contadorAceitarVirgulaProfundidadeCarga = 0; contadorAceitarVirgulaProfundidadeCarga < maximoDeValoresNoArray_profundidadeCarga; contadorAceitarVirgulaProfundidadeCarga++){
										    	if(profundidadeCarga[contadorAceitarVirgulaProfundidadeCarga] == ','){
										    		profundidadeCarga[contadorAceitarVirgulaProfundidadeCarga] = '.';
												}
											}
										    floatProfundidadeCarga = atof(profundidadeCarga);
										    
										    //Aceitar somente valores flutuantes
										    while (sscanf(profundidadeCarga, "%f", &floatProfundidadeCarga) != 1){
										    	system("mode con:cols=122 lines=22"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/", floatLarguraCarga, floatAlturaCarga);
												printf("\n Erro! profundidade em centímetros INVÁLIDA!:");
												scanf("%s", &profundidadeCarga);
										        
										        //trocar virgula por ponto
											    for (int contadorAceitarVirgulaProfundidadeCarga = 0; contadorAceitarVirgulaProfundidadeCarga < maximoDeValoresNoArray_profundidadeCarga; contadorAceitarVirgulaProfundidadeCarga++){
											    	if(profundidadeCarga[contadorAceitarVirgulaProfundidadeCarga] == ','){
											    		profundidadeCarga[contadorAceitarVirgulaProfundidadeCarga] = '.';
													}
												}
											    floatProfundidadeCarga = atof(profundidadeCarga);
										    }
										    
										    carga[indiceCodigoCarga].DIMENSOES_CARGA.altura = floatLarguraCarga;
											carga[indiceCodigoCarga].DIMENSOES_CARGA.largura = floatAlturaCarga;
											carga[indiceCodigoCarga].DIMENSOES_CARGA.profundidade = floatProfundidadeCarga;
											
											//Peso
											float floatPesoCarga;
											system("mode con:cols=122 lines=25"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCodigoCarga].DIMENSOES_CARGA.altura, carga[indiceCodigoCarga].DIMENSOES_CARGA.largura, carga[indiceCodigoCarga].DIMENSOES_CARGA.profundidade);
											multiplicarPrintf("=", 122);
										    printf("\n Peso em quilograma:");
										    scanf("%s", &pesoCarga);
										    
										    //trocar virgula por ponto
										    for (int contadorAceitarVirgulaPesoCarga = 0; contadorAceitarVirgulaPesoCarga < maximoDeValoresNoArray_pesoCarga; contadorAceitarVirgulaPesoCarga++){
										    	if(pesoCarga[contadorAceitarVirgulaPesoCarga] == ','){
										    		pesoCarga[contadorAceitarVirgulaPesoCarga] = '.';
												}
											}
										    floatPesoCarga = atof(pesoCarga);
										    
										    //Aceitar somente valores flutuantes
										    while (sscanf(pesoCarga, "%f", &floatPesoCarga) != 1){
										    	system("mode con:cols=122 lines=25"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
										    	system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCodigoCarga].DIMENSOES_CARGA.altura, carga[indiceCodigoCarga].DIMENSOES_CARGA.largura, carga[indiceCodigoCarga].DIMENSOES_CARGA.profundidade);
												multiplicarPrintf("=", 122);
										        printf("\n ERRO! peso em quilograma INVÁLIDO!:");
										        scanf("%s", &pesoCarga);
										        //trocar virgula por ponto
											    for (int contadorAceitarVirgulaPesoCarga = 0; contadorAceitarVirgulaPesoCarga < maximoDeValoresNoArray_pesoCarga; contadorAceitarVirgulaPesoCarga++){
											    	if(pesoCarga[contadorAceitarVirgulaPesoCarga] == ','){
											    		pesoCarga[contadorAceitarVirgulaPesoCarga] = '.';
													}
												}
										        floatPesoCarga = atof(pesoCarga);
										    }
										    
											carga[indiceCodigoCarga].PESO_CARGA = floatPesoCarga;
											
											//Local de Embarque
											system("mode con:cols=122 lines=29"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCodigoCarga].DIMENSOES_CARGA.altura, carga[indiceCodigoCarga].DIMENSOES_CARGA.largura, carga[indiceCodigoCarga].DIMENSOES_CARGA.profundidade);
											multiplicarPrintf("-", 122);
											printf("\n Peso: %.2fkg \n", carga[indiceCodigoCarga].PESO_CARGA);
											multiplicarPrintf("=", 122);
											printf("\n Local de embarque:");
											scanf("%s", &carga[indiceCodigoCarga].EMBARQUE_CARGA);
											
											//Local de Desembarque
											system("mode con:cols=122 lines=33"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCodigoCarga].DIMENSOES_CARGA.altura, carga[indiceCodigoCarga].DIMENSOES_CARGA.largura, carga[indiceCodigoCarga].DIMENSOES_CARGA.profundidade);
											multiplicarPrintf("-", 122);
											printf("\n Peso: %.2fkg \n", carga[indiceCodigoCarga].PESO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Local de embarque: %s \n", carga[indiceCodigoCarga].EMBARQUE_CARGA);
											multiplicarPrintf("=", 122);
											printf("\n Local de desembarque:");
											scanf("%s", &carga[indiceCodigoCarga].DESEMBARQUE_CARGA);
											
											//Confirmar cadastro nova carga
											system("mode con:cols=122 lines=49"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCodigoCarga].DIMENSOES_CARGA.altura, carga[indiceCodigoCarga].DIMENSOES_CARGA.largura, carga[indiceCodigoCarga].DIMENSOES_CARGA.profundidade);
											multiplicarPrintf("-", 122);
											printf("\n Peso: %.2fkg \n", carga[indiceCodigoCarga].PESO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Local de embarque: %s \n", carga[indiceCodigoCarga].EMBARQUE_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Local de desembarque: %s \n", carga[indiceCodigoCarga].DESEMBARQUE_CARGA);
											multiplicarPrintf("=", 122);
											printf("\n 1 - Confirmar cadastro \n");
											multiplicarPrintf("-", 122);
											printf("\n 2 - Refazer cadastro \n");
											multiplicarPrintf("-", 122);
											printf("\n 0 - Cancelar cadastro \n");
											multiplicarPrintf("=", 122);
											printf("\n Selecione uma opção (1, 2 ou 0):");
											scanf("%s", &confirmarCadastroNovaCarga);
											intConfirmarCadastroNovaCarga = atoi(confirmarCadastroNovaCarga);
											
											//Corrigir erros confirmar cadastro nova carga
											while (intConfirmarCadastroNovaCarga != 1 && intConfirmarCadastroNovaCarga != 2 && intConfirmarCadastroNovaCarga != 0){
										    	system("mode con:cols=122 lines=49"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceCodigoCarga].DIMENSOES_CARGA.altura, carga[indiceCodigoCarga].DIMENSOES_CARGA.largura, carga[indiceCodigoCarga].DIMENSOES_CARGA.profundidade);
												multiplicarPrintf("-", 122);
												printf("\n Peso: %.2fkg \n", carga[indiceCodigoCarga].PESO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de embarque: %s \n", carga[indiceCodigoCarga].EMBARQUE_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de desembarque: %s \n", carga[indiceCodigoCarga].DESEMBARQUE_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n 1 - Confirmar cadastro \n");
												multiplicarPrintf("-", 122);
												printf("\n 2 - Refazer cadastro \n");
												multiplicarPrintf("-", 122);
												printf("\n 0 - Cancelar cadastro \n");
												multiplicarPrintf("=", 122);
												printf("\n ERRO! selecione uma opção VÁLIDA! (1, 2 ou 0):");
												scanf("%s", &confirmarCadastroNovaCarga);
												intConfirmarCadastroNovaCarga = atoi(confirmarCadastroNovaCarga);
										    }
											
											if (intConfirmarCadastroNovaCarga == 1){
												//Contar quantos elementos tem a função 'carga' com valores diferentes de vazio ("")
												contadorquantidadeDeValoresNoArray_carga = 0;
												quantidadeDeValoresNoArray_carga = 0;
												while (contadorquantidadeDeValoresNoArray_carga < MAX_CARGAS){
													if (strcmp(carga[contadorquantidadeDeValoresNoArray_carga].CODIGO_CARGA, "") != 0){
														quantidadeDeValoresNoArray_carga += 1;
													}
													contadorquantidadeDeValoresNoArray_carga += 1;
												}
												refazerCadastroNovaCarga = 1;
												
											}else if (intConfirmarCadastroNovaCarga == 2){
												strcpy(carga[indiceCodigoCarga].CODIGO_CARGA, "");
												strcpy(carga[indiceCodigoCarga].DESCRICAO_CARGA, "");
												carga[indiceCodigoCarga].DIMENSOES_CARGA.altura = 0.0;
												carga[indiceCodigoCarga].DIMENSOES_CARGA.largura = 0.0;
												carga[indiceCodigoCarga].DIMENSOES_CARGA.profundidade = 0.0;
												carga[indiceCodigoCarga].PESO_CARGA = 0.0;
												strcpy(carga[indiceCodigoCarga].EMBARQUE_CARGA, "");
												strcpy(carga[indiceCodigoCarga].DESEMBARQUE_CARGA, "");
												refazerCadastroNovaCarga = 0;
												
											}else if (intConfirmarCadastroNovaCarga == 0){
												strcpy(carga[indiceCodigoCarga].CODIGO_CARGA, "");
												strcpy(carga[indiceCodigoCarga].DESCRICAO_CARGA, "");
												carga[indiceCodigoCarga].DIMENSOES_CARGA.altura = 0.0;
												carga[indiceCodigoCarga].DIMENSOES_CARGA.largura = 0.0;
												carga[indiceCodigoCarga].DIMENSOES_CARGA.profundidade = 0.0;
												carga[indiceCodigoCarga].PESO_CARGA = 0.0;
												strcpy(carga[indiceCodigoCarga].EMBARQUE_CARGA, "");
												strcpy(carga[indiceCodigoCarga].DESEMBARQUE_CARGA, "");
												refazerCadastroNovaCarga = 1;
											}
										}else if (intOpcaoSobreporCarga == 0){
											refazerCadastroNovaCarga = 1;
										}
									}
								}while (refazerCadastroNovaCarga != 1);
								
							//Listar todas as cargas
							}else if(intOpcaoMenuCargas == 2){
								//Verificar se a lista de cargas está vazia
								int listaCargasVazia = 0;
								for (int contadorListaCargasVazia = 0; contadorListaCargasVazia < MAX_CARGAS; contadorListaCargasVazia++){
								    if (strcmp(carga[contadorListaCargasVazia].CODIGO_CARGA, "") != 0){ //Compara se uma variável não tem um valor específico
								        listaCargasVazia = 1;
								        break;
								    }
								}
								
								//Caso não tenha cargas na lista
								if (listaCargasVazia != 1){
									system("mode con:cols=122 lines=17"); //Definindo tamanho do console
									system("color B0"); //Definindo cor do console
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									printf("\n NÃO há carga CADASTRADA! \n");
									multiplicarPrintf("=", 122);
									printf("\n Pressione qualquer tecla para voltar:");
									getch();
								}else if (listaCargasVazia == 1){
									int linesListarCargas = (quantidadeDeValoresNoArray_carga * 9) + 13;
									sprintf(charTamanhoConsoleListarCargas, "mode con:cols=122 lines=%d", linesListarCargas);
									system(charTamanhoConsoleListarCargas); //Definindo tamanho do console
									system("color B0"); //Definindo cor do console
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									int indiceListarCargas;
									for (int contadorListarCargas = 0; contadorListarCargas < MAX_CARGAS; contadorListarCargas++){
									    if (strcmp(carga[contadorListarCargas].CODIGO_CARGA, "") != 0){ //Compara se uma variável tem um valor específico
									        indiceListarCargas = contadorListarCargas;
									        printf("\n Código de embarque: %s", carga[indiceListarCargas].CODIGO_CARGA);;
											printf("\n Descrição: %s", carga[indiceListarCargas].DESCRICAO_CARGA);
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm)", carga[indiceListarCargas].DIMENSOES_CARGA.altura, carga[indiceListarCargas].DIMENSOES_CARGA.largura, carga[indiceListarCargas].DIMENSOES_CARGA.profundidade);
											printf("\n Peso: %.2fkg", carga[indiceListarCargas].PESO_CARGA);
											printf("\n Local de embarque: %s", carga[indiceListarCargas].EMBARQUE_CARGA);
											printf("\n Local de desembarque: %s \n", carga[indiceListarCargas].DESEMBARQUE_CARGA);
											if ((indiceListarCargas + 1) < quantidadeDeValoresNoArray_carga){
												multiplicarPrintf("-", 122);
											}else if ((indiceListarCargas + 1) == quantidadeDeValoresNoArray_carga){
												multiplicarPrintf("=", 122);
											}
									    }
									}
									printf("\n Pressione qualquer tecla para voltar:");
									getch();
								}
								
							//Excluir cargas
							}else if(intOpcaoMenuCargas == 3){
								//Verificar se a lista de cargas está vazia
								int listaCargasVazia = 0;
								for (int contadorListaCargasVazia = 0; contadorListaCargasVazia < MAX_CARGAS; contadorListaCargasVazia++){
								    if (strcmp(carga[contadorListaCargasVazia].CODIGO_CARGA, "") != 0){ //Compara se uma variável não tem um valor específico
								        listaCargasVazia = 1;
								        break;
								    }
								}
								
								//Caso não tenha cargas na lista
								if (listaCargasVazia != 1){
									system("mode con:cols=122 lines=17"); //Definindo tamanho do console
									system("color B0"); //Definindo cor do console
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									printf("\n NÃO há carga CADASTRADA para ser exluida! \n");
									multiplicarPrintf("=", 122);
									printf("\n Pressione qualquer tecla para voltar:");
									getch();
								
								}else if (listaCargasVazia == 1){
									int contadorTentativasExcluirCargas = 3;
									system("mode con:cols=122 lines=14"); //Definindo tamanho do console
									system("color B0"); //Definindo cor do console
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									printf("\n (Tentativas: %i)", contadorTentativasExcluirCargas);
									printf("\n Informe o código de embarque da carga que deseja excluir:");
									scanf("%s", &excluirCargas);
									contadorTentativasExcluirCargas--;
									
									//Verificar se o código de embarque da carga está cadastrado
									int indiceExcluirCargas = -1;
									for (int contadorExcluirCargas = 0; contadorExcluirCargas < MAX_CARGAS; contadorExcluirCargas++){
										if (strcmp(excluirCargas, carga[contadorExcluirCargas].CODIGO_CARGA) == 0){ //Comparar se duas variáveis são iguais
											indiceExcluirCargas = contadorExcluirCargas;
										}
									}
									
									//Corrigir erro se o código de embarque da carga não estiver cadastrado
									if (indiceExcluirCargas == -1){
										
										//Limitar tentativas de excluir cargas
										do{	
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n (Tentativas: %i)", contadorTentativasExcluirCargas);
											printf("\n ERRO! carga NÃO CADASTRADA!:");
											scanf("%s", &excluirCargas);
											contadorTentativasExcluirCargas--;
											
											//Verificar se o código de embarque da carga está cadastrado
											indiceExcluirCargas = -1;
											for (int contadorExcluirCargas = 0; contadorExcluirCargas < MAX_CARGAS; contadorExcluirCargas++){
												if (strcmp(excluirCargas, carga[contadorExcluirCargas].CODIGO_CARGA) == 0){ //Comparar se duas variáveis são iguais
													indiceExcluirCargas = contadorExcluirCargas;
												}
											}
										}while (contadorTentativasExcluirCargas != 0 && indiceExcluirCargas == -1);
										
									}
									
									//Se o código de embarque da carga estiver cadastrado
									if (indiceExcluirCargas != -1){
										system("mode con:cols=122 lines=43"); //Definindo tamanho do console
										system("color B0"); //Definindo cor do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
										multiplicarPrintf("=", 122);
										printf("\n Código de embarque: %s \n", carga[indiceExcluirCargas].CODIGO_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Descrição: %s \n", carga[indiceExcluirCargas].DESCRICAO_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceExcluirCargas].DIMENSOES_CARGA.altura, carga[indiceExcluirCargas].DIMENSOES_CARGA.largura, carga[indiceExcluirCargas].DIMENSOES_CARGA.profundidade);
										multiplicarPrintf("-", 122);
										printf("\n Peso: %.2fkg \n", carga[indiceExcluirCargas].PESO_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Local de embarque: %s \n", carga[indiceExcluirCargas].EMBARQUE_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Local de desembarque: %s \n", carga[indiceExcluirCargas].DESEMBARQUE_CARGA);
										multiplicarPrintf("=", 122);
										printf("\n Tem certeza de que deseja excluir essa carga? \n");
										printf(" 1 - Sim \n");
										printf(" 0 - Não, cancelar \n");
										multiplicarPrintf("=", 122);
										printf("\n Selecione uma opção (1 ou 0):");
										scanf("%s", &opcaoExcluirCarga);
										intOpcaoExcluirCarga = atoi(opcaoExcluirCarga);
										while (intOpcaoExcluirCarga != 1 && intOpcaoExcluirCarga != 0){
											system("mode con:cols=122 lines=43"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n Código de embarque: %s \n", carga[indiceExcluirCargas].CODIGO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Descrição: %s \n", carga[indiceExcluirCargas].DESCRICAO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): (%.2fcm/%.2fcm/%.2fcm) \n", carga[indiceExcluirCargas].DIMENSOES_CARGA.altura, carga[indiceExcluirCargas].DIMENSOES_CARGA.largura, carga[indiceExcluirCargas].DIMENSOES_CARGA.profundidade);
											multiplicarPrintf("-", 122);
											printf("\n Peso: %.2fkg \n", carga[indiceExcluirCargas].PESO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Local de embarque: %s \n", carga[indiceExcluirCargas].EMBARQUE_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Local de desembarque: %s \n", carga[indiceExcluirCargas].DESEMBARQUE_CARGA);
											multiplicarPrintf("=", 122);
											printf("\n Tem certeza de que deseja excluir essa carga? \n");
											printf(" 1 - Sim \n");
											printf(" 0 - Não, cancelar \n");
											multiplicarPrintf("=", 122);
											printf("\n ERRO! selecione uma opção VÁLIDA! (1 ou 0):");
											scanf("%s", &opcaoExcluirCarga);
											intOpcaoExcluirCarga = atoi(opcaoExcluirCarga);
										}
										if(intOpcaoExcluirCarga == 1){
											strcpy(carga[indiceExcluirCargas].CODIGO_CARGA, "");
											strcpy(carga[indiceExcluirCargas].DESCRICAO_CARGA, "");
											carga[indiceExcluirCargas].DIMENSOES_CARGA.altura = 0.0;
											carga[indiceExcluirCargas].DIMENSOES_CARGA.largura = 0.0;
											carga[indiceExcluirCargas].DIMENSOES_CARGA.profundidade = 0.0;
											carga[indiceExcluirCargas].PESO_CARGA = 0.0;
											strcpy(carga[indiceExcluirCargas].EMBARQUE_CARGA, "");
											strcpy(carga[indiceExcluirCargas].DESEMBARQUE_CARGA, "");
											
											//Contar quantos elementos tem a função 'carga' com valores diferentes de vazio ("")
											contadorquantidadeDeValoresNoArray_carga = 0;
											quantidadeDeValoresNoArray_carga = 0;
											while (contadorquantidadeDeValoresNoArray_carga < MAX_CARGAS){
												if (strcmp(carga[contadorquantidadeDeValoresNoArray_carga].CODIGO_CARGA, "") != 0){
													quantidadeDeValoresNoArray_carga += 1;
												}
												contadorquantidadeDeValoresNoArray_carga += 1;
											}
										}else if(intOpcaoExcluirCarga == 0){
											continue;
										}
									}
								}
							//Voltar ao menu principal
							}else{
								sairMenuCarga = 1;
							}
						}while (sairMenuCarga != 1);
						break;
					case 3:
						
						//Menu Passageiros
						system("mode con:cols=122 lines=37"); //Definindo tamanho do console
						system("color E0"); //Definindo cor do console
						system("cls");
						printf("\n\n EM CONSTRUÇÃO... \n\n");
						system("pause");
						break;
					case 4:
						sairMenuAjuda = 0;
						do{
							//Ajuda (dúvidas gerais de como usar o sistema)
							system("mode con:cols=122 lines=37"); //Definindo tamanho do console
							system("color B0"); //Definindo cor do console
							system("cls");
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
							multiplicarPrintf("=", 122);
							printf("\n O ID usado para logar é o mesmo código de cinco dígitos que se encontra no verso do crachá de cada funcionário(a) \n");
							multiplicarPrintf("-", 122);
							printf("\n Caso tenha algum problema com o ID de login, nome ou senha, procure um(a) superior que tenha login de Administrador \n");
							multiplicarPrintf("-", 122);
							printf("\n Para navegar no programa é bem simples, basta ler, ele está bem alto explicativo \n");
							multiplicarPrintf("-", 122);
							printf("\n Você pode alterar sua senha aqui mesmo na tela de ajuda \n");
							multiplicarPrintf("=", 122);
							printf("\n 7 - Trocar senha \n");
							multiplicarPrintf("-", 122);
							printf("\n 0 - Voltar \n");
							multiplicarPrintf("=", 122);
							printf("\n Selecione uma opção (7 ou 0):");
							scanf("%s", opcaoAjuda);
							intOpcaoAjuda = atoi(opcaoAjuda);
							
							//Corrigir erros pedir uma opção para o(a) usuário(a)
							while (opcaoAjuda[0] != '0' && intOpcaoAjuda != 7){
								//Ajuda (dúvidas gerais de como usar o sistema)
								system("mode con:cols=122 lines=37"); //Definindo tamanho do console
								system("color B0"); //Definindo cor do console
								system("cls");
								logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
								printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
								multiplicarPrintf("=", 122);
								printf("\n O ID usado para logar é o mesmo código de cinco dígitos que se encontra no verso do crachá de cada funcionário(a) \n");
								multiplicarPrintf("-", 122);
								printf("\n Caso tenha algum problema com o ID de login, nome ou senha, procure um(a) superior que tenha login de Administrador \n");
								multiplicarPrintf("-", 122);
								printf("\n Para navegar no programa é bem simples, basta ler, ele está bem alto explicativo \n");
								multiplicarPrintf("-", 122);
								printf("\n Você pode alterar sua senha aqui mesmo na tela de ajuda \n");
								multiplicarPrintf("=", 122);
								printf("\n 7 - Trocar senha \n");
								multiplicarPrintf("-", 122);
								printf("\n 0 - Voltar \n");
								multiplicarPrintf("=", 122);
								printf("\n ERRO! selecione uma opção VÁLIDA! (7 ou 0):");
								fflush(stdin); //Sem limpar o buffer de entrada entra em um loop infinito
								scanf("%s", opcaoAjuda);
								intOpcaoAjuda = atoi(opcaoAjuda);
							}
							
							//Decisões do usuário
							//Usuário trocar senha
							if (intOpcaoAjuda == 7){
								int contadorTentativasSenhaAtual = 3;
					
								//Pedir senha atual do(a) usuário(a)
								system("mode con:cols=122 lines=14"); //Definindo tamanho do console
								system("color B0"); //Definindo cor do console
								system("cls");
								logo(54); //(cols(largura da página) - 14) / 2
								printf("\n Olá %s, bem vindo(a)! \n", usuario[contadorUsuario].NOME);
								multiplicarPrintf("-", 122);
								printf("\n (Tentativas: %i)", contadorTentativasSenhaAtual);
								printf("\n Informe sua senha atual:");
								scanf("%s", &loginSenha);
								contadorTentativasSenhaAtual--;
								
								//Corrigir erros pedir senha atual
								if (strcmp(loginSenha, usuario[contadorUsuario].SENHA) != 0){
									
									//Limitar tentativas de senha atual
									do{
										system("mode con:cols=122 lines=14"); //Definindo tamanho do console
										system("color B0"); //Definindo cor do console
										system("cls");
										logo(54); //(cols(largura da página) - 14) / 2
										printf("\n Olá %s, bem vindo(a)! \n", usuario[contadorUsuario].NOME);
										multiplicarPrintf("-", 122);
										printf("\n (Tentativas: %i)", contadorTentativasSenhaAtual);
										printf("\n ERRO! senha atual INVÁLIDA!:");
										scanf("%s", &loginSenha);
										contadorTentativasSenhaAtual--;
									}while (contadorTentativasSenhaAtual != 0 && strcmp(loginSenha, usuario[contadorUsuario].SENHA) != 0);
								}
								
								//Se acertar a senha atual, pedir nova senha
								if (strcmp(loginSenha, usuario[contadorUsuario].SENHA) == 0){ //Compara se duas variáveis são iguais
									do{
										//Pedir para o(a) usuário(a) criar nova senha
										system("mode con:cols=122 lines=16"); //Definindo tamanho do console
										system("color B0"); //Definindo cor do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
										multiplicarPrintf("=", 122);
										printf("\n Senha atual: %s", &loginSenha);
										multiplicarPrintf("-", 122);
										printf("\n Informe uma nova senha:");
										scanf("%s", usuario[contadorUsuario].SENHA);
										
										//Bloquear nova senha com mais de doze (12) dígitos
										if (strlen(usuario[contadorUsuario].SENHA) > 12){ //Comparar se uma variável tem um valor específico igual
											do{
												system("mode con:cols=122 lines=16"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Senha atual: %s", &loginSenha);
												multiplicarPrintf("-", 122);
												printf("\n ERRO! senhas com mais de doze (12) dígitos serão BLOQUEADAS!:");
												scanf("%s", usuario[contadorUsuario].SENHA);
											}while (strlen(usuario[contadorUsuario].SENHA) > 12); //Comparar se uma variável tem um valor específico igual
										}
										
										//Bloquear nova senha "0"
										if (strcmp(usuario[contadorUsuario].SENHA, "0") == 0){ //Comparar se uma variável tem um valor específico igual
											do{
												system("mode con:cols=122 lines=16"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Senha atual: %s", &loginSenha);
												multiplicarPrintf("-", 122);
												printf("\n ERRO! senha BLOQUEADA!:");
												scanf("%s", usuario[contadorUsuario].SENHA);
												
												//Bloquear nova senha com mais de doze (12) dígitos
												if (strlen(usuario[contadorUsuario].SENHA) > 12){ //Comparar se uma variável tem um valor específico igual
													do{
														system("mode con:cols=122 lines=16"); //Definindo tamanho do console
														system("color B0"); //Definindo cor do console
														system("cls");
														logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
														printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
														multiplicarPrintf("=", 122);
														printf("\n Senha atual: %s", &loginSenha);
														multiplicarPrintf("-", 122);
														printf("\n ERRO! senhas com mais de doze (12) dígitos serão BLOQUEADAS!:");
														scanf("%s", usuario[contadorUsuario].SENHA);
													}while (strlen(usuario[contadorUsuario].SENHA) > 12); //Comparar se uma variável tem um valor específico igual
												}
												
											}while (strcmp(usuario[contadorUsuario].SENHA, "0") == 0); //Comparar se uma variável tem um valor específico igual
										}
										
										//Bloquear nova senha ser igual à atual
										if (strcmp(usuario[contadorUsuario].SENHA, loginSenha) == 0){ //Comparar se uma variável tem um valor específico igual
											do{
												system("mode con:cols=122 lines=16"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Senha atual: %s", &loginSenha);
												multiplicarPrintf("-", 122);
												printf("\n ERRO! você NÃO pode usar a MESMA senha que a atual!:");
												scanf("%s", usuario[contadorUsuario].SENHA);
												
												//Bloquear nova senha com mais de doze (12) dígitos
												if (strlen(usuario[contadorUsuario].SENHA) > 12){ //Comparar se uma variável tem um valor específico igual
													do{
														system("mode con:cols=122 lines=16"); //Definindo tamanho do console
														system("color B0"); //Definindo cor do console
														system("cls");
														logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
														printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
														multiplicarPrintf("=", 122);
														printf("\n Senha atual: %s", &loginSenha);
														multiplicarPrintf("-", 122);
														printf("\n ERRO! senhas com mais de doze (12) dígitos serão BLOQUEADAS!:");
														scanf("%s", usuario[contadorUsuario].SENHA);
													}while (strlen(usuario[contadorUsuario].SENHA) > 12); //Comparar se uma variável tem um valor específico igual
												}
												
												//Bloquear nova senha "0"
												if (strcmp(usuario[contadorUsuario].SENHA, "0") == 0){ //Comparar se uma variável tem um valor específico igual
													do{
														system("mode con:cols=122 lines=16"); //Definindo tamanho do console
														system("color B0"); //Definindo cor do console
														system("cls");
														logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
														printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
														multiplicarPrintf("=", 122);
														printf("\n Senha atual: %s", &loginSenha);
														multiplicarPrintf("-", 122);
														printf("\n ERRO! senha BLOQUEADA!:");
														scanf("%s", usuario[contadorUsuario].SENHA);
														
														//Bloquear nova senha com mais de doze (12) dígitos
														if (strlen(usuario[contadorUsuario].SENHA) > 12){ //Comparar se uma variável tem um valor específico igual
															do{
																system("mode con:cols=122 lines=16"); //Definindo tamanho do console
																system("color B0"); //Definindo cor do console
																system("cls");
																logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
																printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
																multiplicarPrintf("=", 122);
																printf("\n Senha atual: %s", &loginSenha);
																multiplicarPrintf("-", 122);
																printf("\n ERRO! senhas com mais de doze (12) dígitos serão BLOQUEADAS!:");
																scanf("%s", usuario[contadorUsuario].SENHA);
															}while (strlen(usuario[contadorUsuario].SENHA) > 12); //Comparar se uma variável tem um valor específico igual
														}
														
													}while (strcmp(usuario[contadorUsuario].SENHA, "0") == 0); //Comparar se uma variável tem um valor específico igual
												}
											}while (strcmp(usuario[contadorUsuario].SENHA, loginSenha) == 0);//Comparar se uma variável tem um valor específico igual
											
										}
										
										//Confirmar criar senha do usuário
										system("mode con:cols=122 lines=16"); //Definindo tamanho do console
										system("color B0"); //Definindo cor do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
										multiplicarPrintf("=", 122);
										printf("\n Nova senha: ");
										//Exibir a nova senha ocultada com asteriscos
										for (int i = 0; i < strlen(usuario[contadorUsuario].SENHA); i++) {
									        printf("*");
									    }
										multiplicarPrintf("-", 122);
										printf("\n Confirme sua nova senha:");
										scanf("%s", confirmarSenha);
										
									}while(strcmp(usuario[contadorUsuario].SENHA, confirmarSenha) != 0); //Comparar se duas variável são diferentes	
								}
							}else{
								sairMenuAjuda = 1;
							}
						}while (sairMenuAjuda != 1);
						break;	
					case 5:
						
						//Sobre (versão do sistema, desenvolvido por, sobre o sistema e funcionalidades em geral, direitos reservados, etc.) 
						system("mode con:cols=122 lines=18"); //Definindo tamanho do console
						system("color B0"); //Definindo cor do console
						system("cls");
						multiplicarPrintf("=", 122);
						printf("\n Versão: Beta 1.1 \n");
						multiplicarPrintf("-", 122);
						printf("\n Desenvolvido por André Felipe de Moraes \n");
						printf(" E-mail para contato: andrefelipe.m1998@gmail.com | Linkedin e GitHub: o0andrefelipe0o \n");
						multiplicarPrintf("-", 122);
						printf("\n Sistema desenvolvido para a empresa 'Boto-Rosa Ltda' com o intuito de solucionar seus problemas de gestão de transportes \n");
						multiplicarPrintf("=", 122);
						printf("\n Pressione qualquer tecla para voltar:");
						getch();
						break;
					case 9:
						break;
				}
			}while (intOpcaoMenuPrincipal != 9);
		}
	}while(fecharPrograma != 1);
	return 0; //Finalizar o programa com sucesso
}

//Definindo funções
//Função Multiplicar Printf (exibir linhas)
void multiplicarPrintf(const char *caracter, int multiplicarPor) { //Estrutura: (caracter, quantidade a ser mulplicado)
    int contadormultiplicarPrintf = 0;
    printf("\n");
    for (contadormultiplicarPrintf = 0; contadormultiplicarPrintf < multiplicarPor; contadormultiplicarPrintf++) {
        printf("%s", caracter);
    }
    printf("\n");
}
//Função Logo (exibir o nome da empresa "Boto-Rosa Ltda")
void logo(int quantidadeEspacos){
	system("cls");
	multiplicarPrintf("=", quantidadeEspacos+14+quantidadeEspacos);
	printf("\n%*sBoto-Rosa Ltda\n", quantidadeEspacos, "");
	multiplicarPrintf("=", quantidadeEspacos+14+quantidadeEspacos);
}
