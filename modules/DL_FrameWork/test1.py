#!/usr/bin/python
# --*-- coding:utf-8 --*--
# Author: GK
# Create on 18-3-14  上午11:04
# Project DL_FrameWork

import cv2
import numpy as np
import imgaug as Ia
from imgaug import augmenters as iaa
from imgaug import parameters as iap
import os
import json


'''
AUG_OPS = ["AUG_OPS_NAME", "AUG_OPS_PARAM", "AUG_OPS"]
'''


def DA_WithChannels_Add(inputimg, AUG_OPS_PARAM = [-50, -25, 25, 50]):
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    AUG_OPS_NAME = ["WithChannels_AddC123" , "WithChannels_AddC12", "WithChannels_AddC23",
                    "WithChannels_AddC13", "WithChannels_AddC1", "WithChannels_AddC2",
                    "WithChannels_AddC3"]
    ret = []
    for i_param in np.arange(len(AUG_OPS_PARAM)):
        VALUE = AUG_OPS_PARAM[i_param]
        for i_name in np.arange(len(AUG_OPS_NAME)):
            Name = AUG_OPS_NAME[i_name]
            if Name == "WithChannels_AddC123":
                augimg = iaa.WithChannels([0,1,2], iaa.Add(value=VALUE)).augment_image(inputimg)
                ret.append((Name, VALUE, augimg))
            elif Name == "WithChannels_AddC12":
                augimg = iaa.WithChannels([0, 1], iaa.Add(value=VALUE)).augment_image(inputimg)
                ret.append((Name, VALUE, augimg))
            elif Name == "WithChannels_AddC23":
                augimg = iaa.WithChannels([1, 2], iaa.Add(value=VALUE)).augment_image(inputimg)
                ret.append((Name, VALUE, augimg))
            elif Name == "WithChannels_AddC13":
                augimg = iaa.WithChannels([0, 1], iaa.Add(value=VALUE)).augment_image(inputimg)
                ret.append((Name, VALUE, augimg))
            elif Name == "WithChannels_AddC1":
                augimg = iaa.WithChannels(0, iaa.Add(value=VALUE)).augment_image(inputimg)
                ret.append((Name, VALUE, augimg))
            elif Name == "WithChannels_AddC2":
                augimg = iaa.WithChannels(1, iaa.Add(value=VALUE)).augment_image(inputimg)
                ret.append((Name, VALUE, augimg))
            elif Name == "WithChannels_AddC3":
                augimg = iaa.WithChannels(2, iaa.Add(value=VALUE)).augment_image(inputimg)
                ret.append((Name, VALUE, augimg))
            else:
                print "invalid ops in DA_WithChannels_Add"
    print "DA_WithChannels_Add aug size is ",len(ret)
    assert len(ret) == 28, "DA_WithChannels_Add Fails"
    return ret

def DA_Superpixels(inputimg):
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    AUG_OPS_NAME = ["Superpixels_25_64", "Superpixels_50_64", "Superpixels_25_128", "Superpixels_50_128"]
    Superpixels_param = [(0.25, 64), (0.5, 64), (0.25, 128), (0.5, 128)]
    ret = []
    for i in np.arange(len(Superpixels_param)):
        VALUE = Superpixels_param[i]
        Name = AUG_OPS_NAME[i]
        if Name == "Superpixels_25_64":
            aug_img = iaa.Superpixels(p_replace=VALUE[0], n_segments=VALUE[1]).augment_image(inputimg)
            ret.append((Name, str(VALUE[0]) + "_" + str(VALUE[1]), aug_img))
        elif Name == "Superpixels_50_64":
            aug_img = iaa.Superpixels(p_replace=VALUE[0], n_segments=VALUE[1]).augment_image(inputimg)
            ret.append((Name, str(VALUE[0]) + "_" + str(VALUE[1]), aug_img))
        elif Name == "Superpixels_25_128":
            aug_img = iaa.Superpixels(p_replace=VALUE[0], n_segments=VALUE[1]).augment_image(inputimg)
            ret.append((Name, str(VALUE[0]) + "_" + str(VALUE[1]), aug_img))
        elif Name == "Superpixels_50_128":
            aug_img = iaa.Superpixels(p_replace=VALUE[0], n_segments=VALUE[1]).augment_image(inputimg)
            ret.append((Name, str(VALUE[0]) + "_" + str(VALUE[1]), aug_img))
        else:
            print "invalid ops in DA_Superpixels"
    print "DA_Superpixels aug size is ", len(ret)
    assert len(ret) == 4, "DA_Superpixels Fails"
    return ret

