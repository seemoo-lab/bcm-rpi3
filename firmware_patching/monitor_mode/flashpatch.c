#include <firmware_version.h>
#include <patcher.h>

__attribute__((at(0x008008d4, "flashpatch")))
BPatch(flash_patch_0, 0x000043d8);

__attribute__((at(0x00806f34, "flashpatch")))
BPatch(flash_patch_1, 0x000048f4);

__attribute__((at(0x00807234, "flashpatch")))
BPatch(flash_patch_2, 0x00004c9c);

__attribute__((at(0x00807bd0, "flashpatch")))
BPatch(flash_patch_3, 0x00002754);

__attribute__((at(0x00808670, "flashpatch")))
BPatch(flash_patch_4, 0x00002bd2);

__attribute__((at(0x00804e24, "flashpatch")))
BPatch(flash_patch_5, 0x00004844);

__attribute__((at(0x00803610, "flashpatch")))
BPatch(flash_patch_6, 0x00003c84);

__attribute__((at(0x008342d0, "flashpatch")))
BPatch(flash_patch_7, 0x00016fe2);

__attribute__((at(0x0080c600, "flashpatch")))
BPatch(flash_patch_8, 0x0000366c);

__attribute__((at(0x0080c868, "flashpatch")))
BPatch(flash_patch_9, 0x00003854);

__attribute__((at(0x0080e54c, "flashpatch")))
BPatch(flash_patch_10, 0x000066ec);

__attribute__((at(0x0080e668, "flashpatch")))
BPatch(flash_patch_11, 0x00006868);

__attribute__((at(0x0080e908, "flashpatch")))
BPatch(flash_patch_12, 0x00006a38);

__attribute__((at(0x0080ebb4, "flashpatch")))
BPatch(flash_patch_13, 0x0000691c);

__attribute__((at(0x008136b4, "flashpatch")))
BPatch(flash_patch_14, 0x00006bd0);

__attribute__((at(0x00813900, "flashpatch")))
BPatch(flash_patch_15, 0x00006b0c);

__attribute__((at(0x008193e8, "flashpatch")))
BPatch(flash_patch_16, 0x000087a8);

__attribute__((at(0x008174f0, "flashpatch")))
BPatch(flash_patch_17, 0x00007110);

__attribute__((at(0x00817914, "flashpatch")))
BPatch(flash_patch_18, 0x000076c6);

__attribute__((at(0x00817cf4, "flashpatch")))
BPatch(flash_patch_19, 0x00007200);

__attribute__((at(0x00817e94, "flashpatch")))
BPatch(flash_patch_20, 0x000071c6);

__attribute__((at(0x00817ec4, "flashpatch")))
BPatch(flash_patch_21, 0x000072e4);

__attribute__((at(0x00817fc4, "flashpatch")))
BPatch(flash_patch_22, 0x00006fce);

__attribute__((at(0x008181a0, "flashpatch")))
BPatch(flash_patch_23, 0x00007658);

__attribute__((at(0x008186d0, "flashpatch")))
BPatch(flash_patch_24, 0x00007054);

__attribute__((at(0x0081880c, "flashpatch")))
BPatch(flash_patch_25, 0x0000740c);

__attribute__((at(0x00818cfc, "flashpatch")))
BPatch(flash_patch_26, 0x000077f8);

__attribute__((at(0x008195d0, "flashpatch")))
BPatch(flash_patch_27, 0x00008024);

__attribute__((at(0x008198ec, "flashpatch")))
BPatch(flash_patch_28, 0x00007dac);

__attribute__((at(0x0081a088, "flashpatch")))
BPatch(flash_patch_29, 0x0000c210);

__attribute__((at(0x0081a284, "flashpatch")))
BPatch(flash_patch_30, 0x0000bd6c);

__attribute__((at(0x0081c47c, "flashpatch")))
BPatch(flash_patch_31, 0x0000c4cc);

__attribute__((at(0x0081ee08, "flashpatch")))
BPatch(flash_patch_32, 0x00008c6c);

__attribute__((at(0x0081f748, "flashpatch")))
BPatch(flash_patch_33, 0x0000c674);

__attribute__((at(0x0081f858, "flashpatch")))
BPatch(flash_patch_34, 0x00008a1c);

