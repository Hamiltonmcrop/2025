public class BinarySearchTree {
    
    static class TreeNode {
        int key;
        TreeNode left;
        TreeNode right;
        TreeNode p; // Parent node

        public TreeNode(int key) {
            this.key = key;
            left = null;
            right = null;
            p = null;
        }
    }

    public static TreeNode BSTInsert(TreeNode root, TreeNode z) {
        TreeNode y = null;
        TreeNode x = root;

        while (x != null) {
            y = x;
            if (z.key < x.key)
                x = x.left;
            else
                x = x.right;
        }
        z.p = y;
        if (y == null)
            root = z;
        else if (z.key < y.key)
            y.left = z;
        else
            y.right = z;
        
        return root; // Return the updated root
    }

    public static TreeNode TreeMinimum(TreeNode x) {
        while (x.left != null)
            x = x.left;
        return x;
    }

    public static TreeNode TreeMaximum(TreeNode x) {
        while (x.right != null)
            x = x.right;
        return x;
    }

    public static TreeNode TreeSearch(TreeNode x, int k) {
        if (x == null || k == x.key)
            return x;
        if (k < x.key)
            return TreeSearch(x.left, k);
        else
            return TreeSearch(x.right, k);
    }

    public static void main(String[] args) {
        TreeNode root = null;
        // Testing BSTInsert
        root = BSTInsert(root, new TreeNode(5));
        BSTInsert(root, new TreeNode(3));
        BSTInsert(root, new TreeNode(7));
        BSTInsert(root, new TreeNode(1));
        BSTInsert(root, new TreeNode(4));
        BSTInsert(root, new TreeNode(6));
        BSTInsert(root, new TreeNode(8));

        // Testing TreeMinimum
        TreeNode minNode = TreeMinimum(root);
        System.out.println("Minimum key in the tree: " + minNode.key);

        // Testing TreeMaximum
        TreeNode maxNode = TreeMaximum(root);
        System.out.println("Maximum key in the tree: " + maxNode.key);

        // Testing TreeSearch
        int keyToSearch = 6;
        TreeNode result = TreeSearch(root, keyToSearch);
        if (result != null)
            System.out.println("Key " + keyToSearch + " found in the tree.");
        else
            System.out.println("Key " + keyToSearch + " not found in the tree.");
    }
}

