package AVL;

public class AVL {

    private No raiz;

    public AVL() {
        this.raiz = null;
    }

    private int altura(No no) {
        return (no == null) ? 0 : no.getAltura();
    }

    private void atualizarAltura(No no) {
        if(no != null) {
            no.setAltura(1 + Math.max(altura(no.getEsquerda()), altura(no.getDireita())));
        }
    }

    public int fatorBalanceamento(No no) {
        return (no == null) ? 0 : altura(no.getEsquerda()) - altura(no.getDireita());
    }

    private No rotacaoDireita(No y) {
        No x = y.getEsquerda();
        No T2 = x.getDireita();

        x.setDireita(y);
        y.setEsquerda(T2);

        atualizarAltura(y);
        atualizarAltura(x);

        return x;
    }

    private No rotacaoEsquerda(No x) {
        No y = x.getDireita();
        No T2 = y.getEsquerda();

        y.setEsquerda(x);
        x.setDireita(T2);

        atualizarAltura(x);
        atualizarAltura(y);

        return y;
    }

    private No rebalancear(No no) {
        atualizarAltura(no);
        int fb = fatorBalanceamento(no);

        if(fb > 1 && fatorBalanceamento(no.getEsquerda()) >= 0) {
            return rotacaoDireita(no);
        }

        if(fb > 1 && fatorBalanceamento(no.getEsquerda()) < 0) {
            no.setEsquerda(rotacaoEsquerda(no.getEsquerda()));
            return rotacaoDireita(no);
        }

        if(fb < -1 && fatorBalanceamento(no.getDireita()) <= 0) {
            return rotacaoEsquerda(no);
        }

        if(fb < -1 && fatorBalanceamento(no.getDireita()) > 0) {
            no.setDireita(rotacaoDireita(no.getDireita()));
            return rotacaoEsquerda(no);
        }

        return no; // Caso já esteja balanceado
    }

    public void inserir(int chave) {
        raiz = inserirRec(raiz, chave);
    }

    private No inserirRec(No no, int chave) {
        if(no == null) return new No(chave);

        if(chave < no.getChave()) {
            no.setEsquerda(inserirRec(no.getEsquerda(), chave));
        } else if(chave > no.getChave()) {
            no.setDireita(inserirRec(no.getDireita(), chave));
        } else {
            return no;
        }

        return rebalancear(no);
    }

    public void remover(int chave) {
        raiz = removerRec(raiz, chave);
    }

    private No removerRec(No no, int chave) {
        if(no == null) return null;

        if(chave < no.getChave()) {
            no.setEsquerda(removerRec(no.getEsquerda(), chave));
        } else if(chave > no.getChave()) {
            no.setDireita(removerRec(no.getDireita(), chave));
        } else {
            if(no.getEsquerda() == null && no.getDireita() == null) {
                return null;
            }

            if(no.getEsquerda() == null) {
                no = no.getDireita();
            }

            else if(no.getDireita() == null) {
                no = no.getEsquerda();
            }

            else {
                No predecessor = maximo(no.getEsquerda());
                no.setChave(predecessor.getChave());
                no.setEsquerda(removerRec(no.getEsquerda(), predecessor.getChave()));
            }
        }

        if(no == null) return null;

        return rebalancear(no);
    }

    private No maximo(No no) {
        while(no.getDireita() != null) {
            no = no.getDireita();
        }
        return no;
    }

    public void exibirInfoNos() {
        System.out.println("Chave | Altura | Fator de Balanceamento");
        System.out.println("------+--------+-----------------------");
        exibirInfoNosRec(raiz);
    }

    private void exibirInfoNosRec(No no) {
        if(no != null) {
            exibirInfoNosRec(no.getEsquerda());
            System.out.printf("   %-5d|   %-5d|  %d%n",
                    no.getChave(),
                    no.getAltura(),
                    fatorBalanceamento(no));
            exibirInfoNosRec(no.getDireita());
        }
    }

    public void emOrdem() {
        emOrdemRec(raiz);
        System.out.println();
    }

    private void emOrdemRec(No no) {
        if(no != null) {
            emOrdemRec(no.getEsquerda());
            System.out.print(no.getChave() + " ");
            emOrdemRec(no.getDireita());
        }
    }

    public No getRaiz() {
        return raiz;
    }

    public int menorValor() {
        if(raiz == null) throw new IllegalStateException("Arvore vazia");
        return menorValorRec(raiz);
    }

    private int menorValorRec(No no) {
        if(no.getEsquerda() == null) {
            return no.getChave();
        }
        return menorValorRec(no.getEsquerda());
    }

    public int maiorValor() {
        if(raiz == null) throw new IllegalStateException("Arvore vazia");
        return maiorValorRec(raiz);
    }

    private int maiorValorRec(No no) {
        if(no.getDireita() == null) {
            return no.getChave();
        }
        return maiorValorRec(no.getDireita());
    }

    @Override
    public String toString() {
        return "Raiz: " + getRaiz() + "\n";
    }
}