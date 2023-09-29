.data
	A: .float	0.11 0.34 1.23 5.34 0.76 0.65 0.34 0.12 0.87 0.56
	B: .float	7.89 6.87 9.89 7.12 6.23 8.76 8.21 7.32 7.32 8.22
	result_A: .asciiz  "Media de A: "
	result_B: .asciiz  "\nMedia de B: "
	digite:	  .asciiz  "Digite o tamanho dos vetores A e B: "

.text
	
	li $v0, 4 	# Comando para escrever string
	la $a0, digite 	# Carrega string (endereço)
	syscall
	
	# lendo N do teclado
	li	$v0, 5	# Comando para ler inteiro
	syscall
	move	$s0, $v0    # $s0 = N
	
	# calculando média de A
	move	$a0, $s0
	la	$a1, A      # $a1 = end. A
	jal	media
	
	mtc1	$v0, $f12	
	
	li 	$v0, 4 # Comando.
	la 	$a0, result_A # Carrega string (endereço).
	syscall
	
	li	$v0, 2
	syscall			# imprime o a média de A
	
	# Calculando média de B
	move	$a0, $s0
	la	$a1, B      # $a1 = end. B
	jal	media
	
	mtc1	$v0, $f12	
	
	li 	$v0, 4 # Comando.
	la 	$a0, result_B # Carrega string (endereço).
	syscall
	
	li	$v0, 2
	syscall	
	
	li	$v0, 10		# comando para encerrar o programa
	syscall			# encerra o programa

media:
	li	$t0, 0     # t0 = contador
	li	$t1, 0
	mtc1	$t1, $f0   # f0 = somatorio . 
	cvt.s.w	$f0, $f0
	
	mtc1	$a0, $f3   # f3 = N
	cvt.s.w	$f3, $f3
	
	Loop:
		l.s	$f1, 0($a1)
		add.s	$f0, $f0, $f1
		addi	$t0, $t0, 1	# contador++
		addi	$a1, $a1, 4	# endereço do vetor += 4
		bne	$t0, $a0, Loop
	
	div.s	$f2, $f0, $f3
	mfc1	$v0, $f2
	jr	$ra

