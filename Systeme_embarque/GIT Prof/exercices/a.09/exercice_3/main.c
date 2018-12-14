#include <stdio.h>
#include <stddef.h>
/**
 * Programmation C: Design OO
 * solution de l'exercice 3
 */

#define container_of(ptr, type, member)\
((type*) ((char*)(ptr) - offsetof(type, member)))

/** type and c-class definition */

struct c_object {
	void (*m_method_1)();
	unsigned long m_attr1;
};

struct c_fsm {
	void (*m_method_2)();
	unsigned long m_attr2;
};

struct c_process {
	void (*m_method_5)();
	unsigned long m_attr5;
	struct c_object m_object;
	struct c_state_1* m_state1;
};

struct attributes 
{
	unsigned long m_attr6;
};

struct c_state_1 {
	void (*m_method_3)();
	unsigned long m_attr3;
	struct c_object m_object;
	struct c_fsm m_fsm;
	struct c_process* m_process;
};

struct c_state_2 {
	void (*m_method_4)();
	unsigned long m_attr4;
	struct c_object m_object;
	struct c_fsm m_fsm;
	struct attributes m_attr[4];
};

/** c-class implementation */

/* c_object */
void object_method_1(struct c_object* oref)
{
	printf("object(%p): method_1\n", (void*)oref);
}

struct c_object* object_init (struct c_object* oref)
{
	oref->m_method_1 = object_method_1;
	oref->m_attr1 = 0;

	return oref;
}

/* c_fsm */
void fsm_method_2(struct c_fsm* oref)
{
	printf("fsm(%p): method_2\n", (void*)oref);
}

struct c_fsm* fsm_init (struct c_fsm* oref)
{
	oref->m_method_2 = fsm_method_2;
	oref->m_attr2 = 0;

	return oref;
}

/* c_process */
void process_method_5(struct c_process* oref)
{
	printf("process(%p): method_5\n", (void*)oref);
}

struct c_object* process_init (struct c_process* oref, struct c_state_1* state_1)
{
	oref->m_method_5 = process_method_5;
	oref->m_attr5 = 0;
	oref->m_state1 = state_1;
	object_init (&oref->m_object);

	return &oref->m_object;
}

/* c_state_1 */
void state_1_method_1(struct c_object* oref)
{
	struct c_state_1* mref = container_of(oref, struct c_state_1, m_object);
	printf("state_1(%p): method_1 (overloaded)\n", (void*)mref);
}

void state_1_method_3 (struct c_state_1* oref)
{
	printf("state_1(%p): method_3\n", (void*)oref);
}

struct c_object* state_1_init (struct c_state_1* oref, struct c_process* process)
{
	oref->m_method_3 = state_1_method_3;
	oref->m_attr3 = 0;
	oref->m_process = process;

	object_init (&oref->m_object);
	oref->m_object.m_method_1 = state_1_method_1;

	fsm_init (&oref->m_fsm);

	return &oref->m_object;
}

/* c_state_2 */
void state_2_method_2(struct c_fsm* oref)
{
	struct c_state_2* mref = container_of(oref, struct c_state_2, m_fsm);
	printf("state_2(%p): method_2 (overloaded)\n", (void*)mref);
}

void state_2_method_4 (struct c_state_2* oref)
{
	printf("state_2(%p): method_4\n", (void*)oref);
}

struct c_object* state_2_init (struct c_state_2* oref)
{
	oref->m_method_4 = state_2_method_4;
	oref->m_attr4 = 0;

	oref->m_attr[0].m_attr6 = 0;
	oref->m_attr[1].m_attr6 = 0;
	oref->m_attr[2].m_attr6 = 0;
	oref->m_attr[3].m_attr6 = 0;

	object_init (&oref->m_object);

	fsm_init (&oref->m_fsm);
	oref->m_fsm.m_method_2 = state_2_method_2;

	return &oref->m_object;
}



/** main program */

int main()
{
	struct c_process process;
	struct c_state_1 state_1;
	struct c_state_2 state_2;

	struct c_object* obj[3];
	struct c_fsm* fsm[2];

	obj[0] = process_init (&process, &state_1);
	obj[1] = state_1_init (&state_1, &process);
	obj[2] = state_2_init (&state_2);

	fsm[0] = &state_1.m_fsm;
	fsm[1] = &state_2.m_fsm;

	obj[0]->m_method_1 (obj[0]);
	obj[1]->m_method_1 (obj[1]);
	obj[2]->m_method_1 (obj[2]);

	fsm[0]->m_method_2 (fsm[0]);
	fsm[1]->m_method_2 (fsm[1]);

	return 0;
}
