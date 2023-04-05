/*
Bug não tratado, se digitar por explo "1,5,5" na hora de registar o peso de uma carga, será resgistado '1.00' por conta das duas virgulas
Gostaria de melhorar o sistema que recolhe as dimensões das cargas ao cadastra-las, pedindo um valor de cada vez, altura, largura e comprimento, sendo todos convertidos para valores flutuantes e apresentandos como unidades de medidas de centímetros
Ideia de praticidade, na parte de cadastrar novas cargas, quando já existir um cadastro com o código de embarque informado, pode ser criado uma opção de sobrepor o cadastro antigo ou inserir outro código de embarque, além de ter a opção de desisitr caso o cadastro já existente seja o mesmo desejado pelo(a) usuário(a) do sistema
O perfil de admin está quase pronto, nele é possivel cadastrar novos(as) usuários(os), excluir existentes, editar nomes e senhas ou resetar as senhas individuais de cada perfil para os(as) usuários(as) criarem uma nova senha na hora de logar
Os menus de passageiros e tripulação ainda não começaram a ser criandos
Falta implementar um sistema ao excluir cargas, que informe para o(a) usuário(a) quando não ouver cargas registradas para serem excluídas
Na parte de trocar senha pode ser implemnetado um sistema para pedir a senha atual antes de pedir para digitar a nova senha
*/

//Incluindo bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <conio.h>

//Criando defines
#define MAX_USUARIOS 12 // Definindo o máximo de valores que a função 'usuario' vai receber
#define MAX_CARGAS 60 // Definindo o máximo de valores que a função 'cargas' vai receber

//Declarando variáveis globais
int quantidadeDeValoresNoArray_usuario;
char loginID[6]; //5 caracteres + 1 que é '\0' (caracter nulo)
char loginSenha[13]; //12 caracteres + 1 que é '\0' (caracter nulo)
char confirmarSenha[13]; //12 caracteres + 1 que é '\0' (caracter nulo)
int contadorUsuario;
char opcaoMenuPrincipal[1];
int intOpcaoMenuPrincipal;
char opcaoAjuda[1];
int intOpcaoAjuda;
int quantidadeDeValoresNoArray_carga;
char opcaoMenuCargas[1];
int intOpcaoMenuCargas;
char opcaoSobreporCargas[1];
int intOpcaoSobreporCargas = 1;
char opcaoConfirmarSobreporCargas[1];
int intOpcaoConfirmarSobreporCargas;
char confirmarCadastroNovaCarga[1];
int intConfirmarCadastroNovaCarga;
char opcaoExcluirCarga[1];
int intOpcaoExcluirCarga;
int sairMenuCarga;
int sairMenuAjuda;
//Máximo de dígitos gerais
char codigoCarga[100];
char pesoCarga[100];
char charTamanhoConsoleListarCargas[100];
char excluirCargas[100];

// Declarando funções
void multiplicarPrintf(const char *caracter, int multiplicarPor); //Exibir linhas
void logo(int quantidadeEspacos); // Exibir o nome da empresa "Boto-Rosa Ltda"

// Declarando structs
//Usuários
struct usuarios{
	char NOME[100];
	char ID[6]; // 5 caracteres + 1 que é '\0' (caracter nulo)
	char SENHA[13];// 12 caracteres + 1 que é '\0' (caracter nulo)
};
//Cargas
struct cargas{ //(Código de embarque, Descrição, Dimensões, Peso, Local de Embarque, Local de Desembarque).
    char CODIGO_CARGA[100];
    char DESCRICAO_CARGA[100];
    char DIMENSOES_CARGA[100];
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
	
	//Chamando structs
	//Struct usuários
	struct usuarios usuario[MAX_USUARIOS] = {
		{"9", "9", "9"}, //Mecanismo para deslogar admin na primeira tela do admin
		{"Admin", "admin", "admin"}, //Login admin
		
		// Cadastro {NOME, ID, SENHA} --> Para ID padrão sempre 5 dígitos e SENHA com limite máximo de 12 dígitoses e valor o zero (0) permite que o usuário crie sua própria senha ao logar
		// Ex: {"A1212", "Cleberson", "0"},
		{"SENAI", "senai", "0"},
	};
	
