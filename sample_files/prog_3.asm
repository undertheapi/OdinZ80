; Program Three:

START:
	LD A, $40
	LD B, $30
	LD C, $20
	LD D, $10
	LD E, $55
	LD H, $11
	LD L, $32
	LD A, [BC]
	LD A, [VALUE]
END:

VALUE:
	DB 54
	