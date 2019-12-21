	.file	1 "bubble.c"

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
	.globl	bubblesort
	.align	2
	.globl	_start

	.text

	.loc	1 4
	.ent	bubblesort
bubblesort:
	.frame	$fp,24,$31		# vars= 16, regs= 1/0, args= 0, extra= 0
	.mask	0x40000000,-8
	.fmask	0x00000000,0
	subu	$sp,$sp,24
	sw	$fp,16($sp)
	move	$fp,$sp
	sw	$4,24($fp)
	sw	$5,28($fp)
	li	$2,0x00000001		# 1
	sw	$2,0($fp)
$L2:
	lw	$2,0($fp)
	bne	$2,$0,$L4
	j	$L3
$L4:
	sw	$0,0($fp)
	sw	$0,4($fp)
$L5:
	lw	$3,28($fp)
	subu	$2,$3,1
	lw	$3,4($fp)
	slt	$2,$3,$2
	bne	$2,$0,$L8
	j	$L6
$L8:
	lw	$2,4($fp)
	move	$3,$2
	sll	$2,$3,2
	lw	$4,24($fp)
	addu	$3,$2,$4
	move	$2,$3
	lw	$3,4($fp)
	move	$4,$3
	sll	$3,$4,2
	lw	$4,24($fp)
	addu	$3,$3,$4
	addu	$4,$3,4
	move	$3,$4
	lw	$2,0($2)
	lw	$3,0($3)
	slt	$2,$3,$2
	beq	$2,$0,$L9
	lw	$2,4($fp)
	move	$3,$2
	sll	$2,$3,2
	lw	$3,24($fp)
	addu	$2,$2,$3
	move	$3,$2
	lw	$2,0($3)
	sw	$2,8($fp)
	lw	$2,4($fp)
	move	$3,$2
	sll	$2,$3,2
	lw	$4,24($fp)
	addu	$3,$2,$4
	move	$2,$3
	lw	$3,4($fp)
	move	$4,$3
	sll	$3,$4,2
	lw	$4,24($fp)
	addu	$3,$3,$4
	addu	$4,$3,4
	move	$3,$4
	lw	$4,0($3)
	sw	$4,0($2)
	lw	$2,4($fp)
	move	$3,$2
	sll	$2,$3,2
	lw	$3,24($fp)
	addu	$2,$2,$3
	addu	$3,$2,4
	move	$2,$3
	lw	$3,8($fp)
	sw	$3,0($2)
	li	$2,0x00000001		# 1
$L9:
$L7:
	lw	$3,4($fp)
	addu	$2,$3,1
	move	$3,$2
	sw	$3,4($fp)
	j	$L5
$L6:
	j	$L2
$L3:
$L1:
	move	$sp,$fp			# sp not trusted here
	lw	$fp,16($sp)
	addu	$sp,$sp,24
	j	$31
	.end	bubblesort

	.loc	1 22
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
	li	$5,0x00000064		# 100
	jal	bubblesort
$L10:
	move	$sp,$fp			# sp not trusted here
	lw	$31,20($sp)
	lw	$fp,16($sp)
	addu	$sp,$sp,24
	j	$31
	.end	_start