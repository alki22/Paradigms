package helpers;
import java.util.Arrays;

public class Helpers {
    public boolean lower_first_letter(char[] word) {
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

    public char[] polish_array(char[] word) {
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
}