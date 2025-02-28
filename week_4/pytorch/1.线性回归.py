from torch import nn
from torch import optim
import torch
"""
* 模型基类
nn.Module是所有模型类的基类，封装了很多成员方法
自己写的模型必须要继承该基类
必须包含初始化，然后在里面初始化父类：super(mymodule_name,self).__init__()
必须包含forward前向计算函数

* 线性回归函数
nn.Linear(in_features,out_features),是一个类，里面有两个Tensor成员:weight,bias
in_features:每条数据的输入特征数量
out_features:输出的特征数量（相当于几个神经元）

* 损失函数
nn.MSELoss(size_average=True，reduce=True)
size_average:是否把本次训练的所有样本计算出来的损失进行求均值（1/N*Loss）
reduce:将为处理，看是不是要对损失求和，
默认True,所以最后求出来的loss是一个一维的Tensor，使用loss.item()变成一个标量

* 优化器
SGD优化器：torch.optim.SGD(module.parameters(),lr)
module.parameters:要进行优化的参数
lr：学习率

"""
# 数据集的准备
x_data = torch.Tensor([[1],[2],[3]])
y_data = torch.Tensor([[2],[4],[6]])

# 规定学习率，训练次数
lr = 0.1
epoachs = 5

# 构造模型
class MyLinear(nn.Module):
    def __init__(self):
        # 初始化父类构造
        super(MyLinear,self).__init__()
        # 构建自己的模型
        self.linear = nn.Linear(1,1)

    def forward(self,x):
        y_hat = self.linear(x)
        return y_hat

# 实例化模型对象
mymodule = MyLinear()
# 获取损失函数计算对象
myloss = nn.MSELoss()
# 获取优化器
optimizer = optim.SGD(mymodule.parameters(),lr)

# 开始训练
for i in range(epoachs):
    # 获取预测值
    y_hat = mymodule(x_data)
    # 计算损失
    loss = myloss(y_data,y_hat)
    # 反向传播
    loss.backward()
    # 参数更新
    optimizer.step()
    # 梯度清零
    optimizer.zero_grad()
    # 打印损失
    print(f"第{i}次训练，损失为：{loss.item()}")

print(mymodule.linear.weight)