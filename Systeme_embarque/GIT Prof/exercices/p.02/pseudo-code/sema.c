// ----------------------------------------------------------------------------
// --- semaphore service implementation ---------------------------------------
// ----------------------------------------------------------------------------

struct sema {
	int32_t count;
	struct kernel_tcb* s_next;
	struct sema* chain;
};

static struct sema* sema_list = 0;

// --- public services ---

semaid_t sema_create (int initial_value) {
	// Allocate memory for a new semaphore
	// Set the counter attribute of the semaphore the the initial value
	// Set the thread list of the semaphore to NULL
	// Add the semaphore to the "sema_list" list
	// Returns the semaphore
}

int sema_destroy (semaid_t sema_id) {
	// If threads are still waiting for the semaphore:
	//   Returns -1
	// Remove the semaphorefrom the list
	// Free the memory
	// Return 0
}


void sema_signal (semaid_t sema_id) {
	// Disable the interrupts to protect the critical section
	// Increment the counter of the semaphore
	// If process are waiting for this semaphore:
	//   Set the status of the first process to KERNEL_READY
	//   Remove the thread from the waiting list of the semaphore
	// Re-enable the interrupts as before the call
}


void sema_wait (semaid_t sema_id) {
	// Disable the interrupts to protect the critical section
	// Decrement the counter of the semaphore
	// If the counter is negative:
	//    Add the thread *at the end* of the waiting list of the semaphore
	//    Set the state of the thread to KERNEL_BLOCKED
	// Re-enable the interrupts as before the call
	// Call yield() ! IMPORTANT !
}

int sema_count(semaid_t sema_id) {
	// Return the counter of a semaphore
}


// ----------------------------------------------------------------------------
// --- micro kernel sema library initialization -------------------------------
// ----------------------------------------------------------------------------

void sema_init() {
	// Nothing to do
}