	//Cargas
	struct cargas carga[MAX_CARGAS] = {
		// Cadastro {CODIGO_CARGA, DESCRICAO_CARGA, DIMENSOES_CARGA, PESO_CARGA, EMBARQUE_CARGA, DESEMBARQUE_CARGA} --> DIMENSOES_CARGA = LARGURAcm/ALTURAcm/PORFUNDIDADEcm (na unidade de medida centímetros)
		// Ex: {"77777", "Carga de eletrônicos", "2,5/1/1", 500.0, "São Paulo", "Belo Horizonte"},
		/*
		{"1", "n", "0cm/0cm/0cm", 0, "n", "n"},
		{"2", "n", "0cm/0cm/0cm", 0, "n", "n"},
		{"3", "n", "0cm/0cm/0cm", 0, "n", "n"},
		{"4", "n", "0cm/0cm/0cm", 0, "n", "n"},
		{"5", "n", "0cm/0cm/0cm", 0, "n", "n"},
		{"6", "n", "0cm/0cm/0cm", 0, "n", "n"},
		{"7", "n", "0cm/0cm/0cm", 0, "n", "n"},
		{"8", "n", "0cm/0cm/0cm", 0, "n", "n"},
		{"9", "n", "0cm/0cm/0cm", 0, "n", "n"},
		{"10", "n", "0cm/0cm/0cm", 0, "n", "n"},
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
										
										//Se o código de embarque já estiver cadastrado, pede para o usuário digitar outro código de embarque
										while (condigoCargaJaCadastrado == 1){
											system("mode con:cols=122 lines=49"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): %s \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Peso: %.2f \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
											multiplicarPrintf("=", 122);
											printf("\n 1 - Cadastrar nova carga com outro código de embarque \n");
											multiplicarPrintf("-", 122);
											printf("\n 2 - Sobrepor carga cadastrada com a nova carga \n");
											multiplicarPrintf("-", 122);
											printf("\n 0 - Voltar \n");;
											multiplicarPrintf("=", 122);
										    printf("\n Código de embarque JÁ CADASTRADO!, selecione uma opção (1, 2 ou 0):");
										    scanf("%s", &opcaoSobreporCargas);
											intOpcaoSobreporCargas = atoi(opcaoSobreporCargas);
										    
										    //Corrigir erros pedir uma opção para o usuário
											while (intOpcaoSobreporCargas != 1 && intOpcaoSobreporCargas != 2 && intOpcaoSobreporCargas != 0){
												system("mode con:cols=122 lines=49"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): %s \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Peso: %.2f \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n 1 - Cadastrar nova carga com outro código de embarque \n");
												multiplicarPrintf("-", 122);
												printf("\n 2 - Sobrepor carga cadastrada com a nova carga \n");
												multiplicarPrintf("-", 122);
												printf("\n 0 - Voltar \n");;
												multiplicarPrintf("=", 122);
												printf("\n ERRO! selecione uma opção VÁLIDA! (1, 2 ou 0):");
												fflush(stdin); //Sem limpar o buffer de entrada entra em um loop infinito
												scanf("%s", &opcaoSobreporCargas);
												intOpcaoSobreporCargas = atoi(opcaoSobreporCargas);
											}
											
										    if (intOpcaoSobreporCargas == 1){
										    	//Código
												system("mode con:cols=122 lines=13"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque:");
												scanf("%s", codigoCarga);
											}else if (intOpcaoSobreporCargas == 2){
												system("mode con:cols=122 lines=47"); //Definindo tamanho do console
												system("color B0"); //Definindo cor do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
												multiplicarPrintf("=", 122);
												printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): %s \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Peso: %.2f \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
												multiplicarPrintf("-", 122);
												printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n Tem certeza de que deseja sobrepor essa carga? \n");
												printf("\n 1 - Sim \n");
												multiplicarPrintf("-", 122);
												printf("\n 0 - Não \n");
												multiplicarPrintf("=", 122);
												printf("\n Selecione uma opção (1 ou 0):");
												scanf("%s", &opcaoConfirmarSobreporCargas);
												intOpcaoConfirmarSobreporCargas = atoi(opcaoConfirmarSobreporCargas);
												while (intOpcaoConfirmarSobreporCargas != 1 && intOpcaoConfirmarSobreporCargas != 0){
													system("mode con:cols=122 lines=47"); //Definindo tamanho do console
													system("color B0"); //Definindo cor do console
													system("cls");
													logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
													printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
													multiplicarPrintf("=", 122);
													printf("\n Código de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Descrição: %s \n", carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): %s \n", carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Peso: %.2f \n", carga[indiceCondigoCargaJaCadastrado].PESO_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Local de embarque: %s \n", carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA);
													multiplicarPrintf("-", 122);
													printf("\n Local de desembarque: %s \n", carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA);
													multiplicarPrintf("=", 122);
													printf("\n Tem certeza de que deseja sobrepor essa carga? \n");
													printf("\n 1 - Sim \n");
													multiplicarPrintf("-", 122);
													printf("\n 0 - Não \n");
													multiplicarPrintf("=", 122);
													printf("\n ERRO! selecione uma opção VÁLIDA! (1 ou 0):");
													scanf("%s", &opcaoConfirmarSobreporCargas);
													intOpcaoConfirmarSobreporCargas = atoi(opcaoConfirmarSobreporCargas);
												}
												if (intOpcaoConfirmarSobreporCargas == 1){
													strcpy(carga[indiceCondigoCargaJaCadastrado].CODIGO_CARGA, "");
													strcpy(carga[indiceCondigoCargaJaCadastrado].DESCRICAO_CARGA, "");
													strcpy(carga[indiceCondigoCargaJaCadastrado].DIMENSOES_CARGA, "");
													carga[indiceCondigoCargaJaCadastrado].PESO_CARGA = 0;
													strcpy(carga[indiceCondigoCargaJaCadastrado].EMBARQUE_CARGA, "");
													strcpy(carga[indiceCondigoCargaJaCadastrado].DESEMBARQUE_CARGA, "");
												}else if (intOpcaoConfirmarSobreporCargas == 0){
													continue;
												}
											}else if (intOpcaoSobreporCargas == 0){
												break;
											}
											
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
										}
										
										if (intOpcaoSobreporCargas == 0){
											intOpcaoSobreporCargas = 1;
											break;
										}
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
										system("mode con:cols=122 lines=21"); //Definindo tamanho do console
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
										scanf("%s", &carga[indiceCodigoCarga].DIMENSOES_CARGA);
										
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
										printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): %s \n", carga[indiceCodigoCarga].DIMENSOES_CARGA);
										multiplicarPrintf("=", 122);
									    printf("\n Peso:");
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
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): %s \n", carga[indiceCodigoCarga].DIMENSOES_CARGA);
											multiplicarPrintf("=", 122);
									        printf("\n ERRO! peso INVÁLIDO!:");
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
										printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): %s \n", carga[indiceCodigoCarga].DIMENSOES_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Peso: %.2f \n", carga[indiceCodigoCarga].PESO_CARGA);
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
										printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): %s \n", carga[indiceCodigoCarga].DIMENSOES_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Peso: %.2f \n", carga[indiceCodigoCarga].PESO_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Local de embarque: %s \n", carga[indiceCodigoCarga].EMBARQUE_CARGA);
										multiplicarPrintf("=", 122);
										printf("\n Local de desembarque:");
										scanf("%s", &carga[indiceCodigoCarga].DESEMBARQUE_CARGA);
										
										//Confirmar cadastro nova carga
										system("mode con:cols=122 lines=45"); //Definindo tamanho do console
										system("color B0"); //Definindo cor do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
										multiplicarPrintf("=", 122);
										printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): %s \n", carga[indiceCodigoCarga].DIMENSOES_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Peso: %.2f \n", carga[indiceCodigoCarga].PESO_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Local de embarque: %s \n", carga[indiceCodigoCarga].EMBARQUE_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Local de desembarque: %s \n", carga[indiceCodigoCarga].DESEMBARQUE_CARGA);
										multiplicarPrintf("=", 122);
										printf("\n 1 - Confirmar cadastro \n");
										multiplicarPrintf("-", 122);
										printf("\n 0 - Refazer cadastro \n");
										multiplicarPrintf("=", 122);
										printf("\n Selecione uma opção (1 ou 0):");
										scanf("%s", &confirmarCadastroNovaCarga);
										intConfirmarCadastroNovaCarga = atoi(confirmarCadastroNovaCarga);
										
										//Corrigir erros confirmar cadastro nova carga
										while (intConfirmarCadastroNovaCarga != 1 && intConfirmarCadastroNovaCarga != 0){
									    	system("mode con:cols=122 lines=45"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n Código de embarque: %s \n", carga[indiceCodigoCarga].CODIGO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Descrição: %s \n", carga[indiceCodigoCarga].DESCRICAO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): %s \n", carga[indiceCodigoCarga].DIMENSOES_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Peso: %.2f \n", carga[indiceCodigoCarga].PESO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Local de embarque: %s \n", carga[indiceCodigoCarga].EMBARQUE_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Local de desembarque: %s \n", carga[indiceCodigoCarga].DESEMBARQUE_CARGA);
											multiplicarPrintf("=", 122);
											printf("\n 1 - Confirmar cadastro \n");
											multiplicarPrintf("-", 122);
											printf("\n 0 - Refazer cadastro \n");
											multiplicarPrintf("=", 122);
											printf("\n ERRO! selecione uma opção VÁLIDA! (1 ou 0):");
											scanf("%s", &confirmarCadastroNovaCarga);
											intConfirmarCadastroNovaCarga = atoi(confirmarCadastroNovaCarga);
									    }
										
										if (intConfirmarCadastroNovaCarga == 1){
											refazerCadastroNovaCarga = 1;
											
											//Contar quantos elementos tem a função 'carga' com valores diferentes de vazio ("")
											contadorquantidadeDeValoresNoArray_carga = 0;
											quantidadeDeValoresNoArray_carga = 0;
											while (contadorquantidadeDeValoresNoArray_carga < MAX_CARGAS){
												if (strcmp(carga[contadorquantidadeDeValoresNoArray_carga].CODIGO_CARGA, "") != 0){
													quantidadeDeValoresNoArray_carga += 1;
												}
												contadorquantidadeDeValoresNoArray_carga += 1;
											}
											
										}else if (intConfirmarCadastroNovaCarga == 0){
											strcpy(carga[indiceCodigoCarga].CODIGO_CARGA, "");
											strcpy(carga[indiceCodigoCarga].DESCRICAO_CARGA, "");
											strcpy(carga[indiceCodigoCarga].DIMENSOES_CARGA, "");
											carga[indiceCodigoCarga].PESO_CARGA = 0.0;
											strcpy(carga[indiceCodigoCarga].EMBARQUE_CARGA, "");
											strcpy(carga[indiceCodigoCarga].DESEMBARQUE_CARGA, "");
											refazerCadastroNovaCarga = 0;
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
									printf("\n NÃO há cargas CADASTRADAS! \n");
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
									int contadorListarCargas = 0;
									for (int indiceListarCargas = 0; indiceListarCargas < MAX_CARGAS; indiceListarCargas++){
									    if (strcmp(carga[indiceListarCargas].CODIGO_CARGA, "") != 0){ //Compara se uma variável tem um valor específico
									        contadorListarCargas += 1;
									        printf("\n Código de embarque: %s", carga[indiceListarCargas].CODIGO_CARGA);;
											printf("\n Descrição: %s", carga[indiceListarCargas].DESCRICAO_CARGA);
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): %s", carga[indiceListarCargas].DIMENSOES_CARGA);
											printf("\n Peso: %.2f", carga[indiceListarCargas].PESO_CARGA);
											printf("\n Local de embarque: %s", carga[indiceListarCargas].EMBARQUE_CARGA);
											printf("\n Local de desembarque: %s \n", carga[indiceListarCargas].DESEMBARQUE_CARGA);
											if (contadorListarCargas < quantidadeDeValoresNoArray_carga){
												multiplicarPrintf("-", 122);
											}else if (contadorListarCargas == quantidadeDeValoresNoArray_carga){
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
									printf("\n NÃO há cargas CADASTRADAS! \n");
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
										printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): %s \n", carga[indiceExcluirCargas].DIMENSOES_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Peso: %.2f \n", carga[indiceExcluirCargas].PESO_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Local de embarque: %s \n", carga[indiceExcluirCargas].EMBARQUE_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Local de desembarque: %s \n", carga[indiceExcluirCargas].DESEMBARQUE_CARGA);
										multiplicarPrintf("=", 122);
										printf("\n Tem certeza de que deseja excluir essa carga? \n");
										printf(" 1 - Sim \n");
										printf(" 0 - Não \n");
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
											printf("\n Dimensões (LARGURAcm/ALTURAcm/PORFUNDIDADEcm): %s \n", carga[indiceExcluirCargas].DIMENSOES_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Peso: %.2f \n", carga[indiceExcluirCargas].PESO_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Local de embarque: %s \n", carga[indiceExcluirCargas].EMBARQUE_CARGA);
											multiplicarPrintf("-", 122);
											printf("\n Local de desembarque: %s \n", carga[indiceExcluirCargas].DESEMBARQUE_CARGA);
											multiplicarPrintf("=", 122);
											printf("\n Tem certeza de que deseja excluir essa carga? \n");
											printf(" 1 - Sim \n");
											printf(" 0 - Não \n");
											multiplicarPrintf("=", 122);
											printf("\n ERRO! selecione uma opção VÁLIDA! (1 ou 0):");
											scanf("%s", &opcaoExcluirCarga);
											intOpcaoExcluirCarga = atoi(opcaoExcluirCarga);
										}
										if(intOpcaoExcluirCarga == 1){
											strcpy(carga[indiceExcluirCargas].CODIGO_CARGA, "");
											strcpy(carga[indiceExcluirCargas].DESCRICAO_CARGA, "");
											strcpy(carga[indiceExcluirCargas].DIMENSOES_CARGA, "");
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
							}else if(intOpcaoMenuCargas == 0){
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
							printf("\n Caso tenha algum problema com nome ou senha entre em contato com um Administrador \n");
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
								printf("\n Caso tenha algum problema com nome ou senha entre em contato com algum Administrador \n");
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
								do{
									
									//Pedir para o(a) usuário(a) criar nova senha
									system("mode con:cols=122 lines=13"); //Definindo tamanho do console
									system("color B0"); //Definindo cor do console
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									printf("\n Informe uma nova senha:");
									scanf("%s", usuario[contadorUsuario].SENHA);
									
									//Bloquear nova senha com mais de doze (12) dígitos
									if (strlen(usuario[contadorUsuario].SENHA) > 12){ //Comparar se uma variável tem um valor específico igual
										do{
											system("mode con:cols=122 lines=13"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n ERRO! senhas com mais de doze (12) dígitos serão BLOQUEADAS!:");
											scanf("%s", usuario[contadorUsuario].SENHA);
										}while (strlen(usuario[contadorUsuario].SENHA) > 12); //Comparar se uma variável tem um valor específico igual
									}
									
									//Bloquear nova senha "0"
									if (strcmp(usuario[contadorUsuario].SENHA, "0") == 0){ //Comparar se uma variável tem um valor específico igual
										do{
											system("mode con:cols=122 lines=13"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n ERRO! senha BLOQUEADA!:");
											scanf("%s", usuario[contadorUsuario].SENHA);
											
											//Bloquear nova senha com mais de doze (12) dígitos
											if (strlen(usuario[contadorUsuario].SENHA) > 12){ //Comparar se uma variável tem um valor específico igual
												do{
													system("mode con:cols=122 lines=13"); //Definindo tamanho do console
													system("color B0"); //Definindo cor do console
													system("cls");
													logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
													printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
													multiplicarPrintf("=", 122);
													printf("\n ERRO! senhas com mais de doze (12) dígitos serão BLOQUEADAS!:");
													scanf("%s", usuario[contadorUsuario].SENHA);
												}while (strlen(usuario[contadorUsuario].SENHA) > 12); //Comparar se uma variável tem um valor específico igual
											}
											
										}while (strcmp(usuario[contadorUsuario].SENHA, "0") == 0); //Comparar se uma variável tem um valor específico igual
									}
									
									//Confirmar criar senha do usuário
									system("mode con:cols=122 lines=13"); //Definindo tamanho do console
									system("color B0"); //Definindo cor do console
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									printf("\n Confirme sua nova senha:");
									scanf("%s", confirmarSenha);
									
								}while(strcmp(usuario[contadorUsuario].SENHA, confirmarSenha) != 0); //Comparar se duas variável são diferentes	
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
						printf("\n Versão: Beta 1.0 \n");
						multiplicarPrintf("-", 122);
						printf("\n Desenvolvido por André Felipe de Moraes \n");
						printf(" E-mail para contato: 0000969778@senaimgaluno.com.br | andrefelipe.m1998@gmail.com \n");
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
//Função Multiplicar Printf
void multiplicarPrintf(const char *caracter, int multiplicarPor) { //Estrutura: (caracter, quantidade a ser mulplicado)
    int contadormultiplicarPrintf = 0;
    printf("\n");
    for (contadormultiplicarPrintf = 0; contadormultiplicarPrintf < multiplicarPor; contadormultiplicarPrintf++) {
        printf("%s", caracter);
    }
    printf("\n");
}

//Função Logo
void logo(int quantidadeEspacos){
	system("cls");
	multiplicarPrintf("=", quantidadeEspacos+14+quantidadeEspacos);
	printf("\n%*sBoto-Rosa Ltda\n", quantidadeEspacos, "");
	multiplicarPrintf("=", quantidadeEspacos+14+quantidadeEspacos);
}