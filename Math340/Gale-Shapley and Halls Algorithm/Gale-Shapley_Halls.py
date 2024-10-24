#This function reads a priorities CSV file and returns the priorities in a single data structure
#as follows:  The top level data structure is a dictionary with two entries.  Each entry is
#indexed by a string that also serves as the prefix for each entity to be paired.  For example,
#when reading size_6_priorities.csv, the two top level keys are 'B' (for blue) and 'R' (for red).
#The values stored in the top level dictionary are two more dictionaries.  This lower level
#dictionary is indexed by an entity name (e.g. 'B3' or 'R2' from size_6_priorities.csv).  The
#lower level dictionary values are lists that indicate priorities from most desired to least
#desired.  For example, calling priorities['B']['B3'][1] would return 'R2' indicating that R2
#is B3's second choice mate.
def read_priorities(csv_filepath):
    priorities={}
    file=open(csv_filepath,"r")
    lines=file.read().split("\n")
    for line in lines:
        if line:
            tokens=line.split(",")
            label=tokens[0].strip(':')
            row_priorities=[]
            for token in tokens[1:]:
                if token.strip()!="":
                    row_priorities.append(token.strip())
            if label[0] in priorities:
                priorities[label[0]][label]=row_priorities
            else:
                priorities[label[0]]={}
                priorities[label[0]][label]=row_priorities
    file.close()
    return priorities

#This function prints a priorities structure from a file to the console.
def show_priorities(csv_path):
    priorities=read_priorities(csv_path)
    for key in priorities:
        for row in priorities[key]:
            print(row,end=": ")
            for col in priorities[key][row]:
                print(col,end=", ")
            print("")
        print("")
    return 0

#This funciton reads a set of parings from a CSV file and returns a dictionary as described:
#The entities that were designated as boys during pairing are used as the keys in the
#dictionary.  The values that are stored are the entities that the boys ended up paired to.
#For example, after reading size_6_pairings_0.csv, pairs['B2'] would return 'R4' indicating
#B2 was paired with R4.
def read_pairs(csv_filename):
    pairs={}
    file=open(csv_filename,"r")
    lines=file.read().split("\n")
    for line in lines:
        if line:
            tokens=line.split(",")
            label=tokens[0].strip(": ")
            pairs[label]=tokens[1]
    file.close()
    return pairs

#This function writes a pairs structure (as defined in the comment for read_pairs() to a CSV
#at the filepath given as a parameter.
def write_pairs(csv_filename,pairs):
    of=open(csv_filename,"w")
    for boy in pairs:
        of.write(boy)
        of.write(": ,")
        of.write(pairs[boy])
        of.write("\n")
    of.close()
    return 0

#function identifies if pairing is stable or not
def find_rogues(pairs_filename, priorities_filename, outputfilename):
    outputfile = open(outputfilename, "w")
    outputfile.write(pairs_filename)
    outputfile.write('\n')
    pairs = read_pairs(pairs_filename)
    priorities = read_priorities(priorities_filename)

    #show_priorities(pairs_filename)
    #show_priorities(priorities_filename)
    
    length = len(priorities['B'])

    counter = 0

    for i in range(length):
    
        blueIndex = 0
        currentBPair = pairs['B' + str(i)]
        #uncomment to test
        # while priorities['B']['B' + str(i)][blueIndex] != currentBPair:
        #     blueIndex += 1
        # print('\n')
        # print('priority B',i ,':', blueIndex)

        for j in range(0 , blueIndex):
            redIndex = 0
            rblueIndex = 0
            currentR = priorities['B']['B' + str(i)][j]
            while priorities['R'][currentR][redIndex] != 'B' + str(i):
                redIndex += 1

            # print(currentR, 'priority for B' + str(i) ,':', redIndex)

            for k in range(length):
                if (pairs['B' + str(k)] == currentR):
                    while priorities['R'][currentR][rblueIndex] != 'B' + str(k):
                        rblueIndex += 1
                    # print(currentR, 'priority for Current Pair B' + str(k) ,':', rblueIndex)

                    # print('B' + str(k),'Difference in value =', (redIndex - rblueIndex))
                    if (redIndex - rblueIndex < 0):
                        #print(currentR, 'and', 'B' + str(i), 'are a rogue pair')
                        outputfile.write('B' + str(i))
                        outputfile.write(' and ')
                        outputfile.write(currentR)
                        outputfile.write(' are a rogue pair')
                        outputfile.write('\n')
                        counter+=1

        # print('\n')
    
    # print(counter)
    if (counter == 0):
        outputfile.write('stable')
    return 0
