# anaconda提供了一些数据，包含房价预测数据，糖尿病等等
# E:\anaconda3\Lib\site-packages\sklearn\datasets\data

from torch import nn
from torch import optim
import torch
import numpy as np
from torch.utils.data import DataLoader
from torch.utils.data import Dataset


# x样本数据的特征是用空格隔开的，excel无法对空格进行分割获取数据，所以需要使用np来分割
datas = np.loadtxt("mydatas/breast_cancer.csv",delimiter=",",dtype=np.float32)

# 训练集与测试集占比
rate = int(np.ceil(0.8*datas.shape[0]))

# 输入特征数量
features = datas.shape[1]-1

# 学习率和训练次数
lr = 0.05
epoachs = 20


class Traindataset(Dataset):
    def __init__(self):
        self.datas = datas
        self.x = datas[:rate,:-1]
        self.y = datas[:rate,[-1]]

    def __getitem__(self, item):
        return self.x[item],self.y[item]

    def __len__(self):
        return self.x.shape[0]


class Testdataset(Dataset):
    def __init__(self):
        self.datas = datas
        self.x = datas[rate:,:-1]
        self.y = datas[rate:,[-1]]

    def __getitem__(self, item):
        return self.x[item],self.y[item]

    def __len__(self):
        return self.x.shape[0]

# 加载训练集和测试集
traindataset = Traindataset()
testdataset = Testdataset()
Traindataloader = DataLoader(dataset=traindataset,batch_size=32,shuffle=True)
Testdataloader = DataLoader(dataset=traindataset,batch_size=32,shuffle=True)


# 模型搭建
class mymodule(nn.Module):
    def __init__(self):
        super(mymodule,self).__init__()
        self.linear1 = nn.Linear(features,6)
        self.linear2 = nn.Linear(6,4)
        self.linear3 = nn.Linear(4,1)
        self.sigmoid = nn.Sigmoid()

    def forward(self,x):
        y_hat1 = self.sigmoid(self.linear1(x))
        y_hat2 = self.sigmoid(self.linear2(y_hat1))
        y_hat3 = self.sigmoid(self.linear3(y_hat2))

        return y_hat3

# 模型
model = mymodule()

# 损失函数
BCELoss = nn.BCELoss()

# 优化器
optimizer = optim.SGD(model.parameters(),lr=0.01)

# 训练
def Train():
    for inputs,target in Traindataloader:
        y_hat = model(inputs)
        loss = BCELoss(y_hat,target)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

# 测试
def Test():
    total = 0
    correct = 0
    with torch.no_grad():
        for x,y in Testdataloader:
            y_hat = model(x)
            # 像这样逻辑回归的二分类问题，预测值是一个概率
            # 应该对概率值进行处理
            pred = torch.where(y_hat >= 0.5,torch.tensor([1.0]),torch.tensor([0.0]))
            total = y_hat.shape[0]
            correct = (pred == y).sum().item()
    print(f"精确度{100*correct/total}")

if __name__ == "__main__":
    for epoach in range(epoachs):
        Train()
        Test()