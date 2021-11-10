import sys
import re
import multiprocessing as mp,os
from itertools import combinations
from collections import OrderedDict
import time


buckets = {} #stores bucket values 
frequent_pairs = []
boom = {}


def FirstPass(filename, threshold, chunk, bucket_num):
    
    baskets = GetBaskets(filename, chunk)#generate baskets from data
    item_frequencies = ItemFrequencies(baskets)#get individual item counts
    frequent_items = FrequentItems(item_frequencies, threshold)#determine if item if frequent or not (count >= threshold)
    sfrequent_items = Simplified(frequent_items)
    GetPairedBaskets(baskets) #generate pairs in each basket
    
    for i in range(0 , bucket_num): #insert empty buckets to create bitmap
        buckets.setdefault(i, 0)

    bitmap = BitMap()
    buckets.clear() 
    SecondPass(sfrequent_items, threshold, bucket_num, baskets, bitmap)#call second pass

def SecondPass(sfrequent_items, threshold, bucket_num, baskets, bitmap):
    
    candidate_pairs = []
    firstBitmap = bitmap  
    candidate_pairs = list(combinations(sorted(sfrequent_items), 2)) #create candidate paris from frequent individual items
    for pair in candidate_pairs:
        support = (int(pair[0]) * int(pair[1])) % bucket_num 
        if bitmap[support] == 1:
            frequent_pairs.append(pair)

    GetPairedBaskets(baskets)
    DisplayFreq()


    
def DisplayFreq():
    
    for (key, value) in boom.items():
        if value >= threshold:
            print(key, "Occured", value, "Times")

def BitMap(): #replaces buckets by bits
    bit_map = []
    
    for(key, value) in buckets.items():
        if value < threshold:
            bit_map.insert(key, 0) #non requent bucket
        else:
            bit_map.insert(key, 1) #frequent bucket

    
    return bit_map
               


def GetPairs(baskets): #hash each pair to basket
    
    for pair in baskets:          
        if pair[0] not in pair[1]:
                support = (int(pair[0]) * int(pair[1])) % bucket_num # i + j mod bucket_num hash 
                buckets.setdefault(support, 0)
                buckets[support]+= 1
    

def Simplified(frequent_items):#creates singleton dict of frequent items
    freqItems = {}

    for items in frequent_items:
        for item in items:
            freqItems.setdefault(item, 0)

    keys = freqItems.keys()
    
    
    return keys
    
    
def FrequentItems(item_frequencies, support): #gets frequent items above threshold
    itemFreq = len(item_frequencies[0]) - 1 
    frequent_items = []

    for item in item_frequencies:
        if item[itemFreq] >= support: #checks if item frequency >= support
            frequent_items.append(item[:-1])
    
    
    frequent_items.sort()
    return frequent_items


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

def GetPairedBaskets(baskets): #generate pairs from data
    result = []
    set2 = set(frequent_pairs)
    
    for basket in baskets:
        pairs = list(combinations(sorted(basket), 2)) #generate pairs from basket
        set1 = set(pairs)

        if frequent_pairs:
            paird = tuple(set1.intersection(set2))
            for pair in paird:
                if pair in boom:
                    boom[pair]+=1
                else:
                    boom.setdefault(pair, 1)


        else:
            GetPairs(pairs)#hash pairs to buckets             

        
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


if __name__ == '__main__':
    time_start = time.time()
    num_of_baskets = 88000
    filename = sys.argv[1]
    bing = sys.argv[3]
    chunk = float(sys.argv[2]) * num_of_baskets
    threshold = float(bing) * float(chunk)
    
    
    bucket_num = 71

    FirstPass(filename, float(threshold), float(chunk), bucket_num)
             #retail.txt, threshold,      chunk size,     num of buckets

    end = time.time() - time_start
    print(end * 1000)