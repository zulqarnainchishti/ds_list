#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

typedef struct{
    int length;
    int *array;
    int size;
}List;

List init(int N){
    List result;
    result.length=0;
    result.array=(int *)malloc(N*sizeof(int));
    result.size=N;
    return result;
}

List copy(List list){
    List cloned=init(list.size);
    for (int i = 0; i < list.length; i++)
    {
        cloned.array[cloned.length++]=list.array[i];
    }
    return cloned;
}

void clear(List *list){
    list->length=0;
}

void delete(List *list){
    list->length=0;
    free(list->array);
    list->array=NULL;
    list->size=0;
}

bool isEmpty(List list){
    return list.length==0;
}

bool isFull(List list){
    return list.length==list.size;
}

bool isIn(List list, int value){
    for (int i = 0; i < list.length; i++)
    {
        if(list.array[i]==value) return true;
    }
    return false;
}

void traverse(List list){
    printf("[ ");
    for (int i = 0; i < list.length; i++)
    {
        printf("%2d ",list.array[i]);
    }
    printf("] : %d/%d\n",list.length,list.size);
}

List slice(List list, int start, int end){
    List divided=init(list.size);
    for (int i = start; i < end; i++)
    {
        divided.array[divided.length++]=list.array[i];
    }
    return divided;
}

List concat(List front, List rear){
    List joined=init(front.size+rear.size);
    for (int i = 0; i < front.length; i++)
    {
        joined.array[joined.length++]=front.array[i];
    }
    for (int i = 0; i < rear.length; i++)
    {
        joined.array[joined.length++]=rear.array[i];
    }
    return joined;
}

void fill(List *list, int value){
    for (int i = 0; i < list->size; i++)
    {
        list->array[list->length++]=value;
    }
}

void random(List *list, int min, int max){
    srand(time(0));
    for (int i = 0; i < list->size; i++)
    {
        list->array[list->length++]=rand()%(max-min)+min;
    }
}

void shuffle(List *list){
    srand(time(0));
    for (int i = 0; i < list->length; i++)
    {
        swap(list->array+i,list->array+(rand()%list->length));
    }
}

void reverse(List *list){
    for (int i = 0; i < list->length/2; i++)
    {
        swap(&list->array[i],&list->array[list->length-i-1]);
    }
}

int linearSearch(List list, int value, int index){
    for (int i = index; i < list.length; i++)
    {
        if(list.array[i]==value) return i;
    }
    return -1;
}

int binarySearch(List list, int value, int index){
    int start=index;
    int end=list.length-1;
    while (start<=end)
    {
        int mid=(start+end)/2;
        if(list.array[mid]==value) return mid;
        else if(list.array[mid]<value) start=mid+1;
        else end=mid-1 ;
    }
    return -1;
}

int ternarySearch(List list, int value, int index){
    int start=index;
    int end=list.length-1;
    while (start<=end)
    {
        int mid1=(2*start+end)/3;
        int mid2=(start+2*end)/3;
        if(list.array[mid1]==value) return mid1;
        else if(list.array[mid2]==value) return mid2;
        else if(value<list.array[mid1]) end=mid1-1;
        else if(list.array[mid2]<value) start=mid2+1;
        else {
            start=mid1;
            end=mid2;
        }
    }
    return -1;
}

int interpolationSearch(List list, int value, int index){
    int start=index;
    int end=list.length-1;
    while (start<=end)
    {
        int pos=start+(end-start)*(value-list.array[start])/(list.array[end]-list.array[start]) ;
        if(list.array[pos]==value) return pos;
        else if(list.array[pos]<value) start=pos+1;
        else end=pos-1 ;
    }
    return -1;
}

int jumpSearch(List list, int value, int index){
    int jump = (int)sqrt(list.length);
    int start=index;
    int end=start+jump;
    while (end<list.length && list.array[end]<=value)
    {
        start=end;
        end+=jump;
        if(end>list.length-1) end=list.length;
    }
    for (int i = start; i < end; i++)
    {
        if(list.array[i]==value) return i;
    }
    return -1;
}