def DA_ColorspaceWithChannel(inputimg, AUG_OPS_PARAM=[-50, -25, 25, 50]):
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    AUG_OPS_NAME = ["ColorspaceWithChannels_AddC23", "ColorspaceWithChannels_AddC2",
                    "ColorspaceWithChannels_AddC3"]
    ret = []

    for i_param in np.arange(len(AUG_OPS_PARAM)):
        VALUE = AUG_OPS_PARAM[i_param]
        for i_name in np.arange(len(AUG_OPS_NAME)):
            Name = AUG_OPS_NAME[i_name]
            if Name == "ColorspaceWithChannels_AddC23":
                aug = iaa.Sequential([
                                iaa.ChangeColorspace(from_colorspace="RGB", to_colorspace="HSV"),
                                iaa.WithChannels([1,2], iaa.Add(VALUE)),
                                iaa.ChangeColorspace(from_colorspace="HSV", to_colorspace="RGB")
                            ])
                augimg = aug.augment_image(inputimg)
                ret.append((Name, VALUE, augimg))
            elif Name == "ColorspaceWithChannels_AddC2":
                aug = iaa.Sequential([
                    iaa.ChangeColorspace(from_colorspace="RGB", to_colorspace="HSV"),
                    iaa.WithChannels(1, iaa.Add(VALUE)),
                    iaa.ChangeColorspace(from_colorspace="HSV", to_colorspace="RGB")
                ])
                augimg = aug.augment_image(inputimg)
                ret.append((Name, VALUE, augimg))
            elif Name == "ColorspaceWithChannels_AddC3":
                aug = iaa.Sequential([
                    iaa.ChangeColorspace(from_colorspace="RGB", to_colorspace="HSV"),
                    iaa.WithChannels(2, iaa.Add(VALUE)),
                    iaa.ChangeColorspace(from_colorspace="HSV", to_colorspace="RGB")
                ])
                augimg = aug.augment_image(inputimg)
                ret.append((Name, VALUE, augimg))
            else:
                print "invalid ops in DA_WithChannels_Add"
    assert len(ret) == 12, "DA_ColorspaceWithChannel Fails"
    return ret

def DA_AllBlur(inputimg):
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    # "MedianBlur5", "GaussianBlur5",
    AUG_OPS_NAME = ["GaussianBlur1", "GaussianBlur3",
                    "MedianBlur1", "MedianBlur3",
                    "AverageBlur1311", "AverageBlur3111",
                    "BilateralBlur"]
    ret = []
    for i in np.arange(len(AUG_OPS_NAME)):
        Name = AUG_OPS_NAME[i]
        if Name == "GaussianBlur1":
            VALUE = 1
            aug_img = iaa.GaussianBlur(sigma=(0.0, 1.0)).augment_image(inputimg)
            ret.append((Name, str(VALUE), aug_img))
        elif Name == "GaussianBlur3":
            VALUE = 3
            aug_img = iaa.GaussianBlur(sigma=(0.0, 3.0)).augment_image(inputimg)
            ret.append((Name, str(VALUE), aug_img))
        # elif Name == "GaussianBlur5":
        #     VALUE = 5
        #     aug_img = iaa.GaussianBlur(sigma=(0.0, 5.0)).augment_image(inputimg)
        #     ret.append((Name, str(VALUE), aug_img))
        elif Name == "MedianBlur1":
            VALUE = 1
            aug_img = iaa.MedianBlur(k=1).augment_image(inputimg)
            ret.append((Name, str(VALUE), aug_img))
        elif Name == "MedianBlur3":
            VALUE = 3
            aug_img = iaa.MedianBlur(k=3).augment_image(inputimg)
            ret.append((Name, str(VALUE), aug_img))
        elif Name == "BilateralBlur":
            VALUE = 3
            aug_img = iaa.BilateralBlur(d=(3, 10), sigma_color=(10, 250), sigma_space=(10, 250)).augment_image(inputimg)
            ret.append((Name, str(VALUE), aug_img))
        elif Name == "AverageBlur1311":
            VALUE = 1311
            aug_img = iaa.AverageBlur(k=((1, 3), (3, 11))).augment_image(inputimg)
            ret.append((Name, str(VALUE), aug_img))
        elif Name == "AverageBlur3111":
            VALUE = 3111
            aug_img = iaa.AverageBlur(k=((3, 11), (1, 3))).augment_image(inputimg)
            ret.append((Name, str(VALUE), aug_img))
        else:
            print "invalid ops in DA_WithChannels_Add"
    assert len(ret) == 7, "DA_AllBlur Fails"
    return ret

