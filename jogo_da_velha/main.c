// Jogo da velha diferente
// Ser um jogo 
// Thalisson Santos
// 22/09/2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Renderiza todo o jogo
void render(int tabuleiro[][3][2], int players[][6], int vez,int rodada, bool jogada_invalida);

// Renderiza as peças dos players
void render_players(int players[][6], int vez);

// Validar movimento do jogador
bool validar_movimento(char jogada[], int vez, int players[][6], int tabuleiro[][3][2], char peca_player[]);

// Retorna o valor da jogada em numero
int valor_da_jogada(char peca_player[], char jogada[]);

// Verifiva se a partida acabou
int verificar_fim(int players[][6], int tabuleiro[][3][2]);

int main()
{
    int tabuleiro[3][3][2];
    int players[2][6];
    int vez = 0;
    char jogada[3];
    int rodada = 0;
    bool jogada_invalida = false;
    bool run = true;

    // Iniciando peças dos players
    if(rodada == 0)
    {
        for(int i = 0; i < 2; i++)
        {
           players[i][0] = 3;
           players[i][1] = 3;
           players[i][2] = 2;
           players[i][3] = 2;
           players[i][4] = 1;
           players[i][5] = 1;
        }
    }

    while(run)
    {
        render(tabuleiro, players, vez, rodada, jogada_invalida);
        
        scanf("%s", jogada);

        char peca_player[3];

        if(vez == 0)
        {
            peca_player[0] = 'X';
            peca_player[1] = 'x';
            peca_player[2] = '.';
        }
        else if(vez == 1)
        {
            peca_player[0] = 'O';
            peca_player[1] = 'o';
            peca_player[2] = ',';
        }

        if(validar_movimento(jogada, vez, players, tabuleiro, peca_player))
        {
            jogada_invalida = false;

            int jogada_int = valor_da_jogada(peca_player, jogada);

            for(int i = 0; i < 6; i++)
            {
                if(players[vez][i] == jogada_int)
                {
                    players[vez][i] = 0;

                    int linha = jogada[1] - '0';
                    int coluna = jogada[2] - '0';

                    tabuleiro[linha-1][coluna-1][0] = jogada_int;
                    tabuleiro[linha-1][coluna-1][1] = vez;

                    break;
                }
            }

            int verificar = verificar_fim(players, tabuleiro);

            if(verificar == 0)
            {
                run = true;

                if(vez == 0)
                {
                    vez = 1;
                }
                else if(vez == 1)
                {
                    vez = 0;
                }

                rodada++;
            }
            else if(verificar == 1 || verificar == 2)
            {   
                rodada++;
                render(tabuleiro, players, vez, rodada, jogada_invalida);
                run = false;
            }
        }
        else
        {
            jogada_invalida = true;
        }
    }

    return 0;
}


void render(int tabuleiro[][3][2], int players[][6], int vez, int rodada, bool jogada_invalida)
{
    system("clear");

    printf("  Jogo da Velha\n");
    printf("   (Diferente)\n");
    printf("    Rodada %d\n\n", rodada);

    if(rodada == 0)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                tabuleiro[i][j][0] = 0;
                tabuleiro[i][j][1] = 2;
            }
        }
    }
    
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {   

            if(tabuleiro[i][j][0] == 0){
                printf("     ");
            }
            else if(tabuleiro[i][j][0] == 1 && tabuleiro[i][j][1] == 0)
            {
                printf("  .  ");
            }
            else if(tabuleiro[i][j][0] == 2 && tabuleiro[i][j][1] == 0)
            {
                printf("  x  ");
            }
            else if(tabuleiro[i][j][0] == 3 && tabuleiro[i][j][1] == 0)
            {
                printf("  X  ");
            }
            else if(tabuleiro[i][j][0] == 1 && tabuleiro[i][j][1] == 1)
            {
                printf("  ,  ");
            }
            else if(tabuleiro[i][j][0] == 2 && tabuleiro[i][j][1] == 1)
            {
                printf("  o  ");
            }
            else if(tabuleiro[i][j][0] == 3 && tabuleiro[i][j][1] == 1)
            {
                printf("  O  ");
            }

            if(j < 2)
            {
                printf("|");
            }
        }

        if(i < 2) 
        {
            printf("\n-----+-----+-----\n");
        }
        else
        {
            printf("\n\n");
        }
    }

    printf("Player 1: ");
    render_players(players, 0);

    printf("Player 2: ");
    render_players(players, 1);

    if(jogada_invalida)
    {
        printf("\nJOGADA INVALIDA!\n");
    }

    int verificar = verificar_fim(players, tabuleiro);

    if(verificar == 0)
    {
        printf("\nPlayer %d:\n", vez+1);
        printf("Digite peça linha coluna (ex.: X13)\n");
        printf("Movimento: ");
    }
    else if(verificar == 1)
    {
        printf("\nEMPATE\n");
    }
    else if(verificar == 2)
    {
        printf("\nPlayer %d: VENCEDOR\n", vez+1);
    }
}


