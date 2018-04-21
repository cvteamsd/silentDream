#!/usr/bin/python
# --*-- coding:utf-8 --*--
# Author: GK
# Create on 18-3-14  上午11:58
# Project DL_FrameWork

from DA1 import *
import cv2
import os
from imgaug import augmenters as iaa
from imgaug import parameters as iap
import time


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


# train_txt = open(DataAugParam['train_txt'], "a+")

if __name__ == "__main__":
    # ss = "*123*"
    # print ss[1:].find("*")
    # key = ss[1: ss[1:].find("*") + 1]
    # ikey = int(key)
    # print type(ikey), ikey
    # print len(np.arange(0.2, 1.01, 0.2))
    # print len(np.arange(0.0, 0.21, 0.05))
    # src1 = cv2.imread("/home/gk/dataSet/2.jpg")
    # aug_src1 = iaa.MultiplyElementwise(mul=0.2).augment_image(src1)
    # aug_src2 = iaa.MultiplyElementwise(mul=0.4).augment_image(src1)
    # aug_src3 = iaa.MultiplyElementwise(mul=0.6).augment_image(src1)
    # cv2.imshow("src1", src1)
    # cv2.imshow("aug", aug_src1)
    # cv2.imshow("aug2", aug_src2)
    # cv2.imshow("aug3", aug_src3)
    # cv2.waitKey(0)
    total_img_dir_list = np.arange(1, 15, 1)
    basepath = "/home/gk/dataSet/ld_std/"
    train_txt = open(basepath + "train.txt", "a+")
    val_txt = open(basepath + "test.txt", "a+")
    SEP = " "
    index = 0
    for i in total_img_dir_list:
        temp_dir = basepath + str(i)
        temp_filename_list = os.listdir(temp_dir)
        for i_filename in np.arange(len(temp_filename_list)):
            filename = temp_filename_list[i_filename]
            key = filename[1: filename[1:].find("*") + 1]
            # print "filename ", filename, " key ", key

            temp_str = str(i) + os.path.sep + temp_filename_list[i_filename]
            # print temp_str
            index += 1
            if index <= 8:
                train_txt.write(temp_str + SEP + key + "\n")
            elif index in [9,10]:
                if index == 10:
                    index = 0
                val_txt.write(temp_str + SEP + key + "\n")
            else:
                assert False, "invalid index, logic error ----> GK"

    train_txt.close()
    val_txt.close()
    print "Done"
    exit(1)
    # sss = r"WithChannels_AddC123_[20]_16-11-24-15-33-14_轿车_2567_519-247-670-398.jpg"
    # ee = sss.split("_")
    # print ee

    start = time.clock()
    for key in LABELS.keys():
        if key != "0" :
            continue
        if True:
            tmp_imgname_list = sorted(os.listdir(LABELS[key]))

            for i in np.arange(len(tmp_imgname_list)):
                if not tmp_imgname_list[i].endswith(".jpg"):
                    continue
                tmp_files = LABELS[key] + os.path.sep + tmp_imgname_list[i]
                src = cv2.imread(tmp_files)
                # dst = iaa.Fliplr(1).augment_image(src)
                dst = DA_WithChannels_Add(src)                # dirname 1
                # dst = DA_ColorspaceWithChannel(src)           # dirname 2
                # dst = DA_Superpixels(src)                     # dirname 3
                # dst = DA_AllBlur(src)                         # dirname 4
                # dst = DA_Sharpen(src)                         # dirname 5
                # dst = DA_Emboss(src)                          # dirname 6
                # dst = DA_AdditiveGaussianNoise(src)           # dirname 7
                # dst = DA_MultiplyElementwise(src)             # dirname 8
                # dst = DA_Dropout(src)                         # dirname 9
                # dst = DA_CoarseDropout(src)                   # dirname 10
                # dst = DA_CoarseSaltAndPepper(src)             # dirname 11
                # dst = DA_ElasticTransformation(src)           # dirname 12
                # dst = DA_Affine(src)                          # dirname 13
                # dst = iaa.Fliplr(1).augment_image(src)          # dirname 14
                # dst_img_name = "*" + key + "*" + "fliplr" + "_" + tmp_imgname_list[i]
                # tmp_output = "/home/gk/dataSet/ld_std/0" + os.path.sep + dst_img_name
                # cv2.imwrite(tmp_output, dst)
                for i_dst in np.arange(len(dst)):
                    dst_img_name = "*" + key + "*" + dst[i_dst][0] + "_" + tmp_imgname_list[i]
                    tmp_output = "/home/gk/dataSet/ld_std/0" + os.path.sep + dst_img_name
                    # cv2.imwrite(tmp_output, dst[i_dst][2])
                    # train_txt.write(dst_img_path + " " + key + "\n")

    print "key 1 Done "
    print "time cost ", time.clock() - start
    # train_txt.close()
