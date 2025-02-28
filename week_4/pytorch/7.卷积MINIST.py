from torch import optim,nn
import torch
from torch.utils.data import DataLoader
from torchvision import transforms,datasets

# MINIST数据集下载
minist_traindataset = datasets.MNIST(root="C:/Users/HP/Desktop/mygithub/study/week_4/pytorch/mydatas/MNIST",
                                     train=True,
                                     download=False,
                                     transform=transforms.ToTensor())
minist_testdataset = datasets.MNIST(root="C:/Users/HP/Desktop/mygithub/study/week_4/pytorch/mydatas/MNIST",
                                    train=False,
                                    download=False,
                                    transform=transforms.ToTensor())


# 加载数据集
Traindataloader = DataLoader(dataset=minist_traindataset,batch_size=64,shuffle=True)
Testdataloader = DataLoader(dataset=minist_testdataset,batch_size=64,shuffle=True)
