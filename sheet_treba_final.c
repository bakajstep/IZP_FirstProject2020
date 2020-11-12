#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_BUFF 10241
#define ERROR -1
#define LOWER 1
#define UPPER 2
#define BETWEEN(value, min, max) (value <= max && value >= min)

int round_number(double number)
{
    double tmp = number - (int)number;
    return tmp < 0.5 ? (int)number : (int)number + 1;
}

char lower(char character)
{
    if (BETWEEN(character, 'A', 'Z'))
    {
        return character + 32;
    }

    return character;
}

char upper(char character)
{
    if (BETWEEN(character, 'a', 'z'))
    {
        return character - 32;
    }

    return character;
}

int number_of_cells(char buff[], char delim[])
{
    // zaciname na jednicce protoze pocet oddelovacu plus jedna se rovna poctu sloupcu tabulky
    int tmp = 1;
    int i = 0;

    while (buff[i] != '\0')
    {
        int j = 0;
        while (delim[j] != '\0')
        {
            if (buff[i] == delim[j])
            {
                tmp++;
            }
            j++;
        }
        i++;
    }

    //osetreni prazdneho souboru
    if (tmp == 1)
    {
        return ERROR;
    }

    return tmp;
}

void insert_row(char delim, int number)
{

    char tmp_row[number];
    // odecitame zde jednicku protoze v number mame pocet bunek a ne pocet oddelovacu
    for (int i = 0; i < (number - 1); i++)
    {
        tmp_row[i] = delim;
    }

    printf("%s\n", tmp_row);
}

// pocitani arow z argumentu
int count_arow(char *argv[], int argc)
{

    int tmp = 0;

    int i = 0;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "arow") == 0)
        {
            tmp++;
        }
    }
    return tmp;
}

//pridani bunky
void insert_cell(char buff[], int number, char delim[])
{

    char tmp_buff[MAX_BUFF];

    if (number == 1)
    {
        int i = 0;
        tmp_buff[i] = delim[0];
        while (buff[i] != '\0')
        {

            tmp_buff[i + 1] = buff[i];
            i++;
        }
        tmp_buff[i + 1] = '\0';
    }
    else
    {
        int column = 0;
        int i = 0;
        int position_buff = 0;
        while (buff[i] != '\0')
        {
            int j = 0;
            while (delim[j] != '\0')
            {
                if (buff[i] == delim[j])
                {
                    column++;
                    if ((number - 1) == column)
                    {
                        tmp_buff[position_buff] = delim[0];
                        position_buff++;
                        continue;
                    }
                }
                j++;
            }

            tmp_buff[position_buff] = buff[i];
            i++;
            position_buff++;
        }
        tmp_buff[position_buff] = '\0';
    }

    strcpy(buff, tmp_buff);
    return;
}

void delete_colls(char buff[], int down, int up, char delim[])
{
    char tmp_buff[MAX_BUFF];
    int column = 1;
    int position_buff = 0;

    int i = 0;
    while (buff[i] != '\0')
    {
        if (!BETWEEN(column, down, up))
        {
            tmp_buff[position_buff] = buff[i];
            position_buff++;
        }
        int j = 0;
        while (delim[j] != '\0')
        {
            if (buff[i] == delim[j])
            {
                column++;
            }
            j++;
        }
        i++;
    }
    if (tmp_buff[position_buff - 1] != '\n')
    {
        tmp_buff[position_buff - 1] = '\n';
        tmp_buff[position_buff] = '\0';
        strcpy(buff, tmp_buff);
        return;
    }

    tmp_buff[position_buff] = '\0';
    strcpy(buff, tmp_buff);
    return;
}

void acol(char buff[], char delim)
{

    char tmp_buff[MAX_BUFF];

    int i = 0;

    while (buff[i] != '\0')
    {
        tmp_buff[i] = buff[i];
        i++;
    }
    tmp_buff[i - 1] = delim;
    tmp_buff[i] = '\n';
    tmp_buff[i + 1] = '\0';
    strcpy(buff, tmp_buff);
    return;
}

