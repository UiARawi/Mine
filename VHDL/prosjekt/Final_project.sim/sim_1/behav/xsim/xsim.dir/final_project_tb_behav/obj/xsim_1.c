/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/


#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/


#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
typedef void (*funcp)(char *, char *);
extern int main(int, char**);
extern void execute_143(char*, char *);
extern void execute_144(char*, char *);
extern void execute_52(char*, char *);
extern void execute_53(char*, char *);
extern void execute_54(char*, char *);
extern void execute_56(char*, char *);
extern void execute_57(char*, char *);
extern void execute_59(char*, char *);
extern void execute_61(char*, char *);
extern void execute_63(char*, char *);
extern void execute_64(char*, char *);
extern void execute_65(char*, char *);
extern void execute_66(char*, char *);
extern void execute_68(char*, char *);
extern void execute_69(char*, char *);
extern void execute_71(char*, char *);
extern void execute_73(char*, char *);
extern void execute_81(char*, char *);
extern void execute_82(char*, char *);
extern void execute_84(char*, char *);
extern void execute_86(char*, char *);
extern void execute_88(char*, char *);
extern void execute_90(char*, char *);
extern void execute_91(char*, char *);
extern void execute_93(char*, char *);
extern void execute_95(char*, char *);
extern void execute_103(char*, char *);
extern void execute_115(char*, char *);
extern void execute_117(char*, char *);
extern void execute_121(char*, char *);
extern void execute_122(char*, char *);
extern void execute_123(char*, char *);
extern void execute_124(char*, char *);
extern void execute_128(char*, char *);
extern void execute_129(char*, char *);
extern void execute_130(char*, char *);
extern void execute_140(char*, char *);
extern void execute_141(char*, char *);
extern void execute_132(char*, char *);
extern void execute_134(char*, char *);
extern void execute_135(char*, char *);
extern void execute_137(char*, char *);
extern void execute_139(char*, char *);
extern void transaction_0(char*, char*, unsigned, unsigned, unsigned);
extern void vhdl_transfunc_eventcallback(char*, char*, unsigned, unsigned, unsigned, char *);
extern void transaction_7(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_43(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_45(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_61(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_93(char*, char*, unsigned, unsigned, unsigned);
funcp funcTab[50] = {(funcp)execute_143, (funcp)execute_144, (funcp)execute_52, (funcp)execute_53, (funcp)execute_54, (funcp)execute_56, (funcp)execute_57, (funcp)execute_59, (funcp)execute_61, (funcp)execute_63, (funcp)execute_64, (funcp)execute_65, (funcp)execute_66, (funcp)execute_68, (funcp)execute_69, (funcp)execute_71, (funcp)execute_73, (funcp)execute_81, (funcp)execute_82, (funcp)execute_84, (funcp)execute_86, (funcp)execute_88, (funcp)execute_90, (funcp)execute_91, (funcp)execute_93, (funcp)execute_95, (funcp)execute_103, (funcp)execute_115, (funcp)execute_117, (funcp)execute_121, (funcp)execute_122, (funcp)execute_123, (funcp)execute_124, (funcp)execute_128, (funcp)execute_129, (funcp)execute_130, (funcp)execute_140, (funcp)execute_141, (funcp)execute_132, (funcp)execute_134, (funcp)execute_135, (funcp)execute_137, (funcp)execute_139, (funcp)transaction_0, (funcp)vhdl_transfunc_eventcallback, (funcp)transaction_7, (funcp)transaction_43, (funcp)transaction_45, (funcp)transaction_61, (funcp)transaction_93};
const int NumRelocateId= 50;

void relocate(char *dp)
{
	iki_relocate(dp, "xsim.dir/final_project_tb_behav/xsim.reloc",  (void **)funcTab, 50);
	iki_vhdl_file_variable_register(dp + 22432);
	iki_vhdl_file_variable_register(dp + 22488);


	/*Populate the transaction function pointer field in the whole net structure */
}

void sensitize(char *dp)
{
	iki_sensitize(dp, "xsim.dir/final_project_tb_behav/xsim.reloc");
}

void simulate(char *dp)
{
		iki_schedule_processes_at_time_zero(dp, "xsim.dir/final_project_tb_behav/xsim.reloc");
	// Initialize Verilog nets in mixed simulation, for the cases when the value at time 0 should be propagated from the mixed language Vhdl net
	iki_execute_processes();

	// Schedule resolution functions for the multiply driven Verilog nets that have strength
	// Schedule transaction functions for the singly driven Verilog nets that have strength

}
#include "iki_bridge.h"
void relocate(char *);

void sensitize(char *);

void simulate(char *);

extern SYSTEMCLIB_IMP_DLLSPEC void local_register_implicit_channel(int, char*);
extern void implicit_HDL_SCinstatiate();

extern SYSTEMCLIB_IMP_DLLSPEC int xsim_argc_copy ;
extern SYSTEMCLIB_IMP_DLLSPEC char** xsim_argv_copy ;

int main(int argc, char **argv)
{
    iki_heap_initialize("ms", "isimmm", 0, 2147483648) ;
    iki_set_sv_type_file_path_name("xsim.dir/final_project_tb_behav/xsim.svtype");
    iki_set_crvs_dump_file_path_name("xsim.dir/final_project_tb_behav/xsim.crvsdump");
    void* design_handle = iki_create_design("xsim.dir/final_project_tb_behav/xsim.mem", (void *)relocate, (void *)sensitize, (void *)simulate, 0, isimBridge_getWdbWriter(), 0, argc, argv);
     iki_set_rc_trial_count(100);
    (void) design_handle;
    return iki_simulate_design();
}
