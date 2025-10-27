package BTree;

import java.util.Scanner;

public class BMain {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Digite o grau mínimo da árvore: ");
        int grau = sc.nextInt();
        BTree tree = new BTree(grau);

        System.out.print("Digite a quantidade de elementos: ");
        int n = sc.nextInt();
        System.out.println("Insira os nós da árvore:");
        for(int i = 0; i < n; i++) {
            System.out.print("Node " + (i+1) + ": ");
            int value = sc.nextInt();
            tree.insert(value);
        }

        tree.print();
        sc.close();
    }
}
