/*
        sysname.c - definition for linux system call 
        Copyright (C) 2003 Skyeye Develop Group
        for help please send mail to <skyeye-developer@lists.sf.linuxforum.net>

        This program is free software; you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation; either version 2 of the License, or
        (at your option) any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with this program; if not, write to the Free Software
        Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/
/*
 * 12/21/2006   Michael.Kang  <blackfin.kang@gmail.com>
 */

#ifndef __SYSNAME_H__
#define __SYSNAME_H__

char * sys_name[] = {
	"NONE",
	" __NR_exit ",
	" __NR_fork ",
	" __NR_read ",
	" __NR_write ",
	" __NR_open ",
	" __NR_close ",
	" __NR_waitpid ",
	" __NR_creat ",
	" __NR_link ",
	" __NR_unlink ",
	" __NR_execve ",
	" __NR_chdir ",
	" __NR_time ",
	" __NR_mknod ",
	" __NR_chmod ",
	" __NR_chown ",
	" __NR_dump ",
	" __NR_oldstat ",
	" __NR_lseek ",
	" __NR_getpid ",
	" __NR_mount ",
	" __NR_umount ",
	" __NR_setuid ",
	" __NR_getuid ",
	" __NR_stime ",
	" __NR_ptrace ",
	" __NR_alarm ",
	" __NR_oldfstat ",
	" __NR_pause ",
	" __NR_utime ",
	" __NR_stty ",
	" __NR_gtty ",
	" __NR_access ",
	" __NR_nice ",
	" __NR_ftime ",
	" __NR_sync ",
	" __NR_kill ",
	" __NR_rename ",
	" __NR_mkdir ",
	" __NR_rmdir ",
	" __NR_dup ",
	" __NR_pipe ",
	" __NR_times ",
	" __NR_prof ",
	" __NR_brk ",
	" __NR_setgid ",
	" __NR_getgid ",
	" __NR_signal ",
	" __NR_geteuid ",
	" __NR_getegid ",
	" __NR_acct ",
	" __NR_umount2 ",
	" __NR_lock ",
	" __NR_ioctl ",
	" __NR_fcntl ",
	" __NR_mpx ",
	" __NR_setpgid ",
	" __NR_ulimit ",
	" __NR_oldolduname ",
	" __NR_umask ",
	" __NR_chroot ",
	" __NR_ustat ",
	" __NR_dup2 ",
	" __NR_getppid ",
	" __NR_getpgrp ",
	" __NR_setsid ",
	" __NR_sigaction ",
	" __NR_sgetmask ",
	" __NR_ssetmask ",
	" __NR_setreuid ",
	" __NR_setregid ",
	" __NR_sigsuspend ",
	" __NR_sigpending ",
	" __NR_sethostname ",
	" __NR_setrlimit ",
	" __NR_old_getrlimit ",
	" __NR_getrusage ",
	" __NR_gettimeofday ",
	" __NR_settimeofday ",
	" __NR_getgroups ",
	" __NR_setgroups ",
	" __NR_select ",
	" __NR_symlink ",
	" __NR_oldlstat ",
	" __NR_readlink ",
	" __NR_uselib ",
	" __NR_swapon ",
	" __NR_reboot ",
	" __NR_readdir ",
	" __NR_mmap ",
	" __NR_munmap ",
	" __NR_truncate ",
	" __NR_ftruncate ",
	" __NR_fchmod ",
	" __NR_fchown ",
	" __NR_getpriority ",
	" __NR_setpriority ",
	" __NR_profil ",
	" __NR_statfs ",
	" __NR_fstatfs ",
	" __NR_ioperm ",
	" __NR_socketcall ",
	" __NR_syslog ",
	" __NR_setitimer ",
	" __NR_getitimer ",
	" __NR_stat ",
	" __NR_lstat ",
	" __NR_fstat ",
	" __NR_olduname ",
	"NONE",
	" __NR_vhangup ",
	"NONE",
	"NONE",
	" __NR_wait4 ",
	" __NR_swapoff ",
	" __NR_sysinfo ",
	" __NR_ipc ",
	" __NR_fsync ",
	" __NR_sigreturn ",
	" __NR_clone ",
	" __NR_setdomainname ",
	" __NR_uname ",
	" __NR_cacheflush ",
	" __NR_adjtimex ",
	" __NR_mprotect ",
	" __NR_sigprocmask ",
	" __NR_create_module ",
	" __NR_init_module ",
	" __NR_delete_module ",
	" __NR_get_kernel_syms ",
	" __NR_quotactl ",
	" __NR_getpgid ",
	" __NR_fchdir ",
	" __NR_bdflush ",
	" __NR_sysfs ",
	" __NR_personality ",
	" __NR_afs_syscall ",	/* Syscall for Andrew File System */
	" __NR_setfsuid ",
	" __NR_setfsgid ",
	" __NR__llseek ",
	" __NR_getdents ",
	" __NR__newselect ",
	" __NR_flock ",
	" __NR_msync ",
	" __NR_readv ",
	" __NR_writev ",
	" __NR_getsid ",
	" __NR_fdatasync ",
	" __NR__sysctl ",
	" __NR_mlock ",
	" __NR_munlock ",
	" __NR_mlockall ",
	" __NR_munlockall ",
	" __NR_sched_setparam ",
	" __NR_sched_getparam ",
	" __NR_sched_setscheduler ",
	" __NR_sched_getscheduler ",
	" __NR_sched_yield ",
	" __NR_sched_get_priority_max ",
	" __NR_sched_get_priority_min ",
	" __NR_sched_rr_get_interval ",
	" __NR_nanosleep ",
	" __NR_mremap ",
	" __NR_setresuid ",
	" __NR_getresuid ",
	" __NR_query_module ",
	" __NR_poll ",
	" __NR_nfsservctl ",
	" __NR_setresgid ",
	" __NR_getresgid ",
	" __NR_prctl ",
	" __NR_rt_sigreturn ",
	" __NR_rt_sigaction ",
	" __NR_rt_sigprocmask ",
	" __NR_rt_sigpending ",
	" __NR_rt_sigtimedwait ",
	" __NR_rt_sigqueueinfo ",
	" __NR_rt_sigsuspend ",
	" __NR_pread ",
	" __NR_pwrite ",
	" __NR_lchown ",
	" __NR_getcwd ",
	" __NR_capget ",
	" __NR_capset ",
	" __NR_sigaltstack ",
	" __NR_sendfile ",
	" __NR_getpmsg ",
	" __NR_putpmsg ",
	" __NR_vfork ",
	" __NR_getrlimit ",
	" __NR_mmap2 ",
	" __NR_truncate64 ",
	" __NR_ftruncate64 ",
	" __NR_stat64 ",
	" __NR_lstat64 ",
	" __NR_fstat64 ",
	" __NR_chown32 ",
	" __NR_getuid32 ",
	" __NR_getgid32 ",
	" __NR_geteuid32 ",
	" __NR_getegid32 ",
	" __NR_setreuid32 ",
	" __NR_setregid32 ",
	" __NR_getgroups32 ",
	" __NR_setgroups32 ",
	" __NR_fchown32 ",
	" __NR_setresuid32 ",
	" __NR_getresuid32 ",
	" __NR_setresgid32 ",
	" __NR_getresgid32 ",
	" __NR_lchown32 ",
	" __NR_setuid32 ",
	" __NR_setgid32 ",
	" __NR_setfsuid32 ",
	" __NR_setfsgid32 ",
	" __NR_pivot_root ",
	" __NR_mincore ",
	" __NR_madvise ",
	" __NR_getdents64 ",
	" __NR_fcntl64 ",
	" __NR_gettid ",
	" __NR_readahead ",
	" __NR_setxattr ",
	" __NR_lsetxattr ",
	" __NR_fsetxattr ",
	" __NR_getxattr ",
	" __NR_lgetxattr ",
	" __NR_fgetxattr ",
	" __NR_listxattr ",
	" __NR_llistxattr ",
	" __NR_flistxattr ",
	" __NR_removexattr ",
	" __NR_lremovexattr ",
	" __NR_fremovexattr ",
	" __NR_tkill ",
	" __NR_sendfile64 ",
	" __NR_futex ",
	" __NR_sched_setaffinity ",
	" __NR_sched_getaffinity ",
	" __NR_set_thread_area ",
	" __NR_get_thread_area ",
	" __NR_io_setup ",
	" __NR_io_destroy ",
	" __NR_io_getevents ",
	" __NR_io_submit ",
	" __NR_io_cancel ",
	" __NR_fadvise64 ",
	" __NR_exit_group ",
	" __NR_lookup_dcookie ",

	" __NR_syscall "
};

#endif