extern void lua_absindex();
extern void lua_arith();
extern void lua_atpanic();
extern void lua_callk();
extern void luaC_barrier_();
extern void luaC_barrierback_();
extern void luaC_changemode();
extern void luaC_checkfinalizer();
extern void luaC_fix();
extern void luaC_freeallobjects();
extern void luaC_fullgc();
extern void lua_checkstack();
extern void lua_close();
extern void lua_closeslot();
extern void luaC_newobj();
extern void lua_compare();
extern void lua_concat();
extern void lua_copy();
extern void lua_createtable();
extern void luaC_runtilstate();
extern void luaC_step();
extern void luaD_call();
extern void luaD_callnoyield();
extern void luaD_closeprotected();
extern void luaD_growstack();
extern void luaD_hook();
extern void luaD_hookcall();
extern void luaD_inctop();
extern void luaD_pcall();
extern void luaD_poscall();
extern void luaD_precall();
extern void luaD_pretailcall();
extern void luaD_protectedparser();
extern void luaD_rawrunprotected();
extern void luaD_reallocstack();
extern void luaD_seterrorobj();
extern void luaD_shrinkstack();
extern void luaD_throw();
extern void luaD_tryfuncTM();
extern void lua_dump();
extern void luaE_checkcstack();
extern void luaE_extendCI();
extern void luaE_freeCI();
extern void luaE_freethread();
extern void luaE_incCstack();
extern void luaE_resetthread();
extern void lua_error();
extern void luaE_setdebt();
extern void luaE_shrinkCI();
extern void luaE_warnerror();
extern void luaE_warning();
extern void luaF_close();
extern void luaF_closeupval();
extern void luaF_findupval();
extern void luaF_freeproto();
extern void luaF_getlocalname();
extern void luaF_initupvals();
extern void luaF_newCclosure();
extern void luaF_newLclosure();
extern void luaF_newproto();
extern void luaF_newtbcupval();
extern void luaF_unlinkupval();
extern void luaG_addinfo();
extern void lua_gc();
extern void luaG_callerror();
extern void luaG_concaterror();
extern void luaG_errormsg();
extern void lua_getallocf();
extern void lua_getfield();
extern void lua_getglobal();
extern void lua_gethook();
extern void lua_gethookcount();
extern void lua_gethookmask();
extern void lua_geti();
extern void lua_getinfo();
extern void lua_getiuservalue();
extern void lua_getlocal();
extern void lua_getmetatable();
extern void lua_getstack();
extern void lua_gettable();
extern void lua_gettop();
extern void lua_getupvalue();
extern void luaG_findlocal();
extern void luaG_forerror();
extern void luaG_getfuncline();
extern void luaG_opinterror();
extern void luaG_ordererror();
extern void luaG_runerror();
extern void luaG_tointerror();
extern void luaG_traceexec();
extern void luaG_typeerror();
extern void luaH_finishset();
extern void luaH_free();
extern void luaH_get();
extern void luaH_getint();
extern void luaH_getn();
extern void luaH_getshortstr();
extern void luaH_getstr();
extern void luaH_new();
extern void luaH_newkey();
extern void luaH_next();
extern void luaH_realasize();
extern void luaH_resize();
extern void luaH_resizearray();
extern void luaH_set();
extern void luaH_setint();
extern void luai_ctype_();
extern void lua_ident();
extern void lua_iscfunction();
extern void lua_isinteger();
extern void lua_isnumber();
extern void lua_isstring();
extern void lua_isuserdata();
extern void lua_isyieldable();
extern void luaK_checkstack();
extern void luaK_code();
extern void luaK_codeABCk();
extern void luaK_codeABx();
extern void luaK_codeAsBx();
extern void luaK_concat();
extern void luaK_dischargevars();
extern void luaK_exp2anyreg();
extern void luaK_exp2anyregup();
extern void luaK_exp2const();
extern void luaK_exp2nextreg();
extern void luaK_exp2RK();
extern void luaK_exp2val();
extern void luaK_finish();
extern void luaK_fixline();
extern void luaK_getlabel();
extern void luaK_goiffalse();
extern void luaK_goiftrue();
extern void luaK_indexed();
extern void luaK_infix();
extern void luaK_int();
extern void luaK_isKint();
extern void luaK_jump();
extern void luaK_nil();
extern void luaK_patchlist();
extern void luaK_patchtohere();
extern void luaK_posfix();
extern void luaK_prefix();
extern void luaK_reserveregs();
extern void luaK_ret();
extern void luaK_self();
extern void luaK_semerror();
extern void luaK_setlist();
extern void luaK_setoneret();
extern void luaK_setreturns();
extern void luaK_settablesize();
extern void luaK_storevar();
extern void luaL_addgsub();
extern void luaL_addlstring();
extern void luaL_addstring();
extern void luaL_addvalue();
extern void luaL_argerror();
extern void luaL_buffinit();
extern void luaL_buffinitsize();
extern void luaL_callmeta();
extern void luaL_checkany();
extern void luaL_checkinteger();
extern void luaL_checklstring();
extern void luaL_checknumber();
extern void luaL_checkoption();
extern void luaL_checkstack();
extern void luaL_checktype();
extern void luaL_checkudata();
extern void luaL_checkversion_();
extern void lua_len();
extern void luaL_error();
extern void luaL_execresult();
extern void luaL_fileresult();
extern void luaL_getmetafield();
extern void luaL_getsubtable();
extern void luaL_gsub();
extern void luaL_len();
extern void luaL_loadbufferx();
extern void luaL_loadfilex();
extern void luaL_loadstring();
extern void luaL_newmetatable();
extern void luaL_newstate();
extern void lua_load();
extern void luaL_openlibs();
extern void luaL_optinteger();
extern void luaL_optlstring();
extern void luaL_optnumber();
extern void luaL_prepbuffsize();
extern void luaL_pushresult();
extern void luaL_pushresultsize();
extern void luaL_ref();
extern void luaL_requiref();
extern void luaL_setfuncs();
extern void luaL_setmetatable();
extern void luaL_testudata();
extern void luaL_tolstring();
extern void luaL_traceback();
extern void luaL_typeerror();
extern void luaL_unref();
extern void luaL_where();
extern void luaM_free_();
extern void luaM_growaux_();
extern void luaM_malloc_();
extern void luaM_realloc_();
extern void luaM_saferealloc_();
extern void luaM_shrinkvector_();
extern void luaM_toobig();
extern void lua_newstate();
extern void lua_newthread();
extern void lua_newuserdatauv();
extern void lua_next();
extern void luaO_arith();
extern void luaO_ceillog2();
extern void luaO_chunkid();
extern void luaO_hexavalue();
extern void luaopen_base();
extern void luaopen_coroutine();
extern void luaopen_debug();
extern void luaopen_io();
extern void luaopen_math();
extern void luaopen_os();
extern void luaopen_package();
extern void luaopen_string();
extern void luaopen_table();
extern void luaopen_utf8();
extern void luaO_pushfstring();
extern void luaO_pushvfstring();
extern void luaO_rawarith();
extern void luaO_str2num();
extern void luaO_tostring();
extern void luaO_utf8esc();
extern void lua_pcallk();
extern void luaP_opmodes();
extern void lua_pushboolean();
extern void lua_pushcclosure();
extern void lua_pushfstring();
extern void lua_pushinteger();
extern void lua_pushlightuserdata();
extern void lua_pushlstring();
extern void lua_pushnil();
extern void lua_pushnumber();
extern void lua_pushstring();
extern void lua_pushthread();
extern void lua_pushvalue();
extern void lua_pushvfstring();
extern void lua_rawequal();
extern void lua_rawget();
extern void lua_rawgeti();
extern void lua_rawgetp();
extern void lua_rawlen();
extern void lua_rawset();
extern void lua_rawseti();
extern void lua_rawsetp();
extern void lua_resetthread();
extern void lua_resume();
extern void lua_rotate();
extern void luaS_clearcache();
extern void luaS_createlngstrobj();
extern void luaS_eqlngstr();
extern void lua_setallocf();
extern void lua_setcstacklimit();
extern void lua_setfield();
extern void lua_setglobal();
extern void lua_sethook();
extern void lua_seti();
extern void lua_setiuservalue();
extern void lua_setlocal();
extern void lua_setmetatable();
extern void lua_settable();
extern void lua_settop();
extern void lua_setupvalue();
extern void lua_setwarnf();
extern void luaS_hash();
extern void luaS_hashlongstr();
extern void luaS_init();
extern void luaS_new();
extern void luaS_newlstr();
extern void luaS_newudata();
extern void luaS_remove();
extern void luaS_resize();
extern void lua_status();
extern void lua_stringtonumber();
extern void luaT_adjustvarargs();
extern void luaT_callorderiTM();
extern void luaT_callorderTM();
extern void luaT_callTM();
extern void luaT_callTMres();
extern void luaT_gettm();
extern void luaT_gettmbyobj();
extern void luaT_getvarargs();
extern void luaT_init();
extern void luaT_objtypename();
extern void lua_toboolean();
extern void lua_tocfunction();
extern void lua_toclose();
extern void lua_tointegerx();
extern void lua_tolstring();
extern void lua_tonumberx();
extern void lua_topointer();
extern void lua_tothread();
extern void lua_touserdata();
extern void luaT_trybinassocTM();
extern void luaT_trybiniTM();
extern void luaT_trybinTM();
extern void luaT_tryconcatTM();
extern void luaT_typenames_();
extern void lua_type();
extern void lua_typename();
extern void luaU_dump();
extern void lua_upvalueid();
extern void lua_upvaluejoin();
extern void luaU_undump();
extern void luaV_concat();
extern void luaV_equalobj();
extern void lua_version();
extern void luaV_execute();
extern void luaV_finishget();
extern void luaV_finishOp();
extern void luaV_finishset();
extern void luaV_flttointeger();
extern void luaV_idiv();
extern void luaV_lessequal();
extern void luaV_lessthan();
extern void luaV_mod();
extern void luaV_modf();
extern void luaV_objlen();
extern void luaV_shiftl();
extern void luaV_tointeger();
extern void luaV_tointegerns();
extern void luaV_tonumber_();
extern void lua_warning();
extern void luaX_init();
extern void luaX_lookahead();
extern void lua_xmove();
extern void luaX_newstring();
extern void luaX_next();
extern void luaX_setinput();
extern void luaX_syntaxerror();
extern void luaX_token2str();
extern void lua_yieldk();
extern void luaY_nvarstack();
extern void luaY_parser();
extern void luaZ_fill();
extern void luaZ_init();
extern void luaZ_read();
struct export_list_t {
    char * name;
    void * pointer;
} liblua_exports[] = {
    { "lua_absindex", lua_absindex }, 
    { "lua_arith", lua_arith }, 
    { "lua_atpanic", lua_atpanic }, 
    { "lua_callk", lua_callk }, 
    { "luaC_barrier_", luaC_barrier_ }, 
    { "luaC_barrierback_", luaC_barrierback_ }, 
    { "luaC_changemode", luaC_changemode }, 
    { "luaC_checkfinalizer", luaC_checkfinalizer }, 
    { "luaC_fix", luaC_fix }, 
    { "luaC_freeallobjects", luaC_freeallobjects }, 
    { "luaC_fullgc", luaC_fullgc }, 
    { "lua_checkstack", lua_checkstack }, 
    { "lua_close", lua_close }, 
    { "lua_closeslot", lua_closeslot }, 
    { "luaC_newobj", luaC_newobj }, 
    { "lua_compare", lua_compare }, 
    { "lua_concat", lua_concat }, 
    { "lua_copy", lua_copy }, 
    { "lua_createtable", lua_createtable }, 
    { "luaC_runtilstate", luaC_runtilstate }, 
    { "luaC_step", luaC_step }, 
    { "luaD_call", luaD_call }, 
    { "luaD_callnoyield", luaD_callnoyield }, 
    { "luaD_closeprotected", luaD_closeprotected }, 
    { "luaD_growstack", luaD_growstack }, 
    { "luaD_hook", luaD_hook }, 
    { "luaD_hookcall", luaD_hookcall }, 
    { "luaD_inctop", luaD_inctop }, 
    { "luaD_pcall", luaD_pcall }, 
    { "luaD_poscall", luaD_poscall }, 
    { "luaD_precall", luaD_precall }, 
    { "luaD_pretailcall", luaD_pretailcall }, 
    { "luaD_protectedparser", luaD_protectedparser }, 
    { "luaD_rawrunprotected", luaD_rawrunprotected }, 
    { "luaD_reallocstack", luaD_reallocstack }, 
    { "luaD_seterrorobj", luaD_seterrorobj }, 
    { "luaD_shrinkstack", luaD_shrinkstack }, 
    { "luaD_throw", luaD_throw }, 
    { "luaD_tryfuncTM", luaD_tryfuncTM }, 
    { "lua_dump", lua_dump }, 
    { "luaE_checkcstack", luaE_checkcstack }, 
    { "luaE_extendCI", luaE_extendCI }, 
    { "luaE_freeCI", luaE_freeCI }, 
    { "luaE_freethread", luaE_freethread }, 
    { "luaE_incCstack", luaE_incCstack }, 
    { "luaE_resetthread", luaE_resetthread }, 
    { "lua_error", lua_error }, 
    { "luaE_setdebt", luaE_setdebt }, 
    { "luaE_shrinkCI", luaE_shrinkCI }, 
    { "luaE_warnerror", luaE_warnerror }, 
    { "luaE_warning", luaE_warning }, 
    { "luaF_close", luaF_close }, 
    { "luaF_closeupval", luaF_closeupval }, 
    { "luaF_findupval", luaF_findupval }, 
    { "luaF_freeproto", luaF_freeproto }, 
    { "luaF_getlocalname", luaF_getlocalname }, 
    { "luaF_initupvals", luaF_initupvals }, 
    { "luaF_newCclosure", luaF_newCclosure }, 
    { "luaF_newLclosure", luaF_newLclosure }, 
    { "luaF_newproto", luaF_newproto }, 
    { "luaF_newtbcupval", luaF_newtbcupval }, 
    { "luaF_unlinkupval", luaF_unlinkupval }, 
    { "luaG_addinfo", luaG_addinfo }, 
    { "lua_gc", lua_gc }, 
    { "luaG_callerror", luaG_callerror }, 
    { "luaG_concaterror", luaG_concaterror }, 
    { "luaG_errormsg", luaG_errormsg }, 
    { "lua_getallocf", lua_getallocf }, 
    { "lua_getfield", lua_getfield }, 
    { "lua_getglobal", lua_getglobal }, 
    { "lua_gethook", lua_gethook }, 
    { "lua_gethookcount", lua_gethookcount }, 
    { "lua_gethookmask", lua_gethookmask }, 
    { "lua_geti", lua_geti }, 
    { "lua_getinfo", lua_getinfo }, 
    { "lua_getiuservalue", lua_getiuservalue }, 
    { "lua_getlocal", lua_getlocal }, 
    { "lua_getmetatable", lua_getmetatable }, 
    { "lua_getstack", lua_getstack }, 
    { "lua_gettable", lua_gettable }, 
    { "lua_gettop", lua_gettop }, 
    { "lua_getupvalue", lua_getupvalue }, 
    { "luaG_findlocal", luaG_findlocal }, 
    { "luaG_forerror", luaG_forerror }, 
    { "luaG_getfuncline", luaG_getfuncline }, 
    { "luaG_opinterror", luaG_opinterror }, 
    { "luaG_ordererror", luaG_ordererror }, 
    { "luaG_runerror", luaG_runerror }, 
    { "luaG_tointerror", luaG_tointerror }, 
    { "luaG_traceexec", luaG_traceexec }, 
    { "luaG_typeerror", luaG_typeerror }, 
    { "luaH_finishset", luaH_finishset }, 
    { "luaH_free", luaH_free }, 
    { "luaH_get", luaH_get }, 
    { "luaH_getint", luaH_getint }, 
    { "luaH_getn", luaH_getn }, 
    { "luaH_getshortstr", luaH_getshortstr }, 
    { "luaH_getstr", luaH_getstr }, 
    { "luaH_new", luaH_new }, 
    { "luaH_newkey", luaH_newkey }, 
    { "luaH_next", luaH_next }, 
    { "luaH_realasize", luaH_realasize }, 
    { "luaH_resize", luaH_resize }, 
    { "luaH_resizearray", luaH_resizearray }, 
    { "luaH_set", luaH_set }, 
    { "luaH_setint", luaH_setint }, 
    { "luai_ctype_", luai_ctype_ }, 
    { "lua_ident", lua_ident }, 
    { "lua_iscfunction", lua_iscfunction }, 
    { "lua_isinteger", lua_isinteger }, 
    { "lua_isnumber", lua_isnumber }, 
    { "lua_isstring", lua_isstring }, 
    { "lua_isuserdata", lua_isuserdata }, 
    { "lua_isyieldable", lua_isyieldable }, 
    { "luaK_checkstack", luaK_checkstack }, 
    { "luaK_code", luaK_code }, 
    { "luaK_codeABCk", luaK_codeABCk }, 
    { "luaK_codeABx", luaK_codeABx }, 
    { "luaK_codeAsBx", luaK_codeAsBx }, 
    { "luaK_concat", luaK_concat }, 
    { "luaK_dischargevars", luaK_dischargevars }, 
    { "luaK_exp2anyreg", luaK_exp2anyreg }, 
    { "luaK_exp2anyregup", luaK_exp2anyregup }, 
    { "luaK_exp2const", luaK_exp2const }, 
    { "luaK_exp2nextreg", luaK_exp2nextreg }, 
    { "luaK_exp2RK", luaK_exp2RK }, 
    { "luaK_exp2val", luaK_exp2val }, 
    { "luaK_finish", luaK_finish }, 
    { "luaK_fixline", luaK_fixline }, 
    { "luaK_getlabel", luaK_getlabel }, 
    { "luaK_goiffalse", luaK_goiffalse }, 
    { "luaK_goiftrue", luaK_goiftrue }, 
    { "luaK_indexed", luaK_indexed }, 
    { "luaK_infix", luaK_infix }, 
    { "luaK_int", luaK_int }, 
    { "luaK_isKint", luaK_isKint }, 
    { "luaK_jump", luaK_jump }, 
    { "luaK_nil", luaK_nil }, 
    { "luaK_patchlist", luaK_patchlist }, 
    { "luaK_patchtohere", luaK_patchtohere }, 
    { "luaK_posfix", luaK_posfix }, 
    { "luaK_prefix", luaK_prefix }, 
    { "luaK_reserveregs", luaK_reserveregs }, 
    { "luaK_ret", luaK_ret }, 
    { "luaK_self", luaK_self }, 
    { "luaK_semerror", luaK_semerror }, 
    { "luaK_setlist", luaK_setlist }, 
    { "luaK_setoneret", luaK_setoneret }, 
    { "luaK_setreturns", luaK_setreturns }, 
    { "luaK_settablesize", luaK_settablesize }, 
    { "luaK_storevar", luaK_storevar }, 
    { "luaL_addgsub", luaL_addgsub }, 
    { "luaL_addlstring", luaL_addlstring }, 
    { "luaL_addstring", luaL_addstring }, 
    { "luaL_addvalue", luaL_addvalue }, 
    { "luaL_argerror", luaL_argerror }, 
    { "luaL_buffinit", luaL_buffinit }, 
    { "luaL_buffinitsize", luaL_buffinitsize }, 
    { "luaL_callmeta", luaL_callmeta }, 
    { "luaL_checkany", luaL_checkany }, 
    { "luaL_checkinteger", luaL_checkinteger }, 
    { "luaL_checklstring", luaL_checklstring }, 
    { "luaL_checknumber", luaL_checknumber }, 
    { "luaL_checkoption", luaL_checkoption }, 
    { "luaL_checkstack", luaL_checkstack }, 
    { "luaL_checktype", luaL_checktype }, 
    { "luaL_checkudata", luaL_checkudata }, 
    { "luaL_checkversion_", luaL_checkversion_ }, 
    { "lua_len", lua_len }, 
    { "luaL_error", luaL_error }, 
    { "luaL_execresult", luaL_execresult }, 
    { "luaL_fileresult", luaL_fileresult }, 
    { "luaL_getmetafield", luaL_getmetafield }, 
    { "luaL_getsubtable", luaL_getsubtable }, 
    { "luaL_gsub", luaL_gsub }, 
    { "luaL_len", luaL_len }, 
    { "luaL_loadbufferx", luaL_loadbufferx }, 
    { "luaL_loadfilex", luaL_loadfilex }, 
    { "luaL_loadstring", luaL_loadstring }, 
    { "luaL_newmetatable", luaL_newmetatable }, 
    { "luaL_newstate", luaL_newstate }, 
    { "lua_load", lua_load }, 
    { "luaL_openlibs", luaL_openlibs }, 
    { "luaL_optinteger", luaL_optinteger }, 
    { "luaL_optlstring", luaL_optlstring }, 
    { "luaL_optnumber", luaL_optnumber }, 
    { "luaL_prepbuffsize", luaL_prepbuffsize }, 
    { "luaL_pushresult", luaL_pushresult }, 
    { "luaL_pushresultsize", luaL_pushresultsize }, 
    { "luaL_ref", luaL_ref }, 
    { "luaL_requiref", luaL_requiref }, 
    { "luaL_setfuncs", luaL_setfuncs }, 
    { "luaL_setmetatable", luaL_setmetatable }, 
    { "luaL_testudata", luaL_testudata }, 
    { "luaL_tolstring", luaL_tolstring }, 
    { "luaL_traceback", luaL_traceback }, 
    { "luaL_typeerror", luaL_typeerror }, 
    { "luaL_unref", luaL_unref }, 
    { "luaL_where", luaL_where }, 
    { "luaM_free_", luaM_free_ }, 
    { "luaM_growaux_", luaM_growaux_ }, 
    { "luaM_malloc_", luaM_malloc_ }, 
    { "luaM_realloc_", luaM_realloc_ }, 
    { "luaM_saferealloc_", luaM_saferealloc_ }, 
    { "luaM_shrinkvector_", luaM_shrinkvector_ }, 
    { "luaM_toobig", luaM_toobig }, 
    { "lua_newstate", lua_newstate }, 
    { "lua_newthread", lua_newthread }, 
    { "lua_newuserdatauv", lua_newuserdatauv }, 
    { "lua_next", lua_next }, 
    { "luaO_arith", luaO_arith }, 
    { "luaO_ceillog2", luaO_ceillog2 }, 
    { "luaO_chunkid", luaO_chunkid }, 
    { "luaO_hexavalue", luaO_hexavalue }, 
    { "luaopen_base", luaopen_base }, 
    { "luaopen_coroutine", luaopen_coroutine }, 
    { "luaopen_debug", luaopen_debug }, 
    { "luaopen_io", luaopen_io }, 
    { "luaopen_math", luaopen_math }, 
    { "luaopen_os", luaopen_os }, 
    { "luaopen_package", luaopen_package }, 
    { "luaopen_string", luaopen_string }, 
    { "luaopen_table", luaopen_table }, 
    { "luaopen_utf8", luaopen_utf8 }, 
    { "luaO_pushfstring", luaO_pushfstring }, 
    { "luaO_pushvfstring", luaO_pushvfstring }, 
    { "luaO_rawarith", luaO_rawarith }, 
    { "luaO_str2num", luaO_str2num }, 
    { "luaO_tostring", luaO_tostring }, 
    { "luaO_utf8esc", luaO_utf8esc }, 
    { "lua_pcallk", lua_pcallk }, 
    { "luaP_opmodes", luaP_opmodes }, 
    { "lua_pushboolean", lua_pushboolean }, 
    { "lua_pushcclosure", lua_pushcclosure }, 
    { "lua_pushfstring", lua_pushfstring }, 
    { "lua_pushinteger", lua_pushinteger }, 
    { "lua_pushlightuserdata", lua_pushlightuserdata }, 
    { "lua_pushlstring", lua_pushlstring }, 
    { "lua_pushnil", lua_pushnil }, 
    { "lua_pushnumber", lua_pushnumber }, 
    { "lua_pushstring", lua_pushstring }, 
    { "lua_pushthread", lua_pushthread }, 
    { "lua_pushvalue", lua_pushvalue }, 
    { "lua_pushvfstring", lua_pushvfstring }, 
    { "lua_rawequal", lua_rawequal }, 
    { "lua_rawget", lua_rawget }, 
    { "lua_rawgeti", lua_rawgeti }, 
    { "lua_rawgetp", lua_rawgetp }, 
    { "lua_rawlen", lua_rawlen }, 
    { "lua_rawset", lua_rawset }, 
    { "lua_rawseti", lua_rawseti }, 
    { "lua_rawsetp", lua_rawsetp }, 
    { "lua_resetthread", lua_resetthread }, 
    { "lua_resume", lua_resume }, 
    { "lua_rotate", lua_rotate }, 
    { "luaS_clearcache", luaS_clearcache }, 
    { "luaS_createlngstrobj", luaS_createlngstrobj }, 
    { "luaS_eqlngstr", luaS_eqlngstr }, 
    { "lua_setallocf", lua_setallocf }, 
    { "lua_setcstacklimit", lua_setcstacklimit }, 
    { "lua_setfield", lua_setfield }, 
    { "lua_setglobal", lua_setglobal }, 
    { "lua_sethook", lua_sethook }, 
    { "lua_seti", lua_seti }, 
    { "lua_setiuservalue", lua_setiuservalue }, 
    { "lua_setlocal", lua_setlocal }, 
    { "lua_setmetatable", lua_setmetatable }, 
    { "lua_settable", lua_settable }, 
    { "lua_settop", lua_settop }, 
    { "lua_setupvalue", lua_setupvalue }, 
    { "lua_setwarnf", lua_setwarnf }, 
    { "luaS_hash", luaS_hash }, 
    { "luaS_hashlongstr", luaS_hashlongstr }, 
    { "luaS_init", luaS_init }, 
    { "luaS_new", luaS_new }, 
    { "luaS_newlstr", luaS_newlstr }, 
    { "luaS_newudata", luaS_newudata }, 
    { "luaS_remove", luaS_remove }, 
    { "luaS_resize", luaS_resize }, 
    { "lua_status", lua_status }, 
    { "lua_stringtonumber", lua_stringtonumber }, 
    { "luaT_adjustvarargs", luaT_adjustvarargs }, 
    { "luaT_callorderiTM", luaT_callorderiTM }, 
    { "luaT_callorderTM", luaT_callorderTM }, 
    { "luaT_callTM", luaT_callTM }, 
    { "luaT_callTMres", luaT_callTMres }, 
    { "luaT_gettm", luaT_gettm }, 
    { "luaT_gettmbyobj", luaT_gettmbyobj }, 
    { "luaT_getvarargs", luaT_getvarargs }, 
    { "luaT_init", luaT_init }, 
    { "luaT_objtypename", luaT_objtypename }, 
    { "lua_toboolean", lua_toboolean }, 
    { "lua_tocfunction", lua_tocfunction }, 
    { "lua_toclose", lua_toclose }, 
    { "lua_tointegerx", lua_tointegerx }, 
    { "lua_tolstring", lua_tolstring }, 
    { "lua_tonumberx", lua_tonumberx }, 
    { "lua_topointer", lua_topointer }, 
    { "lua_tothread", lua_tothread }, 
    { "lua_touserdata", lua_touserdata }, 
    { "luaT_trybinassocTM", luaT_trybinassocTM }, 
    { "luaT_trybiniTM", luaT_trybiniTM }, 
    { "luaT_trybinTM", luaT_trybinTM }, 
    { "luaT_tryconcatTM", luaT_tryconcatTM }, 
    { "luaT_typenames_", luaT_typenames_ }, 
    { "lua_type", lua_type }, 
    { "lua_typename", lua_typename }, 
    { "luaU_dump", luaU_dump }, 
    { "lua_upvalueid", lua_upvalueid }, 
    { "lua_upvaluejoin", lua_upvaluejoin }, 
    { "luaU_undump", luaU_undump }, 
    { "luaV_concat", luaV_concat }, 
    { "luaV_equalobj", luaV_equalobj }, 
    { "lua_version", lua_version }, 
    { "luaV_execute", luaV_execute }, 
    { "luaV_finishget", luaV_finishget }, 
    { "luaV_finishOp", luaV_finishOp }, 
    { "luaV_finishset", luaV_finishset }, 
    { "luaV_flttointeger", luaV_flttointeger }, 
    { "luaV_idiv", luaV_idiv }, 
    { "luaV_lessequal", luaV_lessequal }, 
    { "luaV_lessthan", luaV_lessthan }, 
    { "luaV_mod", luaV_mod }, 
    { "luaV_modf", luaV_modf }, 
    { "luaV_objlen", luaV_objlen }, 
    { "luaV_shiftl", luaV_shiftl }, 
    { "luaV_tointeger", luaV_tointeger }, 
    { "luaV_tointegerns", luaV_tointegerns }, 
    { "luaV_tonumber_", luaV_tonumber_ }, 
    { "lua_warning", lua_warning }, 
    { "luaX_init", luaX_init }, 
    { "luaX_lookahead", luaX_lookahead }, 
    { "lua_xmove", lua_xmove }, 
    { "luaX_newstring", luaX_newstring }, 
    { "luaX_next", luaX_next }, 
    { "luaX_setinput", luaX_setinput }, 
    { "luaX_syntaxerror", luaX_syntaxerror }, 
    { "luaX_token2str", luaX_token2str }, 
    { "lua_yieldk", lua_yieldk }, 
    { "luaY_nvarstack", luaY_nvarstack }, 
    { "luaY_parser", luaY_parser }, 
    { "luaZ_fill", luaZ_fill }, 
    { "luaZ_init", luaZ_init }, 
    { "luaZ_read", luaZ_read }, 
    { 0, 0},
};
