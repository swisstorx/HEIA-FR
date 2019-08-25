typedef void (*thread_t) (void* param);

extern int  thread_create (
	thread_t thread, 
	void* param, 
	const char* name, 
	uint32_t stack_size);
