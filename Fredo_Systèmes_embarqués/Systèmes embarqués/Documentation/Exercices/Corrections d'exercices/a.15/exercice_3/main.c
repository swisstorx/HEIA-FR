/* Interfacing C with assembleur
 * Exercice 3 : solution
 */
/* Global, ou t'as pas encore de corps de méthode*/
extern int add_c(int value1, int value2);
extern void main_asm();

int main()
{
	main_asm();
	int value1=10;
	int value2=100;
	int result=add_c(value1, value2);
	(void)result;

	return 0;
}
