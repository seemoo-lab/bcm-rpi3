SECTIONS
{
    .text.dummy_0F0 0xF0: { KEEP(patch.o (.text.dummy_0F0)) }
    .text.fpb_remap_dest 0x4E9A0 : { KEEP(patch.o (.text.fpb_remap_dest)) }
    .text.wlc_ucode_download_hook 0xa00 : { KEEP(patch.o (.text.wlc_ucode_download_hook)) }

    .text.sub_413E0_hook : { KEEP(patch.o (.text.sub_413E0_hook)) }

	/* All other sections that were not yet placed but referenced by a kept section are collected in the text section */
	.text : { patch.o (.text .text.* .data .data.* .bss .bss.* .rodata .rodata.*) }

	INCLUDE ../../wrapper/wrapper.ld
}