void cset(char buff[], int number, char string[], char delim[])
{
    char tmp_buff[MAX_BUFF];
    int column = 1;
    //tmp done nam slouzi pro zjisteni zda jsme jiz vlozili parametr do tmp_buff
    int tmp_done = 0;
    int position_buff = 0;

    int i = 0;
    while (buff[i] != '\0')
    {

        if (number == 1 && number == column && tmp_done == 0)
        {
            int k = 0;
            while (string[k] != '\0')
            {
                tmp_buff[position_buff++] = string[k++];
            }
            //tmp done nastavime na hodnotu jinou od nuly aby jsme poznali zda jsme provedli zapis
            tmp_done = 1;
        }

        int j = 0;
        while (delim[j] != '\0')
        {
            if (delim[j] == buff[i])
            {
                column++;
                //tmp_buff[position_buff++] = buff[i++];
            }
            j++;
        }

        if (number == column && tmp_done == 0)
        {
            if (number != 1)
            {
                tmp_buff[position_buff++] = delim[0];
            }

            int k = 0;
            while (string[k] != '\0')
            {
                tmp_buff[position_buff++] = string[k++];
            }
            //tmp done nastavime na hodnotu jinou od nuly aby jsme poznali zda jsme provedli zapis
            tmp_done = 1;
        }

        if (number != column)
        {
            tmp_buff[position_buff++] = buff[i];
        }

        i++;
    }
    if (tmp_done == 0)
    {
        int k = 0;
        while (string[k] != '\0')
        {
            tmp_buff[position_buff++] = string[k++];
        }
    }

    if (tmp_buff[position_buff - 1] != '\n')
    {
        tmp_buff[position_buff] = '\n';
        tmp_buff[position_buff + 1] = '\0';
        strcpy(buff, tmp_buff);
        return;
    }

    tmp_buff[position_buff] = '\0';
    strcpy(buff, tmp_buff);
    return;
}

void change_case(char buff[], int number, char delim[], int state)
{
    char tmp_buff[MAX_BUFF];
    int column = 1;
    int position_buff = 0;

    int i = 0;
    while (buff[i] != '\0')
    {
        int j = 0;
        while (delim[j] != '\0')
        {
            if (delim[j] == buff[i])
            {
                column++;
                break;
            }
            j++;
        }

        if (column == number)
        {
            tmp_buff[position_buff++] = state == LOWER ? lower(buff[i]) : upper(buff[i]);
        }
        else
        {
            tmp_buff[position_buff++] = buff[i];
        }

        i++;
    }

    if (tmp_buff[position_buff - 1] != '\n')
    {
        tmp_buff[position_buff] = '\n';
        tmp_buff[position_buff + 1] = '\0';
        strcpy(buff, tmp_buff);
        return;
    }

    tmp_buff[position_buff] = '\0';
    strcpy(buff, tmp_buff);
    return;
}

void get_column(char buff[], int number, char delim[], char input[])
{
    char tmp_column[MAX_BUFF];
    int column = 1;
    int position = 0;

    int i = 0;
    while (buff[i] != '\0')
    {
        if (column == number)
        {
            tmp_column[position++] = buff[i];
        }

        int j = 0;
        while (delim[j] != '\0')
        {
            if (delim[j] == buff[i])
            {
                column++;
            }
            j++;
        }
        i++;
    }

    // osetreni pokud by byl posledni radek prazdny
    if (position == 0)
    {
        tmp_column[position] = '\0';
    }
    else
    {
        tmp_column[position - 1] = '\0';
    }

    strcpy(input, tmp_column);
    return;
}

