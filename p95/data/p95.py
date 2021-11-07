import numpy as np

def cal(N, A):
    S = 0
    a = 1

    for i in range(1, N + 1) :
        a *= A
        S += a * i
    return S

n = 10 # 生成测试点个数
for i in range(1, n + 1) :
    input_file = 'input' + str(i) + '.txt'
    output_file = 'output' + str(i) + '.txt'
    
    if i == 1 :
        N = np.random.randint(1, 150)
        A = 0
    elif i <= n * 0.2 :
        N = np.random.randint(1, 13)
        A = np.random.randint(1, 6)
    elif i <= n * 0.4 :
        N = np.random.randint(13, 19)
        A = np.random.randint(6, 10)
    elif i <= n * 0.8 :
        N = np.random.randint(50, 150)
        A = np.random.randint(10, 15)
    else :
        N = np.random.randint(140, 150)
        A = np.random.randint(14, 16)
    
    S = cal(N, A)
    with open(input_file, 'w', encoding = 'utf-8') as fin :
        fin.write(str(N) + ' ' + str(A))
    
    with open(output_file, 'w', encoding = 'utf-8') as fout :
        fout.write(str(S))
    