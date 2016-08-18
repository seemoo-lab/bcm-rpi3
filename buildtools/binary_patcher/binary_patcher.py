#!/usr/bin/env python2

"""
Based on the 'generic_patcher' by shoote:
https://github.com/shoote/generic_patcher
"""

from subprocess import check_call, STDOUT 
from os import unlink
import os
from os.path import exists
import struct
import binascii

class BasePatch(object):
    def __init__(self, pos, data):
        self.pos = pos
        self.data = data
        self.ram_start = 0x180000
    
    def apply(self, firmware, **kargs):
        fw_pos = self.pos - self.ram_start
        firmware += max(0, fw_pos - len(firmware)) * "\x00"
        return firmware[:fw_pos] + self.data + firmware[fw_pos+len(self.data):]
    def set_ram_start(self, start):
        self.ram_start = start

class ExternalArmPatch(BasePatch):
    def __init__(self, pos, infile, extra_data=""):
        self.pos = pos
        self.infile = infile
        self.extra_data = extra_data

    def _delete_temp(self,path):
        if exists(path):
            unlink(path)

    def _generate_bytes(self):
        try:
            data = file(self.infile,'rb').read() + self.extra_data
            print "data_len: %d" % len(data)
            return data
        finally:
            print "success read"

    def get_bytes(self):
        return self._generate_bytes()
    
    def apply(self, firmware, **kargs):
        self.data = self._generate_bytes()
        return super(ExternalArmPatch, self).apply(firmware)


class BPatch(BasePatch):
    """
    Generates a B.W opcode patch
    """
    def __init__(self, pos, to, real_from=None):
        """
        Creates a B.W patch at pos which will jump to the 'to' destination.
        The read_from paramter needs to be used when the opcodes are copied
        from the pos address to another, and it should contain the address
        which the patch will run from.
        Props: https://github.com/DiGMi/generic_patcher/commit/366ff9f60f9e3df070cfcb84a0be01e13d6cbe19#diff-e8040c3645a0f37b6c027dd5bb240603
        """
        if real_from == None:
            real_from = pos
        self.pos = pos
        self.data = self.patch_b(real_from, to)

    def patch_b(self, src, dst):
        diff = dst - src - 4
        diff_upper = (diff >> 12) & 0x3ff
        diff_lower = ((diff & 0xfff) >> 1) | (((diff >>22)&1) << 11) | (((diff >> 23) & 1) <<13)
        a = (0xF000 | diff_upper)# << 16
        b = (0x9000 | diff_lower)
        if diff < 0:
            a |= 0x0400
        else:
            b = b^ 0x2800
        c = (a << 16) | b
        print "patched: %X to call %X B.W opcode: %s" % (src, dst,
                struct.pack("<HH", a, b).encode('hex'))
        return struct.pack("<HH", a, b)  

        
class BLPatch(BasePatch):
    def __init__(self, pos, to):
        self.pos = pos
        self.to = to

    def patch_bl(self, src, dst):

        if(src < self.ram_start):
            print "ERROR, trying to patch ROM: ", str(hex(self.ram_start))
            return
        
        diff = dst - src - 4
        
        #looks like we jump to a lower addr (not necessary)
        if(diff < 0):
            diff &= 0xffffffff

        diff_upper = (diff >> 12) & 0x7ff
        diff_lower = (diff & 0xfff) >> 1
        a = (0xF000 | diff_upper)# << 16
        b = (0xF800 | diff_lower)
        c = (a << 16) | b
        print "patched: %X to call %X BL opcode: %X" % (src, dst, c)
        packed_data = struct.pack("<HH", a, b)
        print "packed: ", binascii.hexlify(packed_data)
        return packed_data

    def apply(self, firmware, **kargs):
        self.data = str(self.patch_bl(self.pos, self.to))
        return super(BLPatch, self).apply(firmware)

class GenericPatch4(BasePatch):
    """
    Just replace a 4 Byte word
    """
    def __init__(self, pos, to):
        self.pos = pos
        self.to = to

    def patch_gen(self, subst):
        packed_data = struct.pack("<I", subst)
        print "packed: ", binascii.hexlify(packed_data)
        return packed_data

    def apply(self, firmware, **kargs):
        self.data = str(self.patch_gen(self.to))
        return super(GenericPatch4, self).apply(firmware)

class GenericPatch2(BasePatch):
    """
    Just replace a 2 Byte word
    """
    def __init__(self, pos, to):
        self.pos = pos
        self.to = to

    def patch_gen(self, subst):
        packed_data = struct.pack("<H", subst)
        print "packed: ", binascii.hexlify(packed_data)
        return packed_data

    def apply(self, firmware, **kargs):
        self.data = str(self.patch_gen(self.to))
        return super(GenericPatch2, self).apply(firmware)

class StringPatch(BasePatch):
    """
    Place a string into the firmware
    """
    def __init__(self, pos, to):
        self.pos = pos
        self.to = to

    def apply(self, firmware, **kargs):
        self.data = self.to + '\0'
        return super(StringPatch, self).apply(firmware)

        
def patch_firmware(src, dst, patchs, ram_start = 0x180000, **kargs):
    """
    Patch the firmware blob

    :param src: original file (input)
    :param dest: patched file (output)
    """
    firmware = file(src,'rb').read()
    for p in patchs:
        p.set_ram_start(ram_start)
        firmware = p.apply(firmware, **kargs)
    firmware = file(dst,'wb').write(firmware)

