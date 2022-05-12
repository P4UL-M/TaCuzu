#include "user.h"

void user_main()
{
    int menu, action;
    do
    {
        printf("Do you want to:\n1.Solve a grid\n2.See a grid being solved\n3.Create a grid\n4.Quit");
        scanf("%d", &menu);
    } while (0 < menu && menu < 5);
    switch (menu)
    {
    case 1:
    {
        do
        {
            printf("1.Enter a mask manually\n2.Let the mask be automatically generated\n3.Play directly");
            scanf("%d", action);
        } while (0 < action && action < 4);
        switch (action)
        {
        case 1:
        {
            printf("You can change the mask in the constant.h file, and then play!");
            user_main();
            break;
        }
        case 2:
        {
            //fonction displayArray(mask) then play()
            break;
        }
        default:
        {
            //fonction play()
            break;
        }
            break;
        }
        break;
    }
    case 2:
    {
        //fonction solve grid with Obtainable()
    }
    case 3:
    {
        int size;
        printf("What is the size of the grid you want? (4 or 8)");
        do
        {
            scanf("%d", size);
        } while (size != 4 || size != 8);
        
    }
    default:
        break;
    }
}

void test()
{
    unsigned int* grid=getDefaultMask(8);
    for (int i=0; i<8; i++)
    {
        printf("%d\n", grid[i]);
    }
}
