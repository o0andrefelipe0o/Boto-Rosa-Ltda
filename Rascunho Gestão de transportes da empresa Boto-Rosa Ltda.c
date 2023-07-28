/*
CONTEXTUALIZAÇÃO:

A empresa Boto-Rosa Ltda é uma empresa que transporta mercadorias e passageiros do rio amazonas até portos marítimos da costa brasileira. Você acaba de ser contratado como desenvolvedor para construir um sistema que solucione os problemas de gestão de transportes da empresa. Durante as reuniões com a diretoria da empresa, alguns requisitos foram levantados e impostos como mínimos para implantação do sistema:

Sistema de login (requisitar usuário e senha para acesso ao sistema)
Tela Inicial pós login – Boas Vindas – Menu Principal
Menu Principal
Passageiros, Cargas, Tripulação, Ajuda e Sobre

Menu Passageiros
Listar todos, cadastrar novo e excluir.
Classe econômica.
Classe Executiva. 
Informações básicas de cadastro (Código de Embarque, Nome Completo, e-mail, Classe, CPF, Data de Nascimento, Local de Embarque, Local de Desembarque, etc.).
Produtos consumidos (quantidade, descrição e valor).

Menu Cargas
Cadastrar novo, listar todos e excluir.
Informações básicas de cadastro (Código de embarque, Descrição, Dimensões, Peso, Local de Embarque, Local de Desembarque).

Menu Tripulação
Listar todos, cadastrar novo e excluir.
Capitão.
Imediato.
Marinheiro. 
Informações básicas de cadastro (Código de Embarque, Nome Completo, e-mail, Patente, CPF, Data de Nascimento, etc.).Ajuda (dúvidas gerais de como usar o sistema).Sobre (versão do sistema, desenvolvido por, sobre o sistema e funcionalidades em geral, direitos reservados, etc.) 

DESAFIO:

Analisar todos os requisitos do sistema, abstrair o problema, construir um sistema capaz de gerir todos os elementos do sistema e elaborar um documento em formato .pdf explicando o funcionamento do sistema.

Obs. Como os módulos são parecidos. Você pode escolher um deles para entregar. Ou seja, desenvolva o menu principal, ajuda, sobre e escolher entre Passageiros, Carga ou Tripulação para concluir o desafio.
*/

/*
Poderia colocar um sistema de cadastrar novos usuários ou excluir os existentes no perfil 'Admin' mas achei desnecessário já que esses dados não seriam armazenados fora da execução do código
*/




#include <string.h>

#include <ctype.h>
#include <stdbool.h>


#define MAX_USUARIOS 13 // Definindo o máximo de valores que a função 'usuario' vai receber
#define MAX_CARGAS 10 // Definindo o máximo de valores que a função 'cargas' vai receber


//Declarando variáveis globais
int contadorNovoUsuario;
int fecharPrograma;
int sairCadastrarNovoUsuario;



int deslogarAdmin;
char usuarioID[6]; // 5 caracteres + '\0' (caracter nulo)
int intUsuarioID;
char opcaoMenuAdmin[1];
int intOpcaoMenuAdmin;
char opcaoExcluirUsuario[1];
int intOpcaoExcluirUsuario;
char codigoCarga[100];
int intCodigoCarga;
char pesoCarga[100];
float floatPesoCarga;
int contadorExibirCargas;
int sairMenuCarga;
char excluirCodigoCarga[100];
int intExcluirCodigoCarga;
bool haCargasRegistradas;
char opcaoExcluirCarga[1];
int intOpcaoExcluirCarga;
int contadorApagarUsuarioComIdDiferenteDeCincoDigitos;
int contadorquantidadeDeValoresNoArray_usuario;
int quantidadeDeValoresNoArray_carga;
int contadorquantidadeDeValoresNoArray_carga;
int x, y;
int sucessoLogin;
int contadorTentativasLoginSenha;
int contadorMenuAdmin;
int espacoVazio;
int contadorEspacoVazio;
int contadorBloquearIdRepetido;
int indiceCodigoCarga;
int contadorCodigoCarga;
int codigoExistente;
int i;
int contadorHaCargasRegistradas;
int verificarSeTemCodigoCarga;
int contadorVerificarSeTemCodigoCarga;
int contadorExcluirCodigoCarga;


