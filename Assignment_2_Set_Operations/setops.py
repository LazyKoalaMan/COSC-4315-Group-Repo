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

def duplicateRemover(listX, size) :
    '''note why I'm using 1'''
    if size < 1 :
        return listX
    else : 
        numOccurrences = occurrenceCounter(listX, listX[size - 1], count_elements_recursive(listX))
        newList = deletion(listX, listX[size - 1], numOccurrences, count_elements_recursive(listX))
        #if the list hasn't been reduced, then I need to reduce the passed in size by one
        #otherwise, I shouldn't
        if (count_elements_recursive(listX) == count_elements_recursive(newList)) :
            return duplicateRemover(newList, size - 1)
        else :
            size = count_elements_recursive(newList)
            return duplicateRemover(newList, size)

def bubble_sort(ar):

    # Base Case: If array
    # contains a single element
    if count_elements_recursive(ar) <= 1:
        return ar

    # Base Case: If array
    # contains two elements
    if count_elements_recursive(ar) == 2:
        return ar if ar[0] < ar[1] else [ar[1], ar[0]]

    # Store the first two elements
    # of the list in variables a and b
    a, b = ar[0], ar[1]

    # Store remaining elements
    # in the list bs
    bs = ar[2:]

    # Store the list after
    # each recursive call 
    res = []

    # If a < b 
    if a < b:
        res = [a] + bubble_sort([b] + bs)

    # Otherwise, if b >= a
    else:
        res = [b] + bubble_sort([a] + bs)

    # Recursively call for the list
    # less than the last element and
    # and return the newly formed list
    return bubble_sort(res[:-1]) + res[-1:]
 #//https://www.geeksforgeeks.org/sort-an-array-using-bubble-sort-without-using-loops/




#===========================================Main=============================================================

with open("example.txt", "r") as file:
    lines1=[]
    lines2=[]
    lines3=[]
    for line in file:
        line=line.lower()
        line = line.replace(".", ",").replace(" ", ",")
        lines1=line.split(",")


bubble_sort(lines1)
bubble_sort(lines2)

print(lines1)
print(count_elements_recursive(lines1))
print("Duplicate Checker")
lines1=duplicateRemover(lines1,count_elements_recursive(lines1))

print(lines1)
print(lines2)
lines3=perform_set_operation(lines1,lines2,"union")
lines3=perform_set_operation(lines1,lines2,"intersection")
lines3=perform_set_operation(lines1,lines2,"difference")

bubble_sort(lines3)
print(lines3)

with open("result1.txt", "w") as result_file:
    for line in lines3:
        result_file.write(line+" ")
