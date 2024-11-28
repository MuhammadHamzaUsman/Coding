import os
import random

def computer_input(table,legal_input) :
    if (1 in legal_input) and ((table[1] == table[2]) or (table[3] == table[6]) or (table[4] == table[8])) :
        return 1
    elif (2 in legal_input) and ((table[0] == table[2]) or (table[4] == table[7])) :
        return 2
    elif (3 in legal_input) and ((table[0] == table[1]) or (table[4] == table[6]) or (table[5] == table[8])) :
        return 3
    elif (4 in legal_input) and ((table[0] == table[6]) or (table[4] == table[5])) :
        return 4
    elif (5 in legal_input) and ((table[0] == table[8]) or (table[2] == table[6]) or (table[1] == table[7]) or (table[3] == table[5])) :
        return 5
    elif (6 in legal_input) and ((table[2] == table[8]) or (table[3] == table[4])) :
        return 6
    elif (7 in legal_input) and ((table[0] == table[3]) or (table[2] == table[4]) or (table[7] == table[8])) :
        return 7
    elif (8 in legal_input) and ((table[6] == table[8]) or (table[1] == table[4])) :
        return 8
    elif (9 in legal_input) and ((table[2] == table[5]) or (table[0] == table[4]) or (table[6] == table[7])) :
        return 9
    else :
        return random.randint(1,9)

table = [1,2,3,4,5,6,7,8,9]
legal_input = [1,2,3,4,5,6,7,8,9]
player = 1
symbol = ["X","O"]
i = 1
is_random_player = True
player_v_ = True
v_player = True
is_symbol_change = False

if is_symbol_change :
    for symbol_loop in range(2) :
        symbol[symbol_loop] = input(f"Player{symbol_loop+1} symbol: ")
    os.system("clear")
    
if is_random_player :
    player = random.randint(1,2)
    if player == 1 :
        computer_player = 2
    else :
        computer_player = 1

while i <= 9 :
    os.system("clear")
    print(f" {table[0]} | {table[1]} | {table[2]}\n---+---+---\n {table[3]} | {table[4]} | {table[5]}\n---+---+---\n {table[6]} | {table[7]} | {table[8]}")
    if player_v_ and :
        if v_player :
            user_input = int(input(f"Enter({player}): "))
        else :
            player    
    else :
        user_input = computer_input(table,legal_input)
    if user_input in legal_input :
        legal_input.remove(user_input)
        if player == 1 :
            player = 2
            table[user_input - 1] = symbol[0]
        elif player == 2 :
            player = 1
            table[user_input - 1] = symbol[1]
        i += 1
    else :
        print("Invalid Input")
        input()
    if (table[0] == table[1] == table[2]) or (table[3] == table[4] == table[5]) or (table[6] == table[7] == table[8]) or (table[0] == table[3] == table[6]) or (table[1] == table[4] == table[7]) or (table[2] == table[5] == table[8]) or (table[0] == table[4] == table[8]) or (table[2] == table[4] == table[6]):
        if player == 2 :
            print(f"Player {player - 1} won")
        else :
            print(f"Player {player + 1} won")
        break

if i == 10 :
    os.system("clear")
    print(f" {table[0]} | {table[1]} | {table[2]}\n---+---+---\n {table[3]} | {table[4]} | {table[5]}\n---+---+---\n {table[6]} | {table[7]} | {table[8]}")
    print("Draw")