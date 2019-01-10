;/*****************************************************************************
;*   startup.s: startup file for NXP LPC230x Family Microprocessors
;*
;*   Copyright(C) 2006, NXP Semiconductor
;*   All rights reserved.
;*
;*   History
;*   2006.09.01  ver 1.00    Prelimnary version, first Release
;*
;*****************************************************************************/
	PRESERVE8

;/*
; *  The STARTUP.S code is executed after CPU Reset. This file may be 
; *  translated with the following SET symbols. In uVision these SET 
; *  symbols are entered under Options - ASM - Define.
; *
; *  REMAP: when set the startup code initializes the register MEMMAP 
; *  which overwrites the settings of the CPU configuration pins. The 
; *  startup and interrupt vectors are remapped from:
; *     0x00000000  default setting (not remapped)
; *     0x40000000  when RAM_MODE is used
; *
; *  RAM_MODE: when set the device is configured for code execution
; *  from on-chip RAM starting at address 0x40000000. 
; */


; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F

I_Bit           EQU     0x80            ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40            ; when F bit is set, FIQ is disabled


;// <h> Stack Configuration (Stack Sizes in Bytes)
;//   <o0> Undefined Mode      <0x0-0xFFFFFFFF:8>
;//   <o1> Supervisor Mode     <0x0-0xFFFFFFFF:8>
;//   <o2> Abort Mode          <0x0-0xFFFFFFFF:8>
;//   <o3> Fast Interrupt Mode <0x0-0xFFFFFFFF:8>
;//   <o4> Interrupt Mode      <0x0-0xFFFFFFFF:8>
;//   <o5> User/System Mode    <0x0-0xFFFFFFFF:8>
;// </h>

UND_Stack_Size  EQU     0x00000000
SVC_Stack_Size  EQU     0x00000100
ABT_Stack_Size  EQU     0x00000000
FIQ_Stack_Size  EQU     0x00000000
IRQ_Stack_Size  EQU     0x00000120               ;每层嵌套需要9个字堆栈，允许8层嵌套
USR_Stack_Size  EQU     0x00000200

Stack_Size      EQU     (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                         FIQ_Stack_Size + IRQ_Stack_Size + USR_Stack_Size)

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size

StackUsr        EQU     Stack_Mem+USR_Stack_Size

Stack_Top       EQU     Stack_Mem + Stack_Size

								EXPORT  StackUsr        ;声明为外部标号，供IRQ.S调用。
;// <h> Heap Configuration
;//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF>
;// </h>

Heap_Size       EQU     0x00000001
   						
                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
Heap_Mem        SPACE   Heap_Size

; Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

;引入的外部标号在这声明
    						IMPORT  FIQ_Exception                   ;快速中断异常处理程序
    						IMPORT  __main                          ;C语言主程序入口 
    						IMPORT  TargetResetInit                 ;目标板基本初始化
    						IMPORT  SoftwareInterrupt               ;软件中断的处理函数
    						
                AREA    RESET, CODE, READONLY
                ARM

; Exception Vectors
;  Mapped to Address 0.
;  Absolute addressing mode must be used.
;  Dummy Handlers are implemented as infinite loops which can be modified.

;;中断向量表
;;对于1.未定义指令 2.预取指中止 3.数据中止三种异常不做处理
;;
Vectors         LDR     PC, Reset_Addr         
                LDR     PC, Undef_Addr
                LDR     PC, SWI_Addr
                LDR     PC, PAbt_Addr
                LDR     PC, DAbt_Addr
                NOP                            ; Reserved Vector 
;               LDR     PC, IRQ_Addr
                LDR     PC, [PC, #-0x0120]     ; Vector from VicVectAddr
                LDR     PC, FIQ_Addr

Reset_Addr      DCD     Reset_Handler
Undef_Addr      DCD     Undef_Handler
SWI_Addr        DCD     SoftwareInterrupt
PAbt_Addr       DCD     PAbt_Handler
DAbt_Addr       DCD     DAbt_Handler
                DCD		0xB9206E28             ; Reserved Address 
;IRQ_Addr       DCD     IRQ_Handler
FIQ_Addr        DCD     FIQ_Handler

Undef_Handler   B       Undef_Handler
;SWI_Handler    B       SWI_Handler
PAbt_Handler    B       PAbt_Handler
DAbt_Handler    B       DAbt_Handler
;IRQ_Handler    B       IRQ_Handler
FIQ_Handler
								STMFD   SP!, {R0-R3, LR}
        				BL      FIQ_Exception
        				LDMFD   SP!, {R0-R3, LR}
        				SUBS    PC,  LR,  #4


; Reset Handler		   
                EXPORT  Reset_Handler
Reset_Handler   

; Setup Stack for each mode
                LDR     R0, =Stack_Top

;  Enter Undefined Instruction Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #UND_Stack_Size

;  Enter Abort Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #ABT_Stack_Size

;  Enter FIQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #FIQ_Stack_Size

;  Enter IRQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #IRQ_Stack_Size

;  Enter Supervisor Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #SVC_Stack_Size

;  Enter User Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_USR
                MOV     SP, R0
                SUB     SL, SP, #USR_Stack_Size
				
;				IMPORT	TargetResetInit
								BL		TargetResetInit        ;在target.c文件中

; Enter the C code

;                IMPORT  __main
                LDR     R0, =__main
                BX      R0


; User Initial Stack & Heap

;;函数说明参考RV_CC.PDF文件P291
;;function:  __user_initial_stackheap
;;description:初始化堆栈(stack)和堆(heap),函数采用双存储器区域。
;;parameter:r0,sp,r2
;;return value:r0--堆的基址（heap base in r0）
;;r1--堆栈基址，堆栈区域的最高地址
;;r2--堆的限制地址(heap limit in r2)
;;r3--堆栈限制地址，堆栈区域的最低地址
;;

                AREA    |.text|, CODE, READONLY

                IMPORT  __use_two_region_memory           ;select memory model of two memory region
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + USR_Stack_Size)
                LDR     R2, = (Heap_Mem +      Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                END
