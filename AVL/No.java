package AVL;

public class No {
    private int chave;
    private int altura;
    private No esquerda;
    private No direita;

    public No(int chave) {
        this.altura = 1; // Considerando a altura do nó folha como 1
        this.chave = chave;
        this.esquerda = null;
        this.direita = null;
    }

    public int getChave() { return chave; }
    public void setChave(int chave) { this.chave = chave; }

    public No getEsquerda() { return esquerda; }
    public void setEsquerda(No esquerda) { this.esquerda = esquerda; }

    public No getDireita() { return direita; }
    public void setDireita(No direita) { this.direita = direita; }

    public int getAltura() { return altura; }
    public void setAltura(int altura) { this.altura = altura; }

    @Override
    public String toString() {
        return String.valueOf(chave);
    }
}
