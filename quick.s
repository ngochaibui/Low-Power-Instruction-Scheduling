	.file	1 "quick.c"

 # GNU C 2.6.3 [AL 1.1, MM 40, tma 0.1] SimpleScalar running sstrix compiled by GNU C

 # Cc1 defaults:
 # -mgas -mgpOPT

 # Cc1 arguments (-G value = 8, Cpu = default, ISA = 1):
 # -quiet -dumpbase -o

gcc2_compiled.:
__gnu_compiled_c:
	.globl	a
	.data
	.align	2
a:
	.word	2078917053
	.word	1027100827
	.word	-1392230017
	.word	-742093418
	.word	1099951567
	.word	-128898341
	.word	813528929
	.word	-1528577169
	.word	766270699
	.word	1510320440
	.word	-424082616
	.word	1098183682
	.word	-1167412033
	.word	-1504204375
	.word	-1989899610
	.word	-1675923108
	.word	1213147837
	.word	-105255902
	.word	1353778505
	.word	2013649480
	.word	-413516970
	.word	-1402973885
	.word	1440466707
	.word	-1173756985
	.word	-508387316
	.word	1642837685
	.word	154523136
	.word	-1443447816
	.word	1605135681
	.word	-1844911269
	.word	-1877807267
	.word	-295746485
	.word	-2022173009
	.word	1303742040
	.word	899131941
	.word	1785335569
	.word	907175364
	.word	-1261856717
	.word	1745777927
	.word	-1888071466
	.word	48433401
	.word	304920680
	.word	348303940
	.word	-809932359
	.word	208787970
	.word	1568675693
	.word	266772940
	.word	-186195077
	.word	-1275556827
	.word	1871172724
	.word	-2007512461
	.word	-2038293562
	.word	1891386329
	.word	1247304975
	.word	-1440796684
	.word	579587572
	.word	1261483377
	.word	-1189406744
	.word	-254018884
	.word	-731740357
	.word	1788268214
	.word	433233439
	.word	2109864544
	.word	-1847842563
	.word	-782898323
	.word	457882831
	.word	1532354806
	.word	404219416
	.word	-585593712
	.word	618454448
	.word	1010757900
	.word	876213618
	.word	2082550272
	.word	-412938701
	.word	1982435068
	.word	1783300476
	.word	-307743722
	.word	1530777140
	.word	-1831395019
	.word	488944891
	.word	-293735261
	.word	-1109736830
	.word	1513900641
	.word	-1780090263
	.word	946006977
	.word	1049400181
	.word	36406206
	.word	-65961140
	.word	-535062974
	.word	1800004220
	.word	523904750
	.word	923108080
	.word	1504871315
	.word	2018281851
	.word	2136819798
	.word	-793333398
	.word	1306570817
	.word	934220434
	.word	1686379655
	.word	1601294739
	.text
	.align	2
	.globl	swap
	.align	2
	.globl	partition
	.align	2
	.globl	quicksort
	.align	2
	.globl	_start

	.text

	.loc	1 7
	.ent	swap
swap:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, extra= 0
	.mask	0x40000000,-8
	.fmask	0x00000000,0
	subu	$sp,$sp,16
	sw	$fp,8($sp)
	move	$fp,$sp
	sw	$4,16($fp)
	sw	$5,20($fp)
	sw	$6,24($fp)
	lw	$2,20($fp)
	move	$3,$2
	sll	$2,$3,2
	lw	$3,16($fp)
	addu	$2,$2,$3
	move	$3,$2
	lw	$2,0($3)
	sw	$2,0($fp)
	lw	$2,20($fp)
	move	$3,$2
	sll	$2,$3,2
	lw	$4,16($fp)
	addu	$3,$2,$4
	move	$2,$3
	lw	$3,24($fp)
	move	$4,$3
	sll	$3,$4,2
	lw	$4,16($fp)
	addu	$3,$3,$4
	move	$4,$3
	lw	$3,0($4)
	sw	$3,0($2)
	lw	$2,24($fp)
	move	$3,$2
	sll	$2,$3,2
	lw	$3,16($fp)
	addu	$2,$2,$3
	move	$3,$2
	lw	$2,0($fp)
	sw	$2,0($3)
