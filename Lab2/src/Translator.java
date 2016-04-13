import translator.*;
import helpers.*;

import java.io.*;

public class Translator {
    private String translate_word(char[] word, DictTrans dict_t, DictIgnore dict_i) {
        Helpers help = new Helpers();
        word = help.polish_array(word);

        boolean lowered = help.lower_first_letter(word);
        String word_str = new String(word);
        String translated_str = dict_t.search(word_str);

        if (translated_str == null) {
            if (dict_i.is_ignored(word_str)) {
                translated_str = word_str;
            }
            else {
                translated_str = "menu";// menu(word, dict_t, dict_i);
            }
        }

        char[] translated = translated_str.toCharArray();

        if (lowered) {
            translated[0] = Character.toUpperCase(translated[0]);
        }

        return new String(translated);
    }

    private void translate(String ivalue, String ovalue, DictTrans dict_t, DictIgnore dict_i)
            throws IOException {
        char[] word_buffer = new char[100];
        int index = 0;
        word_buffer[0] = '\0';

        try {
            BufferedReader reader = new BufferedReader(new FileReader(ivalue));
            BufferedWriter writer = new BufferedWriter(new FileWriter(ovalue));
            int r;

            while ((r = reader.read()) != -1) {
                char ch = (char) r;

                if (Character.isLetter(ch) || Character.isDigit(ch)) {
                    word_buffer[index] = ch;
                    ++index;
                    word_buffer[index] = '\0';
                }
                else {
                    if (index > 0) {
                        String translated = translate_word(word_buffer, dict_t, dict_i);
                        writer.write(translated);
                    }
                    writer.write(ch);

                    word_buffer = new char[100];
                    index = 0;
                    word_buffer[0] = '\0';
                }
            }
            writer.close();
        }
        catch (IOException e) {
            System.err.println("Caught IOException: " + e.getMessage());
        }
    }

    public static void main(String args[]) throws IOException {
        String ivalue = "input.txt";
        String ovalue = "output.txt";
        boolean reverse = false;

        // parsear argumentos
        DictTrans dict_t = new DictTrans(reverse);
        DictIgnore dict_i = new DictIgnore();

        dict_t.load("dict_t.txt");
        dict_i.load("dict_i.txt");

        System.out.println("dict_t:");
        dict_t.print();

        System.out.println("dict_i:");
        dict_i.print();

        System.out.println("Traduciendo campeón...");
        new Translator().translate(ivalue, ovalue, dict_t, dict_i);
        System.out.println("Listo.");
    }
}