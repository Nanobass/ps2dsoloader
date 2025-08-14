extern void pte_callUserDestroyRoutines();
extern void pte_cancellable_wait();
extern void pte_cleanupKey();
extern void pte_concurrency();
extern void pte_cond_check_need_init();
extern void pte_cond_list_head();
extern void pte_cond_list_lock();
extern void pte_cond_list_tail();
extern void pte_cond_test_init_lock();
extern void pte_features();
extern void pte_get_exception_services_code();
extern void pte_getprocessors();
extern void pte_is_attr();
extern void pte_mutex_check_need_init();
extern void pte_mutex_test_init_lock();
extern void pte_new();
extern void pte_pop_cleanup();
extern void pte_pop_cleanup_all();
extern void pte_processInitialized();
extern void pte_push_cleanup();
extern void pte_relmillisecs();
extern void pte_rwlock_cancelwrwait();
extern void pte_rwlock_check_need_init();
extern void pte_rwlock_test_init_lock();
extern void pte_selfThreadKey();
extern void pte_setthreadpriority();
extern void pte_smp_system();
extern void pte_spinlock_check_need_init();
extern void pte_spinlock_test_init_lock();
extern void pte_threadDestroy();
extern void pte_thread_detach_and_exit_np();
extern void pte_thread_detach_np();
extern void pte_threadExitAndDestroy();
extern void pte_threadReuseBottom();
extern void pte_thread_reuse_lock();
extern void pte_threadReusePop();
extern void pte_threadReusePush();
extern void pte_threadReuseTop();
extern void pte_threadStart();
extern void pte_throw();
extern void pte_tkAssocCreate();
extern void pte_tkAssocDestroy();
extern void pthread_atfork();
extern void pthread_attr_destroy();
extern void pthread_attr_getdetachstate();
extern void pthread_attr_getguardsize();
extern void pthread_attr_getinheritsched();
extern void pthread_attr_getschedparam();
extern void pthread_attr_getschedpolicy();
extern void pthread_attr_getscope();
extern void pthread_attr_getstack();
extern void pthread_attr_getstackaddr();
extern void pthread_attr_getstacksize();
extern void pthread_attr_init();
extern void pthread_attr_setdetachstate();
extern void pthread_attr_setguardsize();
extern void pthread_attr_setinheritsched();
extern void pthread_attr_setschedparam();
extern void pthread_attr_setschedpolicy();
extern void pthread_attr_setscope();
extern void pthread_attr_setstack();
extern void pthread_attr_setstackaddr();
extern void pthread_attr_setstacksize();
extern void pthread_barrierattr_destroy();
extern void pthread_barrierattr_getpshared();
extern void pthread_barrierattr_init();
extern void pthread_barrierattr_setpshared();
extern void pthread_barrier_destroy();
extern void pthread_barrier_init();
extern void pthread_barrier_wait();
extern void pthread_cancel();
extern void pthread_condattr_destroy();
extern void pthread_condattr_getclock();
extern void pthread_condattr_getpshared();
extern void pthread_condattr_init();
extern void pthread_condattr_setclock();
extern void pthread_condattr_setpshared();
extern void pthread_cond_broadcast();
extern void pthread_cond_destroy();
extern void pthread_cond_init();
extern void pthread_cond_signal();
extern void pthread_cond_timedwait();
extern void pthread_cond_wait();
extern void pthread_create();
extern void pthread_delay_np();
extern void pthread_detach();
extern void pthread_equal();
extern void pthread_exit();
extern void pthread_getconcurrency();
extern void pthread_getschedparam();
extern void pthread_getspecific();
extern void pthread_init();
extern void pthread_join();
extern void pthread_key_create();
extern void pthread_key_delete();
extern void pthread_kill();
extern void pthread_mutexattr_destroy();
extern void pthread_mutexattr_getkind_np();
extern void pthread_mutexattr_getpshared();
extern void pthread_mutexattr_gettype();
extern void pthread_mutexattr_init();
extern void pthread_mutexattr_setkind_np();
extern void pthread_mutexattr_setpshared();
extern void pthread_mutexattr_settype();
extern void pthread_mutex_destroy();
extern void pthread_mutex_init();
extern void pthread_mutex_lock();
extern void pthread_mutex_timedlock();
extern void pthread_mutex_trylock();
extern void pthread_mutex_unlock();
extern void pthread_num_processors_np();
extern void pthread_once();
extern void pthread_rwlockattr_destroy();
extern void pthread_rwlockattr_getpshared();
extern void pthread_rwlockattr_init();
extern void pthread_rwlockattr_setpshared();
extern void pthread_rwlock_destroy();
extern void pthread_rwlock_init();
extern void pthread_rwlock_rdlock();
extern void pthread_rwlock_timedrdlock();
extern void pthread_rwlock_timedwrlock();
extern void pthread_rwlock_tryrdlock();
extern void pthread_rwlock_trywrlock();
extern void pthread_rwlock_unlock();
extern void pthread_rwlock_wrlock();
extern void pthread_self();
extern void pthread_setcancelstate();
extern void pthread_setcanceltype();
extern void pthread_setconcurrency();
extern void pthread_setschedparam();
extern void pthread_setspecific();
extern void pthread_sigmask();
extern void pthread_spin_destroy();
extern void pthread_spin_init();
extern void pthread_spin_lock();
extern void pthread_spin_trylock();
extern void pthread_spin_unlock();
extern void pthread_terminate();
extern void pthread_testcancel();
extern void pthread_timechange_handler_np();
extern void sched_get_priority_max();
extern void sched_get_priority_min();
extern void sched_yield();
extern void sem_close();
extern void sem_destroy();
extern void sem_getvalue();
extern void sem_init();
extern void sem_open();
extern void sem_post();
extern void sem_post_multiple();
extern void sem_timedwait();
extern void sem_trywait();
extern void sem_unlink();
extern void sem_wait();
struct export_list_t {
    char * name;
    void * pointer;
} libpthread_exports[] = {
    { "pte_callUserDestroyRoutines", pte_callUserDestroyRoutines }, 
    { "pte_cancellable_wait", pte_cancellable_wait }, 
    { "pte_cleanupKey", pte_cleanupKey }, 
    { "pte_concurrency", pte_concurrency }, 
    { "pte_cond_check_need_init", pte_cond_check_need_init }, 
    { "pte_cond_list_head", pte_cond_list_head }, 
    { "pte_cond_list_lock", pte_cond_list_lock }, 
    { "pte_cond_list_tail", pte_cond_list_tail }, 
    { "pte_cond_test_init_lock", pte_cond_test_init_lock }, 
    { "pte_features", pte_features }, 
    { "pte_get_exception_services_code", pte_get_exception_services_code }, 
    { "pte_getprocessors", pte_getprocessors }, 
    { "pte_is_attr", pte_is_attr }, 
    { "pte_mutex_check_need_init", pte_mutex_check_need_init }, 
    { "pte_mutex_test_init_lock", pte_mutex_test_init_lock }, 
    { "pte_new", pte_new }, 
    { "pte_pop_cleanup", pte_pop_cleanup }, 
    { "pte_pop_cleanup_all", pte_pop_cleanup_all }, 
    { "pte_processInitialized", pte_processInitialized }, 
    { "pte_push_cleanup", pte_push_cleanup }, 
    { "pte_relmillisecs", pte_relmillisecs }, 
    { "pte_rwlock_cancelwrwait", pte_rwlock_cancelwrwait }, 
    { "pte_rwlock_check_need_init", pte_rwlock_check_need_init }, 
    { "pte_rwlock_test_init_lock", pte_rwlock_test_init_lock }, 
    { "pte_selfThreadKey", pte_selfThreadKey }, 
    { "pte_setthreadpriority", pte_setthreadpriority }, 
    { "pte_smp_system", pte_smp_system }, 
    { "pte_spinlock_check_need_init", pte_spinlock_check_need_init }, 
    { "pte_spinlock_test_init_lock", pte_spinlock_test_init_lock }, 
    { "pte_threadDestroy", pte_threadDestroy }, 
    { "pte_thread_detach_and_exit_np", pte_thread_detach_and_exit_np }, 
    { "pte_thread_detach_np", pte_thread_detach_np }, 
    { "pte_threadExitAndDestroy", pte_threadExitAndDestroy }, 
    { "pte_threadReuseBottom", pte_threadReuseBottom }, 
    { "pte_thread_reuse_lock", pte_thread_reuse_lock }, 
    { "pte_threadReusePop", pte_threadReusePop }, 
    { "pte_threadReusePush", pte_threadReusePush }, 
    { "pte_threadReuseTop", pte_threadReuseTop }, 
    { "pte_threadStart", pte_threadStart }, 
    { "pte_throw", pte_throw }, 
    { "pte_tkAssocCreate", pte_tkAssocCreate }, 
    { "pte_tkAssocDestroy", pte_tkAssocDestroy }, 
    { "pthread_atfork", pthread_atfork }, 
    { "pthread_attr_destroy", pthread_attr_destroy }, 
    { "pthread_attr_getdetachstate", pthread_attr_getdetachstate }, 
    { "pthread_attr_getguardsize", pthread_attr_getguardsize }, 
    { "pthread_attr_getinheritsched", pthread_attr_getinheritsched }, 
    { "pthread_attr_getschedparam", pthread_attr_getschedparam }, 
    { "pthread_attr_getschedpolicy", pthread_attr_getschedpolicy }, 
    { "pthread_attr_getscope", pthread_attr_getscope }, 
    { "pthread_attr_getstack", pthread_attr_getstack }, 
    { "pthread_attr_getstackaddr", pthread_attr_getstackaddr }, 
    { "pthread_attr_getstacksize", pthread_attr_getstacksize }, 
    { "pthread_attr_init", pthread_attr_init }, 
    { "pthread_attr_setdetachstate", pthread_attr_setdetachstate }, 
    { "pthread_attr_setguardsize", pthread_attr_setguardsize }, 
    { "pthread_attr_setinheritsched", pthread_attr_setinheritsched }, 
    { "pthread_attr_setschedparam", pthread_attr_setschedparam }, 
    { "pthread_attr_setschedpolicy", pthread_attr_setschedpolicy }, 
    { "pthread_attr_setscope", pthread_attr_setscope }, 
    { "pthread_attr_setstack", pthread_attr_setstack }, 
    { "pthread_attr_setstackaddr", pthread_attr_setstackaddr }, 
    { "pthread_attr_setstacksize", pthread_attr_setstacksize }, 
    { "pthread_barrierattr_destroy", pthread_barrierattr_destroy }, 
    { "pthread_barrierattr_getpshared", pthread_barrierattr_getpshared }, 
    { "pthread_barrierattr_init", pthread_barrierattr_init }, 
    { "pthread_barrierattr_setpshared", pthread_barrierattr_setpshared }, 
    { "pthread_barrier_destroy", pthread_barrier_destroy }, 
    { "pthread_barrier_init", pthread_barrier_init }, 
    { "pthread_barrier_wait", pthread_barrier_wait }, 
    { "pthread_cancel", pthread_cancel }, 
    { "pthread_condattr_destroy", pthread_condattr_destroy }, 
    { "pthread_condattr_getclock", pthread_condattr_getclock }, 
    { "pthread_condattr_getpshared", pthread_condattr_getpshared }, 
    { "pthread_condattr_init", pthread_condattr_init }, 
    { "pthread_condattr_setclock", pthread_condattr_setclock }, 
    { "pthread_condattr_setpshared", pthread_condattr_setpshared }, 
    { "pthread_cond_broadcast", pthread_cond_broadcast }, 
    { "pthread_cond_destroy", pthread_cond_destroy }, 
    { "pthread_cond_init", pthread_cond_init }, 
    { "pthread_cond_signal", pthread_cond_signal }, 
    { "pthread_cond_timedwait", pthread_cond_timedwait }, 
    { "pthread_cond_wait", pthread_cond_wait }, 
    { "pthread_create", pthread_create }, 
    { "pthread_delay_np", pthread_delay_np }, 
    { "pthread_detach", pthread_detach }, 
    { "pthread_equal", pthread_equal }, 
    { "pthread_exit", pthread_exit }, 
    { "pthread_getconcurrency", pthread_getconcurrency }, 
    { "pthread_getschedparam", pthread_getschedparam }, 
    { "pthread_getspecific", pthread_getspecific }, 
    { "pthread_init", pthread_init }, 
    { "pthread_join", pthread_join }, 
    { "pthread_key_create", pthread_key_create }, 
    { "pthread_key_delete", pthread_key_delete }, 
    { "pthread_kill", pthread_kill }, 
    { "pthread_mutexattr_destroy", pthread_mutexattr_destroy }, 
    { "pthread_mutexattr_getkind_np", pthread_mutexattr_getkind_np }, 
    { "pthread_mutexattr_getpshared", pthread_mutexattr_getpshared }, 
    { "pthread_mutexattr_gettype", pthread_mutexattr_gettype }, 
    { "pthread_mutexattr_init", pthread_mutexattr_init }, 
    { "pthread_mutexattr_setkind_np", pthread_mutexattr_setkind_np }, 
    { "pthread_mutexattr_setpshared", pthread_mutexattr_setpshared }, 
    { "pthread_mutexattr_settype", pthread_mutexattr_settype }, 
    { "pthread_mutex_destroy", pthread_mutex_destroy }, 
    { "pthread_mutex_init", pthread_mutex_init }, 
    { "pthread_mutex_lock", pthread_mutex_lock }, 
    { "pthread_mutex_timedlock", pthread_mutex_timedlock }, 
    { "pthread_mutex_trylock", pthread_mutex_trylock }, 
    { "pthread_mutex_unlock", pthread_mutex_unlock }, 
    { "pthread_num_processors_np", pthread_num_processors_np }, 
    { "pthread_once", pthread_once }, 
    { "pthread_rwlockattr_destroy", pthread_rwlockattr_destroy }, 
    { "pthread_rwlockattr_getpshared", pthread_rwlockattr_getpshared }, 
    { "pthread_rwlockattr_init", pthread_rwlockattr_init }, 
    { "pthread_rwlockattr_setpshared", pthread_rwlockattr_setpshared }, 
    { "pthread_rwlock_destroy", pthread_rwlock_destroy }, 
    { "pthread_rwlock_init", pthread_rwlock_init }, 
    { "pthread_rwlock_rdlock", pthread_rwlock_rdlock }, 
    { "pthread_rwlock_timedrdlock", pthread_rwlock_timedrdlock }, 
    { "pthread_rwlock_timedwrlock", pthread_rwlock_timedwrlock }, 
    { "pthread_rwlock_tryrdlock", pthread_rwlock_tryrdlock }, 
    { "pthread_rwlock_trywrlock", pthread_rwlock_trywrlock }, 
    { "pthread_rwlock_unlock", pthread_rwlock_unlock }, 
    { "pthread_rwlock_wrlock", pthread_rwlock_wrlock }, 
    { "pthread_self", pthread_self }, 
    { "pthread_setcancelstate", pthread_setcancelstate }, 
    { "pthread_setcanceltype", pthread_setcanceltype }, 
    { "pthread_setconcurrency", pthread_setconcurrency }, 
    { "pthread_setschedparam", pthread_setschedparam }, 
    { "pthread_setspecific", pthread_setspecific }, 
    { "pthread_sigmask", pthread_sigmask }, 
    { "pthread_spin_destroy", pthread_spin_destroy }, 
    { "pthread_spin_init", pthread_spin_init }, 
    { "pthread_spin_lock", pthread_spin_lock }, 
    { "pthread_spin_trylock", pthread_spin_trylock }, 
    { "pthread_spin_unlock", pthread_spin_unlock }, 
    { "pthread_terminate", pthread_terminate }, 
    { "pthread_testcancel", pthread_testcancel }, 
    { "pthread_timechange_handler_np", pthread_timechange_handler_np }, 
    { "sched_get_priority_max", sched_get_priority_max }, 
    { "sched_get_priority_min", sched_get_priority_min }, 
    { "sched_yield", sched_yield }, 
    { "sem_close", sem_close }, 
    { "sem_destroy", sem_destroy }, 
    { "sem_getvalue", sem_getvalue }, 
    { "sem_init", sem_init }, 
    { "sem_open", sem_open }, 
    { "sem_post", sem_post }, 
    { "sem_post_multiple", sem_post_multiple }, 
    { "sem_timedwait", sem_timedwait }, 
    { "sem_trywait", sem_trywait }, 
    { "sem_unlink", sem_unlink }, 
    { "sem_wait", sem_wait }, 
    { 0, 0},
};
