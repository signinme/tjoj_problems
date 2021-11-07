import numpy as np

# 生成结果为true的表达式
def gen_true_expression(f, b, n, l) : #头部、非、括号、剩余长度、计算优先级
    if n >= 2 and np.random.uniform(0, 1) <= 0.3 : # 生成空格
        return ' ' + gen_true_expression(f, b, n - 1, l)
    if n >= 3 and b == True and np.random.uniform(0, 1) <= 0.2: # 生成括号
        return '(' + gen_true_expression(f, b, n - 2, 0) + ')'
    if l == 0 : # 或级，能生成或、与、非和单字母
        if n >= 2 and f == True and np.random.uniform(0, 1) <= 0.1 : # 生成非
            return '!' + gen_false_expression(f, b, (n - 1), 2)
        if n < 3 or (n <= 5 and np.random.uniform(0, 1) <= 0.3) : # 生成单字母
            return 'V'
        if np.random.uniform(0, 1) <= 0.25 : # 生成与
            return gen_true_expression(f, b, (n - 1) / 2, 1) + '&' + gen_true_expression(f, b, (n - 1) / 2, 1)
        c = np.random.uniform(0, 1)
        # 生成或
        if c <= 0.33 :
            s1 = gen_true_expression(f, b, (n - 1) / 2, 0)
            s2 = gen_false_expression(f, b, (n - 1) / 2, 0)
        elif c <= 0.66 :
            s1 = gen_false_expression(f, b, (n - 1) / 2, 0)
            s2 = gen_true_expression(f, b, (n - 1) / 2, 0)
        else :
            s1 = gen_true_expression(f, b, (n - 1) / 2, 0)
            s2 = gen_true_expression(f, b, (n - 1) / 2, 0)
        return s1 + '|' + s2
    if l == 1 : # 与级，能生成与、非和单字母
        if n >= 2 and f == True and np.random.uniform(0, 1) <= 0.1 : # 生成非
            return '!' + gen_false_expression(f, b, (n - 1), 2)
        if n < 3 or (n <= 5 and np.random.uniform(0, 1) <= 0.3) : # 生成单字母
            return 'V'
        # 生成与
        return gen_true_expression(f, b, (n - 1) / 2, 1) + '&' + gen_true_expression(f, b, (n - 1) / 2, 1)
    if l == 2 : # 非级，能生成非和单字母
        if n >= 3 and b == True and np.random.uniform(0, 1) <= min(n / 50, 0.8): # 生成括号
            return '(' + gen_true_expression(f, b, n - 2, 0) + ')'
        if n < 2 or np.random.uniform(0, 1) <= 0.9 : # 生成单字母
            return 'V'
        return '!' + gen_false_expression(f, b, (n - 1), 2)
    return 'V'

# 生成结果为false的表达式 
def gen_false_expression(f, b, n, l) :
    if n >= 2 and np.random.uniform(0, 1) <= 0.3 : # 生成空格
        return ' ' + gen_false_expression(f, b, n - 1, l)
    if n >= 3 and b == True and np.random.uniform(0, 1) <= 0.2: # 生成括号
        return '(' + gen_false_expression(f, b, n - 2, 0) + ')'
    if l == 0 : # 或级，能生成或、与、非和单字母
        if n >= 2 and f == True and np.random.uniform(0, 1) <= 0.1 : # 生成非
            return '!' + gen_true_expression(f, b, (n - 1), 2)
        if n < 3 or (n <= 5 and np.random.uniform(0, 1) <= 0.1) : # 生成单字母
            return 'F'
        if np.random.uniform(0, 1) <= 0.75 : # 生成与
            c = np.random.uniform(0, 1)
            
            if c <= 0.33 :
                s1 = gen_true_expression(f, b, (n - 1) / 2, 1)
                s2 = gen_false_expression(f, b, (n - 1) / 2, 1)
            elif c <= 0.66 :
                s1 = gen_false_expression(f, b, (n - 1) / 2, 1)
                s2 = gen_true_expression(f, b, (n - 1) / 2, 1)
            else :
                s1 = gen_false_expression(f, b, (n - 1) / 2, 1)
                s2 = gen_false_expression(f, b, (n - 1) / 2, 1)
            return s1 + '&' + s2
        # 生成或
        return gen_false_expression(f, b, (n - 1) / 2, 0) + '|' + gen_false_expression(f, b, (n - 1) / 2, 0)
        
    if l == 1 : # 与级，能生成与、非和单字母
        if n >= 2 and f == True and np.random.uniform(0, 1) <= 0.1 : # 生成非
            return '!' + gen_true_expression(f, b, (n - 1), 2)
        if n < 3 or (n <= 5 and np.random.uniform(0, 1) <= 0.3) : # 生成单字母
            return 'F'
        # 生成与
        c = np.random.uniform(0, 1)
        if c <= 0.33 :
            s1 = gen_true_expression(f, b, (n - 1) / 2, 1)
            s2 = gen_false_expression(f, b, (n - 1) / 2, 1)
        elif c <= 0.66 :
            s1 = gen_false_expression(f, b, (n - 1) / 2, 1)
            s2 = gen_true_expression(f, b, (n - 1) / 2, 1)
        else :
            s1 = gen_false_expression(f, b, (n - 1) / 2, 1)
            s2 = gen_false_expression(f, b, (n - 1) / 2, 1)
        return s1 + '&' + s2
    if l == 2 : # 非级，能生成非和单字母
        if n >= 3 and b == True and np.random.uniform(0, 1) <= min(n / 50, 0.8): # 生成括号
            return '(' + gen_false_expression(f, b, n - 2, 0) + ')'
        if l < 2 or np.random.uniform(0, 1) <= 0.9 : # 生成单字母
            return 'F'
        return '!' + gen_true_expression(f, b, (n - 1), 2)
    return 'F'


n = 10 # 测试数据个数
for i in range(1, n + 1) :
    input_file = 'input' + str(i) + '.txt'
    output_file = 'output' + str(i) + '.txt'
    
    test_data = ''
    ans_data = ''
    f = True if i > n * 0.2 else False # 允许出现!
    b = True if i > n * 0.4 else False # 允许出现()
    if i <= n * 0.2 :
        test_num = 5
        str_len = 20
    elif i <= n * 0.4 :
        test_num = 10
        str_len = 50
    else :
        test_num = 20
        str_len = 100
    for j in range(0, test_num) :
        if np.random.uniform(0, 1) < 0.5 : # True
            test_data = test_data + gen_true_expression(f, b, str_len, 0) + '\n'
            ans_data = ans_data + 'Expression ' + str(j + 1) + ': V' + '\n'
        else : # False
            test_data = test_data + gen_false_expression(f, b, str_len, 0) + '\n'
            ans_data = ans_data + 'Expression ' + str(j + 1) + ': F' + '\n'
    
    with open(input_file, 'w') as fin :
        fin.write(test_data)
    
    with open(output_file, 'w') as fout :
        fout.write(ans_data)

# print(gen_true_expression(True, True, 20, 0))