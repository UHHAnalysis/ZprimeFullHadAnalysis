import operator
print 'open'
file_names=["dust/outHT","dust/outMJ_B","dust/outMJ_C","dust/outMJ_D"]
events=[]
for i in file_names:
    print i
    f=open(i,'r')
    lines=f.readlines()
    f.close()
    for j in lines:
        elements=j.split(' ')
        if elements[0]=='iniziaqui':
           events.append((int(elements[1]),int(elements[2]),int(elements[3])))
sorted_events=sorted(events, key=operator.itemgetter(0, 1, 2))
#print sorted_events
#print len(sorted_events)
outfile=open('allhad_hep_eventlist','w')
for i in sorted_events:
    line=str(i[0])+' '+str(i[1])+' '+str(i[2])+'\n'
    #print line
    outfile.write(line)
outfile.close()


