package HashMap;

import java.util.List;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        MyHashMap<String, Integer> map = new MyHashMap<>();

        List<Thread> threads = List.of(
            new Thread(() -> map.put("chave1", 1)),
            new Thread(() -> map.put("chave2", 2)),
            new Thread(() -> map.put("chave3", 3))
        );

        threads.forEach(Thread::start);
        for(Thread t : threads) t.join();

        System.out.println("Tamanho final: " + map.size());

        map.get("chave2")
           .ifPresent(v -> System.out.println("Valor da chave2: " + v));
    }
}
