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
    transformedImg=data.__transformitem__(path)
    destination = outputs+"/transformed_7.jpg"
    if not os.path.exists(destination):
        transformedImg.save(destination)


    #Get the predictions from the captioner for the above saved transformed image  


def main():
    captioner = ImageCaptioningModel()
    target_image=Image.open("data/imgs/7.jpg")
    w,h=target_image.size
    experiment('./data/annotations.jsonl', captioner, [], "./data/imgs/outputs/T1") 
    experiment('./data/annotations.jsonl', captioner, [FlipImage()], "./data/imgs/outputs/T2") 
    experiment('./data/annotations.jsonl', captioner, [BlurImage(1)], "./data/imgs/outputs/T3") 
    experiment('./data/annotations.jsonl', captioner, [RescaleImage((2*w,2*h))], "./data/imgs/outputs/T4") 
    experiment('./data/annotations.jsonl', captioner, [RescaleImage((int(w/2),int(h/2)))], "./data/imgs/outputs/T5") 
    experiment('./data/annotations.jsonl', captioner, [RotateImage(270)], "./data/imgs/outputs/T6") 
    experiment('./data/annotations.jsonl', captioner, [RotateImage(45)], "./data/imgs/outputs/T7") 


if __name__ == '__main__':
    main()