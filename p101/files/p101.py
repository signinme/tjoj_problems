# p101 数列中的最大值 随机测试数据生成程序
# 张校 2021-10-9
# lertcode题目链接  https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof/
import numpy as np

class Queue :
    def __init__(self, n) :
        self.n = n
        self.queue = []
        self.max_queue = []
        self.error = False
    def enqueue(self, value) :
        if len(self.queue) == self.n :
            self.error = True
            return 0
        else :
            self.queue.append(value)
            while len(self.max_queue) > 0 and self.max_queue[len(self.max_queue) - 1] < value :
                self.max_queue.pop()
            self.max_queue.append(value)
            self.error = False
            
    def dequeue(self) :
        if len(self.queue) == 0:
            self.error = True
            return 0
        value = self.queue.pop(0)
        if value == self.max_queue[0] :
            self.max_queue.pop(0)
        self.error = False
        return value
    
    def max_elem(self) :
        if len(self.queue) == 0 :
            self.error = True
            return 0
        self.error = False
        return self.max_queue[0]
        # return max(self.queue)
    
    def full(self) :
        return len(self.queue) == self.n
    
    def percentage(self) : # 队列中元素个数占比，在实际测试中，对于后80的操作，保证队列中元素占比不小于85%
        return len(self.queue) / self.n

test_num = 10 # 测试点个数
for i in range(1, test_num + 1) :
    input_file = 'input' + str(i) + '.txt'
    output_file = 'output' + str(i) + '.txt'
    
    test = '' # 生成测试文本
    ans = '' # 生成答案文本
    
    if i <= 2 :           # 20%数据
        que_size = 100
        max_num = 10000
    elif i <= 4 :        # %40数据
        que_size = 6000
        max_num = 1000000
    else :               # 100%数据
        que_size = 10000
        max_num = 100000000 
    
    ope_num = int(que_size * (10 + np.random.rand()))# 操作个数
    base_num = np.random.randint(-1000000000,1000000000) # min(m)，反正打不了表，也没必要取到0x80000000和0x7fffffff○( ＾皿＾)っHiahiahia…
    Que = Queue(que_size)
    
    test += str(que_size) + '\n'
    
    last_ope = 'dequeue' # 上一个测试操作，小概率连续测试max
    
    for j in range(0, ope_num) :
        # 在前5%的操作中，试图清空队列，测试队列判空(至多50条指令)
        # 在前5%到前20%的操作中，试图填满队列，测试队列判满
        # 在后80%操作中，测试判max，以enqueue、dequeue和max交替为主，避免连续empty或full
        
        ope = np.random.uniform(0, 1)
        sel = np.random.uniform(0, 1)
        if j <= ope_num * 0.05 and j <= 50: 
            if ope < 0.5 : # 生成dequeue
                test += 'dequeue\n'
                value = Que.dequeue()
                if Que.error == True :
                    ans += 'Queue is Empty\n'
                else :
                    ans += str(value) + '\n'
            elif ope < 0.9 : # 生成enqueue
                num = base_num + np.random.randint(0, max_num)
                test += 'enqueue ' + str(num) + '\n'
                Que.enqueue(num)
                if  Que.error == True :
                    ans += 'Queue is Full\n'
            else : # 生成max
                test += 'max\n'
                value = Que.max_elem()
                if Que.error == True :
                    ans += 'Queue is Empty\n'
                else :
                    ans += str(value) + '\n'
        
        elif j <= ope_num * 0.2 :
            if ope < 0.8 and (Que.full() == True and sel < 0.3) or (Que.full() == False and sel < 0.8) :
                num = base_num + np.random.randint(0, max_num)
                test += 'enqueue ' + str(num) + '\n'
                Que.enqueue(num)
                if Que.error == True :
                    ans += 'Queue is Full\n'
            elif ope < 0.6 :
                test += 'dequeue\n'
                value = Que.dequeue()
                if Que.error == True :
                    ans += 'Queue is Empty\n'
                else :
                    ans += str(value) + '\n'
            else :
                test += 'max\n'
                value = Que.max_elem()
                if Que.error == True :
                    ans += 'Queue is Empty\n'
                else :
                    ans += str(value) + '\n'
                    
        else :
            if Que.percentage() >= 0.85 and ope <= 0.6 and ((last_ope == 'max' and sel <= 0.1) or (last_ope != 'max' and sel <= 0.8)) :
                test += 'max\n'
                value = Que.max_elem()
                if Que.error == True :
                    ans += 'Queue is Empty\n'
                else :
                    ans += str(value) + '\n'
                last_ope = 'max'
            elif Que.percentage() <= 0.85 or (ope <= 0.9 and ((Que.full() == True and sel <= 0.2) or (Que.full() == False and sel <= 0.95))) :
                if i % 2 == 0 : # 保证打表搜索时，至少有一半的数据搜索长度大于1e6
                    num = base_num + np.random.randint(0, max_num)
                else :
                    num = base_num + np.random.randint( - max_num, 0) 
                test += 'enqueue ' + str(num) + '\n'
                Que.enqueue(num)
                if Que.error == True :
                    ans += 'Queue is Full\n'
                last_ope = 'enqueue'
            else :
                test += 'dequeue\n'
                value = Que.dequeue()
                if Que.error == True :
                    ans += 'Queue is Empty\n'
                else :
                    ans += str(value) + '\n'
                last_ope = 'dequeue'
        
    test += 'quit'
    ans += str(Que.queue[0])
    for j in range(1, len(Que.queue)) :
        ans += ' ' + str(Que.queue[j])
    ans += '\n'
    
    with open(input_file, 'w') as fin :
        fin.write(test)
    with open(output_file, 'w') as fout :
        fout.write(ans)