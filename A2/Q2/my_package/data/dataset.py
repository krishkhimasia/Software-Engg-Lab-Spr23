#Imports
import jsonlines
from PIL import Image
import os
import numpy as np

class Dataset(object):
    '''
        A class for the dataset that will return data items as per the given index
    '''

    def __init__(self, annotation_file, transforms=None):
        '''
            Arguments:
            annotation_file: path to the annotation file
            transforms: list of transforms (class instances)
                        For instance, [<class 'RandomCrop'>, <class 'Rotate'>]
        '''
        self._annotation_file=annotation_file
        self._transforms=transforms
     

    def __len__(self):
        '''
            return the number of data points in the dataset
        '''
        cnt=0
        with jsonlines.open(self._annotation_file) as reader:
            for obj in reader:
                cnt+=1
        return cnt

    
    def __getann__(self, idx):
        '''
            return the data items for the index idx as an object
        '''
        cnt=0
        with jsonlines.open(self._annotation_file) as reader:
            return list(reader)[idx]
        

    def __transformitem__(self, path):
        '''
            return transformed PIL Image object for the image in the given path
        '''
        img=Image.open(path)
        for transform in self._transforms:
            im=transform(im)
        return im
