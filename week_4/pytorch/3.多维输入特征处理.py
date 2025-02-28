from torch import nn

# 每个样本有多个特征输入
# 对于每个样本，称为（行数据）record(分类)，对于每个样本的同一个特征/字段称为feature（列数据）

# 设置一个八个特征输入，（单层神经网络，单个神经元）的二分类模型
class mutilLogistic(nn.Module):
    def __init__(self):
        super(mutilLogistic,self).__init__()
        self.linear = nn.Linear(8,1)
        self.sigmoid = nn.Sigmoid()

    def forward(self,x):
        y_hat = self.linear(x)
        y_p = self.sigmoid(y_hat)
        return y_p

model = mutilLogistic()