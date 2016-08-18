SECTIONS
{
	/* The first section can be placed at 0x180020, following sections can be automatically placed after the first section */
	.text.copy_hook 0x1600: { KEEP(patch.o (.text.copy_hook)) }
	/* .text.function_2 : { KEEP(patch.o (.text.function_2)) } */

	/* All other sections that were not yet placed but referenced by a kept section are collected in the text section */
	.text : { patch.o (.text .text.* .data .data.* .bss .bss.* .rodata .rodata.*) }

	INCLUDE ../wrapper/wrapper.ld
}
