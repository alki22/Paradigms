import java.util.TreeMap;
// Mapeo que ordena las keys, en este caso Strings.
// +Info: https://docs.oracle.com/javase/7/docs/api/java/util/TreeMap.html

public class DictTrans {
    public TreeMap<String, String> dict_trans;
    // TreeMap de (palabra, word) o viceversa.
    public boolean reverse;
    // reverse es el sentido de la traducción.

    public DictTrans(boolean is_reverse) {
        this.dict_trans = new TreeMap<String, String>();    
        this.reverse = reverse;
    }
    
    public void add(String word, String trans) {
        this.dict_trans.put(word, trans);
    }
    
    public void load(String path) {
        // leer el archivo y cargar.
    }
    
    public String search(String word) {
        return this.dict_trans.get(word); // devuelve el value asociado a la key "word".
    }
    
    public void save(String path) {
        // Hacer!
    }
}