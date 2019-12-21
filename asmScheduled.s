	.file	1 "asm.c"

 # GNU C 2.6.3 [AL 1.1, MM 40, tma 0.1] SimpleScalar running sstrix compiled by GNU C

 # Cc1 defaults:
 # -mgas -mgpOPT

 # Cc1 arguments (-G value = 8, Cpu = default, ISA = 1):
 # -quiet -dumpbase -o

gcc2_compiled.:
__gnu_compiled_c:
	.text
	.align	2
	.globl	_start

	.comm	x,4

	.text

	.loc	1 3
	.ent	_start
_start:
subu $sp,$sp,24
li $2,0x00000001
sw   $fp,16($sp)
move $fp,$sp
sw $4,24($fp)
sw $5,28($fp)
sw $2,0($fp)
