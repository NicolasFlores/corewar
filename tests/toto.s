.name "GUY"
	.comment "Je te coupe la tete et je te chie dans le cou."
l1:	     live %42				;5
	        ld %4, r78			;7
	        st r1, r1			;4
	        add r2, r3, r2		;5
l2:	     sub r2, r3, r2			;5
	        and %42, %42, r1	;11
	        or r2, %15, r4		;8
	        xor r2, %15, r4		;8
l3:	     zjmp %:l4				;3
	        ldi r1, %42, r2		;6
	        sti r1, %42, %21	;7
	        fork %42			;3
l4:	     lld %4, r78			;7
	        lldi r1, %42, r2	;6
	        lfork %42			;3
	        aff r4				;3
