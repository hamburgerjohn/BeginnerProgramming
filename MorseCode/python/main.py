import build.morse
from build.morse import *
from tkinter import *

decipher = PyMorseCodeDecipher()
writer = PyMorseCodePlayer()



root = Tk()

e1 = Entry(root, width=70, borderwidth=5)
e2 = Entry(root, width=70, borderwidth=5)
e3 = Entry(root, width=70, borderwidth=5)

e1.grid(row=1, column=2)
e2.grid(row=3, column=2)
e3.grid(row=5, column=2)


l1 = Label(root, text= "Result")

l1.grid(row=4, column=2)

f = ""
p = ""

def func(b):

    global f,p
    
    if b == 3:
        pass
    
    if b == 4:
        writer.InitWAVE(f)
        writer.SetCode(p)
        writer.RecordMorse()
  
    if b == 5:
        print(f, p)
        writer.InitWAVE(f)
        writer.ConvertToMorse(p)
        writer.RecordMorse()
    if b == 6:
        writer.PlayMorse(f)
    
    if b == 7:
        f = e1.get()
       
    
    if b == 8:
        p = e2.get()
        

        


buttons = [ #why is this in a list
    Button(root, text="Morse to English", padx=50,command=lambda m=0 : func(0)).grid(row=1,column=0),
    Button(root, text="English to Morse",padx=50,command=lambda m=0 : func(1)).grid(row=3,column=0),
    Button(root, text="Morse from audio",padx=48,command=lambda m=0 : func(2)).grid(row=5,column=0),
    Button(root, text="English from audio",padx=44,command=lambda m=0 : func(3)).grid(row=1,column=1),
    Button(root, text="Morse to audio",padx=54,command=lambda m=0 : func(4)).grid(row=3,column=1),
    Button(root, text="English to audio",padx=50,command=lambda m=0 : func(5)).grid(row=5,column=1),
    Button(root, text="Play audio",padx=65,command=lambda m=0 : func(6)).grid(row=9,column=0),
    Button(root, text="Set Filename",padx=65,command=lambda m=0 : func(7)).grid(row=0,column=2),
    Button(root, text="Set Phrase",padx=65,command=lambda m=0 : func(8)).grid(row=2,column=2),
]



root.mainloop()