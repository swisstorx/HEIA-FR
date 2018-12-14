/**
 * Programmation C: Design OO
 * solution de l'exercice 2
 */
#include <stdio.h>
#include "figure.h"
#include "square.h"
#include "trapeze.h"
#include "triangle.h"
#include "circle.h"
#include "group.h"


int main()
{
	int i;
	struct c_figure* fig[6];
	struct c_figure figure;
	struct c_square square;
	struct c_trapeze trapeze;
	struct c_circle circle;
	struct c_triangle triangle;
	struct c_group group;

	fig[0] = figure_init (&figure);
	fig[1] = square_init (&square, 10,20, 10);
	fig[2] = trapeze_init (&trapeze, 10,20, 30,40, 50,60, 70,80);
	fig[3] = circle_init (&circle, 80,90, 10);
	fig[4] = triangle_init (&triangle, 10,20, 60,50, 30,40);
	fig[5] = group_init (&group);

	for (i=0; i<6; i++) {
		fig[i]->m_draw   (fig[i]);
		fig[i]->m_move   (fig[i], 10, 20);
		fig[i]->m_resize (fig[i], -10, 100);
		fig[i]->m_rotate (fig[i], -45);
		fig[i]->m_erase  (fig[i]);
		fig[i]->m_show   (fig[i]);
	}

	printf("\n\n");
	for (i=0; i<5; i++) {
		group.m_add (&group, fig[i]);
	}
	fig[5]->m_draw   (fig[5]);            printf ("\n");
	fig[5]->m_move   (fig[5], 10, 20);    printf ("\n");
	fig[5]->m_resize (fig[5], -10, 100);  printf ("\n");
	fig[5]->m_rotate (fig[5], -45);       printf ("\n");
	fig[5]->m_erase  (fig[5]);            printf ("\n");
	fig[5]->m_show   (fig[5]);            printf ("\n");

	printf("\n");
	for (i=0; i<5; i++) {
		group.m_remove (&group, fig[i]);
	}
	fig[5]->m_draw   (fig[5]);            
	fig[5]->m_move   (fig[5], 10, 20);    
	fig[5]->m_resize (fig[5], -10, 100);  
	fig[5]->m_rotate (fig[5], -45);       
	fig[5]->m_erase  (fig[5]);            
	fig[5]->m_show   (fig[5]);            

	return 0;
}

