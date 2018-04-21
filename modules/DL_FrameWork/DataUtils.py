#!/usr/bin/python
# --*-- coding:utf-8 --*--
# Author: GK
# Create on 18-3-14  上午10:45
# Project DL_FrameWork

import xml.etree.ElementTree as ET
import numpy as np
import os
import cv2

DATASET_BASE_PATH       = "/home/gk/dataSet/"
DATASET_SRC_ATH        = DATASET_BASE_PATH + "src"
DATASET_ANNOTATION_PATH = DATASET_BASE_PATH + "annotation"
DATASET_OUTPUT_PATH     = DATASET_BASE_PATH + "output"
DATASET_CONFIG_PATH     = DATASET_BASE_PATH + "config"



def parse_annotation(ann_dir, img_dir, labels=[]):
    all_imgs = []
    seen_labels = {}

    for ann in sorted(os.listdir(ann_dir)):
        img = {'object': []}

        tree = ET.parse(ann_dir + ann)

        for elem in tree.iter():
            if 'filename' in elem.tag:
                img['filename'] = img_dir + elem.text
            if 'width' in elem.tag:
                img['width'] = int(elem.text)
            if 'height' in elem.tag:
                img['height'] = int(elem.text)
            if 'object' in elem.tag or 'part' in elem.tag:
                obj = {}

                for attr in list(elem):
                    if 'name' in attr.tag:
                        obj['name'] = attr.text

                        if obj['name'] in seen_labels:
                            seen_labels[obj['name']] += 1
                        else:
                            seen_labels[obj['name']] = 1

                        if len(labels) > 0 and obj['name'] not in labels:
                            break
                        else:
                            img['object'] += [obj]

                    if 'bndbox' in attr.tag:
                        for dim in list(attr):
                            if 'xmin' in dim.tag:
                                obj['xmin'] = int(round(float(dim.text)))
                            if 'ymin' in dim.tag:
                                obj['ymin'] = int(round(float(dim.text)))
                            if 'xmax' in dim.tag:
                                obj['xmax'] = int(round(float(dim.text)))
                            if 'ymax' in dim.tag:
                                obj['ymax'] = int(round(float(dim.text)))

        if len(img['object']) > 0:
            all_imgs += [img]

    return all_imgs, seen_labels


def process_state_record(path, process_num):
    '''
    this is just for record annotation dir process state in a file
    :param path: annotation base dir path
    :param process_num process dir num
    :return: a list which contains dirname which never processed
    '''
    total_list = sorted(os.listdir(path))
    ret_list = []
    index = 0

    recordpath = DATASET_CONFIG_PATH + "/" + "annotation_record.txt";
    if os.path.exists(recordpath):
        record_file = open(recordpath, 'r')
        record_list = record_file.readlines()
        record_file.close()
        record_file = open(recordpath, 'a+')
        rest = len(total_list) - len(record_list)
        indexbase = len(record_list)
        print "rest is ", rest
        if rest <= process_num and rest > 0:
            process_num = rest
        elif rest <= 0:
            print "all dir has processed"
            return []

        for i in np.arange(process_num):
            ret_list.append(total_list[indexbase + i - 1])
            record_file.write(str(total_list[indexbase + i - 1]) + "\n")
        record_file.close()
        return ret_list
    else:
        record_file = open(recordpath, 'a+')
        if process_num >= len(total_list):
            process_num = len(total_list)
        for i in np.arange(process_num):
            record_file.write(str(total_list[i]) + "\n")
            ret_list.append(total_list[i])
        record_file.close()
        return ret_list

def parse_labelimg_win_path(labelimg_path):
    retlist = []
    dirname = labelimg_path[17:35]
    filename = labelimg_path[36:]
    return (dirname, filename)

def parse_labelimg_annotation(anno_path, src_path, output_path, labels =[]):
    '''
    parse annotation image to get cliped samples and save into output_path
    based on src dirname
    :param anno_path: annotation dirname ,contains labeled xml
    :param src_path: source img dirname
    :param output_path: ouput dirname, save all images based on dirname
    :return:
    '''
    all_imgs = []
    seen_labels = {}

    for ann in sorted(os.listdir(anno_path)):
        img = {'object': []}

        tree = ET.parse(anno_path + ann)

        for elem in tree.iter():
            if 'folder' in elem.tag:
                img['folder'] = elem.text
            if 'filename' in elem.tag:
                img['filename'] = src_path + elem.text
            if 'width' in elem.tag:
                img['width'] = int(elem.text)
            if 'height' in elem.tag:
                img['height'] = int(elem.text)
            if 'object' in elem.tag or 'part' in elem.tag:
                obj = {}

                for attr in list(elem):
                    if 'name' in attr.tag:
                        obj['name'] = attr.text

                        if obj['name'] in seen_labels:
                            seen_labels[obj['name']] += 1
                        else:
                            seen_labels[obj['name']] = 1

                        if len(labels) > 0 and obj['name'] not in labels:
                            break
                        else:
                            img['object'] += [obj]

                    if 'bndbox' in attr.tag:
                        for dim in list(attr):
                            if 'xmin' in dim.tag:
                                obj['xmin'] = int(round(float(dim.text)))
                            if 'ymin' in dim.tag:
                                obj['ymin'] = int(round(float(dim.text)))
                            if 'xmax' in dim.tag:
                                obj['xmax'] = int(round(float(dim.text)))
                            if 'ymax' in dim.tag:
                                obj['ymax'] = int(round(float(dim.text)))

        if len(img['object']) > 0:
            all_imgs += [img]

    return all_imgs, seen_labels



if __name__ =="__main__":
    # ret = process_state_record(DATASET_ANNOTATION_PATH, 2)
    # ss = str(r'F:\DataSet\11\V1\20161027_LD_video8\698.jpg')
    s1 = "123.xml"
    rr = s1.split('.')
    print rr
    labels = ['first', 'second', 'third', 'fourth']