package AVL;

public class Main {
    public static void main(String[] args) {
        AVL avl = new AVL();

        avl.inserir(10);
        avl.inserir(4);
        avl.inserir(6);
        avl.inserir(11);
        avl.inserir(1);
        avl.inserir(3);

        System.out.println("Travessia em ordem");
        avl.emOrdem();

        System.out.println("Informações:");
        avl.exibirInfoNos();

        System.out.println("Menor valor: " + avl.menorValor());
        System.out.println("Maior valor: " + avl.maiorValor());

        System.out.println(avl);
    }
}
