#Imports
from PIL import Image

class FlipImage(object):
    '''
        Flips the image.
    '''

    def __init__(self, flip_type='horizontal'):
        '''
            Arguments:
            flip_type: 'horizontal' or 'vertical' Default: 'horizontal'
        '''
        self._flip_type=flip_type

    def __call__(self, image):
        '''
            Arguments:
            image (numpy array or PIL image)

            Returns:
            image (numpy array or PIL image)
        '''
        if self._flip_type=='vertical':
            flippedImage=image.transpose(Image.FLIP_TOP_BOTTOM)
        else:
            flippedImage=image.transpose(Image.FLIP_LEFT_RIGHT)
        return flippedImage

