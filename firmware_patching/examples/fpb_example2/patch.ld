SECTIONS
{
    .text.dummy_0F0 0xF0 : { KEEP(patch.o (.text.dummy_0F0)) }
    .text.fpb_remap_dest 0x84EEA0: { KEEP(patch.o (.text.fpb_remap_dest)) }
    .text.wlc_bmac_recv_hook 0x1BEC4 : { KEEP(patch.o (.text.wlc_bmac_recv_hook)) }
    .text.wlc_valid_chanspec_hook_in_c : { KEEP(patch.o (.text.wlc_valid_chanspec_hook_in_c)) }

    .text.wlc_ucode_download_hook : { KEEP(patch.o (.text.wlc_ucode_download_hook)) }
	
    /* All other sections that were not yet placed but referenced by a kept section are collected in the text section */
	.text : { patch.o (.text .text.* .data .data.* .bss .bss.* .rodata .rodata.*) }

	INCLUDE ../../wrapper/wrapper.ld
}