__attribute__((at(0x00820278, "flashpatch")))
BPatch(flash_patch_35, 0x00010988);

__attribute__((at(0x00820fbc, "flashpatch")))
BPatch(flash_patch_36, 0x000102a2);

__attribute__((at(0x008225b0, "flashpatch")))
BPatch(flash_patch_37, 0x0000fe70);

__attribute__((at(0x00822b68, "flashpatch")))
BPatch(flash_patch_38, 0x00008ef0);

__attribute__((at(0x00822d88, "flashpatch")))
BPatch(flash_patch_39, 0x0000914c);

__attribute__((at(0x008232dc, "flashpatch")))
BPatch(flash_patch_40, 0x000104b6);

__attribute__((at(0x008241e4, "flashpatch")))
BPatch(flash_patch_41, 0x0000f820);

__attribute__((at(0x00832d60, "flashpatch")))
BPatch(flash_patch_42, 0x00013078);

__attribute__((at(0x00833dc8, "flashpatch")))
BPatch(flash_patch_43, 0x00012ee0);

__attribute__((at(0x00834008, "flashpatch")))
BPatch(flash_patch_44, 0x00012d28);

__attribute__((at(0x00834f34, "flashpatch")))
BPatch(flash_patch_45, 0x0001775c);

__attribute__((at(0x00835214, "flashpatch")))
BPatch(flash_patch_46, 0x00017108);

__attribute__((at(0x00835310, "flashpatch")))
BPatch(flash_patch_47, 0x00017024);

__attribute__((at(0x00836b98, "flashpatch")))
BPatch(flash_patch_48, 0x00017a1a);

__attribute__((at(0x00837a10, "flashpatch")))
BPatch(flash_patch_49, 0x00017e24);

__attribute__((at(0x008382e4, "flashpatch")))
BPatch(flash_patch_50, 0x000180f8);

__attribute__((at(0x008383fc, "flashpatch")))
BPatch(flash_patch_51, 0x0001837c);

__attribute__((at(0x0083929c, "flashpatch")))
BPatch(flash_patch_52, 0x00018408);

__attribute__((at(0x00839398, "flashpatch")))
BPatch(flash_patch_53, 0x00018764);

__attribute__((at(0x0083a42c, "flashpatch")))
BPatch(flash_patch_54, 0x000195ca);

__attribute__((at(0x0083a560, "flashpatch")))
BPatch(flash_patch_55, 0x00018cca);

__attribute__((at(0x0083a5c8, "flashpatch")))
BPatch(flash_patch_56, 0x00018fe6);

__attribute__((at(0x0083a768, "flashpatch")))
BPatch(flash_patch_57, 0x00018f2e);

__attribute__((at(0x0083a91c, "flashpatch")))
BPatch(flash_patch_58, 0x00018d16);

__attribute__((at(0x0083aee0, "flashpatch")))
BPatch(flash_patch_59, 0x000197a0);

__attribute__((at(0x0083afa8, "flashpatch")))
BPatch(flash_patch_60, 0x000191ee);

__attribute__((at(0x0083b1c4, "flashpatch")))
BPatch(flash_patch_61, 0x00019062);

__attribute__((at(0x0083b528, "flashpatch")))
BPatch(flash_patch_62, 0x000192ae);

__attribute__((at(0x0083bffc, "flashpatch")))
BPatch(flash_patch_63, 0x0001b5a4);

__attribute__((at(0x0083c4bc, "flashpatch")))
BPatch(flash_patch_64, 0x0001a300);

__attribute__((at(0x0083cefc, "flashpatch")))
BPatch(flash_patch_65, 0x0001aff8);

__attribute__((at(0x0083d944, "flashpatch")))
BPatch(flash_patch_66, 0x0001aec8);

__attribute__((at(0x0083eeb8, "flashpatch")))
BPatch(flash_patch_67, 0x00019b98);

__attribute__((at(0x0083fdac, "flashpatch")))
BPatch(flash_patch_68, 0x0001aaa8);

__attribute__((at(0x008245c4, "flashpatch")))
BPatch(flash_patch_69, 0x0000c1d2);

__attribute__((at(0x00844350, "flashpatch")))
BPatch(flash_patch_70, 0x0001bd74);

__attribute__((at(0x00844b8c, "flashpatch")))
BPatch(flash_patch_71, 0x0001c7ea);