def Convert(lst):
    res_dct = {lst[i]: lst[i + 1] for i in range(0, len(lst), 2)}
    return res_dct

#Gale-Shapley Algorithm creates stable pairings that are boy-favored
def pair(csv_path):
    girls = {}
    #put the girls as keys
    priorities = read_priorities(csv_path)
    #show_priorities(csv_path)
    length = len(priorities['B'])
    #create dictionary of girls
    for i in range(length):
        girls['R' + str(i)] = []
    #while there are girls without a match
    conditional = True
    while(conditional):
        #Each girl gets boys that want them first here
        for i in range(length):
            currentBoy = 'B' + str(i)
            currentBoyTopPref = priorities['B'][currentBoy][0]
            girls[currentBoyTopPref].append(currentBoy)
        #print(girls)
        #Find which boy each girl likes the best
        for i in range(length):
            if len(girls['R' + str(i)]) == 0:
                continue
            else:
                #get intial priority for first boy in girls list
                maxprio = priorities['R']['R'+str(i)].index(girls['R'+str(i)][0])
                bestsuitor = priorities['R']['R'+str(i)][maxprio]
                #get list of boys to see what you need to iterate through to check
                listofboys = girls['R'+ str(i)]
                listofboyslength = len(listofboys)
                #find bestsuitor - person girl likes the best
                for j in range(listofboyslength):
                    priority = priorities['R']['R'+str(i)].index(girls['R'+str(i)][j])
                    if priority < maxprio:
                        maxprio = priority
                        bestsuitor = priorities['R']['R'+str(i)][maxprio]
                rejected = []
                #Add those rejected to the list of rejected
                for k in range(listofboyslength):
                    checkboy = girls['R' + str(i)][k]
                    if(checkboy) != bestsuitor:
                        rejected.append(checkboy)
                #delete these rejected boys 1st priority
                lengthrejected = len(rejected)
                for m in range(lengthrejected):
                    priorities['B'][rejected[m]] = priorities['B'][rejected[m]][1:]
                    #print(priorities['B'][rejected[m]])
        #wipe girls dictionary and run the program again
        
        counter = 0
        for i in range(length):
            if (len(girls['R' + str(i)]) != 1):
                break
            else:
                counter+=1
        if counter == length:
            conditional = False
            return girls
        else:
            for i in range(length):
                girls['R' + str(i)] = []
    return 0


