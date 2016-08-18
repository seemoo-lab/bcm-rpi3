#!/usr/bin/env python -3
# -*- coding: utf-8 -*-
#
# Copyright 2010 K. Richard Pixley.
# See LICENSE for details.
#
# Time-stamp: <02-Jan-2011 18:27:10 PST by rich@noir.com>

"""
A covering script for :py:mod:`elffile`.  Provides basic objdump ability.
"""

from __future__ import unicode_literals, print_function

__docformat__ = 'restructuredtext en'

import glob
import itertools
import optparse
import pprint
import sys

import elffile

if __name__ == '__main__':

    progname = sys.argv[0]
    u = ''
    u += 'usage: %prog objfile [objfile [objfile ...]]'

    parser = optparse.OptionParser(usage = u)

    options, args = parser.parse_args()

    ef = elffile.open(name=args[0])
    for header in ef.sectionHeaders:
        if header.addralign == 4:
            header.addralign = 2
        print("header name: ", header.name, "type: ", header.type, "align: ", header.addralign)
    with open(args[1], 'wb') as f: f.write(ef.pack())

    sys.exit()
