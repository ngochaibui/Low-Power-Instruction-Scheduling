
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
move $12,$4
move $13,$5
move $14,$6
move $4,$13
jal	left
move $15,$2
move $4,$13
jal	right
move $19,$2
move $2,$15
move $3,$14
slt	$2,$3,$2
bne	$2,$0,$L5
move $2,$15
move	$3,$2
sll	$2,$3,2
move $3,$12
addu	$2,$2,$3
subu	$3,$2,4
move	$2,$3
move $3,$13
move	$4,$3
sll	$3,$4,2
move $4,$12
addu	$3,$3,$4
subu	$4,$3,4
move	$3,$4
lw	$2,0($2)
lw	$3,0($3)
slt	$2,$3,$2
beq	$2,$0,$L5
move $2,$15
move $20,$2
j	$L6
$L5:
move $2,$13
move $20,$2
$L6:
move $2,$19
move $3,$14
slt	$2,$3,$2
bne	$2,$0,$L7
move $2,$19
move	$3,$2
sll	$2,$3,2
move $3,$12
addu	$2,$2,$3
subu	$3,$2,4
move	$2,$3
move $3,$20
move	$4,$3
sll	$3,$4,2
move $4,$12
addu	$3,$3,$4
subu	$4,$3,4
move	$3,$4
lw	$2,0($2)
lw	$3,0($3)
slt	$2,$3,$2
beq	$2,$0,$L7
move $2,$19
move $20,$2
$L7:
move $2,$20
move $3,$13
beq	$2,$3,$L8
move $2,$20
move	$3,$2
sll	$2,$3,2
move $3,$12
addu	$2,$2,$3
subu	$3,$2,4
move	$2,$3
lw	$3,0($2)
sw	$3,28($fp)
move $2,$20
move	$3,$2
sll	$2,$3,2
move $3,$12
addu	$2,$2,$3
subu	$3,$2,4
move	$2,$3
move $3,$13
move	$4,$3
sll	$3,$4,2
move $4,$12
addu	$3,$3,$4
subu	$4,$3,4
move	$3,$4
lw	$4,0($3)
sw	$4,0($2)
move $2,$13
move	$3,$2
sll	$2,$3,2
move $3,$12
addu	$2,$2,$3
subu	$3,$2,4
move	$2,$3
lw	$3,28($fp)
sw	$3,0($2)
move $4,$12
move $5,$20
move $6,$14
jal	heapify
