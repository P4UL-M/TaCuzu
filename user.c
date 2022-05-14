#include "user.h"
#include "constant.h"
#include "generation.h"
#include "data.h"
#include "grid.h"
#include <ctype.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void play(unsigned int *sol, unsigned int *mask, int size);
void solve(unsigned int *sol, unsigned int *mask, int size);

void user_main()
{
    int menu, action, size, difficulty;
    do
    {
        system("clear");
        printf("Do you want to:\n1.Solve a grid\n2.See a grid being solved\n3.Create a grid\n4.Quit\n>");
        scanf("%d", &menu);
    } while (menu < 1 || 4 < menu);
    switch (menu)
    {
    case 1:
    {
        do
        {
            system("clear");
            printf("Do you want to:\n1.Enter a mask manually\n2.Let the mask be automatically generated\n3.Play directly\n4.Go back\n>");
            scanf("%d", &action);
        } while (action < 1 || 4 < action);
        unsigned int *mask;
        unsigned int *sol;
        if (action == 2 || action == 3)
        {
            printf("\nWhat is the size of the grid you want? (4 or 8)\n");
            do
            {
                printf(">");
                scanf("%d", &size);
            } while (size != 4 && size != 8);
            printf("\nWhat is the level of difficulty you want? (1 to 3)\n");
            do
            {
                printf(">");
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
                printf(">");
                scanf("%d", &action);
            } while (action != 0 && action != 1);
            if (action)
            {
                printf("\nWhat is the size of the grid you want? (4 or 8)\n");
                do
                {
                    printf(">");
                    scanf("%d", &size);
                } while (size != 4 && size != 8);
                mask = getDefaultMask(size);
                sol = getDefaultGrid(size);
                play(sol, mask, size);
            }
            else
            {
                user_main();
                return;
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
        default:
        {
            user_main();
            return;
        }
        }
        free(mask);
        free(sol);
        // TODO temporisation
        system("clear");
        user_main();
        return;
    }
    case 2:
    {
        do
        {
            system("clear");
            printf("Do you want to:\n1.Enter a mask manually\n2.Let the mask be automatically generated\n3.Go back\n>");
            scanf("%d", &action);
        } while (action < 1 || 3 < action);
        unsigned int *mask;
        unsigned int *sol;
        switch (action)
        {
        case 1:
        {
            printf("\nYou can change the default grids in the constant.h file, and then play!\nDo you want to use default grids? (Enter 0 for no, 1 for yes)\n>");
            do
            {
                printf(">");
                scanf("%d", &action);
            } while (action != 0 && action != 1);
            if (action)
            {
                printf("\nWhat is the size of the grid you want? (4 or 8)\n");
                do
                {
                    printf(">");
                    scanf("%d", &size);
                } while (size != 4 && size != 8);
                mask = getDefaultMask(size);
                sol = getDefaultGrid(size);
            }
            else
            {
                user_main();
                return;
            }
            break;
        }
        case 2:
        {
            printf("\nWhat is the size of the grid you want? (4 or 8)\n");
            do
            {
                printf(">");
                scanf("%d", &size);
            } while (size != 4 && size != 8);
            difficulty = size == 4 ? 2 : 1;
            mask = createMask(size, difficulty);
            sol = generate_grid(size);
            int i = 0;
            while (!solvable(sol, mask, size))
            {
                free(mask);
                mask = createMask(size, difficulty);
                i++;
                if (i % 50 == 0)
                {
                    free(sol);
                    sol = generate_grid(size);
                }
            }
            printf("\nThe mask is:\n\n");
            displayArray(mask, size);
            break;
        }
        case 3:
        {
            user_main();
            return;
        }
        }
        solve(sol, mask, size);
        free(mask);
        free(sol);
        // TODO temporisation
        system("clear");
        user_main();
        return;
    }
    case 3:
    {
        do
        {
            system("clear");
            printf("Do you want to:\n1.Generate 4x4 grid\n2.Generate 8x8 grid\n3.Go back\n>");
            scanf("%d", &action);
        } while (action < 1 || 3 < action);
        switch (action)
        {
        case 1:
        {
            size = 4;
            break;
        }
        case 2:
        {
            size = 8;
            break;
        }
        case 3:
        {
            user_main();
            return;
        }
        }
        unsigned int *ar = generate_grid(size);
        displayArray(ar, size);
        free(ar);
        // TODO temporisation
        system("clear");
        user_main();
        return;
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
    for (int i = 0; i < size; i++)
    {
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
        } while (i.x < 0 || i.x >= size || i.y < 0 || i.y >= size || getValue(mask, i));
        do
        {
            printf("What is the value at that position?\n>");
            scanf(" %d", &value);
        } while (value != 0 && value != 1);
        modifyValue(temp_sol, i, value);
        modifyValue(mask, i, 1);
        if (checkValid(temp_sol, mask, size, true))
        {
            if (getValue(sol, i) == getValue(temp_sol, i))
            {
                printf("Your value is correct!\n");
            }
            else
            {
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
            printf("Here is a clue :\n");
            INDEX *temp_i = Obtainable2D(sol, mask, size, true);
            if (temp_i != NULL)
            {
                printf("Look at index : %c%d\n", 'A' + temp_i->y, temp_i->x + 1);
                free(temp_i);
            }
            else
                printf("No clue possible...\n");
        }
        displayUser(sol, mask, size);
    }
    free(temp_sol);
}

void solve(unsigned int *sol, unsigned int *mask, int size)
{
    INDEX *i;

    displayUser(sol, mask, size);
    while (sum(mask, size) != (int)((pow(2, size) - 1) * size))
    {
        i = Obtainable2D(sol, mask, size, true);
        if (i != NULL)
        {
            printf("%d, %d\n", i->x, i->y);
            modifyValue(mask, *i, true);
            displayUser(sol, mask, size);
        }
        else
        {
            INDEX temp;
            temp.x = 0;
            temp.y = 0;
            i = Hypothesis(sol, mask, size, temp, true);
            if (i != NULL)
            {
                modifyValue(mask, *i, true);
                displayUser(sol, mask, size);
            }
            else
            {
                printf("No more possible resolutions\n");
                break;
            }
        }
        free(i);
        printf("Press a key to continue...\n");
<<<<<<< HEAD
        while (1)
        {
            sleep(0.5f);
            if (getchar())
            {
=======
        while(1){
            if (getchar()) {
                Sleep(100);
>>>>>>> 19e2a50cf3b6894c3ecf0d7ad47795af362465c5
                break;
            }
        }
    }
}