#Gale-Shapley Algorithm creates stable pairings that are girl-favored
def pair2(csv_path):
    boys = {}
    #put the girls as keys
    priorities = read_priorities(csv_path)
    #show_priorities(csv_path)
    length = len(priorities['R'])
    #create dictionary of girls
    for i in range(length):
        boys['B' + str(i)] = []
    #while there are girls without a match
    conditional = True
    while(conditional):
        #Each girl gets boys that want them first here
        for i in range(length):
            currentGirl = 'R' + str(i)
            currentGirlTopPref = priorities['R'][currentGirl][0]
            boys[currentGirlTopPref].append(currentGirl)
        #print(girls)
        #Find which boy each girl likes the best
        for i in range(length):
            if len(boys['B' + str(i)]) == 0:
                continue
            else:
                #get intial priority for first boy in girls list
                maxprio = priorities['B']['B'+str(i)].index(boys['B'+str(i)][0])
                bestsuitor = priorities['B']['B'+str(i)][maxprio]
                #get list of boys to see what you need to iterate through to check
                listofgirls = boys['B'+ str(i)]
                listofgirlslength = len(listofgirls)
                #find bestsuitor - person girl likes the best
                for j in range(listofgirlslength):
                    priority = priorities['B']['B'+str(i)].index(boys['B'+str(i)][j])
                    if priority < maxprio:
                        maxprio = priority
                        bestsuitor = priorities['B']['B'+str(i)][maxprio]
                rejected = []
                #Add those rejected to the list of rejected
                for k in range(listofgirlslength):
                    checkboy = boys['B' + str(i)][k]
                    if(checkboy) != bestsuitor:
                        rejected.append(checkboy)
                #delete these rejected boys 1st priority
                lengthrejected = len(rejected)
                for m in range(lengthrejected):
                    priorities['R'][rejected[m]] = priorities['R'][rejected[m]][1:]
                    #print(priorities['B'][rejected[m]])
        #wipe girls dictionary and run the program again
        
        counter = 0
        for i in range(length):
            if (len(boys['B' + str(i)]) != 1):
                break
            else:
                counter+=1
        if counter == length:
            conditional = False
            return boys
        else:
            for i in range(length):
                boys['B' + str(i)] = []
    return 0


#create dictionary with girls as keys and list of suitors per day as dictionary,
#search through here and find highest priority boy pop the rest out of the list
#Take people that were rejected, delete those rejected from priority list, reset suitors now
#check the priority list again, take those rejected and delete them from the priorities list

#how to delete from priorities, list = list[1:]

#wipe suitors, suitors = NULL dictionary

#find which suitor is best, maxpriority = priorities[R][R5].index(B0)
#for suitor in suitors['R5][1:]:
#   if prefs['R]['R5].index(suitor) < maxprioritiy
#       maxpriority = prefs['R]['R5].index(suitor)
#       bestsuitor = suitor


#This function should test Hall's conditions on a graph defined in a priorities CSV file.  It
#will ensure that all members of the boys set can be paired to a girl from the girls set.  It
#makes no guarantees that all girls can be paired to a boy.  I wrote it to return "pass" or
#"fail" as strings.
def test_halls(priorities_filename,boy_set_label,girl_set_label):
    #This helper function generates and returns the powerset of the input collection (with the
    #exception of null set).
    #source: https://stackoverflow.com/questions/1482308/how-to-get-all-subsets-of-a-set-powerset
    def powerset(iterable):
        from itertools import chain, combinations
        s = list(iterable)
        return chain.from_iterable(combinations(s, r) for r in range(1,len(s)+1))
    #TODO: test Hall's condition
    #TODO: test Hall's condition
    # Given a bipartite graph H
    # L(H) = left vertices of H / set of Boys B
    # R(H) = right vertices of H / set of Girls G
    # E(S) = Edges in a set / pairings
    # To satsify Hall's condition there must be atleast one perfect match
    # a match means L(H) -> R(H) / Every boy has a partner that is a girl
    # a graph of the total injective function L(H) -> R(H) is a subset of E(H)
    # If |S| <= |E(S)| for all sets where S is a subset of L(H) <-- This is the condition
    # If the number of boys is less than or equal to the number of pairings when the boys are a subset of the left side of the bipartite graph
    # then there exists a perfect match
    # S is any combination of boys that fall within the entire set of boys
    priorities = read_priorities(priorities_filename)
    leftSide = priorities[boy_set_label]
    numberOfBoys = len(leftSide)
    subSets = list(powerset(leftSide))
    currentSet = 0
    while currentSet != len(subSets):
        collectiveGirls = list()
        currentSubSet = subSets[currentSet]
        for boy in currentSubSet:
            boyCompatible = priorities[boy_set_label][boy]
            for girl in boyCompatible:
                if girl not in collectiveGirls:
                    collectiveGirls.append(girl)

 

        if len(currentSubSet) > len(collectiveGirls):
            return "fail"

 

        currentSet+=1

 

    return "pass"

