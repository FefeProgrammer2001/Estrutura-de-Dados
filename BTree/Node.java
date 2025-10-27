package BTree;

public class Node {
    private int t;
    private int n;
    private int[] keys;
    private Node[] children;
    private boolean leaf;

    public Node(int t, boolean leaf) {
        this.t = t;
        this.leaf = leaf;
        this.keys = new int[2 * t - 1];
        this.children = new Node[2 * t];
        this.n = 0;
    }

    public int getT() { return t; }

    public int getN() { return n; }
    public void setN(int n) { this.n = n; }

    public int[] getKeys() { return keys; }
    public void setKey(int index, int value) { this.keys[index] = value; }

    public Node[] getChildren() { return children; }
    public void setChild(int index, Node child) { this.children[index] = child; }

    public boolean isLeaf() { return leaf; }
    public void setLeaf(boolean leaf) { this.leaf = leaf; }

    public void printNode(int level) {
        System.out.print("Nível " + level + ": ");
        for(int i = 0; i < n; i++) {
            System.out.print(keys[i] + " ");
        }
        System.out.println();
        if(!leaf) {
            for(int i = 0; i <= n; i++) {
                if(children[i] != null)
                    children[i].printNode(level + 1);
            }
        }
    }
}
