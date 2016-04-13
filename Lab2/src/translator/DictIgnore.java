package translator;
import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class DictIgnore {
    public ArrayList<String> iglist; // Lista de palabras ignoradas.

    public DictIgnore(){
        this.iglist = new ArrayList<String>();
    }

    public void add(String word) {
        this.iglist.add(word);
    }
    
    public void load(String path) throws java.io.FileNotFoundException, IOException {
        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            String line;
            while ((line = br.readLine()) != null) {
                // Deberiamos chequear si hay algun caracter no deseado en la linea.
                this.add(line);
            }
        }
    }
    
    public boolean is_ignored(String word) {
        return this.iglist.contains(word);
    }

    public void print() {
        for (String word : this.iglist) {
            System.out.println("    " + word);
        }
        System.out.println();
    }
    
    public void save(String path) throws java.io.FileNotFoundException {
        PrintWriter pw = new PrintWriter(new FileOutputStream(path));
        for (String line : this.iglist)
            pw.println(line);
        pw.close();
    }
}
