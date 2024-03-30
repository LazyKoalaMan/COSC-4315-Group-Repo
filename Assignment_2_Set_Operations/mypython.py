import sys
import re
#import removeDuplicates
#from removeDuplicates import duplicateRemover


def count_elements_recursive(input_list):
    if not input_list:
        return 0
    return 1 + count_elements_recursive(input_list[1:])

def replace_string(original_string, target, replacement):
    if target not in original_string:
        return original_string
    index = original_string.find(target)
    modified_string = original_string[:index] + replacement + replace_string(original_string[index + count_elements_recursive(target):], target, replacement)

    return modified_string

'''the following auxilary function will count the number of occurrences
of elemToCheck in listX''' 
def occurrenceCounter(listX, elemToCheck, size) :
    if size < 1 : 
        return 0
    else :
        if listX[size - 1] == elemToCheck :
            return 1 + occurrenceCounter(listX, elemToCheck, size - 1)
        else :
            return 0 + occurrenceCounter(listX, elemToCheck, size - 1)

'''numOccurrences should be based on the use of occurrenceCounter
for the same listX, elemToCheck, and size that are passed in;
if so, it will return a list without the duplicates'''
def deletion(listX, elemToCheck, numOccurrences, size) :
    if size < 1 :
        return []
    else :
        if (listX[size - 1] == elemToCheck and numOccurrences > 1) :
            return deletion(listX, elemToCheck, numOccurrences - 1, size - 1) + []
        else :
            return deletion(listX, elemToCheck, numOccurrences, size - 1) + [listX[size - 1]]


#===========================================Main=============================================================

with open("example1.txt", "r") as file:
    lines1=[]
    func=dict()
    amount=0
    funcExist=False

    
    for line in file:
        if(line[0]!="#"):
            lines1.append(line)

        if(funcExist==True):
            if(line.find("return")>0):
                funcExist=False
            func[amount].append(line)
        else:
            if(line.find("def")==-1 and funcExist==False and amount>=1):#Handles test case if there is more than 1 return.
                func[amount].append(line)

            start_index=line.find("def")
            end_index=line.find("def")+len("def")
            if(line[start_index:end_index]=="def" and funcExist==False):
                amount+=1
                func[amount]=[line]
                funcExist=True



    print(lines1)
    modified_lines = []
    in_function = False
    amount=1        

    with open("output.txt", "w") as result_file:
        for line in func:
            result_file.write(str(func[line])+" \n")
            amount+=1
