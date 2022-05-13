#include "user.h"
#include "constant.h"
#include "generation.h"
#include "data.h"
#include "grid.h"
#include <ctype.h>

void play(unsigned int *sol, unsigned int *mask, int size);
void solve(unsigned int *sol, unsigned int *mask, int size);

void user_main()
{
    int menu, action, size, difficulty;
    do
    {
        printf("Do you want to:\n1.Solve a grid\n2.See a grid being solved\n3.Create a grid\n4.Quit\n>");
        scanf("%d", &menu);
    } while (menu < 0 || 5 < menu);
    switch (menu)
    {
    case 1:
    {
        do
        {
            printf("\n1.Enter a mask manually\n2.Let the mask be automatically generated\n3.Play directly\n>");
            scanf("%d", &action);
        } while (action < 1 || 3 < action);
        unsigned int *mask;
        unsigned int *sol;
        if (action != 1)
        {
            printf("\nWhat is the size of the grid you want? (4 or 8)\n>");
            do
            {
                scanf("%d", &size);
            } while (size != 4 && size != 8);
            printf("\nWhat is the level of difficulty you want? (1 to 3)\n>");
            do
            {
                scanf("%d", &difficulty);
            } while (difficulty < 1 || difficulty > 3);
            mask = createMask(size, difficulty);
            sol = generate_grid(size);
        }
        switch (action)
        {
            case 1:
            {
                printf("\nYou can change the default grids in the constant.h file, and then play!\nDo you want to use default grids? (Enter 0 for no, 1 for yes)\n>");
                do
                {
                    scanf("%d", &action);
                } while (action != 0 && action != 1);
                if (action)
                {
                printf("\nWhat is the size of the grid you want? (4 or 8)\n>");
                do
                {
                    scanf("%d", &size);
                } while (size != 4 && size != 8);
                    mask = getDefaultMask(size);
                    sol = getDefaultGrid(size);
                    play(sol, mask, size);
                }
                else
                {
                    user_main();
                }
                break;
            }
            case 2:
            {
                printf("The mask is:\n\n");
                displayArray(mask, size);
                play(sol, mask, size);
                break;
            }
            case 3:
            {
                play(sol, mask, size);
                break;
            }
        }
        break;
    }
    case 2:
    {
        //fonction solve grid with Obtainable()
        break;
    }
    case 3:
    {
        printf("What is the size of the grid you want? (4 or 8)\n>");
        do
        {
            scanf("%d", &size);
        } while (size != 4 || size != 8);
        //fonction to create grid and show it
        break;
    }
    default:
        break;
    }
}

void play(unsigned int *sol, unsigned int *mask, int size)
{
    char column;
    int lives = 3, value;
    unsigned int *temp_sol = (unsigned int *)malloc(sizeof(unsigned int) * size);
    for (int i = 0; i<size;i++){
        temp_sol[i] = sol[i];
    }
    INDEX i;
    printf("Your grid is:\n\n");
    displayUser(sol, mask, size);
    while (sum(mask, size) != (int)((pow(2, size) - 1) * size) && lives > 0)
    {
        do
        {
            printf("Enter coordinates for the point you want to enter (ex: T9):\n>");
            scanf(" %c%d", &column, &i.x);
            if (isupper(column))
            {
                i.y = column - 'A';
            }
            else
            {
                i.y = column - 'a';
            }
            i.x -= 1;
            if (getValue(mask, i))
                printf("Value already seen!\n");
        } while (((i.x < 0 || i.y >= size) && (i.y < 0 || i.y >= size)) || getValue(mask,i));
        do {
            printf("What is the value at that position?\n>");
            scanf(" %d", &value);
        } while (value != 0 && value != 1);
        modifyValue(temp_sol, i, value);
        modifyValue(mask, i, 1);
        if(checkValid(temp_sol, mask, size, true))
        {
            if (getValue(sol,i) == getValue(temp_sol,i)){
                printf("Your value is correct!\n");
            }
            else{
                printf("Your value is valid but incorrect.\n");
                modifyValue(mask, i, 0);
            }
        }
        else
        {
            lives -= 1;
            if (lives <= 0)
            {
                printf("You lose... Try again!\n");
                break;
            }
            printf("You lose 1 life, %d left\n", lives);
            modifyValue(mask, i, 0);
        }
        displayUser(sol, mask, size);
    }
    free(temp_sol);
}

void solve(unsigned int *sol, unsigned int *mask, int size)
{
    
}
