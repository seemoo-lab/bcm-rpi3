#include <plugin.h>
#include <tree.h>
#include <print-tree.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <c-family/c-pragma.h>

static tree handle_nexmon_place_at_attribute(tree *node, tree name, tree args, int flags, bool *no_add_attr);

int plugin_is_GPL_compatible = 1;

static const char *objfile = "patch.o";
static const char *fwfile = "fw_bcmdhd.bin";
static const char *ldfile = "/dev/null";
static const char *makefile = "/dev/null";
static const char *targetregion = NULL;
static unsigned int ramstart = 0x0;
static unsigned int chipver = 0;
static unsigned int fwver = 0;
//static unsigned int fp_config_base = 0x1800;
static unsigned int fp_config_base = 0x5A3A8;
static unsigned int fp_data_base = 0x1000;
static unsigned int fp_config_end = fp_config_base;
static unsigned int fp_data_end = fp_data_base;
static bool fp_active = false;

static FILE *ld_fp, *make_fp;

static struct attribute_spec user_attr =
{
	.name = "at",
	.min_length = 1,
	.max_length = 4,
	.decl_required = true,
	.type_required = false,
	.function_type_required = false,
	.handler = handle_nexmon_place_at_attribute,
	.affects_type_identity = false,
};

char *str1 = (char *) "";

static tree
handle_nexmon_place_at_attribute(tree *node, tree name, tree args, int flags, bool *no_add_attr)
{
	//tree itr; 
	tree tmp_tree;

	const char *decl_name = IDENTIFIER_POINTER(DECL_NAME(*node));
	//const char *attr_name = IDENTIFIER_POINTER(name);
	//const char *param1_str = TREE_STRING_POINTER(TREE_VALUE(args));
	const char *region = NULL;
	unsigned int addr = 0;
	bool is_dummy = false;
	bool is_region = false;
	bool is_flashpatch = false;
	unsigned int chipver_local = 0;
	unsigned int fwver_local = 0;

	if (TREE_CODE(TREE_VALUE(args)) == STRING_CST) {
		region = TREE_STRING_POINTER(TREE_VALUE(args));
		is_region = true;
	} else if (TREE_CODE(TREE_VALUE(args)) == INTEGER_CST) {
		addr = TREE_INT_CST_LOW(TREE_VALUE(args));
	}

	tmp_tree = TREE_CHAIN(args);
	if(tmp_tree != NULL_TREE) {
		is_dummy = strstr(TREE_STRING_POINTER(TREE_VALUE(tmp_tree)), "dummy");
		is_flashpatch = strstr(TREE_STRING_POINTER(TREE_VALUE(tmp_tree)), "flashpatch");

		tmp_tree = TREE_CHAIN(tmp_tree);
		if(tmp_tree != NULL_TREE) {
			chipver_local = TREE_INT_CST_LOW(TREE_VALUE(tmp_tree));

			tmp_tree = TREE_CHAIN(tmp_tree);
			if(tmp_tree != NULL_TREE) {
				fwver_local = TREE_INT_CST_LOW(TREE_VALUE(tmp_tree));
			}
		}
	}

	printf("decl_name: %s\n", decl_name);

	//printf("attr_name: %s\n", attr_name);

	//printf("align: %d\n", DECL_COMMON_CHECK (*node)->decl_common.align);
	if (DECL_COMMON_CHECK (*node)->decl_common.align == 32 && (addr & 1))
		DECL_COMMON_CHECK (*node)->decl_common.align = 8;

	if (DECL_COMMON_CHECK (*node)->decl_common.align == 32 && (addr & 2))
		DECL_COMMON_CHECK (*node)->decl_common.align = 16;
	//printf("align: %d\n", DECL_COMMON_CHECK (*node)->decl_common.align);

	//for(itr = args; itr != NULL_TREE; itr = TREE_CHAIN(itr)) {
	//	printf("arg: %s %08x\n", TREE_STRING_POINTER(TREE_VALUE(itr)), (unsigned int) strtol(TREE_STRING_POINTER(TREE_VALUE(itr)), NULL, 0));
		//debug_tree(itr);
		//debug_tree(TREE_VALUE(itr));
	//}

	if ((chipver == 0 || chipver_local == 0 || chipver == chipver_local) && (fwver == 0 || fwver_local == 0 || fwver == fwver_local)) {
		if (is_region) {
			asprintf(&str1, "%s.text.%s : { KEEP(%s (.*.%s)) } >%s\n", str1, region, objfile, decl_name, region);
		} else if (is_flashpatch) {
			fp_active = true;
			fprintf(ld_fp, ".text.%s 0x%08x : { KEEP(%s (.*.%s)) }\n", decl_name, addr, objfile, decl_name);
			fprintf(make_fp, "\t$(Q)$(CC)objcopy -O binary -j .text.%s $< section.generated.bin && dd if=section.generated.bin of=$@ bs=1 conv=notrunc status=none seek=$$((0x%08x))\n", decl_name, fp_data_end - ramstart);
			fprintf(make_fp, "\t$(Q)printf %08x%08x%08x | xxd -r -p | dd of=$@ bs=1 conv=notrunc status=none seek=$$((0x%08x))\n", htonl(addr), htonl(4), htonl(fp_data_end), fp_config_end - ramstart);
			fprintf(make_fp, "\t$(Q)printf \"  FLASHPATCH %s @ 0x%08x\\n\"\n", decl_name, addr);
			fp_config_end += 12;
			fp_data_end += 8;
		} else if (is_dummy) {
			fprintf(ld_fp, ".text.dummy.%s 0x%08x : { %s (.*.%s) }\n", decl_name, addr, objfile, decl_name);
		} else {
			fprintf(ld_fp, ".text.%s 0x%08x : { KEEP(%s (.*.%s)) }\n", decl_name, addr, objfile, decl_name);
			fprintf(make_fp, "\t$(Q)$(CC)objcopy -O binary -j .text.%s $< section.generated.bin && dd if=section.generated.bin of=$@ bs=1 conv=notrunc status=none seek=$$((0x%08x))\n", decl_name, addr - ramstart);
			fprintf(make_fp, "\t$(Q)printf \"  PATCH %s @ 0x%08x\\n\"\n", decl_name, addr);
		}
	}

	//debug_tree(*node);
	//debug_tree(name);
	return NULL_TREE;
}

