#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 25

struct dll_node
{
    char tytul[SIZE];
    char autor[SIZE];
    char kategoria[SIZE];
    int rok_wydania;
    struct dll_node *prev, *next;
};

struct dll_wsk
{
    struct dll_node *front;
    struct dll_node *back;
};

void create_list(struct dll_wsk *list, char tytul[], char autor[], char kategoria[], int rok_wydania)
{
    if(list->front==NULL)
    {
        struct dll_node *new_node=(struct dll_node*)malloc(sizeof(struct dll_node));
        if(new_node!=NULL)
        {
            new_node->prev=new_node->next=NULL;
            strcpy(new_node->tytul,tytul);
            strcpy(new_node->autor,autor);
            strcpy(new_node->kategoria,kategoria);
            new_node->rok_wydania=rok_wydania;
            list->front=new_node;
            list->back=new_node;
        }
    }
}

void insert_node(struct dll_wsk *list, char tytul[], char autor[], char kategoria[], int rok_wydania)
{
    if(list->front==NULL)
    {
        create_list(list,tytul,autor,kategoria,rok_wydania);
        return;
    }
    struct dll_node *new_node=(struct dll_node*)malloc(sizeof(struct dll_node));
    if(new_node!=NULL)
    {
        strcpy(new_node->tytul,tytul);
        strcpy(new_node->autor,autor);
        strcpy(new_node->kategoria,kategoria);
        new_node->rok_wydania=rok_wydania;
        list->back->next=new_node;
        new_node->prev=list->back;
        list->back=new_node;
        new_node->next=NULL;
    }
}

void print_list(struct dll_wsk list)
{
    int i=1;
    printf("===================================================================================================================\n");
    printf("[%5.5s][%25.25s][%25.25s][%25.25s][%25.25s]\n", "ID","TYTUL","AUTOR","GATUNEK","ROK WYDANIA");
    printf("===================================================================================================================\n");
    while(list.front!=NULL)
    {
        printf("[%5.0d][%25.25s][%25.25s][%25.25s][%25.0d]\n", i,list.front->tytul,list.front->autor,list.front->kategoria,list.front->rok_wydania);
        printf("---------------------------------------------------------------------------------------------------------------------\n");
        list.front=list.front->next;
        i++;
    }
}

void odczyt_pliku(struct dll_wsk *list)
{
    FILE *plik=fopen("dane.txt","r");
    char tmp[4][SIZE];
    if(plik)
    {
        while(!feof(plik))
        {
            fscanf(plik,"%s %s %s %s",tmp[0],tmp[1],tmp[2],tmp[3]);

            for(int i=0;i<4;i++)
            {
                for (int j=0;j<strlen(tmp[i]);j++)
                {
                    if(tmp[i][j]=='_')
                        tmp[i][j]=' ';
                }
            }
            if(!feof(plik))
            {
                insert_node(list,tmp[0],tmp[1],tmp[2],atoi(tmp[3]));
            }
        }
    }
    fclose(plik);
}

void swap(struct dll_node *first,struct dll_node *second)
{
    char tytul_tmp[SIZE];
    char autor_tmp[SIZE];
    char kategoria_tmp[SIZE];
    int rok_wydania_tmp;

    strcpy(tytul_tmp,first->tytul);
    strcpy(autor_tmp,first->autor);
    strcpy(kategoria_tmp,first->kategoria);
    rok_wydania_tmp=first->rok_wydania;

    strcpy(first->tytul,second->tytul);
    strcpy(first->autor,second->autor);
    strcpy(first->kategoria,second->kategoria);
    first->rok_wydania=second->rok_wydania;

    strcpy(second->tytul,tytul_tmp);
    strcpy(second->autor,autor_tmp);
    strcpy(second->kategoria,kategoria_tmp);
    second->rok_wydania=rok_wydania_tmp;
}

struct dll_node* index_of_element(struct dll_node *front,int o)
{
    for(int l=0;l<o;l++)
    {
        front=front->next;
    }
    return front;
}

int partition_tytul(struct dll_wsk list,int pierwszy,int ostatni, int *porownanie, int *przesuniecia)
{
    char pivot[SIZE];
    strcpy(pivot,index_of_element(list.front,pierwszy)->tytul);
    int i=pierwszy-1,j=ostatni+1;
    while(i<j)
    {
        while(strcmp(index_of_element(list.front,--j)->tytul,pivot)>0)
            (*porownanie)++;
        while(strcmp(index_of_element(list.front,++i)->tytul,pivot)<0)
            (*porownanie)++;
        if(i<j)
        {
            swap(index_of_element(list.front,j),index_of_element(list.front,i));
            (*przesuniecia)++;
        }
    }
    return j;
}

