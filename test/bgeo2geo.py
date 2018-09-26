#
# This command line script can be used to turn a .bgeo file into .geo (ascii)
# version of the same file. The nice thing about this is that the exact
# structure of the binary format is preserved to make it easier to debug
# parsing the binary. Writing .geo out from Houdini will sometimes lead to
# a different structure that is more optimal for reading.
#
# Based on an example from 
# http://www.sidefx.com/docs/hdk/_h_d_k__g_a__using.html#HDK_GA_FileFormat
#

import sys

try:
	# Try for ASCII/binary support
	import hjson
	json = hjson
except:
	# Fall back to only ASCII support
	import simplejson
	json = simplejson

if len(sys.argv) != 3:
	print('arguments: in.bgeo out.geo')
	sys.exit(1)

bgeo = json.load(open(sys.argv[1], 'r'))
json.dump(bgeo, open(sys.argv[2], 'w'), binary=False, indent=4)
