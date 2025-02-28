from torch.utils.data import Dataset
from torch.utils.data import DataLoader

"""
1.Dataset
    * 抽象类，可以编写属于我们自己的数据集Dataset类,通常有以下功能：
    class mydataset(Dataset):
        def __init__(self):
            pass
        def __getitem__(self,index):
            pass
        def __len__(self):
            pass
    * 数据集加载
        # __init__中加载：数据数量较少，不会占太大内存（创建dataset子类就马上把数据集写道内存）
        # 需要的时候再加载：数据数量大，占内存多，在其他方法中在加载数据集，方法运行完就释放
2.DataLoader
    * my_datas = DataLoader(dataset="自己的Dataset子类",batch_size,shuffle=True，tansform)
    * 用于随机梯度下降mini_batch的划分
    * 返回值是一个个batch数据集，每个数据集是元组形式(x,y)
"""

