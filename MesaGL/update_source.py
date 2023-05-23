#!/usr/bin/env python
from __future__ import print_function

import buildTools
import os
import sys
import string
import shutil
import re
from sets import Set

p = buildTools.loadCachedProjectInfo()

# expecting to find mesa git repo as peer of tweak repo
mesasrc = "../../../../mesa/src"
mesainclude = "../../../../mesa"

dirs = set()
includes = set()

#
#   Find all the directories that are being used
#

# for src in p.root.srcs:
#    dirs.add(os.path.dirname(src))

for (path, dirfiles, files) in os.walk("."):
    if path != "":
        if len(path) >= 9 and path[2:9] == "include":
            includes.add(path[2:])
        else:
            dirs.add(path[2:])

#
#   Edit the special case files automatically
#


def editFile(filename, includefilename):
    infile = open(filename, "r")
    lines = infile.readlines()
    replacement = includefilename + ".notincluded"
    reg = re.compile('#include "(%s)"' % includefilename)
    newlines = []
    for line in lines:
        m = re.match(reg, line)
        if m:
            fix = line.replace(includefilename, replacement)
            newlines.append(fix)
        else:
            newlines.append(line)
    infile.close()
    outfile = open(filename, "w")
    for line in newlines:
        outfile.write(line)
    outfile.close()


#
#   For each dir find all if its C and C++ files (in the mesa source code)
#


def updateSource(directory_set, mesaroot):
    for d in directory_set:
        mesadir = "%s/%s" % (mesaroot, d)
        files = os.listdir(mesadir)

        for f in files:
            ext = os.path.splitext(f)[1]
            src = "%s/%s" % (mesadir, f)
            if ext == ".c" or ext == ".cpp" or ext == ".h":
                dst = "%s/%s" % (d, os.path.split(f)[1])
                exists = os.path.exists(dst)
                dst_ni = dst + ".notincluded"
                excluded = os.path.exists(dst_ni)
                if not excluded:
                    if not exists:
                        print("INFO: new file", dst)
                    try:
                        shutil.copyfile(src, dst)
                    except:
                        e = sys.exc_info()[0]
                        print("ERROR:", e)
                        print("       src:", src)
                        print("       dst:", dst)
                elif excluded:
                    try:
                        shutil.copyfile(src, dst_ni)
                    except:
                        e = sys.exc_info()[0]
                        print("ERROR:", e)
                        print("       src:", src)
                        print("       dst_ni:", dst_ni)


updateSource(dirs, mesasrc)
updateSource(includes, mesainclude)
editFile("gallium/auxiliary/indices/u_indices_gen.c", "indices/u_indices.c")
editFile("gallium/auxiliary/indices/u_unfilled_gen.c", "indices/u_unfilled_indices.c")
