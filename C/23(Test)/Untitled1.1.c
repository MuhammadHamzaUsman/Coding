#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
int computer_as_player2(char table[9], char player_1_symbol, char player_2_symbol)
{
    if(table [0] == table [3])
    {
        if(table [6] != player_1_symbol || table [6] != player_2_symbol)
            return 7;
    }
    else if(table [1] == table [4])
    {
        if(table [7] != player_1_symbol || table [7] != player_2_symbol)
            return 8;
    }
    else if(table [2] == table [5])
    {
        if(table [7] != player_1_symbol || table [7] != player_2_symbol)
            return 8;
    }
    else if(table [1] == table [2])
    {
        if(table [0] != player_1_symbol || table [0] != player_2_symbol)
            return 1;
    }
    else if(table [4] == table [5])
    {
        if(table [3] != player_1_symbol || table [3] != player_2_symbol)
            return 4;
    }
    else if(table [7] == table [8])
    {
        if(table [6] != player_1_symbol || table [6] != player_2_symbol)
            return 7;
    }
    else if(table [3] == table [6])
    {
        if(table [0] != player_1_symbol || table [0] != player_2_symbol)
            return 1;
    }
    else if(table [4] == table [7])
    {
        if(table [1] != player_1_symbol || table [1] != player_2_symbol)
            return 2;
    }
    else if(table [5] == table [8])
    {
        if(table [2] != player_1_symbol || table [2] != player_2_symbol)
            return 3;
    }
    else if(table [0] == table [1])
    {
        if(table [2] != player_1_symbol || table [2] != player_2_symbol)
            return 3;
    }
    else if(table [3] == table [4])
    {
        if(table [5] != player_1_symbol || table [5] != player_2_symbol)
            return 6;
    }
    else if(table [6] == table [7])
    {
        if(table [8] != player_1_symbol || table [8] != player_2_symbol)
            return 9;
    }
    else if(table [0] == table [4])
    {
        if(table [8] != player_1_symbol || table [8] != player_2_symbol)
            return 9;
    }
    else if(table [4] == table [8])
    {
        if(table [0] != player_1_symbol || table [0] != player_2_symbol)
            return 1;
    }
    else if(table [6] == table [4])
    {
        if(table [2] != player_1_symbol || table [2] != player_2_symbol)
            return 3;
    }
    else if(table [4] == table [2])
    {
        if(table [6] != player_1_symbol || table [6] != player_2_symbol)
            return 7;
    }
    else if(table [0] == table [2])
    {
        if(table [1] != player_1_symbol || table [1] != player_2_symbol)
            return 2;
    }
    else if(table [3] == table [5])
    {
        if(table [4] != player_1_symbol || table [4] != player_2_symbol)
            return 5;
    }
    else if(table [6] == table [8])
    {
        if(table [7] != player_1_symbol || table [7] != player_2_symbol)
            return 8;
    }
    else if(table [0] == table [6])
    {
        if(table [3] != player_1_symbol || table [3] != player_2_symbol)
            return 4;
    }
    else if(table [1] == table [7])
    {
        if(table [4] != player_1_symbol || table [4] != player_2_symbol)
            return 5;
    }
    else if(table [2] == table [8])
    {
        if(table [5] != player_1_symbol || table [5] != player_2_symbol)
            return 6;
    }
    else if(table [0] == table [8])
    {
        if(table [4] != player_1_symbol || table [4] != player_2_symbol)
            return 5;
    }
    else if(table [6] == table [2])
    {
        if(table [4] != player_1_symbol || table [4] != player_2_symbol)
            return 5;
    }
    else
        return (rand() % 9)+ 1;
}
void game(char player_1_symbol, char player_2_symbol, char cp, int player)
{
    char table[9] = {'1','2','3','4','5','6','7','8','9'}, cus;
    int nebu;
    /*
    nebu = number entered by user
    cus = currently used symbol or symbol which is used currently either of player 1 or player 2
    */
    if(player==1)
    {
        cus = player_1_symbol;
    }
    else
    {
        cus = player_2_symbol;
    }
    printf("\n\n\n\n\n\n\t\t\t\t\"TICKCROSS\"\n\t\t\t\t %c | %c | %c\n\t\t\t\t---+---+---\n\t\t\t\t %c | %c | %c\n\t\t\t\t---+---+---\n\t\t\t\t %c | %c | %c\n", table[0], table[1], table[2], table[3], table[4], table[5], table[6], table[7], table[8]);
    for(int i=1;i<=9;i++)
    {
        if(cp=='O')
        {
            if(player == 1)
            {
                printf("\t\t\t Enter choice player %d (%c) : ", player, cus);
                scanf("%d", &nebu);
            }
            else if(player == 2)
            {
                printf("\t\t\tCOMPUTER THINKING NEXT TURN");
                do
                {
                    nebu = computer_as_player2(table, player_1_symbol, player_2_symbol);
                    printf("%d", nebu);
                }while(table[nebu - 1] == player_1_symbol || table[nebu - 1] == player_2_symbol);
                printf("%d", nebu);
                getch();
            }
        }
        else if(cp=='F')
        {
            printf("\t\t\t Enter choice player %d (%c) : ", player, cus);
            scanf("%d", &nebu);
        }
        if(table[nebu-1]==player_1_symbol||table[nebu-1]==player_2_symbol||nebu>9)
        {
            printf("\t\t\t\tInvalid choice\n");
            i--;
        }
        else
        {
            system("cls");
            if(player==1)
            {
                player++ , table[nebu-1] = player_1_symbol , cus = player_2_symbol;
            }
            else if (player==2)
            {
                player-- , table[nebu-1] = player_2_symbol , cus = player_1_symbol;
            }
            printf("\n\n\n\n\n\n\t\t\t\t\"TICKCROSS\"\n\t\t\t\t %c | %c | %c\n\t\t\t\t---+---+---\n\t\t\t\t %c | %c | %c\n\t\t\t\t---+---+---\n\t\t\t\t %c | %c | %c\n", table[0], table[1], table[2], table[3], table[4], table[5], table[6], table[7], table[8]);
            if(table[0]==table[1]&&table[1]==table[2]||table[3]==table[4]&&table[4]==table[5]||table[6]==table[7]&&table[7]==table[8]||table[1]==table[4]&&table[4]==table[7]||table[2]==table[5]&&table[5]==table[8]||table[0]==table[4]&&table[4]==table[8]||table[2]==table[4]&&table[4]==table[6]||table[0]==table[3]&&table[3]==table[6])
            {
                if(player==1)
                {
                    player =3;
                }
                printf("\t\t\t\tPLAYER %d WON\n\t\t\t PRESS ENTER FOR MAIN MENUE",player-1);
                i=9;
            }
            else if(i>8)
            {
                printf("\t\t\t\t    DRAW\n\t\t\t PRESS ANY KEY FOR MAIN MENUE");
            }
        }
    }
}
void main(void)
{
    int player = 1, random_line = 1, computer_play_line = 0;
    char main_menu_choice, control_menu_choice, player_1_symbol = 'X', player_2_symbol = 'O', randomness = 'O', cp = 'F';
    /*
    randomness is randomness of who will take first turn player 1 or player 2
    random line determine if randomness is on or off
    cp = computer player if turned on (O) second player will be computer
    */
    for(int i = 0 ; i <= 1; i--)
    {
        player = 1;
        printf("\n\n\n\n\n\n\t\t\t\t\"TICKCROSS\"\n\t\t\t       START GAME : S\n\t\t\t\tTUTORIAL : T\n\t\t\t\tCONTROLS : C\n\t\t\t\t  QUIT : Q\n\t\t\t       ENTER CHOICE : ");
        scanf("%c", &main_menu_choice);
        if(main_menu_choice=='S')
        {
            if(randomness=='O')
            {
                srand(time(NULL));
            }
            system("cls");
            if(rand()%2==0&&randomness=='O')
            {
                player = 2;
            }
            else if(rand()%2==1&&randomness=='O')
            {
                player = 1;
            }
            game(player_1_symbol, player_2_symbol, cp, player);
            getch();
        }
        else if(main_menu_choice=='T')
        {
            system("cls");
            printf("\n\n\n\n\n\n\t      ENTER NUMBER OF BOX YOU WANT YOUR SYMBOL IN\n\t\t\t\t SYMBOL :\n\t\t\t       PLAYER 1 : X\n\t\t\t       PLAYER 2 : O\n\t     YOU WIN BY GETTING THREE OF YOUR SYMBOL IN ROW\n\t\t      PRESS ANY KEY FOR MAIN MENUE");
            getch();
        }
        else if(main_menu_choice=='C')
        {
            //cmlp=control menu loop variable
            for(int cmlp = 1;cmlp > 0;cmlp++)
            {
                system("cls");
                if(randomness=='O' && cp == 'O')
                {
                    printf("\n\n\n\n\n\n\t\t\t\tSYMBOL :\n\t\t\t      PLAYER 1 : %c\n\t\t\t      PLAYER 2 : %c\n\t\t\t       CHANGE : C\n\t\t\t       RANDOM : ON\n\t\t\tPLAYER VS COMPUTER : ON\n\t       PRESS R TO TURN OFF RANDOMNESS OF FIRST TURN\n\t       PRESS A TO TURN OFF COMPUTER AS SECOND PALYER\n\t\t\t    B FOR MAIN MENUE\n\t\t\t      ENTER CHOICE : ", player_1_symbol, player_2_symbol);
                }
                else if(randomness=='F' && cp == 'F')
                {
                    printf("\n\n\n\n\n\n\t\t\t\tSYMBOL :\n\t\t\t      PLAYER 1 : %c\n\t\t\t      PLAYER 2 : %c\n\t\t\t       CHANGE : C\n\t\t\t      RANDOM : OFF\n\t\t\tPLAYER VS COMPUTER : OFF\n\t       PRESS R TO TURN ON RANDOMNESS OF FIRST TURN\n\t       PRESS A TO TURN ON COMPUTER AS SECOND PALYER\n\t\t\t    B FOR MAIN MENUE\n\t\t\t      ENTER CHOICE : ", player_1_symbol, player_2_symbol);
                }
                else if(randomness=='O' && cp == 'F')
                {
                    printf("\n\n\n\n\n\n\t\t\t\tSYMBOL :\n\t\t\t      PLAYER 1 : %c\n\t\t\t      PLAYER 2 : %c\n\t\t\t       CHANGE : C\n\t\t\t       RANDOM : ON\n\t\t\tPLAYER VS COMPUTER : OFF\n\t       PRESS R TO TURN OFF RANDOMNESS OF FIRST TURN\n\t       PRESS A TO TURN ON COMPUTER AS SECOND PALYER\n\t\t\t    B FOR MAIN MENUE\n\t\t\t      ENTER CHOICE : ", player_1_symbol, player_2_symbol);
                }
                else if(randomness=='F' && cp == 'O')
                {
                    printf("\n\n\n\n\n\n\t\t\t\tSYMBOL :\n\t\t\t      PLAYER 1 : %c\n\t\t\t      PLAYER 2 : %c\n\t\t\t       CHANGE : C\n\t\t\t      RANDOM : OFF\n\t\t\tPLAYER VS COMPUTER : ON\n\t         PRESS R TO TURN ON RANDOMNESS OF FIRST TURN\n\t       PRESS A TO TURN ON COMPUTER AS SECOND PALYER\n\t\t\t    B FOR MAIN MENUE\n\t\t\t      ENTER CHOICE : ", player_1_symbol, player_2_symbol);
                }
                scanf(" %c", &control_menu_choice);
                if(control_menu_choice=='C')
                {
                    for(int l = 2 ; l>1 ; l++)
                    {
                        system("cls");
                        printf("\n\n\n\n\n\n\t\t\t      PLAYER 1 : ");
                        scanf(" %c", &player_1_symbol);
                        printf("\n\t\t\t      PLAYER 2 : ");
                        scanf(" %c", &player_2_symbol);
                        if(player_1_symbol == player_2_symbol)
                        {
                            printf("\n\t\t\t     INVALID CHOICE");
                            getch();
                        }
                        else
                            l=0;
                        getch();
                    }
                }
                else if(control_menu_choice=='R')
                {
                    if(random_line==1)
                    {
                        randomness = 'F';
                        random_line--;
                    }
                    else if(random_line==0)
                    {
                        randomness = 'O';
                        random_line++;
                    }
                }
                else if(control_menu_choice == 'A')
                {
                    if(computer_play_line==1)
                    {
                        cp = 'F';
                        computer_play_line--;
                    }
                    else if(computer_play_line==0)
                    {
                        cp = 'O';
                        computer_play_line++;
                    }
                }
                else if(control_menu_choice=='B')
                {
                    cmlp = -1;
                }
            }
        }
        else if(main_menu_choice=='Q')
        {
            break;
        }
        system("cls");
    }
}
