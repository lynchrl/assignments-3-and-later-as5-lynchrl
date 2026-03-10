#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg, ...)
// #define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg, ...) printf("threading ERROR: " msg "\n", ##__VA_ARGS__)

void *threadfunc(void *thread_param)
{
    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    // struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    struct thread_data *thread_func_args = (struct thread_data *)thread_param;
    int rv = usleep(thread_func_args->wait_to_obtain_ms * 1000);
    if (rv != 0)
    {
        perror("usleep");
        ERROR_LOG("usleep failed while waiting to obtain mutex");
        thread_func_args->thread_complete_success = false;
        return thread_func_args;
    }
    rv = pthread_mutex_lock(thread_func_args->mutex);
    if (rv != 0)
    {
        ERROR_LOG("pthread_mutex_lock failed: %d", rv);
        thread_func_args->thread_complete_success = false;
        return thread_func_args;
    }
    rv = usleep(thread_func_args->wait_to_release_ms * 1000);
    if (rv != 0)
    {
        perror("usleep");
        ERROR_LOG("usleep failed while waiting to release mutex");
        thread_func_args->thread_complete_success = false;
        return thread_func_args;
    }
    rv = pthread_mutex_unlock(thread_func_args->mutex);
    if (rv != 0)
    {
        ERROR_LOG("pthread_mutex_unlock failed: %d", rv);
        thread_func_args->thread_complete_success = false;
        return thread_func_args;
    }
    thread_func_args->thread_complete_success = true;
    return thread_func_args;
}

bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex, int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
    // Allocated and initialize thread_data
    struct thread_data *data = malloc(sizeof(struct thread_data));
    if (data == NULL)
    {
        ERROR_LOG("Failed to allocate memory for thread_data struct");
        return false;
    }
    data->mutex = mutex;
    data->wait_to_obtain_ms = wait_to_obtain_ms;
    data->wait_to_release_ms = wait_to_release_ms;
    data->thread_complete_success = false;

    // Create the thread. Use provided thread pointer (presumably created by caller).
    int rv = pthread_create(thread, NULL, threadfunc, data);
    if (rv != 0) {
        ERROR_LOG("pthread_create failed: %d", rv);
        return false;
    }

    return true;
}