__attribute__((at(0x00844d3c, "flashpatch")))
BPatch(flash_patch_72, 0x0001cc34);

__attribute__((at(0x00844db8, "flashpatch")))
BPatch(flash_patch_73, 0x0001cbd0);

__attribute__((at(0x008455b8, "flashpatch")))
BPatch(flash_patch_74, 0x0001be5e);

__attribute__((at(0x0084616c, "flashpatch")))
BPatch(flash_patch_75, 0x0001c1c8);

__attribute__((at(0x0084634c, "flashpatch")))
BPatch(flash_patch_76, 0x0001c264);

__attribute__((at(0x008465fc, "flashpatch")))
BPatch(flash_patch_77, 0x0001c098);

__attribute__((at(0x00846e94, "flashpatch")))
BPatch(flash_patch_78, 0x0001d0a4);

__attribute__((at(0x008470d4, "flashpatch")))
BPatch(flash_patch_79, 0x0001cdd2);

__attribute__((at(0x008473cc, "flashpatch")))
BPatch(flash_patch_80, 0x0001d130);

__attribute__((at(0x00847a10, "flashpatch")))
BPatch(flash_patch_81, 0x0001ceae);

__attribute__((at(0x00847bcc, "flashpatch")))
BPatch(flash_patch_82, 0x0001d2c4);

__attribute__((at(0x00847d98, "flashpatch")))
BPatch(flash_patch_83, 0x0001ced2);

__attribute__((at(0x008485ac, "flashpatch")))
BPatch(flash_patch_84, 0x0001d6c6);

__attribute__((at(0x00848778, "flashpatch")))
BPatch(flash_patch_85, 0x0001d692);

__attribute__((at(0x00848780, "flashpatch")))
BPatch(flash_patch_86, 0x0001d502);

__attribute__((at(0x0084b9e4, "flashpatch")))
BPatch(flash_patch_87, 0x0001da50);

__attribute__((at(0x0084e9b8, "flashpatch")))
BPatch(flash_patch_88, 0x0001dd4c);

__attribute__((at(0x0084f16c, "flashpatch")))
BPatch(flash_patch_89, 0x0001e10c);

__attribute__((at(0x0084f22c, "flashpatch")))
BPatch(flash_patch_90, 0x0001e3e0);

__attribute__((at(0x0084f284, "flashpatch")))
BPatch(flash_patch_91, 0x0001dd94);

__attribute__((at(0x00851140, "flashpatch")))
BPatch(flash_patch_92, 0x0001fdac);

__attribute__((at(0x00851190, "flashpatch")))
BPatch(flash_patch_93, 0x0001fdf8);

__attribute__((at(0x00825760, "flashpatch")))
BPatch(flash_patch_94, 0x0000b688);

__attribute__((at(0x0084f348, "flashpatch")))
BPatch(flash_patch_95, 0x0001e464);

__attribute__((at(0x00849230, "flashpatch")))
BPatch(flash_patch_96, 0x0001d748);

__attribute__((at(0x00851900, "flashpatch")))
BPatch(flash_patch_97, 0x0001fe58);

__attribute__((at(0x00851950, "flashpatch")))
BPatch(flash_patch_98, 0x0001fe6c);

__attribute__((at(0x0084f484, "flashpatch")))
BPatch(flash_patch_99, 0x0001dd98);

__attribute__((at(0x0082a310, "flashpatch")))
BPatch(flash_patch_100, 0x0000b4da);

__attribute__((at(0x00854130, "flashpatch")))
BPatch(flash_patch_101, 0x0001fed0);

__attribute__((at(0x00855020, "flashpatch")))
BPatch(flash_patch_102, 0x000201f6);

__attribute__((at(0x00854e10, "flashpatch")))
BPatch(flash_patch_103, 0x0001ff30);

__attribute__((at(0x0082a95c, "flashpatch")))
BPatch(flash_patch_104, 0x0000b5b4);

__attribute__((at(0x0082abec, "flashpatch")))
BPatch(flash_patch_105, 0x00009264);

__attribute__((at(0x0082aeb8, "flashpatch")))
BPatch(flash_patch_106, 0x0000d9f8);