def main():
    filepriorities = "size_6_priorities.csv"
    find_rogues("size_6_parings_0.csv", filepriorities, "rogue6_0.txt")
    find_rogues("size_6_parings_1.csv", filepriorities, "rogue6_1.txt")
    find_rogues("size_6_parings_2.csv", filepriorities, "rogue6_2.txt")
    find_rogues("size_6_parings_3.csv", filepriorities, "rogue6_3.txt")

    filepriorities = "size_10_priorities.csv"
    find_rogues("size_10_parings_0.csv", filepriorities, "rogue10_0.txt")
    find_rogues("size_10_parings_1.csv", filepriorities, "rogue10_1.txt")
    find_rogues("size_10_parings_2.csv", filepriorities, "rogue10_2.txt")
    find_rogues("size_10_parings_3.csv", filepriorities, "rogue10_3.txt")

    filepriorities = "size_25_priorities.csv"
    find_rogues("size_25_parings_0.csv", filepriorities, "rogue25_0.txt")
    find_rogues("size_25_parings_1.csv", filepriorities, "rogue25_1.txt")
    find_rogues("size_25_parings_2.csv", filepriorities, "rogue25_2.txt")
    find_rogues("size_25_parings_3.csv", filepriorities, "rogue25_3.txt")

    filepriorities = "size_100_priorities.csv"
    find_rogues("size_100_parings_0.csv", filepriorities, "rogue100_0.txt")
    find_rogues("size_100_parings_1.csv", filepriorities, "rogue100_1.txt")
    find_rogues("size_100_parings_2.csv", filepriorities, "rogue100_2.txt")
    find_rogues("size_100_parings_3.csv", filepriorities, "rogue100_3.txt")


    girlsdict = {}
    boysdict = {}
    outputfile = open("stableBoyPref.txt", "w")   
    girlsdict = pair(filepriorities)
    outputfile.write(filepriorities)
    outputfile.write("\n")
    outputfile.write(str(girlsdict))
    outputfile.write("\n")

    filepriorities = "size_10_priorities.csv"
    girlsdict = pair(filepriorities)
    outputfile.write(filepriorities)
    outputfile.write("\n")
    outputfile.write(str(girlsdict))
    outputfile.write("\n")

    filepriorities = "size_25_priorities.csv"
    girlsdict = pair(filepriorities)
    outputfile.write(filepriorities)
    outputfile.write("\n")
    outputfile.write(str(girlsdict))
    outputfile.write("\n")    

    filepriorities = "size_100_priorities.csv"
    girlsdict = pair(filepriorities)
    outputfile.write(filepriorities)
    outputfile.write("\n")
    outputfile.write(str(girlsdict))
    outputfile.write("\n")

    outputfile.close()
    

    outputfile = open("stabelGirlPref.txt", "w")   
    filepriorities = "size_6_priorities.csv" 
    boysdict = pair2(filepriorities)
    outputfile.write(filepriorities)
    outputfile.write("\n")
    outputfile.write(str(boysdict))
    outputfile.write("\n")

    filepriorities = "size_10_priorities.csv"
    boysdict = pair2(filepriorities)
    outputfile.write(filepriorities)
    outputfile.write("\n")
    outputfile.write(str(boysdict))
    outputfile.write("\n")

    filepriorities = "size_25_priorities.csv"
    boysdict = pair2(filepriorities)
    outputfile.write(filepriorities)
    outputfile.write("\n")
    outputfile.write(str(boysdict))
    outputfile.write("\n")    

    filepriorities = "size_100_priorities.csv"
    boysdict = pair2(filepriorities)
    outputfile.write(filepriorities)
    outputfile.write("\n")
    outputfile.write(str(boysdict))
    outputfile.write("\n")

    outputfile.close()

    #replace filrepairings and filepriorities depending on what is tested - does not print to output files because process takes around 2-5 mins based on size of files
    filepairings = "size_6_parings_0.csv"

    filepriorities = "size6-1.txt"

    #find_rogues(filepairings, filepriorities)

    testOutcome = test_halls(filepriorities, 'B', 'R')

    print(testOutcome)


    return 0

#Here's where main() and/or test() gets executed when you run this script.
main()
