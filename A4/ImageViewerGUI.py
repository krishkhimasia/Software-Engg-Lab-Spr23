from my_package.model import ImageCaptioningModel
from my_package.model import ImageClassificationModel
from tkinter import *
from functools import partial
from PIL import ImageTk, Image
from tkinter import filedialog


def fileClick(clicked):
    # Define the function you want to call when the filebrowser button (Open) is clicked.
    # This function should pop-up a dialog for the user to select an input image file.
    # To have a better clarity, please check out the sample video.

    # declared img_path as a global variable so that it can be used in the process function
    global img_path

    img_types = [("jpg Images", "*.jpg")]
    img_path=filedialog.askopenfilename(initialdir="./data/imgs", filetypes=img_types, title="Select an image file")
    img=ImageTk.PhotoImage(Image.open(img_path))
    e.delete(0,5)
    e.insert(0,img_path[len(img_path)-5:len(img_path)])
    imgLabel=Label(root, image=img)
    imgLabel.grid(row=1,column=0,columnspan=4)


def process(clicked,captioner, classifier):
    # This function will produce the required output when 'Process' button is clicked.
    # Note: This should handle the case if the user clicks on the `Process` button without selecting any image file.
    if(e.get()==""):
        print("Select a file first!")
        return
    if(selected_option.get()=="Caption"):
        caps=captioner(img_path,3)
        output.config(text="Top 3 captions:\n\n"+caps[0]+"\n"+caps[1]+"\n"+caps[2])
        output.config(padx=50, pady=50, borderwidth=1, relief="solid")
    else:
        Classes = classifier(img_path,3)
        Class_list = []
        for Class in Classes:
            Class_list.append(Class[1]+" : "+str(100*Class[0])+"%")
        output.config(text="Top 3 classes:\n\n"+Class_list[0]+"\n"+Class_list[1]+"\n"+Class_list[2])
        output.config(padx=10, pady=50, borderwidth=1, relief="solid")

if __name__ == '__main__':
    # Complete the main function preferably in this order:
    # Instantiate the root window.
    # Provide a title to the root window.
    # Instantiate the captioner, classifier models.
    # Declare the file browsing button.
    # Declare the drop-down button.
    # Declare the process button.
    # Declare the output label.

    # created the root window
    root=Tk()
    root.title("Image Captioner/Classifier")
    root.minsize(400,10)
    
    # instantiated the captioner and classifier models
    captioner=ImageCaptioningModel()
    classifier=ImageClassificationModel()
    
    # declared the elements of my GUI
    selected_option=StringVar()
    selected_option.set("Caption")
    e=Entry(root, width=50)
    dropDown = OptionMenu(root, selected_option, "Caption", "Classify")
    openButton=Button(root, text="Open", command=partial(fileClick,True))
    processButton=Button(root, text="Process", command=partial(process, True, captioner, classifier))
    output=Label(root)
    
    # used grid to place the elements in the root window
    e.grid(row=0,column=0)
    openButton.grid(row=0,column=1)
    dropDown.grid(row=0,column=2)
    processButton.grid(row=0,column=3)
    output.grid(row=0,column=5,rowspan=2)
    output.config(font="")
    
    # run the root window's mainloop
    root.mainloop()
