package translator;
import java.io.*;
import java.util.List;
import java.util.Arrays;
import java.util.TreeMap;
import java.util.Set;
import java.util.Iterator;
import java.util.Map;

public class DictTrans {
    public TreeMap<String, String> tmap;
    // TreeMap de (palabra, word) o viceversa.
    public boolean reverse;
    // reverse es el sentido de la traduccion.

    public DictTrans(boolean is_reverse) {
        this.tmap = new TreeMap<String, String>();    
        this.reverse = is_reverse;
    }
    
    public void add(String word, String trans) {
        this.tmap.put(word, trans);
    }
    
    public void load(String path) throws java.io.FileNotFoundException, IOException {
        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] words = line.split(", ");

                if (this.reverse) {
                    this.tmap.put(words[1], words[0]);
                }
                else {
                    this.tmap.put(words[0], words[1]);
                }
            }
        }
    }
    
    public String search(String word) {
        // devuelve el value asociado a la key "word".
        String result = this.tmap.get(word);
        return result;
    }
    
    public void print() {
        Set set = this.tmap.entrySet();
        Iterator iterator = set.iterator();
        while(iterator.hasNext()) {
            Map.Entry mentry = (Map.Entry)iterator.next();
            System.out.println("    " + mentry.getValue());
        }
        System.out.println();
    }
    
    public void save(String path) throws java.io.FileNotFoundException {
        PrintWriter pw = new PrintWriter(new FileOutputStream(path));
        for(Map.Entry<String,String> entry : this.tmap.entrySet()) {
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