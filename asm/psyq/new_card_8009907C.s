	opt	c+, at+, e+, n-
	section .text

	xdef new_card_8009907C
new_card_8009907C:
	dw 0x240A00B0 ; 0x8009907C
	dw 0x01400008 ; 0x80099080
	dw 0x24090050 ; 0x80099084
	dw 0x00000000 ; 0x80099088
