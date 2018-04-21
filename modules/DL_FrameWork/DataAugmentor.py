#!/usr/bin/python
# --*-- coding:utf-8 --*--
# Author: GK
# Create on 18-3-14  上午10:46
# Project DL_FrameWork

import xml.etree.ElementTree as ET
import numpy as np
import os
import cv2
import imgaug as Ia
from imgaug import augmenters as iaa
from imgaug import parameters as iap
import json
import time


# AUG_OPS = ["AUG_OPS_NAME", "AUG_OPS_PARAM", "AUG_OPS"]
class DataAugmentor(object):

    def __init__(self, inputimg, ops_name=None, ops_param=None):
        assert inputimg.ndim in [2, 3], "input invalid! Please check input"
        self.AUG_OPS_NAME = ops_name
        self.AUG_OPS_PARAM = ops_param
        self.src = inputimg
        self.ret = []

    def set_ops_param(self, ops_param):
        assert ops_param != None, "invalid param"
        self.AUG_OPS_PARAM = ops_param
        print "update params to ", ops_param
        return True


    def get_aug_output_size(self):
        self.output_size = len(self.ret)
        return self.output_size

    def get_aug_name(self):
        return self.AUG_OPS_NAME

    def augment_image(self):
        iaa.Noop()
        print "base class augment_image, do nothing!"

class DA_WithChannels_Add(DataAugmentor):
    pass

class DA_Superpixels(DataAugmentor):
    pass

class DA_ColorspaceWithChannel(DataAugmentor):
    pass

class DA_AllBlur(DataAugmentor):
    pass

class DA_Sharpen(DataAugmentor):
    pass

class DA_Emboss(DataAugmentor):
    pass

class DA_Add(DataAugmentor):
    pass

class DA_AddElementwise(DataAugmentor):
    pass

class DA_AdditiveGaussianNoise(DataAugmentor):
    pass

class DA_MultiplyElementwise(DataAugmentor):
    pass

class DA_Dropout(DataAugmentor):
    pass

class DA_CoarseDropout(DataAugmentor):
    pass

class DA_CoarseSaltAndPepper(DataAugmentor):
    pass

class DA_ContrastNormalization(DataAugmentor):
    pass

class DA_PiecewiseAffine(DataAugmentor):
    pass

class DA_Crop(DataAugmentor):
    pass

class DA_Flip(DataAugmentor):
    pass

class DA_Affine(DataAugmentor):
    pass

class DA_ElasticTransformation(DataAugmentor):
    pass





DataAugParam = {
        "train_image_folder":   "/home/gk/dataSet/ld_std/train",
        "val_image_folder":     "/home/gk/dataSet/ld_std/val",
        "train_txt":            "/home/gk/dataSet/ld_std/train.txt",
        "val_txt":              "/home/gk/dataSet/ld_std/val.txt"
    }

LABELS = {
              "0":  "/home/gk/dataSet/ld_src/0",                # backgroud
              "1":  "/home/gk/dataSet/ld_src/1/up",              # lock1 up
              "2":  "/home/gk/dataSet/ld_src/2/up",              # lock2 up
              "3":  "/home/gk/dataSet/ld_src/3/up",              # lock3 up
              "4":  "/home/gk/dataSet/ld_src/4/up",              # lock4 up
              "5":  "/home/gk/dataSet/ld_src/5/up",              # lock5 up
              "6":  "/home/gk/dataSet/ld_src/6/up/",             # lock6 up
              "7":  "/home/gk/dataSet/ld_src/7",                 # 折叠障碍物
              "8":  "/home/gk/dataSet/ld_src/8",                 # 不可折叠障碍物
              "9":  "/home/gk/dataSet/ld_src/9",                 # 雪糕筒
              "10": "/home/gk/dataSet/ld_src/10_delay/up",      # lock10_d up
              "11": "/home/gk/dataSet/ld_src/11_delay/up",      # lock11_d up
              "12": "/home/gk/dataSet/ld_src/12_delay/up",      # lock12_d up
              "13":  "/home/gk/dataSet/ld_src/1/down",          # lock1 down
              "14":  "/home/gk/dataSet/ld_src/2/down",          # lock2 down
              "15":  "/home/gk/dataSet/ld_src/3/down",          # lock3 down
              "16":  "/home/gk/dataSet/ld_src/4/down",          # lock4 down
              "17":  "/home/gk/dataSet/ld_src/5/down",          # lock5 down
              "18":  "/home/gk/dataSet/ld_src/6/down",          # lock6 down
              "19":  "/home/gk/dataSet/ld_src/10_delay/down",   # lock10_d down
              "20":  "/home/gk/dataSet/ld_src/11_delay/down",   # lock11_d down
              "21":  "/home/gk/dataSet/ld_src/12_delay/down"    # lock12_d down
    }





train_txt = open(DataAugParam['train_txt'], "a+")

start = time.clock()
for key in LABELS.keys():
    tmp_imgname_list = sorted(os.listdir(LABELS[key]))

    for i in np.arange(len(tmp_imgname_list)):
        if not tmp_imgname_list[i].endswith(".jpg"):
            continue
        tmp_files = LABELS[key] + os.path.sep + tmp_imgname_list[i]
        src = cv2.imread(tmp_files)
        # dst = iaa.Fliplr(1).augment_image(src)
        dst = iaa.GaussianBlur(sigma=(1.0))
        # cv2.imshow("dst", dst)
        # cv2.waitKey(0)
        dst_img_path = DataAugParam['train_image_folder'] + os.path.sep +  "_" + tmp_imgname_list[i]
        dst_img_name = os.path.sep + "_" + tmp_imgname_list[i]
        tmp_output = "/home/gk/sample0/output" + os.path.sep + "_" + tmp_imgname_list[i]
        cv2.imwrite(dst_img_path, dst)
        train_txt.write(dst_img_path + " " + key + "\n")

print "Done "
print "time cost ", time.clock() - start
train_txt.close()