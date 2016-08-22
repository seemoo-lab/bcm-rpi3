SECTIONS
{
    .text.wlc_bmac_recv_hook 0x1BEC4 : { KEEP(patch.o (.text.wlc_bmac_recv_hook)) }

	/*.text.dngl_sendpkt_hook 0x92 : { KEEP(patch.o (.text.dngl_sendpkt_hook)) }*/


	/* All other sections that were not yet placed but referenced by a kept section are collected in the text section */
	.text : { patch.o (.text .text.* .data .data.* .bss .bss.* .rodata .rodata.*) }

	INCLUDE ../wrapper/wrapper.ld
}
