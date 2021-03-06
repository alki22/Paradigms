package helpers;

public class GetOpt {

  private String[] theArgs = null;
  private int argCount = 0;
  private String optString = null;

  public GetOpt(String[] args, String opts) {
    theArgs = args;
    argCount = theArgs.length;
    optString = opts;
  }

  // user can toggle this to control printing of error messages
  public boolean optErr = false;

  public int processArg(String arg, int num) {
    int value;
    try {
      value = Integer.parseInt(arg);
    } catch (NumberFormatException err) {
      if (optErr) {
        System.err.println("processArg cannot process " + arg
                           + " as an integer");
      }
      return num;
    }
    return value;
  }

  public long processArg(String arg, long num) {
    long value;
    try {
      value = Long.parseLong(arg);
    } catch (NumberFormatException err) {
      if (optErr) {
        System.err.println("processArg cannot process " + arg
                           + " as a long");
      }
      return num;
    }
    return value;
  }

  public double processArg(String arg, double doub) {
    double value;
    try {
      value = Double.valueOf(arg).doubleValue();
    } catch (NumberFormatException err) {
      if (optErr) {
        System.err.println("processArg cannot process " + arg
                           + " as a double");
      }
      return doub;
    }
    return value;
  }

  public boolean processArg(String arg, boolean bool) {
    // `true' in any case mixture is true; anything else is false
    return Boolean.valueOf(arg).booleanValue();
  }

  public float processArg(String arg, float fl) {
    float value;
    try {
      value = Float.valueOf(arg).floatValue();
    } catch (NumberFormatException err) {
      if (optErr) {
        System.err.println("processArg cannot process " + arg
                           + " as a float");
      }
      return fl;
    }
    return value;
  }

  public int tryArg(int index, int num) {
    int value;
    try {
      value = processArg(theArgs[index], num);
    } catch (ArrayIndexOutOfBoundsException err) {
      if (optErr) {
        System.err.println("tryArg: no theArgs[" + index + "]");
      }
      return num;
    }
    return value;
  }

  public long tryArg(int index, long num) {
    long value;
    try {
      value = processArg(theArgs[index], num);
    } catch (ArrayIndexOutOfBoundsException err) {
      if (optErr) {
        System.err.println("tryArg: no theArgs[" + index + "]");
      }
      return num;
    }
    return value;
  }

  public double tryArg(int index, double doub) {
    double value;
    try {
      value = processArg(theArgs[index], doub);
    } catch (ArrayIndexOutOfBoundsException err) {
      if (optErr) {
        System.err.println("tryArg: no theArgs[" + index + "]");
      }
      return doub;
    }
    return value;
  }

  public float tryArg(int index, float fl) {
    float value;
    try {
      value = processArg(theArgs[index], fl);
    } catch (ArrayIndexOutOfBoundsException err) {
      if (optErr) {
        System.err.println("tryArg: no theArgs[" + index + "]");
      }
      return fl;
    }
    return value;
  }

  public boolean tryArg(int index, boolean bool) {
    boolean value;
    try {
      value = processArg(theArgs[index], bool);
    } catch (ArrayIndexOutOfBoundsException err) {
      if (optErr) {
        System.err.println("tryArg: no theArgs[" + index + "]");
      }
      return bool;
    }
    return value;
  }

  public String tryArg(int index, String string) {
    String value;
    try {
      value = theArgs[index];
    } catch (ArrayIndexOutOfBoundsException err) {
      if (optErr) {
        System.err.println("tryArg: no theArgs[" + index + "]");
      }
      return string;
    }
    return value;
  }

  private static void writeError(String msg, char ch) {
    System.err.println("GetOpt: " + msg + " -- " + ch);
  }

  public static final int optEOF = -1;

  private int optIndex = 0;
  
  public int optIndexGet() {
    return optIndex;
  }

  private String optArg = null;
  
  public String optArgGet() {
    return optArg;
  }

  private int optPosition = 1;

  public int getopt() {
    optArg = null;
    if (theArgs == null || optString == null) {
      return optEOF;
    }
    if (optIndex < 0 || optIndex >= argCount) {
      return optEOF;
    }
    String thisArg = theArgs[optIndex];
    int argLength = thisArg.length();
    // handle special cases
    if (argLength <= 1 || thisArg.charAt(0) != '-') {
      // e.g., "", "a", "abc", or just "-"
      return optEOF;
    } else if (thisArg.equals("--")) { // end of non-option args
      optIndex++;
      return optEOF;
    }
    // get next "letter" from option argument
    char ch = thisArg.charAt(optPosition);
    // find this option in optString
    int pos = optString.indexOf(ch);
    if (pos == -1 || ch == ':') {
      if (optErr) {
        writeError("illegal option", ch);
      }
      ch = '?';
    } else { // handle colon, if present
      if (pos < optString.length() - 1 && optString.charAt(pos + 1) == ':') {
        if (optPosition != argLength - 1) {
          // take rest of current arg as optArg
          optArg = thisArg.substring(optPosition + 1);
          optPosition = argLength - 1; // force advance to next arg below
        } else { // take next arg as optArg
          optIndex++;
          if (optIndex < argCount
              && (theArgs[optIndex].charAt(0) != '-'
              || theArgs[optIndex].length() >= 2
              && (optString.indexOf(theArgs[optIndex].charAt(1)) == -1
              || theArgs[optIndex].charAt(1) == ':'))) {
            optArg = theArgs[optIndex];
          } else {
            if (optErr) {
              writeError("option requires an argument", ch);
            }
            optArg = null;
            ch = ':'; // Linux man page for getopt(3) says : not ?
          }
        }
      }
    }
    // advance to next option argument,
    // which might be in thisArg or next arg
    optPosition++;
    if (optPosition >= argLength) {
      optIndex++;
      optPosition = 1;
    }
    return ch;
  }

  public static void main(String[] args) {  // test the class
    GetOpt go = new GetOpt(args, "Uab:f:h:w:");
    go.optErr = true;
    int ch = -1;
    // process options in command line arguments
    boolean usagePrint = false;                 // set
    int aflg = 0;                               // default
    boolean bflg = false;                       // values
    String filename = "out";                    // of
    int width = 80;                             // options
    double height = 1;                          // here
    while ((ch = go.getopt()) != go.optEOF) {
      if      ((char)ch == 'U') {
        usagePrint = true;
      } else if ((char)ch == 'a') {
        aflg++;
      } else if ((char)ch == 'b') {
        bflg = go.processArg(go.optArgGet(), bflg);
      } else if ((char)ch == 'f') {
        filename = go.optArgGet();
      } else if ((char)ch == 'h') {
        height = go.processArg(go.optArgGet(), height);
      } else if ((char)ch == 'w') {
        width = go.processArg(go.optArgGet(), width);
      } else {
        System.exit(1);                     // undefined option
      }
    }                                           // getopt() returns '?'
    if (usagePrint) {
      System.out.println("Usage: -a -b bool -f file -h height -w width");
      System.exit(0);
    }
    System.out.println("These are all the command line arguments "
                       + "before processing with GetOpt:");
    for (int i = 0; i < args.length; ++i) {
      System.out.print(" " + args[i]);
    }
    System.out.println();
    System.out.println("-U " + usagePrint);
    System.out.println("-a " + aflg);
    System.out.println("-b " + bflg);
    System.out.println("-f " + filename);
    System.out.println("-h " + height);
    System.out.println("-w " + width);
    // process non-option command line arguments
    for (int k = go.optIndexGet(); k < args.length; k++) {
      System.out.println("normal argument " + k + " is " + args[k]);
    }
  }
}
