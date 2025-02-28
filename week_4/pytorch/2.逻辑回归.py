from torch import nn
from torch import optim
import torch

# 分析
"""
# 1.本质就是一个分类问题
# 2.线性回归是做一个数值大小的比较，二逻辑回归是一个分类比较，没有对应实数大小与之对应
# 3.分类问题是计算模型训练结果与真实结果匹配的概率
    1）逻辑回归中的激活函数
     既然是概率问题，那么计算的结果肯定是0~1之间的数值，那么需要一个激活函数是计算结果映射到该范围
     这个激活函数就选择sigmod函数= 1 / （1+e**-x）
    2）逻辑回归中的损失函数
     * MSELoss均方误差中是计算真实值与预测值间的距离，让他们越接近越好

     但是对于分类问题，预测值与分类并没有直接的关系，只是划分为这个类的概率，所以一个建立真实概率与预测概率之间的关系
     * 对于二分类问题，使用BCELoss
     * 对于多分类问题，使用交叉熵损失函数

"""


# 二分类问题
# x > 3为通过，y=1,else,y=0

# 数据集
x_data = torch.Tensor([[1],[2],[4],[5]])
y_data = torch.Tensor([[0],[0],[1],[1]])

# 学习率，训练次数
epoachs = 20
lr = 0.5

# 模型构建
class myBinaryLogistic(nn.Module):
    def __init__(self):
        super(myBinaryLogistic,self).__init__()
        # 全连接层
        self.linear = nn.Linear(1,1)
        # 激活函数
        self.sigmoid = nn.Sigmoid()

    def forward(self,x):
        # 计算预测值
        y_hat = self.linear(x)
        # 计算概率
        y_p = self.sigmoid(y_hat)

        return y_p

# 模型实例化
mymodule = myBinaryLogistic()
# 损失函数
myBCELoss = nn.BCELoss()
# 优化器
optimizer = optim.SGD(mymodule.parameters(), lr)

# 开始训练
for epoach in range(epoachs):
    y_hat = mymodule(x_data)
    loss = myBCELoss(y_hat,y_data)

    loss.backward()
    optimizer.step()
    optimizer.zero_grad()

    print(f"第{epoach+1}次训练，损失为：{loss.item()}")

x = torch.Tensor([-1])
y = torch.Tensor([0])
y_hat = mymodule(x)
print(y_hat.item())