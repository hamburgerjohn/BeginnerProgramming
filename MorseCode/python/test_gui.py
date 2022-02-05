import build.morse
from build.morse import *
from tkinter import *
import asyncio
from pickletools import pyunicode

root = Tk()

e1 = Entry(root, width=70, borderwidth=5)
e2 = Entry(root, width=70, borderwidth=5)
text = Text(root, state='disabled', width=70, height=35)
e1.grid(row=1, column=2)
e2.grid(row=3, column=2)
text.grid(row=5, column=2)


l1 = Label(root, text= "Result")

l1.grid(row=4, column=2)

decipher = PyMorseCodeDecipher()
writer = PyMorseCodePlayer()


def func(b):
    

    if b == 0:
        writer.SetFilename(e1.get())
        decipher.SetFilename(e1.get())

    if b == 1:
        writer.SetPhrase(e2.get())
        decipher.SetPhrase(e2.get())
    
    if b == 2:
        writer.SetPhrase(e2.get())
        writer.InitWAVE()
        writer.ConvertToMorse()
        writer.RecordMorse()
    
    if b == 3:
        writer.SetPhrase(e2.get())
        writer.InitWAVE()
        writer.RecordMorse()
    
    if b == 4:
        decipher.Decipher()
        text.configure(state="normal")
        text.insert(INSERT, decipher.ConvertToEnglish() + '\n')
        text.configure(state="disabled")
    
    if b == 5:
        decipher.Decipher()
        text.configure(state="normal")
        text.insert(INSERT, decipher.GetDecipheredCode() + '\n')
        text.configure(state="disabled")

    if b == 6:
        writer.PlayMorse()

b1=Button(root, text="Set Filename",padx=65,command=lambda m=0 : func(0)).grid(row=0,column=2)
b2=Button(root, text="Set Phrase",padx=65,command=lambda m=0 : func(1)).grid(row=2,column=2)
b3=Button(root, text="English to audio",padx=50,command=lambda m=0 : func(2)).grid(row=1,column=1)
b4=Button(root, text="Morse to audio",padx=54,command=lambda m=0 : func(3)).grid(row=3,column=1)
b5=Button(root, text="English from audio",padx=44,command=lambda m=0 : func(4)).grid(row=1,column=0)
b6=Button(root, text="Morse from audio",padx=48,command=lambda m=0 : func(5)).grid(row=3,column=0)
b7=Button(root, text="Play audio",padx=65,command=lambda m=0 : func(6)).grid(row=5,column=0)

root.mainloop()