def DA_Sharpen(inputimg):
    alpha = np.array([0,1,2,3,4,5,6,7,8]).__div__(8.0)
    lightness = np.array([0,1,2,3,4,5,6,7,8]).__div__(8.0).__add__(0.3)
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    ret = []
    for i in np.arange(len(alpha)):
        for j in np.arange(len(lightness)):
            Name = "SharpenAL_" + str(alpha[i]) + "_" + str(lightness[j])
            VALUE = str(alpha[i]) + "_" + str(lightness[j])
            aug_img = iaa.Sharpen(alpha=alpha[i], lightness=lightness[j])
            ret.append((Name, VALUE, aug_img))
    assert len(ret) == 81, "DA_Sharpen output size not match!"
    return ret

def DA_Emboss(inputimg):
    alpha = np.arange(0.0, 1.0, 0.125)
    strength = np.arange(0.3, 1.3, 0.125)
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    ret = []
    for i in np.arange(len(alpha)):
        for j in np.arange(len(strength)):
            Name = "SharpenAL_" + str(alpha[i]) + "_" + str(strength[j])
            VALUE = str(alpha[i]) + "_" + str(strength[j])
            aug_img = iaa.Emboss(alpha=alpha[i], strength=strength[j]).augment_image(inputimg)
            ret.append((Name, VALUE, aug_img))
    assert len(ret) == 81, "DA_Sharpen output size not match!"
    return ret

def DA_Add(inputimg):
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    values = np.arange(-50,51,10)
    p_channels = np.arange(0.0,1.01,0.2)
    ret = []
    for i in np.arange(len(values)):
        for j in np.arange(len(p_channels)):
            Name = "Add_" + str(values[i]) + "_p_channels_" + str(p_channels[j])
            VALUE = str(values[i]) + "_" + str(p_channels[j])
            aug_img = iaa.Add(values[i], p_channels[j]).augment_image(inputimg)
            ret.append((Name, VALUE, aug_img))
    assert len(ret) == 55, "DA_Add output size not match!"
    return ret

def DA_AddElementwise(inputimg):
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    values = np.arange(-50,51,10)
    p_channels = np.arange(0.01,1.01,0.2)
    ret = []
    for i in np.arange(len(p_channels)):
        for j in np.arange(len(values)):
            Name = "AddElementwise_" + str(j) + "_p_channels_" + str(p_channels[i])
            VALUE = str(values[i]) + "_" + str(p_channels[j])
            aug_img = iaa.AddElementwise(value=(-50, 50), per_channel=p_channels[i]).augment_image(inputimg)
            ret.append((Name, VALUE, aug_img))
    assert len(ret) == 66, "DA_AddElementwise output size not match!"
    return ret

def DA_AdditiveGaussianNoise(inputimg):
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    values = np.arange(10,51,10)
    p_channels = np.arange(0.01,1.01,0.2)
    ret = []
    for i in np.arange(len(values)):
        for j in np.arange(len(p_channels)):
            Name = "DA_AdditiveGaussianNoise_" + str(values[i]) + "_p_channels_" + str(p_channels[j])
            VALUE = str(values[i]) + "_" + str(p_channels[j])
            aug_img = iaa.AdditiveGaussianNoise(scale=(0.0, values[i]), per_channel=p_channels[i]).augment_image(inputimg)
            ret.append((Name, VALUE, aug_img))
    assert len(ret) == 25, "DA_AdditiveGaussianNoise output size not match!"
    return ret

