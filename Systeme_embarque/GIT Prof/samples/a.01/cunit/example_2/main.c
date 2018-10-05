/**
 *  Simple program to demonstrate the CUnit unit test framework.
 */
#include "CUnit/Basic.h"

/** function to be tested */
int max (int i1, int i2)
{
  int r = 0;
  if (i1 >= 1000) return -1;
  if (i1 > i2) 
	r = i1;
  else 
	r = i2;
  return r;
}


/** simple tests of "max" */
void t_max()
{
   CU_ASSERT(max(999,0) == 999);
   CU_ASSERT(max(1000,0) == 1000);
   CU_ASSERT(max(1001,0) == -1);
   CU_ASSERT(max(10001,0) == -1);

   CU_ASSERT(max(2,0)  == 2);
   CU_ASSERT(max(-1,2) == 2);
   CU_ASSERT(max(2,2)  == 2);
}


/** test suite initialisation */
int init_suite() {return 0; }

/** test suite clean-up */
int clean_suite() {return 0; }


/** main program to run the CUnit test suite. */
int main()
{
   /* init the CUnit test registry */
   CU_initialize_registry();

   /* add test suite to registry */
   CU_pSuite suite = CU_add_suite ("Suite", init_suite, clean_suite);
   
   /* add the tests to the suite */
   CU_add_test(suite, "test 1", t_max);

	/* run the tests */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();

   return CU_get_error();
}



