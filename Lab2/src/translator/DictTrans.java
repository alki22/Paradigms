package translator;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

public class DictTrans {
  public TreeMap<String, String> tmap;
  // TreeMap de (palabra, word) o viceversa.
  public boolean reverse;
  // reverse es el sentido de la traduccion.

  public DictTrans(boolean isReverse) {
    this.tmap = new TreeMap<String, String>();    
    this.reverse = isReverse;
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
        } else {
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
    while (iterator.hasNext()) {
      Map.Entry mentry = (Map.Entry)iterator.next();
      System.out.println("    " + mentry.getKey() + ", " + mentry.getValue());
    }
    System.out.println();
  }

  public void save(String path) throws java.io.FileNotFoundException {
    PrintWriter pw = new PrintWriter(new FileOutputStream(path));

    Set set = this.tmap.entrySet();
    Iterator iterator = set.iterator();

    while (iterator.hasNext()) {
      Map.Entry mentry = (Map.Entry)iterator.next();
      String key = (String)mentry.getKey();
      String value = (String)mentry.getValue();
      if (this.reverse) {
        pw.println(value + ", " + key);
      } else {
        pw.println(key + ", " + value);
      }
    }
    pw.close();
  }
}