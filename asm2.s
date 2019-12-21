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
	subu	$sp,$sp,16
	move	$2,$3		
	addu	$2,$3,$5
	addu	$2,$3,$11
	subu	$4,$9,$7
	li	$6,0x00000001
	lw	$3,0($sp)
	slt 	$3,$6,$8 
	sw	$3,0($sp)
	move	$3,$2
	sll	$2,$3,2
	la	$6,0x00000001
	lw	$3,16($fp)
	move	$15,$2
	addu	$12,$14,$15
	lw	$2,0($fp)
	lw	$4,20($sp)
	addu	$4,$5,$9
	move	$2,$3		
	addu	$2,$3,$5
	addu	$4,$5,$11
	subu	$4,$9,$7
	li	$6,0x00000003
	lw	$3,0($sp)
	slt 	$16,$17,$18 
	sw	$3,0($sp)
	move	$3,$2
	sll	$2,$3,2
	la	$6,0x00000001
	lw	$3,16($fp)
	addu	$12,$14,$3
	move	$15,$2
	lw	$2,0($fp)
	lw	$4,20($sp)
	addu	$2,$3,$7
	move	$2,$5		
	addu	$2,$3,$5
	addu	$2,$3,$10
	subu	$4,$5,$6
	li	$6,0x00000004
	lw	$3,0($sp)
	slt 	$16,$17,$8 
	sw	$3,0($sp)
	move	$3,$2
	sll	$2,$3,2
	la	$6,0x00000005
	lw	$3,16($fp)
	addu	$12,$14,$13
	move	$13,$2
	lw	$2,0($fp)
	lw	$4,20($sp)
	addu	$4,$5,$3
	lw	$11,20($sp)
	addu	$2,$3,$5
	move	$6,$5		
	addu	$8,$7,$11
	addu	$12,$20,$10
