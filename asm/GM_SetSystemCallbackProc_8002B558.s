	opt	c+, at+, e+, n-
	section .text

	xdef GM_SetSystemCallbackProc_8002B558
GM_SetSystemCallbackProc_8002B558:
	dw 0x3C02800B ; 0x8002B558
	dw 0x244258C0 ; 0x8002B55C
	dw 0x00042040 ; 0x8002B560
	dw 0x00822021 ; 0x8002B564
	dw 0x03E00008 ; 0x8002B568
	dw 0xA4850000 ; 0x8002B56C
