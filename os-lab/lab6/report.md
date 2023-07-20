Operating Systems Lab, Lab 6

Abstract:

Outline for Implementing FlexProject:
XV6 operating system implementation of flexible system calls.
Approach:
Our strategy for implementing and testing flexible system calls for the xv6 operating system is summarised in the following steps:
• Create system call pages to enter information about upcoming or planned system calls (accessible to user processes). (Addition of Feature)
Change the fourth CPU's scheduler to only handle system calls. (Little adjustment)
. Polling is currently used to find system call entries with the status "submitted" on the syscall page; system call scheduling is optimization. • flexsc register() (slight improvement): into the syscall page
• The handler function for flexsc register (Feature Addition). • Flexsc wait() (small adjustment): Runs at least one system call that the process has registered.
Function handler for flexsc wait (Feature Addition), • On xv6, user-level threading will be implemented in accordance with the source code already in place.
flexsc wait() handler function (Feature Addition), • User-level threading on xv6 will be implemented in accordance with previously existing source code. system call registered by the process.
A user on GitHub, wrote this code. It incorporates a thread scheduler and a context-switching system for user-level threading. Adjustments will be made as necessary to implement flexible system calls. (Addition),
• Test case 1: Verify that flexsc register(fundamental )'s features operate as intended.
• Test case 2: To determine whether the functions of flexsc wait() and flexsc register() are coordinated.
• The aforementioned test cases will be used to test new system calls that employ exception-less system calls.