void bubbleSort(List *list){
    for (int i = 1; i < list->length; i++)
    {
        bool isSorted=true;
        for (int j = 0; j < list->length-i; j++)
        {
            if(list->array[j]>list->array[j+1]){
                swap(&list->array[j],&list->array[j+1]);
                isSorted=false;
            }
        }
        if(isSorted) break;
    }
}

void selectionSort(List *list){
    for (int i = 0; i < list->length-1; i++)
    {
        int minimum=i;
        for (int j = i+1; j < list->length; j++)
        {
            if(list->array[minimum]>list->array[j]) minimum=j;;
        }
        swap(list->array+i,list->array+minimum);
    }
}

void insertionSort(List *list){
    for (int i = 1; i < list->length; i++)
    {
        int curr=list->array[i];
        int j=i;
        while (j>0 && list->array[j-1]>curr)
        {
            list->array[j]=list->array[--j];
        }
        list->array[j]=curr;
    }
}

void countSort(List *list){
    int maximum=list->array[0];
    for (int i = 1; i < list->length; i++) if(list->array[i]>maximum) maximum=list->array[i];
    
    int counted[maximum+1];
    for (int i = 0; i <= maximum; i++) counted[i]=0;
    for (int i = 0; i < list->length; i++) counted[list->array[i]]++;
    for (int i = 1; i <= maximum; i++) counted[i]+=counted[i-1];
    
    int result[list->length];
    for (int i = 0; i < list->length; i++) result[--counted[list->array[i]]]=list->array[i];
    for (int i = 0; i < list->length; i++) list->array[i]=result[i];
}

void cycleSort(List *list){
    int result[list->length];
    for (int i = 0; i < list->length; i++) result[i]=-1;
    
    for (int i = 0; i < list->length; i++)
    {
        int freq=0;
        for (int j = 0; j < list->length; j++) if(list->array[j]<list->array[i]) freq++;
        while(result[freq]==list->array[i]) freq++;
        result[freq]=list->array[i];
    }

    for (int i = 0; i < list->length; i++) list->array[i]=result[i];
}

void merge(List *list, List left, List right){
    int l=0,r=0,i=0;
    while (l<left.length && r<right.length)
    {
        if(left.array[l]<=right.array[r]) list->array[i++]=left.array[l++];
        else list->array[i++]=right.array[r++];
    }
    while (l<left.length) list->array[i++]=left.array[l++];
    while (r<right.length) list->array[i++]=right.array[r++];
}

void mergeSort(List *list){
    if(list->length<=1) return;
    int mid=list->length/2;
    List left=slice(*list,0,mid);
    List right=slice(*list,mid,list->length);
    mergeSort(&left);
    mergeSort(&right);
    merge(list,left,right);
    delete(&left);
    delete(&right);
}

void partition(List *list, int start, int end){
    if(end-start<=0) return;
    int i=start-1, j=start-1;
    while (j<end){
        if(list->array[++j]<=list->array[end]){
            swap(&list->array[++i],&list->array[j]);
        }
    }
    partition(list,start,i-1);
    partition(list,i+1,end);
}

void quickSort(List *list){
    partition(list,0,list->length-1);
}

void heapify(List *list, int size, int index){
    int largest=index;
    int left=2*index+1;
    int right=2*index+2;
    if(left<=size-1 && list->array[largest]<list->array[left]) largest=left;
    if(right<=size-1 && list->array[largest]<list->array[right]) largest=right;
    if(index!=largest){
        swap(list->array+index,list->array+largest);
        heapify(list,size,largest);
    }
}

void heapSort(List *list){
    for (int i=list->size/2-1; i>=0; i--){
        heapify(list,list->length,i);
    }
    for (int i=list->size-1; i>0; i--){
        swap(list->array,list->array+i);
        heapify(list,i,0);
    }
}

int get(List list, int index){
    return list.array[index];
}

void set(List *list, int value, int index){
    list->array[index]=value;
}

void replace(List *list, int new, int old){
    for (int i = 0; i < list->length; i++)
    {
        if(list->array[i]==old)
        {
            list->array[i]=new;
        }
    }
}