int partition_autor(struct dll_wsk list,int pierwszy,int ostatni, int *porownanie, int *przesuniecia)
{
    char pivot[SIZE];
    strcpy(pivot,index_of_element(list.front,pierwszy)->autor);
    int i=pierwszy-1,j=ostatni+1;
    while(i<j)
    {
        while(strcmp(index_of_element(list.front,--j)->autor,pivot)>0)
            (*porownanie)++;
        while(strcmp(index_of_element(list.front,++i)->autor,pivot)<0)
            (*porownanie)++;
        if(i<j)
        {
            swap(index_of_element(list.front,j),index_of_element(list.front,i));
            (*przesuniecia)++;
        }
    }
    return j;
}

int partition_kategoria(struct dll_wsk list,int pierwszy,int ostatni, int *porownanie, int *przesuniecia)
{
    char pivot[SIZE];
    strcpy(pivot,index_of_element(list.front,pierwszy)->kategoria);
    int i=pierwszy-1,j=ostatni+1;
    while(i<j)
    {
        while(strcmp(index_of_element(list.front,--j)->kategoria,pivot)>0)
            (*porownanie)++;
        while(strcmp(index_of_element(list.front,++i)->kategoria,pivot)<0)
            (*porownanie)++;
        if(i<j)
        {
            swap(index_of_element(list.front,j),index_of_element(list.front,i));
            (*przesuniecia)++;
        }
    }
    return j;
}

int partition_rok(struct dll_wsk list,int pierwszy,int ostatni, int *porownanie, int *przesuniecia)
{
    int pivot = index_of_element(list.front,pierwszy)->rok_wydania;
    int i=pierwszy-1,j=ostatni+1;
    while(i<j)
    {
        while(index_of_element(list.front,--j)->rok_wydania>pivot)
            (*porownanie)++;
        while(index_of_element(list.front,++i)->rok_wydania<pivot)
            (*porownanie)++;
        if(i<j)
        {
            swap(index_of_element(list.front,j),index_of_element(list.front,i));
            (*przesuniecia)++;
        }
    }
    return j;
}
void quicksort(struct dll_wsk list, int pierwszy, int ostatni, int wybor_trybu, int *porownanie, int *przesuniecia)
{
    if(pierwszy<ostatni)
    {
        int index;
        switch(wybor_trybu){
        case 1:
            index=partition_tytul(list,pierwszy,ostatni,porownanie,przesuniecia);
            break;
        case 2:
            index=partition_autor(list,pierwszy,ostatni,porownanie,przesuniecia);
            break;
        case 3:
            index=partition_kategoria(list,pierwszy,ostatni,porownanie,przesuniecia);
            break;
        case 4:
            index=partition_rok(list,pierwszy,ostatni,porownanie,przesuniecia);
            break;
        }
        quicksort(list,pierwszy,index,wybor_trybu,porownanie,przesuniecia);
        quicksort(list,index+1,ostatni,wybor_trybu,porownanie,przesuniecia);
    }
}

int index_prawego(int index)
{
    return index*2+2;
}
int index_lewego(int index)
{
    return index*2+1;
}

void heapify_tytul(struct dll_wsk list,int index,int rozmiar, int *porownanie, int *przesuniecia)
{
    int lewy=index_lewego(index);
    int prawy=index_prawego(index);
    int max=index;
    if(lewy<=rozmiar)
        if(strcmp(index_of_element(list.front,lewy)->tytul,index_of_element(list.front,index)->tytul)<0)
        {
              max=lewy;
              (*porownanie)++;
        }
    if(prawy<=rozmiar)
        if(strcmp(index_of_element(list.front,prawy)->tytul,index_of_element(list.front,max)->tytul)<0)
        {
            max=prawy;
            (*porownanie)++;
        }
    if(max!=index)
    {
        swap(index_of_element(list.front,index),index_of_element(list.front,max));
        (*przesuniecia)++;
        heapify_tytul(list,max,rozmiar,porownanie,przesuniecia);
    }
}

