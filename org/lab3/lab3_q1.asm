.data
	x: .double 428135971041
	resultado: .double 0
.text
	
	la	$a0, x		#$a0 =  endereço de x
	
	# Recebendo input do usiario para valor da variavel n
	
	li	$v0, 5		# Comando para ler inteiro
	syscall			# O valor digitado é salvo em $v0
	move	$a1, $v0 	# movendo valor recebido para o registrador de parâmero $a1
	
	# Iniciando função
	jal 	raiz_aproximada
	
	j	exit
	
raiz_aproximada:
	ldc1	$f0, 0($a0)		# $f0 = valor de x !! antes tava l.d
	move	$t0, $a1		# $t0 = valor de n
	
	
	li	$t1, 1			
	mtc1.d	$t1, $f2		# $f2 = estimativa = 1 .
	cvt.d.w	$f2, $f2
	
	li	$t1, 2			
	mtc1.d	$t1, $f4 
	cvt.d.w	$f4, $f4		# $f4 = 2
	
	
	li	$t1, 0			# $t1 é o contador do loop
	
   Loop:
	div.d	$f6, $f0, $f2		# $f6 = $f0 / $f2  ---- $f6 = x / estimativa
	add.d	$f6, $f6, $f2		# $f6 = $f6 + $f2 ---- $f4 = resultado linha de cima + estimativa
	div.d	$f2, $f6, $f4		# $f2 = $f6 / $f4 ---- $f2 = resultado linha de cima /2
	addi	$t1, $t1, 1		# $t1 = $t1 + 1 ----  contador++
	bne	$t1, $t0, Loop		# Enquanto o número de loops for diferente de n, continua loop
	
	# alocando dinâmicamente 8 bytes na memória heap para guardar o resultado (em double)
	li	$v0, 9			
	li	$a0, 8
	syscall
	sdc1	$f2, 0($v0)		# salva o resultado na memória heap
  					# retorno $v0 é o endereço da memória onde o resultado está salvo
	
	jr	$ra

exit:
	lwc1	$f2, 0($v0)
	la	$t2, resultado		#lembrar: resultado salvo em $f2
	sdc1	$f2, 0($t2)
	
# calculando resposta com a função sqrt.d

	la	$t0, x			# $t0 =  endereço de x
	ldc1	$f0, 0($t0)		# $f0 = valor de x 
	sqrt.d	$f0, $f0		# $f0 = raiz quadrada de x
	
# calculando erro absoluto:

	sub.d	$f4, $f0, $f2
	abs.d	$f4, $f4		#$f4 = erro absoluto
	

