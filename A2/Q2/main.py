#Imports
from my_package.model import ImageCaptioningModel
from my_package.data import Dataset, Download
from my_package.data.transforms import FlipImage, RescaleImage, BlurImage, CropImage, RotateImage
import numpy as np
from PIL import Image
import os


def experiment(annotation_file, captioner, transforms, outputs):
    '''
        Function to perform the desired experiments

        Arguments:
        annotation_file: Path to annotation file
        captioner: The image captioner
        transforms: List of transformation classes
        outputs: Path of the output folder to store the images
    '''

    #Create the instances of the dataset, download
    data=Dataset(annotation_file,transforms)
    download=Download()

    #Print image names and their captions from annotation file using dataset object
    for i in range(len(data)):
        entry = data.__getann__(i)
        print(entry.get("file_name"))
        captions = entry.get("captions")
        for caption in captions:
            print(caption.get("caption"))

    #Download images to ./data/imgs/ folder using download object
    for i in range(len(data)):
        entry = data.__getann__(i)
        path="./data/imgs"+"/"+entry.get("file_name")
        if not os.path.exists(path):
            download(path,entry.get("url"))

    #Transform the required image (roll number mod 10) and save it seperately
    #My roll no. is 21CS10037, so I need to transform 7.jpg
    path="./data/imgs/7.jpg"
    l=len(transforms)
    for i in range(l):
        transformedImg=data.__transformitem__(path)
        dest=outputs+"/trans_"+str(i+1)+".jpg"
        if not os.path.exists(dest):
            transformedImg.save(dest)


    #Get the predictions from the captioner for the above saved transformed image  
    for i in range(l):
        print("CAPTIONS FOR TRANSFORMED IMAGE "+str(i+1)+" :")
        path=outputs+"/trans_"+str(i+1)+".jpg"
        caps=captioner(path,3)
        for cap in caps:
            print(cap)

def main():
    captioner = ImageCaptioningModel()
    if not os.path.exists("./data/imgs/outputs"):
        os.mkdir("./data/imgs/outputs")
    experiment('./data/annotations.jsonl', captioner, [], "./data/imgs/outputs")        #called once to download all the images, so I can access dimensions of 7.jpg which are needed for rescaling in the analysis task
    target_image=Image.open("data/imgs/7.jpg")
    w,h=target_image.size
    experiment('./data/annotations.jsonl', captioner, [None,FlipImage(),BlurImage(1),RescaleImage((2*w,2*h)),RescaleImage((int(w/2),int(h/2))),RotateImage(270),RotateImage(45)], "./data/imgs/outputs")  


if __name__ == '__main__':
    main()