def DA_MultiplyElementwise(inputimg):
    '''
    change brightness in a stotic value or a fixed value randomly
    :param inputimg: src img need to be augmented
    :return:(Name, VALUE, aug_img) List augmented img tuples.
    '''
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    mul_values = np.arange(0.2, 2.0, 0.2)
    p_channels = np.arange(0.2, 1.01, 0.2)
    ret = []
    for i in np.arange(len(mul_values)):
        for j in np.arange(len(p_channels)):
            Name = "DA_MultiplyElementwise_" + str(mul_values[i]) + "_p_channels_" + str(p_channels[j])
            VALUE = str(mul_values[i]) + "_" + str(p_channels[j])
            aug_img = iaa.MultiplyElementwise(mul=mul_values[i], per_channel=p_channels[j]).augment_image(inputimg)
            ret.append((Name, VALUE, aug_img))
    assert len(ret) == 45, "DA_MultiplyElementwise output size not match!"
    return ret

def DA_Dropout(inputimg):
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    values = np.arange(0.0,0.21,0.02)
    p_channels = np.arange(0.0,1.01,0.1)
    # p_channels = np.append(p_channels,1.0)
    ret = []
    for i in np.arange(len(values)):
        for j in np.arange(len(p_channels)):
            Name = "DA_Dropout_" + str(values[i]) + "_" + str(p_channels[j])
            VALUE = str(values[i]) + "_" + str(p_channels[j])
            aug_img = iaa.Dropout(p=values[i], per_channel=p_channels[j]).augment_image(inputimg)
            ret.append((Name, VALUE, aug_img))
    assert len(ret) == 121, "DA_Dropout output size not match!"
    return ret

def DA_CoarseDropout(inputimg):
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    values = np.arange(0.0, 0.21, 0.02)
    p_channels = np.arange(0.0, 1.01, 0.1)
    ret = []
    for i in np.arange(len(values)):
        for j in np.arange(len(p_channels)):
            Name = "DA_Dropout_" + str(values[i]) + "_" + str(p_channels[j])
            VALUE = str(values[i]) + "_" + str(p_channels[j])
            aug_img = iaa.CoarseDropout(p=values[i],size_percent=(0.5, 1.0), per_channel=p_channels[j]).augment_image(inputimg)
            ret.append((Name, VALUE, aug_img))
    assert len(ret) == 121, "DA_CoarseDropout output size not match!"
    return ret


def DA_CoarseSaltAndPepper(inputimg):
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    values = np.arange(0.0, 0.21, 0.02)
    p_channels = np.arange(0.0, 1.01, 0.1)
    ret = []
    for i in np.arange(len(values)):
        for j in np.arange(len(p_channels)):
            Name = "DA_CoarseSalt" + str(values[i]) + "_" + str(p_channels[j])
            VALUE = str(values[i]) + "_" + str(p_channels[j])
            aug_img = iaa.CoarseSalt(p=values[i],size_percent=(0.5, 1.0), per_channel=p_channels[j]).augment_image(inputimg)
            ret.append((Name, VALUE, aug_img))
            Name = "DA_CoarseSaltAndPepper" + str(values[i]) + "_" + str(p_channels[j])
            VALUE = str(values[i]) + "_" + str(p_channels[j])
            aug_img1 = iaa.CoarseSaltAndPepper(p=values[i], size_percent=(0.5, 1.0), per_channel=p_channels[j]).augment_image(inputimg)
            ret.append((Name, VALUE, aug_img1))
    assert len(ret) == 242, "DA_CoarseDropout output size not match!"
    return ret

def DA_ContrastNormalization(inputimg):
    '''
    it looks like the same with DA_MultiplyElementwise
    :param inputimg:
    :return:
    '''
    pass

def DA_PiecewiseAffine(inputimg):
    '''
    this augmenter not need now,leave it later!
    :param inputimg:
    :return:
    '''
    pass

def DA_Crop(inputimg):
    '''
    this augmenter not need now,leave it later!
    :param inputimg:
    :return:
    '''
    pass

def DA_Flip(inputimg):
    '''
    this augmenter not need now,leave it later!
    :param inputimg:
    :return:
    '''
    pass

