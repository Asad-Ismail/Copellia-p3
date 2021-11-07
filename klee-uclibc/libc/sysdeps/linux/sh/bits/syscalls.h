#ifndef _BITS_SYSCALLS_H
#define _BITS_SYSCALLS_H
#ifndef _SYSCALL_H
# error "Never use <bits/syscalls.h> directly; include <sys/syscall.h> instead."
#endif

/* The Linux kernel uses different trap numbers on sh-2.  */
#ifdef __CONFIG_SH2__
# define __SH_SYSCALL_TRAP_BASE 0x20
#else
# define __SH_SYSCALL_TRAP_BASE 0x10
#endif

#ifndef __ASSEMBLER__

#include <errno.h>

#define SYS_ify(syscall_name)  (__NR_##syscall_name)

/* user-visible error numbers are in the range -1 - -125: see <asm-sh/errno.h> */
#define __syscall_return(type, res) \
do { \
	if ((unsigned long)(res) >= (unsigned long)(-125)) { \
	/* Avoid using "res" which is declared to be in register r0; \
	   errno might expand to a function call and clobber it.  */ \
		int __err = -(res); \
		__set_errno(__err); \
		res = -1; \
	} \
	return (type) (res); \
} while (0)

/* XXX - _foo needs to be __foo, while __NR_bar could be _NR_bar. */
#define _syscall0(type,name) \
type name(void) \
{ \
register long __sc0 __asm__ ("r3") = __NR_##name; \
__asm__ __volatile__ ("trapa	%1" \
	: "=z" (__sc0) \
	: "i" (__SH_SYSCALL_TRAP_BASE), "0" (__sc0) \
	: "memory" ); \
__syscall_return(type,__sc0); \
}

#define _syscall1(type,name,type1,arg1) \
type name(type1 arg1) \
{ \
register long __sc0 __asm__ ("r3") = __NR_##name; \
register long __sc4 __asm__ ("r4") = (long) arg1; \
__asm__ __volatile__ ("trapa	%1" \
	: "=z" (__sc0) \
	: "i" (__SH_SYSCALL_TRAP_BASE + 1), "0" (__sc0), "r" (__sc4) \
	: "memory"); \
__syscall_return(type,__sc0); \
}

#define _syscall2(type,name,type1,arg1,type2,arg2) \
type name(type1 arg1,type2 arg2) \
{ \
register long __sc0 __asm__ ("r3") = __NR_##name; \
register long __sc4 __asm__ ("r4") = (long) arg1; \
register long __sc5 __asm__ ("r5") = (long) arg2; \
__asm__ __volatile__ ("trapa	%1" \
	: "=z" (__sc0) \
	: "i" (__SH_SYSCALL_TRAP_BASE + 2), "0" (__sc0), "r" (__sc4), \
          "r" (__sc5) \
	: "memory"); \
__syscall_return(type,__sc0); \
}

#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3) \
type name(type1 arg1,type2 arg2,type3 arg3) \
{ \
register long __sc0 __asm__ ("r3") = __NR_##name; \
register long __sc4 __asm__ ("r4") = (long) arg1; \
register long __sc5 __asm__ ("r5") = (long) arg2; \
register long __sc6 __asm__ ("r6") = (long) arg3; \
__asm__ __volatile__ ("trapa	%1" \
	: "=z" (__sc0) \
	: "i" (__SH_SYSCALL_TRAP_BASE + 3), "0" (__sc0), "r" (__sc4), \
          "r" (__sc5), "r" (__sc6) \
	: "memory"); \
__syscall_return(type,__sc0); \
}

#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4) \
type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4) \
{ \
register long __sc0 __asm__ ("r3") = __NR_##name; \
register long __sc4 __asm__ ("r4") = (long) arg1; \
register long __sc5 __asm__ ("r5") = (long) arg2; \
register long __sc6 __asm__ ("r6") = (long) arg3; \
register long __sc7 __asm__ ("r7") = (long) arg4; \
__asm__ __volatile__ ("trapa	%1" \
	: "=z" (__sc0) \
	: "i" (__SH_SYSCALL_TRAP_BASE + 4), "0" (__sc0), "r" (__sc4), \
          "r" (__sc5), "r" (__sc6),  \
	  "r" (__sc7) \
	: "memory" ); \
__syscall_return(type,__sc0); \
}

#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5) \
type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) \
{ \
register long __sc3 __asm__ ("r3") = __NR_##name; \
register long __sc4 __asm__ ("r4") = (long) arg1; \
register long __sc5 __asm__ ("r5") = (long) arg2; \
register long __sc6 __asm__ ("r6") = (long) arg3; \
register long __sc7 __asm__ ("r7") = (long) arg4; \
register long __sc0 __asm__ ("r0") = (long) arg5; \
__asm__ __volatile__ ("trapa	%1" \
	: "=z" (__sc0) \
	: "i" (__SH_SYSCALL_TRAP_BASE + 5), "0" (__sc0), "r" (__sc4), \
          "r" (__sc5), "r" (__sc6), "r" (__sc7), "r" (__sc3) \
	: "memory" ); \
__syscall_return(type,__sc0); \
}

#ifndef __SH_SYSCALL6_TRAPA
#define __SH_SYSCALL6_TRAPA __SH_SYSCALL_TRAP_BASE + 6
#endif

/* Add in _syscall6 which is not in the kernel header */
#define _syscall6(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5,type6,arg6) \
type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6) \
{ \
register long __sc3 __asm__ ("r3") = __NR_##name; \
register long __sc4 __asm__ ("r4") = (long) arg1; \
register long __sc5 __asm__ ("r5") = (long) arg2; \
register long __sc6 __asm__ ("r6") = (long) arg3; \
register long __sc7 __asm__ ("r7") = (long) arg4; \
register long __sc0 __asm__ ("r0") = (long) arg5; \
register long __sc1 __asm__ ("r1") = (long) arg6; \
__asm__ __volatile__ ("trapa	%1" \
	: "=z" (__sc0) \
	: "i" (__SH_SYSCALL6_TRAPA), "0" (__sc0), "r" (__sc4), \
          "r" (__sc5), "r" (__sc6), "r" (__sc7), "r" (__sc3), "r" (__sc1) \
	: "memory" ); \
__syscall_return(type,__sc0); \
}

#endif /* __ASSEMBLER__ */
#endif /* _BITS_SYSCALLS_H */