void render_players(int players[][6], int vez)
{
    for(int i = 0; i < 6; i++)
    {
        if(players[vez][i] != 0)
        {
            if(vez == 0)
            {
                if(i == 0 || i == 1)
                {
                    printf("X ");
                }
                else if(i == 2 || i == 3)
                {
                    printf("x ");
                }
                else if(i == 4 || i == 5)
                {
                    printf(". ");
                }
            }
            else if(vez == 1)
            {
                if(i == 0 || i == 1)
                {
                    printf("O ");
                }
                else if(i == 2 || i == 3)
                {
                    printf("o ");
                }
                else if(i == 4 || i == 5)
                {
                    printf(", ");
                }
            }
        }
    }

    printf("\n");
}


bool validar_movimento(char jogada[], int vez, int players[][6], int tabuleiro[][3][2], char peca_player[])
{
    if(jogada[0] == peca_player[2] || jogada[0] == peca_player[1] || jogada[0] == peca_player[0])
    {
        if(jogada[1] == '1' || jogada[1] == '2' || jogada[1] == '3')
        {
            if(jogada[2] == '1' || jogada[2] == '2' || jogada[2] == '3')
            {   
                int jogada_int = valor_da_jogada(peca_player, jogada);
                bool continuar = false;
                
                for(int i = 0; i < 6; i++)
                {
                    if(players[vez][i] == jogada_int)
                    {
                        continuar = true;
                        break;
                    }
                }

                if(continuar)
                {
                    int linha = jogada[1] - '0';
                    int coluna = jogada[2] - '0';

                    if(tabuleiro[linha - 1][coluna - 1][0] < jogada_int)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


int valor_da_jogada(char peca_player[], char jogada[])
{
    int jogada_int;

    if(jogada[0] == peca_player[0])
    {
        jogada_int = 3;
    }
    else if(jogada[0] == peca_player[1])
    {
        jogada_int = 2;
    }
    else if(jogada[0] == peca_player[2])
    {
        jogada_int = 1;
    }

    return jogada_int;
}


int verificar_fim(int players[][6], int tabuleiro[][3][2])
{
    int soma = 0;
    int soma2 = 0;
    int cont0 = 0;
    int cont1 = 0;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(tabuleiro[i][j][1] == 0)
            {
                cont0++;
            }

            if(tabuleiro[i][j][1] == 1)
            {
                cont1++;
            }
        }

        if(cont0 == 3 || cont1 == 3)
        {
            return 2;
        }

        cont0 = 0;
        cont1 = 0;
   
        for(int j = 0; j < 3; j++)
        {
            if(tabuleiro[j][i][1] == 0)
            {
                cont0++;
            }

            if(tabuleiro[j][i][1] == 1)
            {
                cont1++;
            }
        }

        if(cont0 == 3 || cont1 == 3)
        {   
            return 2;
        }

        cont0 = 0;
        cont1 = 0;
    }

    for(int i = 0; i < 3; i++)
    {
        if(tabuleiro[i][i][1] == 0)
        {
            cont0++;
        }

        if(tabuleiro[i][i][1] == 1)
        {
            cont1++;
        }
    }

    if(cont0 == 3 || cont1 == 3)
    {
        return 2;
    }

    cont0 = 0;
    cont1 = 0;
    
    for(int i = 2; i >= 0; i--)
    {
        if(tabuleiro[i][i][1] == 0)
        {
            cont0++;
        }

        if(tabuleiro[i][i][1] == 1)
        {
            cont1++;
        }
    }

    if(cont0 == 3 || cont1 == 3)
    {
        return 2;
    }

    cont0 = 0;
    cont1 = 0;

    for(int i = 0; i < 6; i++)
    {
        soma += players[0][i];
        soma2 += players[1][i];
    }

    if(soma == 0 && soma2 == 0)
    {
        return 1;    
    }

    return 0;
}