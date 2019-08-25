#define KERNEL_REGS		15
#define KERNEL_NAME_LEN 32

// definition of the possible states of a task
enum kernel_states {
	KERNEL_READY, 
	KERNEL_RUNNING, 
	KERNEL_BLOCKED, 
	KERNEL_DELAYED,
	KERNEL_TERMINATED, 
};

// task context
struct kernel_context {
	uint32_t regs[KERNEL_REGS];
	uint32_t psr;
};

// definition of the task control block (tcb)
struct kernel_tcb {
	struct kernel_context context;
	enum kernel_states state;

	struct kernel_tcb* t_next;	// used to chain all tcb
	struct kernel_tcb* s_next;	// used to chain blocked task within a sema
	struct kernel_tcb* d_next;	// used to chain delayed threads
	uint64_t delay;				// delay in ticks

	int32_t id;					// unique task identification
	char name[KERNEL_NAME_LEN];	// task name

	uint32_t stack_size;		// task stack size in bytes
	uint32_t stack[];			// stack
};
