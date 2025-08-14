extern void accept();
extern void access();
extern void bind();
extern void chdir();
extern void chmod();
extern void _chown();
extern void chown();
extern void clock_getres();
extern void clock_gettime();
extern void clock_settime();
extern void _close();
extern void compile_time_check();
extern void connect();
extern void __cwd();
extern void __cwd_len();
extern void __descriptor_data_pool();
extern void __descriptormap();
extern void __dummy_group();
extern void __dummy_passwd();
extern void __dummy_passwd_loginbuf();
extern void dup();
extern void dup2();
extern void _execve();
extern void faccessat();
extern void fchdir();
extern void fchmod();
extern void fchmodat();
extern void fchown();
extern void fchownat();
extern void _fcntl();
extern void __fdman_deinit();
extern void __fdman_get_dup2_descriptor();
extern void __fdman_get_dup_descriptor();
extern void __fdman_get_new_descriptor();
extern void __fdman_init();
extern void __fdman_release_descriptor();
extern void __fdman_sema();
extern void __fioCloseHelper();
extern void __fioDcloseHelper();
extern void __fioDreadHelper();
extern void __fio_fdman_ops_dir();
extern void __fio_fdman_ops_file();
extern void __fio_fdman_path_ops();
extern void __fioGetFdHelper();
extern void __fioGetFilenameHelper();
extern void __fioGetstatHelper();
extern void __fioIoctlHelper();
extern void __fioLseekDirHelper();
extern void __fioLseekHelper();
extern void __fioMkdirHelper();
extern void __fioOpenHelper();
extern void __fioOpsInitializeImpl();
extern void __fioReadHelper();
extern void __fioWriteHelper();
extern void _fork();
extern void fpathconf();
extern void freeaddrinfo();
extern void _fstat();
extern void fstatat();
extern void fsync();
extern void ftime();
extern void ftruncate();
extern void getaddrinfo();
extern void getcwd();
extern void getdents();
extern void __get_drive();
extern void getegid();
extern void _getentropy();
extern void geteuid();
extern void getgid();
extern void getgrgid();
extern void getgrnam();
extern void gethostbyaddr();
extern void gethostbyname();
extern void gethostbyname_r();
extern void getitimer();
extern void getlogin();
extern void getpeername();
extern void _getpid();
extern void getppid();
extern void getpwnam();
extern void getpwuid();
extern void getrandom();
extern void getsockname();
extern void getsockopt();
extern void _gettimeofday();
extern void getuid();
extern void __gprof_cleanup();
extern void __gprof_init();
extern void __init_cwd();
extern void _ioctl();
extern void issetugid();
extern void isSpecialASCII();
extern void isSpecialSJIS();
extern void _kill();
extern void _libcglue_args_parse();
extern void _libcglue_deinit();
extern void libcglue_dns_getserver();
extern void libcglue_dns_setserver();
extern void _libcglue_fdman_inet_ops();
extern void _libcglue_fdman_path_ops();
extern void _libcglue_fdman_socket_ops();
extern void libcglue_get_fd_info();
extern void libcglue_inet_addr();
extern void libcglue_inet_aton();
extern void libcglue_inet_ntoa();
extern void libcglue_inet_ntoa_r();
extern void _libcglue_init();
extern void __libcglue_init_stdio();
extern void libcglue_ps2ip_getconfig();
extern void libcglue_ps2ip_setconfig();
extern void _libcglue_rtc_get_offset_from_busclk();
extern void _libcglue_rtc_update();
extern void _libcglue_rtc_update_impl();
extern void _libcglue_timezone_update();
extern void _libcglue_timezone_update_impl();
extern void __libpthreadglue_deinit();
extern void __libpthreadglue_init();
extern void _link();
extern void linkat();
extern void listen();
extern void __lock___arc4random_mutex();
extern void __lock___atexit_recursive_mutex();
extern void __lock___at_quick_exit_mutex();
extern void __lock___dd_hash_mutex();
extern void __lock___env_recursive_mutex();
extern void __lock___malloc_recursive_mutex();
extern void __locks_deinit();
extern void __lock___sfp_recursive_mutex();
extern void __locks_init();
extern void __lock___tz_mutex();
extern void _lseek();
extern void lseek64();
extern void lstat();
extern void _mkdir();
extern void mkdir();
extern void mkdirat();
extern void nanosleep();
extern void _open();
extern void openat();
extern void __path_absolute();
extern void pathconf();
extern void pause();
extern void pipe();
extern void _ps2sdk_close();
extern void _ps2sdk_dclose();
extern void _ps2sdk_dread();
extern void ps2sdk_get_iop_fd();
extern void ps2sdk_get_iop_filename();
extern void _ps2sdk_ioctl();
extern void _ps2sdk_ioctl2();
extern void _ps2sdk_lseek();
extern void _ps2sdk_lseek64();
extern void _ps2sdk_read();
extern void _ps2sdk_rtc_offset_from_busclk();
extern void ps2sdk_setDaylightSaving();
extern void ps2sdk_setTimezone();
extern void _ps2sdk_write();
extern void _read();
extern void _readlink();
extern void readlink();
extern void readlinkat();
extern void readv();
extern void recv();
extern void recvfrom();
extern void recvmsg();
extern void _rename();
extern void renameat();
extern void __retarget_lock_acquire();
extern void __retarget_lock_acquire_recursive();
extern void __retarget_lock_close();
extern void __retarget_lock_close_recursive();
extern void __retarget_lock_init();
extern void __retarget_lock_init_recursive();
extern void __retarget_lock_release();
extern void __retarget_lock_release_recursive();
extern void __retarget_lock_try_acquire();
extern void __retarget_lock_try_acquire_recursive();
extern void rmdir();
extern void _sbrk();
extern void sched_yield();
extern void select();
extern void send();
extern void sendmsg();
extern void sendto();
extern void setitimer();
extern void setsockopt();
extern void shutdown();
extern void sigaction();
extern void sigprocmask();
extern void socket();
extern void _stat();
extern void strcpy_ascii();
extern void strcpy_sjis();
extern void _symlink();
extern void symlink();
extern void sysconf();
extern void _system();
extern void tcgetattr();
extern void tcsetattr();
extern void _times();
extern void __transform64_errno();
extern void __transform_errno();
extern void truncate();
extern void umask();
extern void _unlink();
extern void unlinkat();
extern void utime();
extern void utimes();
extern void vfork();
extern void _wait();
extern void waitpid();
extern void _write();
struct export_list_t {
    char * name;
    void * pointer;
} libcglue_exports[] = {
    { "accept", accept }, 
    { "access", access }, 
    { "bind", bind }, 
    { "chdir", chdir }, 
    { "chmod", chmod }, 
    { "_chown", _chown }, 
    { "chown", chown }, 
    { "clock_getres", clock_getres }, 
    { "clock_gettime", clock_gettime }, 
    { "clock_settime", clock_settime }, 
    { "_close", _close }, 
    { "compile_time_check", compile_time_check }, 
    { "connect", connect }, 
    { "__cwd", __cwd }, 
    { "__cwd_len", __cwd_len }, 
    { "__descriptor_data_pool", __descriptor_data_pool }, 
    { "__descriptormap", __descriptormap }, 
    { "__dummy_group", __dummy_group }, 
    { "__dummy_passwd", __dummy_passwd }, 
    { "__dummy_passwd_loginbuf", __dummy_passwd_loginbuf }, 
    { "dup", dup }, 
    { "dup2", dup2 }, 
    { "_execve", _execve }, 
    { "faccessat", faccessat }, 
    { "fchdir", fchdir }, 
    { "fchmod", fchmod }, 
    { "fchmodat", fchmodat }, 
    { "fchown", fchown }, 
    { "fchownat", fchownat }, 
    { "_fcntl", _fcntl }, 
    { "__fdman_deinit", __fdman_deinit }, 
    { "__fdman_get_dup2_descriptor", __fdman_get_dup2_descriptor }, 
    { "__fdman_get_dup_descriptor", __fdman_get_dup_descriptor }, 
    { "__fdman_get_new_descriptor", __fdman_get_new_descriptor }, 
    { "__fdman_init", __fdman_init }, 
    { "__fdman_release_descriptor", __fdman_release_descriptor }, 
    { "__fdman_sema", __fdman_sema }, 
    { "__fioCloseHelper", __fioCloseHelper }, 
    { "__fioDcloseHelper", __fioDcloseHelper }, 
    { "__fioDreadHelper", __fioDreadHelper }, 
    { "__fio_fdman_ops_dir", __fio_fdman_ops_dir }, 
    { "__fio_fdman_ops_file", __fio_fdman_ops_file }, 
    { "__fio_fdman_path_ops", __fio_fdman_path_ops }, 
    { "__fioGetFdHelper", __fioGetFdHelper }, 
    { "__fioGetFilenameHelper", __fioGetFilenameHelper }, 
    { "__fioGetstatHelper", __fioGetstatHelper }, 
    { "__fioIoctlHelper", __fioIoctlHelper }, 
    { "__fioLseekDirHelper", __fioLseekDirHelper }, 
    { "__fioLseekHelper", __fioLseekHelper }, 
    { "__fioMkdirHelper", __fioMkdirHelper }, 
    { "__fioOpenHelper", __fioOpenHelper }, 
    { "__fioOpsInitializeImpl", __fioOpsInitializeImpl }, 
    { "__fioReadHelper", __fioReadHelper }, 
    { "__fioWriteHelper", __fioWriteHelper }, 
    { "_fork", _fork }, 
    { "fpathconf", fpathconf }, 
    { "freeaddrinfo", freeaddrinfo }, 
    { "_fstat", _fstat }, 
    { "fstatat", fstatat }, 
    { "fsync", fsync }, 
    { "ftime", ftime }, 
    { "ftruncate", ftruncate }, 
    { "getaddrinfo", getaddrinfo }, 
    { "getcwd", getcwd }, 
    { "getdents", getdents }, 
    { "__get_drive", __get_drive }, 
    { "getegid", getegid }, 
    { "_getentropy", _getentropy }, 
    { "geteuid", geteuid }, 
    { "getgid", getgid }, 
    { "getgrgid", getgrgid }, 
    { "getgrnam", getgrnam }, 
    { "gethostbyaddr", gethostbyaddr }, 
    { "gethostbyname", gethostbyname }, 
    { "gethostbyname_r", gethostbyname_r }, 
    { "getitimer", getitimer }, 
    { "getlogin", getlogin }, 
    { "getpeername", getpeername }, 
    { "_getpid", _getpid }, 
    { "getppid", getppid }, 
    { "getpwnam", getpwnam }, 
    { "getpwuid", getpwuid }, 
    { "getrandom", getrandom }, 
    { "getsockname", getsockname }, 
    { "getsockopt", getsockopt }, 
    { "_gettimeofday", _gettimeofday }, 
    { "getuid", getuid }, 
    { "__gprof_cleanup", __gprof_cleanup }, 
    { "__gprof_init", __gprof_init }, 
    { "__init_cwd", __init_cwd }, 
    { "_ioctl", _ioctl }, 
    { "issetugid", issetugid }, 
    { "isSpecialASCII", isSpecialASCII }, 
    { "isSpecialSJIS", isSpecialSJIS }, 
    { "_kill", _kill }, 
    { "_libcglue_args_parse", _libcglue_args_parse }, 
    { "_libcglue_deinit", _libcglue_deinit }, 
    { "libcglue_dns_getserver", libcglue_dns_getserver }, 
    { "libcglue_dns_setserver", libcglue_dns_setserver }, 
    { "_libcglue_fdman_inet_ops", _libcglue_fdman_inet_ops }, 
    { "_libcglue_fdman_path_ops", _libcglue_fdman_path_ops }, 
    { "_libcglue_fdman_socket_ops", _libcglue_fdman_socket_ops }, 
    { "libcglue_get_fd_info", libcglue_get_fd_info }, 
    { "libcglue_inet_addr", libcglue_inet_addr }, 
    { "libcglue_inet_aton", libcglue_inet_aton }, 
    { "libcglue_inet_ntoa", libcglue_inet_ntoa }, 
    { "libcglue_inet_ntoa_r", libcglue_inet_ntoa_r }, 
    { "_libcglue_init", _libcglue_init }, 
    { "__libcglue_init_stdio", __libcglue_init_stdio }, 
    { "libcglue_ps2ip_getconfig", libcglue_ps2ip_getconfig }, 
    { "libcglue_ps2ip_setconfig", libcglue_ps2ip_setconfig }, 
    { "_libcglue_rtc_get_offset_from_busclk", _libcglue_rtc_get_offset_from_busclk }, 
    { "_libcglue_rtc_update", _libcglue_rtc_update }, 
    { "_libcglue_rtc_update_impl", _libcglue_rtc_update_impl }, 
    { "_libcglue_timezone_update", _libcglue_timezone_update }, 
    { "_libcglue_timezone_update_impl", _libcglue_timezone_update_impl }, 
    { "__libpthreadglue_deinit", __libpthreadglue_deinit }, 
    { "__libpthreadglue_init", __libpthreadglue_init }, 
    { "_link", _link }, 
    { "linkat", linkat }, 
    { "listen", listen }, 
    { "__lock___arc4random_mutex", __lock___arc4random_mutex }, 
    { "__lock___atexit_recursive_mutex", __lock___atexit_recursive_mutex }, 
    { "__lock___at_quick_exit_mutex", __lock___at_quick_exit_mutex }, 
    { "__lock___dd_hash_mutex", __lock___dd_hash_mutex }, 
    { "__lock___env_recursive_mutex", __lock___env_recursive_mutex }, 
    { "__lock___malloc_recursive_mutex", __lock___malloc_recursive_mutex }, 
    { "__locks_deinit", __locks_deinit }, 
    { "__lock___sfp_recursive_mutex", __lock___sfp_recursive_mutex }, 
    { "__locks_init", __locks_init }, 
    { "__lock___tz_mutex", __lock___tz_mutex }, 
    { "_lseek", _lseek }, 
    { "lseek64", lseek64 }, 
    { "lstat", lstat }, 
    { "_mkdir", _mkdir }, 
    { "mkdir", mkdir }, 
    { "mkdirat", mkdirat }, 
    { "nanosleep", nanosleep }, 
    { "_open", _open }, 
    { "openat", openat }, 
    { "__path_absolute", __path_absolute }, 
    { "pathconf", pathconf }, 
    { "pause", pause }, 
    { "pipe", pipe }, 
    { "_ps2sdk_close", _ps2sdk_close }, 
    { "_ps2sdk_dclose", _ps2sdk_dclose }, 
    { "_ps2sdk_dread", _ps2sdk_dread }, 
    { "ps2sdk_get_iop_fd", ps2sdk_get_iop_fd }, 
    { "ps2sdk_get_iop_filename", ps2sdk_get_iop_filename }, 
    { "_ps2sdk_ioctl", _ps2sdk_ioctl }, 
    { "_ps2sdk_ioctl2", _ps2sdk_ioctl2 }, 
    { "_ps2sdk_lseek", _ps2sdk_lseek }, 
    { "_ps2sdk_lseek64", _ps2sdk_lseek64 }, 
    { "_ps2sdk_read", _ps2sdk_read }, 
    { "_ps2sdk_rtc_offset_from_busclk", _ps2sdk_rtc_offset_from_busclk }, 
    { "ps2sdk_setDaylightSaving", ps2sdk_setDaylightSaving }, 
    { "ps2sdk_setTimezone", ps2sdk_setTimezone }, 
    { "_ps2sdk_write", _ps2sdk_write }, 
    { "_read", _read }, 
    { "_readlink", _readlink }, 
    { "readlink", readlink }, 
    { "readlinkat", readlinkat }, 
    { "readv", readv }, 
    { "recv", recv }, 
    { "recvfrom", recvfrom }, 
    { "recvmsg", recvmsg }, 
    { "_rename", _rename }, 
    { "renameat", renameat }, 
    { "__retarget_lock_acquire", __retarget_lock_acquire }, 
    { "__retarget_lock_acquire_recursive", __retarget_lock_acquire_recursive }, 
    { "__retarget_lock_close", __retarget_lock_close }, 
    { "__retarget_lock_close_recursive", __retarget_lock_close_recursive }, 
    { "__retarget_lock_init", __retarget_lock_init }, 
    { "__retarget_lock_init_recursive", __retarget_lock_init_recursive }, 
    { "__retarget_lock_release", __retarget_lock_release }, 
    { "__retarget_lock_release_recursive", __retarget_lock_release_recursive }, 
    { "__retarget_lock_try_acquire", __retarget_lock_try_acquire }, 
    { "__retarget_lock_try_acquire_recursive", __retarget_lock_try_acquire_recursive }, 
    { "rmdir", rmdir }, 
    { "_sbrk", _sbrk }, 
    { "sched_yield", sched_yield }, 
    { "select", select }, 
    { "send", send }, 
    { "sendmsg", sendmsg }, 
    { "sendto", sendto }, 
    { "setitimer", setitimer }, 
    { "setsockopt", setsockopt }, 
    { "shutdown", shutdown }, 
    { "sigaction", sigaction }, 
    { "sigprocmask", sigprocmask }, 
    { "socket", socket }, 
    { "_stat", _stat }, 
    { "strcpy_ascii", strcpy_ascii }, 
    { "strcpy_sjis", strcpy_sjis }, 
    { "_symlink", _symlink }, 
    { "symlink", symlink }, 
    { "sysconf", sysconf }, 
    { "_system", _system }, 
    { "tcgetattr", tcgetattr }, 
    { "tcsetattr", tcsetattr }, 
    { "_times", _times }, 
    { "__transform64_errno", __transform64_errno }, 
    { "__transform_errno", __transform_errno }, 
    { "truncate", truncate }, 
    { "umask", umask }, 
    { "_unlink", _unlink }, 
    { "unlinkat", unlinkat }, 
    { "utime", utime }, 
    { "utimes", utimes }, 
    { "vfork", vfork }, 
    { "_wait", _wait }, 
    { "waitpid", waitpid }, 
    { "_write", _write }, 
    { 0, 0},
};