static void
register_attributes(void *event_data, void *data)
{
	register_attribute(&user_attr);
}

static void
handle_pragma_targetregion(cpp_reader *dummy)
{
	tree message = 0;
	if (pragma_lex(&message) != CPP_STRING) {
      	printf ("<#pragma NEXMON targetregion> is not a string");
      	return;
    }

 	if (TREE_STRING_LENGTH (message) > 1)
		targetregion = TREE_STRING_POINTER (message);
}

static void 
register_pragmas(void *event_data, void *data)
{
	c_register_pragma("NEXMON", "targetregion", handle_pragma_targetregion);
}

static void
handle_plugin_finish(void *event_data, void *data)
{
	if (fp_active) {
		fprintf(make_fp, "\t$(Q)printf %08x | xxd -r -p | dd of=$@ bs=1 conv=notrunc status=none seek=$$((0x%08x))\n", htonl(fp_data_end), 0x38E3C - ramstart);
		fprintf(make_fp, "\t$(Q)printf \"  PATCH fp_data_end @ 0x%08x\\n\"\n", 0x38E3C);
		fprintf(make_fp, "\t$(Q)printf %08x | xxd -r -p | dd of=$@ bs=1 conv=notrunc status=none seek=$$((0x%08x))\n", htonl(fp_config_base), 0x3AC2C - ramstart);
		fprintf(make_fp, "\t$(Q)printf \"  PATCH fp_config_base @ 0x%08x\\n\"\n", 0x3AC2C);
		fprintf(make_fp, "\t$(Q)printf %08x | xxd -r -p | dd of=$@ bs=1 conv=notrunc status=none seek=$$((0x%08x))\n", htonl(fp_config_end), 0x3AC28 - ramstart);
		fprintf(make_fp, "\t$(Q)printf \"  PATCH fp_config_end @ 0x%08x\\n\"\n", 0x3AC28);
		fprintf(make_fp, "\t$(Q)printf %08x | xxd -r -p | dd of=$@ bs=1 conv=notrunc status=none seek=$$((0x%08x))\n", htonl(fp_config_base), 0x3A9B4 - ramstart);
		fprintf(make_fp, "\t$(Q)printf \"  PATCH fp_config_base @ 0x%08x\\n\"\n", 0x3A9B4);
		fprintf(make_fp, "\t$(Q)printf %08x | xxd -r -p | dd of=$@ bs=1 conv=notrunc status=none seek=$$((0x%08x))\n", htonl(fp_config_end), 0x3A9B0 - ramstart);
		fprintf(make_fp, "\t$(Q)printf \"  PATCH fp_config_end @ 0x%08x\\n\"\n", 0x3A9B0);
	}

	fprintf(make_fp, "\nFORCE:\n");
	
	fprintf(ld_fp, "%s", str1);

	if (targetregion)
		fprintf(ld_fp, ".text.%s : { %s (.text .text.* .data .data.* .bss .bss.* .rodata .rodata.*) } >%s\n", targetregion, objfile, targetregion);

	fclose(ld_fp);
	fclose(make_fp);
}

int
plugin_init(struct plugin_name_args *info, struct plugin_gcc_version *ver)
{
	int i = 0;
	for (i = 0; i < info->argc; i++) {
		if (!strcmp(info->argv[i].key, "objfile")) {
			objfile = info->argv[i].value;
		} else if (!strcmp(info->argv[i].key, "ldfile")) {
			ldfile = info->argv[i].value;
		} else if (!strcmp(info->argv[i].key, "makefile")) {
			makefile = info->argv[i].value;
		} else if (!strcmp(info->argv[i].key, "fwfile")) {
			fwfile = info->argv[i].value;
		} else if (!strcmp(info->argv[i].key, "ramstart")) {
			ramstart = (unsigned int) strtol(info->argv[i].value, NULL, 0);
		} else if (!strcmp(info->argv[i].key, "chipver")) {
			chipver = (unsigned int) strtol(info->argv[i].value, NULL, 0);
		} else if (!strcmp(info->argv[i].key, "fwver")) {
			fwver = (unsigned int) strtol(info->argv[i].value, NULL, 0);
		}
	}

	unlink(ldfile);
	unlink(makefile);

	ld_fp = fopen(ldfile, "a");

	if (!ld_fp) {
		fprintf(stderr, "gcc_nexmon_plugin: Linker file not writeable! (error)\n");
		return -1;
	}

	make_fp = fopen(makefile, "a");

	if (!make_fp) {
		fprintf(stderr, "gcc_nexmon_plugin: Make file not writeable! (error)\n");
		return -1;
	}

	fprintf(make_fp, "%s: patch.elf FORCE\n", fwfile);

	register_callback("nexmon", PLUGIN_ATTRIBUTES, register_attributes, NULL);
	register_callback("nexmon", PLUGIN_PRAGMAS, register_pragmas, NULL);
	register_callback("nexmon", PLUGIN_FINISH, handle_plugin_finish, NULL);

	return 0;
}
