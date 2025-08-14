extern void AddDmacHandler();
extern void AddDmacHandler2();
extern void AddIntcHandler();
extern void AddIntcHandler2();
extern void AddSbusIntcHandler();
extern void __adjustTime();
extern void AlarmHandler();
extern void AllocTimerCounter();
extern void CancelWakeupThread();
extern void ChangeGP();
extern void ChangeThreadPriority();
extern void configConvertToGmtTime();
extern void configConvertToLocalTime();
extern void configConvertToLocalTimeWithIODriver();
extern void configGetDateFormat();
extern void configGetDateFormatWithIODriver();
extern void configGetLanguage();
extern void configGetLanguageWithIODriver();
extern void configGetTimeFormat();
extern void configGetTimeFormatWithIODriver();
extern void configGetTimezone();
extern void configGetTimezoneWithIODriver();
extern void configGetTvScreenType();
extern void configGetTvScreenTypeWithIODriver();
extern void configIsDaylightSavingEnabled();
extern void configIsDaylightSavingEnabledWithIODriver();
extern void configIsSpdifEnabled();
extern void configIsSpdifEnabledWithIODriver();
extern void configSetDateFormat();
extern void configSetDateFormatWithIODriver();
extern void configSetDaylightSavingEnabled();
extern void configSetDaylightSavingEnabledWithIODriver();
extern void configSetLanguage();
extern void configSetLanguageWithIODriver();
extern void configSetSpdifEnabled();
extern void configSetSpdifEnabledWithIODriver();
extern void configSetTimeFormat();
extern void configSetTimeFormatWithIODriver();
extern void configSetTimezone();
extern void configSetTimezoneWithIODriver();
extern void configSetTvScreenType();
extern void configSetTvScreenTypeWithIODriver();
extern void convertfrombcd();
extern void converttobcd();
extern void Copy();
extern void CpuConfig();
extern void cpu_ticks();
extern void CreateEventFlag();
extern void CreateSema();
extern void CreateThread();
extern void Deci2Call();
extern void DelayThread();
extern void DeleteEventFlag();
extern void DeleteSema();
extern void DeleteThread();
extern void DIntr();
extern void DisableCache();
extern void DisableDispatchThread();
extern void _DisableDmac();
extern void DisableDmac();
extern void DisableDmacHandler();
extern void _DisableIntc();
extern void DisableIntc();
extern void DisableIntcHandler();
extern void eenull();
extern void EIntr();
extern void EnableCache();
extern void EnableDispatchThread();
extern void _EnableDmac();
extern void EnableDmac();
extern void EnableDmacHandler();
extern void _EnableIntc();
extern void EnableIntc();
extern void EnableIntcHandler();
extern void EndOfHeap();
extern void EndTimer();
extern void erl_id();
extern void __errno();
extern void errno();
extern void _ExecOSD();
extern void ExecOSD();
extern void _ExecPS2();
extern void ExecPS2();
extern void Exit();
extern void ExitDeleteThread();
extern void ExitThread();
extern void ExpandScratchPad();
extern void _fio_block_mode();
extern void _fio_cd();
extern void fioChstat();
extern void fioClose();
extern void _fio_completion_sema();
extern void fioDclose();
extern void fioDopen();
extern void fioDread();
extern void fioExit();
extern void fioFormat();
extern void fioGetc();
extern void fioGets();
extern void fioGetstat();
extern void _fio_init();
extern void fioInit();
extern void _fio_intr();
extern void _fio_intr_data();
extern void fioIoctl();
extern void _fio_io_sema();
extern void fioLseek();
extern void fioMkdir();
extern void fioOpen();
extern void fioPutc();
extern void fioRead();
extern void _fio_read_intr();
extern void _fio_recv_data();
extern void fioRemove();
extern void fioRmdir();
extern void fioSetBlockMode();
extern void fioSync();
extern void fioWrite();
extern void FlushCache();
extern void ForTimer_InitAlarm();
extern void FreeTimerCounter();
extern void g_AlarmBuf();
extern void g_CounterBuf();
extern void GetCop0();
extern void GetEntryAddress();
extern void GetExceptionHandler();
extern void GetGP();
extern void _GetGsDxDyOffset();
extern void GetGsHParam();
extern void GetGsVParam();
extern void GetInterruptHandler();
extern void GetMemoryMode();
extern void GetMemorySize();
extern void GetOsdConfigParam();
extern void GetOsdConfigParam2();
extern void GetRomName();
extern void GetRomNameWithIODriver();
extern void GetSyscall();
extern void GetSyscallHandler();
extern void GetThreadId();
extern void GetTimerBaseTime();
extern void GetTimerCount();
extern void GetTimerPreScaleFactor();
extern void GetTimerSystemTime();
extern void GetTimerUsedUnusedCounters();
extern void GetTLBEntry();
extern void g_pFreeAlarm();
extern void g_RomName();
extern void GsGetIMR();
extern void GsPutIMR();
extern void g_t10KConfig();
extern void g_Timer();
extern void iAllocTimerCounter();
extern void iCancelWakeupThread();
extern void iChangeThreadPriority();
extern void iCpuConfig();
extern void iDeleteSema();
extern void _iDisableDmac();
extern void iDisableDmac();
extern void iDisableDmacHandler();
extern void _iDisableIntc();
extern void iDisableIntc();
extern void iDisableIntcHandler();
extern void _iEnableDmac();
extern void iEnableDmac();
extern void iEnableDmacHandler();
extern void _iEnableIntc();
extern void iEnableIntc();
extern void iEnableIntcHandler();
extern void iFlushCache();
extern void iFreeTimerCounter();
extern void iGetCop0();
extern void _iGetThreadId();
extern void iGetTimerBaseTime();
extern void iGetTimerCount();
extern void iGetTimerSystemTime();
extern void iGetTimerUsedUnusedCounters();
extern void iGetTLBEntry();
extern void iGsGetIMR();
extern void iGsPutIMR();
extern void _ih_caps();
extern void _ih_cd();
extern void iInvalidDCache();
extern void InitAlarm();
extern void InitDebug();
extern void InitExecPS2();
extern void InitOsd();
extern void _InitSys();
extern void InitThread();
extern void InitTimer();
extern void _InitTLB();
extern void InitTLB();
extern void InitTLBFunctions();
extern void InsertAlarm_ForTimer();
extern void Interrupt2Iop();
extern void _InvalidDCache();
extern void InvalidDCache();
extern void _iop_reboot_count();
extern void iPollSema();
extern void iProbeTLBEntry();
extern void iPutTLBEntry();
extern void iReferSemaStatus();
extern void iReferThreadStatus();
extern void _iReleaseAlarm();
extern void iReleaseAlarm();
extern void iReleaseTimerAlarm();
extern void iReleaseWaitThread();
extern void iResumeThread();
extern void _iRotateThreadReadyQueue();
extern void iRotateThreadReadyQueue();
extern void isceSifDmaStat();
extern void isceSifSendCmd();
extern void isceSifSetDChain();
extern void isceSifSetDma();
extern void IsDESRMachine();
extern void IsDESRMachineWithIODriver();
extern void IsEarlyJap();
extern void _iSetAlarm();
extern void iSetAlarm();
extern void iSetEventFlag();
extern void iSetTimerAlarm();
extern void iSetTimerHandler();
extern void iSetTLBEntry();
extern void iSignalSema();
extern void IsT10K();
extern void IsT10KWithIODriver();
extern void iStartTimerCounter();
extern void iStopTimerCounter();
extern void _iSuspendThread();
extern void iSuspendThread();
extern void iSyncDCache();
extern void iTerminateThread();
extern void _iWakeupThread();
extern void iWakeupThread();
extern void kCopy();
extern void kCopyBytes();
extern void _kExecArg();
extern void KExit();
extern void kputs();
extern void KSeg0();
extern void _lf_cd();
extern void _lf_init();
extern void _LoadExecPS2();
extern void LoadExecPS2();
extern void MachineType();
extern void osdsrc();
extern void PatchIsNeeded();
extern void PollSema();
extern void _print();
extern void ProbeTLBEntry();
extern void _ps2sdk_deinit_timer();
extern void _ps2sdk_deinit_timer_impl();
extern void _ps2sdk_init_timer();
extern void _ps2sdk_init_timer_impl();
extern void PSMode();
extern void PutTLBEntry();
extern void ReferSemaStatus();
extern void ReferThreadStatus();
extern void _ReleaseAlarm();
extern void ReleaseAlarm();
extern void ReleaseTimerAlarm();
extern void ReleaseWaitThread();
extern void RemoveDmacHandler();
extern void RemoveIntcHandler();
extern void RemoveSbusIntcHandler();
extern void ResetEE();
extern void ResumeThread();
extern void RFU009();
extern void RFU059();
extern void RFU060();
extern void RFU061();
extern void RFU105();
extern void RotateThreadReadyQueue();
extern void _rpc_get_fpacket();
extern void _rpc_get_packet();
extern void sceDeci2Close();
extern void sceDeci2ExLock();
extern void sceDeci2ExRecv();
extern void sceDeci2ExReqSend();
extern void sceDeci2ExSend();
extern void sceDeci2ExUnLock();
extern void sceDeci2Open();
extern void sceDeci2Poll();
extern void sceDeci2ReqSend();
extern void sceSifAddCmdHandler();
extern void sceSifBindRpc();
extern void sceSifCallRpc();
extern void sceSifCheckStatRpc();
extern void sceSifDmaStat();
extern void sceSifExecRequest();
extern void sceSifExitCmd();
extern void sceSifExitRpc();
extern void sceSifGetNextRequest();
extern void sceSifGetOtherData();
extern void sceSifGetReg();
extern void sceSifGetSreg();
extern void sceSifInitCmd();
extern void sceSifInitRpc();
extern void sceSifRegisterRpc();
extern void sceSifRemoveCmdHandler();
extern void sceSifRemoveRpc();
extern void sceSifRemoveRpcQueue();
extern void sceSifRpcLoop();
extern void sceSifSendCmd();
extern void sceSifSetCmdBuffer();
extern void sceSifSetDChain();
extern void sceSifSetDma();
extern void sceSifSetReg();
extern void sceSifSetRpcQueue();
extern void sceSifSetSreg();
extern void sceSifSetSysCmdBuffer();
extern void sceSifStopDma();
extern void sceSifWriteBackDCache();
extern void sceTtyHandler();
extern void sceTtyInit();
extern void sceTtyRead();
extern void sceTtyWrite();
extern void _SetAlarm();
extern void SetAlarm();
extern void SetArg();
extern void SetCPUTimer();
extern void SetCPUTimerHandler();
extern void SetEventFlag();
extern void SetGP();
extern void SetGsCrt();
extern void SetGsHParam();
extern void SetGsVParam();
extern void SetMemoryMode();
extern void SetNextComp();
extern void SetOsdConfigParam();
extern void SetOsdConfigParam2();
extern void SetPgifHandler();
extern void SetSyscall();
extern void SetT2();
extern void SetT2_COMP();
extern void SetT2_COUNT();
extern void SetT2_MODE();
extern void SetTimerAlarm();
extern void SetTimerCount();
extern void SetTimerHandler();
extern void _SetTLBEntry();
extern void setup();
extern void SetupHeap();
extern void SetupThread();
extern void SetVCommonHandler();
extern void SetVInterruptHandler();
extern void SetVSyncFlag();
extern void SetVTLBRefillHandler();
extern void SifAllocIopHeap();
extern void _sif_cmd_data();
extern void _SifCmdIntHandler();
extern void SifExecModuleBuffer();
extern void SifExecModuleFile();
extern void SifExitIopHeap();
extern void SifFreeIopHeap();
extern void SifInitIopHeap();
extern void SifIopGetVal();
extern void SifIopIsAlive();
extern void SifIopReboot();
extern void SifIopReset();
extern void SifIopSetVal();
extern void SifIopSync();
extern void SifLoadElf();
extern void SifLoadElfEncrypted();
extern void _SifLoadElfPart();
extern void SifLoadElfPart();
extern void SifLoadFileExit();
extern void SifLoadFileInit();
extern void SifLoadIopHeap();
extern void _SifLoadModule();
extern void SifLoadModule();
extern void _SifLoadModuleBuffer();
extern void SifLoadModuleBuffer();
extern void SifLoadModuleEncrypted();
extern void SifLoadStartModule();
extern void SifLoadStartModuleBuffer();
extern void _sif_rpc_data();
extern void SifSearchModuleByAddress();
extern void SifSearchModuleByName();
extern void _SifSendCmd();
extern void SifStopModule();
extern void SifUnloadModule();
extern void SignalSema();
extern void sio_flush();
extern void sio_getc();
extern void sio_getc_block();
extern void sio_gets();
extern void sio_init();
extern void sio_putc();
extern void sio_puts();
extern void sio_putsn();
extern void sio_read();
extern void sio_write();
extern void size_eenull();
extern void size_osdsrc();
extern void size_srcfile();
extern void size_tlbsrc();
extern void SleepThread();
extern void srcfile();
extern void stack();
extern void StartThread();
extern void StartTimerCounter();
extern void StartTimerSystemTime();
extern void StopTimerCounter();
extern void StopTimerSystemTime();
extern void SuspendThread();
extern void _SyncDCache();
extern void SyncDCache();
extern void __syscall();
extern void SysEntry();
extern void TerminateLibrary();
extern void TerminateThread();
extern void TimerBusClock2Freq();
extern void TimerBusClock2USec();
extern void TimerFreq2BusClock();
extern void TimerHandler_callback();
extern void TimerUSec2BusClock();
extern void tinfo();
extern void tlbsrc();
extern void topArg();
extern void topId();
extern void topSema();
extern void ttyinit();
extern void UnlinkAlarm_ForTimer();
extern void WaitSema();
extern void WaitSemaEx();
struct export_list_t {
    char * name;
    void * pointer;
} libkernel_exports[] = {
    { "AddDmacHandler", AddDmacHandler }, 
    { "AddDmacHandler2", AddDmacHandler2 }, 
    { "AddIntcHandler", AddIntcHandler }, 
    { "AddIntcHandler2", AddIntcHandler2 }, 
    { "AddSbusIntcHandler", AddSbusIntcHandler }, 
    { "__adjustTime", __adjustTime }, 
    { "AlarmHandler", AlarmHandler }, 
    { "AllocTimerCounter", AllocTimerCounter }, 
    { "CancelWakeupThread", CancelWakeupThread }, 
    { "ChangeGP", ChangeGP }, 
    { "ChangeThreadPriority", ChangeThreadPriority }, 
    { "configConvertToGmtTime", configConvertToGmtTime }, 
    { "configConvertToLocalTime", configConvertToLocalTime }, 
    { "configConvertToLocalTimeWithIODriver", configConvertToLocalTimeWithIODriver }, 
    { "configGetDateFormat", configGetDateFormat }, 
    { "configGetDateFormatWithIODriver", configGetDateFormatWithIODriver }, 
    { "configGetLanguage", configGetLanguage }, 
    { "configGetLanguageWithIODriver", configGetLanguageWithIODriver }, 
    { "configGetTimeFormat", configGetTimeFormat }, 
    { "configGetTimeFormatWithIODriver", configGetTimeFormatWithIODriver }, 
    { "configGetTimezone", configGetTimezone }, 
    { "configGetTimezoneWithIODriver", configGetTimezoneWithIODriver }, 
    { "configGetTvScreenType", configGetTvScreenType }, 
    { "configGetTvScreenTypeWithIODriver", configGetTvScreenTypeWithIODriver }, 
    { "configIsDaylightSavingEnabled", configIsDaylightSavingEnabled }, 
    { "configIsDaylightSavingEnabledWithIODriver", configIsDaylightSavingEnabledWithIODriver }, 
    { "configIsSpdifEnabled", configIsSpdifEnabled }, 
    { "configIsSpdifEnabledWithIODriver", configIsSpdifEnabledWithIODriver }, 
    { "configSetDateFormat", configSetDateFormat }, 
    { "configSetDateFormatWithIODriver", configSetDateFormatWithIODriver }, 
    { "configSetDaylightSavingEnabled", configSetDaylightSavingEnabled }, 
    { "configSetDaylightSavingEnabledWithIODriver", configSetDaylightSavingEnabledWithIODriver }, 
    { "configSetLanguage", configSetLanguage }, 
    { "configSetLanguageWithIODriver", configSetLanguageWithIODriver }, 
    { "configSetSpdifEnabled", configSetSpdifEnabled }, 
    { "configSetSpdifEnabledWithIODriver", configSetSpdifEnabledWithIODriver }, 
    { "configSetTimeFormat", configSetTimeFormat }, 
    { "configSetTimeFormatWithIODriver", configSetTimeFormatWithIODriver }, 
    { "configSetTimezone", configSetTimezone }, 
    { "configSetTimezoneWithIODriver", configSetTimezoneWithIODriver }, 
    { "configSetTvScreenType", configSetTvScreenType }, 
    { "configSetTvScreenTypeWithIODriver", configSetTvScreenTypeWithIODriver }, 
    { "convertfrombcd", convertfrombcd }, 
    { "converttobcd", converttobcd }, 
    { "Copy", Copy }, 
    { "CpuConfig", CpuConfig }, 
    { "cpu_ticks", cpu_ticks }, 
    { "CreateEventFlag", CreateEventFlag }, 
    { "CreateSema", CreateSema }, 
    { "CreateThread", CreateThread }, 
    { "Deci2Call", Deci2Call }, 
    { "DelayThread", DelayThread }, 
    { "DeleteEventFlag", DeleteEventFlag }, 
    { "DeleteSema", DeleteSema }, 
    { "DeleteThread", DeleteThread }, 
    { "DIntr", DIntr }, 
    { "DisableCache", DisableCache }, 
    { "DisableDispatchThread", DisableDispatchThread }, 
    { "_DisableDmac", _DisableDmac }, 
    { "DisableDmac", DisableDmac }, 
    { "DisableDmacHandler", DisableDmacHandler }, 
    { "_DisableIntc", _DisableIntc }, 
    { "DisableIntc", DisableIntc }, 
    { "DisableIntcHandler", DisableIntcHandler }, 
    { "eenull", eenull }, 
    { "EIntr", EIntr }, 
    { "EnableCache", EnableCache }, 
    { "EnableDispatchThread", EnableDispatchThread }, 
    { "_EnableDmac", _EnableDmac }, 
    { "EnableDmac", EnableDmac }, 
    { "EnableDmacHandler", EnableDmacHandler }, 
    { "_EnableIntc", _EnableIntc }, 
    { "EnableIntc", EnableIntc }, 
    { "EnableIntcHandler", EnableIntcHandler }, 
    { "EndOfHeap", EndOfHeap }, 
    { "EndTimer", EndTimer }, 
    { "erl_id", erl_id }, 
    { "__errno", __errno }, 
    { "errno", errno }, 
    { "_ExecOSD", _ExecOSD }, 
    { "ExecOSD", ExecOSD }, 
    { "_ExecPS2", _ExecPS2 }, 
    { "ExecPS2", ExecPS2 }, 
    { "Exit", Exit }, 
    { "ExitDeleteThread", ExitDeleteThread }, 
    { "ExitThread", ExitThread }, 
    { "ExpandScratchPad", ExpandScratchPad }, 
    { "_fio_block_mode", _fio_block_mode }, 
    { "_fio_cd", _fio_cd }, 
    { "fioChstat", fioChstat }, 
    { "fioClose", fioClose }, 
    { "_fio_completion_sema", _fio_completion_sema }, 
    { "fioDclose", fioDclose }, 
    { "fioDopen", fioDopen }, 
    { "fioDread", fioDread }, 
    { "fioExit", fioExit }, 
    { "fioFormat", fioFormat }, 
    { "fioGetc", fioGetc }, 
    { "fioGets", fioGets }, 
    { "fioGetstat", fioGetstat }, 
    { "_fio_init", _fio_init }, 
    { "fioInit", fioInit }, 
    { "_fio_intr", _fio_intr }, 
    { "_fio_intr_data", _fio_intr_data }, 
    { "fioIoctl", fioIoctl }, 
    { "_fio_io_sema", _fio_io_sema }, 
    { "fioLseek", fioLseek }, 
    { "fioMkdir", fioMkdir }, 
    { "fioOpen", fioOpen }, 
    { "fioPutc", fioPutc }, 
    { "fioRead", fioRead }, 
    { "_fio_read_intr", _fio_read_intr }, 
    { "_fio_recv_data", _fio_recv_data }, 
    { "fioRemove", fioRemove }, 
    { "fioRmdir", fioRmdir }, 
    { "fioSetBlockMode", fioSetBlockMode }, 
    { "fioSync", fioSync }, 
    { "fioWrite", fioWrite }, 
    { "FlushCache", FlushCache }, 
    { "ForTimer_InitAlarm", ForTimer_InitAlarm }, 
    { "FreeTimerCounter", FreeTimerCounter }, 
    { "g_AlarmBuf", g_AlarmBuf }, 
    { "g_CounterBuf", g_CounterBuf }, 
    { "GetCop0", GetCop0 }, 
    { "GetEntryAddress", GetEntryAddress }, 
    { "GetExceptionHandler", GetExceptionHandler }, 
    { "GetGP", GetGP }, 
    { "_GetGsDxDyOffset", _GetGsDxDyOffset }, 
    { "GetGsHParam", GetGsHParam }, 
    { "GetGsVParam", GetGsVParam }, 
    { "GetInterruptHandler", GetInterruptHandler }, 
    { "GetMemoryMode", GetMemoryMode }, 
    { "GetMemorySize", GetMemorySize }, 
    { "GetOsdConfigParam", GetOsdConfigParam }, 
    { "GetOsdConfigParam2", GetOsdConfigParam2 }, 
    { "GetRomName", GetRomName }, 
    { "GetRomNameWithIODriver", GetRomNameWithIODriver }, 
    { "GetSyscall", GetSyscall }, 
    { "GetSyscallHandler", GetSyscallHandler }, 
    { "GetThreadId", GetThreadId }, 
    { "GetTimerBaseTime", GetTimerBaseTime }, 
    { "GetTimerCount", GetTimerCount }, 
    { "GetTimerPreScaleFactor", GetTimerPreScaleFactor }, 
    { "GetTimerSystemTime", GetTimerSystemTime }, 
    { "GetTimerUsedUnusedCounters", GetTimerUsedUnusedCounters }, 
    { "GetTLBEntry", GetTLBEntry }, 
    { "g_pFreeAlarm", g_pFreeAlarm }, 
    { "g_RomName", g_RomName }, 
    { "GsGetIMR", GsGetIMR }, 
    { "GsPutIMR", GsPutIMR }, 
    { "g_t10KConfig", g_t10KConfig }, 
    { "g_Timer", g_Timer }, 
    { "iAllocTimerCounter", iAllocTimerCounter }, 
    { "iCancelWakeupThread", iCancelWakeupThread }, 
    { "iChangeThreadPriority", iChangeThreadPriority }, 
    { "iCpuConfig", iCpuConfig }, 
    { "iDeleteSema", iDeleteSema }, 
    { "_iDisableDmac", _iDisableDmac }, 
    { "iDisableDmac", iDisableDmac }, 
    { "iDisableDmacHandler", iDisableDmacHandler }, 
    { "_iDisableIntc", _iDisableIntc }, 
    { "iDisableIntc", iDisableIntc }, 
    { "iDisableIntcHandler", iDisableIntcHandler }, 
    { "_iEnableDmac", _iEnableDmac }, 
    { "iEnableDmac", iEnableDmac }, 
    { "iEnableDmacHandler", iEnableDmacHandler }, 
    { "_iEnableIntc", _iEnableIntc }, 
    { "iEnableIntc", iEnableIntc }, 
    { "iEnableIntcHandler", iEnableIntcHandler }, 
    { "iFlushCache", iFlushCache }, 
    { "iFreeTimerCounter", iFreeTimerCounter }, 
    { "iGetCop0", iGetCop0 }, 
    { "_iGetThreadId", _iGetThreadId }, 
    { "iGetTimerBaseTime", iGetTimerBaseTime }, 
    { "iGetTimerCount", iGetTimerCount }, 
    { "iGetTimerSystemTime", iGetTimerSystemTime }, 
    { "iGetTimerUsedUnusedCounters", iGetTimerUsedUnusedCounters }, 
    { "iGetTLBEntry", iGetTLBEntry }, 
    { "iGsGetIMR", iGsGetIMR }, 
    { "iGsPutIMR", iGsPutIMR }, 
    { "_ih_caps", _ih_caps }, 
    { "_ih_cd", _ih_cd }, 
    { "iInvalidDCache", iInvalidDCache }, 
    { "InitAlarm", InitAlarm }, 
    { "InitDebug", InitDebug }, 
    { "InitExecPS2", InitExecPS2 }, 
    { "InitOsd", InitOsd }, 
    { "_InitSys", _InitSys }, 
    { "InitThread", InitThread }, 
    { "InitTimer", InitTimer }, 
    { "_InitTLB", _InitTLB }, 
    { "InitTLB", InitTLB }, 
    { "InitTLBFunctions", InitTLBFunctions }, 
    { "InsertAlarm_ForTimer", InsertAlarm_ForTimer }, 
    { "Interrupt2Iop", Interrupt2Iop }, 
    { "_InvalidDCache", _InvalidDCache }, 
    { "InvalidDCache", InvalidDCache }, 
    { "_iop_reboot_count", _iop_reboot_count }, 
    { "iPollSema", iPollSema }, 
    { "iProbeTLBEntry", iProbeTLBEntry }, 
    { "iPutTLBEntry", iPutTLBEntry }, 
    { "iReferSemaStatus", iReferSemaStatus }, 
    { "iReferThreadStatus", iReferThreadStatus }, 
    { "_iReleaseAlarm", _iReleaseAlarm }, 
    { "iReleaseAlarm", iReleaseAlarm }, 
    { "iReleaseTimerAlarm", iReleaseTimerAlarm }, 
    { "iReleaseWaitThread", iReleaseWaitThread }, 
    { "iResumeThread", iResumeThread }, 
    { "_iRotateThreadReadyQueue", _iRotateThreadReadyQueue }, 
    { "iRotateThreadReadyQueue", iRotateThreadReadyQueue }, 
    { "isceSifDmaStat", isceSifDmaStat }, 
    { "isceSifSendCmd", isceSifSendCmd }, 
    { "isceSifSetDChain", isceSifSetDChain }, 
    { "isceSifSetDma", isceSifSetDma }, 
    { "IsDESRMachine", IsDESRMachine }, 
    { "IsDESRMachineWithIODriver", IsDESRMachineWithIODriver }, 
    { "IsEarlyJap", IsEarlyJap }, 
    { "_iSetAlarm", _iSetAlarm }, 
    { "iSetAlarm", iSetAlarm }, 
    { "iSetEventFlag", iSetEventFlag }, 
    { "iSetTimerAlarm", iSetTimerAlarm }, 
    { "iSetTimerHandler", iSetTimerHandler }, 
    { "iSetTLBEntry", iSetTLBEntry }, 
    { "iSignalSema", iSignalSema }, 
    { "IsT10K", IsT10K }, 
    { "IsT10KWithIODriver", IsT10KWithIODriver }, 
    { "iStartTimerCounter", iStartTimerCounter }, 
    { "iStopTimerCounter", iStopTimerCounter }, 
    { "_iSuspendThread", _iSuspendThread }, 
    { "iSuspendThread", iSuspendThread }, 
    { "iSyncDCache", iSyncDCache }, 
    { "iTerminateThread", iTerminateThread }, 
    { "_iWakeupThread", _iWakeupThread }, 
    { "iWakeupThread", iWakeupThread }, 
    { "kCopy", kCopy }, 
    { "kCopyBytes", kCopyBytes }, 
    { "_kExecArg", _kExecArg }, 
    { "KExit", KExit }, 
    { "kputs", kputs }, 
    { "KSeg0", KSeg0 }, 
    { "_lf_cd", _lf_cd }, 
    { "_lf_init", _lf_init }, 
    { "_LoadExecPS2", _LoadExecPS2 }, 
    { "LoadExecPS2", LoadExecPS2 }, 
    { "MachineType", MachineType },
    { "osdsrc", osdsrc }, 
    { "PatchIsNeeded", PatchIsNeeded }, 
    { "PollSema", PollSema }, 
    { "_print", _print }, 
    { "ProbeTLBEntry", ProbeTLBEntry }, 
    { "_ps2sdk_deinit_timer", _ps2sdk_deinit_timer }, 
    { "_ps2sdk_deinit_timer_impl", _ps2sdk_deinit_timer_impl }, 
    { "_ps2sdk_init_timer", _ps2sdk_init_timer }, 
    { "_ps2sdk_init_timer_impl", _ps2sdk_init_timer_impl }, 
    { "PSMode", PSMode }, 
    { "PutTLBEntry", PutTLBEntry }, 
    { "ReferSemaStatus", ReferSemaStatus }, 
    { "ReferThreadStatus", ReferThreadStatus }, 
    { "_ReleaseAlarm", _ReleaseAlarm }, 
    { "ReleaseAlarm", ReleaseAlarm }, 
    { "ReleaseTimerAlarm", ReleaseTimerAlarm }, 
    { "ReleaseWaitThread", ReleaseWaitThread }, 
    { "RemoveDmacHandler", RemoveDmacHandler }, 
    { "RemoveIntcHandler", RemoveIntcHandler }, 
    { "RemoveSbusIntcHandler", RemoveSbusIntcHandler }, 
    { "ResetEE", ResetEE }, 
    { "ResumeThread", ResumeThread }, 
    { "RFU009", RFU009 }, 
    { "RFU059", RFU059 }, 
    { "RFU060", RFU060 }, 
    { "RFU061", RFU061 }, 
    { "RFU105", RFU105 }, 
    { "RotateThreadReadyQueue", RotateThreadReadyQueue }, 
    { "_rpc_get_fpacket", _rpc_get_fpacket }, 
    { "_rpc_get_packet", _rpc_get_packet }, 
    { "sceDeci2Close", sceDeci2Close }, 
    { "sceDeci2ExLock", sceDeci2ExLock }, 
    { "sceDeci2ExRecv", sceDeci2ExRecv }, 
    { "sceDeci2ExReqSend", sceDeci2ExReqSend }, 
    { "sceDeci2ExSend", sceDeci2ExSend }, 
    { "sceDeci2ExUnLock", sceDeci2ExUnLock }, 
    { "sceDeci2Open", sceDeci2Open }, 
    { "sceDeci2Poll", sceDeci2Poll }, 
    { "sceDeci2ReqSend", sceDeci2ReqSend }, 
    { "sceSifAddCmdHandler", sceSifAddCmdHandler }, 
    { "sceSifBindRpc", sceSifBindRpc }, 
    { "sceSifCallRpc", sceSifCallRpc }, 
    { "sceSifCheckStatRpc", sceSifCheckStatRpc }, 
    { "sceSifDmaStat", sceSifDmaStat }, 
    { "sceSifExecRequest", sceSifExecRequest }, 
    { "sceSifExitCmd", sceSifExitCmd }, 
    { "sceSifExitRpc", sceSifExitRpc }, 
    { "sceSifGetNextRequest", sceSifGetNextRequest }, 
    { "sceSifGetOtherData", sceSifGetOtherData }, 
    { "sceSifGetReg", sceSifGetReg }, 
    { "sceSifGetSreg", sceSifGetSreg }, 
    { "sceSifInitCmd", sceSifInitCmd }, 
    { "sceSifInitRpc", sceSifInitRpc }, 
    { "sceSifRegisterRpc", sceSifRegisterRpc }, 
    { "sceSifRemoveCmdHandler", sceSifRemoveCmdHandler }, 
    { "sceSifRemoveRpc", sceSifRemoveRpc }, 
    { "sceSifRemoveRpcQueue", sceSifRemoveRpcQueue }, 
    { "sceSifRpcLoop", sceSifRpcLoop }, 
    { "sceSifSendCmd", sceSifSendCmd }, 
    { "sceSifSetCmdBuffer", sceSifSetCmdBuffer }, 
    { "sceSifSetDChain", sceSifSetDChain }, 
    { "sceSifSetDma", sceSifSetDma }, 
    { "sceSifSetReg", sceSifSetReg }, 
    { "sceSifSetRpcQueue", sceSifSetRpcQueue }, 
    { "sceSifSetSreg", sceSifSetSreg }, 
    { "sceSifSetSysCmdBuffer", sceSifSetSysCmdBuffer }, 
    { "sceSifStopDma", sceSifStopDma }, 
    { "sceSifWriteBackDCache", sceSifWriteBackDCache }, 
    { "sceTtyHandler", sceTtyHandler }, 
    { "sceTtyInit", sceTtyInit }, 
    { "sceTtyRead", sceTtyRead }, 
    { "sceTtyWrite", sceTtyWrite }, 
    { "_SetAlarm", _SetAlarm }, 
    { "SetAlarm", SetAlarm }, 
    { "SetArg", SetArg }, 
    { "SetCPUTimer", SetCPUTimer }, 
    { "SetCPUTimerHandler", SetCPUTimerHandler }, 
    { "SetEventFlag", SetEventFlag }, 
    { "SetGP", SetGP }, 
    { "SetGsCrt", SetGsCrt }, 
    { "SetGsHParam", SetGsHParam }, 
    { "SetGsVParam", SetGsVParam }, 
    { "SetMemoryMode", SetMemoryMode }, 
    { "SetNextComp", SetNextComp }, 
    { "SetOsdConfigParam", SetOsdConfigParam }, 
    { "SetOsdConfigParam2", SetOsdConfigParam2 }, 
    { "SetPgifHandler", SetPgifHandler }, 
    { "SetSyscall", SetSyscall }, 
    { "SetT2", SetT2 }, 
    { "SetT2_COMP", SetT2_COMP }, 
    { "SetT2_COUNT", SetT2_COUNT }, 
    { "SetT2_MODE", SetT2_MODE }, 
    { "SetTimerAlarm", SetTimerAlarm }, 
    { "SetTimerCount", SetTimerCount }, 
    { "SetTimerHandler", SetTimerHandler }, 
    { "_SetTLBEntry", _SetTLBEntry }, 
    { "setup", setup }, 
    { "SetupHeap", SetupHeap }, 
    { "SetupThread", SetupThread }, 
    { "SetVCommonHandler", SetVCommonHandler }, 
    { "SetVInterruptHandler", SetVInterruptHandler }, 
    { "SetVSyncFlag", SetVSyncFlag }, 
    { "SetVTLBRefillHandler", SetVTLBRefillHandler }, 
    { "SifAllocIopHeap", SifAllocIopHeap }, 
    { "_sif_cmd_data", _sif_cmd_data }, 
    { "_SifCmdIntHandler", _SifCmdIntHandler }, 
    { "SifExecModuleBuffer", SifExecModuleBuffer }, 
    { "SifExecModuleFile", SifExecModuleFile }, 
    { "SifExitIopHeap", SifExitIopHeap }, 
    { "SifFreeIopHeap", SifFreeIopHeap }, 
    { "SifInitIopHeap", SifInitIopHeap }, 
    { "SifIopGetVal", SifIopGetVal }, 
    { "SifIopIsAlive", SifIopIsAlive }, 
    { "SifIopReboot", SifIopReboot }, 
    { "SifIopReset", SifIopReset }, 
    { "SifIopSetVal", SifIopSetVal }, 
    { "SifIopSync", SifIopSync }, 
    { "SifLoadElf", SifLoadElf }, 
    { "SifLoadElfEncrypted", SifLoadElfEncrypted }, 
    { "_SifLoadElfPart", _SifLoadElfPart }, 
    { "SifLoadElfPart", SifLoadElfPart }, 
    { "SifLoadFileExit", SifLoadFileExit }, 
    { "SifLoadFileInit", SifLoadFileInit }, 
    { "SifLoadIopHeap", SifLoadIopHeap }, 
    { "_SifLoadModule", _SifLoadModule }, 
    { "SifLoadModule", SifLoadModule }, 
    { "_SifLoadModuleBuffer", _SifLoadModuleBuffer }, 
    { "SifLoadModuleBuffer", SifLoadModuleBuffer }, 
    { "SifLoadModuleEncrypted", SifLoadModuleEncrypted }, 
    { "SifLoadStartModule", SifLoadStartModule }, 
    { "SifLoadStartModuleBuffer", SifLoadStartModuleBuffer }, 
    { "_sif_rpc_data", _sif_rpc_data }, 
    { "SifSearchModuleByAddress", SifSearchModuleByAddress }, 
    { "SifSearchModuleByName", SifSearchModuleByName }, 
    { "_SifSendCmd", _SifSendCmd }, 
    { "SifStopModule", SifStopModule }, 
    { "SifUnloadModule", SifUnloadModule }, 
    { "SignalSema", SignalSema }, 
    { "sio_flush", sio_flush }, 
    { "sio_getc", sio_getc }, 
    { "sio_getc_block", sio_getc_block }, 
    { "sio_gets", sio_gets }, 
    { "sio_init", sio_init }, 
    { "sio_putc", sio_putc }, 
    { "sio_puts", sio_puts }, 
    { "sio_putsn", sio_putsn }, 
    { "sio_read", sio_read }, 
    { "sio_write", sio_write }, 
    { "size_eenull", size_eenull }, 
    { "size_osdsrc", size_osdsrc }, 
    { "size_srcfile", size_srcfile }, 
    { "size_tlbsrc", size_tlbsrc }, 
    { "SleepThread", SleepThread }, 
    { "srcfile", srcfile }, 
    { "stack", stack }, 
    { "StartThread", StartThread }, 
    { "StartTimerCounter", StartTimerCounter }, 
    { "StartTimerSystemTime", StartTimerSystemTime }, 
    { "StopTimerCounter", StopTimerCounter }, 
    { "StopTimerSystemTime", StopTimerSystemTime }, 
    { "SuspendThread", SuspendThread }, 
    { "_SyncDCache", _SyncDCache }, 
    { "SyncDCache", SyncDCache }, 
    { "__syscall", __syscall }, 
    { "SysEntry", SysEntry }, 
    { "TerminateLibrary", TerminateLibrary }, 
    { "TerminateThread", TerminateThread }, 
    { "TimerBusClock2Freq", TimerBusClock2Freq }, 
    { "TimerBusClock2USec", TimerBusClock2USec }, 
    { "TimerFreq2BusClock", TimerFreq2BusClock }, 
    { "TimerHandler_callback", TimerHandler_callback }, 
    { "TimerUSec2BusClock", TimerUSec2BusClock }, 
    { "tinfo", tinfo }, 
    { "tlbsrc", tlbsrc }, 
    { "topArg", topArg }, 
    { "topId", topId }, 
    { "topSema", topSema }, 
    { "ttyinit", ttyinit }, 
    { "UnlinkAlarm_ForTimer", UnlinkAlarm_ForTimer }, 
    { "WaitSema", WaitSema }, 
    { "WaitSemaEx", WaitSemaEx }, 
    { 0, 0},
};
