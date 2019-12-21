
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
bubblesort:
	sw	$4,40($fp)
	sw	$5,44($fp)
	sw	$6,48($fp)
	lw	$4,44($fp)
	jal	left
	sw	$2,16($fp)
	lw	$4,44($fp)
	jal	right
	sw	$2,20($fp)
	lw	$2,16($fp)
	lw	$3,48($fp)
	slt	$2,$3,$2
	bne	$2,$0,$L5
	lw	$2,16($fp)
	move	$3,$2
	sll	$2,$3,2
	lw	$3,40($fp)
	addu	$2,$2,$3
	subu	$3,$2,4
	move	$2,$3
	lw	$3,44($fp)
	move	$4,$3
	sll	$3,$4,2
	lw	$4,40($fp)
	addu	$3,$3,$4
	subu	$4,$3,4
	move	$3,$4
	lw	$2,0($2)
	lw	$3,0($3)
	slt	$2,$3,$2
	beq	$2,$0,$L5
	lw	$2,16($fp)
	sw	$2,24($fp)
	j	$L6
$L5:
	lw	$2,44($fp)
	sw	$2,24($fp)
$L6:
	lw	$2,20($fp)
	lw	$3,48($fp)
	slt	$2,$3,$2
	bne	$2,$0,$L7
	lw	$2,20($fp)
	move	$3,$2
	sll	$2,$3,2
	lw	$3,40($fp)
	addu	$2,$2,$3
	subu	$3,$2,4
	move	$2,$3
	lw	$3,24($fp)
	move	$4,$3
	sll	$3,$4,2
	lw	$4,40($fp)
	addu	$3,$3,$4
	subu	$4,$3,4
	move	$3,$4
	lw	$2,0($2)
	lw	$3,0($3)
	slt	$2,$3,$2
	beq	$2,$0,$L7
	lw	$2,20($fp)
	sw	$2,24($fp)
$L7:
	lw	$2,24($fp)
	lw	$3,44($fp)
	beq	$2,$3,$L8
	lw	$2,24($fp)
	move	$3,$2
	sll	$2,$3,2
	lw	$3,40($fp)
	addu	$2,$2,$3
	subu	$3,$2,4
	move	$2,$3
	lw	$3,0($2)
	sw	$3,28($fp)
	lw	$2,24($fp)
	move	$3,$2
	sll	$2,$3,2
	lw	$3,40($fp)
	addu	$2,$2,$3
	subu	$3,$2,4
	move	$2,$3
	lw	$3,44($fp)
	move	$4,$3
	sll	$3,$4,2
	lw	$4,40($fp)
	addu	$3,$3,$4
	subu	$4,$3,4
	move	$3,$4
	lw	$4,0($3)
	sw	$4,0($2)
	lw	$2,44($fp)
	move	$3,$2
	sll	$2,$3,2
	lw	$3,40($fp)
	addu	$2,$2,$3
	subu	$3,$2,4
	move	$2,$3
	lw	$3,28($fp)
	sw	$3,0($2)
	lw	$4,40($fp)
	lw	$5,24($fp)
	lw	$6,48($fp)
	jal	heapify
