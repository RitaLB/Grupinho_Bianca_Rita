.data
	x: .double

.text

	la	$s0, x		# s0 = endereço de x
	
	# lendo ângulo x do teclado
	li	$v0, 7		# comando para ler double
	syscall
	sdc1	$f0, 0($s0)	# salva valor lido na memória  (na variável x)
	
	# chamando função para calcular o seno do valor lido (x)
	move	$a0, $s0	# passa endereço de x como argumento a0 para o procedimento calcula_seno
	jal	calcula_seno
	
	ldc1	$f2, 0($v0)	# carrega o resultado do procedimento calcula_seno através do endereço retornado em $v0
				# $f2 = sen(x)
	
	# escrevendo o resultado no console
	li	$v0, 3		# comando para escrever double
	mov.d	$f12, $f2	# argumento $f12 é $f2 = sen(x)
	syscall
	
	# encerra o programa
	li	$v0, 10
	syscall

calcula_seno:

	ldc1	$f2, 0($a0)	# $f2 = x
	
	li	$s1, 0		# $s1 = n
	
	# salvando $ra e $a0 na pilha
	addi	$sp, $sp, -8
	sw	$ra, 4($sp)
	sw	$a0, 0($sp)
	
	# alocando dinâmicamente 16 bytes na memória heap para guardar o resultado (em double) dos procedimentos fatorial e expoente
	li	$v0, 9		
	li	$a0, 16
	syscall
	move	$s5, $v0	# $s5 = endereço heap
	
	
  Loop_somatorio:
	
	move	$a0, $s1	# argumento $a0 = n no procedimento sinal
	jal	sinal		# chama o procedimento que calcula (-1)^n
	move	$s2, $v0	# move retorno do procedimento sinal para $s2 --> $s2 = (-1)^n
	
	
	add	$t0, $s1, $s1	# $t0 = n + n = 2n
	addi	$a0, $t0, 1	# argumento $a0 = 2n + 1 no procedimento fatorial
	move	$a1, $s5	# argumento $a1 = endereço da heap que guardará o resultado do fatorial
	jal	fatorial	# chama o procedimento que calcula (2n + 1)!
	
	
	lw	$a0, 0($sp)	# argumento $a0 é o endereço de x (esse endereço está salvo na pilha) no procedimento expoente
	add	$t0, $s1, $s1
	addi	$a1, $t0, 1	# argumento $a1 = 2n + 1 
	move	$a2, $s5	# argumento a2 = endereço da heap que guardará o resultado de x^(2n+1)
	jal	expoente	# chama o procedimento que calcula x^(2n+1)
	
	
	# cálculo de [(-1)^n * x^(2n+1)]/(2n + 1)!
	
	mtc1.d	$s2, $f2	# coloca (-1)^n em $f2 para fazer os cálculos acima em double
	cvt.d.w	$f2, $f2	# converte $f2 de word para double
	
	ldc1	$f4, 0($s5)	# carrega (2n+1)! da memória heap e coloca em $f4  --> f4 = (2n+1)!
	ldc1	$f6, 8($s5)	# carrega x^(2n+1) da memória heap e coloca em $f6  --> f6 = x^(2n+1)
	
	div.d	$f8, $f2, $f4	# $f8 = (-1)^n / (2n+1)!
	mul.d	$f8, $f8, $f6	# $f8 = [(-1)^n / (2n+1)!] * x^(2n+1)

	# somatório
	add.d	$f10, $f10, $f8  # f10 = resultado do somatorio
	
	
	addi	$s1, $s1, 1	# n++
	bne	$s1, 20, Loop_somatorio	  # se n != 20 volta para o loop
	
	
	# sai do loop
	lw	$a0, 0($sp)
	addi	$sp, $sp, 4
	
	# alocando dinâmicamente 8 bytes na memória heap para guardar o resultado (em double) do somatório
	li	$v0, 9
  	li	$a0, 8
  	syscall
  	sdc1	$f10, 0($v0)	# salva o resultado na memória heap
  				# retorno $v0 é o endereço da memória onde o resultado do somatório (seno(x)) está salvo
  	
  	
	lw	$a0, 0($sp)	# restaura $a0 armazenado na pilha
	lw	$ra, 0($sp)	# restaura $ra armazenado na pilha
	addi	$sp, $sp, 8	# incrementa $sp em 2 words
	jr	$ra


# Procedimento sinal
sinal:
	li	$t0, 1		# $t0 = resultado da operação
	li	$t1, 0		# $t1 = contador
	li	$t2, -1		# $t2 = -1
	
  verificacao_loop:
  	slt	$t3, $t1, $a0	# $t3 = 1 se contador < n
  	bne	$t3, $zero, loop_sinal	# vai para o loop se $t3 != 0, ou seja, se contador < n
  	
  	move	$v0, $t0	# retorno $v0 como o resultado da operação
  	jr	$ra
  	
  loop_sinal:
  	mul	$t0, $t0, $t2	# resultado = resultado anterior * (-1)
  	addi	$t1, $t1, 1	# contador++
  	j	verificacao_loop



# Procedimento fatorial
fatorial:
	
	mtc1.d	$a0, $f2	# $a0 vai ser usado para controlar os loops
	cvt.d.w	$f2, $f2	# $f2 inicializa com 2n + 1 em double, ele será subtraído 1 a cada iteração para fazer a multiplicação
	mov.d	$f4, $f2	# $f4 inicializa com 2n + 1 em double, ele será o resultado do fatorial
	
	li	$t0, -1
	mtc1.d	$t0, $f6
	cvt.d.w	$f6, $f6	# $f6 = -1 em double
	
  verificacao_loop_fat:
	slti	$t3, $a0, 2	# $t3 = 1 se $a0 < 2
	beq	$t3, $zero, loop_fat	# vai para loop_fat se $t3 = 0, ou seja, se $a0 >= 2
	
	sdc1	$f4, 0($a1)	# salva o resultado na memória heap
	jr	$ra
	
  loop_fat:
  	add.d	$f2, $f2, $f6	# $f2 = $f2 - 1
	mul.d	$f4, $f4, $f2	# $f4 = $f4 * $f2
	addi	$a0, $a0, -1	# $a0--
	j	verificacao_loop_fat


# Procedimento expoente
expoente:
	ldc1	$f2, 0($a0)	# $f2 = x
	
	li	$t0, 1		
	mtc1.d	$t0, $f4
	cvt.d.w	$f4, $f4	# f4 inicializa com 1, será o resultado da operação
	
	li	$t1, 0		# t1 = contador
	
  verificacao_loop_exp:
  	slt	$t3, $t1, $a1	# $t3 = 1 se contador < 2n+1
  	bne	$t3, $zero, loop_exp	# vai para loop_exp se $t3 != 0, ou seja, se contador < 2n+1
  	
  	sdc1	$f4, 8($a2)	# salva o resultado na memória heap
  	jr	$ra
  	
  loop_exp:
  	mul.d	$f4, $f4, $f2	# f4 = $f4 * x
  	addi	$t1, $t1, 1	# contador++
  	j	verificacao_loop_exp
	



