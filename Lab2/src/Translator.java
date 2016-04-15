import helpers.GetOpt;
import helpers.Helpers;
import translator.DictIgnore;
import translator.DictTrans;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Translator {
  private String menu(String word, DictTrans dictT, DictIgnore dictI) {
    String result = word;

    System.out.println("There is no translation for the word: " + word);
    System.out.println("Ignore (i) - Ignore All (h) - Translate as (t)"
                       + " - Always translate as (s)");
    
    Scanner reader = new Scanner(System.in);
    char ch = reader.next().charAt(0);

    if (ch == 'i') {
      System.out.println("You chose to ignore the word.\n");
    } else if (ch == 'h') {
      System.out.println("You chose to ignore the word, always.\n");
      dictI.add(word);
    } else if (ch == 't') {
      System.out.print("You chose to translate the word as: ");
      result = (String)reader.next();

      if (!(new Helpers().isAlphaNumeric(result))) {
        System.out.println("Word entered is invalid, ignoring the word.\n");
        result = word;
      } else {
        System.out.println();
      }
    } else if (ch == 's') {
      System.out.print("You chose to translate the word, always, as: ");
      result = (String)reader.next();

      if (new Helpers().isAlphaNumeric(result)) {
        dictT.add(word, result);
        System.out.println("Word added to dictionary.\n");
      } else {
        System.out.println("Word entered is invalid, ignoring the word.\n");
        result = word;
      }
    }

    return result;
  }

  private String translate_word(char[] word, DictTrans dictT, DictIgnore dictI) {
    word = new Helpers().polishArray(word);
    boolean lowered = new Helpers().lowerFirstLetter(word);
    String wordStr = new String(word);
    String translatedStr;

    if (new Helpers().isNumber(wordStr)) {
      translatedStr = wordStr;
    } else {
      wordStr = new String(word);
      translatedStr = dictT.search(wordStr);

      if (translatedStr == null) {
        if (dictI.is_ignored(wordStr)) {
          translatedStr = wordStr;
        } else {
          translatedStr = menu(wordStr, dictT, dictI);
        }
      }

      if (lowered) {
        char[] translated = translatedStr.toCharArray();
        translated[0] = Character.toUpperCase(translated[0]);
        translatedStr = new String(translated);
      }
    }

    return translatedStr;
  }

  private void translate(String ivalue, String ovalue, DictTrans dictT, DictIgnore dictI)
      throws IOException {
    char[] wordBuffer = new char[100];
    int index = 0;
    wordBuffer[0] = '\0';

    try {
      BufferedReader reader = new BufferedReader(new FileReader(ivalue));
      BufferedWriter writer = new BufferedWriter(new FileWriter(ovalue));
      int inputChar;

      while ((inputChar = reader.read()) != -1) {
        char ch = (char) inputChar;

        if (Character.isLetter(ch) || Character.isDigit(ch)) {
          wordBuffer[index] = ch;
          ++index;
          wordBuffer[index] = '\0';
        } else if (ch == '¿' || ch == '¡') {
          System.out.println("Found '" + ch + "', ignoring this character.\n");
        } else {
          if (index > 0) {
            String translated = translate_word(wordBuffer, dictT, dictI);
            writer.write(translated);
          }

          writer.write(ch);

          wordBuffer = new char[100];
          index = 0;
          wordBuffer[0] = '\0';
        }
      }
      writer.close();
    } catch (IOException err) {
      System.err.println("Caught IOException: " + err.getMessage());
    }
  }

  /*
   * Hola
   */
  public static void main(String[] args) throws IOException {
    String ivalue = "input.txt";
    String dvalue = "dictT.txt";
    String gvalue = "dictI.txt";
    String ovalue = "output.txt";
    boolean reverse = false;
    int ch = -1;

    // parsear argumentos
    GetOpt go = new GetOpt(args, "i:d:g:o:r");

    while ((ch = go.getopt()) != go.optEOF) {
      if ((char)ch == 'i') {
        ivalue = go.optArgGet();
      } else if ((char)ch == 'd') {
        dvalue = go.optArgGet();
      } else if ((char)ch == 'g') {
        gvalue = go.optArgGet();
      } else if ((char)ch == 'o') {
        ovalue = go.optArgGet();
      } else if ((char)ch == 'r') {
        reverse = true;
      } else {
        System.exit(1);
      }
    }
    File input = new File(ivalue);
    File dictt = new File(dvalue);
    File dictg = new File(gvalue);

    if (!input.exists()) {
      System.out.println("Input file is non existant.");
      System.exit(1);
    }
    if (!dictt.exists()) {
      System.out.println("Created empty translation dictionary.");
      dictt.createNewFile();
    }
    if (!dictg.exists()) {
      System.out.println("Created empty ignore-words dictionary.");
      dictg.createNewFile();
    }

    // crear dicts
    DictTrans dictT = new DictTrans(reverse);
    DictIgnore dictI = new DictIgnore();

    // cargar dicts
    dictT.load(dvalue);
    dictI.load(gvalue);

    System.out.println(dvalue + ":");
    dictT.print();

    System.out.println(gvalue + ":");
    dictI.print();

    System.out.println("Translating champ...");
    new Translator().translate(ivalue, ovalue, dictT, dictI);

    System.out.println("Done.\n\nSaving dictionaries...");
    dictT.save(dvalue);
    dictI.save(gvalue);

    System.out.println("Done.");

  }
}