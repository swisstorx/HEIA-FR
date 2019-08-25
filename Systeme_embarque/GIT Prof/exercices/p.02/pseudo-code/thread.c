static struct kernel_tcb* delayed_threads;


static void process_delayed_threads(void* param) {
	while (1) {
		// Get the uptime
		// Iterate over all threads linked from "delayed_threads"
		// If the "delay" atttribute of the field is <= uptime:
		//   Wake-up the thread by reseting the delay attribute to 0
		//   and set the state to KERNEL_READY
		// Call yield()
	}
}

// --- implementation of local services / methods -----------------------------

static void thread_startup (void* param, thread_t thread) {
	thread (param);
	thread_exit();
}
 
// --- implementation of public services / methods ----------------------------

void thread_exit()  {
	// Set the state of the running task to KERNEL_TERMINATED
	// Call yield()
}

void thread_yield() {
	// Call kernel_yield
}

const char* thread_name() {
	// Returns the name of the running task
}

int thread_id() {
	// Return the id of the running task
}

int thread_create(
	thread_t thread, 
	void* param, 
	const char* name, 
	uint32_t stack_size)
{
	// Set the minumum stack size to 16KB
	// Create a new tcb
	// Set r0 of the context of the new tcb to the address of the param
	// Set r1 of the context of the new tcb to the address of the thread
	// Set sp of the context of the new tcb to the end of the stack.
	// Make sure that it is at a multiple of 8
	// Set lr of the context of the new tcb at the address of "thread_startup"
	// Set cpsr of the context of the new tcb to supervisor mode,
	// with IRQ and FIQ enabled
	// Set the state of the new tcb to KERNEL_READY
	// add the tcb to the chain
	// Return the id of the added tcb
}

void thread_delay(uint32_t ms) {
	// Get the tcb of the running task
	// Set the delay attribute of the tcb to wake-up time
	// Set the state of the tcb to "KERNEL_DELAYED"
	// Add the tcb the the "delayed_threads" list
	// Call yield()
}

// ----------------------------------------------------------------------------
// --- micro kernel thread library initialization ------------------------------
// ----------------------------------------------------------------------------

void thread_init()  {
	// Create a thread with "process_delayed_threads"
}
