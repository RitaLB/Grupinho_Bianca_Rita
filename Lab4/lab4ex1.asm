.data
	A: 	  .float	0.11 0.34 1.23 5.34 0.76 0.65 0.34 0.12 0.87 0.56
	B: 	  .float	7.89 6.87 9.89 7.12 6.23 8.76 8.21 7.32 7.32 8.22
	result_A: .asciiz  	"Media de A: "
	result_B: .asciiz  	"\nMedia de B: "
	digite:	  .asciiz  	"Digite o tamanho dos vetores A e B: "

.text
	
	li $v0, 4 		# Comando para escrever string
	la $a0, digite 		# Carrega string (endereço)
	syscall			# Escreve "Digite o tamanho dos vetores A e B: " no console
	
	# lendo N do teclado
	li	$v0, 5		# Comando para ler inteiro
	syscall
	move	$s0, $v0    	# $s0 = N
	
	# calculando média de A
	move	$a0, $s0	# argumento $a0 = N
	la	$a1, A      	# argumento $a1 = endereço do vetor A
	jal	media
	
	# movendo o retorno do procedimento media para $f12 --> para depois escrever no console esse valor
	mtc1	$v0, $f12	# $f12 = média de A
	
	li 	$v0, 4 		# Comando para escrever string
	la 	$a0, result_A 	# Carrega string (endereço)
	syscall			# Escreve "Media de A: " no console
	
	li	$v0, 2		# Comando para escrever float
	syscall			# Escreve a média de A no console
	
	# Calculando média de B
	move	$a0, $s0	# argumento $a0 = N
	la	$a1, B      	# argumento $a1 = endereço do vetor B
	jal	media
	
	# movendo o retorno do procedimento media para $f12 --> para depois escrever no console esse valor
	mtc1	$v0, $f12	
	
	li 	$v0, 4 		# Comando para escrever string
	la 	$a0, result_B 	# Carrega string (endereço)
	syscall			# Escreve "\nMedia de B: " no console

	li	$v0, 2		# Comando para escrever float
	syscall			# Escreve a média de B no console
	
	li	$v0, 10		# Comando para encerrar o programa
	syscall			# Encerra o programa


media:
	li	$t0, 0     	# $t0 = contador
	
	li	$t1, 0
	mtc1	$t1, $f0   	# $f0 = somatorio . 
	cvt.s.w	$f0, $f0	# converte $f0 para float
	
	mtc1	$a0, $f3   	# $f3 = N
	cvt.s.w	$f3, $f3	# convere $f3 para float
	
	Loop:
		l.s	$f1, 0($a1)	# $f1 = um elemento do vetor
		add.s	$f0, $f0, $f1	# $f0 = $f0 + $f1    -->    somatório += elemento do vetor
		
		addi	$t0, $t0, 1	# contador++
		addi	$a1, $a1, 4	# endereço do vetor += 4
		bne	$t0, $a0, Loop
	
	div.s	$f2, $f0, $f3	# $f2 = $f0 / $f3   -->   resultado = somatório / N
	mfc1	$v0, $f2	# retorno $v0 = resultado
	jr	$ra