__attribute__((at(0x00840acc, "flashpatch")))
BPatch(flash_patch_107, 0x0001b0c8);

__attribute__((at(0x008411f0, "flashpatch")))
BPatch(flash_patch_108, 0x0001b9a8);

__attribute__((at(0x00857e90, "flashpatch")))
BPatch(flash_patch_109, 0x000207d4);

__attribute__((at(0x0082af84, "flashpatch")))
BPatch(flash_patch_110, 0x0000b7e2);

__attribute__((at(0x00859474, "flashpatch")))
BPatch(flash_patch_111, 0x000214c8);

__attribute__((at(0x00859608, "flashpatch")))
BPatch(flash_patch_112, 0x00021dcc);

__attribute__((at(0x008596a0, "flashpatch")))
BPatch(flash_patch_113, 0x000210ec);

__attribute__((at(0x0085ab58, "flashpatch")))
BPatch(flash_patch_114, 0x000212be);

__attribute__((at(0x0085bda4, "flashpatch")))
BPatch(flash_patch_115, 0x00021e96);

__attribute__((at(0x0085be78, "flashpatch")))
BPatch(flash_patch_116, 0x000216d6);

__attribute__((at(0x0085c204, "flashpatch")))
BPatch(flash_patch_117, 0x00021868);

__attribute__((at(0x0085c258, "flashpatch")))
BPatch(flash_patch_118, 0x00021fce);

__attribute__((at(0x0085c3d8, "flashpatch")))
BPatch(flash_patch_119, 0x00020d78);

__attribute__((at(0x0085c488, "flashpatch")))
BPatch(flash_patch_120, 0x00020e10);

__attribute__((at(0x0085c970, "flashpatch")))
BPatch(flash_patch_121, 0x00022188);

__attribute__((at(0x0085d084, "flashpatch")))
BPatch(flash_patch_122, 0x00022144);

__attribute__((at(0x0085d248, "flashpatch")))
BPatch(flash_patch_123, 0x000222c0);

__attribute__((at(0x0082b494, "flashpatch")))
BPatch(flash_patch_124, 0x0000c08c);

__attribute__((at(0x0085f140, "flashpatch")))
BPatch(flash_patch_125, 0x000223d2);

__attribute__((at(0x008618a8, "flashpatch")))
BPatch(flash_patch_126, 0x0002233a);

__attribute__((at(0x00863388, "flashpatch")))
BPatch(flash_patch_127, 0x0002ba74);

__attribute__((at(0x00863d4c, "flashpatch")))
BPatch(flash_patch_128, 0x0002bc74);

__attribute__((at(0x00863e80, "flashpatch")))
BPatch(flash_patch_129, 0x0002bd12);

__attribute__((at(0x00863f10, "flashpatch")))
BPatch(flash_patch_130, 0x0002bc40);

__attribute__((at(0x0082c530, "flashpatch")))
BPatch(flash_patch_131, 0x00009218);

__attribute__((at(0x0082c580, "flashpatch")))
BPatch(flash_patch_132, 0x0000c1ee);

__attribute__((at(0x0082c8ac, "flashpatch")))
BPatch(flash_patch_133, 0x0000f694);

__attribute__((at(0x008661cc, "flashpatch")))
BPatch(flash_patch_134, 0x0002ca7c);

__attribute__((at(0x008662a4, "flashpatch")))
BPatch(flash_patch_135, 0x0002c9fa);

__attribute__((at(0x0086637c, "flashpatch")))
BPatch(flash_patch_136, 0x0002c8f8);

__attribute__((at(0x00851284, "flashpatch")))
BPatch(flash_patch_137, 0x0001fcc4);

__attribute__((at(0x00836f0c, "flashpatch")))
BPatch(flash_patch_138, 0x00017a3e);

__attribute__((at(0x0082d0ec, "flashpatch")))
BPatch(flash_patch_139, 0x0000f610);

__attribute__((at(0x00841c74, "flashpatch")))
BPatch(flash_patch_140, 0x0001ad18);

__attribute__((at(0x00841f8c, "flashpatch")))
BPatch(flash_patch_141, 0x0001a24a);

__attribute__((at(0x00842218, "flashpatch")))
BPatch(flash_patch_142, 0x0001bb1c);

__attribute__((at(0x008690c8, "flashpatch")))
BPatch(flash_patch_143, 0x0002fa70);

