# 
		.data
print_str:	.asciiz	"Input: "
set_size_str:	.asciiz "Set size: "
max_str:	.asciiz "Max: "
min_str:	.asciiz "Min: "
avg_str:	.asciiz "Average: "

input_str:	.space 1024			# 1023 length string available

cr:		.asciiz "\n"

		.text
main:
		###
		# system call code for $v0 --> prepare parameters --> syscall
		###
		
		# print input waiting string
		li $v0, 4
		la $a0, print_str
		syscall
		
		# get input
		li $v0, 8
		la $a0, input_str		# $a0 : input space
		li $a1, 1024			# $a1 : input space size
		syscall
			
		# initializing variables
		li $s0, 0			# $s0 : temp
		li $s1, 0			# $s1 : sum
		li $s2, 0			# $s2 : max
		li $s3, -1			# $s3 : min
		li $s4, 0			# $s4 : set size
		move $s5, $a0			# $s5 : orig string
		li $s6, 0			# $s6 : string len
		
		###
		# count set size first
		li $t0, 0
		la $t0, 0($s5)			# $t0 : pointer starts from orig string first char
count_size:
		lbu $t1, 0($t0)			# $t1 receives each character
		beq $t1, '}', ret
		bne $t1, ',', pass
		addiu $s4, $s4, 1		# comma cnt ++
	pass:
		addiu $t0, $t0, 1
		addiu $s6, $s6, 1
		j count_size
		
	ret:	
		# set size == comma cnt + 1
		addiu $s4, $s4, 1
		
		# if $s6 == 1, empty set
		beq $s6, 1, empty_set
		
		
		
		# print set size
		li $v0, 4
		la $a0, set_size_str
		syscall
		li $v0, 1
		move $a0, $s4
		syscall
		li $v0, 4
		la $a0, cr
		syscall
		
		###
		# iterate string
		li $t0, 0
		la $t0, 0($s5)
		addiu $t0, $t0, 1			# ignoring first '{'
loop:
		# $t0 holding iteration pointer
		# $t1 holding current iteration character
		lbu $t1, 0($t0)
		
		beq $t1, '}', finish		# check if current char is '}'
		bne $t1, ',', else
		# if comma
		# print current tmp
		li $v0, 1
		move $a0, $s0
		syscall 
		li $v0, 4
		la $a0, cr
		syscall
		# add sum
		addu $s1, $s1, $s0
		
		# max
		sltu $t7, $s2, $s0		# if max < curr
		beq $t7, 0, pass_max
		# update max here
		move $s2, $s0
	pass_max:
		# min
		sltu $t7, $s0, $s3		# if curr < min
		beq $t7, 0, pass_min
		# update min here
		move $s3, $s0
	pass_min:
		# set tmp to 0
		li $s0, 0
		
		j finally
		
	else:
		# if not comma
		# mult 10 to tmp
		mulu $s0, $s0, 10
		mflo $s0
		# add current char to tmp
		subiu $t1, $t1, 48 
		addu $s0, $s0, $t1
	
	finally:
		addiu $t0, $t0, 1
		j loop
		
	finish:
		# current char is '}'
		# final processing and j print_result
		# print current tmp
		li $v0, 1
		move $a0, $s0
		syscall 
		li $v0, 4
		la $a0, cr
		syscall
		# add sum
		addu $s1, $s1, $s0
		
		# max
		sltu $t7, $s2, $s0		# if max < curr
		beq $t7, 0, pass_max_fin
		# update max here
		move $s2, $s0
	pass_max_fin:
		# min
		sltu $t7, $s0, $s3		# if curr < min
		beq $t7, 0, print_result
		# update min here
		move $s3, $s0
		
		j print_result

print_result:
		li $v0, 4
		la $a0, max_str
		syscall
		li $v0, 1
		move $a0, $s2
		syscall
		li $v0, 4
		la $a0, cr
		syscall
		
		
		li $v0, 4
		la $a0, min_str
		syscall
		li $v0, 1
		move $a0, $s3
		syscall
		li $v0, 4
		la $a0, cr
		syscall
		
		# sum = sum / setsize
		divu $s1, $s1, $s4
		
		li $v0, 4
		la $a0, avg_str
		syscall
		li $v0, 1
		move $a0, $s1
		syscall
		li $v0, 4
		la $a0, cr
		syscall
		
		j exit

empty_set:
		# empty set handling
		li $v0, 4
		la $a0, set_size_str
		syscall
		li $v0, 1
		move $a0, $zero
		syscall
		li $v0, 4
		la $a0, cr
		syscall

exit:
		# exit system call
		li $v0, 10
		syscall