def DA_Affine(inputimg):
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    shear_values = np.arange(-20,20,2)
    rotate_values = np.arange(-20,20,2)
    trans_px = np.arange(-20, 20, 2)
    trans_py = np.arange(-20, 20, 2)
    ret = []

    for i in np.arange(len(shear_values)):
        shear_Name = "DA_Affine_shear_" + str(shear_values[i])
        shear_VALUE = str(shear_values[i])
        shear_img = iaa.Affine(shear=shear_values[i], mode=Ia.ALL, cval=(0,255)).augment_image(inputimg)
        ret.append((shear_Name, shear_VALUE, shear_img))
        rotate_img = iaa.Affine(rotate=rotate_values[i], mode=Ia.ALL, cval=(0,255)).augment_image(inputimg)
        rotate_Name = "DA_Affine_rotate_" + str(shear_values[i])
        rotate_VALUE = str(shear_values[i])
        ret.append((rotate_Name, rotate_VALUE, rotate_img))
        trans_px_img = iaa.Affine(translate_px={"x":trans_px[i], "y":0}, mode=Ia.ALL, cval=(0, 255)).augment_image(inputimg)
        trans_px_Name = "DA_Affine_trans_px_" + str(shear_values[i])
        trans_px_VALUE = str(shear_values[i])
        ret.append((trans_px_Name, trans_px_VALUE, trans_px_img))
        trans_py_img = iaa.Affine(translate_px={"x":0, "y":trans_py[i]}, mode=Ia.ALL, cval=(0, 255)).augment_image(inputimg)
        trans_py_VALUE = str(shear_values[i])
        trans_py_Name = "DA_Affine_trans_py_" + trans_py_VALUE
        ret.append((trans_py_Name, trans_py_VALUE, trans_py_img))

    assert len(ret) == 80, "DA_Affine output size not match"
    return ret


def DA_ElasticTransformation(inputimg):
    assert inputimg.ndim in [2, 3], "input invalid! Please check input"
    alpha_values = np.arange(0.2, 2.01, 0.2)
    sigma_values =0.5

    ret = []
    for i in np.arange(len(alpha_values)):
        Name = "DA_ElasticTransformation_0.5" + str(alpha_values[i])
        VALUE = str(alpha_values[i])
        Elastic_img = iaa.ElasticTransformation(alpha=alpha_values[i], sigma=sigma_values).augment_image(img)
        ret.append((Name, VALUE, Elastic_img))

    assert len(ret) == 10, "DA_ElasticTransformation output size not match"
    return ret


