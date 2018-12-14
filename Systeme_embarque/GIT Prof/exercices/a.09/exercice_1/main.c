/**
 * Programmation C: Design OO
 * solution de l'exercice 1
 */

#include <stdio.h>
#include "figure.h"


int main()
{
	struct c_figure fig;
	figure_init (&fig);

	fig.m_draw   (&fig);
	fig.m_move   (&fig, 10, 20);
	fig.m_resize (&fig, -10, 100);
	fig.m_rotate (&fig, -45);
	fig.m_erase  (&fig);
	fig.m_show   (&fig);

	return 0;
}
