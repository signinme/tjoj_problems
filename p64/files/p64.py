import pandas as pd


class Solution:
    def compute(self):
        # 读取两份EXCEL文件
        df1 = pd.read_excel("data_client_1.xlsx")
        df2 = pd.read_excel("data_client_1_hist.xlsx")
        # WARNING! 以下内容请修改为你处理数据的代码！
        a = df1[df1['if_approved'] == True].shape[0]  / df1.shape[0]
        b = df1[df1['if_used'] == True].shape[0]  / df1[df1['if_approved'] == True].shape[0]
        
        sub_df = df2[['client_no','loan_amt']].groupby("client_no").max()
        c = sub_df["loan_amt"].sum()
        d = 1 - df2[df2['third_interest'] == 0].shape[0] / df2[['client_no','loan_amt']].groupby("client_no").max().shape[0]
        return (a, b, c, d)

# if __name__ == 'main' :
if True :
    sln = Solution()
    res = sln.compute()

    data = [
        0.5904,
        0.34010840108401086,
        81550955.0,
        0.10568031402639216
    ]

    for i in range(len(data)):
        error = res[i]-data[i]
        print("Error:"+str(error))