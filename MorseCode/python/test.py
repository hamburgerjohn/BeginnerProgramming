#cmake .. && make && python ../test.py
from asyncore import write
from pickletools import pyunicode
import build.morse
from build.morse import *

def func(x):
    decipher = PyMorseCodeDecipher()
    writer = PyMorseCodePlayer()

    if x == 7:
        filename = input("Enter filename: ")
        writer.PlayMorse(filename)
        return

    phrase = input("Enter Phrase: ")
   
    if x == 1:
        print("\n" + decipher.ConvertToEnglish(phrase))
        return
    if x == 2:
        print("\n" + writer.ConvertToMorse(phrase))
        return

    filename = ""
    filename = input("Enter filename: ")
    decipher.SetFilename(filename)
    decipher.Decipher()
    
    if x == 3:
        print("\n" + decipher.GetDecipheredCode())
        return
    
    if x == 4:
        print("\n" + decipher.ConvertToEnglish(decipher.GetDecipheredCode()))
        return
    
    writer.InitWAVE(filename)

    if x == 5:
        writer.SetCode(phrase)
    
    if x == 6:
        writer.ConvertToMorse(phrase)
    
    writer.RecordMorse()

while(True):
    x = int(input("1: Morse to English 2: English to Morse \n3: Morse from audio 4: English from audio \n5: Morse to audio   6: English to audio\n7: Play Audio\n"))

    match x:
        case 1:
            func(x)
        case 2:
            print(x)
            func(x)
        case 3:
            func(x)
        case 4:
            func(x)
        case 5:
            func(x)
        case 6:
            func(x)
        case 7:
            func(x)
            

