from PIL import Image
import requests
from io import BytesIO

class Download(object):
    '''
        A class for helping in dowloading the required images from the given url to the specified path
    '''

    def __call__(self, path, url):
        '''
            Arguments:
            path: download path with the file name
            url: required image URL
        '''
        res = requests.get(url, stream= True)
        img = Image.open(BytesIO(res.content))
        path+="/down.png"
        img.save(path)