#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<conio.h>

typedef struct _tab
{
    unsigned long int time;
    double num;
} tab;

typedef struct _tnode
{
    tab data;
    struct _tnode *left;
    struct _tnode *right;
} tnode;

int bubblesort(tab *mas,int length);
int quicksort(tab *mas, int length);
int insertsort(tab *mas,int length);
int heapsort(tab *mas, int length);
void quicksortfunc(tab *mas,int low, int high);


tab* createarray(int length);
tab* copyarray(tab *mas,int length);
tnode* treeaddnode(tnode * tree, tab elem);
void treearrscan(tab * mas,tnode * tree, int lflag);
void deletetree(tnode *tree);


unsigned long int linesearch(tab * mas,unsigned long int numtos,unsigned long int length);
unsigned long int binarysearch(tab *mas,unsigned long int numtos,unsigned long int length);
unsigned long int treesearch(tab *mas,unsigned long int numtofind,unsigned long int length);
unsigned long int interpolationsearch(tab *mas, unsigned long int numtofind,unsigned long int length);

double TIMEquick,TIMEbubble,TIMEins,TIMEheap;

unsigned long int CMPRquick,CMPRbubble,CMPRins,CMPRheap;

unsigned long int ITERquick,ITERbubble,ITERins,ITERheap;

unsigned long int ITERSline,ITERSbin,ITERStree,ITERSint;

double TIMESline,TIMESbin,TIMEStree,TIMESint;

