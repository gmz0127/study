from torch import optim,nn
import torch
from torch.utils.data import DataLoader
from torchvision import transforms,datasets

"""
出现的问题
1.reshape不能改变原数据形状，他只是返回一个副本，所以在y_hat2.reshape的时候需要用一个变量接收，
或者直接放到线形层中
2.学习率，使用Aadm优化器，刚开始传入的学习率是0.01，准确率非常低，后面改成0.001才达到95%以上

"""
"""
1.此时读取到的手写数字图片是一个PIL数据类型的数组，所以在dataset阶段
要使用数据预处理，把PIL转换为Tensor张量，transforms = transforms.ToTensor()

2. 直接读取的图像数据通常都是(w,h,c) -> (c,w,h)这是Pytorch需要的，
这个时候可以使用transforms.ToTensor()函数

3.卷积网络相关的层
    卷积层：nn.Conv2d(in_channel,out_features,kernerl_size,stride,podding)
    ReLU激活函数：nn.ReLU()
    最大池化层：nn.MaxPool2d(kernel_size)
    连接:nn.Sequential()
    
4.卷积核的设置（可以自定义）

"""
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

# 模型构建
class myCNN(nn.Module):
    def __init__(self):
        super(myCNN,self).__init__()
        self.conv1 = nn.Sequential(nn.Conv2d(in_channels=1,
                                             out_channels=8,
                                             kernel_size=(5,5),
                                             stride=(1,1),
                                             padding=2),
                                   nn.ReLU(),
                                   nn.MaxPool2d(kernel_size=(2,2)))

        self.conv2 = nn.Sequential(nn.Conv2d(in_channels=8,
                                             out_channels=16,
                                             kernel_size=(5, 5),
                                             stride=(1, 1),
                                             padding=2),
                                   nn.ReLU(),
                                   nn.MaxPool2d(kernel_size=(2,2)))

        self.linear1 = nn.Sequential(nn.Linear(7*7*16,1000),
                                    nn.ReLU())
        
        self.linear2 = nn.Sequential(nn.Linear(1000,10),
                                     nn.Softmax(dim=1))

    def forward(self,x):
        y_hat1 = self.conv1(x)
        y_hat2 = self.conv2(y_hat1)
        y_hat3 = self.linear1(y_hat2.reshape(x.shape[0],-1))
        y_hat4 = self.linear2(y_hat3)
        return y_hat4


# 获取模型
model = myCNN()

# 损失函数
crossloss = nn.CrossEntropyLoss()

# 优化器
optimizer = optim.Adam(model.parameters(),lr=0.001)

# 训练
def Train():
    for inputs,target in Traindataloader:
        y_pred = model(inputs)
        loss = crossloss(y_pred,target)
        loss.backward()
        optimizer.step()
        optimizer.zero_grad()

# 测试
def Test():
    total = 0
    correct = 0
    with torch.no_grad():
        for x,y in Testdataloader:
            y_pred = model(x)
            _,pred = torch.max(y_pred,dim=1)
            correct += (pred==y).sum().item()
            total += x.shape[0]
    print(f"准确率：{100*correct/total}")

epoachs = 15

if __name__ == "__main__":
    for epoach in range(epoachs):
        print(f"第{epoach+1}次训练")
        Train()
        Test()