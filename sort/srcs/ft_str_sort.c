#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lexicographic_sort(const char* a, const char* b) {
    int i;
    
    i = 0;
    while (*(a + i) == *(b + i)) {
        if (!*(b + i))
            break;
        i++;
    }
    return (*(a + i) - *(b + i)); 
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    char *a_pt;
    char *b_pt;

    a_pt = (char *)a;
    b_pt = (char *)b;
    while (*(a_pt) == *(b_pt)) {   
        if (!a_pt)
            break;
        b_pt++;
        a_pt++;
    }
    
    return (~(*a_pt - *b_pt - 1));
}

int get_distinct(const char *str)
{
	char	*str_pt;
	char	val;
	int		ret;
	int		ascstack[95] = {0};

	str_pt = (char *)str;
	while (*str_pt) {
		val = *str_pt - 32;
		if (val >= 0 && val < 95) {
			*(ascstack + val) += 1;
		}
		str_pt++;
	}

	val = 0;
	ret = 0;
	while (val < 95) {
		if (*(ascstack + val))
			ret += 1;
		*(ascstack + val) = 0;
		val++;
	}

	return (ret);
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    int i;
    int dis_a, dis_b;

    i = 0;
    dis_a = get_distinct(a);
    dis_b = get_distinct(b);
    if ((dis_a == dis_b))
        return (lexicographic_sort_reverse(a, b));

    return (dis_a - dis_b);
}

int sort_by_length(const char* a, const char* b) {
    char    *a_pt;
    char    *b_pt;
    int     ret;

    a_pt = (char *)a;
    b_pt = (char *)b;
    ret = 0;
    while (*a_pt++)
        ret++;
        
    while (*b_pt++)
        ret--;
        
    return ((ret) ? (ret) : (lexicographic_sort(a, b)));
}

void swap(char **s1, char **s2)
{
    char *tmp;
    
    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}


void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b))
{
	char **pivot;
    int last;
    int cmp_i;
	int i;
    
    if (len < 2)
        return;

    cmp_i = 1;
    last = 0;
    pivot = (arr + ((len - 1) / 2));
    swap(arr, pivot);
    
    while (cmp_i < len) {
        if ((*cmp_func)(*arr, *(arr + cmp_i)) > 0) {
            last++;
            swap((arr + cmp_i), (arr + last));
        }
        cmp_i++;
    }
    swap(arr, (arr + last));


    string_sort(arr, last, cmp_func);
   	string_sort((arr + last + 1), (len - last - 1), cmp_func);
}

int main() 
{
    int n;
    char** arr;

    scanf("%d", &n);
	arr = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);

    printf("\n");
    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 

    printf("\n");
    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    

    printf("\n");
    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++) {
        printf("%s\n", arr[i]); 
		free(arr[i]);
	}

	free(arr);
    printf("\n");
}
