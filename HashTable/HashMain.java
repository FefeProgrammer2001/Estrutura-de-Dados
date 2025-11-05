package Hash;

import java.util.Random;
import java.util.Scanner;

public class HashMain {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Random rand = new Random();

        System.out.print("Digite o tamanho da tabela: ");
        int n = sc.nextInt();

        System.out.print("Digite a quantidade de valores: ");
        int qnt = sc.nextInt();

        SondagemLinear sl = new SondagemLinear(n);
        SondagemQuadratica sq = new SondagemQuadratica(n);
        DuploHash dh = new DuploHash(n);

        for (int i = 0; i < qnt; i++) {
            int valor = rand.nextInt(qnt);
            sl.inserir(valor);
            sq.inserir(valor);
            dh.inserir(valor);
        }

        sl.exibirTabela();
        sq.exibirTabela();
        dh.exibirTabela();

        System.out.println();
        System.out.println("Total de colisões (sondagem linear): " + sl.getContadorColisoes());
        System.out.println("Total de colisões (sondagem quadrática): " + sq.getContadorColisoes());
        System.out.println("Total de colisões (duplo hash): " + dh.getContadorColisoes());

        sc.close();
    }
}
