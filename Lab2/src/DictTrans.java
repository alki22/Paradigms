import java.io.*;
import java.util.List;
import java.util.Arrays;
import java.util.TreeMap;
import java.util.Map;

public class DictTrans {
    public TreeMap<String, String> dict_trans;
    // TreeMap de (palabra, word) o viceversa.
    public boolean reverse;
    // reverse es el sentido de la traduccion.

    public DictTrans(boolean is_reverse) {
        this.dict_trans = new TreeMap<String, String>();    
        this.reverse = is_reverse;
    }
    
    public void add(String word, String trans) {
        this.dict_trans.put(word, trans);
    }
    
    public void load(String path) throws java.io.FileNotFoundException, IOException {
        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] words = line.split(", ");
                if (this.reverse) {
                    this.add(words[1], words[0]);
                }
                else {
                    this.add(words[0], words[1]);
                }
            }
        }
    }
    
    public String search(String word) {
        return this.dict_trans.get(word); // devuelve el value asociado a la key "word".
    }
    
    public void save(String path) throws java.io.FileNotFoundException {
        PrintWriter pw = new PrintWriter(new FileOutputStream(path));
        for(Map.Entry<String,String> entry : this.dict_trans.entrySet()) {
            String key = entry.getKey();
            String value = entry.getValue();
            if (this.reverse) {
                pw.println(value + ", " + key);
            }
            else {
                pw.println(key + ", " + value);
            }
        }
        pw.close();
    }
}