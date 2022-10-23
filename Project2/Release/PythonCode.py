import re
import string
import os.path
from os import path


#Description:
# The CallProcedure function must receive the function name in order to be called	
#Example:
#	callProcedure("TotalingAll");
#Output:
#	returns a list of all CS210 unique items and prints every instance of each
#Return:
#	None

def TotalingAll():
    #Open the file in read-only mode
    text = open("CS210_Text_Input_File.txt", "r")

    # Make a blank dictionary to keep "found" words in.
    dictionary = dict()

    # Verify every line in the input file
    for line in text:
        # if there are any extra spaces or newlines, remove them
        line = line.strip()

        # For better matching, lowercase characters will be converted
        word = line.lower()
        
        #Verify the dictionary to see if the word is there
        if word in dictionary:
            dictionary[word] = dictionary[word] + 1
        else:
            dictionary[word] = 1

    #Print out the dictionary's entire contents
    for key in list (dictionary.keys()):
        print(key.capitalize(), ":", dictionary[key])
    # Close the active document
    text.close()



#Description:
#	User must input the desired search phrase and this function to the CallIntFunc function in order to call it.
#Example:
#	callIntFunc("CountOccurrences", lookupTerm);
#Output:
#	Returns the number of occurrances of the desired search term.
#Return:
#	int wordCounter
def CountOccurrences(lookupTerm):

    #Convert user-inputted search term to lowercase for better matching
    lookupTerm = lookupTerm.lower()

    #Open the file in read mode
    text = open("CS210_Text_Input_File.txt", "r")

    #Create variable to track how many times the search term has been "found"
    wordCounter = 0

    #Check each line of the input file
    for line in text:
        line = line.strip()
        word = line.lower()
        if word == lookupTerm: #Verify that the retrieved word matches the user's input
            wordCounter += 1
    return wordCounter  #Return the specified number of times the search term was found
     #Close opened file
    text.close()



#Count each item's appearances, then add them up to find the frequency. dat

#Description:
#	Send this function to the CallProcedure function in order to call it.
#Example:
#	callProcedure("CollectingData");
#Output:
# returns a document (frequency.dat) containing each distinct word and the quantity of times it appears.	
#Return:
#	frequency.dat
def CollectingData():
    text = open("CS210_Text_Input_File.txt", "r")
    frequency = open("frequency.dat", "w")

    #Make a blank dictionary to keep "found" words in.
    dictionary = dict()

   
    for line in text:
        line = line.strip()
        word = line.lower()
        
       #Verify the word's inclusion in the dictionary
        if word in dictionary:
            dictionary[word] = dictionary[word] + 1
        else:
           # Add a value of 1 if the word isn't in the dictionary.
            dictionary[word] = 1

   # Each key and value pair should be written to frequency.dat
    for key in list (dictionary.keys()):
        # Format the key-value pair as strings and add a newline after each string.
        frequency.write(str(key.capitalize()) + " " + str(dictionary[key]) + "\n")

    #Close any active files.
    text.close()
    frequency.close()