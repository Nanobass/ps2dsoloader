extern void bindDiskReady();
extern void bindInit();
extern void bindNCmd();
extern void bindSCmd();
extern void bindSearchFile();
extern void callbackSemaId();
extern void callbackThreadId();
extern void callbackThreadParam();
extern void cbSema();
extern void _CdAlignReadBuffer();
extern void CdCallbackNum();
extern void _CdCheckNCmd();
extern void _CdCheckSCmd();
extern void CdConfigRdWrNumBlocks();
extern void cdda_st_buf();
extern void CdDebug();
extern void _CdGenericCallbackFunction();
extern void _CdSemaExit();
extern void _CdSemaInit();
extern void _CdSyncS();
extern void CdThreadId();
extern void CdThreadParam();
extern void clientDiskReady();
extern void clientInit();
extern void clientNCmd();
extern void clientSCmd();
extern void clientSearchFile();
extern void curReadPos();
extern void diskReadyMode();
extern void dummyMode();
extern void erl_dependancies();
extern void erl_id();
extern void getTocSendBuff();
extern void initMode();
extern void nCmdNum();
extern void nCmdRecvBuff();
extern void nCmdSemaId();
extern void nCmdSendBuff();
extern void ps2time();
extern void _rd_intr_data();
extern void readChainData();
extern void readData();
extern void readStreamData();
extern void sceCdApplyNCmd();
extern void sceCdApplySCmd();
extern void sceCdAutoAdjustCtrl();
extern void sceCdBreak();
extern void sceCdCallback();
extern void sceCdCallbackFunc();
extern void sceCdCddaStream();
extern void sceCdCloseConfig();
extern void sceCdCtrlADout();
extern void sceCdDecSet();
extern void sceCdDiskReady();
extern void sceCdForbidDVDP();
extern void sceCdGetDiskType();
extern void sceCdGetError();
extern void sceCdGetReadPos();
extern void sceCdGetToc();
extern void sceCdInit();
extern void sceCdInitEeCB();
extern void sceCdIntToPos();
extern void sceCdMV();
extern void sceCdNCmdDiskReady();
extern void sceCdNoticeGameStart();
extern void sceCdOpenConfig();
extern void sceCdPause();
extern void sceCdPosToInt();
extern void sceCdRead();
extern void sceCdReadCDDA();
extern void sceCdReadClock();
extern void sceCdReadConfig();
extern void sceCdReadConsoleID();
extern void sceCdReadDVDV();
extern void sceCdReadIOPMem();
extern void sceCdReadKey();
extern void sceCdReadNVM();
extern void sceCdReadSUBQ();
extern void sceCdRI();
extern void sceCdSearchFile();
extern void sceCdSeek();
extern void sceCdSetHDMode();
extern void sceCdStandby();
extern void sceCdStatus();
extern void sceCdStInit();
extern void sceCdStop();
extern void sceCdStPause();
extern void sceCdStRead();
extern void sceCdStream();
extern void sceCdStResume();
extern void sceCdStSeek();
extern void sceCdStStart();
extern void sceCdStStat();
extern void sceCdStStop();
extern void sceCdSync();
extern void sceCdTrayReq();
extern void sceCdWI();
extern void sceCdWriteClock();
extern void sceCdWriteConfig();
extern void sceCdWriteConsoleID();
extern void sceCdWriteNVM();
extern void sCmdNum();
extern void sCmdRecvBuff();
extern void sCmdSemaId();
extern void sCmdSendBuff();
extern void searchFileRecvBuff();
extern void searchFileSendBuff();
extern void seekSector();
extern void streamStatus();
extern void tocBuff();
struct export_list_t {
    char * name;
    void * pointer;
} libcdvd_exports[] = {
    { "bindDiskReady", bindDiskReady }, 
    { "bindInit", bindInit }, 
    { "bindNCmd", bindNCmd }, 
    { "bindSCmd", bindSCmd }, 
    { "bindSearchFile", bindSearchFile }, 
    { "callbackSemaId", callbackSemaId }, 
    { "callbackThreadId", callbackThreadId }, 
    { "callbackThreadParam", callbackThreadParam }, 
    { "cbSema", cbSema }, 
    { "_CdAlignReadBuffer", _CdAlignReadBuffer }, 
    { "CdCallbackNum", CdCallbackNum }, 
    { "_CdCheckNCmd", _CdCheckNCmd }, 
    { "_CdCheckSCmd", _CdCheckSCmd }, 
    { "CdConfigRdWrNumBlocks", CdConfigRdWrNumBlocks }, 
    { "cdda_st_buf", cdda_st_buf }, 
    { "CdDebug", CdDebug }, 
    { "_CdGenericCallbackFunction", _CdGenericCallbackFunction }, 
    { "_CdSemaExit", _CdSemaExit }, 
    { "_CdSemaInit", _CdSemaInit }, 
    { "_CdSyncS", _CdSyncS }, 
    { "CdThreadId", CdThreadId }, 
    { "CdThreadParam", CdThreadParam }, 
    { "clientDiskReady", clientDiskReady }, 
    { "clientInit", clientInit }, 
    { "clientNCmd", clientNCmd }, 
    { "clientSCmd", clientSCmd }, 
    { "clientSearchFile", clientSearchFile }, 
    { "curReadPos", curReadPos }, 
    { "diskReadyMode", diskReadyMode }, 
    { "dummyMode", dummyMode }, 
    { "erl_dependancies", erl_dependancies }, 
    { "erl_id", erl_id }, 
    { "getTocSendBuff", getTocSendBuff }, 
    { "initMode", initMode }, 
    { "nCmdNum", nCmdNum }, 
    { "nCmdRecvBuff", nCmdRecvBuff }, 
    { "nCmdSemaId", nCmdSemaId }, 
    { "nCmdSendBuff", nCmdSendBuff }, 
    { "ps2time", ps2time }, 
    { "_rd_intr_data", _rd_intr_data }, 
    { "readChainData", readChainData }, 
    { "readData", readData }, 
    { "readStreamData", readStreamData }, 
    { "sceCdApplyNCmd", sceCdApplyNCmd }, 
    { "sceCdApplySCmd", sceCdApplySCmd }, 
    { "sceCdAutoAdjustCtrl", sceCdAutoAdjustCtrl }, 
    { "sceCdBreak", sceCdBreak }, 
    { "sceCdCallback", sceCdCallback }, 
    { "sceCdCallbackFunc", sceCdCallbackFunc }, 
    { "sceCdCddaStream", sceCdCddaStream }, 
    { "sceCdCloseConfig", sceCdCloseConfig }, 
    { "sceCdCtrlADout", sceCdCtrlADout }, 
    { "sceCdDecSet", sceCdDecSet }, 
    { "sceCdDiskReady", sceCdDiskReady }, 
    { "sceCdForbidDVDP", sceCdForbidDVDP }, 
    { "sceCdGetDiskType", sceCdGetDiskType }, 
    { "sceCdGetError", sceCdGetError }, 
    { "sceCdGetReadPos", sceCdGetReadPos }, 
    { "sceCdGetToc", sceCdGetToc }, 
    { "sceCdInit", sceCdInit }, 
    { "sceCdInitEeCB", sceCdInitEeCB }, 
    { "sceCdIntToPos", sceCdIntToPos }, 
    { "sceCdMV", sceCdMV }, 
    { "sceCdNCmdDiskReady", sceCdNCmdDiskReady }, 
    { "sceCdNoticeGameStart", sceCdNoticeGameStart }, 
    { "sceCdOpenConfig", sceCdOpenConfig }, 
    { "sceCdPause", sceCdPause }, 
    { "sceCdPosToInt", sceCdPosToInt }, 
    { "sceCdRead", sceCdRead }, 
    { "sceCdReadCDDA", sceCdReadCDDA }, 
    { "sceCdReadClock", sceCdReadClock }, 
    { "sceCdReadConfig", sceCdReadConfig }, 
    { "sceCdReadConsoleID", sceCdReadConsoleID }, 
    { "sceCdReadDVDV", sceCdReadDVDV }, 
    { "sceCdReadIOPMem", sceCdReadIOPMem }, 
    { "sceCdReadKey", sceCdReadKey }, 
    { "sceCdReadNVM", sceCdReadNVM }, 
    { "sceCdReadSUBQ", sceCdReadSUBQ }, 
    { "sceCdRI", sceCdRI }, 
    { "sceCdSearchFile", sceCdSearchFile }, 
    { "sceCdSeek", sceCdSeek }, 
    { "sceCdSetHDMode", sceCdSetHDMode }, 
    { "sceCdStandby", sceCdStandby }, 
    { "sceCdStatus", sceCdStatus }, 
    { "sceCdStInit", sceCdStInit }, 
    { "sceCdStop", sceCdStop }, 
    { "sceCdStPause", sceCdStPause }, 
    { "sceCdStRead", sceCdStRead }, 
    { "sceCdStream", sceCdStream }, 
    { "sceCdStResume", sceCdStResume }, 
    { "sceCdStSeek", sceCdStSeek }, 
    { "sceCdStStart", sceCdStStart }, 
    { "sceCdStStat", sceCdStStat }, 
    { "sceCdStStop", sceCdStStop }, 
    { "sceCdSync", sceCdSync }, 
    { "sceCdTrayReq", sceCdTrayReq }, 
    { "sceCdWI", sceCdWI }, 
    { "sceCdWriteClock", sceCdWriteClock }, 
    { "sceCdWriteConfig", sceCdWriteConfig }, 
    { "sceCdWriteConsoleID", sceCdWriteConsoleID }, 
    { "sceCdWriteNVM", sceCdWriteNVM }, 
    { "sCmdNum", sCmdNum }, 
    { "sCmdRecvBuff", sCmdRecvBuff }, 
    { "sCmdSemaId", sCmdSemaId }, 
    { "sCmdSendBuff", sCmdSendBuff }, 
    { "searchFileRecvBuff", searchFileRecvBuff }, 
    { "searchFileSendBuff", searchFileSendBuff }, 
    { "seekSector", seekSector }, 
    { "streamStatus", streamStatus }, 
    { "tocBuff", tocBuff }, 
    { 0, 0},
};