__attribute__((at(0x00869214, "flashpatch")))
BPatch(flash_patch_144, 0x0002fa08);

__attribute__((at(0x0086939c, "flashpatch")))
BPatch(flash_patch_145, 0x0002f9b2);

__attribute__((at(0x0082d914, "flashpatch")))
BPatch(flash_patch_146, 0x0000f860);

__attribute__((at(0x0082ddc4, "flashpatch")))
BPatch(flash_patch_147, 0x0000dc84);

__attribute__((at(0x0082eb54, "flashpatch")))
BPatch(flash_patch_148, 0x0000bbca);

__attribute__((at(0x0082ec54, "flashpatch")))
BPatch(flash_patch_149, 0x0000f588);

__attribute__((at(0x0086ca48, "flashpatch")))
BPatch(flash_patch_150, 0x0003205a);

__attribute__((at(0x0082ed78, "flashpatch")))
BPatch(flash_patch_151, 0x0000f308);

__attribute__((at(0x0082eef0, "flashpatch")))
BPatch(flash_patch_152, 0x0000c242);

__attribute__((at(0x0082f1e0, "flashpatch")))
BPatch(flash_patch_153, 0x0000c15e);

__attribute__((at(0x0086fbf4, "flashpatch")))
BPatch(flash_patch_154, 0x00034674);

__attribute__((at(0x0086fde8, "flashpatch")))
BPatch(flash_patch_155, 0x00032b50);

__attribute__((at(0x00870858, "flashpatch")))
BPatch(flash_patch_156, 0x0003321a);

__attribute__((at(0x00871438, "flashpatch")))
BPatch(flash_patch_157, 0x00032246);

__attribute__((at(0x00871494, "flashpatch")))
BPatch(flash_patch_158, 0x000325d0);

__attribute__((at(0x0087169c, "flashpatch")))
BPatch(flash_patch_159, 0x00033d04);

__attribute__((at(0x008718f0, "flashpatch")))
BPatch(flash_patch_160, 0x00032cb4);

__attribute__((at(0x00871ac0, "flashpatch")))
BPatch(flash_patch_161, 0x00032e32);

__attribute__((at(0x00871dd0, "flashpatch")))
BPatch(flash_patch_162, 0x00032c10);

__attribute__((at(0x00871edc, "flashpatch")))
BPatch(flash_patch_163, 0x00032fac);

__attribute__((at(0x00872038, "flashpatch")))
BPatch(flash_patch_164, 0x000338ca);

__attribute__((at(0x008722c0, "flashpatch")))
BPatch(flash_patch_165, 0x000332da);

__attribute__((at(0x00872580, "flashpatch")))
BPatch(flash_patch_166, 0x000335be);

__attribute__((at(0x00872810, "flashpatch")))
BPatch(flash_patch_167, 0x00033b64);

__attribute__((at(0x00872920, "flashpatch")))
BPatch(flash_patch_168, 0x000327bc);

__attribute__((at(0x00872e3c, "flashpatch")))
BPatch(flash_patch_169, 0x000322b8);

__attribute__((at(0x00873c40, "flashpatch")))
BPatch(flash_patch_170, 0x0003251a);

__attribute__((at(0x00874d30, "flashpatch")))
BPatch(flash_patch_171, 0x0003493c);

__attribute__((at(0x00874dc8, "flashpatch")))
BPatch(flash_patch_172, 0x00033c9c);

__attribute__((at(0x00874f94, "flashpatch")))
BPatch(flash_patch_173, 0x00033148);

__attribute__((at(0x0087501c, "flashpatch")))
BPatch(flash_patch_174, 0x0003483c);

__attribute__((at(0x0082fe44, "flashpatch")))
BPatch(flash_patch_175, 0x0000c6f6);

__attribute__((at(0x00830014, "flashpatch")))
BPatch(flash_patch_176, 0x0000f7b8);

__attribute__((at(0x0083090c, "flashpatch")))
BPatch(flash_patch_177, 0x0000918a);

__attribute__((at(0x0085c4fc, "flashpatch")))
BPatch(flash_patch_178, 0x00020f02);

__attribute__((at(0x81F620, "flashpatch")))
BLPatch(flash_patch_179, wl_monitor_hook);
