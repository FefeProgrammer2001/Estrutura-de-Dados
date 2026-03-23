package AVL;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        AVL avl = new AVL();
        System.out.print("Digite a quantidade de elementos da AVL: ");
        int n = sc.nextInt();

        System.out.println("Digite a os valores da AVL");
        for(int i = 0; i < n; i++) {
            System.out.print("Elemento " + (i+1) + ": ");
            int elemento = sc.nextInt();
            avl.inserir(elemento);
        }

        System.out.println("Informações da árvore:");
        avl.exibirInfoNos();

        System.out.println("Menor elemento: " + avl.menorValor());
        System.out.println("Maior elemento: " + avl.maiorValor());

        System.out.println(avl);
        sc.close();
    }
}
