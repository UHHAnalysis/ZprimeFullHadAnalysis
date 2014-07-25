from subprocess import call, check_output
from sys import argv
from math import ceil
nl=float(check_output(["wc", "-l",argv[1]]).split(' ')[0])
print nl
number_of_files=float(argv[3])
lines_per_file=int(ceil(nl/number_of_files))
cmd=['split','-d','-l',str(lines_per_file),argv[1],argv[2]]
print' '.join(cmd)
call(cmd)
call(['ls '+argv[2]+'*'],shell=True)
