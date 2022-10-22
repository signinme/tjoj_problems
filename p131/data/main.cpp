class BinaryTree {
private:
    TreeNode *root;
public:
    BinaryTree(const std::vector<int> &order) {
        int index = 0;
        root = buildTreeDFS(order, index);
    }
    ~BinaryTree() {
        if( root != nullptr )
            delete root;
    }
    TreeNode *getRoot() {
        return root;
    }
private:
    TreeNode *buildTreeDFS(const std::vector<int> &order, int &index) {
        if( index >= order.size() || order[index] == -1 ) {
            index ++;
            return nullptr;
        }
        return new TreeNode(order[index ++], buildTreeDFS(order, index), buildTreeDFS(order, index));
    }
};

int main() {
    int x, num_nodes = 0, num_null = 0;
    std::vector<int> order;
    while( cin >> x ) {
        order.push_back(x);
        if( x == -1 ) {
            num_null ++;
            if( num_null == num_nodes + 1) {
                break;
            }
        }
        else {
            num_nodes ++;
        }
    }
    BinaryTree bt(order); // 构造二叉树
    Solution solution;
    std::vector<int> ans(solution.postorderTraversal(bt.getRoot())); // 调用Solution::postorderTraversal
    for( int i = 0; i < ans.size(); i ++ ) { // 打印结果
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}