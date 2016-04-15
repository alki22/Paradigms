import translator.*;
import helpers.*;

import java.io.*;
import java.util.Scanner;

public class Translator {
    private String menu(String word, DictTrans dict_t, DictIgnore dict_i) {
        String result = word;

        System.out.println("There is no translation for the word: " + word);
        System.out.println("Ignore (i) - Ignore All (h) - Translate as (t)" +
                           " - Always translate as (s)");
        
        Scanner reader = new Scanner(System.in);
        char ch = reader.next().charAt(0);

        if (ch == 'i') {
            System.out.println("You chose to ignore the word.\n");
        }
        else if (ch == 'h') {
            System.out.println("You chose to ignore the word, always.\n");
            dict_i.add(word);
        }
        else if (ch == 't') {
            System.out.print("You chose to translate the word as: ");
            result = (String)reader.next();

            if (!(new Helpers().isAlphaNumeric(result))) {
                System.out.println("Word entered is invalid, ignoring the word.\n");
                result = word;
            }
            else {
                System.out.println();
            }
        }
        else if (ch == 's') {
            System.out.print("You chose to translate the word, always, as: ");
            result = (String)reader.next();

            if (new Helpers().isAlphaNumeric(result)) {
                dict_t.add(word, result);
                System.out.println("Word added to dictionary.\n");
            }
            else {
                System.out.println("Word entered is invalid, ignoring the word.\n");
                result = word;
            }
        }

        return result;
    }

    private String translate_word(char[] word, DictTrans dict_t, DictIgnore dict_i) {
        word = new Helpers().polishArray(word);
        String word_str = new String(word);
        String translated_str;

        if (new Helpers().isNumber(word_str)) {
            translated_str = word_str;
        } 
        else {
            boolean lowered = new Helpers().lowerFirstLetter(word);
            word_str = new String(word);
            translated_str = dict_t.search(word_str);

            if (translated_str == null) {
                if (dict_i.is_ignored(word_str)) {
                    translated_str = word_str;
                }
                else {
                    translated_str = menu(word_str, dict_t, dict_i);
                }
            }


            if (lowered) {
                char[] translated = translated_str.toCharArray();
                translated[0] = Character.toUpperCase(translated[0]);
                translated_str = new String(translated);
            }
        }

        return translated_str;
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
                else if (ch == '¿' || ch == '¡') {
                    System.out.println("Found '" + ch + "', ignoring this character.\n");
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
        String dvalue = "dict_t.txt";
        String gvalue = "dict_i.txt";
        String ovalue = "output.txt";
        boolean reverse = false;
        int ch = -1;

        // parsear argumentos
        GetOpt go = new GetOpt(args, "i:d:g:o:r");

        while ((ch = go.getopt()) != go.optEOF) {
            if ((char)ch == 'i')
                ivalue = go.optArgGet();
            else if ((char)ch == 'd')
                dvalue = go.optArgGet();
            else if ((char)ch == 'g')
                gvalue = go.optArgGet();
            else if ((char)ch == 'o')
                ovalue = go.optArgGet();
            else if ((char)ch == 'r')
                reverse = true;
            else System.exit(1);
        }
        File input = new File(ivalue);
        File dictt = new File(dvalue);
        File dictg = new File(gvalue);

        if(!input.exists()) {
            System.out.println("Input file is non existant.");
            System.exit(1);
        }
        if (!dictt.exists()){
            System.out.println("Created empty translation dictionary.");
            dictt.createNewFile();
        }
        if (!dictg.exists()){
            System.out.println("Created empty ignore-words dictionary.");
            dictg.createNewFile();
        }

        // crear dicts
        DictTrans dict_t = new DictTrans(reverse);
        DictIgnore dict_i = new DictIgnore();

        // cargar dicts
        dict_t.load(dvalue);
        dict_i.load(gvalue);

        System.out.println(dvalue + ":");
        dict_t.print();

        System.out.println(gvalue + ":");
        dict_i.print();

        System.out.println("Translating champ...");
        new Translator().translate(ivalue, ovalue, dict_t, dict_i);

        System.out.println("Done.\n\nSaving dictionaries...");
        dict_t.save(dvalue);
        dict_i.save(gvalue);

        System.out.println("Done.");

    }
}