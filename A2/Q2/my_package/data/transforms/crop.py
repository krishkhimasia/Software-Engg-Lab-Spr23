#Imports
from PIL import Image
import random

class CropImage(object):
    '''
        Performs either random cropping or center cropping.
    '''

    def __init__(self, shape, crop_type='center'):
        '''
            Arguments:
            shape: output shape of the crop (h, w)
            crop_type: center crop or random crop. Default: center
        '''
        self._shape=shape
        self._crop_type=crop_type

    def __call__(self, image):
        '''
            Arguments:
            image (numpy array or PIL image)

            Returns:
            image (numpy array or PIL image)
        '''
        w,h=image.size
        if(self._shape==(h,w)):     #handles the case where no cropping takes place
            return image
        else:
            if self._crop_type=='random':       #random cropping, randrange() generates random position for cropping
                if(2*self._shape[1]<=w):
                    l=random.randrange(self._shape[1],w-self._shape[1])
                else:
                    l=random.randrange(0,w-self._shape[1])
                if(2*self._shape[0]<=h):
                    t=random.randrange(self._shape[0],h-self._shape[0])
                else:
                    t=random.randrange(0,h-self._shape[0])
            else:                               #center cropping, position chose appropriately to crop at center
                l=int(w/2-self._shape[1]/2)
                t=int(h/2-self._shape[0]/2)
        croppedImage=image.crop((l,t,l+self._shape[1],t+self._shape[0]))       #using PIL to crop the image
        return croppedImage

 