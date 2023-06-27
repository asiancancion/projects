import csv

def read_csv(file_path):
    names = []
    salaries = []
    with open(file_path, 'r') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)  # Skip the header row
        for row in reader:
            names.append(row[0])
            salaries.append(float(row[1]))  # Assuming salary is a floating-point number
    return names, salaries

def Cloning(li1):
    li_copy = li1[:]
    return li_copy

# Replace 'salaries.csv' with the actual path to your CSV file
print("Input the name of your csv files with employees in the first column and salaries in the second column")
employee_file = input()
# employee_file = "salaries.csv"
names_list, salaries_list = read_csv(employee_file)

# print("Employee Names:", names_list)
# print("Salaries:", salaries_list)




test = True
meetinglist = []
employee_names = Cloning(names_list)
while (test == True):
    print("List of Employees:")
    length = len(employee_names)
    for i in range(length):
        print((int(i)+1), employee_names[i])
    print(" ")

    print("Current meeting members:")
    if (len(meetinglist) == 0):
        print("[No Members]")
    else:
        print(meetinglist)
    if (len(employee_names) == 0):
        break
    print("Who will be attending the meeting? Type \'all\' for everyone, \'end\' to stop adding names, and the number next to employee's names to add individuals")
    response = input()
    if (response == "all"):
        meetinglist = employee_names
        break
    if (response == "end"):
        break
    else:
        employee_chosen = employee_names[int(response)-1]
        employee_names.remove(employee_chosen)
        meetinglist.append(employee_chosen)
        print(" ")
        

print("Members at the meeting: ")
numemployees = int(len(meetinglist))

numemployees = int(len(meetinglist))
totalsalaray = 0

for i in range(numemployees):
    print(meetinglist[i])
    current = meetinglist[i]
    index = names_list.index(current)
    salary = salaries_list[index]
    salary/= 2080
    salary/=60
    totalsalaray+=salary
# print(totalsalaray)

print("How long is the meeting planned for in minutes")
meeting_length = int(input())
print(" ")

totalcost = totalsalaray*meeting_length

print("Cost of your meeting is")
print(f'${totalcost:.2f}')

print("How long did your meeting last")
actualtime = int(input())

print("")

if (actualtime < meeting_length):
    print("Congrats! You saved: ")
    saved = totalcost - actualtime*totalsalaray
    print(f'${saved:.2f}')
    print("Total Meeting cost: ")
    print(f'${actualtime*totalsalaray:.2f}')

else:
    print("You costed an additional: ")
    additional = actualtime*totalsalaray - totalcost
    print(f'${additional:.2f}')
    print("Total Meeting cost: ")
    print(f'${actualtime*totalsalaray:.2f}')