#Imports
from PIL import Image

class RescaleImage(object):
    '''
        Rescales the image to a given size.
    '''

    def __init__(self, output_size):
        '''
            Arguments:
            output_size (tuple or int): Desired output size. If tuple, output is
            matched to output_size. If int, smaller of image edges is matched
            to output_size keeping aspect ratio the same.
        '''
        self._size=output_size


    def __call__(self, image):
        '''
            Arguments:
            image (numpy array or PIL image)

            Returns:
            image (numpy array or PIL image)

            Note: You do not need to resize the bounding boxes. ONLY RESIZE THE IMAGE.
        '''
        w,h= image.size         #get original image size
        if type(self._size)==int:
            if(w<=h):
                img=image.resize((self._size,int((self._size/w)*h)))
            else:
                img=image.resize((int((self._size/h)*w),self._size))
        else:
            img=image.resize(self._size)
        return img