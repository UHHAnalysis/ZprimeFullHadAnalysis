import operator
print 'open'
f1 = open('evtout', 'r')
f2 = open('data_events_sorted.txt', 'r')
list1=[]
list2=[]
list3=[]
f1l=f1.readlines()
f2l=f2.readlines()
print 'fill'
cnt=0
for i in f1l:
  cnt+=1
  if cnt%1000000==0:
    print cnt*1.0/len(f1l)
  ia=i.split(' ')
  if ia[0]=='iniziaqui':
    list1.append((int(ia[1]),int(ia[2]),int(ia[3])))
    list3.append((int(ia[1]),int(ia[2]),int(ia[3]),float(ia[4]),float(ia[5]),float(ia[6]),float(ia[7]),float(ia[8]),float(ia[9]),float(ia[10]),float(ia[11]),float(ia[12])))
for i in f2l:
  ia=i.split(' ')
  list2.append((int(ia[0]),int(ia[1]),int(ia[2])))
print 'sort'
slist1 = sorted(list1, key=operator.itemgetter(0, 1, 2))
slist3 = sorted(list3, key=operator.itemgetter(0, 1, 2))
#slist2 = sorted(list2, key=operator.itemgetter(0, 1, 2))

#print slist1
print 'check'
intersection = set(list1) & set(list2)
intersection_sorted = sorted(intersection, key=operator.itemgetter(0, 1, 2))
print intersection_sorted
print len(intersection_sorted)

last_index=0
for i in range(len(intersection_sorted)):
  for j in range(last_index,len(slist1)):
    if intersection_sorted[i][0]==slist1[j][0] and intersection_sorted[i][1]==slist1[j][1] and intersection_sorted[i][2]==slist1[j][2]:
      print slist3[j]
      #print slist1[j]
      #print intersection_sorted[i]
      #print 'bla'
      last_index=j
      break
#cnt=0
#lastcount=1
#for i in range(len(slist1)):
  #for j in range(lastcount-1,len(slist2)):
    #cnt+=1
    #if cnt%1000000==0:
      #print 1.0*cnt/(len1*len2)
    #if list1[i][0]==list2[j][0]:#equal
    #elif list1[i][0]==list2[j][0]:
     
    #if run1[i]==run2[j] and lumi1[i]==lumi2[j] and evt1[i]==evt2[j]:
      #print  run1[i],lumi1[i],evt1[i]
  
  #print run1