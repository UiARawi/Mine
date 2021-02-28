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
extern void execute_51(char*, char *);
extern void execute_52(char*, char *);
extern void execute_53(char*, char *);
extern void execute_55(char*, char *);
extern void execute_56(char*, char *);
extern void execute_58(char*, char *);
extern void execute_60(char*, char *);
extern void execute_62(char*, char *);
extern void execute_63(char*, char *);
extern void execute_64(char*, char *);
extern void execute_65(char*, char *);
extern void execute_67(char*, char *);
extern void execute_68(char*, char *);
extern void execute_70(char*, char *);
extern void execute_72(char*, char *);
extern void execute_80(char*, char *);
extern void execute_81(char*, char *);
extern void execute_83(char*, char *);
extern void execute_85(char*, char *);
extern void execute_87(char*, char *);
extern void execute_89(char*, char *);
extern void execute_90(char*, char *);
extern void execute_92(char*, char *);
extern void execute_94(char*, char *);
extern void execute_102(char*, char *);
extern void execute_114(char*, char *);
extern void execute_116(char*, char *);
extern void execute_120(char*, char *);
extern void execute_121(char*, char *);
extern void execute_122(char*, char *);
extern void execute_123(char*, char *);
extern void execute_126(char*, char *);
extern void execute_127(char*, char *);
extern void execute_128(char*, char *);
extern void execute_138(char*, char *);
extern void execute_139(char*, char *);
extern void execute_130(char*, char *);
extern void execute_132(char*, char *);
extern void execute_133(char*, char *);
extern void execute_135(char*, char *);
extern void execute_137(char*, char *);
extern void transaction_0(char*, char*, unsigned, unsigned, unsigned);
extern void vhdl_transfunc_eventcallback(char*, char*, unsigned, unsigned, unsigned, char *);
extern void transaction_43(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_45(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_61(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_82(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_97(char*, char*, unsigned, unsigned, unsigned);
funcp funcTab[48] = {(funcp)execute_51, (funcp)execute_52, (funcp)execute_53, (funcp)execute_55, (funcp)execute_56, (funcp)execute_58, (funcp)execute_60, (funcp)execute_62, (funcp)execute_63, (funcp)execute_64, (funcp)execute_65, (funcp)execute_67, (funcp)execute_68, (funcp)execute_70, (funcp)execute_72, (funcp)execute_80, (funcp)execute_81, (funcp)execute_83, (funcp)execute_85, (funcp)execute_87, (funcp)execute_89, (funcp)execute_90, (funcp)execute_92, (funcp)execute_94, (funcp)execute_102, (funcp)execute_114, (funcp)execute_116, (funcp)execute_120, (funcp)execute_121, (funcp)execute_122, (funcp)execute_123, (funcp)execute_126, (funcp)execute_127, (funcp)execute_128, (funcp)execute_138, (funcp)execute_139, (funcp)execute_130, (funcp)execute_132, (funcp)execute_133, (funcp)execute_135, (funcp)execute_137, (funcp)transaction_0, (funcp)vhdl_transfunc_eventcallback, (funcp)transaction_43, (funcp)transaction_45, (funcp)transaction_61, (funcp)transaction_82, (funcp)transaction_97};
const int NumRelocateId= 48;

void relocate(char *dp)
{
	iki_relocate(dp, "xsim.dir/Final_prosjekt_top_file_behav/xsim.reloc",  (void **)funcTab, 48);
	iki_vhdl_file_variable_register(dp + 22824);
	iki_vhdl_file_variable_register(dp + 22880);


	/*Populate the transaction function pointer field in the whole net structure */
}

void sensitize(char *dp)
{
	iki_sensitize(dp, "xsim.dir/Final_prosjekt_top_file_behav/xsim.reloc");
}

void simulate(char *dp)
{
		iki_schedule_processes_at_time_zero(dp, "xsim.dir/Final_prosjekt_top_file_behav/xsim.reloc");
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
    iki_set_sv_type_file_path_name("xsim.dir/Final_prosjekt_top_file_behav/xsim.svtype");
    iki_set_crvs_dump_file_path_name("xsim.dir/Final_prosjekt_top_file_behav/xsim.crvsdump");
    void* design_handle = iki_create_design("xsim.dir/Final_prosjekt_top_file_behav/xsim.mem", (void *)relocate, (void *)sensitize, (void *)simulate, 0, isimBridge_getWdbWriter(), 0, argc, argv);
     iki_set_rc_trial_count(100);
    (void) design_handle;
    return iki_simulate_design();
}