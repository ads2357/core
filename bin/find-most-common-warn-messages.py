#!/usr/bin/python

# A script to search our test logs and sort the messages by how common they are so we can start to
# reduce the noise a little.

import sys
import re
import io
import subprocess

# find . -name '*.log' | xargs grep -h 'warn:' | sort | uniq -c | sort -n --field-separator=: --key=5,6

process = subprocess.Popen("find workdir -name '*.log' | xargs grep -h 'warn:' | sort",
                            shell=True, stdout=subprocess.PIPE, universal_newlines=True)

messages = dict() # dict of sourceAndLine->count
for line in process.stdout:
    line = line.strip()
    # a sample line is:
    #    warn:sw:18790:1:sw/source/core/doc/DocumentRedlineManager.cxx:98: redline table corrupted: overlapping redlines
    tokens = line.split(":")
    sourceAndLine = tokens[4] + ":" + tokens[5]
    if (sourceAndLine in messages):
        messages[sourceAndLine] = messages[sourceAndLine] + 1
    else:
        messages[sourceAndLine] = 1

tmplist = list() # set of tuple (count, sourceAndLine)
for key, value in messages.iteritems():
    tmplist.append([value,key])

for i in sorted(tmplist, key=lambda v: v[0]):
    print i


