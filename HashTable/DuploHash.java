package Hash;

public class DuploHash {
    private int[] tabela;
    private boolean[] ocupado;
    private int tamanho;
    private int contadorColisoes;

    public DuploHash(int tamanho) {
        this.tamanho = tamanho;
        this.tabela = new int[tamanho];
        this.ocupado = new boolean[tamanho];
        this.contadorColisoes = 0;
    }

    private int hash1(int chave) {
        return chave % tamanho;
    }

    private int hash2(int chave) {
        return 1 + (chave % (tamanho - 1));
    }

    public void inserir(int chave) {
        int indice = hash1(chave);
        int passo = hash2(chave);
        int i = 0;

        while(ocupado[indice]) {
            contadorColisoes++;
            i++;
            indice = (hash1(chave) + i * passo) % tamanho;

            if(i == tamanho) {
                System.out.println("Tabela cheia! Não foi possível inserir a chave: " + chave);
                return;
            }
        }

        tabela[indice] = chave;
        ocupado[indice] = true;
    }

    public boolean buscar(int chave) {
        int indice = hash1(chave);
        int passo = hash2(chave);
        int i = 0;

        while(ocupado[indice]) {
            if(tabela[indice] == chave) return true;
            i++;
            indice = (hash1(chave) + i * passo) % tamanho;
            if(i == tamanho) break;
        }
        return false;
    }

    public void exibirTabela() {
        System.out.println("\n--- Tabela Hash (Duplo Hash) ---");
        for(int i = 0; i < tamanho; i++) {
            System.out.printf("[%02d] -> %s\n", i, ocupado[i] ? String.valueOf(tabela[i]) : "vazio");
        }
        System.out.println("Colisões registradas: " + contadorColisoes);
    }

    public int getContadorColisoes() {
        return contadorColisoes;
    }
}
