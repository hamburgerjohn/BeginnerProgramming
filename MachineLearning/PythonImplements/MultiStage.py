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
    GetPairedBaskets(baskets, sfrequent_items, 1, None) #generate pairs in each basket
    
    
    for i in range(0 , bucket_num): #insert empty buckets to create bitmap
        buckets.setdefault(i, 0)

    bitmap = BitMap()
    buckets.clear() 
    SecondPass(sfrequent_items, threshold, bucket_num, baskets, bitmap)#call second pass

def SecondPass(sfrequent_items, threshold, bucket_num, baskets, bitmap):
    
    candidate_pairs = []
    temp = []

    firstBitmap = bitmap
    candidate_pairs = list(combinations(sorted(sfrequent_items), 2)) #create pairs of frequent items
    
    
    for pair in candidate_pairs: #check if candidate pair hashed to populat bucket
        support = (int(pair[0]) + int(pair[1])) % bucket_num 
        if firstBitmap[support] == 1:
            temp.append(pair)

    candidate_pairs = temp
   
    GetPairedBaskets(baskets, sfrequent_items, 2, firstBitmap) #GetPairs a second time to setup second bitmap
    
    for i in range(0 , bucket_num + 2):
        buckets.setdefault(i, 0)
    
    secondBitmap = BitMap()

    ThirdPass(candidate_pairs, sfrequent_items, firstBitmap, secondBitmap, baskets)

    

def ThirdPass(candidate_pairs, sfrequent_items, firstBitmap, secondBitmap, baskets):
    
    global frequent_pairs
    temp = []

    GetPairedBaskets(baskets, sfrequent_items, 3, firstBitmap) #GetPairs a third time to setup third bitmap

    for i in range(0 , bucket_num + 8):
        buckets.setdefault(i, 0)

    thirdBitmap = BitMap()


    for pair in candidate_pairs: #check if candidate pairs hashed to frequent buckets both passes
        support = (int(pair[0]) + int(pair[1])) % bucket_num 
        if firstBitmap[support] == 1:
            support = (int(pair[0]) * int(pair[1])) % bucket_num + 2
            if secondBitmap[support] == 1:
                support = (int(pair[0]) * int(pair[1])) % bucket_num + 8
                if thirdBitmap[support] == 1:
                    temp.append(pair)

    frequent_pairs = temp
    GetPairedBaskets(baskets, None, None, None) #count candidate pairs
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
               


def GetPairs(baskets, frequent_items, pass_num, bitmap): #hash each pair to bucket
    
    
    for pair in baskets:          
        if pair[0] not in pair[1]:

            if pass_num == 3:
                support = (int(pair[0]) + int(pair[1])) % bucket_num + 8 # i * j mod bucket_num hash for third pass (extra hashtable)
                buckets.setdefault(support, 0)
                buckets[support]+= 1

            elif pass_num == 2: 
                support = (int(pair[0]) * int(pair[1])) % bucket_num + 2  # i * j mod bucket_num hash for second pass
                buckets.setdefault(support, 0)
                buckets[support]+= 1
                        
            else:
                support = (int(pair[0]) + int(pair[1])) % bucket_num # i + j mod bucket_num hash for second pass
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

def GetPairedBaskets(baskets, sfrequent_items, pass_num, bitmap): #generate pairs from data

    result = []
    set1 = set(frequent_pairs)


    for basket in baskets:
        pairs = list(combinations(sorted(basket), 2)) #generate pairs from basket
         
        
        if frequent_pairs:
            set2 = set(pairs)
            paird = tuple(set2.intersection(set1))
            for pair in paird:
                if pair in boom:
                    boom[pair]+=1
                else:
                    boom.setdefault(pair, 1)

        else:
            GetPairs(pairs, sfrequent_items, pass_num, bitmap)#hash pairs to buckets
    
                 

        
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