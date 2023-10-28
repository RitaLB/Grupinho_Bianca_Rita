.data
	digite: 	.asciiz "Digite o valor a ser calculado o fatorial: "
	resultado:	.asciiz "Resultado: "

.text

	li	$v0, 4		# Comando para escrever string no console
	la	$a0, digite	# "Digite o valor a ser calculado o fatorial: " será escrito
	syscall			

	
	li	$v0, 5		# Comando para ler inteiro do teclado
	syscall
	
	move	$a0, $v0	# $t0 = valor lido
	jal	fatorial
	move	$s5, $v0
	
	li	$v0, 4		# Comando para escrever string no console
 	la	$a0, resultado	# "Resultado: " será escrito
 	syscall
 	
  	li	$v0, 1		# Comando para escrever inteiro no console
  	move 	$a0, $s5	# Valor a ser escrito no console: fatorial do número lido
  	syscall
	
	li	$v0, 10
	syscall


  fatorial:
	slti	$t1, $a0, 1
	beq	$t1, $zero, label1
	
	li	$v0, 1
	jr	$ra
	
  label1:
	addi	$sp, $sp, -8
	sw	$a0, 4($sp)
	sw	$ra, 0($sp)
	
	subi	$a0, $a0, 1
	jal	fatorial
	
	lw	$ra, 0($sp)
	lw	$a0, 4($sp)
	addi	$sp, $sp, 8

	mul	$v0, $v0, $a0
	jr	$ra