int main()
{
    int i,flag=10,infflag=0;
    unsigned long int length,datemin,datemax,numtofind,smallestindex,lineindex=0,binindex=0,treeindex=0,interindex=0;
    double smallestnum=1.0;
    char c,name[100];
    FILE *f;
    tab *mas1,*mas2;
    struct tm m_time;
    while (flag)
    {
        flag=10;
        numtofind=0;
        length=0;
        smallestindex=0;
        smallestnum=1.0;
        printf("%s","Chose the way to create array:\n1 - by yourself.\n2 - randomly.\n3 - read from CSV file.\n0 - exit.\n");
        scanf("%d",&flag);
        fflush(stdin);
        system("CLS");
//Выбор способа заполнить массив---------------------------------------------------------------------------------------------------------------
        switch (flag)
        {
        case 1:
        {
            printf("%s","Enter the length of array:\n");
            scanf("%lu",&length);
            fflush(stdin);
            printf("Enter number and time %lu times:\n",length);
            mas1=(tab*)malloc(length*sizeof(tab));
            for (i=0; i<length; ++i)
            {
                scanf("%lf %lu",&mas1[i].num,&mas1[i].time);
                fflush(stdin);
            }
            flag=10;
            break;
        }
        case 2:
        {
            printf("%s","Enter the length of array:\n");
            scanf("%lu",&length);
            fflush(stdin);
            mas1=createarray(length);
            flag=10;
            break;
        }
        case 3:
        {
            printf("%s","Enter the file name:\n");
            gets(name);
            fflush(stdin);
            while ((f=fopen(name,"r"))==0)
            {
                system("CLS");
                printf("Error opening a file! Enter the correct file name:\n");
                gets(name);
                fflush(stdin);
            }
            while ((c=fgetc(f))!=EOF)
                if (c=='\n') ++length;
            mas1=(tab*)malloc(length*sizeof(tab));
            fseek(f,0,SEEK_SET);
            for (i=0; fscanf(f,"%lf,%lu\n",&mas1[i].num,&mas1[i].time)!=EOF; ++i);
            flag=10;
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            system("CLS");
            printf("%s","Wrong choice!\n");
            flag=10;
            continue;
            break;
        }
        }
//Поиск минимального дробного числа между дат 1 января 1980 года и 31 декабря 1984 года-----------------------------------------------
        m_time.tm_sec = 0;
        m_time.tm_min = 0;
        m_time.tm_hour = 0;
        m_time.tm_mday = 1;
        m_time.tm_mon = 0;
        m_time.tm_year = 80;
        datemin=mktime(&m_time);

        m_time.tm_sec = 0;
        m_time.tm_min = 0;
        m_time.tm_hour = 0;
        m_time.tm_mday = 31;
        m_time.tm_mon = 11;
        m_time.tm_year = 84;
        datemax=mktime(&m_time);

        for (i=0; i<length; ++i)
            if ((mas1[i].time<datemax)&&(mas1[i].time>datemin)&&(mas1[i].num<smallestnum))
            {
                smallestnum=mas1[i].num;
                smallestindex=i;
            }
//Начало сортировки-----------------------------------------------------------------------------------------------
        infflag=1;
        system("CLS");
//Соохранение неотсортированного массива-------------------------------------------------------------------
        printf("Array size: %lu\n\n",length);
        printf("|Bubblesort| - Sorting...\nEstimated time: -\nReplacements: -\nComparisons: -\n\n");
        printf("|Insertionsort| - Sorting...\nEstimated time: -\nReplacements: -\nComparisons: -\n\n");
        printf("|Heapsort| - Sorting...\nEstimated time: -\nReplacements: -\nComparisons: -\n\n");
        printf("|Quicksort| - Sorting...\nEstimated time: -\nReplacements: -\nComparisons: -\n\n");
        mas2=copyarray(mas1,length);
        if ((f=fopen("1 Array (Not sorted).txt","w"))==0)
        {
            printf("STRANGE ERROR IN CREATING FILE!!\n");
            return(-1);
        }
        else
        {
            for (i=0; i<length; ++i)
                fprintf(f,"%4d) %.9lf %11lu %s",i+1,mas2[i].num,mas2[i].time,ctime(&mas2[i].time));
            fclose(f);
            f=0;
        }
//Сохранение массива, отсортированного пузырьковой сортировкой--------------------------------------------------------
        if (bubblesort(mas2,length))
        {
            printf("ERROR WHILE BUBBLESORTING");
            return (-1);
        }

        if ((f=fopen("2 Array (Bubble Sorted).txt","w"))==0)
        {
            printf("STRANGE ERROR IN CREATING FILE!!\n");
            return(-1);
        }
        else
        {
            for (i=0; i<length; ++i)
                fprintf(f,"%4d) %.9lf %11lu %s",i+1,mas2[i].num,mas2[i].time,ctime(&mas2[i].time));
            fclose(f);
            f=0;
        }
        system("CLS");
        printf("Array size: %lu\n\n",length);
        printf("|Bubblesort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEbubble,ITERbubble,CMPRbubble);
        printf("|Insertionsort| - Sorting...\nEstimated time: -\nReplacements: -\nComparisons: -\n\n");
        printf("|Heapsort| - Sorting...\nEstimated time: -\nReplacements: -\nComparisons: -\n\n");
        printf("|Quicksort| - Sorting...\nEstimated time: -\nReplacements: -\nComparisons: -\n\n");
        free(mas2);
        mas2=copyarray(mas1,length);
//Сохранение массива, отсортированного сортировкой вставками-------------------------------------------------------
        if (insertsort(mas2,length))
        {
            printf("ERROR WHILE INSERTIONSORTING");
            return (-1);
        }

        if ((f=fopen("3 Array (Insertion Sorted).txt","w"))==0)
        {
            printf("STRANGE ERROR IN CREATING FILE!!\n");
            return(-1);
        }
        else
        {
            for (i=0; i<length; ++i)
                fprintf(f,"%4d) %.9lf %11lu %s",i+1,mas2[i].num,mas2[i].time,ctime(&mas2[i].time));
            fclose(f);
            f=0;
        }
        system("CLS");
        printf("Array size: %lu\n\n",length);
        printf("|Bubblesort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEbubble,ITERbubble,CMPRbubble);
        printf("|Insertionsort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEins,ITERins,CMPRins);
        printf("|Heapsort| - Sorting...\nEstimated time: -\nReplacements: -\nComparisons: -\n\n");
        printf("|Quicksort| - Sorting...\nEstimated time: -\nReplacements: -\nComparisons: -\n\n");
        free(mas2);
        mas2=copyarray(mas1,length);
//Сохранение массива, отсортированного деревом-------------------------------------------------------
        if (heapsort(mas2,length))
        {
            printf("ERROR WHILE HEAPSORTING");
            return (-1);
        }
        if ((f=fopen("4 Array (Heap Sorted).txt","w"))==0)
        {
            printf("STRANGE ERROR IN CREATING FILE!!\n");
            return(-1);
        }
        else
        {
            for (i=0; i<length; ++i)
                fprintf(f,"%4d) %.9lf %11lu %s",i+1,mas2[i].num,mas2[i].time,ctime(&mas2[i].time));
            fclose(f);
            f=0;
        }
        system("CLS");
        printf("Array size: %lu\n\n",length);
        printf("|Bubblesort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEbubble,ITERbubble,CMPRbubble);
        printf("|Insertionsort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEins,ITERins,CMPRins);
        printf("|Heapsort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEheap,ITERheap,CMPRheap);
        printf("|Quicksort| - Sorting...\nEstimated time: -\nReplacements: -\nComparisons: -\n\n");
        free(mas2);
        mas2=copyarray(mas1,length);
//Сохранение массива, отсортированного быстрой сортировкой-------------------------------------------------------
        if (quicksort(mas2,length))
        {
            printf("ERROR WHILE QUICKSORTING");
            return (-1);
        }

        if ((f=fopen("5 Array (Quick Sorted).txt","w"))==0)
        {
            printf("STRANGE ERROR IN CREATING FILE!!\n");
            return(-1);
        }
        else
        {
            for (i=0; i<length; ++i)
                fprintf(f,"%4d) %.9lf %11lu %s",i+1,mas2[i].num,mas2[i].time,ctime(&mas2[i].time));
            fclose(f);
            f=0;
        }
        system("CLS");
        printf("Array size: %lu\n\n",length);
        printf("|Bubblesort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEbubble,ITERbubble,CMPRbubble);
        printf("|Insertionsort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEins,ITERins,CMPRins);
        printf("|Heapsort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEheap,ITERheap,CMPRheap);
        printf("|Quicksort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEquick,ITERquick,CMPRquick);
        printf("Minimal element between 1 Jan 1980 and 31 Dec 1984: %.9lf (index: %d in not sorted)\n",smallestnum,smallestindex);
//Конец сортировки, сохранение информации в файл-------------------------------------------------------
        if ((f=fopen("6 Sort Results.txt","w"))==0)
        {
            printf("STRANGE ERROR IN CREATING FILE!!\n");
            return(-1);
        }
        else
        {
            fprintf(f,"Array size: %lu\n\n",length);
            fprintf(f,"|Bubblesort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEbubble,ITERbubble,CMPRbubble);
            fprintf(f,"|Insertionsort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEins,ITERins,CMPRins);
            fprintf(f,"|Heapsort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEheap,ITERheap,CMPRheap);
            fprintf(f,"|Quicksort| - Sorted!\nEstimated time: %.3lf\nReplacements: %lu\nComparisons: %lu\n\n",TIMEquick,ITERquick,CMPRquick);
            fprintf(f,"Minimal element between 1 Jan 1980 and 31 Dec 1984: %.9lf (index: %d in not sorted)\n",smallestnum,smallestindex+1);
            fclose(f);
            f=0;
        }
        system("PAUSE");
        system("CLS");
//Переход к поиску-------------------------------------------------------
        while (1)
        {
            printf("%s","Chose way to find number:\n1 - find random number,\n2 - find your number.\n3 - return to sort again.\n0 - exit.\n");
            scanf("%d",&flag);
            fflush(stdin);
            switch(flag)
            {
            case 1:
            {
                numtofind=mas2[(rand()%length)].time;
                flag=10;
                break;
            }
            case 2:
            {
                printf("Enter number:\n");
                scanf("%lu",&numtofind);
                fflush(stdin);
                flag=10;
                break;
            }
            case 3:
            {
                flag=15;
                break;
            }
            case 0:
            {
                return 0;
            }
            default:
            {
                system("CLS");
                printf("%s","Wrong choice!\n");
                continue;
                break;
            }
            }
            if (flag==15)
            {
                flag=10;
                system("CLS");
                break;
            }
            else
            {
//Непосредственно поиск-----------------------------------------------------------------------------------------
                system("CLS");
                printf("Array size: %d\nNumber to find: %lu\n\n",length,numtofind);
                printf("|Linesearch| - Searching...\nEstimated time: -\nIterations: -\nElement index:-\n\n");
                printf("|Binarysearch| - Searching...\nEstimated time: -\nIterations: -\nElement index:-\n\n");
                printf("|Treesearch| - Searching...\nEstimated time: -\nIterations: -\nElement index:-\n\n");
                printf("|Interpolationsearch| - Searching...\nEstimated time: -\nIterations: -\nElement index:-\n\n");
//Линейный поиск-----------------------------------------------------------------------------------------
                lineindex=linesearch(mas2,numtofind,length);
                system("CLS");
                printf("Array size: %d\nNumber to find: %lu\n\n",length,numtofind);
                printf("|Linesearch| - Completed!\nEstimated time: %lf \nIterations: %lu \nElement index: %lu\n\n",TIMESline,ITERSline,lineindex+1);
                printf("|Binarysearch| - Searching...\nEstimated time: -\nIterations: -\nElement index:-\n\n");
                printf("|Treesearch| - Searching...\nEstimated time: -\nIterations: -\nElement index:-\n\n");
                printf("|Interpolationsearch| - Searching...\nEstimated time: -\nIterations: -\nElement index:-\n\n");
//Бинарный поиск-----------------------------------------------------------------------------------------
                binindex=binarysearch(mas2,numtofind,length);
                system("CLS");
                printf("Array size: %d\nNumber to find: %lu\n\n",length,numtofind);
                printf("|Linesearch| - Completed!\nEstimated time: %.3lf\nIterations: %lu\nElement index: %lu\n\n",TIMESline,ITERSline,lineindex+1);
                printf("|Binarysearch| - Completed!\nEstimated time: %.3lf\nIterations: %lu\nElement index: %lu\n\n",TIMESbin,ITERSbin,binindex+1);
                printf("|Treesearch| - Searching...\nEstimated time: -\nIterations: -\n\n");
                printf("|Interpolationsearch| - Searching...\nEstimated time: -\nIterations: -\n\n");
//Поиск деревом-----------------------------------------------------------------------------------------
                treeindex=lineindex;
                treesearch(mas1,numtofind,length);
                system("CLS");
                printf("Array size: %d\nNumber to find: %lu\n\n",length,numtofind);
                printf("|Linesearch| - Completed!\nEstimated time: %.3lf\nIterations: %lu\nElement index: %lu\n\n",TIMESline,ITERSline,lineindex+1);
                printf("|Binarysearch| - Completed!\nEstimated time: %.3lf\nIterations: %lu\nElement index: %lu\n\n",TIMESbin,ITERSbin,binindex+1);
                printf("|Treesearch| - Completed!\nEstimated time: %.3lf\nIterations: %lu\nElement index: %lu\n\n",TIMEStree,ITERStree,treeindex+1);
                printf("|Interpolationsearch| - Searching...\nEstimated time: -\nIterations: -\n\n");
//Интерполяционный поиск--------------------------------------------------------------------------------
                interindex=interpolationsearch(mas2,numtofind,length);
                system("CLS");
                printf("Array size: %d\nNumber to find: %lu\n\n",length,numtofind);
                printf("|Linesearch| - Completed!\nEstimated time: %.3lf\nIterations: %lu\nElement index: %lu\n\n",TIMESline,ITERSline,lineindex+1);
                printf("|Binarysearch| - Completed!\nEstimated time: %.3lf\nIterations: %lu\nElement index: %lu\n\n",TIMESbin,ITERSbin,binindex+1);
                printf("|Treesearch| - Completed!\nEstimated time: %.3lf\nIterations: %lu\nElement index: %lu\n\n",TIMEStree,ITERStree,treeindex+1);
                printf("|Interpolationsearch| - Completed!\nEstimated time: %.3lf\nIterations: %lu\nElement index: %lu\n\n",TIMESint,ITERSint,interindex+1);
                system("PAUSE");
                system("CLS");
            }
        }

//-----------------------------------------------------------------------
    }
    return 0;
}

unsigned long int interpolationsearch(tab *mas, unsigned long int numtofind,unsigned long int length)
{
    unsigned long int left=0,right=length-1,mid;
    ITERSint=0;
    TIMESint=clock();
    while ((mas[left].time < numtofind)&&(numtofind<mas[right].time))
    {
        ++ITERSint;
        mid = left + (numtofind - mas[left].time) * (right - left) / (mas[right].time - mas[left].time);
        if (mas[mid].time < numtofind)
            left = mid + 1;
        else if (mas[mid].time > numtofind)
            right = mid - 1;
        else
        {
            TIMESint=(clock()-TIMESint)/(double)CLOCKS_PER_SEC;
            return (mid);
        }
    }
    if (mas[left].time == numtofind)
    {
        TIMESint=(clock()-TIMESint)/(double)CLOCKS_PER_SEC;
        return (left);
    }
    else if (mas[right].time == numtofind)
    {
        TIMESint=(clock()-TIMESint)/(double)CLOCKS_PER_SEC;
        return (right);
    }
    else
    {
        TIMESint=(clock()-TIMESint)/(double)CLOCKS_PER_SEC;
        return (-1);
    }
}

unsigned long int treesearch(tab *mas,unsigned long int numtofind,unsigned long int length)
{
    int i;
    tnode *tree;
    ITERStree=0;
    TIMEStree=clock();
    tree=0;
    for (i=0; i<length; ++i)
        tree=treeaddnode(tree,mas[i]);
    while (tree->data.time!=numtofind)
    {
        ++ITERStree;
        if (tree->data.time>numtofind)
        {
            if(tree->left)
                tree=tree->left;
            else
            {
                TIMESline=(clock()-TIMESline)/(double)CLOCKS_PER_SEC;
                return(-1);
            }
        }
        else
        {
            if(tree->right)
                tree=tree->right;
            else
                {
                    TIMESline=(clock()-TIMESline)/(double)CLOCKS_PER_SEC;
                    return(-1);
                }
        }
    }
    TIMESline=(clock()-TIMESline)/(double)CLOCKS_PER_SEC;
    deletetree(tree);
    return 0;
}
unsigned long int linesearch(tab * mas,unsigned long int numtofind,unsigned long int length)
{
    int i;
    extern unsigned long int ITERSline;
    extern double TIMESline;
    ITERSline=0;
    TIMESline=clock();
    for (i=0; i<length; ++i)
    {
        ++ITERSline;
        if (numtofind==mas[i].time)
        {
            TIMESline=(clock()-TIMESline)/(double)CLOCKS_PER_SEC;
            return (i);
        }
    }
    TIMESline=(clock()-TIMESline)/(double)CLOCKS_PER_SEC;
    return(-1);
}
/*
unsigned long int binarysearch(tab *mas,unsigned long int numtofind,unsigned long int length)
{
    unsigned long int left,right,mid;
    ITERSbin=0;
    left=0;
    right=length-1;
    while (left<=right)
    {
        mid=(left+right)/2;
        ++ITERSbin;
        if (numtofind<mas[mid].time)
        {
            if (mid==0)
                return (-1);
            right=--mid;
        }
        else if (numtofind>mas[mid].time)
            left=++mid;
        else
            return (mid);
    }
    return (-1);
}*/

unsigned long int binarysearch(tab *mas,unsigned long int numtofind, unsigned long int length)
{
    unsigned long int l,r,m;
    extern unsigned long int ITERSbin;
    extern double TIMESbin;
    l=0;
    r=length-1;
    ITERSbin=0;
    TIMESbin=clock();
    while (l<=r)
    {
        m=(l+r)/2;
        ++ITERSbin;
        if (numtofind<mas[m].time)
        {
            r=m-1;
        }
        else if (numtofind>mas[m].time)
            l=m+1;
        else
        {
            TIMESbin=(clock()-TIMESbin)/(double)CLOCKS_PER_SEC;
            return (m);
        }
    }
    TIMESbin=(clock()-TIMESbin)/(double)CLOCKS_PER_SEC;
    return -1;
}

int bubblesort(tab *mas,int length)
{
    int i,j;
    tab temp;
    ITERbubble=0;
    CMPRbubble=0;
    TIMEbubble=clock();
    for (i=0; i<length-1; ++i)
    {
        for (j=0; j<length-1-i; ++j)
        {
            if (mas[j].time>mas[j+1].time)
            {
                temp = mas[j];
                mas[j]=mas[j+1];
                mas[j+1]=temp;
                ++ITERbubble;
            }
            ++CMPRbubble;
        }
    }
    TIMEbubble=(clock()-TIMEbubble)/(double)CLOCKS_PER_SEC;
    return 0;
}

int insertsort(tab *mas,int length)
{
    int i,p;
    tab temp;
    ITERins=0;
    CMPRins=0;
    TIMEins=clock();
    for (i = 1; i < length; ++i)
    {
        temp = mas[i];
        p = i - 1;
        while((p >= 0) && (mas[p].time > temp.time))
        {
            mas[p+1] = mas[p];
            p = p - 1;
            ++ITERins;
            ++CMPRins;
        }
        mas[p+1] = temp;
        ++ITERins;
    }
    TIMEins=(clock()-TIMEins)/(double)CLOCKS_PER_SEC;
    return 0;
}

int heapsort(tab *mas, int length)
{
    int i;
    tnode *tree;
    ITERheap=0;
    CMPRheap=0;
    tree=0;
    TIMEheap=clock();
    for (i=0; i<length; ++i)
        tree=treeaddnode(tree,mas[i]);
    treearrscan(mas,tree,1);
    TIMEheap=(clock()-TIMEheap)/(double)CLOCKS_PER_SEC;
    deletetree(tree);
    return 0;
}

void treearrscan(tab * mas,tnode * tree, int lflag)
{
    static int i;
    if (tree)
    {
        if (tree->left)
        {
            treearrscan(mas,tree->left,0);
        }
        mas[i++]=tree->data;
        ++ITERheap;
        if (tree->right)
        {
            treearrscan(mas,tree->right,0);
        }
    }
    if (lflag) i=0;
}

tnode* treeaddnode(tnode * tree, tab elem)
{
    if (tree)
    {
        if ((elem.time)<((tree->data).time))
        {
            ++CMPRheap;
            tree->left=treeaddnode(tree->left, elem);
        }
        else
        {
            ++CMPRheap;
            tree->right=treeaddnode(tree->right, elem);
        }
    }
    else
    {
        ++ITERheap;
        tree=(tnode*)malloc(sizeof(tnode));
        tree->data=elem;
        tree->left=0;
        tree->right=0;
    }
    return (tree);
}

void deletetree(tnode *tree)
{
    if (tree)
    {
        deletetree(tree->left);
        deletetree(tree->right);
        free(tree);
    }
}

int quicksort(tab *mas, int length)
{
    CMPRquick=0;
    ITERquick=0;
    TIMEquick=clock();
    quicksortfunc(mas,0,length-1);
    TIMEquick=(clock()-TIMEquick)/(double)CLOCKS_PER_SEC;
    return 0;
}

void quicksortfunc(tab *mas,int low, int high)
{
    int l=low,r=high;
    static int i,min,max;
    static unsigned long int sred;
    tab temp;
    min=l;
    max=r;
    for (i=l; i<r; ++i)
    {
        if (mas[i].time > mas[max].time)
        {
            max=i;
        }
        ++CMPRquick;
        if (mas[i].time < mas[min].time)
        {
            min=i;
        }
        ++CMPRquick;
    }
    sred=(mas[max].time + mas[min].time)/2;
    while (l <= r)
    {
        ++CMPRquick;
        while (mas[l].time < sred)
        {
            ++CMPRquick;
            ++l;
        }
        while (mas[r].time > sred)
        {
            ++CMPRquick;
            --r;
        }
        if (l <= r)
        {
            ++ITERquick;
            ++CMPRquick;
            temp=mas[l];
            mas[l]=mas[r];
            mas[r]=temp;
            --r;
            ++l;
        }
    }
    if (low < r)
    {
        ++CMPRquick;
        quicksortfunc(mas,low,r);
    }
    if (high > l)
    {
        ++CMPRquick;
        quicksortfunc(mas,l,high);
    }
}


tab* copyarray(tab *mas,int length)
{
    int i;
    tab *temp;
    temp=(tab*)malloc(length * sizeof(tab));
    for (i=0; i<length; ++i)
    {
        temp[i].time=mas[i].time;
        temp[i].num=mas[i].num;
    }
    return temp;
}

tab* createarray(int length)
{
    int i;
    tab *temp;
    temp=(tab*)malloc(length*sizeof(tab));
    srand(time(0));
    for (i=0; i<length; ++i)
    {
        temp[i].time=rand()%38142*54933+1;
        temp[i].num=rand()%9873*0.000051264+0.0000001261324;
    }
    return temp;
}
