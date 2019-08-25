extern void kernel_transfer(
	struct kernel_context* former, 
	struct kernel_context* new);

static struct kernel_tcb idle_task = { // kernel idle task
	.state = KERNEL_RUNNING,
	.t_next = &idle_task,
	.id = 0,
	.name = "idle",
	.stack_size = 0,
};

static struct kernel_tcb* running_task  = &idle_task;

static void process_terminated_tasks(struct kernel_tcb* head) {
	// Remove all processes (tcb) having a KERNEL_TERMINATED state
	// don't forget to "free" the memory as well.
}

// this method shall be called to get a new task id
static int32_t kernel_new_taskid() {
	// Use a static variable to store the last id given
	// The first id returned by this function should be 1,
	// because 0 is reserved the the "idle" process. 
}

// --- implementation of public services / methods ----------------------------

struct kernel_tcb* kernel_new_tcb(uint32_t stack_sz, const char* name) {
	// Allocate memory for the tcb and for the stack.
	// Initialize the tcb fields (stack_size, id, name) with proper values
	// Returns a pointer to the allocated tcb
}

void kernel_add_tcb(struct kernel_tcb* tcb) {
	// Insert the tcb at the beginning of the chain starting at "idle_task"
}

struct kernel_tcb* kernel_running_task() {
	// Returns a pointer to the running task
}

void kernel_yield() {
	// Set the current task to KERNEL_READY if it is KERNEL_RUNNING.
	// Look for a task having a state of KERNEL_READY (starting from
	// the task that directly follow the current task).
	// Set "running_task" to the task that we just found.
	// Set the state of the new running task to KERNEL_RUNNING
	// Call the assembler method "kernel_transfer" to do the "real"
	// tranfer.
}

void kernel_launch() {
	while(1) {
		// Enable interrupts
		// call Yield
		// Process terminated tasks
	}
}

// --- micro kernel initialization --------------------------------------------
void kernel_init() { 
	// Nothing to do
}
