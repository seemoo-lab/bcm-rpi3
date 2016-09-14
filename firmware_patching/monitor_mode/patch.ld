SECTIONS
{
    /*.text.wlc_bmac_recv_hook 0x1BEC4 : { KEEP(patch.o (.text.wlc_bmac_recv_hook)) }*/
    .text.fpb_remap_dest 0x81F620 : { KEEP(patch.o (.text.fpb_remap_dest)) }
    .text.wlc_recvdata_hook 0x1210C : { KEEP(patch.o (.text.wlc_recvdata_hook)) }

    .text.wlc_ucode_download_hook : { KEEP(patch.o (.text.wlc_ucode_download_hook)) }
    .text.wl_monitor_hook : { KEEP(patch.o (.text.wl_monitor_hook)) }

	/* All other sections that were not yet placed but referenced by a kept section are collected in the text section */
	.text : { patch.o (.text .text.* .data .data.* .bss .bss.* .rodata .rodata.*) }

	INCLUDE ../wrapper/wrapper.ld
}
