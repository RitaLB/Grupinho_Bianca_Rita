.data
	resultado: .double 0
	
.text
	
	# Recebendo input do usiario para valor de x
	
	li	$v0, 5		# Comando para ler inteiro
	syscall			# O valor digitado é salvo em $v0
	move	$a0, $v0 	# movendo valor recebido para o registrador de parâmero $a0
	
	# Iniciando função
	jal 	sin_aprox
	
	j	exit
	
sin_aprox:
	mtc1.d	$a0, $f0		# f0 = x
	cvt.d.w	$f0, $f0
	
	li	$t0, 0			# $t0 = n
	
	li	$t1, -1
	mtc1.d	$t1, $f2		# f2 = -1
	cvt.d.w	$f2, $f2
	
	li	$t1, 2
	mtc1.d	$t1, $f4		# f4 = 2
	cvt.d.w	$f4, $f4
	
	li	$t1, 1
	mtc1.d	$t1, $f6		# f6 = 1
	cvt.d.w	$f6, $f6
	
	li	$t1, 0
	mtc1.d	$t1, $f20		# f20 = 0 Inicializa registrador para resultado
	cvt.d.w	$f20, $f20
	
	Loop_somatorio:
		
		
		mov.d	$f8, $f2		# $f8 = -1 para o loop de sinal	
		li	$t1, -1			#contatador loop sinal
	
		Loop_sinal:
		
			mul.d	$f8, $f8, $f8		# $f8 = (-1)^n
			
			addi	$t1, $t1, 1		# $t1 = $t1 + 1 ---- n = n+1
			bne	$t1, $t0, Loop_sinal	# Enquanto o número de loops for diferente de n atual, continua loop
		
		
		mtc1.d	$t0, $f10		# f10 = n para calculos de do somatório
		cvt.d.w	$f10, $f10
		
		mul.d	$f12, $f4, $f10		#$f12 = 2n
		add.d	$f12, $f12, $f6		#$f12 = 2n + 1
			
		cvt.w.s	$f14,$f12		#$f14  = word. 2n+1 !! $f14 temporário
		mfc1	$t2,$f14		#$t2 = valor resultado de 2n+1 para controlar loop de fatorial
		addi	$t2, $t2, 1			#$t2 ajustado para loop
		
		#sub.d	$f14, $f12, $f6		#$f14 = (2n+1) -1
		mov.d	$f14, $f12
		mov.d	$f16, $f12
		Loop_fatorial:
			
			mul.d	$f16, $f16, $f14	#$f16 = multiplicação do fatorial
			sub.d	$f14, $f14, $f6		#$f14 = (2n+1) anterior -1
				
			
			subi	$t2, $t2, 1 
			bne	$t2, 0, Loop_fatorial		# Enquanto o fatorial não chegar a 1, continua loop
			
		######### $F14 NÃO ESTÁ RECEBENDO VALOR CORRETO DE $F12
		
		li	$t1, 0			#contatador loop de potência  
		cvt.w.d	$f14,$f12		#$f14  = word. 2n+1 !! $f14 temporário
		mfc1	$t2,$f14		#$t2 = valor resultado de 2n+1 para controlar loop de potência do x
		#addi	$t2, $t2, 1
		
		mov.d	$f18, $f6		#$f18 = 1
		Loop_potencia_x:
			
			mul.d	$f18, $f18, $f0		#$f18 = x^(2n+1)
			
			subi	$t2, $t2, 1		# decrescentando $t2 (começa em 2n+1) até 0
			bne	$t2, 0, Loop_potencia_x		
	
		mul.d	$f22, $f8, $f18		# $f22 = (-1)^n * x^(2n+1)
		div.d	$f22, $f22, $f16	# $f22 = $f22 / (2n+1)!
		
		add.d	$f20, $f22, $f20	# soma resultado anterior com o próximo 
						# somatório = reultado anterior ($f20) + resultafo novo ($f22) 
		
		addi	$t0, $t0, 1		# $t0 = $t0 + 1 ---- n = n+1
		bne	$t0, 2, Loop_somatorio	# Enquanto o número de loops for diferente de 20, continua loop
	
	# mov.d	$v0, $f2  resolver como fazer esse retorno pelo registrador certo	
	
	jr	$ra

exit:
	la	$t3, resultado		#lembrar: resultado salvo em $f20
	sdc1	$f20, 0($t3)
	


