.data
	digite: 	.asciiz "Digite o valor a ser calculado o fatorial: "
	resultado:	.asciiz "Resultado: "

.text

	li	$v0, 4		# Comando para escrever string no console
	la	$a0, digite	# "Digite o valor a ser calculado o fatorial: " será escrito
	syscall			
	
	#   --- início calculo do fatorial ---
	
	li	$v0, 5		# Comando para ler inteiro do teclado
	syscall
	move	$t0, $v0	# $t0 = valor lido
	
	li	$s0, 1		# $s0 será o resultado do fatorial, inicializa com 1

  loop:
	slti	$t1, $t0, 2		# $t1 = 1 se $t0 < 2
	bne	$t1, $zero, exit	# Sai do loop se $t1 != 0, ou seja, se $t1 < 2
	
	mul	$s0, $s0, $t0		# $s0 = $s0 * $t0
	subi	$t0, $t0, 1		# Decrementa $t0
	
	j	loop			# Volta para o loop

 exit:
 	#   --- fim cálculo do fatorial ---
 	
 	li	$v0, 4		# Comando para escrever string no console
 	la	$a0, resultado	# "Resultado: " será escrito
 	syscall
 	
  	li	$v0, 1		# Comando para escrever inteiro no console
  	move 	$a0, $s0	# Valor a ser escrito no console: fatorial do número lido
  	syscall
