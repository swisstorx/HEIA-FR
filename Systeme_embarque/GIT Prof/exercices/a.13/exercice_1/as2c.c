/* Interfacing C with assembleur
 * Exercice 1 : solution
 */

extern int fnct2(int* b);

int fnct(int a1, int a2, int a3, int a4, int a5, 
         int a6, int a7, int a8, int a9, int a10)
{
    int v[] = {
      [0] = a1,  [1] = a2,  [2] = a3,  [3] = a4,  [4] = a5,
      [5] = a6,  [6] = a7,  [7] = a8,  [8] = a9,  [9] = a10,
    };
  
    return a1+a2+a3+a4+a5+a6+a7+a8+a9+a10 + fnct2(v); 
}


int main ()
{
    return fnct (1,2,3,4,5,6,7,8,9,10);
} 