void append(List *list, int value){
    list->array[list->length++]=value;
}

void insert(List *list, int value, int index){
    for (int i = list->length; i > index; i--)
    {
        list->array[i]=list->array[i-1];
    }
    list->array[index]=value;
    list->length++;
}

int pop(List *list){
    return list->array[--list->length];
}

int discard(List *list, int index){
    int value = list->array[index];
    for (int i = index; i < list->length; i++)
    {
        list->array[i]=list->array[i+1];
    }
    list->length--;
}

void map(List *list, char operator, int operand){
    for (int i = 0; i < list->length; i++){    
        switch (operator){
            case '+':
                list->array[i]+=operand;
                break;
            case '-':
                list->array[i]-=operand;
                break;
            case '*':
                list->array[i]*=operand;
                break;
            case '/':
                list->array[i]/=operand;
                break;
            case '%':
                list->array[i]%=operand;
                break;
            case '&':
                list->array[i]&=operand;
                break;
            case '|':
                list->array[i]|=operand;
                break;
            case '^':
                list->array[i]^=operand;
                break;
            case '=':
                list->array[i]=list->array[i]==operand;
                break;
            case '!':
                list->array[i]=list->array[i]!=operand;
                break;
            case '<':
                list->array[i]=list->array[i]<operand;
                break;
            case 'S':
                list->array[i]=list->array[i]<=operand;
                break;
            case '>':
                list->array[i]=list->array[i]>operand;
                break;
            case 'Z':
                list->array[i]=list->array[i]>=operand;
                break;
        }
    }
}

void filter(List *list, char operator, int operand){
    int filtered[list->length];
    int index=0;
    for (int i=0; i < list->length; i++){
        switch (operator){
            case '=':
                if(list->array[i]==operand) filtered[index++]=list->array[i];
                break;
            case '!':
                if(list->array[i]!=operand) filtered[index++]=list->array[i];
                break;
            case '<':
                if(list->array[i]<operand) filtered[index++]=list->array[i];
                break;
            case 'S':
                if(list->array[i]<=operand) filtered[index++]=list->array[i];
                break;
            case '>':
                if(list->array[i]>operand) filtered[index++]=list->array[i];
                break;
            case 'Z':
                if(list->array[i]>=operand) filtered[index++]=list->array[i];
                break;
        }
    }
    list->length=0;
    for (int i=0; i < index; i++)
        list->array[list->length++]=filtered[i];
}

void reduce(List *list){
    int reduced[list->length];
    int index=0;
    bool isUnique;
    for (int i = 0; i < list->length; i++){
        isUnique=true;
        for (int j = 0; j < i; j++){
            if(list->array[i]==list->array[j]){
                isUnique=false;
                break;
            }
        }
        if(isUnique)
            reduced[index++]=list->array[i];
    }
    list->length=0;
    for (int i=0; i < index; i++)
        list->array[list->length++]=reduced[i];
}

bool any(List list){
    for (int i = 0; i < list.length; i++)
    {
        if(list.array[i]==1) return true;
    }
    return false;
}

bool all(List list){
    for (int i = 0; i < list.length; i++)
    {
        if(list.array[i]==0) return false;
    }
    return true;
}

int max(List list){
    int maximum=list.array[0];
    for (int i = 1; i < list.length; i++)
    {
        if(maximum<list.array[i]) maximum=list.array[i];
    }
    return maximum;
}

int min(List list){
    int minimum=list.array[0];
    for (int i = 1; i < list.length; i++)
    {
        if(minimum>list.array[i]) minimum=list.array[i];
    }
    return minimum;
}

int sum(List list){
    int sum=0;
    for (int i = 0; i < list.length; i++)
    {
        sum+=list.array[i];
    }
    return sum;
}

int prod(List list){
    int prod=1;
    for (int i = 0; i < list.length; i++)
    {
        prod*=list.array[i];
    }
    return prod;
}

int count(List list, int value){
    int freq=0;
    for (int i = 0; i < list.length; i++)
    {
        if(list.array[i]==value) freq++;
    }
    return freq;
}