void heapify_autor(struct dll_wsk list,int index,int rozmiar, int *porownanie, int *przesuniecia)
{
    int lewy=index_lewego(index);
    int prawy=index_prawego(index);
    int max=index;
    if(lewy<=rozmiar)
        if(strcmp(index_of_element(list.front,lewy)->autor,index_of_element(list.front,index)->autor)<0)
        {
              max=lewy;
              (*porownanie)++;
        }
    if(prawy<=rozmiar)
        if(strcmp(index_of_element(list.front,prawy)->autor,index_of_element(list.front,max)->autor)<0)
        {
            max=prawy;
            (*porownanie)++;
        }
    if(max!=index)
    {
        swap(index_of_element(list.front,index),index_of_element(list.front,max));
        (*przesuniecia)++;
        heapify_autor(list,max,rozmiar,porownanie,przesuniecia);
    }
}

void heapify_kategoria(struct dll_wsk list,int index,int rozmiar, int *porownanie, int *przesuniecia)
{
    int lewy=index_lewego(index);
    int prawy=index_prawego(index);
    int max=index;
    if(lewy<=rozmiar)
        if(strcmp(index_of_element(list.front,lewy)->kategoria,index_of_element(list.front,index)->kategoria)<0)
        {
              max=lewy;
              (*porownanie)++;
        }
    if(prawy<=rozmiar)
        if(strcmp(index_of_element(list.front,prawy)->kategoria,index_of_element(list.front,max)->kategoria)<0)
        {
            max=prawy;
            (*porownanie)++;
        }
    if(max!=index)
    {
        swap(index_of_element(list.front,index),index_of_element(list.front,max));
        (*przesuniecia)++;
        heapify_kategoria(list,max,rozmiar,porownanie,przesuniecia);
    }
}

void heapify_data(struct dll_wsk list,int index,int rozmiar, int *porownanie, int *przesuniecia)
{
    int lewy=index_lewego(index);
    int prawy=index_prawego(index);
    int max=index;
    if(lewy<=rozmiar)
        if(index_of_element(list.front,lewy)->rok_wydania<index_of_element(list.front,index)->rok_wydania)
        {
              max=lewy;
              (*porownanie)++;
        }
    if(prawy<=rozmiar)
        if(index_of_element(list.front,prawy)->rok_wydania<index_of_element(list.front,max)->rok_wydania)
        {
            max=prawy;
            (*porownanie)++;
        }
    if(max!=index)
    {
        swap(index_of_element(list.front,index),index_of_element(list.front,max));
        (*przesuniecia)++;
        heapify_data(list,max,rozmiar,porownanie,przesuniecia);
    }
}

void build_heap(struct dll_wsk list,int element_counter, int wybor_trybu, int *porownanie, int *przesuniecia)
{
    for(int i=element_counter/2;i>=0;i--)
    {
            switch(wybor_trybu){
        case 1:
            heapify_tytul(list,i,element_counter-1,porownanie,przesuniecia);
            break;
        case 2:
            heapify_autor(list,i,element_counter-1,porownanie,przesuniecia);
            break;
        case 3:
            heapify_kategoria(list,i,element_counter-1,porownanie,przesuniecia);
            break;
        case 4:
            heapify_data(list,i,element_counter-1,porownanie,przesuniecia);
            break;
        }
    }
}

void heapsort(struct dll_wsk list,int element_counter, int wybor_trybu, int *porownanie, int *przesuniecia)
{
   int last_index=element_counter-1;
   build_heap(list,element_counter,wybor_trybu,porownanie,przesuniecia);
   for(int i=last_index;i>0;i--)
   {
       swap(index_of_element(list.front,0),index_of_element(list.front,i));
       switch(wybor_trybu){
        case 1:
            heapify_tytul(list,0,--last_index,porownanie,przesuniecia);
            break;
        case 2:
            heapify_autor(list,0,--last_index,porownanie,przesuniecia);
            break;
        case 3:
            heapify_kategoria(list,0,--last_index,porownanie,przesuniecia);
            break;
        case 4:
            heapify_data(list,0,--last_index,porownanie,przesuniecia);
            break;
        }
   }
}


int main()
{
    struct dll_wsk lista={NULL,NULL};
    int porownanie=0,przesuniecia=0;
    odczyt_pliku(&lista);
    print_list(lista);
    printf("********************************************************************************************************************\n");
    heapsort(lista,15,1,&porownanie,&przesuniecia);
    quicksort(lista,0,14,4,&porownanie,&przesuniecia);
    print_list(lista);
    porownanie=0;
    przesuniecia=0;
    heapsort(lista,15,1,&porownanie,&przesuniecia);
    quicksort(lista,0,14,4,&porownanie,&przesuniecia);

    print_list(lista);
    printf("Liczba porownan: %d\nLiczba przesuniec: %d", porownanie,przesuniecia);

    return 0;
}
