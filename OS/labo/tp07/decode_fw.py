import re
import gzip

filter = re.compile(r"Shorewall:[^:]+:(?P<action>[^:]+):.*?SRC=(?P<src>\S+).*?DST=(?P<dst>\S+)")
f = gzip.open("shorewall-2012-45.log.gz","rt")

for line in f:
    m = re.search(filter,line)
    if m:
        print(m.group("action"),m.group("src"),m.group("dst"))