if __name__ == "__main__":
    print "test code"
    config_path = "/home/gk/PycharmProjects/DL_Data/config/config.json"

    with open(config_path) as config_buffer:
        augconfig = json.load(config_buffer)


    srcimg_dir = "/home/gk/sample0"
    srcimg_output_dir = srcimg_dir + os.path.sep + "output"

    file_list = sorted(os.listdir(srcimg_dir))

    for i in np.arange(len(file_list)):
        filepath = srcimg_dir + os.path.sep + file_list[i]

        print filepath
        if not file_list[i].endswith(".jpg"):
            continue

        img = cv2.imread(filepath)
        # r_img = cv2.resize(img, (256,256), interpolation=cv2.INTER_CUBIC)

        if False:
            print "test DA_WithChannels_Add"
            ret = DA_WithChannels_Add(img)
            for i_ret in np.arange(len(ret)):
                str_value = ret[i_ret][1]
                str_name = ret[i_ret][0]
                aug_img = ret[i_ret][2]
                aug_img_name = str(str_value) + "_" + str(str_name) + file_list[i]
                abs_out_file_path = srcimg_output_dir + os.path.sep + aug_img_name
                cv2.imwrite(abs_out_file_path, aug_img)
        elif False:
            print "test DA_Superpixels"
            ret = DA_Superpixels(img)
            for i_ret in np.arange(len(ret)):
                str_value = ret[i_ret][1]
                str_name = ret[i_ret][0]
                aug_img = ret[i_ret][2]
                aug_img_name = str(str_value) + "_" + str_name + file_list[i]
                abs_out_file_path = srcimg_output_dir +os.path.sep + aug_img_name
                cv2.imwrite(abs_out_file_path, aug_img)
        elif False:
            print "test Fliplr"
            ret = iaa.Fliplr(1).augment_image(img)
            str_name = "Fliplr"
            str_value = "1"
            aug_img = ret
            aug_img_name = str(str_value) + "_" + str_name + file_list[i]
            abs_out_file_path = srcimg_output_dir + os.path.sep + aug_img_name
            cv2.imwrite(abs_out_file_path, aug_img)
        elif False:
            print " test DA_ColorspaceWithChannel"
            ret = DA_ColorspaceWithChannel(img)
            for i_ret in np.arange(len(ret)):
                str_value = ret[i_ret][1]
                str_name = ret[i_ret][0]
                aug_img = ret[i_ret][2]
                aug_img_name = str(str_value) + "_" + str_name + file_list[i]
                abs_out_file_path = srcimg_output_dir +os.path.sep + aug_img_name
                cv2.imwrite(abs_out_file_path, aug_img)
        elif False:
            print " test Blur Method"
            ret = DA_AllBlur(img)
            for i_ret in np.arange(len(ret)):
                str_value = ret[i_ret][1]
                str_name = ret[i_ret][0]
                aug_img = ret[i_ret][2]
                aug_img_name = str(str_value) + "_" + str_name + file_list[i]
                abs_out_file_path = srcimg_output_dir + os.path.sep + aug_img_name
                cv2.imwrite(abs_out_file_path, aug_img)

        elif True:
            # aug_img = iaa.Sharpen(alpha=0.5, lightness=1.3).augment_image(img)
            a = np.array([0,1,2,3,4,5,6,7,8]).__div__(8.0)
            b = np.array([0,1,2,3,4,5,6,7,8]).__div__(8.0).__add__(0.3)
            # aug_img = iaa.Add((-50, 50)).augment_image(img)
            result = []
            # aug_img = iaa.AdditiveGaussianNoise(scale=(0.0, 50)).augment_image(img)
            # aug_img = iaa.MultiplyElementwise(0.5).augment_image(img)
            # aug_img = iaa.Dropout(p=0.3, per_channel=1).augment_image(img)
            # aug_img = iaa.CoarseDropout(0.2,size_percent=(0.5, 1.0),per_channel=0.5).augment_image(img)
            # aug_img = iaa.CoarseSaltAndPepper(0.2, size_percent=(0.5, 1.0),per_channel=0).augment_image(img)
            # aug_img = iaa.CoarseSalt(0.2, size_percent=(0.5, 1.0)).augment_image(img)
            # aug_img = iaa.CoarsePepper(0.2, size_percent=(0.5, 1.0)).augment_image(img)
            # aug_img = iaa.ContrastNormalization(2.0).augment_image(img)
            # shear_aug_img = iaa.Affine(shear=20,mode=Ia.ALL, cval=(0,255)).augment_image(img)
            # rotate_aug_img = iaa.Affine(rotate=-20,mode=Ia.ALL, cval=(0,255)).augment_image(img)
            # trans_X_aug_img = iaa.Affine(translate_px={"x":(-20,20), "y":0}, mode=Ia.ALL, cval=(0,255)).augment_image(img)
            # trans_Y_aug_img = iaa.Affine(translate_px={"x":0, "y":(-20,20)}, mode=Ia.ALL, cval=(0,255)).augment_image(img)
            # trans_YX = iaa.Affine(translate_px={"x":(-20,20), "y":(-20,20)}, mode=Ia.ALL, cval=(0,255)).augment_image(img)
            Elastic_img = iaa.ElasticTransformation(alpha=0.5, sigma=0.25).augment_image(img)
            Elastic_img1 = iaa.ElasticTransformation(alpha=1, sigma=0.25).augment_image(img)
            Elastic_img2 = iaa.ElasticTransformation(alpha=1.5, sigma=0.25).augment_image(img)

            cv2.imshow("src", img)
            cv2.imshow("Elastic_img", Elastic_img)
            cv2.imshow("1Elastic_img", Elastic_img1)
            cv2.imshow("2Elastic_img", Elastic_img2)
            # cv2.imshow("shear", shear_aug_img)
            # cv2.imshow("rotate", rotate_aug_img)
            # cv2.imshow("trans_X", trans_X_aug_img)
            # cv2.imshow("trans_Y", trans_Y_aug_img)
            # cv2.imshow("transXY", trans_YX)

            # print np.arange(-50,51,5)
            # print np.arange(0.0,1.01,0.2)
            # print len(np.arange(-20, 20, 2))
            values = np.arange(0.0, 0.21, 0.02)
            p_channels = np.arange(0.0, 1.01, 0.1)
            print len(np.arange(0.2, 2.01, 0.2))

            cv2.waitKey(0)


    print "Done"