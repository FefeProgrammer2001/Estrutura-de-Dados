package Hash;

public class SondagemQuadratica {
    private int[] tabela;
    private boolean[] ocupado;
    private int tamanho;
    private int contadorColisoes;

    public SondagemQuadratica(int tamanho) {
        this.tamanho = tamanho;
        this.tabela = new int[tamanho];
        this.ocupado = new boolean[tamanho];
        this.contadorColisoes = 0;
    }

    private int hash(int chave) {
        return chave % tamanho;
    }

    public void inserir(int chave) {
        int indice = hash(chave);
        int indiceOriginal = indice;
        int i = 0;

        while(ocupado[indice]) {
            contadorColisoes++;
            i++;
            indice = (indiceOriginal + i * i) % tamanho;

            if(i == tamanho) {
                System.out.println("Tabela cheia! Não foi possível inserir a chave: " + chave);
                return;
            }
        }

        tabela[indice] = chave;
        ocupado[indice] = true;
    }

    public boolean buscar(int chave) {
        int indice = hash(chave);
        int indiceOriginal = indice;
        int passo = 0;

        while(ocupado[indice]) {
            if(tabela[indice] == chave) return true;
            passo++;
            indice = (indiceOriginal + passo) % tamanho;
            if(passo == tamanho) break;
        }
        return false;
    }

    public void exibirTabela() {
        System.out.println("\n--- Tabela Hash (Sondagem Quadrática) ---");
        for(int i = 0; i < tamanho; i++) {
            System.out.printf("[%02d] -> %s\n", i, ocupado[i] ? String.valueOf(tabela[i]) : "vazio");
        }
        System.out.println("Colisões registradas: " + contadorColisoes);
    }

    public int getContadorColisoes() {
        return contadorColisoes;
    }
}
