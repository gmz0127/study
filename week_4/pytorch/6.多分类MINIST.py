from torch import optim,nn
import torch
from torch.utils.data import DataLoader
from torchvision import transforms,datasets

"""
对于多分类问题，我们希望最后的输出结果（对于每个类别的预测概率）服从一个已知的分布。例如正态分布等等
在前面的层次使用sigmoid激活函数，在最后的输出层，使用softmax激活函数，最后的输出结果全部求和，结果为1
也就是经过softmax激活函数之后，最后的输出结果都大于等于0，且每一个值对应属于该类别的概率

* 隐藏层激活函数
 nn.Sigmoid()
* 输出层激活函数
 nn.Softmax()
* 多分类损失函数：交叉熵损失
 nn.CrossEntropLoss()
 内部封装了softmax-loss-on_hot流程，实现了对输入特征进行softmax的多分类概率计算，
 然后将输入的target转变为one_hot编码，进行损失计算,这样就不需要拿到target后还要变为ont_hot才能计算损失
 
 
* 计算损失的时候使用one-hot编码
 target = 2,但是预测的结果是对多分类的概率
 假设为四分类，target=2,则他应该对应one-hot编码tensor([[0,0,1,0]) 
 对应的softmax输出结果tensor([[p0],[p1],[p2],[p3]])，这样才能正确的去除损失
 
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
class mymodule(nn.Module):
    def __init__(self):
        super(mymodule,self).__init__()
        self.linear1 = nn.Linear(784,512)
        self.linear2 = nn.Linear(512,256)
        self.linear3 = nn.Linear(256,128)
        self.linear4 = nn.Linear(128,10)
        self.sigmoid = nn.ReLU()
        # 对列数据进行softmax
        self.softmax = nn.Softmax(dim=1)

    def forward(self,x):
        # 因为输入的是图像数据，三维（1,28,28）的，所以需要先改变他的形状
        x = x.reshape(-1,784)
        y_hat1 = self.sigmoid(self.linear1(x))
        y_hat2 = self.sigmoid(self.linear2(y_hat1))
        y_hat3 = self.sigmoid(self.linear3(y_hat2))
        y_hat4 = self.sigmoid(self.linear4(y_hat3))
        y_pred = self.softmax(y_hat4)

        return y_pred

# 获取模型对象
model = mymodule()

# 损失函数
CrossentropLoss = nn.CrossEntropyLoss()

# 优化器
SGD = optim.SGD(model.parameters(),lr=0.1,momentum=0.5)

# 训练
def Train():
    for i,(x,y) in enumerate(Traindataloader):
        y_pre = model(x)
        loss = CrossentropLoss(y_pre,y)
        loss.backward()
        SGD.step()
        SGD.zero_grad()

# 测试
def Test():
    total = 0
    correct = 0
    with torch.no_grad():
        for (x,y) in Testdataloader:
            y_pred = model(x)
            _,pred_num = torch.max(y_pred.data,dim=1)
            correct += ((pred_num == y).sum().item())
            total += x.shape[0]
    print(f"准确率：{100*correct/total}")

epoachs = 20

if __name__ == "__main__":
    for epoach in range(epoachs):
        print(f"第{epoach + 1}次训练")
        Train()
        Test()