int main(int argc, char *argv[])
{
    //pocet radku
    int row = 0;

    //pocet bunek v radku
    int cells;

    //nactenej radek
    char buff[MAX_BUFF];

    //muzeme zacit na jednicce protoze prvek nula je nazev souboru
    int arg = 1;

    //maximalni velikost argumentu
    char delim[100];

    //pomocna promnena pro arow
    int arow = 0;

    //
    int result = EXIT_SUCCESS;

    if (argc > 1 && strstr(argv[1], "-d") != NULL)
    {
        strcpy(delim, argv[2]);
        arg += 2;
        // --------------------------------- TODO-------------------------------------------------
        // odstranit duplicitu delimiteru
    }
    else
    {
        delim[0] = ' ';
    }

    //zpracovani souboru radek po radku
    while (fgets(buff, MAX_BUFF, stdin))
    {
        //promnena row nam slouzi k zjisteni na kterym radku se nachazime
        row++;

        //pro rozhodovani jestli tisknout nebo ne
        int print = 1;

        //pocet sloupecku zjistujeme jen na prvnim radku podle zadani
        if (row == 1)
        {
            cells = number_of_cells(buff, delim);
            if (cells == ERROR)
            {
                fprintf(stderr, "Zadali jste prazdny soubor!!\n");
                result = EXIT_FAILURE;
            }
        }

        for (int i = arg; i < argc; ++i)
        {
            if (strcmp(argv[i], "irow") == 0)
            {
                if (row == atoi(argv[i + 1]))
                {
                    insert_row(delim[0], cells);
                    row++;
                }
            }
            else if (strcmp(argv[i], "drow") == 0)
            {
                if (row == atoi(argv[i + 1]))
                {
                    print = 0;
                }
            }
            else if (strcmp(argv[i], "drows") == 0)
            {
                if (BETWEEN(row, atoi(argv[i + 1]), atoi(argv[i + 2])))
                {
                    print = 0;
                }
            }
            else if (strcmp(argv[i], "icol") == 0)
            {
                insert_cell(buff, atoi(argv[i + 1]), delim);
            }
            else if (strcmp(argv[i], "dcol") == 0)
            {
                delete_colls(buff, atoi(argv[i + 1]), atoi(argv[i + 1]), delim);
            }
            else if (strcmp(argv[i], "dcols") == 0)
            {
                if (atoi(argv[i + 1]) <= atoi(argv[i + 2]))
                {
                    delete_colls(buff, atoi(argv[i + 1]), atoi(argv[i + 2]), delim);
                }
                else
                {
                    fprintf(stderr, "Zadali jste nevalidni parametr dcols!!\n");
                    result = EXIT_FAILURE;
                }
            }
            else if (strcmp(argv[i], "acol") == 0)
            {
                acol(buff, delim[0]);
            }
            else if (strcmp(argv[i], "cset") == 0)
            {
                cset(buff, atoi(argv[i + 1]), argv[i + 2], delim);
            }
            else if (strcmp(argv[i], "tolower") == 0)
            {
                change_case(buff, atoi(argv[i + 1]), delim, LOWER);
            }
            else if (strcmp(argv[i], "toupper") == 0)
            {
                change_case(buff, atoi(argv[i + 1]), delim, UPPER);
            }
            else if (strcmp(argv[i], "round") == 0)
            {
                char input[101];
                get_column(buff, atoi(argv[i + 1]), delim, input);
                //zjistujem zda v bunce mame vubec desetinny cislo
                if (strstr(input, ".") != NULL)
                {
                    // osetrujem jestli ta bunka ma v sobe jen desetinny cislo
                    atof(input) == 0 ? input : sprintf(input, "%d", round_number(atof(input)));
                    cset(buff, atoi(argv[i + 1]), input, delim);
                }
                else
                {
                    cset(buff, atoi(argv[i + 1]), input, delim);
                }
            }
            else if (strcmp(argv[i], "int") == 0)
            {
                char input[101];
                get_column(buff, atoi(argv[i + 1]), delim, input);

                if (atof(input) != 0)
                {
                    sprintf(input, "%d", (int)atof(input));
                    cset(buff, atoi(argv[i + 1]), input, delim);
                }
                else
                {
                    cset(buff, atoi(argv[i + 1]), input, delim);
                }
            }
            else if (strcmp(argv[i], "copy") == 0)
            {
                char n[101];
                get_column(buff, atoi(argv[i + 1]), delim, n);
                cset(buff, atoi(argv[i + 2]), n, delim);
            }
            else if (strcmp(argv[i], "swap") == 0)
            {
                char n[101];
                get_column(buff, atoi(argv[i + 1]), delim, n);
                char m[101];
                get_column(buff, atoi(argv[i + 2]), delim, m);
                cset(buff, atoi(argv[i + 2]), n, delim);
                cset(buff, atoi(argv[i + 1]), m, delim);
            }
            else if (strcmp(argv[i], "move") == 0)
            {
                char n[101];
                get_column(buff, atoi(argv[i + 1]), delim, n);
                if (atoi(argv[i + 1]) <= atoi(argv[i + 2]))
                {
                    insert_cell(buff, atoi(argv[i + 2]), delim);
                    cset(buff, atoi(argv[i + 2]), n, delim);
                    delete_colls(buff, atoi(argv[i + 1]), atoi(argv[i + 1]), delim);
                }
                else
                {
                    insert_cell(buff, atoi(argv[i + 2]), delim);
                    cset(buff, atoi(argv[i + 2]), n, delim);
                    delete_colls(buff, atoi(argv[i + 1]) + 1, atoi(argv[i + 1]) + 1, delim);
                }
            }
        }
        if (print == 1)
        {
            printf("%s", buff);
        }
    }

    if (count_arow(argv + 1, argc - 1) > 0)
    {
        int tmp = count_arow(argv + 1, argc - 1);

        for (int i = 0; i < tmp; ++i)
        {
            insert_row(delim[0], cells);
        }
    }
    return result;
}