.data
	digite: 	.asciiz "Digite o valor a ser calculado o fatorial: "
	resultado:	.asciiz "Resultado: "

.text
# Código principal
	li	$v0, 4		# Comando para escrever string no console
	la	$a0, digite	# "Digite o valor a ser calculado o fatorial: " será escrito
	syscall			
	
	li	$v0, 5		# Comando para ler inteiro do teclado
	syscall
	
	move	$a0, $v0	# Passa o valor lido para o argumento $a0 do procedimento "fatorial"
	jal	fatorial	# Chama o procedimento "fatorial"
	move	$s5, $v0
	
	li	$v0, 4		# Comando para escrever string no console
 	la	$a0, resultado	# "Resultado: " será escrito
 	syscall
 	
  	li	$v0, 1		# Comando para escrever inteiro no console
  	move 	$a0, $s5	# Valor a ser escrito no console: fatorial do número lido
  	syscall
	
	li	$v0, 10		# Comando para encerrar o programa
	syscall			# Programa é encerrado


  fatorial:
	slti	$t1, $a0, 2	# $t1 = 1 se $a0 < 2
	beq	$t1, $zero, l1	# Vai para o label "l1" se $a0 >= 2
	
	li	$v0, 1		# Retorno $v0 inicializa com 1    -->   é o fatorial do $a0 atual
	jr	$ra		# Volta para o chamador
	
  l1:
	addi	$sp, $sp, -8	# Decrementa o $sp
	sw	$a0, 4($sp)	# Salva o argumento $a0 atual na pilha
	sw	$ra, 0($sp)	# Salva o endereço de retorno na pilha
	
	subi	$a0, $a0, 1	# Decrementa o argumento $a0 em 1 para ser o argumento do novo procedimento "fatorial"
	jal	fatorial	# Chama "fatorial" recursivamente
	
	# Restaura a pilha
	lw	$ra, 0($sp)	# Recupera o endereço de retorno
	lw	$a0, 4($sp)	# Recupera o argumento $a0 do procedimento atual
	addi	$sp, $sp, 8	# Incrementa o $sp
	
	mul	$v0, $v0, $a0	# $v0 atual = $v0 anterior * $a0 atual   -->  $v0 atual é o fatorial do $a0 atual
	jr	$ra		# Volta para o chamador