$L1:
	move	$sp,$fp			# sp not trusted here
	lw	$fp,8($sp)
	addu	$sp,$sp,16
	j	$31
	.end	swap

	.loc	1 17
	.ent	partition
partition:
	.frame	$fp,40,$31		# vars= 16, regs= 2/0, args= 16, extra= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	subu	$sp,$sp,40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	sw	$4,40($fp)
	sw	$5,44($fp)
	sw	$6,48($fp)
	lw	$2,44($fp)
	lw	$4,48($fp)
	addu	$3,$2,$4
	sra	$2,$3,1
	lw	$4,40($fp)
	lw	$5,44($fp)
	move	$6,$2
	jal	swap
	lw	$2,44($fp)
	sw	$2,24($fp)
	lw	$2,44($fp)
	addu	$3,$2,1
	sw	$3,20($fp)
$L3:
	lw	$2,20($fp)
	lw	$3,48($fp)
	slt	$2,$3,$2
	beq	$2,$0,$L6
	j	$L4
$L6:
	lw	$2,20($fp)
	move	$3,$2
	sll	$2,$3,2
	lw	$4,40($fp)
	addu	$3,$2,$4
	move	$2,$3
	lw	$3,44($fp)
	move	$4,$3
	sll	$3,$4,2
	lw	$4,40($fp)
	addu	$3,$3,$4
	move	$4,$3
	lw	$2,0($2)
	lw	$3,0($4)
	slt	$2,$2,$3
	beq	$2,$0,$L7
	lw	$2,24($fp)
	addu	$3,$2,1
	move	$2,$3
	sw	$2,24($fp)
	lw	$4,40($fp)
	move	$5,$2
	lw	$6,20($fp)
	jal	swap
$L7:
$L5:
	lw	$3,20($fp)
	addu	$2,$3,1
	move	$3,$2
	sw	$3,20($fp)
	j	$L3
$L4:
	lw	$4,40($fp)
	lw	$5,44($fp)
	lw	$6,24($fp)
	jal	swap
	lw	$2,24($fp)
	j	$L2
$L2:
	move	$sp,$fp			# sp not trusted here
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addu	$sp,$sp,40
	j	$31
	.end	partition

	.loc	1 29
	.ent	quicksort
quicksort:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, extra= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	subu	$sp,$sp,32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	sw	$4,32($fp)
	sw	$5,36($fp)
	sw	$6,40($fp)
	lw	$2,36($fp)
	lw	$3,40($fp)
	slt	$2,$2,$3
	beq	$2,$0,$L9
	lw	$4,32($fp)
	lw	$5,36($fp)
	lw	$6,40($fp)
	jal	partition
	sw	$2,16($fp)
	lw	$3,16($fp)
	subu	$2,$3,1
	lw	$4,32($fp)
	lw	$5,36($fp)
	move	$6,$2
	jal	quicksort
	lw	$3,16($fp)
	addu	$2,$3,1
	lw	$4,32($fp)
	move	$5,$2
	lw	$6,40($fp)
	jal	quicksort
$L9:
$L8:
	move	$sp,$fp			# sp not trusted here
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addu	$sp,$sp,32
	j	$31
	.end	quicksort

	.loc	1 42
	.ent	_start
_start:
	.frame	$fp,24,$31		# vars= 0, regs= 2/0, args= 16, extra= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	subu	$sp,$sp,24
	sw	$31,20($sp)
	sw	$fp,16($sp)
	move	$fp,$sp
	la	$4,a
	move	$5,$0
	li	$6,0x00000063		# 99
	jal	quicksort
$L10:
	move	$sp,$fp			# sp not trusted here
	lw	$31,20($sp)
	lw	$fp,16($sp)
	addu	$sp,$sp,24
	j	$31
	.end	_start