//Início
int main(int argc, char *argv[]) {
	
	//setlocale(LC_ALL, ""); //Configuração de idioma
	//setlocale(LC_ALL, "Portugues");
	//setlocale(LC_CTYPE, "Portuguese_Brazil");
	//setlocale(LC_CTYPE, "Brazil");
	
	//Usuários
	struct usuarios usuario[MAX_USUARIOS] = {
		{"9", "9", "9"}, //Mecanismo para deslogar e não ficar preso na primeira tela do admin
		{"Admin", "admin", "admin"}, //Conta do admin 
		{"00001", "00001", "00001"}, //ID proibido, ele não consegue ser tratado pelo admin
		
		// Cadastro {NOME, ID, SENHA} --> Para ID (padrão sempre 5 dígitos) e SENHA (zero (0) permite que o usuário crie uma senha ao logar)
		{"SENAI", "senai", "0"},
		//{"N", "N", "N"}, --> O ultimo é não inclusivo dor conta do #define MAX_CARGAS
	};
	
	//Cargas
	struct cargas carga[MAX_CARGAS] = {
		// Cadastro {CODIGO_CARGA, DESCRICAO_CARGA, DIMENSOES_CARGA, PESO_CARGA, EMBARQUE_CARGA, DESEMBARQUE_CARGA}
		{77777, "Carga de eletrônicos", "2x1x1", 500.0, "São Paulo", "Belo Horizonte"},
		//{0, "n", "0x0x0", 0, "n", "n"},
		//{0, "n", "0x0x0", 0, "n", "n"},
		//{0, "n", "0x0x0", 0, "n", "n"},
		//{0, "n", "0x0x0", 0, "n", "n"},
		//{0, "n", "0x0x0", 0, "n", "n"},
		//{0, "n", "0x0x0", 0, "n", "n"},
		//{0, "n", "0x0x0", 0, "n", "n"},
		//{0, "n", "0x0x0", 0, "n", "n"},
		//{0, "n", "0x0x0", 0, "n", "n"},
	};
	
		
	do{
		

		//Abrindo
		
		
		//Tela de login
		
		do{
			sucessoLogin = 0;
			
			//Pedir ID de login do usuário
			system("mode con:cols=122 lines=16"); //Definindo tamanho do console
			system("color B0"); //Definindo cor do console
			system("cls");
			logo(54); //(cols(largura da página) - 14) / 2
			printf("\n Usuário ID:");
			scanf("%s", &loginID);
			
			//Corrigir erros pedir ID
			contadorUsuario = 0;
			while (strcmp(loginID, usuario[contadorUsuario].ID) != 0 || strcmp(loginID, usuario[0].ID) == 0 || strcmp(usuario[contadorUsuario].ID, "0") == 0){ //Compara se duas variáveis são diferentes e iguais e se uma string tem um valor específico
				contadorUsuario += 1;
				if (contadorUsuario == quantidadeDeValoresNoArray_usuario){
					system("mode con:cols=122 lines=16"); //Definindo tamanho do console
					system("color B0"); //Definindo cor do console
					system("cls");
					logo(54); //(cols(largura da página) - 14) / 2
					printf("\n ERRO! usuário ID NÃO CADASTRADO!:");
					scanf("%s", &loginID);
					contadorUsuario = 0;
				}
			}
			
			if (strcmp(usuario[contadorUsuario].SENHA, "0") == 0){
				do{
					
					//Criar senha do usuário
					system("mode con:cols=122 lines=15"); //Definindo tamanho do console
					system("color B0"); //Definindo cor do console
					system("cls");
					logo(54); //(cols(largura da página) - 14) / 2
					printf("\n Olá %s, bem vindo(a)! \n", usuario[contadorUsuario].NOME);
					multiplicarPrintf("-", 122);
					printf("\n Crie uma senha:");
					scanf("%s", usuario[contadorUsuario].SENHA);
					
					//Bloquear senha '0'
					if (strcmp(usuario[contadorUsuario].SENHA, "0") == 0){ //Comparar se uma variável tem um valor específico igual
						do{
							system("mode con:cols=122 lines=15"); //Definindo tamanho do console
							system("color B0"); //Definindo cor do console
							system("cls");
							logo(54); //(cols(largura da página) - 14) / 2
							printf("\n Olá %s, bem vindo(a)! \n", usuario[contadorUsuario].NOME);
							multiplicarPrintf("-", 122);
							printf("\n ERRO! essa senha está BLOQUEADA!:");
							scanf("%s", usuario[contadorUsuario].SENHA);
						}while (strcmp(usuario[contadorUsuario].SENHA, "0") == 0); //Comparar se uma variável tem um valor específico igual
					}
					
					//Confirmar criar senha do usuário
					system("mode con:cols=122 lines=15"); //Definindo tamanho do console
					system("color B0"); //Definindo cor do console
					system("cls");
					logo(54); //(cols(largura da página) - 14) / 2
					printf("\n Olá %s, bem vindo(a)! \n", usuario[contadorUsuario].NOME);
					multiplicarPrintf("-", 122);
					printf("\n Confirmar senha:");
					scanf("%s", confirmarSenha);
					
					//Sair da tela de Login
					if (strcmp(usuario[contadorUsuario].SENHA, confirmarSenha) == 0){ //Compara se duas variáveis são iguais
						sucessoLogin = 1;
					}
					
				}while(strcmp(usuario[contadorUsuario].SENHA, confirmarSenha) != 0); //Comparar se duas variável são diferentes
			}else{
				contadorTentativasLoginSenha = 3;
				
				//Pedir senha do usuário
				system("mode con:cols=122 lines=16"); //Definindo tamanho do console
				system("color B0"); //Definindo cor do console
				system("cls");
				logo(54); //(cols(largura da página) - 14) / 2
				printf("\n Olá %s, bem vindo(a)! \n", usuario[contadorUsuario].NOME);
				multiplicarPrintf("-", 122);
				printf("\n (Tentativas: %i)", contadorTentativasLoginSenha);
				printf("\n Senha:");
				scanf("%s", &loginSenha);
				contadorTentativasLoginSenha--;
				
				//Corrigir erros pedir senha
				if (strcmp(loginSenha, usuario[contadorUsuario].SENHA) != 0){
					//Limitartentativas de senha no login
					do{
						system("mode con:cols=122 lines=16"); //Definindo tamanho do console
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
			multiplicarPrintf("=", 122);
		}while (sucessoLogin != 1);
		
		//Se logar como admin
		if (strcmp(loginID, usuario[1].ID) == 0){ //Compara se duas variáveis são iguais
			do{
				deslogarAdmin = 0;
				
				//Menu cadatrar usuário com pedir ID de login do usuário que vai ser analisado
				system("mode con:cols=122 lines=21"); //Definindo tamanho do console
				system("color 0A"); //Definindo cor do console
				system("cls");
				logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
				printf("\n 1 - Cadastrar usuário \n");
				multiplicarPrintf("-", 122);
				printf("\n 9 - Deslogar \n");
				multiplicarPrintf("-", 122);
				printf("\n / - Informar usuário ID \n");
				multiplicarPrintf("=", 122);
				printf("\n Selecione uma opção (1 ou 9) ou infome um usuário ID:");
				scanf("%s", &usuarioID);
				intUsuarioID = atoi(usuarioID);
				
				//Bloquear admin de ser analisado
				while (strcmp(usuarioID, usuario[1].ID) == 0){ //Compara se duas variáveis são iguais
					system("mode con:cols=122 lines=21"); //Definindo tamanho do console
					system("color 0A"); //Definindo cor do console
					system("cls");
					logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
					printf("\n 1 - Cadastrar usuário \n");
					multiplicarPrintf("-", 122);
					printf("\n 9 - Deslogar \n");
					multiplicarPrintf("-", 122);
					printf("\n / - Informar usuário ID \n");
					multiplicarPrintf("=", 122);
					printf("\n ERRO! selecione uma opção VÁLIDA! (1 ou 9) ou infome um usuário ID que NÃO esteja BLOQUEADO!:");
					scanf("%s", &usuarioID);
					intUsuarioID = atoi(usuarioID);
				}
				
				//Corrigir erros menu cadatrar usuário com pedir ID de login do usuário que vai ser analisado
				contadorMenuAdmin = 0;
				while (strcmp(usuarioID, usuario[contadorMenuAdmin].ID) != 0 && intUsuarioID != 1 || strcmp(usuario[contadorMenuAdmin].ID, "0") == 0){ //Compara se duas variáveis são diferentes e se uma variável tem um valor específico
					contadorMenuAdmin += 1;
					if (contadorMenuAdmin == quantidadeDeValoresNoArray_usuario){
						system("mode con:cols=122 lines=21"); //Definindo tamanho do console
						system("color 0A"); //Definindo cor do console
						system("cls");
						logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
						printf("\n 1 - Cadastrar usuário \n");
						multiplicarPrintf("-", 122);
						printf("\n 9 - Deslogar \n");
						multiplicarPrintf("-", 122);
						printf("\n / - Informar usuário ID \n");
						multiplicarPrintf("=", 122);
						printf("\n ERRO! selecione uma opção VÁLIDA! (1 ou 9) ou infome um usuário ID que esteja CADASTRADO!:");
						scanf("%s", &usuarioID);
						intUsuarioID = atoi(usuarioID);
						
						//Bloquear admin de ser analisado dentro de corrigir erros
						while (strcmp(usuarioID, usuario[1].ID) == 0){ //Compara se duas variáveis são iguais
							system("mode con:cols=122 lines=21"); //Definindo tamanho do console
							system("color 0A"); //Definindo cor do console
							system("cls");
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n 1 - Cadastrar usuário \n");
							multiplicarPrintf("-", 122);
							printf("\n 9 - Deslogar \n");
							multiplicarPrintf("-", 122);
							printf("\n / - Informar usuário ID \n");
							multiplicarPrintf("=", 122);
							printf("\n ERRO! selecione uma opção VÁLIDA! (1 ou 9) ou infome um usuário ID que NÃO esteja BLOQUEADO!:");
							scanf("%s", &usuarioID);
							intUsuarioID = atoi(usuarioID);
						}
						contadorMenuAdmin = 0;
					}
				}
				
				//Cadastrar novo usuário
				if (intUsuarioID == 1){
					
					//Em construção
					system("mode con:cols=122 lines=37"); //Definindo tamanho do console
					system("color 0A"); //Definindo cor do console
					system("cls");
					printf("\n\n EM CONSTRUÇÃO... \n\n");
					system("pause");
					
					/*contadorNovoUsuario = 0;
					do{
						
						//Verificar se tem espaço vazio
						espacoVazio = 0;
						
						for (contadorEspacoVazio = 0; contadorEspacoVazio < quantidadeDeValoresNoArray_usuario; contadorEspacoVazio++){
							if (strcmp(usuario[contadorEspacoVazio].ID, "00000") == 0){
								espacoVazio = 1;
							}
						}
						
						//Limitar máximo de cadastros
						if (quantidadeDeValoresNoArray_usuario == MAX_USUARIOS && espacoVazio == 0){
							system("mode con:cols=122 lines=13"); //Definindo tamanho do console
							system("color 0A"); //Definindo cor do console
							system("cls");
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n ERRO! infelizmente o sistema já atingiu o número máximo de cadastros! \n");
							multiplicarPrintf("=", 122);
							printf("\n Pressione qualquer tecla para voltar:");
							getch();
							break;
						}
						
						//Preencher espaços vazios
						if (strcmp(usuario[contadorNovoUsuario].ID, "00000") == 0){ //Comparar se tem alguma variável com valor 00000
							
							//Cadastrar usuário ID
							system("mode con:cols=122 lines=9"); //Definindo tamanho do console
							system("color 0A"); //Definindo cor do console
							system("cls");
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n Informe um novo usuário ID (código de cinco dígitos do verso do crachá):");
							scanf("%s", &usuarioID);
							
							//Só aceitar 5 dígitos
							while(strlen(usuarioID) != 5){
								system("mode con:cols=122 lines=9"); //Definindo tamanho do console
								system("color 0A"); //Definindo cor do console
								system("cls");
								logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
								printf("\n ERRO! informe um novo usuário ID de CINCO (5) dígitos (do verso do crachá)!:");
								scanf("%s", &usuarioID);
							}
							
							//Bloquear ID repetido
							
							for (contadorBloquearIdRepetido = 0; contadorBloquearIdRepetido < quantidadeDeValoresNoArray_usuario; contadorBloquearIdRepetido++){
								if (strcmp(usuarioID, usuario[contadorBloquearIdRepetido].ID) == 0){ //Compara se duas variáveis são iguais
									system("mode con:cols=122 lines=11"); //Definindo tamanho do console
									system("color 0A"); //Definindo cor do console
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n ERRO! informe um novo usuário ID (código de cinco dígitos do verso do crachá) que NÃO esteja CADASTRADO!:");
									scanf("%s", &usuarioID);
									
									//Só aceitar 5 dígitos
									while(strlen(usuarioID) != 5){
										system("mode con:cols=122 lines=10"); //Definindo tamanho do console
										system("color 0A"); //Definindo cor do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n ERRO! informe um novo usuário ID de CINCO (5) dígitos (do verso do crachá)!:");
										scanf("%s", &usuarioID);
									}
									
									contadorBloquearIdRepetido = 0;
								}
							}
							
							strcpy(usuario[contadorNovoUsuario].ID, usuarioID);
							
							//Cadastrar nome
							system("mode con:cols=122 lines=9"); //Definindo tamanho do console
							system("color 0A"); //Definindo cor do console
							system("cls");
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n Informe o primeiro nome do(a) novo(a) usuário(a):");
							scanf("%s", &usuario[contadorNovoUsuario].NOME);
							
							//Cadastrar senha
							strcpy(usuario[contadorNovoUsuario].SENHA, "0");
							
							//Confirmação
							system("mode con:cols=122 lines=17"); //Definindo tamanho do console
							system("color 0A"); //Definindo cor do console
							system("cls");
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorNovoUsuario].ID, usuario[contadorNovoUsuario].NOME);
							multiplicarPrintf("-", 122);
							printf("\n Cadastro efetuado com SUCESSO! \n");
							multiplicarPrintf("=", 122);
							printf("\n Pressione qualquer tecla para voltar:");
							getch();
							break;
							
						//Criar novos espaços
						}else if (strcmp(usuario[contadorNovoUsuario].ID, "") == 0){ //Comparar se tem alguma variável vazia
							//Cadastrar usuário ID
							system("mode con:cols=122 lines=9"); //Definindo tamanho do console
							system("color 0A"); //Definindo cor do console
							system("cls");
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n Informe um novo usuário ID (código de cinco dígitos do verso do crachá):");
							scanf("%s", &usuarioID);
							
							//Só aceitar 5 dígitos
							while(strlen(usuarioID) != 5){
								system("mode con:cols=122 lines=9"); //Definindo tamanho do console
								system("color 0A"); //Definindo cor do console
								system("cls");
								logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
								printf("\n ERRO! informe um novo usuário ID de CINCO (5) dígitos (do verso do crachá)!:");
								scanf("%s", &usuarioID);
							}
							
							//Bloquear ID repetido
							
							for (contadorBloquearIdRepetido = 0; contadorBloquearIdRepetido < quantidadeDeValoresNoArray_usuario; contadorBloquearIdRepetido++){
								if (strcmp(usuarioID, usuario[contadorBloquearIdRepetido].ID) == 0){ //Compara se duas variáveis são iguais
									system("mode con:cols=122 lines=11"); //Definindo tamanho do console
									system("color 0A"); //Definindo cor do console
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n ERRO! informe um novo usuário ID (código de cinco dígitos do verso do crachá) que NÃO esteja CADASTRADO!:");
									scanf("%s", &usuarioID);
									
									//Só aceitar 5 dígitos
									while(strlen(usuarioID) != 5){
										system("mode con:cols=122 lines=10"); //Definindo tamanho do console
										system("color 0A"); //Definindo cor do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n ERRO! informe um novo usuário ID de CINCO (5) dígitos (do verso do crachá)!:");
										scanf("%s", &usuarioID);
									}
									
									contadorBloquearIdRepetido = 0;
								}
							}
							
							strcpy(usuario[contadorNovoUsuario].ID, usuarioID);
							
							//Cadastrar nome
							system("mode con:cols=122 lines=9"); //Definindo tamanho do console
							system("color 0A"); //Definindo cor do console
							system("cls");
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n Informe o primeiro nome do(a) novo(a) usuário(a):");
							scanf("%s", &usuario[contadorNovoUsuario].NOME);
							
							//Cadastrar senha
							strcpy(usuario[contadorNovoUsuario].SENHA, "0");
							
							//Confirmação
							system("mode con:cols=122 lines=17"); //Definindo tamanho do console
							system("color 0A"); //Definindo cor do console
							system("cls");
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorNovoUsuario].ID, usuario[contadorNovoUsuario].NOME);
							multiplicarPrintf("-", 122);
							printf("\n Cadastro efetuado com SUCESSO! \n");
							multiplicarPrintf("=", 122);
							printf("\n Pressione qualquer tecla para voltar:");
							getch();
							break;
						}
						contadorNovoUsuario += 1;
					}while (sairCadastrarNovoUsuario == 0);*/
				}
				
				do{
					
					//Deslogar admin se ele enviar '9' em menu cadatrar usuário com pedir ID de login do usuário que vai ser analisado
					if (strcmp(usuarioID, usuario[0].ID) == 0){ //Compara se duas variáveis são iguais
						deslogarAdmin = 9;
						break;
					}
					
					//Deslogar ID 1, caso o usuário ID seja zeros, final um (ex: 00001) ou um (1), o programa loga no primeiro perfil que achar, no caso, de índice zero (0).
					if(intUsuarioID == 1){
						break;
					}
					
					intOpcaoMenuAdmin = 0;
					system("mode con:cols=122 lines=33"); //Definindo tamanho do console
					system("color 0A"); //Definindo cor do console
					system("cls");
					logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
					printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorMenuAdmin].ID, usuario[contadorMenuAdmin].NOME);
					multiplicarPrintf("=", 122);
					printf("\n 1 - Trocar nome \n");
					multiplicarPrintf("-", 122);
					printf("\n 2 - Trocar senha \n");
					multiplicarPrintf("-", 122);
					printf("\n 3 - Excluir \n");
					multiplicarPrintf("-", 122);
					printf("\n 0 - Voltar \n");
					multiplicarPrintf("-", 122);
					printf("\n 9 - Deslogar \n");
					multiplicarPrintf("=", 122);
					printf("\n Selecione uma opção (1, 2, 3, 0 ou 9):");
					scanf("%s", &opcaoMenuAdmin);
					intOpcaoMenuAdmin = atoi(opcaoMenuAdmin);
					
					//Corrigir erros pedir uma opção para o admin
					while (intOpcaoMenuAdmin != 1 && intOpcaoMenuAdmin != 2 && intOpcaoMenuAdmin != 3 && opcaoMenuAdmin[0] != '0' && intOpcaoMenuAdmin != 9){
						system("mode con:cols=122 lines=34"); //Definindo tamanho do console
						system("color 0A"); //Definindo cor do console
						system("cls");
						logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
						printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorMenuAdmin].ID, usuario[contadorMenuAdmin].NOME);
						multiplicarPrintf("=", 122);
						printf("\n 1 - Trocar nome \n");
						multiplicarPrintf("-", 122);
						printf("\n 2 - Trocar senha \n");
						multiplicarPrintf("-", 122);
						printf("\n 3 - Excluir \n");
						multiplicarPrintf("-", 122);
						printf("\n 0 - Voltar \n");
						multiplicarPrintf("-", 122);
						printf("\n 9 - Deslogar \n");
						multiplicarPrintf("=", 122);
						printf("\n ERRO! selecione uma opção VÁLIDA! (1, 2, 3, 0 ou 9):");
						fflush(stdin); //Sem limpar o buffer de entrada entra em um loop infinito
						scanf("%s", &opcaoMenuAdmin);
						intOpcaoMenuAdmin = atoi(opcaoMenuAdmin);
					}
					
					//Decisões do admin
					switch (intOpcaoMenuAdmin){
						
						//Admin trocar nome
						case 1:
							system("mode con:cols=122 lines=13"); //Definindo tamanho do console
							system("color 0A"); //Definindo cor do console
							system("cls");
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n Usuário ID: %s | Nome atual: %s \n ", usuario[contadorMenuAdmin].ID, usuario[contadorMenuAdmin].NOME);
							multiplicarPrintf("=", 122);
							printf("\n Informe o novo nome:");
							scanf("%s", usuario[contadorMenuAdmin].NOME);
							break;
							
						//Admin trocar senha
						case 2:
							//Trocando senha
							system("mode con:cols=122 lines=15"); //Definindo tamanho do console
							system("color 0A"); //Definindo cor do console
							system("cls");
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorMenuAdmin].ID, usuario[contadorMenuAdmin].NOME);
							multiplicarPrintf("=", 122);
							printf("\n Informe uma nova senha ou deixe zero (0) caso queira que a mesma seja criada no momento do login:");
							scanf("%s", usuario[contadorMenuAdmin].SENHA);
							
							//Exibindo nova senha
							if (strcmp(usuario[contadorMenuAdmin].SENHA, "0") != 0){ //Comparar se uma variável tem um valor específico diferente
								system("mode con:cols=122 lines=17"); //Definindo tamanho do console
								system("color 0A"); //Definindo cor do console
								system("cls");
								logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
								printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorMenuAdmin].ID, usuario[contadorMenuAdmin].NOME);
								multiplicarPrintf("=", 122);
								printf("\n Senha alterada para: %s \n", usuario[contadorMenuAdmin].SENHA);
								multiplicarPrintf("=", 122);
								printf("\n Pressione qualquer tecla para voltar:");
								getch();
							}else{
								system("mode con:cols=122 lines=18"); //Definindo tamanho do console
								system("color 0A"); //Definindo cor do console
								system("cls");
								logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
								printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorMenuAdmin].ID, usuario[contadorMenuAdmin].NOME);
								multiplicarPrintf("=", 122);
								printf("\n Senha RESETADA, uma nova senha será criada no momento do login \n");
								multiplicarPrintf("=", 122);
								printf("\n Pressione qualquer tecla para voltar:");
								getch();
							}
							
							break;
							
						//Menu excluir usuário
						case 3:
							system("mode con:cols=122 lines=19"); //Definindo tamanho do console
							system("color 0A"); //Definindo cor do console
							system("cls");
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n Usuário ID: %s | Nome atual: %s \n ", usuario[contadorMenuAdmin].ID, usuario[contadorMenuAdmin].NOME);
							multiplicarPrintf("=", 122);
							printf("\n Tem certeza de que deseja excluir este usuário? \n");
							printf(" 1 - Sim \n");
							printf(" 0 - Não \n");
							multiplicarPrintf("=", 122);
							printf("\n Selecione uma opção (1 ou 0):");
							scanf("%s", &opcaoExcluirUsuario);
							intOpcaoExcluirUsuario = atoi(opcaoExcluirUsuario);
							
								
							//Corrigir erros menu confirmarção excluir usuário
							while (opcaoExcluirUsuario[0] != '0' && intOpcaoExcluirUsuario != 1){
								system("mode con:cols=122 lines=19"); //Definindo tamanho do console
								system("color 0A"); //Definindo cor do console
								system("cls");
								logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
								printf("\n Usuário ID: %s | Nome atual: %s \n ", usuario[contadorMenuAdmin].ID, usuario[contadorMenuAdmin].NOME);
								multiplicarPrintf("=", 122);
								printf("\n Tem certeza de que deseja excluir este usuário? \n");
								printf(" 1 - Sim \n");
								printf(" 0 - Não \n");
								multiplicarPrintf("=", 122);
								printf("\n ERRO! selecione uma opção VÁLIDA! (1 ou 0):");
								fflush(stdin); //Sem limpar o buffer de entrada entra em um loop infinito
								scanf("%s", &opcaoExcluirUsuario);
								intOpcaoExcluirUsuario = atoi(opcaoExcluirUsuario);
							}
							//Excluir usuário
							if (intOpcaoExcluirUsuario == 1){
								strcpy(usuario[contadorMenuAdmin].NOME, "0");
								strcpy(usuario[contadorMenuAdmin].ID, "00000");
								strcpy(usuario[contadorMenuAdmin].SENHA, "0");
								intOpcaoMenuAdmin = 0;
								break;
							}else{
								break;
							}
						//Voltar, trocar usuário
						case 0: //Case desnecessária, intOpcaoMenuAdmin já tá igual a 0
							intOpcaoMenuAdmin = 0;
							break;
							
						//Deslogar admin
						case 9:
							intOpcaoMenuAdmin = 0;
							deslogarAdmin = 9;
							break;
					}
				}while (intOpcaoMenuAdmin != 0);
			}while (deslogarAdmin != 9);
			
		//Se logar como usuário
		}else{
			do{
				//Deslogar usuário se ele for índice '0'
				if (strcmp(loginID, usuario[0].ID) == 0){ //Compara se duas variáveis são iguais
					break;
				}
				
				intOpcaoMenuPrincipal = 0;
				system("mode con:cols=122 lines=37"); //Definindo tamanho do console
				system("color B0"); //Definindo cor do console
				system("cls");
				logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
				printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
				multiplicarPrintf("=", 122);
				printf("\n 1 - Passageiros \n");
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
					system("mode con:cols=122 lines=38"); //Definindo tamanho do console
					system("color B0"); //Definindo cor do console
					system("cls");
					logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
					printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
					multiplicarPrintf("=", 122);
					printf("\n 1 - Passageiros \n");
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
							do{
								//Menu Cargas
								system("mode con:cols=122 lines=30"); //Definindo tamanho do console
								system("color B0"); //Definindo cor do console
								logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
								printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
								multiplicarPrintf("=", 122);
								printf("\n 1 - Cadastrar novos \n");
								multiplicarPrintf("-", 122);
								printf("\n 2 - Listar todos \n");
								multiplicarPrintf("-", 122);
								printf("\n 3 - Excluir \n");
								multiplicarPrintf("-", 122);
								printf("\n 0 - Voltar \n");
								multiplicarPrintf("=", 122);
								printf("\n Selecione uma opção (1, 2, 3, ou 0):");
								scanf("%s", &opcaoMenuCargas);
								intOpcaoMenuCargas = atoi(opcaoMenuCargas);
								
								//Corrigir erros pedir uma opção para o usuário
								while (intOpcaoMenuCargas != 1 && intOpcaoMenuCargas != 2 && intOpcaoMenuCargas != 3 && intOpcaoMenuCargas != 0){
									system("mode con:cols=122 lines=38"); //Definindo tamanho do console
									system("color B0"); //Definindo cor do console
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									printf("\n 1 - Cadastrar novos \n");
									multiplicarPrintf("-", 122);
									printf("\n 2 - Listar todos \n");
									multiplicarPrintf("-", 122);
									printf("\n 3 - Excluir \n");
									multiplicarPrintf("-", 122);
									printf("\n 0 - Voltar \n");;
									multiplicarPrintf("=", 122);
									printf("\n ERRO! selecione uma opção VÁLIDA! (1, 2, 3, ou 0):");
									fflush(stdin); //Sem limpar o buffer de entrada entra em um loop infinito
									scanf("%s", &opcaoMenuCargas);
									intOpcaoMenuCargas = atoi(opcaoMenuCargas);
								}
								indiceCodigoCarga = 0;
								contadorCodigoCarga = 0;
								
								if (intOpcaoMenuCargas == 1){
									//Preencer espaços vazios ao cadastrar cargas
									indiceCodigoCarga = -1; // inicializa com -1, indicando que não há elementos com código zero
									for (contadorCodigoCarga = 0; contadorCodigoCarga < MAX_CARGAS; contadorCodigoCarga++) {
									    if (carga[contadorCodigoCarga].CODIGO_CARGA == 0) {
									        indiceCodigoCarga = contadorCodigoCarga;
									        break; // interrompe o loop assim que encontrar o primeiro elemento com código zero
									    }
									}
									
									system("mode con:cols=122 lines=38"); //Definindo tamanho do console
									system("color B0"); //Definindo cor do console
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									
									//Código de embarque
									printf("\n Código de embarque:");
									scanf("%s", codigoCarga);
									intCodigoCarga = atoi(codigoCarga);
									
									while (!isdigit(codigoCarga[indiceCodigoCarga])) {//Só aceita números
										system("mode con:cols=122 lines=38"); //Definindo tamanho do console
										system("color B0"); //Definindo cor do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
										multiplicarPrintf("=", 122);
									    printf("\n ERRO! código de embarque INVÁLIDO!: ");
									    scanf("%s", codigoCarga);
									    intCodigoCarga = atoi(codigoCarga);
									}
									
									// Verifica se o código de embarque já existe
									codigoExistente = 0;
									for (i = 0; i < MAX_CARGAS; i++) {
									    if (carga[i].CODIGO_CARGA == intCodigoCarga) {
									        codigoExistente = 1;
									        break;
									    }
									}
									
									// Se o código já existe, pede para o usuário digitar novamente
									while (codigoExistente) {
										system("mode con:cols=122 lines=38"); //Definindo tamanho do console
										system("color B0"); //Definindo cor do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
										multiplicarPrintf("=", 122);
									    printf("\n ERRO! Código de embarque JÁ CADASTRADO!: ");
									    scanf("%s", codigoCarga);
									    intCodigoCarga = atoi(codigoCarga);
									    
									    while (!isdigit(codigoCarga[indiceCodigoCarga])) {
											system("mode con:cols=122 lines=38"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
										    printf("\n ERRO! código de embarque INVÁLIDO!: ");
										    scanf("%s", codigoCarga);
										    intCodigoCarga = atoi(codigoCarga);
										}
									
									    // Verifica novamente se o código já existe
									    codigoExistente = 0;
									    for (i = 0; i < MAX_CARGAS; i++) {
									        if (carga[i].CODIGO_CARGA == intCodigoCarga) {
									            codigoExistente = 1;
									            break;
									        }
									    }
									}
									
									carga[indiceCodigoCarga].CODIGO_CARGA = intCodigoCarga;
									//strcpy(&carga[1].CODIGO_CARGA, intCodigoCarga);
									multiplicarPrintf("-", 122);
									
									//Descrição
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									printf("\n Código de embarque: %i", carga[indiceCodigoCarga].CODIGO_CARGA);
									multiplicarPrintf("-", 122);
									
									printf("\n Descrição:");
									scanf("%s", &carga[indiceCodigoCarga].DESCRICAO_CARGA);
									multiplicarPrintf("-", 122);
									
									//Dimensões
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									printf("\n Código de embarque: %i", carga[indiceCodigoCarga].CODIGO_CARGA);
									multiplicarPrintf("-", 122);
									printf("\n Descrição: %s", carga[indiceCodigoCarga].DESCRICAO_CARGA);
									multiplicarPrintf("-", 122);
									
									printf("\n Dimensões:");
									scanf("%s", &carga[indiceCodigoCarga].DIMENSOES_CARGA);
									multiplicarPrintf("-", 122);
									
									//Peso
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									printf("\n Código de embarque: %i", carga[indiceCodigoCarga].CODIGO_CARGA);
									multiplicarPrintf("-", 122);
									printf("\n Descrição: %s", carga[indiceCodigoCarga].DESCRICAO_CARGA);
									multiplicarPrintf("-", 122);
									printf("\n Dimensões: %s", carga[indiceCodigoCarga].DIMENSOES_CARGA);
									multiplicarPrintf("-", 122);
									
								    printf("\n Peso:");
								    scanf("%s", &pesoCarga);
								    floatPesoCarga = atof(pesoCarga);
								    while (sscanf(pesoCarga, "%f", &floatPesoCarga) != 1){
								    	system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
										multiplicarPrintf("=", 122);
										printf("\n Código de embarque: %i", carga[indiceCodigoCarga].CODIGO_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Descrição: %s", carga[indiceCodigoCarga].DESCRICAO_CARGA);
										multiplicarPrintf("-", 122);
										printf("\n Dimensões: %s", carga[indiceCodigoCarga].DIMENSOES_CARGA);
										multiplicarPrintf("-", 122);
								        printf("\n ERRO! peso INVÁLIDO!:\n");
								        scanf("%s", &pesoCarga);
								        floatPesoCarga = atof(pesoCarga);
								    }
									carga[indiceCodigoCarga].PESO_CARGA = floatPesoCarga;
									//strcpy(carga[1].PESO_CARGA, floatPesoCarga);
									multiplicarPrintf("-", 122);
									
									//Local de Embarque
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									printf("\n Código de embarque: %i", carga[indiceCodigoCarga].CODIGO_CARGA);
									multiplicarPrintf("-", 122);
									printf("\n Descrição: %s", carga[indiceCodigoCarga].DESCRICAO_CARGA);
									multiplicarPrintf("-", 122);
									printf("\n Dimensões: %s", carga[indiceCodigoCarga].DIMENSOES_CARGA);
									multiplicarPrintf("-", 122);
									printf("\n Peso: %.2f", carga[indiceCodigoCarga].PESO_CARGA);
									multiplicarPrintf("-", 122);
									
									printf("\n Local de Embarque:");
									scanf("%s", &carga[indiceCodigoCarga].EMBARQUE_CARGA);
									multiplicarPrintf("-", 122);
									
									//Local de Desembarque
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									printf("\n Código de embarque: %i", carga[indiceCodigoCarga].CODIGO_CARGA);
									multiplicarPrintf("-", 122);
									printf("\n Descrição: %s", carga[indiceCodigoCarga].DESCRICAO_CARGA);
									multiplicarPrintf("-", 122);
									printf("\n Dimensões: %s", carga[indiceCodigoCarga].DIMENSOES_CARGA);
									multiplicarPrintf("-", 122);
									printf("\n Peso: %.2f", carga[indiceCodigoCarga].PESO_CARGA);
									multiplicarPrintf("-", 122);
									printf("\n Local de Embarque: %s", carga[indiceCodigoCarga].EMBARQUE_CARGA);
									multiplicarPrintf("-", 122);
									
									printf("\n Local de Desembarque:");
									scanf("%s", &carga[indiceCodigoCarga].DESEMBARQUE_CARGA);
									multiplicarPrintf("=", 122);
									
								}else if (intOpcaoMenuCargas == 2){
									haCargasRegistradas = false;
									for (contadorHaCargasRegistradas = 0; contadorHaCargasRegistradas < MAX_CARGAS; contadorHaCargasRegistradas++) {
									    if (carga[contadorHaCargasRegistradas].CODIGO_CARGA != 0) {
									        haCargasRegistradas = true;
									        break;
									    }
									}
									if (!haCargasRegistradas) {
										system("mode con:cols=122 lines=150"); //Definindo tamanho do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
										multiplicarPrintf("=", 122);
									    printf("\n Não há cargas registradas \n");
									    multiplicarPrintf("=", 122);
									    printf("\n Pressione qualquer tecla para voltar:");
										getch();
									}else{
										system("mode con:cols=122 lines=150"); //Definindo tamanho do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
										multiplicarPrintf("=", 122);
										quantidadeDeValoresNoArray_carga -= 1;
										for (contadorExibirCargas = 0; contadorExibirCargas < quantidadeDeValoresNoArray_carga ;contadorExibirCargas++){
											printf("\n Código de embarque: %i \n", carga[contadorExibirCargas].CODIGO_CARGA);
											printf("\n Descrição: %s \n", carga[contadorExibirCargas].DESCRICAO_CARGA);
											printf("\n Dimensões: %s \n", carga[contadorExibirCargas].DIMENSOES_CARGA);
											printf("\n Peso: %.2f \n", carga[contadorExibirCargas].PESO_CARGA);
											printf("\n Local de Embarque: %s \n", carga[contadorExibirCargas].EMBARQUE_CARGA);
											printf("\n Dimensões: %s \n", carga[contadorExibirCargas].DIMENSOES_CARGA);
											if (contadorExibirCargas < quantidadeDeValoresNoArray_carga - 1){
												multiplicarPrintf("-", 122);
											}
										}
										multiplicarPrintf("=", 122);
										printf("\n Pressione qualquer tecla para voltar:");
										getch();
									}
									
								}else if (intOpcaoMenuCargas == 3){
									
									//Não tem carga
									haCargasRegistradas = false;
									for (contadorHaCargasRegistradas = 0; contadorHaCargasRegistradas < MAX_CARGAS; contadorHaCargasRegistradas++) {
									    if (carga[contadorHaCargasRegistradas].CODIGO_CARGA != 0) {
									        haCargasRegistradas = true;
									        break;
									    }
									}
									if (!haCargasRegistradas) {
										system("mode con:cols=122 lines=30"); //Definindo tamanho do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
										multiplicarPrintf("=", 122);
									    printf("\n Não há cargas para serem excluídas \n");
									    multiplicarPrintf("=", 122);
									    printf("\n Pressione qualquer tecla para voltar:");
										getch();
										
									//Tem carga
									}else{
										system("mode con:cols=122 lines=30"); //Definindo tamanho do console
										system("cls");
										logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
										printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
										multiplicarPrintf("=", 122);
										printf("Digite o código de embarque que deseja excluír: ");
										scanf("%s", &excluirCodigoCarga);
										intExcluirCodigoCarga = atoi(excluirCodigoCarga);
										
										verificarSeTemCodigoCarga = 0;
										contadorVerificarSeTemCodigoCarga;
										for (contadorVerificarSeTemCodigoCarga = 0; contadorVerificarSeTemCodigoCarga < MAX_CARGAS; contadorVerificarSeTemCodigoCarga++) {
											if (carga[contadorVerificarSeTemCodigoCarga].CODIGO_CARGA == intExcluirCodigoCarga) {
										        verificarSeTemCodigoCarga = 1;
										    }
										}
										
									    if (verificarSeTemCodigoCarga == 1) {
											
											system("mode con:cols=122 lines=30"); //Definindo tamanho do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n Código de embarque: %i \n", carga[intExcluirCodigoCarga].CODIGO_CARGA);
											printf("\n Descrição: %s \n", carga[intExcluirCodigoCarga].DESCRICAO_CARGA);
											printf("\n Dimensões: %s \n", carga[intExcluirCodigoCarga].DIMENSOES_CARGA);
											printf("\n Peso: %.2f \n", carga[intExcluirCodigoCarga].PESO_CARGA);
											printf("\n Local de Embarque: %s \n", carga[intExcluirCodigoCarga].EMBARQUE_CARGA);
											printf("\n Dimensões: %s \n", carga[intExcluirCodigoCarga].DIMENSOES_CARGA);
											multiplicarPrintf("=", 122);
											printf("\n Tem certeza de que deseja excluir essa carga? \n");
											printf(" 1 - Sim \n");
											printf(" 0 - Não \n");
											multiplicarPrintf("=", 122);
											printf("\n Selecione uma opção (1 ou 0):");
											scanf("%s", &opcaoExcluirCarga);
											intOpcaoExcluirCarga = atoi(opcaoExcluirCarga);
											
												
											/*/Corrigir erros menu confirmarção excluir usuário
											while (opcaoExcluirCarga[0] != '0' && intOpcaoExcluirCarga != 1){
												system("mode con:cols=122 lines=30"); //Definindo tamanho do console
												system("cls");
												logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
												printf("\n Código de embarque: %i \n", carga[intExcluirCodigoCarga].CODIGO_CARGA);
												printf("\n Descrição: %s \n", carga[intExcluirCodigoCarga].DESCRICAO_CARGA);
												printf("\n Dimensões: %s \n", carga[intExcluirCodigoCarga].DIMENSOES_CARGA);
												printf("\n Peso: %.2f \n", carga[intExcluirCodigoCarga].PESO_CARGA);
												printf("\n Local de Embarque: %s \n", carga[intExcluirCodigoCarga].EMBARQUE_CARGA);
												printf("\n Dimensões: %s \n", carga[intExcluirCodigoCarga].DIMENSOES_CARGA);
												multiplicarPrintf("=", 122);
												printf("\n Tem certeza de que deseja excluir essa carga? \n");
												printf(" 1 - Sim \n");
												printf(" 0 - Não \n");
												multiplicarPrintf("=", 122);
												printf("\n ERRO! selecione uma opção VÁLIDA! (1 ou 0):");
												fflush(stdin); //Sem limpar o buffer de entrada entra em um loop infinito
												scanf("%s", &opcaoExcluirCarga);
												intOpcaoExcluirCarga = atoi(opcaoExcluirCarga);
											}*/
											if(intOpcaoExcluirCarga == 1){
												for (contadorExcluirCodigoCarga = 0; contadorExcluirCodigoCarga < MAX_CARGAS; contadorExcluirCodigoCarga++) {
												    if (carga[contadorExcluirCodigoCarga].CODIGO_CARGA == intExcluirCodigoCarga) {
												        carga[contadorExcluirCodigoCarga].CODIGO_CARGA = 0;
												        strcpy(carga[contadorExcluirCodigoCarga].DESCRICAO_CARGA, "n");
												        strcpy(carga[contadorExcluirCodigoCarga].DIMENSOES_CARGA, "0x0x0");
												        carga[contadorExcluirCodigoCarga].PESO_CARGA = 0;
												        strcpy(carga[contadorExcluirCodigoCarga].EMBARQUE_CARGA, "n");
												        strcpy(carga[contadorExcluirCodigoCarga].DESEMBARQUE_CARGA, "n");
												        break;
												    }
												}
											}
									    }else{
									    	system("mode con:cols=122 lines=30"); //Definindo tamanho do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n Usuário ID: %s | Nome: %s \n", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n ERRO! carga não registrada! \n");
											multiplicarPrintf("=", 122);
											printf("\n Pressione qualquer tecla para voltar:");
											getch();
										}
									}
								}else if (intOpcaoMenuCargas == 0){
									break;
								}
								//Cadastrar novos
								//Listar todos
								//Excluir
								//(Código de embarque, Descrição, Dimensões, Peso, Local de Embarque, Local de Desembarque).
							}while (sairMenuCarga == 0);
							break;
						case 3:
							//Menu Tripulação
							system("mode con:cols=122 lines=37"); //Definindo tamanho do console
							system("color E0"); //Definindo cor do console
							system("cls");
							printf("\n\n EM CONSTRUÇÃO... \n\n");
							system("pause");
							break;
						case 4:
							//Ajuda (dúvidas gerais de como usar o sistema)
							system("mode con:cols=122 lines=30"); //Definindo tamanho do console
							system("color B0"); //Definindo cor do console
							system("cls");
							logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
							printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
							multiplicarPrintf("=", 122);
							printf("\n O usuário ID usado para logar é o mesmo código de cinco dígitos que se encontra no verso do crachá de cada funcionário(a) \n");
							multiplicarPrintf("-", 122);
							printf("\n Caso tenha algum problema com nome ou senha entre em contato com um Administrador \n");
							multiplicarPrintf("-", 122);
							printf("\n Você pode alterar sua senha aqui mesmo na tela de ajuda \n");
							multiplicarPrintf("-", 122);
							printf("\n Para navegar no programa é bem simples, basta ler, ele está bem alto explicativo \n");
							multiplicarPrintf("=", 122);
							printf("\n 7 - Trocar senha \n");
							multiplicarPrintf("-", 122);
							printf("\n 0 - Voltar \n");
							multiplicarPrintf("=", 122);
							printf("\n Selecione uma opção (7 ou 0):");
							scanf("%s", opcaoAjuda);
							intOpcaoAjuda = atoi(opcaoAjuda);
							
							//Corrigir erros pedir uma opção para o usuário
							while (opcaoAjuda[0] != '0' && intOpcaoAjuda != 7){
								//Ajuda (dúvidas gerais de como usar o sistema)
								system("mode con:cols=122 lines=30"); //Definindo tamanho do console
								system("color B0"); //Definindo cor do console
								system("cls");
								logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
								printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
								multiplicarPrintf("=", 122);
								printf("\n O usuário ID usado para logar é o mesmo código de cinco dígitos que se encontra no verso do crachá de cada funcionário(a) \n");
								multiplicarPrintf("-", 122);
								printf("\n Caso tenha algum problema com nome ou senha entre em contato com um Administrador \n");
								multiplicarPrintf("-", 122);
								printf("\n Você pode alterar sua senha aqui mesmo na tela de ajuda \n");
								multiplicarPrintf("-", 122);
								printf("\n Para navegar no programa é bem simples, basta ler, ele está bem alto explicativo \n");
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
									
									//Criar senha do usuário
									system("mode con:cols=122 lines=13"); //Definindo tamanho do console
									system("color B0"); //Definindo cor do console
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									printf("\n Informe uma nova senha:");
									scanf("%s", usuario[contadorUsuario].SENHA);
									
									//Bloquear senha '0'
									if (strcmp(usuario[contadorUsuario].SENHA, "0") == 0){ //Comparar se uma variável tem um valor específico igual
										do{
											system("mode con:cols=122 lines=14"); //Definindo tamanho do console
											system("color B0"); //Definindo cor do console
											system("cls");
											logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
											printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
											multiplicarPrintf("=", 122);
											printf("\n ERRO! essa senha está BLOQUEADA!:");
											scanf("%s", usuario[contadorUsuario].SENHA);
										}while (strcmp(usuario[contadorUsuario].SENHA, "0") == 0); //Comparar se uma variável tem um valor específico igual
									}
									
									//Confirmar criar senha do usuário
									system("mode con:cols=122 lines=13"); //Definindo tamanho do console
									system("color B0"); //Definindo cor do console
									system("cls");
									logo((122 -14) / 2); //(cols(largura da página) - 14) / 2
									printf("\n Usuário ID: %s | Nome: %s \n ", usuario[contadorUsuario].ID, usuario[contadorUsuario].NOME);
									multiplicarPrintf("=", 122);
									printf("\n Confirme sua nova senha:");
									scanf("%s", confirmarSenha);
									
								}while(strcmp(usuario[contadorUsuario].SENHA, confirmarSenha) != 0); //Comparar se duas variável são diferentes
								break;
							}else{
								break;
							}
						case 5:
							//Sobre (versão do sistema, desenvolvido por, sobre o sistema e funcionalidades em geral, direitos reservados, etc.) 
							system("mode con:cols=122 lines=50"); //Definindo tamanho do console
							system("color B0"); //Definindo cor do console
							system("cls");
							multiplicarPrintf("=", 122);
							printf("\n Versão: Beta 1.0 \n");
							multiplicarPrintf("-", 122);
							printf("\n Desenvolvido por André Felipe de Moraes \n");
							printf(" E-mail para contato: 0000969778@senaimgaluno.com.br \n");
							multiplicarPrintf("-", 122);
							printf("\n Sistema Desenvolvido para a empresa 'Boto-Rosa Ltda',\n Com o intuito de solucionar os problemas de gestão de\n transportes da mesma \n");
							multiplicarPrintf("=", 122);
							printf("\n Pressione qualquer tecla para voltar:");
							getch();
							break;
					}
			}while (intOpcaoMenuPrincipal != 9);
		}
	}while(fecharPrograma == 0);
	
	return 0; // Sair do programa com sucesso
}

//Definindo funções
//Multiplicar Printf
void multiplicarPrintf(const char *caracter, int multiplicarPor) { //Estrutura: (caracter, quantidade a ser mulplicado)
    int contadormultiplicarPrintf = 0;
    printf("\n");
    for (contadormultiplicarPrintf = 0; contadormultiplicarPrintf < multiplicarPor; contadormultiplicarPrintf++) {
        printf("%s", caracter);
    }
    printf("\n");
}

//Exibir logo "Boto-Rosa Ltda"
void logo(int quantidadeEspacos){
	system("cls");
	multiplicarPrintf("=", quantidadeEspacos+14+quantidadeEspacos);
	printf("\n%*sBoto-Rosa Ltda\n", quantidadeEspacos, "");
	multiplicarPrintf("=", quantidadeEspacos+14+quantidadeEspacos);
}

/*
corrigir bug de criar noto usuario em novo espaço
regular quantidade de linhas de cada página
arrys com  limite cem [100], mudar para ilimitado
*/