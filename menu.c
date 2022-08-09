#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "game.h"

void mainMenu(SnakeGame* snakeGame)
{
    int exit = 0;
    do
    {
        cleamMenu();
        drawBoardGame(snakeGame);

        switch(choiceMenuItems())
        {
        case 1:
            choiceObstacleItems(snakeGame);
            break;
        case 2:
            choiceMenuSnakePosition(snakeGame);
            break;
        case 3:
            choiceMenuSimulator(snakeGame);
            break;
        case 0:
            exit = 1;
            break;
        }
    }
    while(exit == 0);
    cleamMenu();
    printf("\n\n --- Bye ;) ---\n\n");
}


int choiceMenuItems()
{

    int choice;
    printf(" -----------------------------------------\n"
           " 1 - Adicionar obstaculos.\n"
           " 2 - Definir local inicial da minhoca.\n"
           " 3 - Iniciar uma sumula��o de movimento.\n"
           " -----------------------------------------\n"
           " 0 - Sair.\n"
           " -----------------------------------------\n"
           " Selecione a op��o: ");
    scanf("%d",&choice);
    return choice;
}


void choiceObstacleItems(SnakeGame* snakeGame)
{
    int sizeBoardX = getBoardSizeX(snakeGame);
    int sizeBoardY = getBoardSizeY(snakeGame);

    int snakePositionX = getSnakePositionX(snakeGame);
    int snakePositionY = getSnakePositionY(snakeGame);

    int choice1, choice2, error = 0;

    cleamMenu();
    drawBoardGame(snakeGame);

    while(1)
    {
        cleamMenu();
        drawBoardGame(snakeGame);
        printf(" -----------------------------------------\n"
               " Adicionar obstaculo.\n"
               " Posi��o: X (COLUNA).\n"
               " Posi��o: Y (LINHA).\n"
               " Ex: 5 2.\n");

        if (error != 0)
        {
            printf(" -----------------------------------------\n"
                   "  ERRO! Posi��o selecionada n�o � v�lida!\n"
                   "  ERRO! Tente novamente.\n");
        }


        printf(" -----------------------------------------\n"
               " Digite a posi��o X e Y para o obstaculo: ");

        scanf("%d %d", &choice1, &choice2);
        if ((choice1 <= sizeBoardX && choice1 > 0) && (choice2 <= sizeBoardY && choice2 > 0))
        {
            if (choice1 != snakePositionX || choice2 != snakePositionY)
            {
                error = 0;
                break;
            }
        }
        error = 1;
    }

    setBoardObstacle(snakeGame, choice1, choice2);
}


void choiceMenuSnakePosition(SnakeGame* snakeGame)
{
    const int sizeBoardX = getBoardSizeX(snakeGame);
    const int sizeBoardY = getBoardSizeY(snakeGame);

    int choice1, choice2, error = 0;

    resetWalkCount(snakeGame);
    cleamMenu();
    drawBoardGame(snakeGame);

    while(1)
    {
        cleamMenu();
        drawBoardGame(snakeGame);
        printf(" -----------------------------------------\n"
               " Adicionar posi��o inicial da minhoca.\n"
               " Posi��o: X (COLUNA).\n"
               " Posi��o: Y (LINHA).\n"
               " Ex: 5 2.\n");

        if (error != 0)
        {
            printf(" -----------------------------------------\n"
                   "  ERRO! Posi��o selecionada n�o � v�lida!\n"
                   "  ERRO! Tente novamente.\n");
        }


        printf(" -----------------------------------------\n"
               " Digite a posi��o X e Y para a minhoca: ");

        scanf("%d %d", &choice1, &choice2);

        if (choice1 <= sizeBoardX && choice1 > 0)
        {

            if (choice2 <= sizeBoardY && choice2 > 0)
            {


                if (checkObstacleOnPosition(snakeGame,  choice1, choice2) == 0)
                {
                    error = 0;
                    break;
                }
            }
        }
        error = 1;
    }

    setSnakeToPosition(snakeGame, choice1, choice2);

}


void choiceMenuSimulator(SnakeGame* snakeGame)
{
    int choice, runSimulator, error = 0;

    cleamMenu();


    if(getSnakePositionX(snakeGame) == -1)
    {
        printf("\n\n Defina o local inicial da minhoca antes de inicializar a simula��o.\n\n");
        sleep(3);
        return;
    }

    resetWalkCount(snakeGame);

    while(1)
    {
        cleamMenu();
        drawBoardGame(snakeGame);
        printf(" -----------------------------------------\n"
               " Iniciar simula��o.\n"
               " Digite um valor de movimentos rand�micos que a minhoca percorrera.\n"
               " Valor de 1 a N.\n");

        if (error != 0)
        {
            printf(" -----------------------------------------\n"
                   "  ERRO! A quantidade n�o � v�lida!\n"
                   "  ERRO! Tente novamente.\n");
        }

        printf(" -----------------------------------------\n"
               " Digite o n�mero de simula��es: ");

        scanf("%d",&choice);
        if ((choice))
        {
            error = 0;
            break;
        }
        error = 1;
    }

    cleamMenu();
    runSimulator = simuleSnake(snakeGame, choice);
    if (runSimulator < 0)
    {
        printf("\n\n A simula��o terminou com a minhoca presa :(\n\n");
    }
    sleep(4);

}


void cleamMenu()
{
    system("clear||cls");
}

