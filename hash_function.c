#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 16
#define NAME_LENGTH 20

typedef struct ROW
{
    int index;
    char *name[NAME_LENGTH];
    struct ROW *pNext;
}Row;

typedef struct TABLE
{
    Row rows[MAX_ROW];
}Table;

Table *table;
void initialize_Table();
int RSHash(char *str,int len);
void add_Row(char *str);
void collision(Row *row, Row *startRow);
int find_Row(char *str);
void display_Table();

int main()
{
    int i,index;
    char aranan[30];
    char *names[MAX_ROW] = {"armagan","basin","cebir","diyet","erkek","film","gram","hastane","insan","joker","kale","lizbon","makine"
                            ,"number","orta","pilav"};

    initialize_Table();
    for(i=0; i<MAX_ROW; i++)
    {
        add_Row(names[i]);
    }

    printf("\nAranacak ifadeyi giriniz:");
    scanf("%s",&aranan);
    index = find_Row(aranan);
    printf("%s index = %d ",aranan,index);
    display_Table();
    return 0;



}

void initialize_Table()
{
    int i;
    for(i=0; i<MAX_ROW; i++)
    {
        table.rows[i].index = -1;
        sprintf(table.rows[i].name,"%s", "$$BOS$$");
        table.rows[i].pNext = NULL;
    }
}


int RSHash(char *str, int len)
{
    int b= 378551;
    int a = 63689;
    int hash = 0;
    int i= 0;

    for(i=0; i<len; str++,i++)
    {
        hash = hash*a+(*str);
        a = a*b;
    }

    return (hash & 0xFFFFFF)%MAX_ROW;
}

void add_Row(char *str)
{
    int hash_index;
    Row *row;
    hash_index = RSHash(str,strlen(str));
    printf("%d ",hash_index);

    if(table.rows[hash_index] == -1 || strcmp(table.rows[hash_index].name,str)==0)
    {
        table.rows[hash_index].index = hash_index;
        sprintf(table.rows[hash_index].name,"%s",str);
        return;
    }

    row = (Row*)malloc(sizeof(Row));
    row->index = hash_index;
    sprintf(row->name,"%s",str);
    collision(row, &table.rows[hash_index]);

}

void collision(Row *row, Row *startRow)
{
    Row *old;
    old = startRow;

    while(startRow)
    {
        old = startRow;
        startRow = startRow->pNext;
    }

    old->pNext = NULL;
    row->pNext = NULL;
}

int find_Row(char *str)
{
    int hash_index;
    Row *row;
    hash_index = RSHash(str,strlen(str));
    if(strcmp(table.rows[hash_index].name,str)==0)
    {
        return table.rows[hash_index].index;
    }

    else
    {

        row = table.rows[hash_index].pNext;
        while(row)
        {

            if(!strcmp(row->name,str))
            {
                return row->index;
            }

            else
                row = row->pNext;
        }
    }

    return -1;
}

void display_Table()
{
    int i;
    Row *row;
    puts("Tablo");
    for(i=0; i<MAX_ROW; i++)
    {
        if(table.rows[i].pNext==NULL)
        {
            printf("%2d %s\n",table.rows[i].index,table.rows[i].name);

        }
        else
        {
            printf("%2d %s\n",table.rows[i].index,table.rows[i].name);
            row = table.rows[i]->pNext;
            while(row)
            {
                printf("%2d %s\n",row->index,row->name);
                row = row->pNext;
            }
        }
    }
}









