from fileinput import filename
from PIL import Image
import os.path
from matplotlib import pyplot as pp
import numpy as np
import tensorflow as tf
from keras.preprocessing.image import load_img
from keras.preprocessing.image import img_to_array


print("Program start")

labelList = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
images = []
labels = []
imageSize = [120, 90]


def imageToTensor ():
    for labelIter in range(len(labelList)):
        for iter in range(5):

            # construct file name and directory
            fileName = "img" + str(labelIter + 1).zfill(3) + "-" + str(iter + 1).zfill(3) + ".png"
            iPath = ("./archive/Img/" + fileName)
            # import image, rescale, and convert to greyscale
            inputArr = img_to_array(load_img(iPath).resize([imageSize[0], imageSize[1]]).convert('L'))
            # convert image to numpy array
            inputArr = np.array([inputArr])
            # 
            images.append(inputArr[0, :, :, 0])
            labels.append(labelList[labelIter])

    images = tf.constant(images)

