#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
void game(char player_1_symbol, char player_2_symbol, int player)
{
    char table[9] = {'1','2','3','4','5','6','7','8','9'}, cus;
    int sebu;
    /*
    sebu = symbol entered by user
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
        printf("\t\t\t Enter choice player %d (%c) : ", player, cus);
        scanf("%d", &sebu);
        if(table[sebu-1]==player_1_symbol||table[sebu-1]==player_2_symbol||sebu>9)
        {
            printf("\t\t\t\tInvalid choice\n");
        }
        else
        {
            system("cls");
            if(player==1)
            {
                player++ , table[sebu-1] = player_1_symbol , cus = player_2_symbol;
            }
            else if (player==2)
            {
                player-- , table[sebu-1] = player_2_symbol , cus = player_1_symbol;
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
    int player = 1, random_line = 1;
    char main_menu_choice, control_menu_choice, player_1_symbol = 'X', player_2_symbol = 'O', randomness = 'O';
    /*
    randomness is randomness of who will take first turn player 1 or player 2
    random line determine if randomness is on or off
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
            game(player_1_symbol,player_2_symbol,player);
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
                if(randomness=='O')
                {
                    printf("\n\n\n\n\n\n\t\t\t\tSYMBOL :\n\t\t\t      PLAYER 1 : %c\n\t\t\t      PLAYER 2 : %c\n\t\t\t       RANDOM : ON\n\t\t\t       CHANGE : C\n\t     PRESS R TO TURN OFF RANDOMNESS OF FIRST TURN\n\t\t\t    B FOR MAIN MENUE\n\t\t\t      ENTER CHOICE : ", player_1_symbol, player_2_symbol);
                }
                else if(randomness=='F')
                {
                    printf("\n\n\n\n\n\n\t\t\t\tSYMBOL :\n\t\t\t      PLAYER 1 : %c\n\t\t\t      PLAYER 2 : %c\n\t\t\t      RANDOM : OFF\n\t\t\t       CHANGE : C\n\t     PRESS R TO TURN ON RANDOMNESS OF FIRST TURN\n\t\t\t    B FOR MAIN MENUE\n\t\t\t      ENTER CHOICE : ", player_1_symbol, player_2_symbol);
                }
                scanf(" %c", &control_menu_choice);
                if(control_menu_choice=='C')
                {
                    system("cls");
                    printf("\n\n\n\n\n\n\t\t\t      PLAYER 1 : ");
                    scanf(" %c", &player_1_symbol);
                    printf("\n\t\t\t      PLAYER 2 : ");
                    scanf(" %c", &player_2_symbol);
                    getch();
                }
                else if(control_menu_choice=='R')
                {
                    if(random_line==1)
                    {
                        randomness = 'F';
                        random_line++;
                    }
                    else if(random_line==2)
                    {
                        randomness = 'O';
                        random_line--;
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
