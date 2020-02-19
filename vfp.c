// VFP
#define OS_VFPSupport_ActiveContext 0x58EC6
#define OS_VFPSupport_CreateContext 0x58EC1
#define OS_VFPSupport_DestroyContext 0x58EC2
#define OS_VFPSupport_ChangeContext 0x58EC3
#define OS_VFPSupport_ActiveContext 0x58EC6
UINT VFP_context;
UINT saved_VFP_context;

void active_vfp_context() {
	_kernel_swi_regs regs;
	_kernel_swi(OS_VFPSupport_ActiveContext, &regs, &regs);
	printf("Current VFP Context:%X\n", regs.r[0]);
}

void create_vfp_context() {
	_kernel_swi_regs regs;
	regs.r[0] = (1 << 31);
	regs.r[1] = 32;
	regs.r[2] = 0;
	regs.r[3] = 0;
	_kernel_swi(OS_VFPSupport_CreateContext, &regs, &regs);
	VFP_context = regs.r[0];
	printf("VFP Context:%X\n", VFP_context);
}

void destroy_vfp_context() {
	_kernel_swi_regs regs;
	regs.r[0] = VFP_context;
	regs.r[1] = 0;
	_kernel_swi(OS_VFPSupport_DestroyContext, &regs, &regs);
	printf("Destroying VFP Context:%X\n", VFP_context);
}

void save_vfp_context() {
	_kernel_swi_regs regs;
	_kernel_swi(OS_VFPSupport_ActiveContext, &regs, &regs);
	saved_VFP_context = regs.r[0];
	printf("Saved VFP Context:%X\n", saved_VFP_context);
}

void restore_vfp_context() {
	_kernel_swi_regs regs;
	regs.r[0] = saved_VFP_context;
	regs.r[1] = 1;
	_kernel_swi(OS_VFPSupport_ChangeContext, &regs, &regs);
	saved_VFP_context = regs.r[0];
}
