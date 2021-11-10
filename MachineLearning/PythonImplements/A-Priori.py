import sys
import re
import multiprocessing as mp,os
from itertools import combinations
from itertools import islice
from collections import OrderedDict
import time

buckets = {} #stores bucket values 

def FirstPass(filename, threshold, chunk):
    baskets = GetBaskets(filename, chunk)#generate baskets from data
    item_frequencies = ItemFrequencies(baskets)#get individual item counts
    frequent_items = FrequentItems(item_frequencies, threshold)#determine if item if frequent or not (count >= threshold)
    sfrequent_items = Simplified(frequent_items)
    SecondPass(sfrequent_items, baskets)


def SecondPass(sfrequent_items, baskets):
    candidate_pairs = []
    candidate_pairs = list(combinations(sorted(sfrequent_items), 2))#create pairs with frequent items 
    frequent_pairs = GetPairs(baskets, candidate_pairs)


def GetPairs(baskets, candidate_pairs):
    frequent_pairs = {}
    set2 = set(candidate_pairs)

    for basket in baskets:
        pairs = list(combinations(sorted(basket), 2)) #create pair combinations from basket 
        set1 = set(pairs)
        pair = tuple(set1.intersection(set2))#check if a frequent pair is in basket
        
        for p in pair:
            if p in frequent_pairs:
                frequent_pairs[p]+=1
            else:
                frequent_pairs.setdefault(p, 0)
                
   
        
    for (key,value) in frequent_pairs.items():
        if value < threshold:
            frequent_pairs.pop(key)

        else:
            print key, "occurs", value, "times"


def ItemFrequencies(baskets): #counts frequency of each item
    
    result = [] #to store recorded frequency of each item
    itemFreq = {}

    for basket in baskets: #sorts into dictionaries, counts number of time item appears in different baskets
        for item in basket:
            itemFreq.setdefault(item, 0)
            itemFreq[item] += 1  

    for(item, count) in itemFreq.items(): #returns in a list the frequency of each item
        result.append([item, count])

    return result


def FrequentItems(item_frequencies, support): #gets frequent items above threshold
    itemFreq = len(item_frequencies[0]) - 1 
    frequent_items = []

    for item in item_frequencies:
        if item[itemFreq] >= support: #checks if item frequency >= support
            frequent_items.append(item[:-1])
    
    
    frequent_items.sort()
    return frequent_items


def GetBaskets(filename, chunk): #get each basket/line from input file
    
    baskets = [] #list to hold each basket
    count = 0

    with open(filename) as f:
        for line in f:
            count += 1
            baskets.append(line.split())
            if count == int(chunk):
                break

    f.close()
    return baskets


def Simplified(frequent_items):#creates singleton dict of frequent items
    freqItems = {}

    for items in frequent_items:
        for item in items:
            freqItems.setdefault(item, 0)

    keys = freqItems.keys()
    
    
    return keys

if __name__ == '__main__':
    start = time.time()
    num_of_baskets = 88000
    filename = sys.argv[1]
    chunk = float(sys.argv[2]) * num_of_baskets
    threshold = float(sys.argv[3]) * float(chunk)
    
   
    FirstPass(filename, int(threshold), float(chunk))
             #retail.txt, threshold,      chunk size,    

    end = time.time() - start
    print(end * 1000)