import java.io.*;
import java.util.List;
import java.util.Arrays;
import java.util.Collections;

public class DictIgnore {
    public List<String> dict_ignore; // Lista de palabras ignoradas.

    public DictIgnore(){
        this.dict_ignore = Collections.<String>emptyList();
    }

    public void add(String word) {
        this.dict_ignore.add(word);
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
        return this.dict_ignore.contains(word);
    }
    
    public void save(String path) throws java.io.FileNotFoundException {
        PrintWriter pw = new PrintWriter(new FileOutputStream(path));
        for (String line : this.dict_ignore)
            pw.println(line);
        pw.close();
    }
}
