import numpy as np
import pandas as pd

class cards: # 扑克牌栈类
    types = ['Spade', 'Heart', 'Club', 'Diamond']
    numbers = ['A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K']
    data = pd.DataFrame({'type':[],'number':[]})
    def __init__(self):
        pass
    
    def Append(self, type_, number_) : #插入一张牌
        new_data = pd.DataFrame({'type':[type_],'number':[number_]},index=[0])
        self.data = new_data.append(self.data, ignore_index=True)
        
    def Extract(self, type_) : # 抽取一类牌
        t = self.data.loc[self.data['type'] == type_]
        if t.shape[0] == 0 :
            return
        self.data = self.data.drop(t.index)
        t = t.sort_values(by='number', ascending=False)
        self.data = self.data.append(t, ignore_index = True)
    
    def Revert(self) : # 反转牌堆
        self.data = self.data.iloc[::-1]
        self.data.reset_index(drop=True, inplace=True)
        
    def Pop(self) : # 弹出排队顶的牌
        if self.data.shape[0] == 0 : # 没有则跳过
            return
        self.data = self.data.drop(self.data.tail(1).index)
    
    def Top(self) : # 查找牌堆顶的牌
        return self.data.tail(1)
    
    # def Display(self) :
    #     print(self.data) # 展示牌堆

n = 10 # 测试点个数
for i in range(1, n + 1) :
    input_file = 'input' + str(i) + '.txt'
    output_file = 'output' + str(i) + '.txt'
    
    if i <= n * 0.2 :
        E = False # 是否有Extract操作
        R = False # 是否有Revert操作
        num = 20    # 测试指令数
    elif i <= n * 0.4 :
        E = False
        R = True
        num = 50
    else :
        E = True
        R = True
        num = 200

    test_data = str(num) + '\n'
    ans_data = ''
    c = cards()
    for j in range(0, num) :
        type_ = np.random.randint(0, 4) # 生成类型
        number_ =np.random.randint(0, 13) # 生成点数
        if E == True and np.random.uniform(0, 1) <= min(j / num, 0.15) : # 生成Extract操作
            test_data += 'Extract ' + c.types[type_] + '\n'
            c.Extract(type_)
        elif R == True and np.random.uniform(0, 1) <= min(j / num, 0.15) : # 生成Revert操作
            test_data += 'Revert' + '\n'
            c.Revert()
        elif np.random.uniform(0, 1) <= max(min(1 - j / num, 0.4),0.2) : # 生成pop操作
            test_data += 'Pop' + '\n'
            if c.data.shape[0] == 0 :
                ans_data += 'NULL\n' 
            else :
                ans_data += c.types[int(c.data.values[-1][0])] + ' ' + c.numbers[int(c.data.values[-1][1])] + '\n'
            c.Pop()
        else : # 生成Append操作
            test_data += 'Append ' + c.types[type_] + ' ' + c.numbers[number_] + '\n'
            c.Append(type_, number_)
    
    if c.data.shape[0] == 0 :
        ans_data += 'NULL\n'
    else :
        for j in range(c.data.shape[0] - 1, -1, -1) :
            ans_data += c.types[int(c.data.values[j][0])] + ' ' + c.numbers[int(c.data.values[j][1])] + '\n'
    
    with open(input_file, 'w') as fin :
        fin.write(test_data)
    with open(output_file, 'w') as fout:
        fout.write(ans_data)