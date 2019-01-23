#include <stdio.h>
#include <stdlib.h>

#define array_length(arr) (sizeof(arr) == 0 ? 0 : sizeof(arr) / sizeof((arr)[0]))

int main() 
{
  int i;
  int arr[10] = {4,5,3,7,9,8,2,6,1,0};
  int *sorted_array[10];
  int len = array_length(arr);
  
  for (i = 0; i < len; i++) {
    sorted_array[i] = &arr[i];
  }
  
  /* move previous elements down until insertion point reached */ 
  void shift_element(unsigned int i) { 
    int *pvalue ;
    /* guard against going outside array */
    for (pvalue = sorted_array[i]; i && *sorted_array[i-1] > *pvalue; i--) {
      /* move pointer down */
      sorted_array[i] = sorted_array[i-1];
    }
    sorted_array[i] = pvalue; /* insert pointer */ 
    
  }
  
  /* iterate until out−of−order element found ; shift the element , and continue iterating∗ */
  void insertion_sort (void){ 
    unsigned int i;
    for (i = 1; i < len; i++) {
      if (*sorted_array[i] < *sorted_array[i-1]) {
        shift_element(i); 
      }
    }
  }
  
  insertion_sort();
  printf("original array \n");
  for (int i = 0; i < len; i++) {
    printf("%d  ",arr[i]);
  }
  
  printf("\nsorted array by pointers \n");
  for (int i = 0; i < len; i++) {
    printf("%d  ",*sorted_array[i]);
  }
  
  return 1;
}
