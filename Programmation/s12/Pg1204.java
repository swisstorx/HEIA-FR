//==============================================================================
//  HEIA-FR 
//==============================================================================
package s12;

import java.io.*;

//------------------------------------------------------------------------------
//  Key used: "JAVA"
//    Test coding with file "codeWithVigenere.txt"
//    Test decoding with file "decodeWithVigenere.vig"
//  Key used: "E"
//    Test coding with file "codeWithCesar.txt"
//    Test decoding with file "decodeWithCesar.vig"
//------------------------------------------------------------------------------

public class Pg1204 {

//------------------------------------------------------------------------------
  public static void main(String[] args) {
    String filenameIn="codeWithVigenere.txt";
    String key="JAVA";
    if (args.length==0) {
      System.out.println("No parameter given... Trying with "+filenameIn+" "+key);
    } else if (args.length == 2) {
      filenameIn = args[0];
      key = args[1];
    } else {
      System.out.println("Error: two arguments expected, "
                       + "i.e. filename and uppercase cipher key word.");
      return;
    }
    String filenameOut = filenameIn.substring(0,filenameIn.length() - 4);
    boolean decode;
    if (filenameIn.endsWith(".vig")) {
      filenameOut += ".txt";
      decode = true;
    } else if (filenameIn.endsWith(".txt")) {
      filenameOut += ".vig";
      decode = false;
    } else {
      System.out.println("ERROR: filename should end with '.txt' or '.vig'");
      return;
    }
    // TODO: prepare fileIn/fileOut, call vigenereCypher...
  }

  //----------------------------------------------------------------------------
  // Encrypts/decrypts input using Vigenere's cipher algorithm with given key
  //----------------------------------------------------------------------------
  public static void vigenereCypher(BufferedReader in,  PrintWriter out,
                                    String         key, boolean     decode)
                                                            throws IOException {
    // TODO...
    System.out.println("Finished.");
  }
}