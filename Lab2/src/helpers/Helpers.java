package helpers;
import java.util.Arrays;

public class Helpers {
    public boolean lowerFirstLetter(char[] word) {
        boolean result;
        if (Character.isUpperCase(word[0])) {
            result = true;
            word[0] = Character.toLowerCase(word[0]);
        }
        else {
            result = false;
        }
        return result;
    }

    public char[] polishArray(char[] word) {
    	// Darle el largo justo al array.
    	int length = 0;
        for (int i = 0; i < 100; ++i) {
            if (word[i] != '\0')
                ++length;
            else
                break;
        }

        char[] result = Arrays.copyOfRange(word, 0, length);
        return result;
    }

    public boolean isAlphaNumeric(String word) {
        boolean result = true;
        for (char ch : word.toCharArray())
            result = result && Character.isLetterOrDigit(ch);
        return result;
    }

    public boolean isNumber(String word) {
        boolean result = true;
        for (char ch : word.toCharArray())
            result = result && Character.isDigit(ch);
        return result;
    }
}