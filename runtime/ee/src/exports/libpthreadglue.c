extern void __getThreadData();
extern void __getTlsStructFromThread();
extern void __globalTls();
extern void __globalTlsLock();
extern void __keysUsed();
extern void __maxTlsValues();
extern void __ps2StubThreadEntry();
extern void pte_osAtomicCompareExchange();
extern void pte_osAtomicDecrement();
extern void pte_osAtomicExchange();
extern void pte_osAtomicExchangeAdd();
extern void pte_osAtomicIncrement();
extern void pte_osInit();
extern void pte_osMutexCreate();
extern void pte_osMutexDelete();
extern void pte_osMutexLock();
extern void pte_osMutexTimedLock();
extern void pte_osMutexUnlock();
extern void pte_osSemaphoreCancellablePend();
extern void pte_osSemaphoreCreate();
extern void pte_osSemaphoreDelete();
extern void pte_osSemaphorePend();
extern void pte_osSemaphorePost();
extern void pte_osTerminate();
extern void pte_osThreadCancel();
extern void pte_osThreadCheckCancel();
extern void pte_osThreadCreate();
extern void pte_osThreadDelete();
extern void pte_osThreadExit();
extern void pte_osThreadExitAndDelete();
extern void pte_osThreadGetDefaultPriority();
extern void pte_osThreadGetHandle();
extern void pte_osThreadGetMaxPriority();
extern void pte_osThreadGetMinPriority();
extern void pte_osThreadGetPriority();
extern void pte_osThreadSetPriority();
extern void pte_osThreadSleep();
extern void pte_osThreadStart();
extern void pte_osThreadWaitForEnd();
extern void pte_osTlsAlloc();
extern void pte_osTlsFree();
extern void pte_osTlsGetValue();
extern void pte_osTlsSetValue();
extern void __pteTlsAlloc();
extern void pteTlsFree();
extern void pteTlsGetValue();
extern void pteTlsGlobalDestroy();
extern void pteTlsGlobalInit();
extern void __pteTlsSetValue();
extern void pteTlsThreadDestroy();
extern void pteTlsThreadInit();
extern void pthread_num_processors_np();
extern void __threadDataKey();
struct export_list_t {
    char * name;
    void * pointer;
} libpthreadglue_exports[] = {
    { "__getThreadData", __getThreadData }, 
    { "__getTlsStructFromThread", __getTlsStructFromThread }, 
    { "__globalTls", __globalTls }, 
    { "__globalTlsLock", __globalTlsLock }, 
    { "__keysUsed", __keysUsed }, 
    { "__maxTlsValues", __maxTlsValues }, 
    { "__ps2StubThreadEntry", __ps2StubThreadEntry }, 
    { "pte_osAtomicCompareExchange", pte_osAtomicCompareExchange }, 
    { "pte_osAtomicDecrement", pte_osAtomicDecrement }, 
    { "pte_osAtomicExchange", pte_osAtomicExchange }, 
    { "pte_osAtomicExchangeAdd", pte_osAtomicExchangeAdd }, 
    { "pte_osAtomicIncrement", pte_osAtomicIncrement }, 
    { "pte_osInit", pte_osInit }, 
    { "pte_osMutexCreate", pte_osMutexCreate }, 
    { "pte_osMutexDelete", pte_osMutexDelete }, 
    { "pte_osMutexLock", pte_osMutexLock }, 
    { "pte_osMutexTimedLock", pte_osMutexTimedLock }, 
    { "pte_osMutexUnlock", pte_osMutexUnlock }, 
    { "pte_osSemaphoreCancellablePend", pte_osSemaphoreCancellablePend }, 
    { "pte_osSemaphoreCreate", pte_osSemaphoreCreate }, 
    { "pte_osSemaphoreDelete", pte_osSemaphoreDelete }, 
    { "pte_osSemaphorePend", pte_osSemaphorePend }, 
    { "pte_osSemaphorePost", pte_osSemaphorePost }, 
    { "pte_osTerminate", pte_osTerminate }, 
    { "pte_osThreadCancel", pte_osThreadCancel }, 
    { "pte_osThreadCheckCancel", pte_osThreadCheckCancel }, 
    { "pte_osThreadCreate", pte_osThreadCreate }, 
    { "pte_osThreadDelete", pte_osThreadDelete }, 
    { "pte_osThreadExit", pte_osThreadExit }, 
    { "pte_osThreadExitAndDelete", pte_osThreadExitAndDelete }, 
    { "pte_osThreadGetDefaultPriority", pte_osThreadGetDefaultPriority }, 
    { "pte_osThreadGetHandle", pte_osThreadGetHandle }, 
    { "pte_osThreadGetMaxPriority", pte_osThreadGetMaxPriority }, 
    { "pte_osThreadGetMinPriority", pte_osThreadGetMinPriority }, 
    { "pte_osThreadGetPriority", pte_osThreadGetPriority }, 
    { "pte_osThreadSetPriority", pte_osThreadSetPriority }, 
    { "pte_osThreadSleep", pte_osThreadSleep }, 
    { "pte_osThreadStart", pte_osThreadStart }, 
    { "pte_osThreadWaitForEnd", pte_osThreadWaitForEnd }, 
    { "pte_osTlsAlloc", pte_osTlsAlloc }, 
    { "pte_osTlsFree", pte_osTlsFree }, 
    { "pte_osTlsGetValue", pte_osTlsGetValue }, 
    { "pte_osTlsSetValue", pte_osTlsSetValue }, 
    { "__pteTlsAlloc", __pteTlsAlloc }, 
    { "pteTlsFree", pteTlsFree }, 
    { "pteTlsGetValue", pteTlsGetValue }, 
    { "pteTlsGlobalDestroy", pteTlsGlobalDestroy }, 
    { "pteTlsGlobalInit", pteTlsGlobalInit }, 
    { "__pteTlsSetValue", __pteTlsSetValue }, 
    { "pteTlsThreadDestroy", pteTlsThreadDestroy }, 
    { "pteTlsThreadInit", pteTlsThreadInit }, 
    { "pthread_num_processors_np", pthread_num_processors_np }, 
    { "__threadDataKey", __threadDataKey }, 
    { 0, 0},
};
